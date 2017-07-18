/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Allocate imatrix using dimensions of other.

\param other imatrix
*/
void imatrix::allocate(const imatrix& other)
{
  allocate(other.rowmin(), other.rowmax());
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i).allocate(other(i));
  }
}
