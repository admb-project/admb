
#include <admodel.h>

param_init_bounded_dev_vector& param_init_bounded_dev_vector::operator = (const dvector& m)
{
  dvar_vector::operator=(m);
  return *this;
}
param_init_bounded_dev_vector& param_init_bounded_dev_vector::operator = (const dvar_vector& m)
{
  dvar_vector::operator=(m);
  return *this;
}

param_init_bounded_dev_vector& param_init_bounded_dev_vector::operator = (const prevariable& m)
{
  dvar_vector::operator=(m);
  return *this;
}
param_init_bounded_dev_vector& param_init_bounded_dev_vector::operator = (const double& m)
{
  dvar_vector::operator=(m);
  return *this;
}

#undef HOME_VERSION
