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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
double sqrt_m5(double x) {return .5/sqrt(x);}

/**
 * Description not yet available.
 * \param
 */
double sqrt_m32(double x) {return -.25/(sqrt(x)*x);}

/**
 * Description not yet available.
 * \param
 */
double sqrt_m52(double x) {return 3.0/(8.0*sqrt(x)*x*x);}

df1b2function1 ADf1b2_sqrt(::sqrt,::sqrt_m5,::sqrt_m32,::sqrt_m52,"sqrt");

/**
 * Description not yet available.
 * \param
 */
df1b2variable sqrt(const df1b2variable& x)
{
  return ADf1b2_sqrt(x);
}
