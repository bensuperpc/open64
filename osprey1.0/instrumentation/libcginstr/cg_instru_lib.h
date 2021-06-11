/*
  Copyright (C) 2000-2002, Institute of Computing Technology, Chinese Academy of Sciences
  All rights reserved.
  
  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:
  
  Redistributions of source code must retain the above copyright notice, this list
  of conditions and the following disclaimer. 

  Redistributions in binary form must reproduce the above copyright notice, this list
  of conditions and the following disclaimer in the documentation and/or other materials
  provided with the distribution. 

  Neither the name of the owner nor the names of its contributors may be used to endorse or
  promote products derived from this software without specific prior written permission. 

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
 
//-*-c++-*-
//*********************************************************************
//
// Module: instru_lib
// $Date: 2002/02/18 20:45:34 $
// $Author: douillet $
// $Source: /cvsroot/open64/open64/osprey1.0/instrumentation/libcginstr/cg_instru_lib.h,v $
//
// Description:
//
// Interface to cg instrumentation library functions.
//
//*********************************************************************
#ifndef cg_instru_lib_INCLUDED
#define cg_instru_lib_INCLUDED

#ifndef EDGE_PROFILE
#define EDGE_PROFILE
#endif

#include "profile_com.h"

#define ERROR_VALUE -1

#ifndef MAP_FILE              // 44BSD defines this & requires it to mmap files 
#define MAP_FILE 0            // to compile under systems other than 44BSD  
#endif  

enum FB_FREQ_TYPE {
    FB_FREQ_TYPE_EXACT   =  1, 
    FB_FREQ_TYPE_GUESS   =  0, 
    FB_FREQ_TYPE_UNKNOWN = -1, 
    FB_FREQ_TYPE_UNINIT  = -2, 
    FB_FREQ_TYPE_ERROR   = -3
};

struct _FREQ {
    FB_FREQ_TYPE  _type;
    INT32 _value;
};

struct FB_FREQ {
    FB_FREQ_TYPE  _type;
    float _value;
};

#define EDGE_PROFILE_ALLOC   0x0001
#define VALUE_PROFILE_ALLOC  0x0002

struct FB_TNV{
    UINT32 _id;            // instruction id.
    INT32 _flag;           // 0 for integer type, 1 for float type.
                           // Note: for "float" type, we just put it here as an "integer".
                           // Because they have same size.
    UINT64 _exec_counter;  // how many times does this instruction executed.
    UINT64 _clear_counter;
    UINT64 _values[10];    // top 10 values. 
    UINT64 _counters[10];  // counters for top 10 values.
};

struct PU_PROFILE_INFO{
    // edge profile info
    INT32  _edge_sum;
    INT32  _has_alloc;
    _FREQ* _counter;
    
    // value profile info
    UINT32 _instr_count; //how many instrutions has been profiled in this pu. E
                         //qual to the item number in <_val_prof_tnv_table>
    UINT64 _sum_count;   //the sum of each profiled instruction executes. Used as
                         //Checksum.
    FB_TNV* _val_prof_tnv_table;
    
    PU_PROFILE_INFO():_has_alloc(0),
      _edge_sum(0),
      _counter(NULL),
      _sum_count(0),
      _instr_count(0),
      _val_prof_tnv_table(NULL){}
      
    PU_PROFILE_INFO(INT32 sum, _FREQ* counter)
    {
      _edge_sum = sum;
      _has_alloc = EDGE_PROFILE_ALLOC;
      _counter = counter;
      _sum_count= 0;
      _instr_count = 0;
      _val_prof_tnv_table = NULL;
    }
    
    PU_PROFILE_INFO(UINT32 instr_count, UINT32 sum_count, FB_TNV* tnv_table)
    {
      _edge_sum = 0;
      _has_alloc = VALUE_PROFILE_ALLOC;
      _counter = NULL;
      _sum_count= sum_count;
      _instr_count = instr_count;
      _val_prof_tnv_table = tnv_table;
    }
};

// ------------------------------------------------------------------
// List of functions that is used to write feedback data into output 
// file in instrumentation lib 
// ------------------------------------------------------------------
void _write_File_Header(void);
void _write_Pu_Header(void);
void _write_Str_Header(void);
void _write_pu_data(void);
void _write_edge_profile(PU_PROFILE_INFO* pu_info);

void _write_TNV_items_profile( PU_PROFILE_INFO* pu_info );
// ------------------------------------------------------------------    
// List of functions in instrumentation lib 
// ------------------------------------------------------------------
extern "C"{

void __profile_init( char* output_file, 
                    PROFILE_PHASE phasenum);
void __profile_pu_init(char* _srcfile_pu_name, INT32 checksum);
void __profile_edge(char* srcfile_pu_name,UINT32 id);

void __value_profile_pu_init(char * outputfile, 
           char* srcfile_pu_name,  PROFILE_PHASE phase, UINT32 instr_count);
void __value_profile_invoke( char* srcfile_pu_name, 
                             UINT32 instr_id, UINT64 value);
}

// __profile_finalize will be invoked in crt, it write feedback data into
// output file
void __profile_finalize(void);

// Free_Space free the allocated memory space
void Free_Space(void);

// ------------------------------------------------------------------    
// function in instrumentation lib when errors occur 
// ------------------------------------------------------------------
void instru_lib_error(const char *fmt, char* msg="");

#endif

