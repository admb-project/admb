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
#include <fvar.hpp>

  double norm(_CONST dvector& t1)
  {
    double tmp;
    tmp=t1*t1;
    if (tmp>0)
    {
      tmp=pow(tmp,.5);
    }
    return(tmp);
  }

  double norm2(_CONST dvector& t1)
  {
    double tmp;
    tmp=t1*t1;
    return(tmp);
  }

#undef HOME_VERSION
