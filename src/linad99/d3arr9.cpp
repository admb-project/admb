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
double d3_array::fill_seqadd(double i1,double i2)
{
  int mmin=indexmin();
  int mmax=indexmax();
  double inp = i1;
  for (int i=mmin;i<=mmax;i++)
  {
    double tmp=(*this)(i).fill_seqadd(inp,i2);
    inp=tmp;
  }
  return inp;
}
