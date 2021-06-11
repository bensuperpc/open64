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

//
// Generate an ISA containing the instructions specified.
/////////////////////////////////////////////////////////
// The instructions are listed by category. The different categories of
// instructions are:
//
//   1. Integer instructions
//   2. FP instructions
//   3. Simulated instructions
//   4. Dummy instructions
//
// Within each category, the instructions are in alphabetical order.
// This arrangement of instructions matches the order in the ISA manual.
/////////////////////////////////////
//
//  $Revision: 1.25 $
//  $Date: 2001/03/10 01:16:13 $
//  $Author: mtibuild $
//  $Source: /osprey.src/osprey1.0/common/targ_info/isa/ia64/RCS/isa.cxx,v $

#include <stddef.h>
#include "isa_gen.h"

main ()
{
  ISA_Create ("ia64", 
	"add",
	"add_1",
	"adds",
	"addl",
	"addp4",
	"addp4_i",
	"alloc_3",
	"and",
	"and_i",
	"andcm",
	"andcm_i",
	"br.cond",
	"br_r.cond",
	"br.call",
	"br_r.call",
	"br.ret",
	"br.ia",
	"br.cloop",
	"br.ctop",
	"br.cexit",
	"br.wtop",
	"br.wexit",
	"break.i",
	"break.b",
	"break.m",
	"break.f",
	"break.x",
	"brl.cond",
	"brl.call",
	"brp",
	"brp_r",
	"brp.ret",
	"bsw.0",
	"bsw.1",
	"chk.s.i",
	"chk.s.m",
	"chk_f.s",
	"chk.a",
	"chk_f.a",
	"clrrrb",
	"clrrrb.pr",
	"cmp.eq",
	"cmp.eq.unc",
	"cmp.eq.and",
	"cmp.eq.or",
	"cmp.eq.or.andcm",
	"cmp.ne.and",
	"cmp.ne.or",
	"cmp.ne.or.andcm",
	"cmp.lt",
	"cmp.lt.unc",
	"cmp.ltu",
	"cmp.ltu.unc",
	"cmp_z1.lt.and",
	"cmp_z1.lt.or",
	"cmp_z1.lt.or.andcm",
	"cmp_z1.le.and",
	"cmp_z1.le.or",
	"cmp_z1.le.or.andcm",
	"cmp_z1.gt.and",
	"cmp_z1.gt.or",
	"cmp_z1.gt.or.andcm",
	"cmp_z1.ge.and",
	"cmp_z1.ge.or",
	"cmp_z1.ge.or.andcm",
	"cmp_i.eq",
	"cmp_i.eq.unc",
	"cmp_i.eq.and",
	"cmp_i.eq.or",
	"cmp_i.eq.or.andcm",
	"cmp_i.ne.and",
	"cmp_i.ne.or",
	"cmp_i.ne.or.andcm",
	"cmp_i.lt",
	"cmp_i.lt.unc",
	"cmp_i.ltu",
	"cmp_i.ltu.unc",
	"cmp4.eq",
	"cmp4.eq.unc",
	"cmp4.eq.and",
	"cmp4.eq.or",
	"cmp4.eq.or.andcm",
	"cmp4.ne.and",
	"cmp4.ne.or",
	"cmp4.ne.or.andcm",
	"cmp4.lt",
	"cmp4.lt.unc",
	"cmp4.ltu",
	"cmp4.ltu.unc",
	"cmp4_z1.lt.and",
	"cmp4_z1.lt.or",
	"cmp4_z1.lt.or.andcm",
	"cmp4_z1.le.and",
	"cmp4_z1.le.or",
	"cmp4_z1.le.or.andcm",
	"cmp4_z1.gt.and",
	"cmp4_z1.gt.or",
	"cmp4_z1.gt.or.andcm",
	"cmp4_z1.ge.and",
	"cmp4_z1.ge.or",
	"cmp4_z1.ge.or.andcm",
	"cmp4_i.eq",
	"cmp4_i.eq.unc",
	"cmp4_i.eq.and",
	"cmp4_i.eq.or",
	"cmp4_i.eq.or.andcm",
	"cmp4_i.ne.and",
	"cmp4_i.ne.or",
	"cmp4_i.ne.or.andcm",
	"cmp4_i.lt",
	"cmp4_i.lt.unc",
	"cmp4_i.ltu",
	"cmp4_i.ltu.unc",
	"cmpxchg1",
	"cmpxchg2",
	"cmpxchg4",
	"cmpxchg8",
	"cover",
	"czx1.l",
	"czx1.r",
	"czx2.l",
	"czx2.r",
	"dep",
	"dep.z",
	"dep_i",
	"dep_i.z",
	"epc",
	"extr",
	"extr.u",
	"famax",
	"famin",
	"fand",
	"fandcm",
	"fc",
	"fchkf",
	"fclass.m",
	"fclass.m.unc",
	"fclrf",
	"fcmp.eq",
	"fcmp.eq.unc",
	"fcmp.lt",
	"fcmp.lt.unc",
	"fcmp.le",
	"fcmp.le.unc",
	"fcmp.unord",
	"fcmp.unord.unc",
	"fcvt.fx",
	"fcvt.fx.trunc",
	"fcvt.fxu",
	"fcvt.fxu.trunc",
	"fcvt.xf",
	"fetchadd4",
	"fetchadd8",
	"flushrs",
	"fma",
	"fma.s",
	"fma.d",
	"fmax",
	"fmerge.ns",
	"fmerge.s",
	"fmerge.se",
	"fmin",
	"fmix.l",
	"fmix.r",
	"fmix.lr",
	"fms",
	"fms.s",
	"fms.d",
	"fnma",
	"fnma.s",
	"fnma.d",
	"for",
	"fpack",
	"fpamax",
	"fpamin",
	"fpcmp.eq",
	"fpcmp.lt",
	"fpcmp.le",
	"fpcmp.unord",
	"fpcmp.neq",
	"fpcmp.nlt",
	"fpcmp.nle",
	"fpcmp.ord",
	"fpcvt.fx",
	"fpcvt.fx.trunc",
	"fpcvt.fxu",
	"fpcvt.fxu.trunc",
	"fpma",
	"fpmax",
	"fpmerge.ns",
	"fpmerge.s",
	"fpmerge.se",
	"fpmin",
	"fpms",
	"fpnma",
	"fprcpa",
	"fprsqrta",
	"frcpa",
	"frsqrta",
	"fselect",
	"fsetc",
	"fswap",
	"fswap.nl",
	"fswap.nr",
	"fsxt.l",
	"fsxt.r",
	"fwb",
	"fxor",
	"getf.s",
	"getf.d",
	"getf.exp",
	"getf.sig",
	"invala",
	"invala.e",
	"invala_f.e",
	"itc.i",
	"itc.d",
	"itr.i",
	"itr.d",
	"ld1",
	"ld1_r",
	"ld1_i",
	"ld2",
	"ld2_r",
	"ld2_i",
	"ld4",
	"ld4_r",
	"ld4_i",
	"ld8",
	"ld8_r",
	"ld8_i",
	"ld8.fill",
	"ld8_r.fill",
	"ld8_i.fill",
	"ldfs",
	"ldfs_r",
	"ldfs_i",
	"ldfd",
	"ldfd_r",
	"ldfd_i",
	"ldfe",
	"ldfe_r",
	"ldfe_i",
	"ldf8",
	"ldf8_r",
	"ldf8_i",
	"ldf.fill",
	"ldf_r.fill",
	"ldf_i.fill",
	"ldfps",
	"ldfps_i",
	"ldfpd",
	"ldfpd_i",
	"ldfp8",
	"ldfp8_i",
	"lfetch",
	"lfetch.excl",
	"lfetch.fault",
	"lfetch.fault.excl",
	"lfetch_r",
	"lfetch_r.excl",
	"lfetch_r.fault",
	"lfetch_r.fault.excl",
	"lfetch_i",
	"lfetch_i.excl",
	"lfetch_i.fault",
	"lfetch_i.fault.excl",
	"loadrs",
	"mf",
	"mf.a",
	"mix1.l",
	"mix1.r",
	"mix2.l",
	"mix2.r",
	"mix4.l",
	"mix4.r",
	"mov_f_ar.i",
	"mov_t_ar_r.i",
	"mov_t_ar_i.i",
	"mov_f_ar.m",
	"mov_t_ar_r.m",
	"mov_t_ar_i.m",
	"mov_f_br",
	"mov_t_br_i",
	"mov_t_br.ret",
	"mov_t_cr",
	"mov_f_cr",
	"mov_f_cpuid",
	"mov_t_dbr",
	"mov_f_dbr",
	"mov_t_ibr",
	"mov_f_ibr",
	"mov_t_msr",
	"mov_f_msr",
	"mov_t_pkr",
	"mov_f_pkr",
	"mov_t_pmc",
	"mov_f_pmc",
	"mov_t_pmd",
	"mov_f_pmd",
	"mov_t_rr",
	"mov_f_rr",
	"mov_f_ip",
	"mov_f_pr",
	"mov_t_pr",
	"mov_t_pr_i",
	"mov_t_psr",
	"mov_f_psr",
	"mov_t_psrum",
	"mov_f_psrum",
	"movl",
	"mux1",
	"mux2",
	"nop.i",
	"nop.b",
	"nop.m",
	"nop.f",
	"nop.x",
	"or",
	"or_i",
	"pack2.sss",
	"pack2.uss",
	"pack4.sss",
	"padd1",
	"padd1.sss",
	"padd1.uus",
	"padd1.uuu",
	"padd2",
	"padd2.sss",
	"padd2.uus",
	"padd2.uuu",
	"padd4",
	"pavg1",
	"pavg1.raz",
	"pavg2",
	"pavg2.raz",
	"pavgsub1",
	"pavgsub2",
	"pcmp1.eq",
	"pcmp1.gt",
	"pcmp2.eq",
	"pcmp2.gt",
	"pcmp4.eq",
	"pcmp4.gt",
	"pmax1.u",
	"pmax2",
	"pmin1.u",
	"pmin2",
	"pmpy2.r",
	"pmpy2.l",
	"pmpyshr2",
	"pmpyshr2.u",
	"popcnt",
	"probe.r",
	"probe.w",
	"probe_i.r",
	"probe_i.w",
	"probe.r.fault",
	"probe.w.fault",
	"probe.rw.fault",
	"psad1",
	"pshl2",
	"pshl4",
	"pshl2_i",
	"pshl4_i",
	"pshladd2",
	"pshr2",
	"pshr2.u",
	"pshr4",
	"pshr4.u",
	"pshr2_i",
	"pshr2_i.u",
	"pshr4_i",
	"pshr4_i.u",
	"pshradd2",
	"psub1",
	"psub2",
	"psub4",
	"psub1.sss",
	"psub1.uus",
	"psub1.uuu",
	"psub2.sss",
	"psub2.uus",
	"psub2.uuu",
	"ptc.e",
	"ptc.g",
	"ptc.ga",
	"ptc.l",
	"ptr.d",
	"ptr.i",
	"rfi",
	"rsm",
	"rum",
	"setf.s",
	"setf.d",
	"setf.exp",
	"setf.sig",
	"shl",
	"shladd",
	"shladdp4",
	"shr",
	"shr.u",
	"shrp",
	"srlz.i",
	"srlz.d",
	"ssm",
	"st1",
	"st1_i",
	"st2",
	"st2_i",
	"st4",
	"st4_i",
	"st8",
	"st8_i",
	"st8.spill",
	"st8_i.spill",
	"stfs",
	"stfs_i",
	"stfd",
	"stfd_i",
	"stfe",
	"stfe_i",
	"stf8",
	"stf8_i",
	"stf.spill",
	"stf_i.spill",
	"sub",
	"sub_1",
	"sub_i",
	"sum",
	"sxt1",
	"sxt2",
	"sxt4",
	"sync.i",
	"tak",
	"tbit.z",
	"tbit.z.unc",
	"tbit.z.and",
	"tbit.z.or",
	"tbit.z.or.andcm",
	"tbit.nz.and",
	"tbit.nz.or",
	"tbit.nz.or.andcm",
	"thash",
	"tnat.z",
	"tnat.z.unc",
	"tnat.z.and",
	"tnat.z.or",
	"tnat.z.or.andcm",
	"tnat.nz.and",
	"tnat.nz.or",
	"tnat.nz.or.andcm",
	"tpa",
	"ttag",
	"unpack1.l",
	"unpack1.h",
	"unpack2.l",
	"unpack2.h",
	"unpack4.l",
	"unpack4.h",
	"xchg1",
	"xchg2",
	"xchg4",
	"xchg8",
	"xma.l",
	"xma.h",
	"xma.hu",
	"xor",
	"xor_i",
	"zxt1",
	"zxt2",
	"zxt4",
	"alloc",
	"br",
	"br_r",
	"brl",
	"cmp.eq.orcm",
	"cmp.eq.andcm",
	"cmp.eq.and.orcm",
	"cmp.ne",
	"cmp.ne.unc",
	"cmp.ne.orcm",
	"cmp.ne.andcm",
	"cmp.ne.and.orcm",
	"cmp.le",
	"cmp.le.unc",
	"cmp.gt",
	"cmp.gt.unc",
	"cmp.ge",
	"cmp.ge.unc",
	"cmp.leu",
	"cmp.leu.unc",
	"cmp.gtu",
	"cmp.gtu.unc",
	"cmp.geu",
	"cmp.geu.unc",
	"cmp_z1.lt.orcm",
	"cmp_z1.lt.andcm",
	"cmp_z1.lt.and.orcm",
	"cmp_z1.le.orcm",
	"cmp_z1.le.andcm",
	"cmp_z1.le.and.orcm",
	"cmp_z1.gt.orcm",
	"cmp_z1.gt.andcm",
	"cmp_z1.gt.and.orcm",
	"cmp_z1.ge.orcm",
	"cmp_z1.ge.andcm",
	"cmp_z1.ge.and.orcm",
	"cmp_z2.lt.orcm",
	"cmp_z2.lt.andcm",
	"cmp_z2.lt.and.orcm",
	"cmp_z2.le.orcm",
	"cmp_z2.le.andcm",
	"cmp_z2.le.and.orcm",
	"cmp_z2.gt.orcm",
	"cmp_z2.gt.andcm",
	"cmp_z2.gt.and.orcm",
	"cmp_z2.ge.orcm",
	"cmp_z2.ge.andcm",
	"cmp_z2.ge.and.orcm",
	"cmp_z2.lt.and",
	"cmp_z2.lt.or",
	"cmp_z2.lt.or.andcm",
	"cmp_z2.le.and",
	"cmp_z2.le.or",
	"cmp_z2.le.or.andcm",
	"cmp_z2.gt.and",
	"cmp_z2.gt.or",
	"cmp_z2.gt.or.andcm",
	"cmp_z2.ge.and",
	"cmp_z2.ge.or",
	"cmp_z2.ge.or.andcm",
	"cmp_i.eq.orcm",
	"cmp_i.eq.andcm",
	"cmp_i.eq.and.orcm",
	"cmp_i.ne",
	"cmp_i.ne.unc",
	"cmp_i.ne.orcm",
	"cmp_i.ne.andcm",
	"cmp_i.ne.and.orcm",
	"cmp_i.le",
	"cmp_i.le.unc",
	"cmp_i.gt",
	"cmp_i.gt.unc",
	"cmp_i.ge",
	"cmp_i.ge.unc",
	"cmp_i.leu",
	"cmp_i.leu.unc",
	"cmp_i.gtu",
	"cmp_i.gtu.unc",
	"cmp_i.geu",
	"cmp_i.geu.unc",
	"cmp4.eq.orcm",
	"cmp4.eq.andcm",
	"cmp4.eq.and.orcm",
	"cmp4.ne",
	"cmp4.ne.unc",
	"cmp4.ne.orcm",
	"cmp4.ne.andcm",
	"cmp4.ne.and.orcm",
	"cmp4.le",
	"cmp4.le.unc",
	"cmp4.gt",
	"cmp4.gt.unc",
	"cmp4.ge",
	"cmp4.ge.unc",
	"cmp4.leu",
	"cmp4.leu.unc",
	"cmp4.gtu",
	"cmp4.gtu.unc",
	"cmp4.geu",
	"cmp4.geu.unc",
	"cmp4_z1.lt.orcm",
	"cmp4_z1.lt.andcm",
	"cmp4_z1.lt.and.orcm",
	"cmp4_z1.le.orcm",
	"cmp4_z1.le.andcm",
	"cmp4_z1.le.and.orcm",
	"cmp4_z1.gt.orcm",
	"cmp4_z1.gt.andcm",
	"cmp4_z1.gt.and.orcm",
	"cmp4_z1.ge.orcm",
	"cmp4_z1.ge.andcm",
	"cmp4_z1.ge.and.orcm",
	"cmp4_z2.lt.orcm",
	"cmp4_z2.lt.andcm",
	"cmp4_z2.lt.and.orcm",
	"cmp4_z2.le.orcm",
	"cmp4_z2.le.andcm",
	"cmp4_z2.le.and.orcm",
	"cmp4_z2.gt.orcm",
	"cmp4_z2.gt.andcm",
	"cmp4_z2.gt.and.orcm",
	"cmp4_z2.ge.orcm",
	"cmp4_z2.ge.andcm",
	"cmp4_z2.ge.and.orcm",
	"cmp4_z2.lt.and",
	"cmp4_z2.lt.or",
	"cmp4_z2.lt.or.andcm",
	"cmp4_z2.le.and",
	"cmp4_z2.le.or",
	"cmp4_z2.le.or.andcm",
	"cmp4_z2.gt.and",
	"cmp4_z2.gt.or",
	"cmp4_z2.gt.or.andcm",
	"cmp4_z2.ge.and",
	"cmp4_z2.ge.or",
	"cmp4_z2.ge.or.andcm",
	"cmp4_i.eq.orcm",
	"cmp4_i.eq.andcm",
	"cmp4_i.eq.and.orcm",
	"cmp4_i.ne",
	"cmp4_i.ne.unc",
	"cmp4_i.ne.orcm",
	"cmp4_i.ne.andcm",
	"cmp4_i.ne.and.orcm",
	"cmp4_i.le",
	"cmp4_i.le.unc",
	"cmp4_i.gt",
	"cmp4_i.gt.unc",
	"cmp4_i.ge",
	"cmp4_i.ge.unc",
	"cmp4_i.leu",
	"cmp4_i.leu.unc",
	"cmp4_i.gtu",
	"cmp4_i.gtu.unc",
	"cmp4_i.geu",
	"cmp4_i.geu.unc",
	"fabs",
	"fadd",
	"fadd.s",
	"fadd.d",
	"fclass.nm",
	"fclass.nm.unc",
	"fcmp.gt",
	"fcmp.gt.unc",
	"fcmp.ge",
	"fcmp.ge.unc",
	"fcmp.neq",
	"fcmp.neq.unc",
	"fcmp.nlt",
	"fcmp.nlt.unc",
	"fcmp.nle",
	"fcmp.nle.unc",
	"fcmp.ngt",
	"fcmp.ngt.unc",
	"fcmp.nge",
	"fcmp.nge.unc",
	"fcmp.ord",
	"fcmp.ord.unc",
	"fcvt.xuf",
	"fcvt.xuf.s",
	"fcvt.xuf.d",
	"fmpy",
	"fmpy.s",
	"fmpy.d",
	"fneg",
	"fnegabs",
	"fnmpy",
	"fnmpy.s",
	"fnmpy.d",
	"fnorm",
	"fnorm.s",
	"fnorm.d",
	"fpabs",
	"fpcmp.gt",
	"fpcmp.ge",
	"fpcmp.ngt",
	"fpcmp.nge",
	"fpmpy",
	"fpneg",
	"fpnegabs",
	"fpnmpy",
	"fsub",
	"fsub.s",
	"fsub.d",
	"mov_t_br",
	"mov_f",
	"mov",
	"mov_i",
	"shl_i",
	"shr_i",
	"shr_i.u",
	"tbit.nz",
	"tbit.nz.unc",
	"tnat.nz",
	"tnat.nz.unc",
	"xma.lu",
	"xmpy.l",
	"xmpy.lu",
	"xmpy.h",
	"xmpy.hu",
	"break",
	"chk.s",
	"cmp.lt.and",
	"cmp.lt.or",
	"cmp.lt.or.andcm",
	"cmp.le.and",
	"cmp.le.or",
	"cmp.le.or.andcm",
	"cmp.gt.and",
	"cmp.gt.or",
	"cmp.gt.or.andcm",
	"cmp.ge.and",
	"cmp.ge.or",
	"cmp.ge.or.andcm",
	"cmp.lt.orcm",
	"cmp.lt.andcm",
	"cmp.lt.and.orcm",
	"cmp.le.orcm",
	"cmp.le.andcm",
	"cmp.le.and.orcm",
	"cmp.gt.orcm",
	"cmp.gt.andcm",
	"cmp.gt.and.orcm",
	"cmp.ge.orcm",
	"cmp.ge.andcm",
	"cmp.ge.and.orcm",
	"cmp4.lt.and",
	"cmp4.lt.or",
	"cmp4.lt.or.andcm",
	"cmp4.le.and",
	"cmp4.le.or",
	"cmp4.le.or.andcm",
	"cmp4.gt.and",
	"cmp4.gt.or",
	"cmp4.gt.or.andcm",
	"cmp4.ge.and",
	"cmp4.ge.or",
	"cmp4.ge.or.andcm",
	"cmp4.lt.orcm",
	"cmp4.lt.andcm",
	"cmp4.lt.and.orcm",
	"cmp4.le.orcm",
	"cmp4.le.andcm",
	"cmp4.le.and.orcm",
	"cmp4.gt.orcm",
	"cmp4.gt.andcm",
	"cmp4.gt.and.orcm",
	"cmp4.ge.orcm",
	"cmp4.ge.andcm",
	"cmp4.ge.and.orcm",
	"mov_f_ar",
	"mov_t_ar_r",
	"mov_t_ar_i",
	"nop",

      // Simulated instructions
//      "gotdisp",
      "asm",
      "intrncall",
      "spadjust",
      "copy.br",

      // Dummy instructions
      "begin.pregtn",
      "end.pregtn",
      "bwd.bar",
      "fwd.bar",
      "dfixup",
      "ffixup",
      "ifixup",
      "label",
      "noop",

      NULL);
}
