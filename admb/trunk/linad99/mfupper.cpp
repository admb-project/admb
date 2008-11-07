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



#include <fvar.hpp>

  dvariable mf_upper_bound(_CONST prevariable& x,double M,prevariable& fpen)
  {
    if (x<=M) 
    {
      return x;
    }
    else
    {
      fpen+=square(x-M);
      return M+(1.+2.*(x-M))/(1.+x-M);
    }
  }

