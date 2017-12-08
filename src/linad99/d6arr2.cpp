/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

/// Default constructor
d6_array::d6_array()
{
  allocate();
}
/// Does NOT allocate, but initializes d6_array members.
void d6_array::allocate()
{
  shape = NULL;
  t = NULL;
}
