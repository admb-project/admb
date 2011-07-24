#include <fvar.hpp>
#include <admodel.h>

dvar_matrix ageLengthKey(const dvar_vector& mu, const dvar_vector& sig, const dvector& x);
dmatrix ageLengthKey(const dvector& mu, const dvector& sig, const dvector& x);
void fill(const dmatrix& _d,const dvector& _v);
void fill(const dvar_matrix& _d,const dvar_vector& _v);
double get_ft(const double& ct, const double& m, const dvector& va, const dvector& ba);
dvector get_ft( dvector& ct,const double& m, const dmatrix& V,const dvector& ba );
dvector get_ft( dvector& ct,const double& m, const dmatrix& V,const dvector& na, const dvector& wa );

// DISTRIBUTION FUNCTIONS
// Binomial distribution
dvariable dbinom(const prevariable& x,const double& n,const double& p);
dvariable dbinom(const prevariable& x,const prevariable& n,const double& p);
dvariable dbinom(const prevariable& x,const prevariable& n,const prevariable& p);
// Negative binomial distribution
dvariable dnbinom(const double& x,const prevariable& size, const prevariable& mu);
dvariable dnbinom(const dvector& x, const dvar_vector& lambda, const prevariable& tau, dvector& residual);
// Gamma distribution
dvariable dgamma( const dvariable &x, const double& a, const double& b );
dvariable dgamma( const dvariable &x, const dvariable& a, const dvariable &b );
dvariable prior_dgamma( const dvariable &x, const double& a, const double& b );
// Normal distribution
dvariable dnorm( const prevariable& x, const double& mu, const double& std );
dvariable dnorm( const dvar_vector& x, const double& mu, const double& std );
dvariable dnorm( const dvector& x, const prevariable& mu, const prevariable& std );
dvariable dnorm( const dvar_vector& residual, const prevariable& std );
dvariable dnorm( const dvar_vector& residual, const double& std );
dvariable dnorm( const dvar_vector& residual, const dvector& std );
dvariable dnorm( const dvar_vector& residual, const dvar_vector std );
// Plogis distribution
dvariable plogis( const prevariable& x, const double& location, const double& scale );
dvariable plogis( const prevariable& x, const prevariable& location, const prevariable& scale );
dvar_vector plogis( const dvector& x, const prevariable& location, const prevariable& scale );
dvector plogis( const dvector& x, const double& location, const double& scale );
dvar_vector plogis( const dvar_vector& x, const prevariable& location, const prevariable& scale );
// Beta distribution
dvariable dbeta( const dvariable& x, const double& shape1, const double& shape2 );
// Lognormal distribution
dvariable dlnorm( const prevariable& x, const double& mu, const double& std );
dvariable dlnorm( const prevariable& x, const prevariable& mu, const double& std );
dvariable dlnorm( const prevariable& x, const prevariable& mu, const prevariable& std );
dvariable dlnorm( const dvar_vector& x, const double& mu, const double& std );
dvariable dlnorm( const dvar_vector& x, const prevariable& mu, const double& std );
dvariable dlnorm( const dvar_vector& x, const prevariable& mu, const prevariable& std );
// Poisson distribution
dvariable dpois(const double& k, const prevariable& lambda);
dvariable dpois(const prevariable& k, const prevariable& lambda);

/**
* @file statsLib.h
* @brief Library of statistic functions
* \ingroup STATLIB
* This library contains numerous statistical functions
* that can easily be used in ADMB templates. This is the
* header file that contains preprocessor directive to 
* include all of the necessary files into the library.
* 
* @author Steven Martell
* 
* @date 2/05/2011
*
*
*
*
*
*/


