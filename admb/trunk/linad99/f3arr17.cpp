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

 dvar3_array::dvar3_array(void)
 {
   allocate();
 }

 void dvar3_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }

#undef HOME_VERSION

