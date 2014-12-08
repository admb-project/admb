// $Id$
/** \file gdbprintlib.h
  Function prototypes for printing ADMB objects during GDB sessions.

* @author Chris Grandin, Dave Fournier
* @date 6/18/2013
**/

#ifndef _GDBPRINT_H_
#define _GDBPRINT_H_

#include <fvar.hpp>
#include <admodel.h>
#include <df1b2fun.h>

void pad();

void pad(double v);

void pad(const adstring & v);

void pad(const dvar3_array & v);
void pad(const dvar3_array & v,int i);
void pad(const dvar3_array & v,int i,int j);
void pad(const dvar3_array & v,int i,int j,int k);

void pad(const dvar4_array & v);
void pad(const dvar4_array & v,int i);
void pad(const dvar4_array & v,int i,int j);
void pad(const dvar4_array & v,int i,int j,int k);

void pad(const d4_array & v);
void pad(const d4_array & v,int i);
void pad(const d4_array & v,int i,int j);
void pad(const d4_array & v,int i,int j,int k);

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

void pad(const dvar_vector & v);
void pad(const dvar_vector & v,int i);

void pad(const prevariable & v);
void pad(const dvector & v);
void pad(const ivector & v);

void pad(const dvar_matrix & v);
void pad(const dvar_matrix & v,int i);
void pad(const dvar_matrix & v,int i,int j);

void pad(const dmatrix & v);

void pad(const dfsdmat & v);

void pad(const imatrix & v);
void pad(const imatrix & v,int i);
void pad(const imatrix & v,int i,int j);

void pads(const dvar_vector & v);
void pads(const dvar_vector & v,int i);

void padp(const dmatrix & v,int i);
void padp(const dvar_matrix & v,int i);

void padsum(const dvar_vector & v);
void padsum(const dvector & v);
void padsum(const ivector & v);
void padsum(const dvar_matrix & v);
void padsum(const dmatrix & v);
void padsum(const imatrix & v);

#endif
