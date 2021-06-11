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


#pragma ident "@(#) libf/pxf/pxfreaddir.c	92.1	06/29/99 11:36:06"

#include <errno.h>
#include <liberrno.h>
#include <fortran.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <dirent.h>
#include "pxfstruct.h"
#include "table.h"

/*  PXFREADDIR  -- read director entry
 *  (section 5.1.2 of Posix 1003.9-1992)
 *
 *  Synopsis:
 *     SUBROUTINE PXFREADDIR(IDIRID,JDIRENT,IERROR)
 *     INTEGER IDIRID,JDIRENT,IERROR
 *
 *  Function Description:
 *  The routine PXFREADDIR uses readdir(3C) to read a directory
 *  directory stream for the next entry in the directory stream.
 *
 *  Description of arguments:
 *  IDIRID  is a input interger variable for the unique directory ID
 *          generated by PXFOPENDIR.
 *
 *  JDIRENT is an output structure handle created by PXFSTRUCTCREATE
 *          that contains one directory entry.
 *
 *  IERROR  is an output integer variable that will contain
 *          the status:
 *
 *              zero    - PXFREADDIR was successful.
 *
 *              nonzero - PXFREADDIR was not successful.
 *
 *          PXFREADDIR may return any of the following error
 *          values:
 *
 *           EBADF         If the IDIRID argument does not refer to an
 *                         open directory stream.
 *
 *           EEND          If the end of the directory stream has been
 *                         reached.
 *
 *           ENOMEM        If data structures need for successful
 *                         completion of PXFREADIR cannot be allocated.
 *
 *           ENOENT        If the current file pointer for the directory
 *                         stream is not located at a valid directory entry.
 *
 *           EDIRCORRUPTED If the directory on disk is corrupt.
 *                         (IRIX only)
 *
 *           EAGAIN        If there was a blocking record lock while
 *                         mandatory file/record locking and O_NDELAY
 *                         or O_NONBLOCK were set, or if an insufficent
 *                         amount of system memory available when
 *                         raw I/0 read was used, or if a file associated
 *                         with a tty device and with O_NONBLOCK set
 *                         has no data waiting to be read, or if messages
 *                         are not waiting to be read on a directory
 *                         stream and O_NDELAY or O_NONBLOCK was set.
 *                         (Solaris only)
 *
 *           EBADMSG       If message data read from a directory stream
 *                         was not a directory.
 *                         (Solaris only)
 *
 *           EDEADLK       If deadlock protection detected a possible
 *                         deadlock if read(2) went to sleep.
 *                         (Solaris only)
 *
 *           EINTR         If read(2) or readv(2) was interrupted by a
 *                         signal.
 *                         (Solaris only)
 *
 *           EINVAL        If a stream linked to a multiplexor was attempted
 *                         to be read.
 *                         (Solaris only)
 *
 *           EIO           If a physical I/O problem occurred.
 *                         (Solaris only)
 *
 *           ENOLCK        If read(2) or readv(2) were prevented from
 *                         sleeping because the system record lock table
 *                         was full keeping the blocking record lock from
 *                         being removed.
 *                         (Solaris only)
 *
 *           ENOLINK       If the directory is on a remote machine and the
 *                         machine is no longer available.
 *                         (Solaris only)
 *
 *           ENXIO         If the directory is on a block special or
 *                         character special file with the file pointer
 *                         out of range.
 *                         (Solaris only)
 *
 *           EBADHANDLE    The JDIRENT argument is invalid.
 *
 *           EBADID        IDIRID is invalid.
 */

#ifdef _UNICOS
void
PXFREADDIR(
#else
void
_PXFREADDIR(
#endif
	    _f_int *IDIRID,
	    _f_int *JDIRENT,
	    _f_int *IERROR
)
{
#if defined(_MIPSEB)
  struct dirent64 *direntptr, *newdirentptr;
#else
  struct dirent *direntptr, *newdirentptr;
#endif
  int errno_save;
  DIR *dirp;
  int cdirent, cdirid;
  
  /* set errno to invalid error number so end of directory can be checked since
   * readdir returns NULL but does not set errno when the end of a directory
   * is reached. */
  errno_save = errno;
  errno = -1;
  
  cdirid = *IDIRID;
  if (cdirid < 0) {
    cdirid = -cdirid;
  }

  /* fetch the real DIR pointer from the pxfdir_table */
  dirp = _table_lookup(&_pxfdir_table, cdirid);
  if (dirp == NULL) {
    *IERROR = EBADID;
    return;
  }
  
#if defined(_MIPSEB)
  if ((direntptr = readdir64(dirp)) == NULL) {
#else
  if ((direntptr = readdir(dirp)) == NULL) {
#endif
    if (errno == -1) {
      /* end of directory entries */
      *IERROR = EEND;
    } else {
      *IERROR = errno;
    }
    errno = errno_save;
    return;
  }

  errno = errno_save;

  /* Since the size of the dirent structure returned from readdir varies in
   * size the old dirent struct needs to be free'd and a new struct of size
   * direntptr->d_reclen malloc'd.
   */

#if defined(_MIPSEB)
  newdirentptr = (struct dirent64 *)malloc(direntptr->d_reclen);
#else
  newdirentptr = (struct dirent *)malloc(direntptr->d_reclen);
#endif
  if (newdirentptr == NULL) {
    *IERROR = ENOMEM;
    return;
  }

  (void)memcpy(newdirentptr, direntptr, direntptr->d_reclen);

  /* Determine if a new entry in the pxfhandle table is needed.
   * If IDIRID is negative, then pxfreaddir has not been called
   * and a new pxfhandle table entry is needed.
   */
  if (*IDIRID < 0) {
    cdirent = _pxfhandle_table_add(&_pxfhandle_table,
				   newdirentptr,
				   PXF_DIRENT);
    if (cdirent < 0) {
      *IERROR = ENOMEM;
      return;
    } else {
      *JDIRENT = cdirent;
      *IDIRID = cdirid;
    }
  } else if (!_pxfhandle_table_replace(&_pxfhandle_table,
				       *JDIRENT,
				       newdirentptr,
				       PXF_DIRENT)) {
    *IERROR = EBADHANDLE;
    return;
  }
  
  *IERROR = 0;
}
  
#ifndef _UNICOS
void
pxfreaddir_(
	    _f_int *IDIRID,
	    _f_int *JDIRENT,
	    _f_int *IERROR
)
{
  _PXFREADDIR(IDIRID, JDIRENT, IERROR);
}
#endif
