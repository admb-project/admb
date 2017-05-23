/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns diagonal of variable matrix m.
\param m square dvar_matrix
*/
dvar_vector extract_diagonal(const dvar_matrix& m)
{
  if ((m.rowmin() != m.colmin()) || (m.rowmax() != m.colmax()))
  {
    cerr << "Error in extract_diagonal function -- input matrix not square\n";
    ad_exit(1);
  }
  RETURN_ARRAYS_INCREMENT();
  dvar_vector diagonal(m.rowmin(), m.rowmax());

  for (int i = m.rowmin(); i <= m.rowmax(); ++i)
  {
      diagonal.elem(i) = m.elem(i,i);
  }

  RETURN_ARRAYS_DECREMENT();

  return diagonal;
}
