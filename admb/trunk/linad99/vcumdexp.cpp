#include <fvar.hpp>

dvariable inv_cumd_exponential(const prevariable& y)
{
  if (y<=0.5)
    return log(2.0*y);
  else
    return log(2.0*(1-y));
}


dvariable cumd_exponential(const prevariable& x)
{
  if (x<=0.0)
    return 0.5*exp(x);
  else
    return 1.0-0.5*exp(-x);
}

