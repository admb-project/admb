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

void d3_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}

d3_array::d3_array(void)
{
  allocate();
}
#undef HOME_VERSION

