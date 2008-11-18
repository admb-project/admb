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


//#define HOME_VERSION
#include "fvar.hpp"

dvar5_array::dvar5_array() 
{
  allocate();
}

void dvar5_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }
#undef HOME_VERSION

