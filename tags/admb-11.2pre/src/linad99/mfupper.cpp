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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable mf_upper_bound(const prevariable& x, double M, prevariable& fpen)
  {
    if (x<=M)
    {
      return x;
    }
    else
    {
      fpen+=square(x-M);
      return M+(1.+2.*(x-M))/(1.+x-M);
    }
  }
