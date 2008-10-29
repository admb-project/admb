#include <fvar.hpp>

double norm_to_gamma(double v,double alpha,double bound)
{
  double z=bounded_cumd_norm(v,bound);
  return inv_cumd_gamma(z,alpha);
}

