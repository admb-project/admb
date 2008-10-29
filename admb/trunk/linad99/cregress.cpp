

//COPYRIGHT (c) 1994 OTTER RESEARCH LTD
#define HOME_VERSION
#include <fvar.hpp>

double regression(_CONST dvector& obs,_CONST dvector& pred)
{
  double nobs=double(size_count(obs));
  double vhat=norm2(obs-pred);
  vhat/=nobs;
  return (.5*nobs*log(vhat));
}
#undef HOME_VERSION
