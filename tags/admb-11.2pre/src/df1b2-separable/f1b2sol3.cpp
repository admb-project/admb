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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
dvar_vector solve(const named_dvar_matrix& M,const random_effects_vector& v)
{
  dvar_matrix & tM=(dvar_matrix&)(M);
  dvar_vector & tv=(dvar_vector&)(v);
  return solve( tM,tv);
}
