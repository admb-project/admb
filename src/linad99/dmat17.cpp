/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return an identity matrix with
dimensions [min to max] x [min to max].

\param min lower row and column index
\param max upper row and column index
*/
dmatrix identity_matrix(int min, int max)
{
  dmatrix identity(min, max, min, max);

#ifndef SAFE_INITIALIZE
  identity.initialize();
#endif

  for (int i = min; i <= max; ++i)
  {
    identity.elem(i, i) = 1;
  }

  return identity;
}
