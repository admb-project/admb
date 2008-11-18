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

void dmatrix::allocate(void)  //default constructor
{
  index_min=1;
  index_max=0;
  m=NULL;
  shape=NULL;
} 

dmatrix::dmatrix()  //default constructor 
{
  allocate();
} 
#undef HOME_VERSION
