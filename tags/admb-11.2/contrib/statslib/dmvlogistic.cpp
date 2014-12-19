#include "statsLib.h"

/**
* @file dmvlogistic.cpp
* @brief Multivariate logistic negative log likelihood
* 
* This file contains the Multivariate logistic negative log likelihood functions
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/13/2011
* @remarks
*/

dvariable dmvlogistic(const dmatrix o, const dvar_matrix& p,dvar_matrix& nu, double& tau2,const double minp)
{	//returns the negative loglikelihood using the MLE for the variance
	/*
		This is a modified version of the dmvlogistic negative log likelihood
		where proportions at age less than minp are pooled into the consecutive
		age-classes.  See last paragraph in Appendix A of Richards, Schnute and
		Olsen 1997.

		NB minp must be greater than 0, otherwise this algorithm returns an
		error if one of the observed proportions is zero.

		-1) first count the number of observations for each year > minp
		-2) normalized observed and predicted age-proportions
		-3) loop over ages, and check if observed proportion is < minp
				-if yes, then add observed proprtion to bin k
				-if no then add observed proportion to bin k and increment
				 bin k if k is currently less than the number of bins.
		-4) do the same grouping for the predicted proportions.
		-5) use ivector iiage to correctly assign residuals into nu

		FEB 8, 2011.  Fixed a bug in the variance calculation &
		likelihood scaling that was discovered at the 2011 Hake
		assessment STAR panel in Seattle.
	*/
	RETURN_ARRAYS_INCREMENT();
	int i,j,k,n;
	int age_counts=0;
	int a = o.colmin();
	int A=o.colmax();
	double tiny=0.001/(A-a+1);
	int t=o.rowmin();
	int T=o.rowmax();
	dvariable tau_hat2;		//mle of the variance
	//dvar_matrix nu(t,T,a,A);
	nu.initialize();

	for(i=t; i<=T; i++)
	{
		n=0;
		dvector oo = o(i)/sum(o(i));
		dvar_vector pp = p(i)/sum(p(i));

		//count # of observations greater than minp (2% is a reasonable number)
		for(j=a;j<=A;j++)
			if(oo(j) > minp)n++;

		ivector iiage(1,n);
		dvector o1(1,n); o1.initialize();
		dvar_vector p1(1,n); p1.initialize();
		k=1;
		for(j=a;j<=A;j++)
		{
			if(oo(j)<=minp)
			{
				o1(k)+=oo(j);
				p1(k)+=pp(j);
			}
			else
			{
				o1(k)+=oo(j);
				p1(k)+=pp(j);
				if(k<=n)iiage(k)=j;		//ivector for the grouped residuals
				if(k<n) k++;
			}
		}

		//assign residuals to nu based on iiage index
		dvar_vector t1 = log(o1)-log(p1) - mean(log(o1)-log(p1));

		for(j=1;j<=n;j++)
			nu(i)(iiage(j))=t1(j);

		age_counts += n-1;
	}
	//Depricated  Wrong Variance & likelihood calculation.
	//tau_hat2 = 1./(age_counts*(T-t+1))*norm2(nu);
	//dvariable nloglike =(age_counts*(T-t+1))*log(tau_hat2);

	//Feb 8, 2011  Fixed variance & likelihood
	tau_hat2 = 1./(age_counts)*norm2(nu);
	dvariable nloglike =(age_counts)*log(tau_hat2);
	tau2=value(tau_hat2); //mle of the variance
	RETURN_ARRAYS_DECREMENT();
	return(nloglike);
}

//The following function has been depricated.
dvariable dmvlogistic(const dmatrix o, const dvar_matrix& p, double& tau2)
{

	//returns the negative loglikelihood using the MLE for the variance
	RETURN_ARRAYS_INCREMENT();

	int a = o.colmin();
	int A=o.colmax();
	double tiny=0.001/(A-a+1);
	int t=o.rowmin();
	int T=o.rowmax();
	dvariable tau_hat2;		//mle of the variance
	dvar_matrix nu(t,T,a,A);
	for(int i=t; i<=T; i++)
	{
		dvector o1=o(i)/sum(o(i));
		dvar_vector p1=p(i)/sum(p(i));
		//p1=log(p1)-mean(p1);
		//p1=log(p1)-mean(log(p1));
		//p1 = exp(p1)/sum(exp(p1));
		nu(i) = log(o1+tiny)-log(p1+tiny) - mean(log(o1+tiny)-log(p1+tiny));
	}
	tau_hat2 = 1./((A-a)*(T-t+1))*norm2(nu);
	dvariable nloglike =((A-a)*(T-t+1))*log(tau_hat2);
	tau2=value(tau_hat2); //mle of the variance
	RETURN_ARRAYS_DECREMENT();
	return(nloglike);
}

