/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fun.h>

double sqrt_m5(double x) {return .5/sqrt(x);}
double sqrt_m32(double x) {return -.25/(sqrt(x)*x);}
double sqrt_m52(double x) {return 3.0/(8.0*sqrt(x)*x*x);}
df1b2function1 ADf1b2_sqrt(::sqrt,::sqrt_m5,::sqrt_m32,::sqrt_m52,"sqrt");
df1b2variable sqrt(const df1b2variable& x) 
{
  return ADf1b2_sqrt(x);
}
