#ifndef _STATSLIB_H_
#define _STATSLIB_H_

#include <fvar.hpp>
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 



dvar_matrix ageLengthKey( const dvar_vector& mu, const dvar_vector& sig, const dvector& x );
dmatrix ageLengthKey( const dvector& mu, const dvector& sig, const dvector& x );
dvar_matrix ALK(dvar_vector mu, dvar_vector sig, dvector x);

void fill( const dmatrix& _d,const dvector& _v );
void fill( const dvar_matrix& _d,const dvar_vector& _v );

double get_ft(const double& ct, const double& m, const dvector& va, const dvector& ba );
dvector get_ft( dvector& ct,const double& m, const dmatrix& V,const dvector& ba );
dvector get_ft( dvector& ct,const double& m, const dmatrix& V,const dvector& na, const dvector& wa );

dvector pearson_residuals(long m, dvector obs_p, dvector pred_p);

// DISTRIBUTION FUNCTIONS

// Uniform distribution
dvariable dunif( const dvariable& x, const double min, const double max );

// Student-t Distribution
dvariable dstudent_t( const dvar_vector& residual, const dvar_vector& df);

// Inverse gamma distribution
dvariable dinvgamma( const dvariable& x, const double a, const double b );

// Binomial distribution
dvariable dbinom( const prevariable& x,const double& n,const double& p );
dvariable dbinom( const prevariable& x,const prevariable& n,const double& p );
dvariable dbinom( const prevariable& x,const prevariable& n,const prevariable& p );
dvariable dbinom(const dvar_vector& x,const dvar_vector& n,const dvar_vector& p);
dvariable dbinom(const prevariable& x,const dvar_vector& n,const dvar_vector& p);
dvariable dbinom(const dvar_vector& x,const prevariable& n,const dvar_vector& p);
dvariable dbinom(const dvar_vector& x,const dvar_vector& n,const prevariable& p);
df1b2variable dbinom( const df1b2variable& x,const double& n,const double& p );
df1b2variable dbinom( const df1b2variable& x,const df1b2variable& n,const double& p );
df1b2variable dbinom( const df1b2variable& x,const df1b2variable& n,const df1b2variable& p );
df1b2variable dbinom(const df1b2vector& x,const df1b2vector& n,const df1b2vector& p);
df1b2variable dbinom(const df1b2variable& x,const df1b2vector& n,const df1b2vector& p);
df1b2variable dbinom(const df1b2vector& x,const df1b2variable& n,const df1b2vector& p);
df1b2variable dbinom(const df1b2vector& x,const df1b2vector& n,const df1b2variable& p);

// Negative binomial distribution
dvariable dnbinom(const double& x,const prevariable& mu, const prevariable& k);
df1b2variable dnbinom(const double& x, const df1b2variable& mu, const df1b2variable& k);
df1b2variable dnbinom(const dvector& x, const df1b2vector& mu, const df1b2variable& k);
df1b2variable dnbinom(const dvector& x, const df1b2vector& mu, const df1b2vector& k);
dvariable dnbinom(const dvector& x, const dvar_vector& mu, const prevariable& k);
dvariable dnbinom(const dvector& x, const dvar_vector& mu, const dvar_vector& k);

// Negative binomial distribution (other parametarization)
dvariable dnbinom_tau(const double& x,const prevariable& mu, const prevariable& tau);
df1b2variable dnbinom_tau(const double& x, const df1b2variable& mu, const df1b2variable& tau);
df1b2variable dnbinom_tau(const dvector& x, const df1b2vector& mu, const df1b2variable& tau);
df1b2variable dnbinom_tau(const dvector& x, const df1b2vector& mu, const df1b2vector& tau);
dvariable dnbinom_tau(const dvector& x, const dvar_vector& mu, const prevariable& tau);
dvariable dnbinom_tau(const dvector& x, const dvar_vector& mu, const dvar_vector& tau);

// Zero Inflated Negative binomial distribution
df1b2variable dzinbinom(const double& x, const df1b2variable& mu, const df1b2variable& k, const df1b2variable& p);
dvariable dzinbinom(const double& x, const prevariable& mu, const prevariable& k, const prevariable& p);
df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2variable& k, const df1b2variable& p);
df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2vector& k, const df1b2variable& p);
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const prevariable& k, const prevariable& p);
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const dvar_vector& k, const prevariable& p);
df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2variable& k, const df1b2vector& p);
df1b2variable dzinbinom(const dvector& x, const df1b2vector& mu, const df1b2vector& k, const df1b2vector& p);
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const prevariable& k, const dvar_vector& p);
dvariable dzinbinom(const dvector& x, const dvar_vector& mu, const dvar_vector& k, const dvar_vector& p);

// Gamma distribution
dvariable dgamma( const dvariable &x, const double& a, const double& b );
dvariable dgamma( const dvariable &x, const dvariable& a, const dvariable &b );
dvariable dgamma( const dvector &x, const prevariable& a, const prevariable& b );
dvariable dgamma( const dvector &x, const prevariable& a, const dvar_vector& b );
dvariable dgamma( const dvector &x, const dvar_vector& a, const dvar_vector& b );
dvariable dgamma( const dvector &x, const dvar_vector& a, const prevariable& b );

// Normal distribution
dvariable dnorm( const prevariable& x, const double& mu, const double& std );
dvariable dnorm( const dvar_vector& x, const double& mu, const double& std );
dvariable dnorm( const prevariable& x, const double& mu, const double& std, bool bLog );
dvariable dnorm( const dvector& x, const prevariable& mu, const prevariable& std );
dvariable dnorm( const dvector& x, const prevariable& mu, const prevariable& std, bool dLog );
dvariable dnorm( const dvar_vector& residual, const prevariable& std );
dvariable dnorm( const dvar_vector& residual, const double& std );
dvariable dnorm( const dvar_vector& residual, const dvector& std );
dvariable dnorm( const dvar_vector& residual, const dvar_vector std );
dvariable dnorm( const dvar_vector& residual );
dvariable dnorm( const dmatrix& obs, const dvar_matrix& pred );
df1b2variable dnorm( const df1b2variable& x, const double& mu, const double& std );
df1b2variable dnorm( const df1b2variable& x, const double& mu, const double& std, bool bLog );
df1b2variable dnorm( const df1b2variable& x, const df1b2variable& mu, const df1b2variable& std, bool bLog );
df1b2variable dnorm( const df1b2vector& x, const df1b2variable& mu, const df1b2variable& std, bool dLog );


// Plogis distribution
#ifndef LOGISTIC_HPP
#define LOGISTIC_HPP

template <typename T>
class plogisTraits;

template<>
class plogisTraits<double> {
public:
  typedef dvector plogisT;
};

template<>
class plogisTraits<named_dvariable> {
public:
  typedef dvar_vector plogisT;
};

template<>
class plogisTraits<dvariable> {
public:
  typedef dvar_vector plogisT;
};


template<typename T, typename T1>
inline
typename plogisTraits<T>::plogisT plogis(const T1 &x, const T &location, const T &scale)
{
  typedef typename plogisTraits<T>::plogisT plogisT;
  plogisT y = 1./(1.+mfexp((location - x) / scale));
  return (y);
}


// template <typename T1, typename T2>
// T1 plogis(T1 *x, T2 *location, T2 *scale)
// {
//   T1 y = 1./(1.+mfexp((*location - *x) / *scale));
//   return (y);
// }  

// template <typename T1, typename T2>
// T1 plogis(T1 x, T2 location, T2 scale)
// {
//   T1 y = 1./(1.+mfexp((location - x) / scale));
//   return (y);
// } 



#endif


// #include "plogis.hpp"
// template <typename T1, typename T2>
// T1 plogis(T1 *x, T2 *location, T2 *scale)
// {
//   T1 y = 1./(1.+mfexp((*location - *x) / *scale));
//   return (y);
// }  

// template <typename T1, typename T2>
// T1 plogis(T1 x, T2 location, T2 scale)
// {
//   T1 y = 1./(1.+mfexp((location - x) / scale));
//   return (y);
// } 

// template <typename T1, typename T2, typename T3>
// T1 plogis(T2 x, T3 location, T3 scale)
// {
//   T1 y = 1./(1.+mfexp((location - x) / scale));
//   //cout<<typeid(y)<<endl;
//   return (y);
// } 

// template class plogis<dvariable>;
// template class plogis<dvector>;
// template class plogis<dvar_vector>;
// template<typename T>
// class AccumulationTraits;
// template<>
// class AccumulationTraits<dvector> {
//   public:
//   typedef dvar_vector AccT;
// };
// template<>
// class AccumulationTraits<dvar_vector> {
//   public:
//   typedef dvector AccT;
// };

// template <typename T1, typename T2>
// typename AccumulationTraits<T1>::AccT plogis(  T1& x,  T2& location,  T2& scale )
// {
//   if( scale<=0 ) 
//   {
//     cerr<<"Standard deviation is less than or equal to zero in "
//     "plogis( const dvar_vector& x, const dvariable& location, "
//             "const dvariable& scale )\n";
//     return 0;
//   }
//   typedef typename AccumulationTraits<T1>::AccT AccT;
//   AccT logistic = 1./(1.+mfexp((location-x)/scale));
//   return (logistic);
// }  

// dvariable   plogis( const prevariable& x, const double& location, const double& scale );
// dvariable   plogis( const prevariable& x, const prevariable& location, const prevariable& scale );
// dvector     plogis( const dvector& x, const double& location, const double& scale );
// dvar_vector plogis( const dvector& x, const prevariable& location, const prevariable& scale );
// dvar_vector plogis( const dvar_vector& x, const prevariable& location, const prevariable& scale );

// Exponential logistic distribution
dvar_vector eplogis(const dvar_vector& x, const dvariable& alpha, const dvariable& beta, const dvariable& gamma);
dvector eplogis(const dvector& x, const double& alpha, const double& beta, const double& gamma);

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

// Multinomial distribution
dvariable dmultinom(const dvector& x, const dvar_vector& p);
// dvariable dmultinom(const dmatrix o, const dvar_matrix& p,dvar_matrix& nu,double& tau2,const double minp, double &neff);
dvariable dmultinom(const dmatrix o, const dvar_matrix& p,dvar_matrix& nu,double& tau2,const double minp);
double neff(const dvector& obs, const dvar_vector& pred);

// Multivariate logistic negative log likelihood
dvariable dmvlogistic(const dmatrix o, const dvar_matrix& p,dvar_matrix& nu, double& tau2,const double minp);
dvariable dmvlogistic(const dmatrix o, const dvar_matrix& p, double& tau2); // *deprecated*

// Random multivariate logistic negative log likelihood
dvector rmvlogistic(const dvector& p, const double& tau2, const int& seed);

// Robust normal approximation to the multinomial distribution
dvariable multifan(const dmatrix oprop,const dvar_matrix& pprop, const int& Nsamp);
dvariable multifan(const int& n, const dmatrix obs, const dvar_matrix pred,double& nef);
dvariable multifan(const double& s,const dvector obsQ,const dvar_vector& preQ, double& nmle);


// Spline class and functions
typedef vcubic_spline_function * pvcubic_spline_function;

/**
 * \brief A class for implementin cubic splines
 * \author Dave Fournier, Jim Ianelli, Steve Martell
 * \remarks
 * Uses cubic spline interpolation.
**/
class vcubic_spline_function_array
{
public:
	// GET methods
  int indexmin(void) {return index_min;}
  int indexmax(void) {return index_max;}

	// Constructors
  vcubic_spline_function_array(int,int,const dvector & x, const dvar_matrix& _y);
  vcubic_spline_function_array(const dvector & x);
  vcubic_spline_function_array(const vcubic_spline_function_array&);

	// Destructor
  ~vcubic_spline_function_array();

	// Operator overloads
	vcubic_spline_function & operator () (int i);
  dvar_matrix operator( ) (const dvector & v);

private:
  vcubic_spline_function ** ptr;
  int index_min;
  int index_max;
};

void bicubic_spline(const dvector& x, const dvector& y, dvar_matrix& knots, dvar_matrix& S);

dvar_vector cubic_spline(const dvar_vector& spline_nodes, const dvar_vector& ip);

dvariable splin2(const dvector& _x1a,const dvector& _x2a, const dvar_matrix _ya,dvar_matrix& _y2a, const double& x1,const double& x2);

dvar_matrix splie2(const dvector& _x1a,const dvector& _x2a,const dvar_matrix& _ya);

dvar_vector spline(const dvector &_x,const dvar_vector&_y,double yp1,double ypn);
dvariable splint(const dvector& _xa,const dvar_vector& _ya, const dvar_vector& _y2a,double x);

/**
* @file statsLib.h
* @brief Library of statistic functions
* \ingroup STATLIB
* \remarks
* This library contains declaratioins for
* numerous statistical functions
* that can be used in ADMB TPL files.
* 
* @author  Steve Martell, Chris Grandin, Mollie Brooks
* 
* @date 12/14/2011
*/



#endif

















