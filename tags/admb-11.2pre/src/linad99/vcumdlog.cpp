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
dvariable cumd_logistic(const prevariable& x)
{
  if (value(x)>=0.0)
  {
    return 1.0/(1.0+exp(-x));
  }
  else
  {
    dvariable y=exp(x);
    return y/(1.0+y);
  }
}

/**
 * Description not yet available.
 * \param
 */
dvariable inv_cumd_logistic(const prevariable& x)
{
  return log(x/(1.0-x));
}
