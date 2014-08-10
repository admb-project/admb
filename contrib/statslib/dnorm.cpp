#include "statsLib.h"
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

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
* functions for the normal distribution and is implemented to be consistent
* with the statistical program R with log=TRUE. The function
* dnorm is overloaded to accomodate single variables and vectors. 
*
* There are also overloaded versions where the user can specify the likelihood (i.e., log=FALSE)
* 
* The function is implemented as the negative log of the normal density function:
* \f[
*  0.5\ln(2 \pi) + \ln(\sigma) + 0.5\frac{(x-\mu)^2}{\sigma^2}
* \f]
* where \f$\mu\f$ is the mean and \f$\sigma\f$
* is the standard deviation.
* 
* The concentrated likelihood is implemented as:
* \f[
*  0.5 n \ln(\sum_{i=1}^{n}\epsilon^2)
* \f]
* where \f$ \epsilon \f$ is a vector of residuals with an assumed mean 0.
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

dvariable dnorm( const prevariable& x, const double& mu, const double& std, bool bLog=true )
{

	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm(const dvariable& x, const double& mu, const double& std)\n";
		return 0;
	}
	dvariable tmp = 0.5*log(2.*M_PI)+log(std)+0.5*square(x-mu)/(std*std);
	if(!bLog)  tmp = mfexp(-tmp);
	return tmp;
}



df1b2variable dnorm( const df1b2variable& x, const df1b2variable& mu, const df1b2variable& std, bool bLog=true )
{

	if( value(std)<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm(const dvariable& x, const double& mu, const double& std)\n";
		ad_exit(1);
		//return df1b2variable(0);
	}
	df1b2variable tmp = 0.5*log(2.*M_PI)+log(std)+0.5*square(x-mu)/(std*std);
	if(!bLog)  	  tmp = mfexp(-tmp);
	return tmp;
}

df1b2variable dnorm( const df1b2variable& x, const double& mu, const double& std )
{

	if( value(std)<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm(const df1b2variable& x, const double& mu, const double& std)\n";
		ad_exit(1);
		//return df1b2variable(0);
	}
	df1b2variable tmp = 0.5*log(2.*M_PI)+log(std)+0.5*square(x-mu)/(std*std);
	return tmp;
}


df1b2variable dnorm( const df1b2variable& x, const double& mu, const double& std, bool bLog=true )
{

	if( value(std)<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm(const df1b2variable& x, const double& mu, const double& std)\n";
		ad_exit(1);
		//return df1b2variable(0);
	}
	df1b2variable tmp = 0.5*log(2.*M_PI)+log(std)+0.5*square(x-mu)/(std*std);
	if(!bLog)  	  tmp = mfexp(-tmp);
	return tmp;
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
		ad_exit(1);
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable SS=norm2(x-mu);
	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}

dvariable dnorm( const dvar_vector& x, const double& mu, const double& std, bool bLog=true )
{
	
	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& x, const double& mu, const double& std )\n";
		ad_exit(1);
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable SS=norm2(x-mu);
	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	if(!bLog) tmp = mfexp(-tmp);
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}

df1b2variable dnorm( const df1b2vector& x, const double& mu, const double& std, bool bLog=true )
{
	
	if( std<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"dnorm( const dvar_vector& x, const double& mu, const double& std )\n";
		ad_exit(1);
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n             = size_count(x);
	df1b2variable SS   = norm2(x-mu);
	df1b2variable tmp = n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	if(!bLog) tmp      = mfexp(-tmp);
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
		ad_exit(1);
	}
	
	RETURN_ARRAYS_INCREMENT();
	long n=size_count(x);
	dvariable SS=norm2(x-mu);
	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}

// dvariable dnorm( const dvector& x, const prevariable& mu, const prevariable& std, bool dLog=true )
// {
	
// 	if( std<=0 ) 
// 	{
// 		cerr<<"Standard deviation is less than or equal to zero in "
// 		"dnorm( const dvar_vector& x, const double& mu, const double& std )\n";
// 		ad_exit(1);
// 	}
	
// 	RETURN_ARRAYS_INCREMENT();
// 	long n=size_count(x);
// 	dvariable SS=norm2(x-mu);
// 	dvariable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
// 	if(!dLog) tmp=mfexp(-tmp);
// 	RETURN_ARRAYS_DECREMENT();
// 	return( tmp );
// }

// df1b2variable dnorm( const df1b2vector& x, const df1b2variable& mu, const df1b2variable& std, bool dLog=true )
// {
	
// 	if( std<=0 ) 
// 	{
// 		cerr<<"Standard deviation is less than or equal to zero in "
// 		"dnorm( const dvar_vector& x, const double& mu, const double& std )\n";
// 		ad_exit(1);
// 	}
	
// 	RETURN_ARRAYS_INCREMENT();
// 	long n=size_count(x);
// 	df1b2variable SS=norm2(x-mu);
// 	df1b2variable tmp=n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std);
// 	if(!dLog) tmp= mfexp(-tmp);
// 	RETURN_ARRAYS_DECREMENT();
// 	return( tmp );
// }

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
		ad_exit(1);
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
		ad_exit(1);
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
		ad_exit(1);
	}
	if (std.indexmin()!=residual.indexmin() && std.indexmax()!=residual.indexmax())
	{
		cerr<<"Indices do not match in "
		"dnorm( const dvar_vector& residual, const dvector& std )\n";
		ad_exit(1);
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
	\return returns the concentrated likelihood for the normal distribution.
	\sa
**/
dvariable dnorm( const dvar_vector& residual )
{
	RETURN_ARRAYS_INCREMENT();
	int n              = size_count(residual);
	dvariable SS       = norm2(residual);
	dvariable nloglike = 0.5*n*log(SS);
	RETURN_ARRAYS_DECREMENT();
	return(nloglike);
}

/** 
	\author Steven James Dean Martell
	\date 2011-06-21
	\param  obs a matrix of observed values
	\param  pred a variable matrix of predicted values
	\return returns the concentrated likelihood for the normal distribution.
	\sa
**/
dvariable dnorm( const dmatrix& obs, const dvar_matrix& pred)
{
	RETURN_ARRAYS_INCREMENT();
	int n = size_count(obs);
	dvariable SS = sum(elem_div(square(obs-pred),0.01+pred));
	RETURN_ARRAYS_DECREMENT();
	return 0.5*n*log(SS);
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
		ad_exit(1);
	}
	if (std.indexmin()!=residual.indexmin() && std.indexmax()!=residual.indexmax())
	{
		cerr<<"Indices do not match in "
		"dnorm( const dvar_vector& residual, const dvector& std )\n";
		ad_exit(1);
	}
	
	
	RETURN_ARRAYS_INCREMENT();
	int n=size_count(residual);
	dvar_vector var=elem_prod(std,std);
	dvar_vector SS=elem_prod(residual,residual);
	dvariable tmp=0.5*n*log(2.*M_PI)+sum(log(std))+sum(elem_div(SS,2.*var));
	RETURN_ARRAYS_DECREMENT();
	return( tmp );
}
