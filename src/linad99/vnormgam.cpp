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
dvariable norm_to_gamma(const prevariable & v,const prevariable& alpha,
  double bound)
{
  dvariable z=bounded_cumd_norm(v,bound);
  return inv_cumd_gamma(z,alpha);
}
