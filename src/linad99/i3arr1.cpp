/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifndef OPT_LIB

/// Returns reference to integer element at i3_array(i, j, k).
int& i3_array::operator()(int i, int j, int k)
{
  return elem(i)(j, k);
}
/// Returns reference to vector element at i3_array(i, j).
ivector& i3_array::operator()(int i, int j)
{
  return elem(i)(j);
}
/// Returns reference to matrix element at i3_array[i].
imatrix& i3_array::operator[](int i)
{
  return elem(i);
}
/// Returns reference to matrix element at i3_array(i).
imatrix& i3_array::operator()(int i)
{
  return elem(i);
}
#endif
