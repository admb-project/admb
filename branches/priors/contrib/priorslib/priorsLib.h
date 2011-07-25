#include "statsLib.h"
#include <admodel.h>

/**
* 
* \file priorsLib.h
* \brief Prior distribution functions
* \ingroup STATLIB
* \author Chris Grandin
* \date 7/21/2011
* 
* 
* This file contains prior and likelihood wrappers for the contrib/statsLib library. 
* 
*/

/** 
	\author Chris Grandin
	\date 2011-07-21
	\sa
**/

// Binomial distribution
dvariable prior_dbinom(const prevariable& x,const double& n,const double& p);
dvariable prior_dbinom(const prevariable& x,const prevariable& n,const double& p);
dvariable prior_dbinom(const prevariable& x,const prevariable& n,const prevariable& p);
dvariable like_dbinom(const prevariable& x,const double& n,const double& p);
dvariable like_dbinom(const prevariable& x,const prevariable& n,const double& p);
dvariable like_dbinom(const prevariable& x,const prevariable& n,const prevariable& p);
// Negative binomial distribution
dvariable prior_dnbinom(const double& x,const prevariable& size, const prevariable& mu);
dvariable prior_dnbinom(const dvector& x, const dvar_vector& lambda, const prevariable& tau, dvector& residual);
dvariable like_dnbinom(const double& x,const prevariable& size, const prevariable& mu);
dvariable like_dnbinom(const dvector& x, const dvar_vector& lambda, const prevariable& tau, dvector& residual);
// Gamma distribution
dvariable prior_dgamma( const dvariable &x, const double& a, const double& b );
dvariable prior_dgamma( const dvariable &x, const dvariable& a, const dvariable &b );
dvariable like_dgamma( const dvariable &x, const double& a, const double& b );
dvariable like_dgamma( const dvariable &x, const dvariable& a, const dvariable &b );
// Normal distribution
dvariable prior_dnorm( const prevariable& x, const double& mu, const double& std );
dvariable prior_dnorm( const dvar_vector& x, const double& mu, const double& std );
dvariable prior_dnorm( const dvector& x, const prevariable& mu, const prevariable& std );
dvariable prior_dnorm( const dvar_vector& residual, const prevariable& std );
dvariable prior_dnorm( const dvar_vector& residual, const double& std );
dvariable prior_dnorm( const dvar_vector& residual, const dvector& std );
dvariable prior_dnorm( const dvar_vector& residual, const dvar_vector std );
dvariable like_dnorm( const prevariable& x, const double& mu, const double& std );
dvariable like_dnorm( const dvar_vector& x, const double& mu, const double& std );
dvariable like_dnorm( const dvector& x, const prevariable& mu, const prevariable& std );
dvariable like_dnorm( const dvar_vector& residual, const prevariable& std );
dvariable like_dnorm( const dvar_vector& residual, const double& std );
dvariable like_dnorm( const dvar_vector& residual, const dvector& std );
dvariable like_dnorm( const dvar_vector& residual, const dvar_vector std );
// Plogis distribution
dvariable prior_plogis( const prevariable& x, const double& location, const double& scale );
dvariable prior_plogis( const prevariable& x, const prevariable& location, const prevariable& scale );
dvar_vector prior_plogis( const dvector& x, const prevariable& location, const prevariable& scale );
dvector prior_plogis( const dvector& x, const double& location, const double& scale );
dvar_vector prior_plogis( const dvar_vector& x, const prevariable& location, const prevariable& scale );
dvariable like_plogis( const prevariable& x, const double& location, const double& scale );
dvariable like_plogis( const prevariable& x, const prevariable& location, const prevariable& scale );
dvar_vector like_plogis( const dvector& x, const prevariable& location, const prevariable& scale );
dvector like_plogis( const dvector& x, const double& location, const double& scale );
dvar_vector like_plogis( const dvar_vector& x, const prevariable& location, const prevariable& scale );
// Lognormal distribution
dvariable prior_dbeta( const dvariable& x, const double& shape1, const double& shape2 );
dvariable like_dbeta( const dvariable& x, const double& shape1, const double& shape2 );
// Lognormal distribution
dvariable prior_dlnorm( const prevariable& x, const double& mu, const double& std );
dvariable prior_dlnorm( const prevariable& x, const prevariable& mu, const double& std );
dvariable prior_dlnorm( const prevariable& x, const prevariable& mu, const prevariable& std );
dvariable prior_dlnorm( const dvar_vector& x, const double& mu, const double& std );
dvariable prior_dlnorm( const dvar_vector& x, const prevariable& mu, const double& std );
dvariable prior_dlnorm( const dvar_vector& x, const prevariable& mu, const prevariable& std );
dvariable like_dlnorm( const prevariable& x, const double& mu, const double& std );
dvariable like_dlnorm( const prevariable& x, const prevariable& mu, const double& std );
dvariable like_dlnorm( const prevariable& x, const prevariable& mu, const prevariable& std );
dvariable like_dlnorm( const dvar_vector& x, const double& mu, const double& std );
dvariable like_dlnorm( const dvar_vector& x, const prevariable& mu, const double& std );
dvariable like_dlnorm( const dvar_vector& x, const prevariable& mu, const prevariable& std );
// Poisson distribution
dvariable prior_dpois(const double& k, const prevariable& lambda);
dvariable prior_dpois(const prevariable& k, const prevariable& lambda);
dvariable like_dpois(const double& k, const prevariable& lambda);
dvariable like_dpois(const prevariable& k, const prevariable& lambda);
