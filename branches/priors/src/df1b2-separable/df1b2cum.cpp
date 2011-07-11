/*
 * $Id: df1b2cum.cpp 944 2011-01-12 22:48:46Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2variable inv_cumd_exponential(const df1b2variable& y)
{
  if (value(y)<=0.5)
    return log(2.0*y);
  else
    return log(2.0*(1-y));
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable cumd_exponential(const df1b2variable& x)
{
  if (value(x)<=0.0)
    return 0.5*exp(x);
  else
    return 1.0-0.5*exp(-x);
}

