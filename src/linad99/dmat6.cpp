/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return copy of jth column vector from matrix m.

/param m matrix
/param j column index to return
*/
dvector column(const dmatrix& matrix, int j)
{
  return extract_column(matrix, j);
}
/**
Returns a copied row for matrix at i.
Note: i must be a valid row.

\param matrix dmatrix
\param i row index
*/
dvector row(const dmatrix& matrix, int i)
{
  return extract_row(matrix, i);
}
/**
Extract copy of jth column vector from matrix m.

/param m matrix
/param j column index to return
*/
dvector extract_column(const dmatrix& matrix, int j)
{
  if (j < matrix.colmin() || j > matrix.colmax())
  {
    cerr << "Error: Invalid matrix column index specified in "
         << "dvector extract_column(const dmatrix&, int).\n",
    ad_exit(1);
  }
  int min = matrix.rowmin();
  int max = matrix.rowmax();
  dvector column(min, max);

  for (int i = min; i <= max; ++i)
  {
    column.elem(i) = matrix.elem(i,j);
  }
  return column;
}
/**
Returns a copied row for matrix at i.
Note: i must be a valid row.

\param matrix dmatrix
\param i row index
*/
dvector extract_row(const dmatrix& matrix, int i)
{
  if (i < matrix.rowmin() || i > matrix.rowmax())
  {
    cerr << "Error: Invalid matrix row index specified in "
         << "dvector extract_row(const dmatrix&, int).\n",
    ad_exit(1);
  }

  dvector row(matrix(i).indexmin(), matrix(i).indexmax());
  row = matrix.elem(i);

  return row;
}
