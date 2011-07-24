#include "priorsLib.h"

/**
* 
* \file priorsLib.cpp
* \brief Prior distribution functions
* \ingroup STATLIB
* \author Chris Grandin
* \date 7/21/2011
* 
* 
* This file contains 'prior' wrappers for the contrib/statsLib library. 
* 
*/

/** 
	\author Chris Grandin
	\date 2011-07-21
	\sa
**/

// Binomial distribution
dvariable prior_dbinom(const prevariable& x,const double& n,const double& p){return(dbinom(x,n,p));}
dvariable prior_dbinom(const prevariable& x,const prevariable& n,const double& p){return(dbinom(x,n,p));}
dvariable prior_dbinom(const prevariable& x,const prevariable& n,const prevariable& p){return(dbinom(x,n,p));}
// Negative binomial distribution
dvariable prior_dnbinom(const double& x,const prevariable& size, const prevariable& mu){return(dnbinom(x,size,mu));}
dvariable prior_dnbinom(const dvector& x, const dvar_vector& lambda, const prevariable& tau, dvector& residual){return(dnbinom(x,lambda,tau,residual));}
// Gamma distribution
dvariable prior_dgamma( const dvariable &x, const double& a, const double& b ){return(dgamma(x,a,b));}
dvariable prior_dgamma( const dvariable &x, const dvariable& a, const dvariable &b ){return(dgamma(x,a,b));}
// Normal distribution
dvariable prior_dnorm( const prevariable& x, const double& mu, const double& std ){return(dnorm(x,mu,std));}
dvariable prior_dnorm( const dvar_vector& x, const double& mu, const double& std ){return(dnorm(x,mu,std));}
dvariable prior_dnorm( const dvector& x, const prevariable& mu, const prevariable& std ){return(dnorm(x,mu,std));}
dvariable prior_dnorm( const dvar_vector& residual, const prevariable& std ){return(dnorm(residual,std));}
dvariable prior_dnorm( const dvar_vector& residual, const double& std ){return(dnorm(residual,std));}
dvariable prior_dnorm( const dvar_vector& residual, const dvector& std ){return(dnorm(residual,std));}
dvariable prior_dnorm( const dvar_vector& residual, const dvar_vector std ){return(dnorm(residual,std));}
// Plogis distribution
dvariable prior_plogis( const prevariable& x, const double& location, const double& scale ){return(plogis(x,location,scale));}
dvariable prior_plogis( const prevariable& x, const prevariable& location, const prevariable& scale ){return(plogis(x,location,scale));}
dvar_vector prior_plogis( const dvector& x, const prevariable& location, const prevariable& scale ){return(plogis(x,location,scale));}
dvector prior_plogis( const dvector& x, const double& location, const double& scale ){return(plogis(x,location,scale));}
dvar_vector prior_plogis( const dvar_vector& x, const prevariable& location, const prevariable& scale ){return(plogis(x,location,scale));}
// Lognormal distribution
dvariable prior_dbeta( const dvariable& x, const double& shape1, const double& shape2 ){return(dbeta(x,shape1,shape2));}
// Lognormal distribution
dvariable prior_dlnorm( const prevariable& x, const double& mu, const double& std ){return(dlnorm(x,mu,std));}
dvariable prior_dlnorm( const prevariable& x, const prevariable& mu, const double& std ){return(dlnorm(x,mu,std));}
dvariable prior_dlnorm( const prevariable& x, const prevariable& mu, const prevariable& std ){return(dlnorm(x,mu,std));}
dvariable prior_dlnorm( const dvar_vector& x, const double& mu, const double& std ){return(dlnorm(x,mu,std));}
dvariable prior_dlnorm( const dvar_vector& x, const prevariable& mu, const double& std ){return(dlnorm(x,mu,std));}
dvariable prior_dlnorm( const dvar_vector& x, const prevariable& mu, const prevariable& std ){return(dlnorm(x,mu,std));}
// Poisson distribution
dvariable prior_dpois(const double& k, const prevariable& lambda){return(k,lambda);}
dvariable prior_dpois(const prevariable& k, const prevariable& lambda){return(k,lambda);}
