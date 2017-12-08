/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#if (__cplusplus > 199711L)
  #include <iterator>
  #include <algorithm>
#endif
#include "fvar.hpp"

/// Initalize all elements of dmatrix to zero.
void dmatrix::initialize()
{
  // only initialize allocated objects
  if (m)
  {
#if (__cplusplus <= 199711L)
    for (int i = rowmin(); i <= rowmax(); ++i)
    {
      elem(i).initialize();
    }
#else
    std::for_each(begin(), end(), [](dvector& v) {
      v.initialize();
    });
#endif
  }
}
