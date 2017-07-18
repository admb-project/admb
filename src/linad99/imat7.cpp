/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
#include "admb_messages.h"

/**
Return total sum of the values in matrix.

\param matrix imatrix
*/
int sum(const imatrix& matrix)
{
  int total = 0;
  for (int i = matrix.rowmin(); i <= matrix.rowmax(); ++i)
  {
    total += sum(matrix(i));
  }
  return total;
}
/**
Return sum of matrix at specified column index.

\param matrix imatrix
\param column index
*/
int colsum(const imatrix& matrix, int column)
{
  if (column < matrix.colmin() || column > matrix.colmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Specified column is out of bounds",
    "in colsum(const imatrix&,int column)",
    matrix.colmin(), matrix.colmax(), column);
  }
  int sum = 0;
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  for (int i = min; i <= max; ++i)
  {
    sum += matrix(i, column);
  }
  return sum;
}
/**
Return copy of column vector from matrix at specified column index.

/param matrix imatrix
/param column index
*/
ivector column(const imatrix& matrix, int column)
{
  if (column < matrix.colmin() || column > matrix.colmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Specified column is out of bounds",
    "in column(const imatrix&, int column)",
    matrix.colmin(), matrix.colmax(), column);
  }
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  ivector vector(min, max);
  for (int i = min; i <= max; ++i)
  {
    vector(i) = matrix(i, column);
  }
  return vector;
}
