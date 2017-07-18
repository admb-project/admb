/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return vector containing diagonal of a matrix.

\param matrix dmatrix
*/
dvector diagonal(const dmatrix& matrix)
{
  if (matrix.indexmin() != matrix.colmin()
      || matrix.indexmax() != matrix.colmax())
  {
    cerr << "Error: matrix should be square"
         << "in diagonal(const dmatrix&)";
    ad_exit(1);
  }
  int min = matrix.indexmin();
  int max = matrix.indexmax();
  dvector vector(min, max);
  for (int i = min;i <= max; ++i)
  {
    vector(i) = matrix(i, i);
  }
  return vector;
}
