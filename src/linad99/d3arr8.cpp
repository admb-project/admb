/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifndef OPT_LIB

/**
Return reference to the element at d3_array(i, j, k).

\param i index
\param j index
\param k index
*/
const double& d3_array::operator()(int i, int j, int k) const
{
  if (i < slicemin())
  {
    cerr << "array bound exceeded -- slice index too low in "
         << "d3_array::operator(int, int, int)";
          ad_exit(1);
  }
  if (i > slicemax())
  {
    cerr << "array bound exceeded -- slice index too high in "
         << "d3_array::operator(int, int, int)";
    ad_exit(1);
  }
  return elem(i)(j,k);
}
/**
Return reference to the dvector element at d3_array(i, j).

\param i index
\param j index
*/
const dvector& d3_array::operator()(int i, int j) const
{
  if (i < slicemin())
  {
    cerr << "array bound exceeded -- slice index too low in "
         << "d3_array::operator(int, int)";
    ad_exit(1);
  }
  if (i > slicemax())
  {
    cerr << "array bound exceeded -- slice index too high in "
         << "d3_array::operator(int, int)";
    ad_exit(1);
  }
  return elem(i)(j);
}
/**
Return reference to the dmatrix element at d3_array(i).

\param i index
*/
const dmatrix& d3_array::operator[](int i) const
{
  if (i < slicemin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
         << "d3_array::operator[]" << "value was" << i;
    ad_exit(1);
  }
  if (i > slicemax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
         << "d3_array::operator[]" << "value was" << i;
    ad_exit(1);
  }
  return t[i];
}
#endif

/**
Assign element values to d3_array.

\param values d3_array
*/
d3_array& d3_array::operator=(const d3_array& values)
{
  if (slicemin() != values.slicemin() || slicemax() != values.slicemax())
  {
    cerr << " Incompatible array bounds in "
         << "d3_array& operator=(const d3_array&)\n";
    ad_exit(1);
  }

  // check for condition that both matrices
  // don't point to the same object
  if (t != values.t)
  {
     for (int i = slicemin(); i <= slicemax(); ++i)
     {
       elem(i) = values.elem(i);
     }
  }
  return *this;
}
/**
Assign elements of d3_array to value.

\param value double
*/
d3_array& d3_array::operator=(double value)
{
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i) = value;
  }
  return *this;
}
