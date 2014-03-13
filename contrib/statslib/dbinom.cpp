#include <df1b2fun.h>
#include <adrndeff.h> 
#include "statsLib.h"


/**
* 
* \file dbinom.cpp
* \brief Binomial density functions.
* \ingroup STATLIB
* \author Steven Martell and Mollie Brooks
* \date 5/02/2014
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
		return(0.0);
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
			"dbinom(const prevariable& x,const prevariable& n,const double& p)\n";
		return(0.0);
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
			"dbinom(const prevariable& x,const prevariable& n,const prevariable& p)\n";
		return(0.0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = -log_comb(n,x)-x*log(p)-(n-x)*log(1.-p);
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x is a vector of the number of sucesses
	\param  n is vector for the number of trials
	\param  p is a vector for the binomial probability
	\return returns the negative loglikelihood of the normal distribution
	\sa
**/
dvariable dbinom(const dvar_vector& x,const dvar_vector& n,const dvar_vector& p)
{
	if(min(p)<=0. && max(p)>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const dvar_vector& x,const dvar_vector& n,const dvar_vector& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = x.indexmin();
	int imax = x.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n(i),x(i))-x(i)*log(p(i))-(n(i)-x(i))*log(1.-p(i));
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}

dvariable dbinom(const prevariable& x,const dvar_vector& n,const dvar_vector& p)
{
	if(min(p)<=0. && max(p)>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const prevariable& x,const dvar_vector& n,const dvar_vector& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = n.indexmin();
	int imax = n.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n(i),x)-x*log(p(i))-(n(i)-x)*log(1.-p(i));
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
dvariable dbinom(const dvar_vector& x,const prevariable& n,const dvar_vector& p)
{
	if(min(p)<=0. && max(p)>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const dvar_vector& x,const prevariable& n,const dvar_vector& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = x.indexmin();
	int imax = x.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n,x(i))-x(i)*log(p(i))-(n-x(i))*log(1.-p(i));
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
dvariable dbinom(const dvar_vector& x,const dvar_vector& n,const prevariable& p)
{
	if(p<=0. && p>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const dvar_vector& x,const dvar_vector& n,const prevariable& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = x.indexmin();
	int imax = x.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	dvariable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n(i),x(i))-x(i)*log(p)-(n(i)-x(i))*log(1.-p);
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
df1b2variable dbinom(const df1b2variable& x,const double& n,const double& p)
{
	if(p<=0. && p>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const df1b2variable& x,const double& n,const double& p)\n";
		return(0.0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tmp = -log_comb(n,x)-x*log(p)-(n-x)*log(1.-p);
	//df1b2variable tmp = factln(x)-factln(n-x)-factln(n)-x*log(p)-(n-x)*log(1.-p);
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
df1b2variable dbinom(const df1b2variable& x,const df1b2variable& n,const double& p)
{
	if(p<=0. && p>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const df1b2variable& x,const df1b2variable& n,const double& p)\n";
		return(0.0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tmp = -log_comb(n,x)-x*log(p)-(n-x)*log(1.-p);
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
df1b2variable dbinom(const df1b2variable& x,const df1b2variable& n,const df1b2variable& p)
{
	if(value(p)<=0. && value(p)>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const df1b2variable& x,const df1b2variable& n,const df1b2variable& p)\n";
		return(0.0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tmp = -log_comb(n,x)-x*log(p)-(n-x)*log(1.-p);
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x is a vector of the number of sucesses
	\param  n is vector for the number of trials
	\param  p is a vector for the binomial probability
	\return returns the negative loglikelihood of the normal distribution
	\sa
**/
df1b2variable dbinom(const df1b2vector& x,const df1b2vector& n,const df1b2vector& p)
{
	if(min(value(p))<=0. && max(value(p))>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const df1b2vector& x,const df1b2vector& n,const df1b2vector& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = x.indexmin();
	int imax = x.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n(i),x(i))-x(i)*log(p(i))-(n(i)-x(i))*log(1.-p(i));
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}

df1b2variable dbinom(const df1b2variable& x,const df1b2vector& n,const df1b2vector& p)
{
	if(min(value(p))<=0. && max(value(p))>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const df1b2variable& x,const df1b2vector& n,const df1b2vector& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = n.indexmin();
	int imax = n.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n(i),x)-x*log(p(i))-(n(i)-x)*log(1.-p(i));
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
df1b2variable dbinom(const df1b2vector& x,const df1b2variable& n,const df1b2vector& p)
{
	if(min(value(p))<=0. && max(value(p))>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const df1b2vector& x,const df1b2variable& n,const df1b2vector& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = x.indexmin();
	int imax = x.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n,x(i))-x(i)*log(p(i))-(n-x(i))*log(1.-p(i));
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
df1b2variable dbinom(const df1b2vector& x,const df1b2vector& n,const df1b2variable& p)
{
	if(value(p)<=0. && value(p)>=1.0)
	{
		cerr<<"The probability p must be greater than 0 or less than 1 in "
			"dbinom(const df1b2vector& x,const df1b2vector& n,const df1b2variable& p)\n";
		return(0.0);
	}
	
	int i;
	int imin = x.indexmin();
	int imax = x.indexmax();
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable tmp = 0.0;
	for(i=imin; i<=imax;i++)
	{
		tmp += log_comb(n(i),x(i))-x(i)*log(p)-(n(i)-x(i))*log(1.-p);
	}
	
	RETURN_ARRAYS_DECREMENT();
	return(tmp);
}
