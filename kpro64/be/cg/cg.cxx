/*

  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/


/* ====================================================================
 * ====================================================================
 *
 * Module: cg.cxx
 * $Revision: 1.1.1.1 $
 * $Date: 2005/10/21 19:00:00 $
 * $Author: marcel $
 * $Source: /proj/osprey/CVS/open64/osprey1.0/be/cg/cg.cxx,v $
 *
 * Description:
 *
 * This file contains the main driver and initialization,termination
 * routines for the code generator.
 *
 * ====================================================================
 * ====================================================================
 */

#include "defs.h"
#include "wn.h"
#include "cg.h"
#include "cg_internal.h"
#include "cg_flags.h"
#include "config.h"
#include "config_list.h"
#include "tracing.h"
#include "timing.h"
#include "strtab.h"
#include "cgir.h"
#include "erglob.h"
#include "ercg.h"
#include "data_layout.h"
#include "whirl2ops.h"
#include "calls.h"
#include "bitset.h"
#include "tn_set.h"
#include "gtn_universe.h"
#include "bb_set.h"
#include "register.h"
#include "gra.h"
#include "freq.h"
#include "fb_whirl.h"
#include "lra.h"
#include "cgemit.h"
#include "cg_loop.h"
#include "glob.h"
#include "cgexp.h"
#include "igls.h"
#include "tn_map.h"
#include "cg_region.h"
#include "wn_util.h"
#include "cg_spill.h"
#include "localize.h"
#include "gra_live.h"
#include "opt_alias_interface.h"
#include "ir_reader.h"
#include "cflow.h"
#include "dwarf_DST_mem.h"
#include "region_util.h"
#include "eh_region.h"
#include "reg_live.h"
#include "findloops.h"
#include "cgdriver.h"
#include "label_util.h"
#include "cgtarget.h"
#include "ebo.h"
#include "hb.h"
#include "pqs_cg.h"
#include "tag.h"
#include "ipfec.h"
#include "ipfec_defs.h"
#include "ipfec_options.h"
#include "region_update.h"
#include "region_verify.h"
#include "vt_region.h"
#include "recovery.h"
#include "edge_profile.h"
#include "val_prof.h"
#include "bb_verifier.h"
#include "config_opt.h"
#include "be_util.h"
#include "stride_prefetch.h"
#include "cache_analysis.h"
#include "multi_branch.h"

#define _value_profile_before_region_formation
#define can_invoke_profile_with_current_cg_opt_level (CG_opt_level>1)
//#define can_invoke_profile_with_current_cg_opt_level (1)

MEM_POOL MEM_local_region_pool; /* allocations local to processing a region */
MEM_POOL MEM_local_region_nz_pool;

BOOL Trace_REGION_Interface = FALSE;

INT32 current_PU_handle = 0;
INT32 rse_budget;

BOOL PU_Has_Calls;
BOOL PU_References_GP;
BOOL GRA_optimize_restore_pr;
BOOL GRA_optimize_restore_b0_ar_pfs;
BOOL GRA_optimize_restore_ar_lc;
BOOL EBO_data_spec;
// Control assemly output on file number
typedef mempool_allocator<INT> INT_ALLOC;
typedef std::vector<INT, INT_ALLOC>  INT_CONTAINER;

static INT_CONTAINER asm_file_visited;
INT Asm_File_Visited(INT file_number)
{   
    INT i = 1;
    INT_CONTAINER::iterator iter;
    for(iter = asm_file_visited.begin();iter != asm_file_visited.end();iter++)
    {
        if (*iter == file_number) return i;
        i++;
    }
    asm_file_visited.push_back(file_number);
    return i;
}

BOOL CG_PU_Has_Feedback;

BOOL RGN_Formed = FALSE;

BOOL gra_pre_create = TRUE; 

BOOL edge_done = FALSE;

RID *Current_Rid;

TN_MAP TN_To_PREG_Map;

/* WOPT alias manager */
struct ALIAS_MANAGER *Alias_Manager;

static BOOL Orig_Enable_SWP;
extern BOOL gra_self_recursive;
extern BOOL fat_self_recursive;

/* Stuff that needs to be done at the start of each PU in cg. */
void
CG_PU_Initialize (WN *wn_pu)
{
  static INT pu_num;

  MEM_POOL_Push ( &MEM_phase_pool );
  MEM_POOL_Push ( &MEM_local_pool );
  MEM_POOL_Push ( &MEM_phase_nz_pool );
  MEM_POOL_Push ( &MEM_local_nz_pool );

  PU_Has_Calls = FALSE;
  PU_References_GP = FALSE;
  GRA_optimize_restore_pr = TRUE;
  GRA_optimize_restore_b0_ar_pfs = TRUE;
  GRA_optimize_restore_ar_lc = TRUE;
  EBO_data_spec=FALSE;

  Regcopies_Translated = FALSE;

  CG_Configure_Opt_Level((   pu_num < CG_skip_before
              || pu_num > CG_skip_after
              || pu_num == CG_skip_equal)
             ? 0 : Opt_Level);
  pu_num++;

  if (PU_has_syscall_linkage(Get_Current_PU())) {
    // turn off swp so stacked registers are preserved
    Orig_Enable_SWP = Enable_SWP;
    Enable_SWP = FALSE;
  }

  Reuse_Temp_TNs = (CG_opt_level == 0);
  if (Get_Trace (TP_CGEXP, 1024)) Reuse_Temp_TNs = FALSE;

  CGTARG_Initialize();
  BB_PU_Initialize ();
  Init_TNs_For_PU ();
  LOOP_DESCR_Init_For_PU();
  TN_MAP_Init();
  BB_MAP_Init();
  REGION_MAP_Init();
  OP_MAP_Init();
  CGSPILL_Initialize_For_PU ();
  CFLOW_Initialize();
  CG_LOOP_Init();
  HB_Init();
  if (Enable_CG_Peephole) EBO_Init();
  Init_Label_Info();

#ifdef EMULATE_LONGLONG
  extern void Init_TN_Pair();
  Init_TN_Pair ();
#endif

  /* initialize register package for current pu */
  REGISTER_Pu_Begin();

  Init_Entry_Exit_Code (wn_pu);
  REGISTER_Reset_FP();  // in case $fp is used, must be after entry_exit init

  /* Initialize global tn universe */
  GTN_UNIVERSE_Pu_Begin();

  Trace_REGION_Interface = Get_Trace( TP_REGION, TT_REGION_CG_DEBUG ) ||
    Get_Trace(TP_REGION, TT_REGION_BOUND_DEBUG );

  Init_gen_quad_preg(); // init statics to hold quad preg STs

  /* data layout and lowering now happens earlier, in bedriver. */
  /* don't finalize stack frame until just before emit, after all spills. */

  if (Get_Trace (TKIND_ALLOC, TP_CG)) {
    // start tracing at beginning of cg.
    MEM_Tracing_Enable();
  }

}

void
CG_PU_Finalize(void)
{
  TAG_Finish();
  GTN_UNIVERSE_Pu_End ();
  OP_MAP_Finish();
  CGSPILL_Finalize_For_PU();
  if (Enable_CG_Peephole) EBO_Finalize();

  if (PU_has_syscall_linkage(Get_Current_PU())) {
    Enable_SWP = Orig_Enable_SWP;
  }

  /* TN_To_PREG_Map is allocated from MEM_pu_pool and so can't be popped
     but it can be put on the free list and cleared at the end of the PU */
  TN_MAP_Delete(TN_To_PREG_Map);
  TN_To_PREG_Map = NULL;

  Free_BB_Memory();         /* Free non-BB_Alloc space. */
  MEM_POOL_Pop ( &MEM_local_pool );
  MEM_POOL_Pop ( &MEM_local_nz_pool );
  MEM_POOL_Pop ( &MEM_phase_pool );
  MEM_POOL_Pop ( &MEM_phase_nz_pool );
}

/* Stuff that needs to be done at the start of each REGION in cg. */
static void
CG_Region_Initialize (WN *rwn, struct ALIAS_MANAGER *alias_mgr)
{
  MEM_POOL_Push (&MEM_local_region_pool);
  MEM_POOL_Push (&MEM_local_region_nz_pool);
  Init_CG_Expand ();
  FREQ_Region_Initialize ();
  BB_REGION_Initialize ();
  LRA_Init();
  GRA_Initialize();
  Init_TNs_For_REGION ();
  /*
   * Create Array to map PREGs into TNs
   * Must be done after Init_Entry_Exit_Code, since
   * Init_Entry_Exit_Code creates special PREGs to represent
   * save locations in WHIRL
   */
  PREG_NUM last_preg_num;
  last_preg_num = Get_Preg_Num (PREG_Table_Size(CURRENT_SYMTAB))+1;
  PREG_To_TN_Array = (TN **) Pu_Alloc (sizeof (TN *) * last_preg_num);
  PREG_To_TN_Mtype = (TYPE_ID *) Pu_Alloc (sizeof (TYPE_ID) * last_preg_num);

  PREG_To_TN_Clear();   /* this enforces different preg maps between regions */
  if (TN_To_PREG_Map == NULL)
    TN_To_PREG_Map = TN_MAP_Create();

  TN_CORRESPOND_Free(); /* remove correspondence between tns (ex. divrem) */

  GTN_UNIVERSE_REGION_Begin();

  Whirl2ops_Initialize(alias_mgr);

  Current_Rid = REGION_get_rid( rwn );
}

/*
 * Stuff that needs to be done at the end of each REGION in cg.
 * This includes making glue code to map TNs in CG'd code
 * from/to PREGs in WHIRL
 */
static void
CG_Region_Finalize (WN *result_before, WN *result_after,
            WN *rwn, struct ALIAS_MANAGER *am, BOOL generate_glue_code)
{
  RID *rid;
  CGRIN *cgrin;
  WN *entry_fixup, *exit_fixup;
  INT32 i, num_exits;

  Is_True(REGION_consistency_check(rwn),("CG_Region_Finalize"));
  rid = REGION_get_rid( rwn );
  cgrin = RID_cginfo( rid );
  FmtAssert(rid != NULL && cgrin != NULL,
        ("CG_Region_Finalize, inconsistent region"));

  REGION_set_level(rid, RL_CGSCHED);

  if (generate_glue_code) {
    /* region entry glue code */
    entry_fixup = CGRIN_entry_glue( cgrin );
    REGION_Entry_PREG_Whirl( rid, entry_fixup, CGRIN_tns_in( cgrin ), am );
    if ( Trace_REGION_Interface ) {
      fprintf( TFile, "<region> Entry glue code for RGN %d\n", RID_id(rid) );
      fdump_tree( TFile, entry_fixup );
    }
    WN_INSERT_BlockFirst( result_before, entry_fixup );

    num_exits = RID_num_exits( rid );
    for (i=0; i<num_exits; i++) {
      exit_fixup = CGRIN_exit_glue_i( cgrin, i );
      REGION_Exit_PREG_Whirl( rid, i, exit_fixup,
                 CGRIN_tns_out_i( cgrin, i ), am );
      if ( Trace_REGION_Interface ) {
        fprintf( TFile, "<region> Exit glue code for exit %d RGN %d\n",
                i, RID_id(rid) );
        fdump_tree( TFile, exit_fixup );
      }
      WN_INSERT_BlockLast( result_after, exit_fixup );
    }
  }

  Whirl2ops_Finalize();

  MEM_POOL_Pop (&MEM_local_region_pool);
  MEM_POOL_Pop (&MEM_local_region_nz_pool);
}

static void Config_Ipfec_Flags() {
 
  /* copy ORC_... Flags to Ipfec_... Flags */
  Copy_Ipfec_Flags();

  /*start Config_Ipfec_Flags*/
  IPFEC_Enable_Edge_Profile = IPFEC_Enable_Edge_Profile || 
	  ((Instrumentation_Enabled || Instrumentation_Enabled_Before)
           && (Instrumentation_Phase_Num==4 && Instrumentation_Type_Num & CG_EDGE_PROFILE));

  IPFEC_Enable_Value_Profile= IPFEC_Enable_Value_Profile || ( (Instrumentation_Enabled || Instrumentation_Enabled_Before) 
      && (Instrumentation_Phase_Num==4 && Instrumentation_Type_Num & CG_VALUE_PROFILE) ); 
  IPFEC_Enable_Stride_Profile= IPFEC_Enable_Stride_Profile || ( (Instrumentation_Enabled || Instrumentation_Enabled_Before) 
  && (Instrumentation_Phase_Num==4 && Instrumentation_Type_Num & CG_STRIDE_PROFILE) ); 
  IPFEC_Enable_Value_Profile_Annot = IPFEC_Enable_Value_Profile_Annot || Feedback_Enabled[PROFILE_PHASE_BEFORE_REGION];
  IPFEC_Enable_Stride_Profile_Annot = IPFEC_Enable_Stride_Profile_Annot || Feedback_Enabled[PROFILE_PHASE_BEFORE_REGION];
  IPFEC_Enable_Edge_Profile_Annot = IPFEC_Enable_Edge_Profile_Annot || Feedback_Enabled[PROFILE_PHASE_BEFORE_REGION];
  IPFEC_Enable_Opt_after_schedule=IPFEC_Enable_Opt_after_schedule && CG_Enable_Ipfec_Phases && CG_opt_level > 1;
  IPFEC_Enable_Region_Formation = IPFEC_Enable_Region_Formation && CG_Enable_Ipfec_Phases && CG_opt_level > 1;
  IPFEC_Enable_If_Conversion = IPFEC_Enable_If_Conversion && CG_Enable_Ipfec_Phases;
  IPFEC_Force_If_Conv = IPFEC_Force_If_Conv && CG_Enable_Ipfec_Phases;
  IPFEC_Force_Para_Comp_Gen = IPFEC_Force_Para_Comp_Gen && CG_Enable_Ipfec_Phases;
  IPFEC_Para_Comp_Gen = IPFEC_Para_Comp_Gen && CG_Enable_Ipfec_Phases;
  IPFEC_Disable_Merge_BB = IPFEC_Disable_Merge_BB && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_PRDB = IPFEC_Enable_PRDB && CG_Enable_Ipfec_Phases && IPFEC_Enable_Region_Formation && (IPFEC_Enable_Prepass_GLOS || IPFEC_Enable_Postpass_LOCS);
  IPFEC_Enable_BB_Verify = IPFEC_Enable_BB_Verify && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Prepass_GLOS = IPFEC_Enable_Prepass_GLOS && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Postpass_GLOS = IPFEC_Enable_Postpass_GLOS && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Prepass_LOCS = IPFEC_Enable_Prepass_LOCS && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Postpass_LOCS = IPFEC_Enable_Postpass_LOCS && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Speculation = IPFEC_Enable_Speculation && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Data_Speculation = IPFEC_Enable_Data_Speculation && IPFEC_Enable_Speculation;
  IPFEC_Enable_Cntl_Speculation = IPFEC_Enable_Cntl_Speculation && IPFEC_Enable_Speculation;
  IPFEC_Enable_Compressed_Template = IPFEC_Enable_Compressed_Template && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Pre_Bundling = IPFEC_Enable_Pre_Bundling && CG_Enable_Ipfec_Phases;
  IPFEC_Force_CHK_Fail = IPFEC_Force_CHK_Fail && IPFEC_Enable_Speculation;
  IPFEC_Glos_Enable_Cntl_Spec_If_Converted_Code = IPFEC_Glos_Enable_Cntl_Spec_If_Converted_Code && IPFEC_Enable_Cntl_Speculation;
  IPFEC_Enable_Cascade = IPFEC_Enable_Cascade && IPFEC_Enable_Speculation;
  IPFEC_Hold_Uses = IPFEC_Hold_Uses && IPFEC_Enable_Speculation;
  IPFEC_Chk_Compact = IPFEC_Chk_Compact && IPFEC_Enable_Speculation;
  IPFEC_Enable_Safety_Load = IPFEC_Enable_Safety_Load && IPFEC_Enable_Speculation;
  IPFEC_Profitability = IPFEC_Profitability && CG_Enable_Ipfec_Phases;

  IPFEC_Enable_Multi_Branch = IPFEC_Enable_Multi_Branch && CG_Enable_Ipfec_Phases; 
  IPFEC_Enable_Pre_Multi_Branch = IPFEC_Enable_Pre_Multi_Branch && CG_Enable_Ipfec_Phases;
  IPFEC_Enable_Post_Multi_Branch = IPFEC_Enable_Post_Multi_Branch && CG_Enable_Ipfec_Phases;

  ORC_Enable_Cache_Analysis = ORC_Enable_Cache_Analysis && CG_Enable_Ipfec_Phases; 

  if (IPFEC_Chk_Compact && locs_skip_bb) {
    DevWarn("Although chk_compact is turned on, it should be turned off since some BBs are forced to be skipped in local scheduling phase!");
    IPFEC_Chk_Compact = 0;
  } 
  if (IPFEC_Chk_Compact && !IPFEC_Enable_Postpass_LOCS) {
    DevWarn("Although chk_compact is turned on, it should be turned off since postpass local scheduling is disabled!");
    IPFEC_Chk_Compact = 0;
  }
}

/* Can be called two ways:
   1) on a region (pu_dst is NULL, returns code)
   2) on a PU (pu_dst is no NULL, returns NULL)
*/
WN *
CG_Generate_Code( 
    WN *rwn, 
    struct ALIAS_MANAGER *alias_mgr, 
    DST_IDX pu_dst, 
    BOOL region )
{
  BOOL value_profile_need_gra = FALSE;
/*later:  BOOL region = DST_IS_NULL(pu_dst); */
  BOOL orig_reuse_temp_tns = Reuse_Temp_TNs;
  /* Initialize RGN_Formed to FALSE. */
  RGN_Formed = FALSE;
  Alias_Manager = alias_mgr;

  Set_Error_Phase( "Code Generation" );
  Start_Timer( T_CodeGen_CU );

  // Use of feedback information can be disabled in CG using the 
  // -CG:enable_feedback=off flag. The flag CG_PU_Has_Feedback is used
  // all over CG instead of Cur_PU_Feedback for this reason.
  CG_PU_Has_Feedback = ((Cur_PU_Feedback != NULL) && CG_enable_feedback);
  BOOL frequency_verify = Get_Trace( TP_FEEDBACK, TP_CG_FEEDBACK );

  if (FALSE) {
     ST *func_st = Get_Current_PU_ST();
     rse_budget = PU_gp_group(Pu_Table [ST_pu (func_st)]);
     if (rse_budget == 0) DevWarn("FAINT THE RSE BUDGET IS ZERO!");
  }

        
  CG_Region_Initialize ( rwn, alias_mgr );

  Set_Error_Phase ( "Code_Expansion" );
  Start_Timer ( T_Expand_CU );

  // If this PU is simply a wrapper for assembly code to be placed
  // into the .s file, take care of that job and move on.
  if (WN_operator(rwn) == OPR_FUNC_ENTRY &&
      ST_asm_function_st(*WN_st(rwn))) {
    FmtAssert(Assembly && !Object_Code,
          ("Cannot produce non-assembly output with file-scope asm"));
    fprintf(Asm_File, "\n%s\n", ST_name(WN_st(rwn)));
    return rwn;
  }

  Convert_WHIRL_To_OPs ( rwn );

  // split large bb's to minimize compile speed and register pressure
  Split_BBs();

  if ( ! CG_localize_tns ) {
    // Localize dedicated tns involved in calls that cross bb's,
    // and replace dedicated TNs involved in REGION interface with the
    // corresponding allocated TNs from previously compiled REGIONs.
    Localize_or_Replace_Dedicated_TNs();
  }

  // If using feedback, incorporate into the CFG as early as possible.
  // This phase also fills in any missing feedback using heuristics.
  if (CG_PU_Has_Feedback) {
    Set_Error_Phase ("FREQ");
    Start_Timer (T_Freq_CU);
    FREQ_Incorporate_Feedback ( rwn );
    Stop_Timer (T_Freq_CU);
    Set_Error_Phase ( "Code_Expansion" );
    if (frequency_verify)
      FREQ_Verify("Feedback Incorporation");
  }
  
  // Prior to CG optimization, EH_Prune_Range_List is called to
  // eliminate unneeded EH ranges.  This gets rid of ranges which
  // do not have calls or throws. 

  EH_Prune_Range_List();

#ifdef OSP_OPT
  // it's high time to compute pu_need_LSDA after EH_Prune_Range_List, 
  pu_need_LSDA = !PU_Need_Not_Create_LSDA ();
#endif 

  // trace all the EH ranges 
  if (Get_Trace (TP_EH, 0x0002)) {
    fprintf (TFile, "\n=======================================================================\n");
    fprintf (TFile, "\t   EH RANGE INFO for PU: %s \n", ST_name(Get_Current_PU_ST()));
    fprintf (TFile, "\t   (After EH_Prune_Range_List) \t\n");
    fprintf (TFile, "=======================================================================\n");
    EH_Print_Range_List ();
  }

  Optimize_Tail_Calls( Get_Current_PU_ST() );

  Init_Callee_Saved_Regs_for_REGION( Get_Current_PU_ST(), region );

  //this is a hack for edge profiling
  //when invoke edge profiling, it does not save/restore b0
  //while Generate_Entry_Exit_Code will do this instead, but it need to know
  //IPFEC_Enable_Edge_Profile in time.
  Config_Ipfec_Flags();
  
  Generate_Entry_Exit_Code ( Get_Current_PU_ST(), region );
  Stop_Timer ( T_Expand_CU );
  Check_for_Dump ( TP_CGEXP, NULL );

  if (IPFEC_Enable_Edge_Profile && can_invoke_profile_with_current_cg_opt_level )
  {
    Set_Error_Phase ( "edge profile instrument" );
    Start_Timer ( T_Ipfec_Profiling_CU );
    CG_Edge_Profile_Instrument(RID_cginfo(Current_Rid),PROFILE_PHASE_BEFORE_REGION);
    Stop_Timer( T_Ipfec_Profiling_CU );
    Check_for_Dump(TP_A_PROF, NULL);
  } else if (IPFEC_Enable_Edge_Profile_Annot && can_invoke_profile_with_current_cg_opt_level ) {
    Set_Error_Phase ( "edge profile annotation" );
    CG_Edge_Profile_Annotation(RID_cginfo(Current_Rid),PROFILE_PHASE_BEFORE_REGION);
    Check_for_Dump(TP_A_PROF, NULL);
   
  }

#ifdef _value_profile_before_region_formation
  if ((IPFEC_Enable_Value_Profile||IPFEC_Enable_Stride_Profile) && can_invoke_profile_with_current_cg_opt_level )
  {
    Set_Error_Phase ( "value profile instrument" );
    if (EBO_Opt_Level != 0) 
    {
      DevWarn("Value profiling need -CG:ebo_level=0!! Set ebo_level to 0!!");
      EBO_Opt_Level = 0;
    }
     
    //We take all load instructions for example to show how to specify the 
    //OP's type and how it should be value profiled.
    inst2prof_list.clear();
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld1,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld2,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld4,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld8,0,FALSE),&MEM_pu_pool) );
    
    UINT32 Min_Instr_Pu_Id, Max_Instr_Pu_Id;
    Min_Instr_Pu_Id = Value_Instr_Pu_Id >> 16;
    Max_Instr_Pu_Id = Value_Instr_Pu_Id & 0xffff;
    Is_True((current_PU_handle<=Max_Instr_Pu_Id)&&(current_PU_handle>=Min_Instr_Pu_Id),("The number of PU exceed the boundery !"));
    Start_Timer ( T_Ipfec_Profiling_CU );
    CG_VALUE_Instrument(RID_cginfo(Current_Rid),PROFILE_PHASE_BEFORE_REGION,IPFEC_Enable_Stride_Profile, IPFEC_Enable_Value_Profile);
    value_profile_need_gra = TRUE;
    Stop_Timer( T_Ipfec_Profiling_CU );
    Check_for_Dump(TP_A_PROF, NULL);
  } else if ((IPFEC_Enable_Value_Profile_Annot||IPFEC_Enable_Stride_Profile_Annot)&& can_invoke_profile_with_current_cg_opt_level ) {
    //We take all load instructions for example to show how to specify the 
    //OP's type and how it should be value profiled.
    inst2prof_list.clear();
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld1,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld2,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld4,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld8,0,FALSE),&MEM_pu_pool) );

    Set_Error_Phase ( "value profile annotation" );
    UINT32 Min_Instr_Pu_Id, Max_Instr_Pu_Id;
    Min_Instr_Pu_Id = Value_Instr_Pu_Id >> 16;
    Max_Instr_Pu_Id = Value_Instr_Pu_Id & 0xffff;
    Is_True((current_PU_handle<=Max_Instr_Pu_Id)&&(current_PU_handle>=Min_Instr_Pu_Id),("The number of PU exceed the boundery !"));
    CG_VALUE_Annotate(RID_cginfo(Current_Rid),PROFILE_PHASE_BEFORE_REGION);
  }
#endif

  if (CG_localize_tns && !value_profile_need_gra ) {
    /* turn all global TNs into local TNs */
    Set_Error_Phase ( "Localize" );
    Start_Timer ( T_Localize_CU );
    Localize_Any_Global_TNs(region ? REGION_get_rid( rwn ) : NULL);
    Stop_Timer ( T_Localize_CU );
    Check_for_Dump ( TP_LOCALIZE, NULL );
  } else {
    /* Initialize liveness info for new parts of the REGION */
    /* also compute global liveness for the REGION */
    Set_Error_Phase( "Global Live Range Analysis");
    Start_Timer( T_GLRA_CU );
    GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
    Stop_Timer ( T_GLRA_CU );
    Check_for_Dump ( TP_FIND_GLOB, NULL );
  }

  if (Enable_CG_Peephole) {
    Set_Error_Phase("Extended Block Optimizer");
    Start_Timer(T_EBO_CU);
    EBO_Pre_Process_Region (region ? REGION_get_rid(rwn) : NULL);
    Stop_Timer ( T_EBO_CU );
    Check_for_Dump ( TP_EBO, NULL );
  }

  // Optimize control flow (first pass)
  if (CG_opt_level > 0 && CFLOW_opt_before_cgprep) {
    // Perform all the optimizations that make things more simple.
    // Reordering doesn't have that property.
    CFLOW_Optimize(  (CFLOW_ALL_OPTS|CFLOW_IN_CGPREP)
                   & ~(CFLOW_FREQ_ORDER | CFLOW_REORDER),
                   "CFLOW (first pass)");
    if (frequency_verify && CG_PU_Has_Feedback)
      FREQ_Verify("CFLOW (first pass)");
  }

  extern void Perform_Loop_Invariant_Code_Motion (void);
  if (IPFEC_Enable_LICM && CG_opt_level > 1) {
    Perform_Loop_Invariant_Code_Motion ();
  }

  if (CG_Enable_Ipfec_Phases && CG_opt_level > 1 &&
      (IPFEC_Enable_If_Conversion || IPFEC_Enable_PRDB ||
       IPFEC_Enable_Prepass_GLOS  || IPFEC_Enable_Postpass_GLOS))
    IPFEC_Enable_Region_Formation = TRUE;

  REGION_TREE *region_tree;
  if (IPFEC_Enable_Region_Formation) {
    // Build Ipfec region tree.
    Set_Error_Phase("Ipfec region formation");
    Start_Timer(T_Ipfec_Region_CU);
    region_tree=CXX_NEW(REGION_TREE(REGION_First_BB),&MEM_pu_pool);
    Stop_Timer(T_Ipfec_Region_CU);
    RGN_Formed = TRUE;
  }
 
  // Invoke global optimizations before register allocation at -O2 and above.
  if (CG_opt_level > 1) {

    // Compute frequencies using heuristics when not using feedback.
    // It is important to do this after the code has been given a
    // cleanup by cflow so that it more closely resembles what it will
    // to the later phases of cg.
    if (!CG_PU_Has_Feedback && !IPFEC_Enable_Edge_Profile_Annot) {
      Set_Error_Phase("FREQ");
      Start_Timer (T_Freq_CU);
      FREQ_Compute_BB_Frequencies();
      Stop_Timer (T_Freq_CU);
      if (frequency_verify)
         FREQ_Verify("Heuristic Frequency Computation");
    }


    if (IPFEC_Enable_Region_Formation) {
      // Build Ipfec region tree.
      Set_Error_Phase("Ipfec region formation");
      Start_Timer(T_Ipfec_Region_CU);
      REGION *root = region_tree->Root();
      IPFEC_Enable_Region_Decomposition = TRUE;
      if (IPFEC_Enable_Region_Decomposition) {
        region_tree->Decomposition(); 
        GRA_LIVE_Recalc_Liveness(region ? REGION_get_rid(rwn) : NULL);
      }

      Stop_Timer(T_Ipfec_Region_CU);

#ifdef Is_True_On
      if (Get_Trace(TP_IPFEC,TT_IPFEC_GRAPHIC)) {
        printf("After Region Formation draw global cfg\n"); 
        draw_global_cfg("after Decompose_Region_To_SEME");
        printf("After Region Formation draw region tree\n"); 
        draw_region_tree(region_tree->Root(),"After Region Formation");
      }
      Verify_Region_Tree(region_tree, REGION_First_BB);
#endif
    }

    // Perform stride prefetch 
    if (IPFEC_Enable_Stride_Prefetch && IPFEC_Enable_Stride_Profile_Annot){
        Set_Error_Phase( "Stride prefetch \n");
        Stride_Region(region_tree, IPFEC_Enable_Stride_Prefetch);
 	}

    // Perform hyperblock formation (if-conversion).  Only works for
    // IA-64 at the moment. 
    //
        

    
    if (CGTARG_Can_Predicate()) {
      if (IPFEC_Enable_If_Conversion) {
        Set_Error_Phase( "Ipfec if conversion"); 
        IF_CONVERTOR convertor(region_tree);
#ifdef Is_True_On
        if (IPFEC_Enable_BB_Verify) {
          BB_Verify_Flags();
        }
        if (Get_Trace(TP_IPFEC,TT_IPFEC_GRAPHIC)) {
          printf("After If Conversion draw global cfg\n"); 
          draw_global_cfg("after if conversion");
          printf("After If Conversion draw tree\n");
          draw_region_tree(region_tree->Root(),"After If Conversion");
        }
        Verify_Region_Tree(region_tree, REGION_First_BB);
#endif
      }
      else if (!IPFEC_Enable_Region_Formation) {
        // Initialize the predicate query system in the hyperblock
        // formation phase.
        HB_Form_Hyperblocks(region ? REGION_get_rid(rwn) : NULL, NULL);
        if (!PQSCG_pqs_valid()) {
          PQSCG_reinit(REGION_First_BB);
        }
      }
      if (frequency_verify)
        FREQ_Verify("Hyberblock Formation");
    }

    if (!CG_localize_tns || value_profile_need_gra ) {
      /* Initialize liveness info for new parts of the REGION */
      /* also compute global liveness for the REGION */
      Set_Error_Phase( "Global Live Range Analysis");
      Start_Timer( T_GLRA_CU );
      GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
      Stop_Timer ( T_GLRA_CU );
      Check_for_Dump ( TP_FIND_GLOB, NULL );
    }

    // Add analysis for Cache information
    if (ORC_Enable_Cache_Analysis) Cache_Location_Analysis(); 

    if (CG_enable_loop_optimizations) {
      Set_Error_Phase("CGLOOP");
      Start_Timer(T_Loop_CU);
      if (IPFEC_Enable_Region_Formation) {
        REGION_LOOP_UPDATE    *rgn_loop_update;
        rgn_loop_update = CXX_NEW(REGION_LOOP_UPDATE(region_tree,REGION_First_BB),&MEM_pu_pool);
        Perform_Loop_Optimizations(rgn_loop_update);
        CXX_DELETE(rgn_loop_update, &MEM_pu_pool);
#ifdef Is_True_On
        if (Get_Trace(TP_IPFEC,TT_IPFEC_GRAPHIC)) {
          draw_global_cfg("after loop opt");
          draw_region_tree(region_tree->Root());
        }
        Verify_Region_Tree(region_tree, REGION_First_BB);
#endif
      } else {
        Perform_Loop_Optimizations();
      }
      GRA_LIVE_Recalc_Liveness(region ? REGION_get_rid( rwn) : NULL);
      GRA_LIVE_Rename_TNs();  // rename TNs -- required by LRA
      Stop_Timer(T_Loop_CU);
      Check_for_Dump(TP_CGLOOP, NULL);
      if (frequency_verify)
        FREQ_Verify("CGLOOP");
    }

    /* Optimize control flow (second pass) */
    if (CFLOW_opt_after_cgprep) {
      CFLOW_Optimize(CFLOW_ALL_OPTS, "CFLOW (second pass)");
      if (frequency_verify)
        FREQ_Verify("CFLOW (second pass)");
#ifdef Is_True_On
        if (Get_Trace(TP_IPFEC,TT_IPFEC_GRAPHIC)) {
          draw_global_cfg("after cflow opt");
          draw_region_tree(region_tree->Root());
        }
        if (IPFEC_Enable_Region_Formation)
          Verify_Region_Tree(region_tree, REGION_First_BB);
#endif
    }

    if (Enable_CG_Peephole) {
      Set_Error_Phase( "Extended Block Optimizer");
      Start_Timer( T_EBO_CU );
      EBO_Process_Region (region ? REGION_get_rid(rwn) : NULL);
      PQSCG_reinit(REGION_First_BB);
      Stop_Timer ( T_EBO_CU );
      Check_for_Dump ( TP_EBO, NULL );
    }
  }



  BOOL locs_bundle_value = LOCS_Enable_Bundle_Formation;
  BOOL emit_bundle_value = EMIT_explicit_bundles;
  LOCS_Enable_Bundle_Formation = IPFEC_Enable_Pre_Bundling;
  EMIT_explicit_bundles = IPFEC_Enable_Pre_Bundling;

  if (!Get_Trace (TP_CGEXP, 1024))
    Reuse_Temp_TNs = TRUE;  /* for spills */

  if (CGSPILL_Enable_Force_Rematerialization)
    CGSPILL_Force_Rematerialization();

  if (!region) {
    /* in case cgprep introduced a gp reference */
    Adjust_GP_Setup_Code( Get_Current_PU_ST(), FALSE /* allocate registers */ );
    /* in case cgprep introduced a lc reference */
    Adjust_LC_Setup_Code();

    // TODO:  when generate control speculation (ld.s) and st8.spill
    // of NaT bits, then need to save and restore ar.unat. 
  }

  /* Global register allocation, Scheduling:
   *
   * The overall algorithm is as follows:
   *   - Global code motion before register allocation
   *   - Local scheduling before register allocation
   *   - Global register allocation
   *   - Local register allocation
   *   - Global code motion phase (GCM) 
   *   - Local scheduling after register allocation
   */

  if (!CG_localize_tns) {
    /* Initialize liveness info for new parts of the REGION */
    /* also compute global liveness for the REGION */
    /* Set_Error_Phase( "Global Live Range Analysis");
    Start_Timer( T_GLRA_CU );
    GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
    Stop_Timer ( T_GLRA_CU );
    Check_for_Dump ( TP_FIND_GLOB, NULL ); */
  }

  //Temporary solution for performance tuning.
  gra_self_recursive = FALSE;
  fat_self_recursive = FALSE;
  //Check_Self_Recursive();
  if (CG_opt_level > 1 && IPFEC_Enable_PRDB) PRDB_Init(region_tree);
  
  if (IPFEC_Enable_Prepass_GLOS && CG_opt_level > 1) {
    Start_Timer( T_GLRA_CU );
    GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
    Stop_Timer ( T_GLRA_CU );

    if(Enable_CG_Peephole)
      EBO_Pre_Process_Region (region ? REGION_get_rid(rwn) : NULL);
    Check_Self_Recursive();
    Global_Insn_Sched(region_tree, TRUE);
  } else if (IPFEC_Enable_Prepass_LOCS) {
    Local_Insn_Sched(TRUE);
  } else {
    IGLS_Schedule_Region (TRUE /* before register allocation */);
  }

  
  if (CG_opt_level > 1 && IPFEC_Enable_PRDB) PRDB_Init(region_tree);
  if (IPFEC_Enable_Opt_after_schedule) {
    BOOL tmp = CG_localize_tns ;
    CG_localize_tns = TRUE;
    CFLOW_Optimize(CFLOW_BRANCH|CFLOW_UNREACHABLE|CFLOW_MERGE|CFLOW_REORDER, "CFLOW (third pass)");
    CG_localize_tns = tmp ;
  }
  
  if (CG_opt_level > 1 && IPFEC_Enable_Post_Multi_Branch) {
    GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
    Post_Multi_Branch_Collect();
  }

  if (IPFEC_Enable_Prepass_GLOS && CG_opt_level > 1) {
     BOOL need_recalc_liveness = (Generate_Recovery_Code() > 0);
     if (need_recalc_liveness) 
        GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
  }
#ifdef Is_True_On
  if (IPFEC_Enable_BB_Verify) {
    BB_Verify_Flags();
  }
#endif


  LOCS_Enable_Bundle_Formation = locs_bundle_value;
  EMIT_explicit_bundles = emit_bundle_value;
#ifndef _value_profile_before_region_formation
   if (IPFEC_Enable_Value_Profile && can_invoke_profile_with_current_cg_opt_level )
  {
    Set_Error_Phase ( "value profile instrument" );
        if (EBO_Opt_Level != 0)
        {
                DevWarn("Value profiling need -CG:ebo_level=0!! Set ebo_level to 0!!");
                EBO_Opt_Level = 0;
        }
    //We take all load instructions for example to show how to specify the
    //OP's type and how it should be value profiled.
    inst2prof_list.clear();
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld1,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld2,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld4,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld8,0,FALSE),&MEM_pu_pool) );
        UINT32 Min_Instr_Pu_Id, Max_Instr_Pu_Id;
        UINT64 tmpmask=1;
        tmpmask = tmpmask << current_PU_handle;
        Min_Instr_Pu_Id = Value_Instr_Pu_Id >> 16;
        Max_Instr_Pu_Id = Value_Instr_Pu_Id & 0xffff;
        if (current_PU_handle >= Min_Instr_Pu_Id
                && current_PU_handle <= Max_Instr_Pu_Id
                && ((unsigned long long)( tmpmask &~ Value_Instr_Pu_Id_Mask ))                )
        {
        Start_Timer ( T_Ipfec_Profiling_CU );
            CG_VALUE_Instrument(RID_cginfo(Current_Rid),PROFILE_PHASE_LAST,FALSE,FALSE);
            value_profile_need_gra = TRUE;
        Stop_Timer( T_Ipfec_Profiling_CU );
#if 0
                if (CG_localize_tns) {
                    /* turn all global TNs into local TNs */
                    Set_Error_Phase ( "Localize" );
                    Start_Timer ( T_Localize_CU );
                    Localize_Any_Global_TNs(region ? REGION_get_rid( rwn ) : NULL);
                    Stop_Timer ( T_Localize_CU );
                    Check_for_Dump ( TP_LOCALIZE, NULL );
                  } else {
                    /* Initialize liveness info for new parts of the REGION */                    /* also compute global liveness for the REGION */
                    Set_Error_Phase( "Global Live Range Analysis");
                    Start_Timer( T_GLRA_CU );
                    GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
                    Stop_Timer ( T_GLRA_CU );
                    Check_for_Dump ( TP_FIND_GLOB, NULL );
                  }
#endif

        }
        Check_for_Dump(TP_A_PROF, NULL);

   } else if (IPFEC_Enable_Value_Profile_Annot && can_invoke_profile_with_current_cg_opt_level ) {
    //We take all load instructions for example to show how to specify the
    //OP's type and how it should be value profiled.
    inst2prof_list.clear();
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld1,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld2,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld4,0,FALSE),&MEM_pu_pool) );
    inst2prof_list.push_back( CXX_NEW(INST_TO_PROFILE(TOP_ld8,0,FALSE),&MEM_pu_pool) );

    Set_Error_Phase ( "value profile annotation" );
        UINT32 Min_Instr_Pu_Id, Max_Instr_Pu_Id;
        UINT64 tmpmask=1;
        tmpmask = tmpmask << current_PU_handle;
        Min_Instr_Pu_Id = Value_Instr_Pu_Id >> 16;
        Max_Instr_Pu_Id = Value_Instr_Pu_Id & 0xffff;
        if (current_PU_handle >= Min_Instr_Pu_Id
                && current_PU_handle <= Max_Instr_Pu_Id
                && ((unsigned long long)( tmpmask &~ Value_Instr_Pu_Id_Mask ))                )
        {
            CG_VALUE_Annotate(RID_cginfo(Current_Rid),PROFILE_PHASE_LAST,FALSE,FALSE);
        }
  }
  DevWarn("Now we are testing instrumentation after RegionFormation!");
#endif
  current_PU_handle++;


  if (!CG_localize_tns || value_profile_need_gra )
  {
    // Earlier phases (esp. GCM) might have introduced local definitions
    // and uses for global TNs. Rename them to local TNs so that GRA 
    // does not have to deal with them.

    if (GRA_recalc_liveness) {
      Start_Timer( T_GLRA_CU);
      GRA_LIVE_Recalc_Liveness(region ? REGION_get_rid( rwn) : NULL);
      Stop_Timer ( T_GLRA_CU );
      Check_for_Dump (TP_FIND_GLOB, NULL);
    } else if (!(IPFEC_Enable_Prepass_GLOS && (CG_opt_level > 1 || value_profile_need_gra))) {
      GRA_LIVE_Recalc_Liveness(region ? REGION_get_rid( rwn) : NULL);
      GRA_LIVE_Rename_TNs ();
    }

    if (GRA_redo_liveness || IPFEC_Enable_Prepass_GLOS && (CG_opt_level > 1 || value_profile_need_gra)) {
      Start_Timer( T_GLRA_CU );
      GRA_LIVE_Init(region ? REGION_get_rid( rwn ) : NULL);
      Stop_Timer ( T_GLRA_CU );
      Check_for_Dump ( TP_FIND_GLOB, NULL );
    }

    GRA_Allocate_Global_Registers( region );
  }

  LRA_Allocate_Registers (!region);

  if (!CG_localize_tns || value_profile_need_gra) {
    Set_Error_Phase ( "GRA_Finish" );
    /* Done with all grant information */
    GRA_Finalize_Grants();
  }
 
  if (!region) {
    /* Check that we didn't introduce a new gp reference */
    Adjust_GP_Setup_Code( Get_Current_PU_ST(), TRUE /* allocate registers */ );

    /* The stack frame is final at this point, no more spilling after this.
     * We can set the Frame_Len now.
     * Then we can go through all the entry/exit blocks and fix the SP 
     * adjustment OP or delete it if the frame length is zero.
     */
    Set_Frame_Len (Finalize_Stack_Frame());
    Set_Error_Phase ( "Final SP adjustment" );
    Adjust_Entry_Exit_Code ( Get_Current_PU_ST() );
  }

  if (Enable_EBO_Post_Proc_Rgn) {
    Set_Error_Phase("Extended Block Optimizer");
    Start_Timer(T_EBO_CU);
    EBO_Post_Process_Region (region ? REGION_get_rid(rwn) : NULL);
    Stop_Timer ( T_EBO_CU );
    Check_for_Dump ( TP_EBO, NULL );
  }

  if (IPFEC_Enable_Postpass_LOCS) {
    if (IPFEC_sched_care_machine!=Sched_care_bundle) {
      Local_Insn_Sched(FALSE);
      CGGRP_Bundle();
    }
    else if (CG_opt_level <1){
      IPFEC_sched_care_machine = Sched_care_nothing;
      CGGRP_Bundle();
    }
    else{
      Local_Insn_Sched(FALSE);
    }
  } else {
    if (PRDB_Valid()) Delete_PRDB();
    IGLS_Schedule_Region (FALSE /* after register allocation */);
  }
#ifdef Is_True_On
  if (IPFEC_Enable_BB_Verify) {
    BB_Verify_Flags();
  }
#endif

  if(PRDB_Valid()) Delete_PRDB();
  if (IPFEC_Force_CHK_Fail)
    Force_Chk_Fail();

  if (CG_opt_level > 1 && IPFEC_Enable_Post_Multi_Branch) {
    Post_Multi_Branch();
  }
  Reuse_Temp_TNs = orig_reuse_temp_tns;     /* restore */
  
  if (PRDB_Valid()) Delete_PRDB();
  if (IPFEC_Enable_Region_Formation) {
    /* Empty BB eliminating has no relation with region, 
     * so it can turn off IPFEC_Enable_Region_Formation temporarily,
     * Or it will cause many errors which deal with region
     */
     IPFEC_Enable_Region_Formation = FALSE;
     CFLOW_Delete_Empty_BB();  
     IPFEC_Enable_Region_Formation = TRUE;
  }
  if (region) {
    /*--------------------------------------------------------------------*/
    /* old region: rwn, rid_orig                      */
    /* new region: rwn_new, rid_new (encloses old region)         */
    /*--------------------------------------------------------------------*/
    WN  *inner_body, *outer_body, *exitBlock, *comment;
    WN  *rwn_new, *result_block_before, *result_block_after;
    RID *rid_orig;
    char str[100];

    Is_True(REGION_consistency_check(rwn),("CG_Generate_Code"));
    rid_orig = REGION_get_rid(rwn);

    /* don't delete rwn, it contains the stub that helps find the MOPS
       that the region has been lowered to */

    outer_body = WN_CreateBlock();
    /* put inner region inside outer containment block */
    WN_INSERT_BlockFirst(outer_body, rwn);
    /* we assembled the new exit block earlier in Build_CFG()       */
    exitBlock = CGRIN_nested_exit(RID_cginfo(rid_orig));
    WN_region_exits(rwn) = exitBlock; /* PPP ??? */

    rwn_new = outer_body;

    /* put a note in the inner body that the code isn't there anymore */
    inner_body = WN_CreateBlock();
    WN_region_body(rwn) = inner_body; /* overwrite old body, now in MOPs */
    sprintf(str,"RGN %d has been lowered to MOPs, level=%s",
            RID_id(rid_orig), RID_level_str(rid_orig));
    comment = WN_CreateComment(str);
    WN_INSERT_BlockFirst(inner_body, comment);

    /* Need to split result block for glue code into two parts: before and
       after the region body. The reason we can't just insert the glue code
       directly before or after the region directly is that we need to keep
       it separate for updating the alias info.
       If CG_LOOP has made some WHIRL glue, it is inserted in result_block. */
    result_block_before = WN_CreateBlock();
    result_block_after = WN_CreateBlock();

    /* fill-in blocks with glue code */
    Set_Error_Phase("Region Finalize");
    Start_Timer(T_Region_Finalize_CU);
    CG_Region_Finalize( result_block_before, result_block_after,
                       rwn, alias_mgr, TRUE /* generate_glue_code */ );
    Stop_Timer(T_Region_Finalize_CU);

    /* generate alias information for glue code */
    REGION_update_alias_info(result_block_before, alias_mgr);
    REGION_update_alias_info(result_block_after, alias_mgr);

    /* insert glue code before and after */
    WN_INSERT_BlockFirst( rwn_new, result_block_before );
    WN_INSERT_BlockLast( rwn_new, result_block_after );

    GRA_LIVE_Finish_REGION();
    PQSCG_term();

    Stop_Timer ( T_CodeGen_CU );
    Set_Error_Phase ( "Codegen Driver" );

    return rwn_new;
  } /* if (region */

  else { /* PU */
    // dump EH entry info
    if (Get_Trace (TP_EH, 0x0001)) {
      Print_PU_EH_Entry(Get_Current_PU(), WN_st(rwn), TFile);
    }
    
#ifdef OPS_OPT
    /* Write the EH range table. 
     * if pu_need_LSDA is set for current PU, 
     * means no need to write EH range table
     */
    if (PU_has_exc_scopes(Get_Current_PU()) && pu_need_LSDA) {
#else
    if (PU_has_exc_scopes(Get_Current_PU())) {
#endif
      EH_Write_Range_Table(rwn);
    }

    // dump LSDA of current PU
    if (Get_Trace (TP_EH, 0x0008)) {
      EH_Dump_LSDA (TFile);
    }

    /* Emit the code for the PU. This may involve writing out the code to
     * an object file or to an assembly file or both. Additional tasks
     * performed by this module are:
     *
     *   - convert long branches into a chain of short branches.
     *   - add nada's to quad-align branch targets for TFP.
     */
    Set_Error_Phase ( "Assembly" );
    Start_Timer ( T_Emit_CU );
    if (Create_Cycle_Output)
        Cycle_Count_Initialize(Get_Current_PU_ST(), region);      
    /* Generate code to call mcount. See description of gcc -pg option.
     * This instrumentation is done just before code emission.
     */
    Instru_Call_Mcount();
    EMT_Emit_PU (Get_Current_PU_ST(), pu_dst, rwn);
    Check_for_Dump (TP_EMIT, NULL);
    Stop_Timer ( T_Emit_CU );

    if (ORC_Enable_Cache_Analysis) Cache_Analysis_End();

    Set_Error_Phase("Region Finalize");
    Start_Timer(T_Region_Finalize_CU);
    CG_Region_Finalize( NULL, NULL, rwn, alias_mgr,
                        FALSE /* generate_glue_code */ );
    Stop_Timer(T_Region_Finalize_CU);

    GRA_LIVE_Finish_PU();
    PQSCG_term();

    /* List local symbols if desired: */
    if ( List_Symbols )
      Print_symtab (Lst_File, CURRENT_SYMTAB);

    Stop_Timer ( T_CodeGen_CU );
    Set_Error_Phase ( "Codegen Driver" );

    return rwn;
  }
}


/* ================================================================= */
/* routines for dumping/tracing the program */

void
Trace_IR(
  INT phase,        /* Phase after which we're printing */
  const char *pname,    /* Print name for phase */
  BB *cur_bb,       /* BB to limit traces to */
  BOOL after)
{
  INT cur_bb_id = cur_bb ? BB_id(cur_bb) : 0;
  if (   Get_Trace(TKIND_IR, phase)
      && (cur_bb_id == 0 || Get_BB_Trace(cur_bb_id)))
  {
    if(after)
      fprintf(TFile, "\n%s%s\tIR after %s(BEGIN)  PU:%d\n%s%s\n ",
            DBar, DBar, pname, Current_PU_Count(), DBar, DBar);
    else
      fprintf(TFile, "\n%s%s\tIR before %s(BEGIN)  PU:%d\n%s%s\n ",
            DBar, DBar, pname, Current_PU_Count(), DBar, DBar); 	
    if (cur_bb != NULL) {
      Print_BB(cur_bb);
    } else {
      BB *bb;
      for (bb = REGION_First_BB; bb; bb = BB_next(bb))  {
        if (Get_BB_Trace(BB_id(bb)) && Get_Trace(TKIND_IR, phase)) {
          Print_BB(bb);
        }
      }
    }
    fprintf(TFile, "%s%s\n", DBar, DBar);
    if(after)
      fprintf(TFile, "\n%s%s\tIR after %s(END)  PU:%d\n%s%s\n ",
            DBar, DBar, pname, Current_PU_Count(), DBar, DBar);
    else
      fprintf(TFile, "\n%s%s\tIR before %s(END)  PU:%d\n%s%s\n ",
            DBar, DBar, pname, Current_PU_Count(), DBar, DBar);
    	
  }
}

static void
Trace_TN (
  INT phase,            /* Phase after which we're printing */
  const char *pname )   /* Print name for phase */
{
  if ( Get_Trace ( TKIND_TN, phase ) ) {
    fprintf ( TFile, "\n%s%s\tTNs after %s\n%s%s\n",
             DBar, DBar, pname, DBar, DBar );
    Print_TNs ();
  }
}

static void
Trace_ST (
  INT phase,            /* Phase after which we're printing */
  const char *pname )   /* Print name for phase */
{
  if ( Get_Trace ( TKIND_SYMTAB, phase ) ) {
    fprintf ( TFile, "\n%s%s\tSymbol table after %s\n%s%s\n",
              DBar, DBar, pname, DBar, DBar );
    SYMTAB_IDX level = CURRENT_SYMTAB;
    while (level >= GLOBAL_SYMTAB) {
        Print_symtab (TFile, level);
        --level;
    }
  }
}

/* ====================================================================
 *
 * Check_for_Dump
 *
 * Check whether symbol table, TN, or IR dumps have been requested for
 * the given pass; if so, generate them to the trace file.  If a BB is
 * given, limit the dumps to that BB.
 *
 * ====================================================================
 */
void
Check_for_Dump ( INT32 pass, BB *bb )
{
  if (bb == NULL || Get_BB_Trace(BB_id(bb))) {
    const char *s = Get_Error_Phase();

    /* Check to see if we should dump the STAB.
     */
    Trace_ST ( pass, s );

    /* Check to see if we should dump the TNs.
     */
    Trace_TN ( pass, s );

    /* Check to see if we should dump the IR.  If yes, check each BB.
     */
    Trace_IR ( pass, s, bb );

    /* Check to see if we should give a memory allocation trace.
     */
    Trace_Memory_Allocation ( pass, s );
  }
}

BOOL
Get_Trace ( INT func, INT arg, BB *bb )
{
  BOOL result = Get_Trace(func, arg);

  /* Check the BB if necessary: */
  if ( result && bb ) {
    result = Get_BB_Trace ( BB_id(bb) );
  }

  return result;
}


void
CG_Dump_Region(FILE *fd, WN *wn)
{
  RID   *rid = REGION_get_rid(wn);
  Is_True(rid != NULL, ("CG_Dump_Region, NULL RID"));
  if (rid && RID_level(rid) >= RL_CGSCHED) {
    CGRIN  *cgrin = RID_cginfo(rid);
    if (cgrin && CGRIN_entry(cgrin)) {
      BB *bb;
      for (bb=CGRIN_entry(cgrin); bb; bb=BB_next(bb))
        Print_BB( bb );
    }
  }
}

/* just an externally-visible wrapper to cgemit function */
extern void
CG_Change_Elf_Symbol_To_Undefined (ST *st)
{
    EMT_Change_Symbol_To_Undefined(st);
}
