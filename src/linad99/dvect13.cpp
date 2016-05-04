/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include <fvar.hpp>

/**
Returns dmatrix with a single column using values from v.
*/
dmatrix column_vector(const dvector& v)
{
  int min = v.indexmin();
  int max = v.indexmax();
  dmatrix ret(min, max, 1, 1);
  for (int i = min; i <= max; ++i)
  {
    ret.elem(i, 1) = v.elem(i);
  }
  return ret;
}
/**
Returns dvar_matrix with a single row using values from v.
*/
dmatrix row_vector(const dvector& v)
{
  int min = v.indexmin();
  int max = v.indexmax();
  dmatrix ret(1, 1, min, max);
  for (int i = min; i <= max; ++i)
  {
    ret.elem(1, i) = v.elem(i);
  }
  return ret;
}
/**
Returns dmatrix with a single column using values from v.
*/
dvar_matrix column_vector(const dvar_vector& v)
{
  int min = v.indexmin();
  int max = v.indexmax();
  dvar_matrix ret(min, max, 1, 1);
  for (int i = min; i <= max; ++i)
  {
    ret.elem(i, 1) = v.elem(i);
  }
  return ret;
}
/**
Returns dvar_matrix with a single row using values from v.
*/
dvar_matrix row_vector(const dvar_vector& v)
{
  int min = v.indexmin();
  int max = v.indexmax();
  dvar_matrix ret(1, 1, min, max);
  for (int i = min; i <= max; ++i)
  {
    ret.elem(1, i) = v.elem(i);
  }
  return ret;
}
