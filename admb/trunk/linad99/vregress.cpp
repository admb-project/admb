/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <fvar.hpp>

dvariable regression(_CONST dvector& obs,_CONST dvar_vector& pred)
{
  double nobs=double(size_count(obs));
  dvariable vhat=norm2(obs-pred);
  vhat/=nobs;
  return (.5*nobs*log(vhat));
}

