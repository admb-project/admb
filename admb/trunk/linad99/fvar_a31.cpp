/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
#include <fvar.hpp>

  dvar_vector colsum(_CONST dvar_matrix&v)
  {
    int cmin=v.colmin();
    int cmax=v.colmax();
    int rmin=v.rowmin();
    int rmax=v.rowmax();

    dvar_vector tmp(cmin,cmax);
    tmp.initialize();
    for (int j=cmin; j<=cmax; j++)
    {
      for (int i=rmin; i<=rmax; i++)
      {
        tmp(j)+=v(i,j);
      }
    }
    return tmp;
  }

  dvar_vector rowsum(_CONST dvar_matrix&v)
  {
    int cmin=v.colmin();
    int cmax=v.colmax();
    int rmin=v.rowmin();
    int rmax=v.rowmax();

    dvar_vector tmp(rmin,rmax);
    for (int i=rmin; i<=rmax; i++)
    {
      tmp(i)=sum(v(i));
    }
    return tmp;
  }

#undef HOME_VERSION

