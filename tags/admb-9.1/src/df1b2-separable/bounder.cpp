/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "df1b2fun.h"


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

