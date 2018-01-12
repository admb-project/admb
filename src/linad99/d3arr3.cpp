/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Return computed mean of d3_array array.
*/
double mean(const d3_array& array)
{
  unsigned int size = size_count(array);
  if (size == 0)
  {
    cerr << "Error: Unable to compute mean of empty d3_array.\n";
    ad_exit(1);
  }
  return sum(array) / size;
}
