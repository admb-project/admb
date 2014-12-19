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
#include "fvar.hpp"

/**
 * Compute the mean of the matrix m.
 * \param
 */
double mean(const dmatrix& m)
{
  double tmp = sum(m) / size_count(m);
  return tmp;
}
