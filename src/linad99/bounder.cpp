/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function bounder for double and dvariable type.
*/

#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
  double bounder(double x,double min,double max, double scale)
  {
    double y=x/scale;
    double z;
    if (y<20.0)
    {
      z=exp(y)/(1.0+exp(y));
    }
    else
    {
      z=1.0/(1+exp(-y));
    }
    return min+(max-min)*z;
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable bounder(const prevariable&  x,double min,double max, double scale)
  {
    dvariable y=x/scale;
    dvariable z;
    if (y<20.0)
    {
      z=exp(y)/(1.0+exp(y));
    }
    else
    {
      z=1.0/(1+exp(-y));
    }
    return min+(max-min)*z;
  }
