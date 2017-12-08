/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>

/**
Returns a selected vector of rows from ivector using positions
in indexes, then for each selected row select only values each
position in indexes.

Note: Assumes positions are in range [indexmin() to indexmax()].

\param indexes contains vector of valid index values
 */
dmatrix dmatrix::operator()(const ivector& indexes)
{
  dmatrix rows(indexes.indexmin(), indexes.indexmax(),
               indexes.indexmin(), indexes.indexmax());

  for (int i = rows.rowmin(); i <= rows.rowmax(); ++i)
  {
    rows(i) = operator()(indexes(i))(indexes);
  }
  return rows;
}
