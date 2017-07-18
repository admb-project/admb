/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return vector of the diagonal elements from matrix.

\param matrix dmatrix
*/
dvector extract_diagonal(const dmatrix& matrix)
{
  return diagonal(matrix);
}
