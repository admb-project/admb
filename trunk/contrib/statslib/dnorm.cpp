#include "statsLib.h"
#include <admodel.h>

/**
* 
* \file dnorm.cpp
* \brief Normal density functions.
* \ingroup STATLIB
* \author Steven Martell
* \date 2/05/2011
* 
* 
* This file contains the negative loglikelihood 
* functions for the normal distribution. The function
* dnorm is overloaded to accomodate single variables and vectors. 
* 
* The function is implemented as:
* \f[
*  0.5\ln(2 \pi) + \ln(\sigma) + 0.5\frac{(x-\mu)^2}{\sigma^2}
* \f]
* where \f$\mu\f$ is the mean and \f$\sigma\f$
* is the standard deviation.
* 
* 
* 
*/

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a differentiable variable
	\param  mu the mean
	\param  std a double precision standard deviation
	\return returns the negative loglikelihood of the normal distribution
	\sa
**/
dvariable dnorm( const prevariable& x, const double& mu, const double& std )
{

	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm(const dvariable& x, const double& mu, const double& std)\n";
		return 0;
	}

	return 0.5*log(2.*M_PI)+log(std)+0.5*square(x-mu)/(std*std);
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x variable vector of observations
	\param  mu a double mean
	\param  std a double standard deviation
	\return returns the sum of negative loglikelihoods of the normal distribution
	\sa
**/
dvariable dnorm( const dvar_vector& x, const double& mu, const double& std )
{
	
	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& x, const double& mu, const double& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable SS=norm2(x-mu);
	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  x a vector of observations
	\param  mu a variable mean
	\param  std a variable standard deviation
	\return returns the sum of negative loglikelihoods of the normal distribution
	\sa
**/
dvariable dnorm( const dvector& x, const prevariable& mu, const prevariable& std )
{
	
	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& x, const double& mu, const double& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable SS=norm2(x-mu);
	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  residual a variable vector of residuals
	\param  std a variable standard deviation
	\return returns the sum of negative loglikelihoods of the normal distribution
	\sa
**/
dvariable dnorm( const dvar_vector& residual, const prevariable& std )
{
	
	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& residual, const dvariable& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(residual);
	dvariable SS=norm2(residual);
	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  residual a variable vector of residuals
	\param  std a double standard deviation
	\return returns the sum of negative loglikelihoods of the normal distribution
	\sa
**/
dvariable dnorm( const dvar_vector& residual, const double& std )
{   
	
	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& residual, const double& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(residual);
	dvariable SS=norm2(residual);
	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  residual a variable vector of residuals
	\param  std a vector of standard deviations
	\return returns the sum of negative loglikelihoods of the normal distribution
	\sa
**/
dvariable dnorm( const dvar_vector& residual, const dvector& std )
{
	
	if( min(std)<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& residual, const dvector& std )\n";
		return 0;
	}
	if (std.indexmin()!=residual.indexmin() && std.indexmax()!=residual.indexmax())
	{
		cerr<<"Indices do not match in "
		"dnorm( const dvar_vector& residual, const dvector& std )\n";
		return 0;
	}
	
	RETURN_ARRAYS_INCREMENT();
	int n=size_count(residual);
	dvector var=elem_prod(std,std);
	dvar_vector SS=elem_prod(residual,residual);
	dvariable tmp = 0.5*n*log(2.*M_PI)+sum(log(std))+sum(elem_div(SS,2.*var));
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}


/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  residual a variable vector of residuals
	\param  std a variable vector of standard deviations
	\return returns the sum of negative loglikelihoods of the normal distribution
	\sa
**/
dvariable dnorm( const dvar_vector& residual, const dvar_vector std )
{
	
	if( min(std)<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& residual, const dvar_vector std )\n";
		return 0;
	}
	if (std.indexmin()!=residual.indexmin() && std.indexmax()!=residual.indexmax())
	{
		cerr<<"Indices do not match in "
		"dnorm( const dvar_vector& residual, const dvector& std )\n";
		return 0;
	}
	
	
	RETURN_ARRAYS_INCREMENT();
	int n=size_count(residual);
	dvar_vector var=elem_prod(std,std);
	dvar_vector SS=elem_prod(residual,residual);
	dvariable tmp=0.5*n*log(2.*M_PI)+sum(log(std))+sum(elem_div(SS,2.*var));
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}
