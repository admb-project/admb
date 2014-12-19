#include <df1b2fun.h>
#include <adrndeff.h> 
/** negative log likelihood of negative binomial with mean=mu and variance = mu + mu^2 /k 
\brief Negative binomial with mean and quadratic variance
\author Steven Martell and Mollie Brooks
\param x observed count
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying gamma heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
dvariable dnbinom(const double& x, const prevariable& mu, const prevariable& k)
{
	//x is the observed count
	//mu is the predicted mean
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dnbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	dvariable loglike;

	loglike = gammln(k+x)-gammln(k)-gammln(x+1)+k*log(k)-k*log(mu+k)+x*log(mu)-x*log(mu+k);

	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}

/** negative log likelihood of negative binomial with mean=mu and variance = mu + mu^2 /k 
\brief Negative binomial with mean and quadratic variance
\author Mollie Brooks
\param x observed count
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying gamma heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
df1b2variable dnbinom(const double& x, const df1b2variable& mu, const df1b2variable& k)
{
	//x is the observed count
	//mu is the predicted mean
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dnbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	df1b2variable loglike;
	loglike = gammln(k+x)-gammln(k)-gammln(x+1)+k*log(k)-k*log(mu+k)+x*log(mu)-x*log(mu+k);

	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}

/** negative log likelihood of negative binomial with mean=mu and variance = mu + mu^2 /k 
\brief Negative binomial with mean and quadratic variance
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying gamma heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
df1b2variable dnbinom(const dvector& x, const df1b2vector& mu, const df1b2variable& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dnbinom()";
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
		loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean=mu and variance = mu + mu^2 /k 
\brief Negative binomial with mean and quadratic variance
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying gamma heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
df1b2variable dnbinom(const dvector& x, const df1b2vector& mu, const df1b2vector& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter

	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable loglike;
	loglike=0.;
 
	for(i = imin; i<=imax; i++)
	{
		if (value(k(i))<0.0)
		{
			cerr<<"k("<<i<<") is <=0.0 in dnbinom()";
			return(0.0);
		}
		loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean=mu and variance = mu + mu^2 /k 
\brief Negative binomial with mean and quadratic variance
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying gamma heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/

dvariable dnbinom(const dvector& x, const dvar_vector& mu, const prevariable& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dnbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike = 0.;

	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** negative log likelihood of negative binomial with mean=mu and variance = mu + mu^2 /k 
\brief Negative binomial with mean and quadratic variance
\author Mollie Brooks
\param x observed counts
\param mu is the predicted mean
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying gamma heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\mu)-(k+x)\ln(k+\mu) )\f$
\ingroup STATLIB
**/
dvariable dnbinom(const dvector& x, const dvar_vector& mu, const dvar_vector& k)
{
	//the observed counts are in x
	//mu is the predicted mean
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike;
	loglike=0.;

	for(i = imin; i<=imax; i++)
	{
		if (value(k(i))<0.0)
		{
			cerr<<"k("<<i<<") is <=0.0 in dnbinom()";
			return(0.0);
		}
		
		loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}


