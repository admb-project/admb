#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

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
/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( log(\Gamma(x+r))-log(\Gamma(r))-log(x!)+rlog(r)+xlog(\mu)-(r+x)log(r+\mu) )\f$
**/
df1b2variable dnbinom(const dvector& x, const df1b2vector& lambda, const df1b2variable& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable loglike;
	loglike=0.;
	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( log(\Gamma(x+r))-log(\Gamma(r))-log(x!)+rlog(r)+xlog(\mu)-(r+x)log(r+\mu) )\f$
**/
df1b2variable dnbinom(const dvector& x, const df1b2vector& lambda, const df1b2vector& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable loglike;
	loglike=0.;
 
	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( log(\Gamma(x+r))-log(\Gamma(r))-log(x!)+rlog(r)+xlog(\mu)-(r+x)log(r+\mu) )\f$
**/

dvariable dnbinom(const dvector& x, const dvar_vector& lambda, const prevariable& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike = 0.;

	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( log(\Gamma(x+r))-log(\Gamma(r))-log(x!)+rlog(r)+xlog(\mu)-(r+x)log(r+\mu) )\f$
**/
dvariable dnbinom(const dvector& x, const dvar_vector& lambda, const dvar_vector& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike;
	loglike=0.;

	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}