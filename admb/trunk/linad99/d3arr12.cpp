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
#include "fvar.hpp"


dmatrix operator * (const d3_array & t,const dvector& v)
{
  int mmin=t.indexmin();
  int mmax=t.indexmax();
  dmatrix tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=t(i)*v;
  }
  return tmp;
}

#undef HOME_VERSION

