//priors.cpp (taken from stats.cxx)
/*
	Statistical distributions commonly used in ADMB programs.
	Based on the documenation found in R.
	All distributions are in negative log-space.
	Author: Martell
	Date: 12/18/2007
*/


#include "fvar.hpp"
#include <admodel.h>

dvariable plogis(const dvariable& x, const double& mu, const dvariable& std)
{
	return 1./(1.+mfexp((mu-x)/std));
}
//dvariable prior_plogis(const dvariable& x, const double& mu, const dvariable& std){
//	return plogis(x,mu,std);
//}


dvar_vector plogis(const dvector& x, const dvariable& mu, const dvariable& std)
{
	return 1./(1.+mfexp((mu-x)/std));
}

dvector plogis(const dvector& x, const double& mu, const double& std)
{
	return 1./(1.+mfexp((mu-x)/std));
}

dvar_vector plogis(const dvar_vector& x, const dvariable& mu, const dvariable& std)
{
	return 1./(1.+mfexp((mu-x)/std));
}

//uniform distribution
dvariable dunif(const dvariable& x, const double min, const double max)
{
	return log(max-min);
}

dvariable dunif(const dvar_vector& x, const double min, const double max)
{
	return log(max-min);
}

//beta distribution
dvariable dbeta(const dvariable& x, const double a, const double b)
{
	return - gammln(a+b)+(gammln(a)+gammln(b))-(a-1.)*log(x)-(b-1.)*log(1.-x);
}

//inverse-gamma
dvariable dinvgamma(const dvariable& x, const double a, const double b)
{
	return -a*log(b)+gammln(a)+(a+1)*log(x)+b/x;
}

//gamma
dvariable dgamma(const dvariable &x, const double a, const double b)
{
	return -a*log(b)+gammln(a)-(a-1)*log(x)+b*x;
}

//normal distribution
dvariable dnorm(const dvariable& x, const double& mu, const double& std)
{
	return 0.5*log(2.*M_PI)+log(std)+0.5*square(x-mu)/(std*std);
}

dvariable dnorm(const dvar_vector& residual, const dvariable std)
{
	long n=size_count(residual);
	dvariable SS=norm2(residual);
	return(n*(0.5*log(2.*M_PI)+log(std))+0.5*SS/(std*std));
	//return(n*(0.5*log(2.*M_PI)-log(std))+0.5*SS*(std*std));
}

dvariable dnorm(const dvar_vector& residual, const dvector std)
{
	int n=size_count(residual);
	dvector var=elem_prod(std,std);
	dvar_vector SS=elem_prod(residual,residual);
	return(0.5*n*log(2.*M_PI)+sum(log(std))+sum(elem_div(SS,2.*var)));
}

dvariable dnorm(const dvar_vector& residual, const dvar_vector std)
{
	int n=size_count(residual);
	dvar_vector var=elem_prod(std,std);
	dvar_vector SS=elem_prod(residual,residual);
	return(0.5*n*log(2.*M_PI)+sum(log(std))+sum(elem_div(SS,2.*var)));
}


//log normal distribution
dvariable dlnorm(const dvariable& x, const double& mu, const double& std)
{
	return 0.5*log(2.*M_PI)+log(std)+log(x)+square(log(x)-mu)/(2.*std*std);
}

// log multinomial distribution
dvariable dmultinom(const dvector& x, const dvar_vector& p)
{
	double n=sum(x);
	return -gammln(n+1.)+sum(gammln(x+1.))-x*log(p/sum(p));
}

double neff(const dvector& obs, const dvar_vector& pred)
{
	dvector resid=value(obs-pred);
	dvector var=value(elem_prod(1.-pred,pred));
	return sum(var)/norm2(resid);
}

//poisson distribution
dvariable dpois(const double& x, const dvariable& lambda)
{
	return -x*log(lambda)+lambda+gammln(x+1);
}

// multivariate logistic negative log likelihood
dvariable dmvlogistic(const dmatrix o, const dvar_matrix& p, double& tau2)
{	//returns the negative loglikelihood using the MLE for the variance
	double tiny=1.e-10;
	int a = o.colmin();
	int A=o.colmax();
	int t=o.rowmin();
	int T=o.rowmax();
	dvariable tau_hat2;		//mle of the variance
	dvar_matrix nu(t,T,a,A);
	for(int i=t; i<=T; i++)
	{
		dvector o1=o(i)/sum(o(i));
		dvar_vector p1=p(i)/sum(p(i));
		//p1=log(p1)-mean(p1);
		p1=log(p1)-mean(log(p1));
		p1 = exp(p1)/sum(exp(p1));
		nu(i) = log(o1+tiny)-log(p1+tiny) - mean(log(o1+tiny)-log(p1+tiny));
	}
	tau_hat2 = 1./((A-a)*(T-t+1))*norm2(nu);
	dvariable nloglike =((A-a)*(T-t+1))*log(tau_hat2);
	tau2=value(tau_hat2); //mle of the variance

	return(nloglike);
}

//robust normal approximation to the multinomial distribution
dvariable multifan(const dmatrix oprop,const dvar_matrix& pprop, const int& Nsamp)
{	//Vivian Haist.
    dvariable extra=0.1/14.;
    dvar_matrix resid=elem_div((oprop-pprop),sqrt((elem_prod(pprop,1.-pprop)+extra)/Nsamp));
    return sum(0.5*log(elem_prod(pprop,1. -pprop)+extra) -log(mfexp(-0.5*elem_prod(resid,resid))+0.01));
}

dvariable multifan(const int& n, const dmatrix obs, const dvar_matrix pred,double& nef)
{
	int A=obs.colmax()-obs.colmin()+1;
	//dvar_matrix xi=(elem_prod(1.-pred,pred)+0.1/A)/n; //variance from Fourniers paper.
	dvar_matrix xi=(elem_prod(1.-obs,obs)+0.1/A)/n;	 //variance from the multifanCL manual.
	dvar_matrix resid=obs-pred;
	nef=value(sum(elem_prod(1.-pred,pred))/sum(elem_prod(resid,resid)));
	//cout<<"oh FUCK\t"<<nef<<endl;
	return sum(0.5*log(2.*M_PI*xi)-log(mfexp(-0.5*elem_div(elem_prod(resid,resid),xi))+0.01));
}

dvar_vector eplogis(const dvar_vector& x, const dvariable& alpha, const dvariable& beta, const dvariable& gamma)
{
	//exponential logistic based on Grant Thompson (1994) Paper, CJFAS.
	return (1./(1.-gamma))*pow((1.-gamma)/gamma,gamma)*elem_div(exp(alpha*gamma*(beta-x)),1.+exp(alpha*(beta-x)));
}

dvector eplogis(const dvector& x, const double& alpha, const double& beta, const double& gamma)
{
	//exponential logistic based on Grant Thompson (1994) Paper, CJFAS.
	return (1./(1.-gamma))*pow((1.-gamma)/gamma,gamma)*elem_div(exp(alpha*gamma*(beta-x)),1.+exp(alpha*(beta-x)));
}
