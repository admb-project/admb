#include <fvar.hpp>

dvariable norm_to_gamma(const prevariable & v,const prevariable& alpha,
  double bound)
{
  dvariable z=bounded_cumd_norm(v,bound);
  return inv_cumd_gamma(z,alpha);
}

