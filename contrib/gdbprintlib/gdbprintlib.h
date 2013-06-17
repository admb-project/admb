#ifndef _GDBPRINT_H_
#define _GDBPRINT_H_

#include <fvar.hpp>
#include <admodel.h>
#include <df1b2fun.h>

void pad(const adstring & v);
void pad(const dvar3_array & v);
void pad(const dvar3_array & v,int i);
void pad(const dvar3_array & v,int i,int j);
void pad(const dvar4_array & v);
void pad(const dvar4_array & v,int i);
void pad(const dvar4_array & v,int i,int j);
void pad(const dvar4_array & v,int i,int j,int k);
void pad(const d4_array & v,int i,int j,int k);
void pad(const d4_array & v);
void pad(const d4_array & v,int i);
void pad(const d4_array & v,int i,int j);
void pad(const dvar3_array & v,int i,int j,int k);
void pad(const d3_array & v);
void pad(const d3_array & v,int i);
void pad(const d3_array & v,int i,int j);
void pad(const d3_array & v,int i,int j,int k);
void pad(const i3_array & v);
void pad(const i3_array & v,int i);
void pad(const i3_array & v,int i,int j);
void pad(const i3_array & v,int i,int j,int k);
void pad(const i4_array & v);
void pad(const i4_array & v,int i);
void pad(const i4_array & v,int i,int j);
void pad(const i4_array & v,int i,int j,int k);
void pad(const i4_array & v,int i,int j,int k,int l);
void pad(const dvar_vector & v,const char * s);
void pad(const dvar_vector & v,int i);
//void pad(const dvar_vector & v,int i,int j);
//void pad(const dvector & v,int i,int j);
void pads(const dvar_vector & v,int i);
void pads(const dvar_vector & v);
void pad(const dvar_vector & v);
void pad(double v);
void pad(const prevariable & v);
void pad(const dvector & v);
void pad(const ivector & v);
void padp(const dmatrix & v,int i);
void padp(const dvar_matrix & v,int i);
void pad(const dvar_matrix & v,int i);
void pad(const dvar_matrix & v,int i,int j);
void pad(const dvar_matrix & v);
void pad(const dmatrix & v);
void pad(const imatrix & v);
void pad(const imatrix & v,int i);
void pad(const imatrix & v,int i,int j);
void sumprint(const dvar_vector & v);
void sumprint(const dvector & v);
void sumprint(const ivector & v);
void sumprint(const dvar_matrix & v,int i);
void sumprint(const dvar_matrix & v,int i,int j);
void sumprint(const dvar_matrix & v);
void sumprint(const dmatrix & v);
void sumprint(const imatrix & v);

/**
* @file gdbPrint.h
* @brief Library of statistic functions
* \ingroup STATLIB
* This library contains declarations for
* print functions that can be used during a
* gdb debugging session.
* 
* @author Chris Grandin, Dave Fournier
* 
* @date 05/06/2013
*/

#endif
