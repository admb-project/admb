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

//#define HOME_VERSION
#include "fvar.hpp"
#include <d4arr.hpp>

dvar4_array::dvar4_array() 
{
  allocate();
}

void dvar4_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}
#undef HOME_VERSION

