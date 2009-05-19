/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
#include <d4arr.hpp>

d4_array::d4_array() 
{
  allocate();
}

void d4_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}

