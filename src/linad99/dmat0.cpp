/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/// Does NOT allocate, but initializes dmatrix members.
void dmatrix::allocate()
{
  index_min = 1;
  index_max = 0;
  m = nullptr;
  shape = nullptr;
}
/// Default constructor
dmatrix::dmatrix()
{
  allocate();
}
