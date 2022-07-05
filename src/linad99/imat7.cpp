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
  int min = matrix.rowmin();
  int max = matrix.rowmax();

  int total = 0;
  const ivector* pmatrixi = &matrix(min);
  for (int i = min; i <= max; ++i)
  {
    total += sum(*pmatrixi);
    ++pmatrixi;
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
#ifndef OPT_LIB
  if (column < matrix.colmin() || column > matrix.colmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Specified column is out of bounds",
    "in colsum(const imatrix&,int column)",
    matrix.colmin(), matrix.colmax(), column);
  }
#endif
  int sum = 0;
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  const ivector* pmatrixi = &matrix(min);
  for (int i = min; i <= max; ++i)
  {
    sum += *(pmatrixi->get_v() + column);
    ++pmatrixi;
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
#ifndef OPT_LIB
  if (column < matrix.colmin() || column > matrix.colmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Specified column is out of bounds",
    "in column(const imatrix&, int column)",
    matrix.colmin(), matrix.colmax(), column);
  }
#endif
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  ivector vector(min, max);
  int* pvectori = &vector(min);
  const ivector* pmatrixi = &matrix(min);
  for (int i = min; i <= max; ++i)
  {
    *pvectori = *(pmatrixi->get_v() + column);
    ++pmatrixi;
    ++pvectori;
  }
  return vector;
}
