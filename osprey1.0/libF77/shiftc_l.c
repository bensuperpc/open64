/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2.1 of the GNU Lesser General Public License 
  as published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU Lesser General Public 
  License along with this program; if not, write the Free Software 
  Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, 
  USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/


/* $Header: /isms/cmplrs.src/osprey1.0/libF77/RCS/shiftc_l.c,v 8.7 2001/03/10 04:46:25 mtibuild Exp $ */
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	actual or intended publication of such source code.	*/

#include "bit.h"
#include "cmplrs/host.h"


/* Circular shift - The right most ic bits are shifted circularly k-places.
 * k > 0 => left shift.
 * k < 0 => right shift.
 * k = 0 => no shift.
 *	left shift			 right shift
 *	[  b1   |   k2   |   d   ]       [  b1   |   d   |   k2   ]
 */

int32 shftc_l(int32 *m,int32 *k,int32 *ic)
{
	int32 b1, b2, b3, k2, d;
	int16 left;

	left = (*k > 0);
	k2 = left ? *k : -*k;
	if (k2 == 0 || k2 > NBI || k2 > *ic || *ic < 1 || *ic > NBI)
		return(*m);
	d = (*ic - k2);
	b1 = *m & ~F77mask[*ic];		/* mask off left most bits */

	if (left) {
		b2 = ( (unsigned)(*m & F77mask[  d]) ) << k2; /* get  d bits */
		b3 = ( (unsigned)(*m & F77mask[*ic]) ) >> d;  /* get k2 bits */
		}
	else {
		b2 = ( (unsigned)(*m & F77mask[ k2]) ) <<   d;/* get k2 bits */
		b3 = ( (unsigned)(*m & F77mask[*ic]) ) >>  k2;/* get d  bits */
		}
	return( b1 | b2 | b3 );
}
