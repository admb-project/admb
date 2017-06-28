/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
#include "admb_messages.h"

#ifndef OPT_LIB
/**
Return the value from d3_array indexed at i, j and k.

\param i int
\param j int
\param k int
*/
double& d3_array::operator()(int i, int j, int k)
{
  if (i < slicemin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
      "dmatrix& d3_array::operator() (int i, int j, int k)",
      slicemin(), slicemax(), i);
  }
  if (i > slicemax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
      "dmatrix& d3_array::operator() (int i, int j, int k)",
      slicemin(), slicemax(), i);
  }
  return (elem(i))(j, k);
}
/**
Return a vector from d3_array indexed at i and j.

\param i int
\param j int
\param k int
*/
dvector& d3_array::operator()(int i, int j)
{
  if (i < slicemin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
      "dmatrix& d3_array::operator()(int i, int j)",
      slicemin(), slicemax(), i);
  }
  if (i > slicemax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
      "dmatrix& d3_array::operator()(int i, int j)",
      slicemin(), slicemax(), i);
  }
  return (elem(i))(j);
}
/**
Return a matrix from d3_array indexed at i.

\param i int
*/
dmatrix& d3_array::operator[](int i)
{
  if (i < slicemin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
      "dmatrix& d3_array::operator[] (int i)", indexmin(), indexmax(), i);
  }
  if (i > slicemax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
      "dmatrix& d3_array::operator[] (int i)", indexmin(), indexmax(), i);
  }
  return t[i];
}
/**
Return a matrix from d3_array indexed at i.

\param i int
*/
dmatrix& d3_array::operator()(int i)
{
  if (i < slicemin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
      "dmatrix& d3_array::operator()(int i)", indexmin(), indexmax(), i);
  }
  if (i > slicemax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
      "dmatrix& d3_array::operator()(int i)", indexmin(), indexmax(), i);
  }
   return t[i];
}
#endif
