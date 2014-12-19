 #include "statsLib.h"

/**
* @file logistic.cpp
* @brief Logistic distrutions and densities.
* \ingroup STATLIB
* Density and distribution functions for the logistic 
* distribution.  Common use is plogis for obtaining 
* logistic selectivity curves based on location and 
* scale parameters.
* The function is implemented as:
* \f[
* 	\frac{1}{1-\exp(-(x-location)/scale)}
* \f]
* 
* @author Steven Martell
* 
* @date 2/26/2011
*/


/**
* \author Steven Martell
* \param x is a quantile.
* \param location is where 50% percentile occurs.
* \param scale determines in the standard deviation of the distribution.
* 
* \return Function returns a dvariable.
*/
dvariable plogis( const prevariable& x, const double& location, const double& scale )
{
	if( scale<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"plogis( const dvariable& x, const double& location, const double& scale )\n";
		return 0;
	}
	return 1./(1.+mfexp((location-x)/scale));
}

/**
* \author Steven Martell
* \param x is a quantile.
* \param location is where 50% percentile occurs.
* \param scale determines in the standard deviation of the distribution.
* 
* \return Function returns a dvariable.
*/
dvariable plogis( const prevariable& x, const prevariable& location, const prevariable& scale )
{
	if( scale<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"plogis( const dvariable& x, const dvariable& location, const dvariable& scale )\n";
		return 0;
	}
	return 1./(1.+mfexp((location-x)/scale));
}

/**
* \author Steven Martell
* \param x is a vector of quantiles.
* \param location is where 50% percentile occurs.
* \param scale determines in the standard deviation of the distribution.
* 
* \return a variable vector
*/
dvar_vector plogis( const dvector& x, const prevariable& location, const prevariable& scale )
{
	if( scale<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"plogis( const dvector& x, const dvariable& location, const dvariable& scale )\n";
		return 0;
	}
	return 1./(1.+mfexp((location-x)/scale));
}

/**
* \author Steven Martell
* \param x is a vector of quantiles.
* \param location is where 50% percentile occurs.
* \param scale determines in the standard deviation of the distribution.
* 
* \return a variable vector
*/
dvector plogis( const dvector& x, const double& location, const double& scale )
{
	if( scale<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"plogis( const dvector& x, const double& location, const double& scale )\n";
		return 0;
	}
	return 1./(1.+mfexp((location-x)/scale));
}

/**
* \author Steven Martell
* \param x is a vector of quantiles.
* \param location is where 50% percentile occurs.
* \param scale determines in the standard deviation of the distribution.
* 
* \return a variable vector
*/
dvar_vector plogis( const dvar_vector& x, const prevariable& location, const prevariable& scale )
{
	if( scale<=0 ) 
	{
		cerr<<"Standard deviation is less than or equal to zero in "
		"plogis( const dvar_vector& x, const dvariable& location, const dvariable& scale )\n";
		return 0;
	}
	return 1./(1.+mfexp((location-x)/scale));
}

/**
* Template function for plogis
* \author Steven Martell
* \param x is a vector of quantiles.
* \param location is where 50% percentile occurs.
* \param scale determines in the standard deviation of the distribution.
* 
* \return a template vector
*/
// template <typename T1, typename T2>
// T1 plogis( const T1& x, const T2& location, const T2& scale )
// {
// 	if( scale<=0 ) 
// 	{
// 		cerr<<"Standard deviation is less than or equal to zero in "
// 		"plogis( const dvar_vector& x, const dvariable& location, const dvariable& scale )\n";
// 		return 0;
// 	}
// 	return 1./(1.+mfexp((location-x)/scale));
// } 
