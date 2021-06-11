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


/* ====================================================================
 * ====================================================================
 *
 * Module: ori.h
 * $Revision: 1.1.1.1 $
 * $Date: 2001/09/10 17:48:06 $
 * $Author: morrone $
 * $Source: /cvsroot/open64/open64/osprey1.0/be/region/ori.h,v $
 *
 * Description:
 * Olimit Region Insertion (ORI)
 *
 * ====================================================================
 * ====================================================================
 */

#ifndef ori_INCLUDED
#define ori_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

extern WN * Olimit_Region_Insertion (WN *pu_tree, INT32 olimit);

#ifdef __cplusplus
}
#endif

#endif /* ori_INCLUDED */
