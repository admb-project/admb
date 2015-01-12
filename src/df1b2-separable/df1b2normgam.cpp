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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2variable norm_to_gamma(const df1b2variable & v,const df1b2variable& alpha,
  double bound)
{
  df1b2variable z=bounded_cumd_norm(v,bound);
  return inv_cumd_gamma(z,alpha);
}
