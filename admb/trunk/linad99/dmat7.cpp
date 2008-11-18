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

void dmatrix::initialize(void)
{
  if (!(!(*this)))  // only initialize allocated objects
  {
    for (int i=rowmin();i<=rowmax();i++)
    {
      elem(i).initialize();
    }
  }
} 


#undef HOME_VERSION
