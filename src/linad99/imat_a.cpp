/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Construct imatrix using dimensions in position.

\param position imatrix_position
*/
imatrix::imatrix(const imatrix_position& position)
{
  if (position.row_min != position.lb.indexmin()
      || position.row_max != position.lb.indexmax()
      || position.row_min != position.ub.indexmin()
      || position.row_max != position.ub.indexmax())
  {
    cerr << "Incompatible array bounds"
         << " in imatrix::imatrix(const imatrix_position&)\n";
    ad_exit(1);
  }

  allocate(position.row_min, position.row_max);

#ifdef DIAG
  cerr << "Created a imatrix with adress "<< farptr_tolong(m)<<"\n";
#endif

  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(position.lb(i), position.ub(i));
  }
}
