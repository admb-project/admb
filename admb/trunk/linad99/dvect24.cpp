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




#define HOME_VERSION
#include "fvar.hpp"

  ivector sgn(_CONST dvector& v)
  {
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    ivector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      if(v(i)>0.0) 
        tmp(i)=1;
      else
        tmp(i)=-1;
    }
    return tmp;
  }

#undef HOME_VERSION
