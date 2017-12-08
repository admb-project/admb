/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>

/**
Returns symmetric matrix by averaging the elements upper and lower triangles
in matrix.  So, results(i, j) and results(j, i) are equal to (matrix(i, j) + matrix(j, i)) / 2.
Note: Requires that matrix is square.

\param m dmatrix
*/
dmatrix symmetrize(const dmatrix& matrix)
{
  if (matrix.rowmin() != matrix.colmin() || matrix.rowmax() != matrix.colmax())
  {
    cerr << "Error: Parameter is non square matrix in "
         << "symmetrize(dmatrix&)\n";
    ad_exit(1);
  }
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  dmatrix results(min, max, min, max);
  for (int i = min; i <= max; ++i)
  {
    results(i, i) = matrix(i, i);
    for (int j = min; j < i; ++j)
    {
      results(i,j) = (matrix(i, j) + matrix(j, i)) * 0.5;
      results(j,i) = results(i,j);
    }
  }
  return results;
}
