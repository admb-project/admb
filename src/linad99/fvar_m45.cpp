/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns negative elements of varmat.

\param varmat varaible matrix
*/
dvar_matrix operator-(const dvar_matrix& varmat)
{
  return -1.0 * varmat;
}
