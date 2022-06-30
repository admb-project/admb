/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Assignment function dvar3_array::operator=(const dvar3_array&)
*/
#include "fvar.hpp"

/**
Assign values from other to dvar3_array.

\param other dvar3_array
*/
dvar3_array& dvar3_array::operator=(const dvar3_array& other)
{
  if (t != other.t)
  {
    int min = slicemin();
    int max = slicemax();
#ifndef OPT_LIB
    if (min != other.slicemin() || max != other.slicemax())
    {
      cerr << "Incompatible array bounds in "
           << "dvar_matrix& dvar3_array::operator=(const dvar3_vector&).\n";
      ad_exit(1);
    }
#endif
    // check for condition that both matricesdon't point to the same object
    dvar_matrix* pti = t + min;
    const dvar_matrix* potheri = &other(min);
    for (int i = min; i <= max; ++i)
    {
      *pti = *potheri;
      ++pti;
      ++potheri;
    }
  }
  return *this;
}
