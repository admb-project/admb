//Soon I plan to allow k to be a vector and add checking
//0<p<1
//0<k
//0<x
//Aug 1, 2011
//Mollie Brooks
#include "statsLib.h"
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts. should be >0.
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/

df1b2variable dnbinom_eco_zi(const dvector& x, const df1b2vector& lambda, const df1b2variable& k, const df1b2variable& p)
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
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k/(k+lambda(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/
df1b2variable dnbinom_eco_zi(const dvector& x, const df1b2vector& lambda, const df1b2vector& k, const df1b2variable& p)
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
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k(i)/(k(i)+lambda(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/
dvariable dnbinom_eco_zi(const dvector& x, const dvar_vector& lambda, const prevariable& k, const prevariable& p)
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
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k/(k+lambda(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/
dvariable dnbinom_eco_zi(const dvector& x, const dvar_vector& lambda, const dvar_vector& k, const prevariable& p)
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
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k(i)/(k(i)+lambda(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
////////////////////////
/// now p is a vector///
////////////////////////
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/
df1b2variable dnbinom_eco_zi(const dvector& x, const df1b2vector& lambda, const df1b2variable& k, const df1b2vector& p)
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
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k/(k+lambda(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/
df1b2variable dnbinom_eco_zi(const dvector& x, const df1b2vector& lambda, const df1b2vector& k, const df1b2vector& p)
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
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k(i)/(k(i)+lambda(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/
dvariable dnbinom_eco_zi(const dvector& x, const dvar_vector& lambda, const prevariable& k, const dvar_vector& p)
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
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k/(k+lambda(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(lambda(i)+k)+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k);
			
		}
	}	
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\author Mollie Brooks
\param x observed counts
\param lambda is the predicted mean
\param k is the overdispersion parameter, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log likelihood
**/
dvariable dnbinom_eco_zi(const dvector& x, const dvar_vector& lambda, const dvar_vector& k, const dvar_vector& p)
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
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k(i)/(k(i)+lambda(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(lambda(i)+k(i))+x(i)*log(lambda(i))-x(i)*log(lambda(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
