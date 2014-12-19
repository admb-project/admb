/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/**
Reallocate size of array.

\param percent change
*/
void dvector::reallocate(double s)
{
  if (::allocated(*this))
  {
    int oldmin=indexmin();
    int oldmax=indexmax();
    dvector tmp(indexmin(),indexmax());
    tmp=(*this);
    deallocate();
    allocate(indexmin(),int(s*indexmax()));
#ifndef OPT_LIB
    initialize();
#endif
    int max = oldmax < indexmax() ? oldmax : indexmax();
    (*this)(oldmin, max) = tmp(oldmin, max);
  }
}
