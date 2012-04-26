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
#ifndef __SPCOMM__
#define __SPCOMM__
#include <windows.h>
#include <windows.h>
#if defined (__BORLANDC__)
#  include <winnt.h>
#endif
#include <ddeml.h>
#include <admodel.h>

void printconnectstatus(int status);
void printInitializestatus(int status);



class DDEspclient
{
  static DWORD idInst;
  static DWORD sleeptime; 
  static HCONV cstatus;
  static UINT status;
public:
  DDEspclient(DWORD sleeptime=1000); 
  static HCONV get_cstatus(void){return cstatus;}
  static DWORD get_idInst(void){return idInst;}
  static DWORD get_sleeptime(void){return sleeptime;}

};

void SPreceive(BOR_CONST data_number& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST data_number& x);

void SPreceive(BOR_CONST dvariable& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST double& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST named_dvariable& x);

void SPreceive(BOR_CONST dvector& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST named_dvector& x);

void SPreceive(BOR_CONST named_dvar_matrix& x);

void SPreceive(BOR_CONST dvar_vector& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST named_dvar_vector& x);

void SPreceive(BOR_CONST named_dmatrix& x);

void SPreceive_double(BOR_CONST double& x,BOR_CONST adstring& name);

void SPreceive_double(BOR_CONST dmatrix& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST dmatrix& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST double& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST dvector& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST named_dvector& x);

void SPsend(BOR_CONST named_dvariable& x);

void SPsend(BOR_CONST named_dvar_vector& x);

void SPsend(BOR_CONST named_dvar_matrix& x);

void SPsend(BOR_CONST named_dmatrix& x);

void SPexecute( LPBYTE  cbuff,HCONV cstatus);


void SPsend_char(char * pch,HCONV cstatus);



/*
class DDEspclient
{
  static DWORD idInst;
  static DWORD sleeptime; 
  static HCONV cstatus;
  static UINT status;
public:
  DDEspclient(DWORD sleeptime=1000); 
  static HCONV get_cstatus(void){return cstatus;}
  static DWORD get_idInst(void){return idInst;}
  static DWORD get_sleeptime(void){return sleeptime;}

};

HDDEDATA SPreceive(BOR_CONST dvector& x,BOR_CONST adstring& name);

HDDEDATA SPreceive(BOR_CONST named_dvector& x);

HDDEDATA SPreceive(BOR_CONST named_dvar_matrix& x);

HDDEDATA SPreceive(BOR_CONST named_dmatrix& x);

HDDEDATA SPreceive_double(BOR_CONST double& x,BOR_CONST adstring& name);


HDDEDATA SPsend(BOR_CONST dvector& x,BOR_CONST adstring& name);

HDDEDATA SPsend(BOR_CONST named_dvector& x);

HDDEDATA SPsend(BOR_CONST named_dvar_matrix& x);

HDDEDATA SPsend(BOR_CONST named_dmatrix& x);

HDDEDATA SPexecute( LPBYTE  cbuff,HCONV cstatus);


HDDEDATA SPsend_char(char * pch,HCONV cstatus);
*/

#endif
