/*
 * $Id: fvar_m13.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

/**
 * Description not yet available.
 * \param
 */
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
