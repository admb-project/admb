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
#include "df1b2fun.h"

/**
 * Description not yet available.
 * \param x
 * \param min
 * \param max
 * \param mscale
 */
df1b2variable bounder(const df1b2variable&  x,double min,double max,
    double scale)
{
  df1b2variable y=x/scale;
  df1b2variable z;
  if (value(y)<20.0)
  {
    z=exp(y)/(1.0+exp(y));
  }
  else
  {
    z=1.0/(1+exp(-y));
  }
  return min+(max-min)*z;
}
