#include "statsLib.h"

/**
* @file dbeta.cpp
* @brief Beta density functions.
* 
* This file contains the negative loglikelihood 
* functions for the beta distribution. The function
* dbeta is overloaded to accomodate single variables and vectors. 
* \ingroup STATLIB
* @author Steven Martell
* 
* @date 2/27/2011
* @remarks
* The general log density function is implemented as:
* \f[
* 	-\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)
* \f]
* where \f$a\f$ and \f$b\f$ are the shape parameters and \f$ x \f$ is the 
* quantile value that must lie between 0-1.
*/

/**
* @author Steven Martell
* @param shape1 = a parameter (a > 0)
* @param shape2 = b parameter (b > 0)
* 
* @remarks  x must greater than 0 and less than 1.  The
* mean is given by a/(a+b) and the variance ab/((a+b)^2(a+b+1)).
* 
* The log density function is implemented as:
* \f[
* 	-\ln(\Gamma(a+b)) +\ln(\Gamma(a)) + \ln(\Gamma(b))-(a-1)\ln(x)-(b-1)\ln(1-x)
* \f]
* 
*/
dvariable dbeta( const dvariable& x, const double& shape1, const double& shape2 )
{
	if( x<=0 || x>=1.0 )
	{
		cerr<<"x is <=0 or >=1.0 in "
			"dbeta( const dvariable& x, const double& shape1, const double& shape2 )\n";
		return 0;
	}
	
	if( shape1<=0 || shape2 <=0 )
	{
		cerr<<"shape1 or shape2 is <= 0 in "
			"dbeta( const dvariable& x, const double& shape1, const double& shape2 )\n";
		return 0;
	}
	
	double a=shape1;
	double b=shape2;
	return -1.* gammln(a+b)+(gammln(a)+gammln(b))-(a-1.)*log(x)-(b-1.)*log(1.-x);
}

dvariable dbeta( const dvariable& x, const dvariable& shape1, const dvariable& shape2 )
{
	if( x<=0 || x>=1.0 )
	{
		cerr<<"x is <=0 or >=1.0 in "
			"dbeta( const dvariable& x, const double& shape1, const double& shape2 )\n";
		return 0;
	}
	
	if( shape1<=0 || shape2 <=0 )
	{
		cerr<<"shape1 or shape2 is <= 0 in "
			"dbeta( const dvariable& x, const double& shape1, const double& shape2 )\n";
		return 0;
	}
	
	dvariable a=shape1;
	dvariable b=shape2;
	return -1.* gammln(a+b)+(gammln(a)+gammln(b))-(a-1.)*log(x)-(b-1.)*log(1.-x);
}


