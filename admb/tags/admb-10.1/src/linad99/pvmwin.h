/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 *
 * License:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * \file
 * Description not yet available.
 */
/*
 *         PVM version 3.4:  Parallel Virtual Machine System
 *               University of Tennessee, Knoxville TN.
 *           Oak Ridge National Laboratory, Oak Ridge TN.
 *                   Emory University, Atlanta GA.
 *      Authors:  J. J. Dongarra, G. E. Fagg, M. Fischer, 
 *          G. A. Geist, J. A. Kohl, R. J. Manchek, P. Mucci,
 *         P. M. Papadopoulos, S. L. Scott, and V. S. Sunderam
 *                   (C) 1997 All Rights Reserved
 *
 *                              NOTICE
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted
 * provided that the above copyright notice appear in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * Neither the Institutions (Emory University, Oak Ridge National
 * Laboratory, and University of Tennessee) nor the Authors make any
 * representations about the suitability of this software for any
 * purpose.  This software is provided ``as is'' without express or
 * implied warranty.
 *
 * PVM version 3 was funded in part by the U.S. Department of Energy,
 * the National Science Foundation and the State of Tennessee.
 */

/* cruft file for different compiler specifications 
*  like Watcom, Visual, Borland ... 
*
*  added __fortran stub    06/21/1997 	Fischer
*/


#ifdef WIN32
#define __fortran __stdcall
#endif

#define STRICT

#include <sys/timeb.h>
#include <time.h>
#include <process.h>
#include <winsock.h>

#include <windows.h>

/*	WIN32 gets stdarg.h via pvm3.h -> pvmwin.h -> windows.h
	nice coding trail - NOT...
	since WIN32 is not a __STDC__ environment - it needs varargs.h
	so, this will cleanup the incorrect include order for var args
	from windows.h first must remove va_start va_end to avoid compiler
	warnings...  Someone else must then include the varargs.h file
	or that will then cause error.
	uggghhhhh... this is ugly coding at its best
*/

#ifdef WIN32
#undef va_start
#undef va_end
#endif

#include <stdio.h>
#include <io.h>

#ifndef HASSTDLIB
#define HASSTDLIB
#endif

#ifndef SYSVBFUNC
#define SYSVBFUNC
#endif

#ifndef SYSVSTR
#define SYSVSTR
#endif

#ifndef HASERRORVARS
#define HASERRORVARS
#endif

#ifndef NOWAIT3
#define NOWAIT3
#endif

#ifndef NOGETDTBLSIZ
#define NOGETDTBLSIZ
#endif

#ifndef ARCHCLASS 
#define ARCHCLASS "WIN32"
#endif

#ifndef NOUNIXDOM
#define NOUNIXDOM
#endif

#ifndef NOTMPNAM
#define NOTMPNAM
#endif

#ifndef HASERRORVARS
#define HASERRORVARS
#endif
/* sys/param.h doesn't exist: */
#define MAXHOSTNAMELEN 64
#define MAXPATHLEN 64
	   
#ifndef TIME
#define TIME
struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};
#endif


/* to keep the compiler satisfied */
extern int gettimeofday(struct timeval *, struct timezone *);
extern char *MyGetUserName();
extern int kill(int,int, int);
 
extern HANDLE win32_open_file( char *);
extern HANDLE win32_create_file(char *s, int );
extern int win32_close_file(HANDLE);
extern int win32_write_file(HANDLE,char *,int);
extern int win32_read_file(HANDLE,char *, int);
extern int win32_write_socket (SOCKET, const char FAR *, int);
extern int win32_read_socket (SOCKET, char FAR *, int);

extern void Wait(HANDLE id, DWORD *prv);

