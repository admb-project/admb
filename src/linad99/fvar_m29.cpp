/**
\file
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Return the variable mean of matrix m.
*/
dvariable mean(const dvar_matrix& m)
{
  dvariable tmp;
  const unsigned int size = size_count(m);
  if (size > 0)
  {
    tmp = sum(m) / size;
  }
  else
  {
    cerr << "Error: Unable to compute mean of dvar_matrix.\n";
    ad_exit(1);
  }
  return tmp;
}
