/*
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include <fvar.hpp>

/**
Returns integer vector colsums where each element
is the sum of the jth column in matrix.

\param matrix imatrix
*/
ivector colsum(const imatrix& matrix)
{
  int jmin = matrix.colmin();
  int jmax = matrix.colmax();
  ivector colsums(jmin, jmax);
  colsums.initialize();

  int imin = matrix.rowmin();
  int imax = matrix.rowmax();
  for (int j = jmin; j <= jmax; ++j)
  {
    for (int i = imin; i <= imax; ++i)
    {
      colsums(j) += matrix(i, j);
    }
  }
  return colsums;
}
/**
Returns integer vector rowsums where each element
is the sum of the ith row in matrix.

\param matrix imatrix
*/
ivector rowsum(const imatrix& matrix)
{
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  ivector rowsums(min, max);

  for (int i = min; i <= max; ++i)
  {
    rowsums(i) = sum(matrix(i));
  }

  return rowsums;
}
/**
Fill imatrix with sequence of integers from start and adding with increment.

\param start starting value
\param increment incremental value
*/
void imatrix::fill_seqadd(int start, int increment)
{
  int current = start;

  int imin = indexmin();
  int imax = indexmax();
  for (int i = imin; i <= imax; ++i)
  {
    if (allocated(elem(i)))
    {
      elem(i).fill_seqadd(current, increment);
      current = elem(i, elem(i).indexmax()) + increment;
    }
  }
}
