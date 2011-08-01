//Ecological parametarization of the negative log likelihood distribution
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\lambda)-(k+x)\ln(k+\lambda) )\f$
**/
df1b2variable dnbinom_eco(const dvector& x, const df1b2vector& lambda, const df1b2variable& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable loglike;
	loglike=0.;
	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\lambda)-(k+x)\ln(k+\lambda) )\f$
**/
df1b2variable dnbinom_eco(const dvector& x, const df1b2vector& lambda, const df1b2vector& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	df1b2variable loglike;
	loglike=0.;
 
	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\lambda)-(k+x)\ln(k+\lambda) )\f$
**/

dvariable dnbinom_eco(const dvector& x, const dvar_vector& lambda, const prevariable& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike = 0.;

	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\return negative log likelihood \f$ -( \ln(\Gamma(x+k))-\ln(\Gamma(k))-\ln(x!)+k\ln(k)+x\ln(\lambda)-(k+x)\ln(k+\lambda) )\f$
**/
dvariable dnbinom_eco(const dvector& x, const dvar_vector& lambda, const dvar_vector& k)
{
	//the observed counts are in x
	//lambda is the predicted count
	//k is the overdispersion parameter
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike;
	loglike=0.;

	for(i = imin; i<=imax; i++)
	{
		loglike += gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}