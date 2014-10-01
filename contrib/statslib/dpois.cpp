#include "statsLib.h"

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
*  -k  \ln( \lambda ) - \lambda  + \ln(k!)
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
	\return returns the negative loglikelihood \f$ -k  \ln( \lambda ) - \lambda  + \ln(k)! \f$
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
	\return returns the negative loglikelihood \f$ -k  \ln( \lambda ) - \lambda  + \ln(k!) \f$
	\sa
**/
dvariable dpois(const prevariable& k, const prevariable& lambda)
{
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = -k*log(lambda)+lambda + gammln(k+1.);
	RETURN_ARRAYS_DECREMENT();
	return tmp;
}

/**	
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-06-24
	\param  k vector of observed numbers
	\param  lambda vector of epected means of the distribution
	\return returns the negative loglikelihood \f$\sum_i -k_i  \ln( \lambda_i ) - \lambda_i  + \ln(k_i!) \f$
	\sa
**/
dvariable dpois(const dvector& k, const dvar_vector& lambda)
{
	RETURN_ARRAYS_INCREMENT();
	int i;
	int n = size_count(k);
	dvariable nll=0;
	for(i = 1; i <= n; i++)
	{
		// nll -= k(i)*log(lambda(i))+lambda(i)+gammln(k(i)+1.);
		nll += -k(i)*log(lambda(i))+lambda(i)+gammln(k(i)+1.);
	}
	RETURN_ARRAYS_DECREMENT();
	return nll;
}


