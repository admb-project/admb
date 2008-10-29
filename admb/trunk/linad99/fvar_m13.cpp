
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif


  dmatrix value(_CONST dvar_matrix& m)
  {
    int nrl=m.rowmin();
    int nrh=m.rowmax();
    ivector ncl(nrl,nrh);
    ivector nch(nrl,nrh);
    int i;
    for (i=nrl;i<=nrh;i++)
    {
      ncl(i)=m(i).indexmin();
      nch(i)=m(i).indexmax();
    }
    dmatrix tmp(nrl,nrh,ncl,nch);
    for (i=nrl;i<=nrh;i++)
    {
      tmp(i)=value(m(i));
    }
    return tmp;
  }

#undef HOME_VERSION
