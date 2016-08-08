/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Return computed mean of matrix m.
*/
double mean(const dmatrix& m)
{
  double ret = sum(m) / size_count(m);
  return ret;
}
