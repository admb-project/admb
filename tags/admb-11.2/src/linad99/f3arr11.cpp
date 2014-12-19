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
dvar3_array mfexp(const dvar3_array& m)
{
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i) = mfexp(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar3_array mfexp(const dvar3_array& m, const double d)
{
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=mfexp(m(i),d);
  }
  return tmp;
}
