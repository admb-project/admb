#include "statsLib.h"

/**
* 
* \file dnbinom.cpp
* \brief Negative binomial density functions.
* \ingroup STATLIB
* \author Steven Martell
* \date 2/05/2011
* 
* 
* This file contains the negative loglikelihood 
* functions for the negative binomial distribution. The function
* dnbinom is overloaded to accomodate variable and data objects. 
* 
* The negative log function is implemented as:
* \f[
*  \ln \Gamma (n) + \ln x! - \ln \Gamma(x+n) - n \ln(p) - x \ln(1-p)
* \f]
* where \f$p\f$ is the negative binomial probability and \f$n\f$
* number of trials, and \f$x\f$ is the number of successes.
* 
* 
* 
*/
/** \brief Negative binomial with size and mean
	
	
	
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-06-23
	\param  x This represents the number of failures which 
	* occur in a sequence of Bernoulli trials before a target
	*  number of successes is reached. 
	\param  size target for number of successful trials, or
	*  dispersion parameter (the shape parameter of the gamma
	*  mixing distribution). Must be strictly positive, need not be integer.
	\param mu is the expected mean number of successful trials.
	\return the negative log likelihood for the negative binomial distribution.
	\sa
**/

dvariable dnbinom(const double& x,const prevariable& size, const prevariable& mu)
{
	if (value(size)<0.0)
	{
		cerr<<"size is <=0.0 in"
			"dnbinom(const double& x,const prevariable& mu, const prevariable& size)\n";
		return(0);
	}
	RETURN_ARRAYS_INCREMENT();
	dvariable p=size/(size+mu);
	dvariable tmp;
	tmp = gammln(x+size) - gammln(size) - factln(x)
		+size*log(p)+x*log(1.-p);
	RETURN_ARRAYS_DECREMENT();
	return(-tmp);
}



