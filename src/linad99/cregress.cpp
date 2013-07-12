/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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
double regression(const dvector& obs, const dvector& pred)
{
  double nobs=double(size_count(obs));
  double vhat=norm2(obs-pred);
  vhat/=nobs;
  return (.5*nobs*log(vhat));
}
