/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable regression(_CONST dvector& obs,_CONST dvar_vector& pred)
{
  double nobs=double(size_count(obs));
  dvariable vhat=norm2(obs-pred);
  vhat/=nobs;
  return (.5*nobs*log(vhat));
}
