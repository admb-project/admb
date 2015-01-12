/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
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


#if defined(USE_ADPVM)

#if !defined(__ADPVM2__)
#  define __ADPVM2__

#include <admodel.h>

#if defined(__cplusplus)  
//  extern "C" {
#  endif
#if defined(__BORLANDC__) 
#  if !defined(__linux__)
#   include <pvm3bor.h>
#   include <pvm3.h>
#  endif
#else
#  include <pvm3.h>
#endif
#if defined(__cplusplus)  
//}
#endif

#if defined(WIN32)  && !defined(__linux__)
#  include <windows.h>
#endif


int adpvm_initsend( int mode);
int adpvm_recv( int id,int n );
void adpvm_pack_number_derivative(void);
void adpvm_send_derivatives(void);
void adpvm_receive_derivatives(void);
void adpvm_send(int id,int n);
void adpvm_unpack_vector_derivatives(void);
void initialize_pvm_buffer(void);
void  adpvm_end_receive(void);
void  pvm_end_receive(void);
void adpvm_unpack_number_derivative(void);
void adpvm_pack_vector_derivatives(void);

void pvm_pack(const prevariable& _v);
void pvm_pack(const dvar_vector& _v);
void pvm_pack(const dvar_matrix & _m);
void pvm_pack(const dvar3_array & _m);
void pvm_pack(const dvar4_array & _m);
void pvm_pack(const dvar5_array & _m);

void pvm_unpack(const int& _v);
void pvm_unpack(const prevariable& _v);
void pvm_unpack(const dvar_vector& _v);
void pvm_unpack(const dvar_matrix & _m);
void pvm_unpack(const dvar3_array & _m);
void pvm_unpack(const dvar4_array & _m);
void pvm_unpack(const dvar5_array & _m);

void pvm_pack(double v);
void pvm_pack(const dvector& _v);
void pvm_pack(const dmatrix & _m);
void pvm_pack(const d3_array & _m);
void pvm_pack(const d4_array & _m);
void pvm_pack(const d5_array & _m);

void pvm_unpack(const double& _v);
void pvm_unpack(const dvector& _v);
void pvm_unpack(const dmatrix & _m);
void pvm_unpack(const d3_array & _m);
void pvm_unpack(const d4_array & _m);
void pvm_unpack(const d5_array & _m);
    
void pvm_pack(int v);
void pvm_pack(const ivector& _v);
void pvm_pack(const imatrix & _m);
void pvm_pack(const i3_array & _m);
//void pvm_pack(const i4_array & _m);
//void pvm_pack(const i5_array & _m);

void pvm_unpack(const int& _v);
void pvm_unpack(const ivector& _v);
void pvm_unpack(const imatrix & _m);
void pvm_unpack(const i3_array & _m);
//void pvm_unpack(const i4_array & _m);
//void pvm_unpack(const i5_array & _m);
    
void adpvm_pack(const prevariable& _v);
void adpvm_pack(const dvar_vector& _v);
void adpvm_pack(const dvar_matrix & _m);
void adpvm_pack(const dvar3_array & _m);
void adpvm_pack(const dvar4_array & _m);
void adpvm_pack(const dvar5_array & _m);

void adpvm_unpack(const int& _v);
void adpvm_unpack(const prevariable& _v);
void adpvm_unpack(const dvar_vector& _v);
void adpvm_unpack(const dvar_matrix & _m);
void adpvm_unpack(const dvar3_array & _m);
void adpvm_unpack(const dvar4_array & _m);
void adpvm_unpack(const dvar5_array & _m);

void adpvm_pack(double v);
void adpvm_pack(const dvector& _v);
void adpvm_pack(const dmatrix & _m);
void adpvm_pack(const d3_array & _m);
void adpvm_pack(const d4_array & _m);
void adpvm_pack(const d5_array & _m);

void adpvm_unpack(const double& _v);
void adpvm_unpack(const dvector& _v);
void adpvm_unpack(const dmatrix & _m);
void adpvm_unpack(const d3_array & _m);
void adpvm_unpack(const d4_array & _m);
void adpvm_unpack(const d5_array & _m);
    
void adpvm_pack(int v);
void adpvm_pack(const ivector& _v);
void adpvm_pack(const imatrix & _m);
void adpvm_pack(const i3_array & _m);
//void adpvm_pack(const i4_array & _m);
//void adpvm_pack(const i5_array & _m);

void adpvm_unpack(const int& _v);
void adpvm_unpack(const ivector& _v);
void adpvm_unpack(const imatrix & _m);
void adpvm_unpack(const i3_array & _m);
#if defined(linux)
#  define __declspec(dllexport) 
#endif

int load_adpvm_library(void);


int adpvm_slave_vinitsend(int mode);
  
int adpvm_slave_cinitsend(int mode);
  
void adpvm_slave_vsend(int ptid);

void adpvm_slave_csend(int ptid);

int adpvm_slave_vrecv(int ptid);

int adpvm_slave_crecv(int ptid);

int adpvm_master_vinitsend(int mode);

int adpvm_master_cinitsend(int mode);

void adpvm_master_csend(int id);

void adpvm_master_vsend(int id);

int adpvm_master_vrecv(int id);

int adpvm_master_crecv(int id) ;

void  adpvm_master_end_vreceive(void);

void  adpvm_slave_end_vreceive(void);

void  adpvm_master_end_creceive(void);

void  adpvm_slave_end_creceive(void);

void adpvm_unpack(char * v,int n);

void adpvm_pack(char * v,int n);

#endif
#endif  // #if defined(USE_ADPVM)
