/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

dvar6_array::dvar6_array() 
{
  allocate();
}

void dvar6_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}


