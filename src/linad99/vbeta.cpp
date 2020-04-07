/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function beta(const prevariable&,const prevariable&)
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
