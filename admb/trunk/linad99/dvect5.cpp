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
  void dvector::initialize(void)
  {
    if (!(!(*this)))  // only initialize allocated objects
    {
      for (int i=indexmin();i<=indexmax();i++)
      {
        elem(i)=0.0;
      }
    }
  }
#undef HOME_VERSION
