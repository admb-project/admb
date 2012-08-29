#include "statsLib.h"

/**
* 
* \file dbinom.cpp
* \brief Binomial density functions.
* \ingroup STATLIB
* \author Steven Martell
* \date 2/05/2011
* 
* 
* This file contains the negative loglikelihood 
* functions for the binomial distribution. The function
* dbinom is overloaded to accommodate variable and data objects. 
* 
* The negative log likelihood function is implemented as:
* \f[
*  \ln k! - \ln(n-k)! -\ln n!  - x \ln(p) - (n-x) \ln(1-p)
* \f]
* where \f$p\f$ is the probability and \f$n\f$
* number of trials, and \f$x\f$ is the number of successes.
* 
* 
* 
*/

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x number of sucesses
	\param  n is the number of trials
	\param  p is the binomial probability
	\return returns the negative loglikelihood of the normal distribution
	\sa
**/
dvariable dbinom(const prevariable& x,const double& n,const double& p)
{
	if(p<=0. && p>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const prevariable& x,const double& n,const double& p)\n";
		return(0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = -log_comb(n,x)-x*log(p)-(n-x)*log(1.-p);
	//dvariable tmp = factln(x)-factln(n-x)-factln(n)-x*log(p)-(n-x)*log(1.-p);
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x number of sucesses
	\param  n is the number of trials
	\param  p is the binomial probability
	\return returns the negative loglikelihood of the normal distribution
	\sa
**/
dvariable dbinom(const prevariable& x,const prevariable& n,const double& p)
{
	if(p<=0. && p>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const prevariable& x,const double& n,const double& p)\n";
		return(0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = -log_comb(n,x)-x*log(p)-(n-x)*log(1.-p);
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x number of sucesses
	\param  n is the number of trials
	\param  p is the binomial probability
	\return returns the negative loglikelihood of the normal distribution
	\sa
**/
dvariable dbinom(const prevariable& x,const prevariable& n,const prevariable& p)
{
	if(p<=0. && p>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const prevariable& x,const double& n,const double& p)\n";
		return(0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = -log_comb(n,x)-x*log(p)-(n-x)*log(1.-p);
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
