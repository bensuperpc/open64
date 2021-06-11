/*

  Copyright (C) 1999-2001, Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2.1 of the GNU Lesser General Public License
  as published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  Further, any
  license provided herein, whether implied or otherwise, is limited to 
  this program in accordance with the express provisions of the 
  GNU Lesser General Public License.  

  Patent licenses, if any, provided herein do not apply to combinations 
  of this program with other product or programs, or any other product 
  whatsoever.  This program is distributed without any warranty that the 
  program is delivered free of the rightful claim of any third person by 
  way of infringement or the like.  

  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

*/

/* $Header: /cvsroot/open64/open64/osprey1.0/libU77/gmtime_.c,v 1.1.1.1 2001/09/10 17:50:04 morrone Exp $ */
/*
 *
 * return broken down time
 *
 * calling sequence:
 *	integer time, t[9]
 *	call gmtime(time, t)
 * where:
 *	time is a system time. (see time(3F))
 *	t will receive the broken down time assuming GMT.
 *	(see ctime(3))
 */

#include <time.h>

extern void
gmtime_ (int *clock, int *t)
{
	int i;
	int *g;

	g = (int*)gmtime((time_t *)clock);
	for (i=0; i<9; i++)
		*t++ = *g++;
}

