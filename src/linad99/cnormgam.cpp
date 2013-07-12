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
double norm_to_gamma(double v,double alpha,double bound)
{
  double z=bounded_cumd_norm(v,bound);
  return inv_cumd_gamma(z,alpha);
}
