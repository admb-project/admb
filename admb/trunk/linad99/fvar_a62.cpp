/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#include <admodel.h>

dvar_vector posfun(const dvar_vector&x,double eps,const prevariable& _pen)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  dvar_vector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=posfun(x(i),eps,_pen);
  }
  return tmp;
}


