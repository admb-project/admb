/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <fvar.hpp>

/**
Return the total sum of the elements in values.
\param values dvector
*/
double sum(const dvector& values)
{
  double total = 0.0;
  int min = values.indexmin();
  int max = values.indexmax();
  double* pvi = values.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    total += *pvi;

    ++pvi;
  }
  return total;
}
/**
Returns dvector where each element contains the sum total of each column 
in matrix.

\param matrix dmatrix
*/
dvector colsum(const dmatrix& matrix)
{
  int cmin = matrix.colmin();
  int cmax = matrix.colmax();
  int rmin = matrix.rowmin();
  int rmax = matrix.rowmax();

  dvector sums(cmin, cmax);
  sums.initialize();
  for (int j=cmin; j<=cmax; ++j)
  {
    for (int i=rmin; i<=rmax; ++i)
    {
      sums(j) += matrix(i, j);
    }
  }
  return sums;
}
/**
Returns dvector where each element contains the sum total of each row
in matrix.

\param matrix dmatrix
*/
dvector rowsum(const dmatrix& matrix)
{
  int min = matrix.rowmin();
  int max = matrix.rowmax();

  dvector sums(min, max);
  for (int i = min; i <= max; ++i)
  {
    sums(i) = sum(matrix(i));
  }
  return sums;
}
/**
Return total sum of all elements in matrix.

\param matrix dmatrix
*/
double sum(const dmatrix& matrix)
{
  double total = 0.0;
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  const dvector* pmi = &matrix(min);
  for (int i = min; i <= max; ++i)
  {
    total += sum(*pmi);

    ++pmi;
  }
  return total;
}
