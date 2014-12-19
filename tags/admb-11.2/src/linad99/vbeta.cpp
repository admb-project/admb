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
 * Beta density function
 * \param a shape parameter
 * \param b shape parameter
 * 
 * Note that the mean of the distribution is given by 
 * mu = a/(a+b), and the variance is ab/((a+b)^2 (a+b+1))
 */
dvariable beta(const prevariable& a,const prevariable& b )
{
  return exp(gammln(a)+gammln(b)-gammln(a+b));
}
