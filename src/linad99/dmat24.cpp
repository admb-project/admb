/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Return computed mean of matrix m.

\param m dmatrix
*/
double mean(const dmatrix& m)
{
  unsigned int size = size_count(m);
  if (size == 0)
  {
    cerr << "Error: Unable to compute mean of empty dmatrix.\n";
    ad_exit(1);
  }
  return sum(m) / size;
}
