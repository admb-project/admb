/*
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include "fvar.hpp"

/**
Returns dvector containing the differences of an values(i) and values(i + 1)
for i = 1 to values.indexmax() - 1.

\param values dvector
*/
dvector first_difference(const dvector& values)
{
  if (values.size() <= 1)
  {
    cerr << "Error -- vector size should be greater than 1"
         << " in first_difference(const dvector&)" << endl;
    ad_exit(1);
  }
  int indexmin = values.indexmin();
  int indexmax = values.indexmax() - 1;
  dvector differences(indexmin, indexmax);
  for (int i = indexmin; i <= indexmax; ++i)
  {
    differences.elem(i) = values.elem(i + 1) - values.elem(i);
  }
  return differences;
 }
