#include <admodel.h>
/**
* 
* \file dpois.cpp
* \brief Poisson density functions.
* \ingroup STATLIB
* \author Steven Martell
* \date 24/06/2011
* 
* 
* This file contains the negative loglikelihood 
* functions for the Poisson distribution. The function
* dpois is overloaded to accommodate variable and data objects. 
* 
* The negative log likelihood function is implemented as:
* \f[
*  -k  \ln( \lambda ) - \lambda  + x!
* \f]
* where \f$p\f$ is the probability and \f$n\f$
* number of trials, and \f$x\f$ is the number of successes.
* 
* 
* 
*/

/**	
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-06-24
	\param  k observed number
	\param  lambda epected mean of the distribution
	\return returns the negative loglikelihood of the Poisson density function.
	\sa
**/
dvariable dpois(const double& k, const prevariable& lambda)
{
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = -k*log(lambda)+lambda + gammln(k+1.);
	RETURN_ARRAYS_DECREMENT();
	return tmp;
}

/**	
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-06-24
	\param  k observed number
	\param  lambda epected mean of the distribution
	\return returns the negative loglikelihood of the Poisson density function.
	\sa
**/
dvariable dpois(const prevariable& k, const prevariable& lambda)
{
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = -k*log(lambda)+lambda + gammln(k+1.);
	RETURN_ARRAYS_DECREMENT();
	return tmp;
}
