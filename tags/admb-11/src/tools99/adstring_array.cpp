/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 ADMB Foundation
 */
#include "adstring.hpp"

adstring_array& adstring_array::operator=(const adstring_array& a)
{
  if (this != &a)
  {
    const int min = a.indexmin();
    const int max = a.indexmax();
    allocate(min, max);
    for (int i = min; i <= max; i++)
    {
      (*this)[i] = a[i];
    }
  }
  return *this;
}
