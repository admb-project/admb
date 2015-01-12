/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
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

