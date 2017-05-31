#include "statsLib.h"

/**
* \file dgamma.cpp
* \brief Gamma density functions.
* \ingroup STATLIB
* \author Steven Martell and Mollie Brooks
* \date 2/28/2011
* 
* This file contains the negative loglikelihood 
* functions for the gamma distribution. The function dgamma
* is implemented as:
* \f[
*  -a \ln(b) + \ln(\Gamma(a)) - (a-1) \ln(x)+b x
* \f]
* The expected value is given by \f$ E(x)=a/b \f$ and the variance as
* \f$ V(x)=a/b^2 \f$.  Note that you can also derive \f$a\f$ and \f$b\f$ from
* the expected value and variance via:
* \f[
* 	a = \frac{E(x)^2}{V(x)}, \quad b=\sqrt{\frac{a}{V(x)}}
* \f]
* 
* 
**/



/**
* \date 2/28/2011
* \author Steven Martell
* \param x is the quantile and must be greater than 0.
* \param a is the shape parameter and must be positive.
* \param b is the rate parameter and must be positive.
* \return a dvariable object
* \sa
**/
dvariable dgamma( const dvariable &x, const double& a, const double& b )
{
	//E(x)=a/b;
	//V(x)=a/b^2
	if ( a<= 0 || b<=0 )
	{
		cerr<<"a or b parameters are less than or equal to 0 in"
			"dgamma( const dvariable &x, const double a, const double b )\n";
		return 0;
	}
	if ( x<=0 )
	{
		cerr<<"The x parameter is less than or equal to 0 in"
			"dgamma( const dvariable &x, const double a, const double b )\n";
		return 0;
	}
	
	return -a*log(b)+gammln(a)-(a-1.)*log(x)+b*x;
}

/**
* \date 2/28/2011
* \author Steven Martell
* \param x is the quantile and must be greater than 0.
* \param a is the shape parameter and must be positive.
* \param b is the rate parameter and must be positive.
* \return a dvariable object
* \sa
**/
dvariable dgamma( const dvariable &x, const dvariable& a, const dvariable &b )
{
	//E(x)=a/b;
	//V(x)=a/b^2
	if ( a<= 0 || b<=0 )
	{
		cerr<<"a or b parameters are less than or equal to 0 in"
			"dgamma( const dvariable &x, const double a, const double b )\n";
		return 0;
	}
	if ( x<=0 )
	{
		cerr<<"The x parameter is less than or equal to 0 in"
			"dgamma( const dvariable &x, const double a, const double b )\n";
		return 0;
	}
	
	return -a*log(b)+gammln(a)-(a-1.)*log(x)+b*x;

}

/**
* \date 8/1/2011
* \author Mollie Brooks
* \param x is the quantile and must be greater than 0.
* \param a is the shape parameter and must be positive.
* \param b is the rate parameter and must be positive.
* \return a dvariable object \f$ \Sigma_i (-a \ln(b)+\ln(\Gamma(a))-(a-1)\ln(x_i)+b x_i) \f$
* \sa
**/

dvariable dgamma( const dvector &x, const prevariable& a, const prevariable& b )
{
	//E(x)=a/b;
	//V(x)=a/b^2
	if ( a<= 0 || b<=0 )
	{
		cerr<<"a or b parameters are less than or equal to 0 in"
			"dgamma( const dvariable &x, const double a, const double b )\n";
		return 0;
	}
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		if ( x(i)<=0 )
		{
			cerr<<"The x("<<i<<") parameter is less than or equal to 0 in"
				"dgamma( const dvariable &x, const double a, const double b )\n";
			return 0;
		}
	}
	return sum(-a*log(b)+gammln(a)-(a-1.)*log(x)+b*x);

}
/**
* \date 8/1/2011
* \author Mollie Brooks
* \param x is the quantile and must be greater than 0.
* \param a is the shape parameter and must be positive.
* \param b is the rate parameter and must be positive.
* \return a dvariable object \f$ \Sigma_i (-a \ln(b_i)+\ln(\Gamma(a))-(a-1)\ln(x_i)+b_i x_i) \f$
* \sa
**/

dvariable dgamma( const dvector &x, const prevariable& a, const dvar_vector& b )
{
	//E(x)=a/b;
	//V(x)=a/b^2
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		if ( a<= 0 || b(i)<=0 )
		{
			cerr<<"a or b ("<<i<<") parameters are less than or equal to 0 in"
				"dgamma( const dvariable &x, const double a, const double b )\n";
			return 0;
		}
	}	
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		if ( x(i)<=0 )
		{
			cerr<<"The x ("<<i<<") parameter is less than or equal to 0 in"
				"dgamma( const dvariable &x, const double a, const double b )\n";
			return 0;
		}
	}
	return sum(-a*log(b)+gammln(a)-(a-1.)*log(x)+elem_prod(b, x));
}
/**
* \date 8/1/2011
* \author Mollie Brooks
* \param x is the quantile and must be greater than 0.
* \param a is the shape parameter and must be positive.
* \param b is the rate parameter and must be positive.
* \return a dvariable object \f$ \Sigma_i (-a_i \ln(b_i)+\ln(\Gamma(a_i))-(a_i-1)\ln(x_i)+b_i x_i) \f$
* \sa
**/

dvariable dgamma( const dvector &x, const dvar_vector& a, const dvar_vector& b )
{
	//E(x)=a/b;
	//V(x)=a/b^2
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		if ( a(i)<= 0 || b(i)<=0 )
		{
			cerr<<"a or b ("<<i<<") parameters are less than or equal to 0 in"
				"dgamma( const dvariable &x, const double a, const double b )\n";
			return 0;
		}
	}	
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		if ( x(i)<=0 )
		{
			cerr<<"The x ("<<i<<") parameter is less than or equal to 0 in"
				"dgamma( const dvariable &x, const double a, const double b )\n";
			return 0;
		}
	}
	return sum(-elem_prod(a, log(b))+gammln(a)-elem_prod((a-1.), log(x))+elem_prod(b, x));
}
/**
* \date 8/1/2011
* \author Mollie Brooks
* \param x is the quantile and must be greater than 0.
* \param a is the shape parameter and must be positive.
* \param b is the rate parameter and must be positive.
* \return a dvariable object \f$ \Sigma_i (-a_i \ln(b)+\ln(\Gamma(a_i))-(a_i-1)\ln(x_i)+b x_i) \f$
* \sa
**/

dvariable dgamma( const dvector &x, const dvar_vector& a, const prevariable& b )
{
	//E(x)=a/b;
	//V(x)=a/b^2
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		if ( a(i)<= 0 || b<=0 )
		{
			cerr<<"a or b ("<<i<<") parameters are less than or equal to 0 in"
				"dgamma( const dvariable &x, const double a, const double b )\n";
			return 0;
		}
	}	
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		if ( x(i)<=0 )
		{
			cerr<<"The x ("<<i<<") parameter is less than or equal to 0 in"
				"dgamma( const dvariable &x, const double a, const double b )\n";
			return 0;
		}
	}
	return sum(-a*log(b)+gammln(a)-elem_prod((a-1.), log(x))+b*x);
}

