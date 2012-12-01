#include "statsLib.h"
#include <df1b2fun.h>
#include <adrndeff.h> 

/**
* 
* \file dnbinom.cpp
* \brief Negative binomial density functions.
* \ingroup STATLIB
* \author Steven Martell and Mollie Brooks
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
    \ingroup STATLIB
**/

dvariable dnbinom(const double& x,const prevariable& mu, const prevariable& size)
{
	if (value(size)<0.0)
	{
		cerr<<"size is <=0.0 in"
			"dnbinom(const double& x,const prevariable& mu, const prevariable& size)\n";
		return(0);
	}
	RETURN_ARRAYS_INCREMENT();
	//dvariable p=size/(size+mu);
	dvariable tmp;
	//tmp = gammln(x+size) - gammln(size) - factln(x)
	//	+size*log(p)+x*log(1.-p);
	dvariable tau = (1.0 + size*mu);
	tmp = log_negbinomial_density(x,mu,tau);
		
	RETURN_ARRAYS_DECREMENT();
	return(-tmp);
}

/** negative log likelihood of negative binomial with mean and size 
\brief Negative binomial with size and mean
\author Mollie Brooks
\param x observed count
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
df1b2variable dnbinom(const double& x, const df1b2variable& mu, const df1b2variable& k)
{
	//x is the observed count
	//mu is the predicted mean
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dnbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tau;
	df1b2variable loglike;
	tau = (1.0 + mu*k);
	//loglike = gammln(k+x)-gammln(k)-gammln(x+1)+k*log(k)-k*log(mu+k)+x*log(mu)-x*log(mu+k);
	loglike = log_negbinomial_density(x,mu,tau);

	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
//dvariable dnbinom(const double& x, const prevariable& mu, const prevariable& k)
//{
//	//x is the observed count
//	//mu is the predicted mean
//	//k is the overdispersion parameter
//	if (value(k)<0.0)
//	{
//		cerr<<"k is <=0.0 in dnbinom()";
//		return(0.0);
//	}
//	RETURN_ARRAYS_INCREMENT();
//	dvariable loglike;
//
//	loglike = gammln(k+x)-gammln(k)-gammln(x+1)+k*log(k)-k*log(mu+k)+x*log(mu)-x*log(mu+k);
//
//	RETURN_ARRAYS_DECREMENT();
//	return(-loglike);
//}

/** negative log likelihood of negative binomial with mean and size 
\brief Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
df1b2variable dnbinom(const dvector& x, const df1b2vector& mu, const df1b2variable& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dnbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable tau;
	df1b2variable loglike;
	loglike=0.;
	for(i = imin; i<=imax; i++)
	{	tau      = (1.0+mu(i)*k);
		loglike += log_negbinomial_density(x(i),mu(i),tau);
		//loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean and size 
\brief Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
df1b2variable dnbinom(const dvector& x, const df1b2vector& mu, const df1b2vector& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter

	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable tau;
	df1b2variable loglike;
	loglike=0.;
 
	for(i = imin; i<=imax; i++)
	{
		if (value(k(i))<0.0)
		{
			cerr<<"k("<<i<<") is <=0.0 in dnbinom()";
			return(0.0);
		}
		tau      = (1.0+mu(i)*k(i));
		loglike += log_negbinomial_density(x(i),mu(i),tau);
		//loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean and size 
\brief Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/

dvariable dnbinom(const dvector& x, const dvar_vector& mu, const prevariable& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dnbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable tau;
	dvariable loglike = 0.;

	for(i = imin; i<=imax; i++)
	{
		tau      =(1.0+mu(i)*k);
		loglike +=log_negbinomial_density(x(i),mu(i),tau);
		//loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean and size 
\brief Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
dvariable dnbinom(const dvector& x, const dvar_vector& mu, const dvar_vector& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable tau;
	dvariable loglike;
	loglike=0.;

	for(i = imin; i<=imax; i++)
	{
		if (value(k(i))<0.0)
		{
			cerr<<"k("<<i<<") is <=0.0 in dnbinom()";
			return(0.0);
		}
		tau      =(1.0+mu(i)*k(i));
		loglike +=log_negbinomial_density(x(i),mu(i),tau);
		
		//loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}


