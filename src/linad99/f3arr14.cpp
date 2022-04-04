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
  if (slicemin() != other.slicemin() || slicemax() != other.slicemax())
  {
    cerr << "Incompatible array bounds in "
         << "dvar_matrix& dvar3_array::operator=(const dvar_vector&).\n";
    ad_exit(1);
  }
  // check for condition that both matricesdon't point to the same object
  if (t != other.t)
  {
    for (int i = slicemin(); i <= slicemax(); ++i)
    {
      elem(i) = other.elem(i);
    }
  }
  return *this;
}
