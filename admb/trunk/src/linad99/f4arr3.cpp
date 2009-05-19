/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

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

