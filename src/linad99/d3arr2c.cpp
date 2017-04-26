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
Returns d3_array with square root values from m.
\param m input values
 */
d3_array sqrt(const d3_array& m)
{
  d3_array tmp;
  tmp.allocate(m);
  for (int i = tmp.slicemin(); i <= tmp.slicemax(); ++i)
  {
    tmp(i) = sqrt(m(i));
  }
  return tmp;
}
/**
Returns d3_array with square root values from m.
\param m input values
*/
d3_array sqr(const d3_array& m)
{
  d3_array tmp;
  tmp.allocate(m);
  for (int i = tmp.slicemin(); i <= tmp.slicemax(); ++i)
  {
    tmp(i) = sqrt(m(i));
  }
  return tmp;
}
