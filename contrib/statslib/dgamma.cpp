#include <admodel.h>
/**
* \file dgamma.cpp
* \brief Gamma density functions.
* \ingroup pdf
* \author Steven Martell
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
* 	a = \frac{E(x)^2}{V(x)}, \quad b=\frac{E(x)}{V(x)}
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



