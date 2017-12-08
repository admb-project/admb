/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return the sum of the diagonal of a square matrix mat.

\param mat is a square scalar matrix
*/
double trace(const dmatrix& mat)
{
  if (mat.colmin() != mat.rowmin() || mat.colmax() != mat.rowmax() )
  {
    cerr << "Matrix not square in trace\n";
    ad_exit(1);
  }

  double sum = 0.0;
  for (int i = mat.colmin(); i <= mat.colmax(); ++i)
  {
    sum += mat.elem(i, i);
  }
  return sum;
}
