/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

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


//-*-c++-*-
// ====================================================================
// ====================================================================
//
// Module: instr_reader.cxx
// $Revision: 1.17 $
// $Date: 2001/03/10 03:19:07 $
// $Author: mtibuild $
// $Source: /isms/cmplrs.src/osprey1.0/common/instrument/RCS/instr_reader.cxx,v $
//
// Revision history:
//  03-Aug-98 - Original Version
//
// Description:
//
// This module implements the reader for the feedback file generated
// by compiler instrumentation
//
// ====================================================================
// ====================================================================

#include "instr_reader.h"
#include "instr_memory.h"

static char* ERR_POS = "Error in positioning within %s";
static char* ERR_READ = "Error in reading from %s";

#ifndef _BUILD_INSTR

BOOL Feedback_Enabled[PROFILE_PHASE_LAST] = {FALSE,FALSE,FALSE,FALSE};
Fb_File_Info_Vector Feedback_File_Info[PROFILE_PHASE_LAST];

void
Process_Feedback_File(char *fb_name)
{
  FILE *fp;
  Fb_Hdr fb_hdr;
  Pu_Hdr *pu_hdr_table;
  char *str_table;
  PROFILE_PHASE phase_num;

  if ((fp = fopen(fb_name, "r")) == NULL) {
       profile_error("Unable to open file: %s", fb_name);
  }

  Get_File_Header(fp, fb_name, &fb_hdr);

  pu_hdr_table = CXX_NEW_ARRAY(Pu_Hdr, fb_hdr.fb_pu_hdr_num,
			       MEM_pu_nz_pool_ptr);

  Get_Pu_Hdr_Table(fp,fb_name,fb_hdr,pu_hdr_table);

  
  str_table = CXX_NEW_ARRAY(char, fb_hdr.fb_str_table_size,
			    MEM_pu_nz_pool_ptr);
  Get_Str_Table(fp, fb_name,fb_hdr,str_table);

  phase_num = Get_Phase_Num(fb_hdr);

  Feedback_Enabled[phase_num] = TRUE;

  Fb_File_Info_Vector& fi = Feedback_File_Info[phase_num];

  fi.push_back (CXX_NEW(Fb_File_Info(fb_name, fp, fb_hdr, pu_hdr_table,
				     str_table),
			MEM_pu_nz_pool_ptr));  
}

void
Close_Feedback_Files()
{
 
  INT32 i;

  for (i = (INT32)PROFILE_PHASE_BEFORE_VHO; 
       i < (INT32) PROFILE_PHASE_LAST;
       i++) 
  {
    if (Feedback_Enabled[i]) {
	for (File_Info_Iterator iter (Feedback_File_Info[i].begin ());
	     iter != Feedback_File_Info[i].end (); ++iter)
	    fclose((*iter)->fp);
    }
  }
}


PROFILE_PHASE
Get_Phase_Num(Fb_Hdr& fb_hdr)
{
  return fb_hdr.phase_num;
}


PU_PROFILE_HANDLES
Get_PU_Profile (char *pu_name, char *src_fname,
		Fb_File_Info_Vector& file_info_vector)
{
    PU_PROFILE_HANDLES handles (MEM_pu_nz_pool_ptr);
    
    for (File_Info_Iterator i (file_info_vector.begin ());
	 i != file_info_vector.end (); ++i) {
	Fb_File_Info* file_info = *i;
	PU_PROFILE_HANDLE handle = Get_PU_Profile (pu_name, src_fname,
						   file_info->fp,
						   file_info->name,
						   file_info->fb_hdr,
						   file_info->pu_hdr_table,
						   file_info->str_table);
	if (handle)
	    handles.push_back (handle);
    }

    return handles;
}

// Given a PU name, the main header in the feedback file, the PU
// header tabel and the string table, locate the information for the 
// PU in the feedback file. Create a new PU handle and update the
// various tables in the PU handle with the data from the feedback file.
// Returns a PU handle.

PU_PROFILE_HANDLE
Get_PU_Profile(char *pu_name, char *src_fname, FILE *fp, char *fb_fname, 
	       Fb_Hdr& fb_hdr, Pu_Hdr *pu_hdr_table, char *str_table) 
{
  PU_PROFILE_HANDLE pu_handle;
  Pu_Hdr pu_hdr_entry;
  long pu_ofst;
  char *entry_name;

  // Concatenate the file name and pu_name and look for the resultant string
  // in the pu header table.

  char *s;
  s = CXX_NEW_ARRAY(char, strlen(src_fname) + strlen("/") + strlen(pu_name)
		    + 1, MEM_pu_nz_pool_ptr);

  strcpy(s,src_fname);
  strcat(s,"/");
  strcat(s,pu_name);

  // Search the PU header table

  for (long i = 0; i < fb_hdr.fb_pu_hdr_num; i++) {
    pu_hdr_entry = pu_hdr_table[i];
    entry_name = str_table + pu_hdr_entry.pu_name_index;
    if (strcmp(s, entry_name) == 0) break;
  }

  // Make sure PU was found.
  if (strcmp(s, entry_name) != 0) 
    return NULL;

  pu_ofst = fb_hdr.fb_profile_offset + pu_hdr_entry.pu_file_offset;

  pu_handle = CXX_NEW(PU_Profile_Handle(entry_name, pu_hdr_entry.pu_checksum),
		      MEM_pu_nz_pool_ptr);

  read_invoke_profile(   pu_handle, pu_hdr_entry, pu_ofst, fp, fb_fname );
  read_branch_profile(   pu_handle, pu_hdr_entry, pu_ofst, fp, fb_fname );
  read_switch_profile(   pu_handle, pu_hdr_entry, pu_ofst, fp, fb_fname );
  read_cgoto_profile(    pu_handle, pu_hdr_entry, pu_ofst, fp, fb_fname );
  read_loop_profile(     pu_handle, pu_hdr_entry, pu_ofst, fp, fb_fname );
  read_scircuit_profile( pu_handle, pu_hdr_entry, pu_ofst, fp, fb_fname );
  read_call_profile(     pu_handle, pu_hdr_entry, pu_ofst, fp, fb_fname );

  return pu_handle;
}

// Given a PU handle, return the pu_name

char *
Get_PU_Name(PU_PROFILE_HANDLE pu_handle)
{
  return pu_handle->pu_name;
}

// Given a PU handle, return the checksum
INT32
Get_PU_Checksum(PU_PROFILE_HANDLE pu_handle)
{
  return pu_handle->checksum;
}


// Given a PU handle, returns the size of the invoke table for that PU.

size_t
Get_Invoke_Table_Size(PU_PROFILE_HANDLE pu_handle)
{
   FB_Invoke_Vector& Inv_Table = pu_handle->Get_Invoke_Table();
   return Inv_Table.size();
}

// Given a PU handle and a invoke id, returns the profile data for that id.

FB_Info_Invoke&
Get_Invoke_Profile(PU_PROFILE_HANDLE pu_handle, INT32 id)
{
   FB_Invoke_Vector& Inv_Table = pu_handle->Get_Invoke_Table();
   return Inv_Table[id];
}

// Given a PU handle, returns the size of the branch table for that PU.

size_t
Get_Branch_Table_Size(PU_PROFILE_HANDLE pu_handle)
{
   FB_Branch_Vector& Br_Table = pu_handle->Get_Branch_Table();
   return Br_Table.size();
}

// Given a PU handle and a branch id, returns the profile data for that id.

FB_Info_Branch&
Get_Branch_Profile(PU_PROFILE_HANDLE pu_handle, INT32 id)
{
   FB_Branch_Vector& Br_Table = pu_handle->Get_Branch_Table();
   return Br_Table[id];
}

// Given a PU handle, returns the size of the switch table for that PU.

size_t
Get_Switch_Table_Size(PU_PROFILE_HANDLE pu_handle)
{
   FB_Switch_Vector& Switch_Table = pu_handle->Get_Switch_Table();
   return Switch_Table.size();

}

// Given a PU handle and a switch id, returns the profile data for that id.

FB_Info_Switch&
Get_Switch_Profile(PU_PROFILE_HANDLE pu_handle, INT32 id)
{
   FB_Switch_Vector& Switch_Table = pu_handle->Get_Switch_Table();
   return Switch_Table[id];
}

size_t
Get_Compgoto_Table_Size(PU_PROFILE_HANDLE pu_handle)
{
   FB_Switch_Vector& Cgoto_Table = pu_handle->Get_Compgoto_Table();
   return Cgoto_Table.size();

}

// Given a PU handle and a compgoto id, returns the profile data for that id.

FB_Info_Switch&
Get_Compgoto_Profile(PU_PROFILE_HANDLE pu_handle, INT32 id)
{
   FB_Switch_Vector& Cgoto_Table = pu_handle->Get_Compgoto_Table();
   return Cgoto_Table[id];
}

// Given a PU handle, returns the size of the loop table for that PU.

size_t
Get_Loop_Table_Size(PU_PROFILE_HANDLE pu_handle)
{
   FB_Loop_Vector& Loop_Table = pu_handle->Get_Loop_Table();
   return Loop_Table.size();
}

// Given a PU handle and a loop id, return the profile data for that id.

FB_Info_Loop&
Get_Loop_Profile(PU_PROFILE_HANDLE pu_handle, INT32 id)
{
   FB_Loop_Vector& Loop_Table = pu_handle->Get_Loop_Table();
   return Loop_Table[id];
}

// Given a PU handle, returns the size of the scircuit table for that PU.

size_t
Get_Short_Circuit_Table_Size(PU_PROFILE_HANDLE pu_handle)
{
   FB_Circuit_Vector& Short_Circuit_Table
     = pu_handle->Get_Short_Circuit_Table();
   return Short_Circuit_Table.size();

}

// Given a PU handle and a CAND/COR id, return the profile data for that id.

FB_Info_Circuit&
Get_Short_Circuit_Profile(PU_PROFILE_HANDLE pu_handle, INT32 id)
{
   FB_Circuit_Vector& Short_Circuit_Table
     = pu_handle->Get_Short_Circuit_Table();
   return Short_Circuit_Table[id];
}

// Given a PU handle, returns the size of the call table for that PU.

size_t
Get_Call_Table_Size(PU_PROFILE_HANDLE pu_handle)
{
   FB_Call_Vector& Call_Table = pu_handle->Get_Call_Table();
   return Call_Table.size();
}

// Given a PU handle and a call id, return the profile data for that id.

FB_Info_Call&
Get_Call_Profile(PU_PROFILE_HANDLE pu_handle, INT32 id)
{
   FB_Call_Vector& Call_Table = pu_handle->Get_Call_Table();
   return Call_Table[id];
}

#endif // _BUILD_INSTR


// Read the main header in the feedback file

void
Get_File_Header(FILE *fp, char *fname, Fb_Hdr *fb_hdr)
{
  FSEEK(fp,0,SEEK_SET,ERR_POS,fname);

  FREAD(fb_hdr, sizeof(Fb_Hdr), 1, fp,
        "Error while writing to: %s", fname);
}

// Read the PU header table; It is assumed that the caller has 
// allocated the necessary storage in pu_hdr_table.

void
Get_Pu_Hdr_Table(FILE *fp, char *fname, Fb_Hdr& fb_hdr, 
		 Pu_Hdr *pu_hdr_table)
{
  FSEEK(fp,fb_hdr.fb_pu_hdr_offset,SEEK_SET, ERR_POS, fname);

  FREAD(pu_hdr_table, sizeof(Pu_Hdr), fb_hdr.fb_pu_hdr_num, fp, ERR_READ,
	fname);
}

// Read the string table that holds the names of PU's;
// It is assumed that the caller has allocated the 
// necessary storage in str_table.

void
Get_Str_Table(FILE *fp, char *fname, Fb_Hdr& fb_hdr, char *str_table)
{
  FSEEK(fp,fb_hdr.fb_str_table_offset, SEEK_SET, ERR_POS, fname);

  FREAD(str_table, sizeof(char), fb_hdr.fb_str_table_size, fp, ERR_READ,
        fname);
}

// Given a PU handle, allocate storage for the Invoke Table in 
// PU handle and update it with data from feedback file.

void
read_invoke_profile(PU_PROFILE_HANDLE pu_handle, Pu_Hdr& pu_hdr_entry,
                    long pu_ofst, FILE *fp, char *fname)
{
  FB_Invoke_Vector& Inv_Table = pu_handle->Get_Invoke_Table();

  Is_True (Inv_Table.empty (), ("pu_handle not empty"));

  Inv_Table.resize(pu_hdr_entry.pu_num_inv_entries);

  
  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_inv_offset, SEEK_SET, ERR_POS, fname);
 
  FREAD (&(Inv_Table.front ()), sizeof(FB_Info_Invoke),
	 pu_hdr_entry.pu_num_inv_entries, fp, ERR_READ, fname);
}

// Given a PU handle, allocate storage for the Branch Table in 
// PU handle and update it with data from feedback file.

void
read_branch_profile(PU_PROFILE_HANDLE pu_handle, Pu_Hdr& pu_hdr_entry,
                    long pu_ofst, FILE *fp, char *fname)
{
  FB_Branch_Vector& Br_Table = pu_handle->Get_Branch_Table();

  Is_True (Br_Table.empty (), ("pu_handle not empty"));

  Br_Table.resize(pu_hdr_entry.pu_num_br_entries);

  
  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_br_offset, SEEK_SET, ERR_POS, fname);

  FREAD (&(Br_Table.front ()), sizeof(FB_Info_Branch),
	 pu_hdr_entry.pu_num_br_entries, fp, ERR_READ, fname);
}

// Given a PU handle, allocate storage for the Switch Table in 
// PU handle and update it with data from feedback file.

void
read_switch_profile(PU_PROFILE_HANDLE pu_handle, Pu_Hdr& pu_hdr_entry,
                    long pu_ofst, FILE *fp, char *fname)
{
  vector<INT32> targets_vector (pu_hdr_entry.pu_num_switch_entries);
  
  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_switch_target_offset, SEEK_SET,
	ERR_POS, fname);

  FREAD (&(targets_vector.front ()), sizeof(INT32),
	 pu_hdr_entry.pu_num_switch_entries, fp, ERR_READ, fname);

  FB_Switch_Vector& Switch_Table = pu_handle->Get_Switch_Table();

  Is_True (Switch_Table.empty (), ("pu_handle not empty"));

  Switch_Table.resize(pu_hdr_entry.pu_num_switch_entries);

  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_switch_offset, SEEK_SET, ERR_POS, fname);
 
  vector<INT32>::const_iterator target (targets_vector.begin ());
  for (FB_Switch_Vector::iterator first (Switch_Table.begin ());
       first != Switch_Table.end (); ++first) {

      first->freq_targets.resize (*target);

      FREAD (&(first->freq_targets.front ()), sizeof(FB_FREQ), *target, fp,
	     ERR_READ, fname);  

      ++target;
  }
} 

// Given a PU handle, allocate storage for the Compgoto Table in 
// PU handle and update it with data from feedback file.

void
read_cgoto_profile(PU_PROFILE_HANDLE pu_handle, Pu_Hdr& pu_hdr_entry,
                    long pu_ofst, FILE *fp, char *fname)
{
  vector<INT32> target_vectors (pu_hdr_entry.pu_num_cgoto_entries);

  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_cgoto_target_offset, SEEK_SET,
	ERR_POS, fname);
  
  FREAD (&(target_vectors.front ()), sizeof(INT32),
	 pu_hdr_entry.pu_num_cgoto_entries, fp, ERR_READ, fname);

  FB_Switch_Vector& Cgoto_Table = pu_handle->Get_Compgoto_Table();

  Is_True (Cgoto_Table.empty (), ("pu_handle not empty"));

  Cgoto_Table.resize(pu_hdr_entry.pu_num_cgoto_entries);

  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_cgoto_offset, SEEK_SET, ERR_POS, fname);
 
  vector<INT32>::const_iterator target (target_vectors.begin ());
  for (FB_Switch_Vector::iterator first (Cgoto_Table.begin ());
       first != Cgoto_Table.end (); ++first) {

      first->freq_targets.resize(*target);

      FREAD (&(first->freq_targets.front ()), sizeof(FB_FREQ), *target, fp,
	     ERR_READ, fname); 
      ++target;
  }
}  

// Given a PU handle, allocate storage for the Loop Table in 
// PU handle and update it with data from feedback file.

void
read_loop_profile(PU_PROFILE_HANDLE pu_handle, Pu_Hdr& pu_hdr_entry,
                    long pu_ofst, FILE *fp, char *fname)
{
  FB_Loop_Vector& Loop_Table = pu_handle->Get_Loop_Table();

  Is_True (Loop_Table.empty (), ("pu_handle not empty"));

  Loop_Table.resize(pu_hdr_entry.pu_num_loop_entries);

  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_loop_offset, SEEK_SET, ERR_POS, fname);
 
  FREAD (&(Loop_Table.front ()), sizeof (FB_Info_Loop),
	 pu_hdr_entry.pu_num_loop_entries, fp, ERR_READ, fname);
}

// Given a PU handle, allocate storage for the Short Circuit Table in 
// PU handle and update it with data from feedback file.

void
read_scircuit_profile(PU_PROFILE_HANDLE pu_handle, Pu_Hdr& pu_hdr_entry,
                    long pu_ofst, FILE *fp, char *fname)
{
  FB_Circuit_Vector& Scircuit_Table = pu_handle->Get_Short_Circuit_Table();

  Is_True (Scircuit_Table.empty (), ("pu_handle not empty"));
  
  Scircuit_Table.resize(pu_hdr_entry.pu_num_scircuit_entries);

  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_scircuit_offset, SEEK_SET, ERR_POS,
	fname); 
 
  FREAD (&(Scircuit_Table.front ()), sizeof(FB_Info_Circuit),
	 pu_hdr_entry.pu_num_scircuit_entries, fp, ERR_READ, fname);
}

// Given a PU handle, allocate storage for the Call Table in 
// PU handle and update it with data from feedback file.

void
read_call_profile(PU_PROFILE_HANDLE pu_handle, Pu_Hdr& pu_hdr_entry,
                    long pu_ofst, FILE *fp, char *fname)
{
  FB_Call_Vector& Call_Table = pu_handle->Get_Call_Table();

  Is_True (Call_Table.empty (), ("pu_handle not empty"));

  Call_Table.resize(pu_hdr_entry.pu_num_call_entries);

  FSEEK(fp, pu_ofst + pu_hdr_entry.pu_call_offset, SEEK_SET, ERR_POS, fname);
 
  FREAD (&(Call_Table.front ()), sizeof(FB_Info_Call),
	 pu_hdr_entry.pu_num_call_entries, fp, ERR_READ, fname);
}
