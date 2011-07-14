#include <admodel.h>

/**
* 
* \file dnbinom.cpp
* \brief Negative binomial density functions.
* \ingroup STATLIB
* \author Steven Martell
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
**/

dvariable dnbinom(const double& x,const prevariable& size, const prevariable& mu)
{
	if (value(size)<0.0)
	{
		cerr<<"size is <=0.0 in"
			"dnbinom(const double& x,const prevariable& mu, const prevariable& size)\n";
		return(0);
	}
	RETURN_ARRAYS_INCREMENT();
	dvariable p=size/(size+mu);
	dvariable tmp;
	tmp = gammln(x+size) - gammln(size) - factln(x)
		+size*log(p)+x*log(1.-p);
	RETURN_ARRAYS_DECREMENT();
	return(-tmp);
}



/** \brief A negative binomial likelihood for tagging data.
* 
* This is a special case of the negative binomial distribution used 
* primarily in the analysis of tagging data.  The likelihood is only evaluated
* in cases where the number of observations \f$x_i>0\f$.
	\author Steven James Dean Martell
	\date 2011-06-23
	\param  x a data vector of number of observations
	\param  lambda is the predicted number of observations
	\param  tau is the overdispersion parameter
	\param residual is a modified vector of standardized residuals
	\return returns the negative loglikelihood of the normal distribution
	\sa
**/
dvariable dnbinom(const dvector& x, const dvar_vector& lambda, const prevariable& tau, dvector& residual)
{
	//the observed counts are in x
	//lambda is the predicted count
	//tau is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	double o=1.e-30;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike=0.;
	residual.initialize();

	for(i = imin; i<=imax; i++)
		if(x(i)>0){
			dvariable p=tau/(tau+lambda(i));
			loglike += gammln(tau+x(i)) - gammln(tau) -factln(x(i))
								+tau*log(p) + x(i)*log(1.-p);
			residual(i) =value((x(i)-lambda(i))
						/sqrt(o+lambda(i)+square(lambda(i))/tau)) ;
		}
	//cout<<"OK in dnbinom"<<endl;
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}