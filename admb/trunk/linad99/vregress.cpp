

//COPYRIGHT (c) 1994 OTTER RESEARCH LTD
#define HOME_VERSION
#include <fvar.hpp>

dvariable regression(_CONST dvector& obs,_CONST dvar_vector& pred)
{
  double nobs=double(size_count(obs));
  dvariable vhat=norm2(obs-pred);
  vhat/=nobs;
  return (.5*nobs*log(vhat));
}

#undef HOME_VERSION
