/**
Copyright (c) 2016 ADMB Foundation
*/

#include <admodel.h>

/**
Return computed random gamma number.

Function copied and modified from GNU Scientific Library 
http://git.savannah.gnu.org/cgit/gsl.git/tree/randist/gamma.c
*/
double rgamma(double alpha, random_number_generator& rng) 
{
  double b=1.0;
  double a=alpha;

  if (a<1)
  {
    double u = randu(rng);
    return rgamma (1.0 + a,rng) * pow (u, 1.0 / a);
  }

  double x, v, u;
  double d = a - 1.0 / 3.0;
  double c = (1.0 / 3.0) / sqrt (d);
 
  while (1)
  {
    do
    {
      x = randn(rng);
      v = 1.0 + c * x;
    } while (v<0);
 
    v = v * v * v;
    u = randu(rng);
 
    if (u < (1 - 0.0331 * x * x * x * x)) 
      break;
 
    if (log (u) < (0.5 * x * x + d * (1 - v + log (v))))
      break;
  }
 
  return b * d * v;
}
