//0<p<1
//0<k
//0<=x
//Aug 1, 2011
//Mollie Brooks
#include <df1b2fun.h>
#include <adrndeff.h> 

/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed count. should be greater than or equal to 0.
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/

df1b2variable dzinbinom(const double& x, const df1b2variable& mu, const df1b2variable& k, const df1b2variable& p)
{
	//the observed counts are in x
	//mu is the predicted count
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dzinbinom()";
		return(0.0);
	}
	
	RETURN_ARRAYS_INCREMENT();
	df1b2variable loglike;
	if(x==0)
	{
		loglike=log(p + (1-p)* pow(k/(k+mu),k) );
	}
	else//x(i)>0
	{
		loglike=log(1-p) + gammln(k+x)-gammln(k)-gammln(x+1)+k*log(k)-k*log(mu+k)+x*log(mu)-x*log(mu+k);
		
	}

	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed count. should be greater than or equal to 0.
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/

dvariable dzinbinom(const double& x, const prevariable& mu, const prevariable& k, const prevariable& p)
{
	//the observed counts are in x
	//mu is the predicted count
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dzinbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	dvariable loglike;
	if(x==0)
	{
		loglike=log(p + (1-p)* pow(k/(k+mu),k) );
	}
	else//x(i)>0
	{
		loglike=log(1-p) + gammln(k+x)-gammln(k)-gammln(x+1)+k*log(k)-k*log(mu+k)+x*log(mu)-x*log(mu+k);
	}

	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts. should be greater than or equal to 0.
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/

df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2variable& k, const df1b2variable& p)
{
	//the observed counts are in x
	//mu is the predicted count
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dzinbinom()";
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
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k/(k+mu(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/
df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2vector& k, const df1b2variable& p)
{
	//the observed counts are in x
	//mu is the predicted count
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
			cerr<<"k("<<i<<") is <=0.0 in dzinbinom()";
			return(0.0);
		}
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k(i)/(k(i)+mu(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const prevariable& k, const prevariable& p)
{
	//the observed counts are in x
	//mu is the predicted count
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dzinbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike = 0.;

	for(i = imin; i<=imax; i++)
	{
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k/(k+mu(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const dvar_vector& k, const prevariable& p)
{
	//the observed counts are in x
	//mu is the predicted count
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
			cerr<<"k("<<i<<") is <=0.0 in dzinbinom()";
			return(0.0);
		}
		if(x(i)==0)
		{
			loglike+=log(p + (1-p)* pow(k(i)/(k(i)+mu(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
////////////////////////
/// now p is a vector///
////////////////////////
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/
df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2variable& k, const df1b2vector& p)
{
	//the observed counts are in x
	//mu is the predicted count
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dzinbinom()";
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
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k/(k+mu(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/
df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2vector& k, const df1b2vector& p)
{
	//the observed counts are in x
	//mu is the predicted count
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
			cerr<<"k("<<i<<") is <=0.0 in dzinbinom()";
			return(0.0);
		}
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k(i)/(k(i)+mu(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const prevariable& k, const dvar_vector& p)
{
	//the observed counts are in x
	//mu is the predicted count
	//k is the overdispersion parameter
	if (value(k)<0.0)
	{
		cerr<<"k is <=0.0 in dzinbinom()";
		return(0.0);
	}
	RETURN_ARRAYS_INCREMENT();
	int i,imin,imax;
	imin=x.indexmin();
	imax=x.indexmax();
	dvariable loglike = 0.;

	for(i = imin; i<=imax; i++)
	{
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k/(k+mu(i)),k) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k+x(i))-gammln(k)-gammln(x(i)+1)+k*log(k)-k*log(mu(i)+k)+x(i)*log(mu(i))-x(i)*log(mu(i)+k);
			
		}
	}	
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
/** ecologically parametarized negative binomial with zero inflation
\brief Zero Inflated Negative binomial with size and mean
\author Mollie Brooks
\param x observed counts
\param mu is the mean of the negative binomial part
\param k is the overdispersion parameter, i.e. size, i.e. shape parameter of underlying heterogeneity (different from tau). should be >0
\param p is the zero inflation paramerer, i.e. extra chance of observing zeros. 0<p<1.  
\return negative log-likelihood
\ingroup STATLIB
**/
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const dvar_vector& k, const dvar_vector& p)
{
	//the observed counts are in x
	//mu is the predicted count
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
			cerr<<"k("<<i<<") is <=0.0 in dzinbinom()";
			return(0.0);
		}
		if(x(i)==0)
		{
			loglike+=log(p(i) + (1-p(i))* pow(k(i)/(k(i)+mu(i)),k(i)) );
		}
		else//x(i)>0
		{
			loglike+=log(1-p(i)) + gammln(k(i)+x(i))-gammln(k(i))-gammln(x(i)+1)+k(i)*log(k(i))-k(i)*log(mu(i)+k(i))+x(i)*log(mu(i))-x(i)*log(mu(i)+k(i));
			
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return(-loglike);
}
