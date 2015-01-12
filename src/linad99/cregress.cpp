/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <fvar.hpp>

double regression(_CONST dvector& obs,_CONST dvector& pred)
{
  double nobs=double(size_count(obs));
  double vhat=norm2(obs-pred);
  vhat/=nobs;
  return (.5*nobs*log(vhat));
}
