/**
 * \file
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Does NOT allocate, but initializes empty d3_array.
*/
void d3_array::allocate()
{
  shape = NULL;
  t = NULL;
}

/**
Default constructor
*/
d3_array::d3_array()
{
  allocate();
}
