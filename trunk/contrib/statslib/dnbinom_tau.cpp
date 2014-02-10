#include "statsLib.h"
#include <df1b2fun.h>
#include <adrndeff.h> 


/** negative log likelihood of negative binomial with mean and tau 
\brief Negative binomial with mean=mu and variance = mu*tau
\author  Mollie Brooks
\param x observed count
\param mu is the predicted mean
\param tau is the overdispersion parameter like in the quasi-poisson. should be >1
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$ 
 where \f$ k=\mu/(10^{-120}+\tau-1.0) \f$
\ingroup STATLIB
**/
dvariable dnbinom_tau(const double& x, const prevariable& mu, const prevariable& tau)
{
	//x is the observed count
	//mu is the predicted mean
	//tau is the overdispersion parameter
	if (value(tau)<1.0)
	{
		cerr<<"tau is <=1.0 in dnbinom_tau()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	dvariable loglike;

	loglike =  log_negbinomial_density(x, mu, tau);

	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}

/** negative log likelihood of negative binomial with mean and tau 
\brief Negative binomial with mean=mu and variance = mu*tau
\author Mollie Brooks
\param x observed count
\param mu is the predicted mean
\param tau is the overdispersion parameter like in the quasi-poisson. should be >1
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
where \f$ k=\mu/(10^{-120}+\tau-1.0) \f$
\ingroup STATLIB
**/
df1b2variable dnbinom_tau(const double& x, const df1b2variable& mu, const df1b2variable& tau)
{
	//x is the observed count
	//mu is the predicted mean
	//tau is the overdispersion parameter
	if (value(tau)<1.0)
	{
		cerr<<"tau is <=1.0 in dnbinom_tau()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	df1b2variable loglike;
	loglike = log_negbinomial_density(x, mu, tau);

	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}

/** negative log likelihood of negative binomial with mean and tau 
\brief Negative binomial with mean=mu and variance = mu*tau
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param tau is the overdispersion parameter like in the quasi-poisson. should be >1
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
where \f$ k=\mu/(10^{-120}+\tau-1.0) \f$
\ingroup STATLIB
**/
df1b2variable dnbinom_tau(const dvector& x, const df1b2vector& mu, const df1b2variable& tau)
{
	//the observed counts are in x
	//mu is the predicted mean
	//tau is the overdispersion parameter
	if (value(tau)<1.0)
	{
		cerr<<"tau is <=1.0 in dnbinom_tau()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable loglike;
	loglike=0.;
	for(i = imin; i<=imax; i++)
	{	
		loglike += log_negbinomial_density(x(i), mu(i), tau);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean and tau 
\brief Negative binomial with mean=mu and variance = mu*tau
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param tau is the overdispersion parameter like in the quasi-poisson. should be >1
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
where \f$ k=\mu/(10^{-120}+\tau-1.0) \f$
\ingroup STATLIB
**/
df1b2variable dnbinom_tau(const dvector& x, const df1b2vector& mu, const df1b2vector& tau)
{
	//the observed counts are in x
	//mu is the predicted mean
	//tau is the overdispersion parameter

	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable loglike;
	loglike=0.;
 
	for(i = imin; i<=imax; i++)
	{
		if (value(tau(i))<1.0)
		{
			cerr<<"tau("<<i<<") is <=1.0 in dnbinom_tau()";
			return(0.0);
		}
		loglike += log_negbinomial_density(x(i), mu(i), tau(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean and tau 
\brief Negative binomial with mean=mu and variance = mu*tau
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param tau is the overdispersion parameter like in the quasi-poisson. should be >1
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
where \f$ k=\mu/(10^{-120}+\tau-1.0) \f$
\ingroup STATLIB
**/

dvariable dnbinom_tau(const dvector& x, const dvar_vector& mu, const prevariable& tau)
{
	//the observed counts are in x
	//mu is the predicted mean
	//tau is the overdispersion parameter
	if (value(tau)<1.0)
	{
		cerr<<"tau is <=1.0 in dnbinom_tau()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike = 0.;

	for(i = imin; i<=imax; i++)
	{
		loglike += log_negbinomial_density(x(i), mu(i), tau);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean and tau 
\brief Negative binomial with mean=mu and variance = mu*tau
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param tau is the overdispersion parameter like in the quasi-poisson. should be >1
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
where \f$ k=\mu/(10^{-120}+\tau-1.0) \f$
\ingroup STATLIB
**/
dvariable dnbinom_tau(const dvector& x, const dvar_vector& mu, const dvar_vector& tau)
{
	//the observed counts are in x
	//mu is the predicted mean
	//tau is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike;
	loglike=0.;

	for(i = imin; i<=imax; i++)
	{
		if (value(tau(i))<1.0)
		{
			cerr<<"tau("<<i<<") is <=1.0 in dnbinom_tau()";
			return(0.0);
		}
		
		loglike += log_negbinomial_density(x(i), mu(i), tau(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}


