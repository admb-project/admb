#include "statsLib.h"

/**
* \file dlnorm.cpp
* \brief Lognormal density functions.
* \author Steven Martell
* \date 2/05/2011
* \ingroup STATLIB
* This file contains the negative loglikelihood 
* functions for the lognormal distribution. The function
* dlnorm is overloaded to accomodate single variables and vectors. 
* 
* * The function is implemented as:
* \f[
*  0.5\ln(2 \pi) + \ln(\sigma)+\ln(x) + 0.5\frac{(\ln(x)-\mu)^2}{\sigma^2}
* \f]
* where \f$\mu\f$ is the logmean and \f$\sigma\f$
* is the log standard deviation.  The function returns an error
* if either the std<=0 or x<=0
* 
* 
*/




/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a differentiable variable
	\param  mu is a double precision log mean
	\param  std a double precision log standard deviation
	\return returns the negative loglikelihood of the lognormal distribution
	\sa
**/
dvariable dlnorm( const prevariable& x, const double& mu, const double& std )
{	
	
	if( std<=0 || x<=0 ) 
	{
		cerr<<"Standard deviation or the mean is less than or equal to zero in "
		"dlnorm( const dvariable& x, const double& mu, const double& std )\n";
		return 0;
	}
	
	return 0.5*log(2.*M_PI)+log(std)+log(x)+square(log(x)-mu)/(2.*std*std);
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a differentiable variable
	\param  mu is a variable log mean
	\param  std a double precision log standard deviation
	\return returns the negative loglikelihood of the lognormal distribution
	\sa
**/
dvariable dlnorm( const prevariable& x, const prevariable& mu, const double& std )
{	
	
	if( std<=0 || x<=0 ) 
	{
		cerr<<"Standard deviation or the mean is less than or equal to zero in "
		"dlnorm( const dvariable& x, const dvariable& mu, const double& std )\n";
		return 0;
	}
	
	return 0.5*log(2.*M_PI)+log(std)+log(x)+square(log(x)-mu)/(2.*std*std);
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a differentiable variable
	\param  mu is a variable log mean
	\param  std a variable log standard deviation
	\return returns the negative loglikelihood of the lognormal distribution
	\sa
**/
dvariable dlnorm( const prevariable& x, const prevariable& mu, const prevariable& std )
{	
	
	if( std<=0 || x<=0 ) 
	{
		cerr<<"Standard deviation or the mean is less than or equal to zero in "
		"dlnorm( const dvariable& x, const dvariable& mu, const dvariable& std )\n";
		return 0;
	}
	
	return 0.5*log(2.*M_PI)+log(std)+log(x)+square(log(x)-mu)/(2.*std*std);
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a differentiable vector
	\param  mu is a double precision log mean
	\param  std a double precision log standard deviation
	\return returns the negative loglikelihood of the lognormal distribution
	\sa
**/
dvariable dlnorm( const dvar_vector& x, const double& mu, const double& std )
{
	
	if( std<=0 || min(x)<=0 )
	{
		cerr<<"Standard deviation or the mix(x) is less than or equal to zero in "
		"dlnorm( const dvar_vector& x, const double& mu, const double& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable ss = norm2( log(x)-mu );
	dvariable t1 = n*(0.5*log(2*M_PI)+log(std));
	dvariable nloglike = t1 + sum(log(x)) + ss/(2.*std*std);
	RETURN_ARRAYS_DECREMENT();
	return nloglike;	
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a differentiable vector
	\param  mu is a prevariable log mean
	\param  std a double precision log standard deviation
	\return returns the negative loglikelihood of the lognormal distribution
	\sa
**/
dvariable dlnorm( const dvar_vector& x, const prevariable& mu, const double& std )
{
	
	if( std<=0 || min(x)<=0 )
	{
		cerr<<"Standard deviation or the mix(x) is less than or equal to zero in "
		"dlnorm( const dvar_vector& x, const dvariable& mu, const double& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable ss = norm2( log(x)-mu );
	dvariable t1 = n*(0.5*log(2*M_PI)+log(std));
	dvariable nloglike = t1 + sum(log(x)) + ss/(2.*std*std);
	RETURN_ARRAYS_DECREMENT();
	return nloglike;	
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a differentiable vector
	\param  mu is a prevariable log mean
	\param  std a prevariable log standard deviation
	\return returns the negative loglikelihood of the lognormal distribution
	\sa
**/
dvariable dlnorm( const dvar_vector& x, const prevariable& mu, const prevariable& std )
{
	
	if( std<=0 || min(x)<=0 )
	{
		cerr<<"Standard deviation or the mix(x) is less than or equal to zero in "
		"dlnorm( const dvar_vector& x, const dvariable& mu, const dvariable& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable ss = norm2( log(x)-mu );
	dvariable t1 = n*(0.5*log(2*M_PI)+log(std));
	dvariable nloglike = t1 + sum(log(x)) + ss/(2.*std*std);
	RETURN_ARRAYS_DECREMENT();
	return nloglike;	
}

