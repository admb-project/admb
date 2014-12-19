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
 * Description not yet available.
 * \param
 */
d3_array operator/(const d3_array& m, const double d)
{
  d3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=m(i)/d;
  }
  return tmp;
}
/**
 * Description not yet available.
 * \param
 */
void d3_array::operator/=(const double d)
{
  for (int i=slicemin();i<=slicemax();i++)
  {
    (*this)(i) /= d;
  }
}
