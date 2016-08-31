
 /**
  * \file	qfc_sim.h
  * \brief functions useful for simulation model in admb
  * \date 7/28/2011
  * \author Weihai Liu
  * \ingroup QFC
  *
  *  Following user defined functions are more useful for doing simulation model in admb,
  *  the easy way to use these functions is with your tpl file
  *  under the GLOBALS_SECTION , add a line on top as	#include "qfclib.h",
  *  there is a testfunction.tpl file within this folder show how to use these functions.
  *
  *  ================  brief list for usage  ============================\n
  *  1. return some values for the specific variable name in admb ouput file,
  *	such as find the parameter value and its std value from .std file,
  *	use findValFromFile("test.std","linf",2), see findValFromFile()  \n
  *  2. doing random sampling with or without replacement, see sample()  \n
  *  3. remove the duplicate values from a vector, see unique()  \n
  *  4. several random number generator, runif(), rnorm(), rgamma(), rdirichlet() \n
  *  5. convert vector to matrix by row or by column or its reverse form,
  *	see matrix2vector(), vector2matrix() \n
  *  =============================================================\n
  *
  *  Update: Oct 8, 2015  (N.Dobiesz) \n
  *  Error found in Inverse Gamma NLL functions \n
  *	function was: nll= - a*log(b)+gammln(a)-(a-1.)*log(x+EPS) + b/(x+EPS); \n
  *	changed to: nll=   - a*log(b)+gammln(a)+(a+1.)*log(x+EPS) + b/(x+EPS); \n
  *
  *  If you encounter an error, contact the Quantitative Fisheries Center(QFC) at \n
  *  Michigan State University at qfc@msu.edu \n

  */

#ifndef _QFCLIB_H_
#define _QFCLIB_H_

#include <math.h>
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>
// define constant variable
const double EPS = 1.e-20;
const double QFC_M_E= 1.e-20;

//function defined for simulation model
int		numRows4VarFromFile (adstring filename, adstring varName);
dmatrix 	findValFromFile (adstring filename, adstring varName, int numVals);
dvector 	unique (const dvector &in);
ivector 	sample (const dvector &source, int nSample, int withReplace, const random_number_generator &rng);
dvector 	matrix2vector (const dmatrix &input, int byrow);
dvar_vector	matrix2vector (const dvar_matrix &input, int byrow);
df1b2vector	matrix2vector (const df1b2matrix &input, int byrow);
dmatrix 	vector2matrix (dvector &input, int nrow, int ncol, int byrow);
df1b2matrix	vector2matrix (df1b2vector &input, int nrow, int ncol, int byrow);
dvar_matrix	vector2matrix (const dvar_vector &input, int nrow, int ncol, int byrow);
bool		doubleEqual (double nVal1, double nVal2, int nPrecision);
double		runif (double low, double upper, random_number_generator &rng);
double		rnorm (double mu, double sigma, random_number_generator &rng);
double rlnorm(double mu, double sigma, random_number_generator & rng);
double		rgamma (double alpha, random_number_generator &rng);
double		rgamma (double alpha, double beta, random_number_generator &rng);
double rbeta(double alpha, double beta, random_number_generator& rng);
dvector 	rdirichlet (const dvector &shape, random_number_generator &rng);

//function defined for estimation model
dvar_vector	logitProp (const dvar_vector &a);
df1b2vector	logitProp (const df1b2vector &a);
dvar_vector	invLogitProp (const dvar_vector &p);
df1b2vector	invLogitProp (const df1b2vector &p);
dvar_vector	normalize_p (dvar_vector &p, dvariable fpen);
df1b2vector	normalize_p (df1b2vector &p, df1b2variable fpen);
dvar_vector	posfun (dvar_vector &x, const dvector &eps, dvariable &pen);
df1b2vector	posfun (df1b2vector &x, const dvector &eps, df1b2variable &pen);
dvar_matrix	posfun (dvar_matrix &x, const dmatrix &eps, dvariable &pen);
df1b2matrix	posfun (df1b2matrix &x, const dmatrix &eps, df1b2variable &pen);
dvariable	mf_upper_bound2 (const dvariable &x, const double fmax, dvariable &fpen);
df1b2variable	mf_upper_bound2 (const df1b2variable &x, const double fmax, df1b2variable &fpen);
dvar_vector	boundp (const dvar_vector &x, const double fmin, const double fmax, const dvariable &fpen);
df1b2vector	boundp (const df1b2vector &x, const double fmin, const double fmax, const df1b2variable &fpen);
df1b2vector	log_comb (const df1b2vector &n, const df1b2vector &x);
df1b2vector	log_comb (const df1b2vector &n, const dvector &x);
df1b2vector	log_comb (const dvector &n, const df1b2vector &x);
double	nllNegativeBinomial (const double obs, const double m, const double s);
dvariable	nllNegativeBinomial (const dvariable &obs, const double m, const double s);
dvariable	nllNegativeBinomial (const double obs, const dvariable &m, const dvariable &s);
dvariable	nllNegativeBinomial (const dvariable &obs, const dvariable &m, const double s);
dvariable	nllNegativeBinomial (const dvariable &obs, const double m, const dvariable &s);
dvariable	nllNegativeBinomial (const dvariable &obs, const dvariable &m, const dvariable &s);
df1b2variable	nllNegativeBinomial (const df1b2variable &obs, const double m, const double s);
df1b2variable	nllNegativeBinomial (const double obs, const df1b2variable &m, const df1b2variable &s);
df1b2variable	nllNegativeBinomial (const df1b2variable &obs, const df1b2variable &m, const double s);
df1b2variable	nllNegativeBinomial (const df1b2variable &obs, const double m, const df1b2variable &s);
df1b2variable	nllNegativeBinomial (const df1b2variable &obs, const df1b2variable &m, const df1b2variable &s);
dvariable	nllNegativeBinomial (const dvector &obs, const dvariable &m, const dvariable &s);
dvariable	nllNegativeBinomial (const dvar_vector &obs, const double m, const double s);
dvariable	nllNegativeBinomial (const dvar_vector &obs, const dvariable &m, const dvariable &s);
df1b2variable	nllNegativeBinomial (const df1b2vector &obs, const double m, const double s);
df1b2variable	nllNegativeBinomial (const dvector &obs, const df1b2variable &m, const df1b2variable &s);
df1b2variable	nllNegativeBinomial (const df1b2vector &obs, const df1b2variable &m, const df1b2variable &s);
double	nllNegativeBinomial2 (const double obs, const double m, const double tau);
dvariable	nllNegativeBinomial2 (const double obs, const dvariable &m, const dvariable &tau);
dvariable	nllNegativeBinomial2 (const dvariable &obs, const double m, const double tau);
dvariable	nllNegativeBinomial2 (const dvariable &obs, const dvariable &m, const double tau);
dvariable	nllNegativeBinomial2 (const dvariable &obs, const double m, const dvariable &tau);
dvariable	nllNegativeBinomial2 (const dvariable &obs, const dvariable &m, const dvariable &tau);
df1b2variable	nllNegativeBinomial2 (const df1b2variable &obs, const double m, const double tau);
df1b2variable	nllNegativeBinomial2 (const double obs, const df1b2variable &m, const df1b2variable &tau);
df1b2variable	nllNegativeBinomial2 (const df1b2variable &obs, const df1b2variable &m, const df1b2variable &tau);
double	nllMultiNomial (const dvector &obsN, const dvector &p);
dvariable	nllMultiNomial (const dvector &obsN, const dvar_vector &p);
dvariable	nllMultiNomial (const dvar_vector &obsN, const dvector &p);
dvariable	nllMultiNomial (const dvar_vector &obsN, const dvar_vector &p);
df1b2variable	nllMultiNomial (const df1b2vector &obsN, const dvector &p);
df1b2variable	nllMultiNomial (const dvector &obsN, const df1b2vector &p);
df1b2variable	nllMultiNomial (const df1b2vector &obsN, const df1b2vector &p);
double	nllDirichlet (const dvector &p, const dvector &shape);
dvariable	nllDirichlet (const dvar_vector &p, const dvector &shape);
dvariable	nllDirichlet (const dvector &p, const dvar_vector &shape);
dvariable	nllDirichlet (const dvar_vector &p, const dvar_vector &shape);
df1b2variable	nllDirichlet (const df1b2vector &p, const dvector &shape);
df1b2variable	nllDirichlet (const dvector &p, const df1b2vector &shape);
df1b2variable	nllDirichlet (const df1b2vector &p, const df1b2vector &shape);
double	nllGamma (const double &x, const double a, const double b);
dvariable	nllGamma (const dvariable &x, const double a, const double b);
dvariable	nllGamma (const double x, const dvariable &a, const dvariable &b);
dvariable	nllGamma (const dvariable &x, const dvariable &a, const double b);
dvariable	nllGamma (const dvariable &x, const double a, const dvariable &b);
dvariable	nllGamma (const dvariable &x, const dvariable &a, const dvariable &b);
df1b2variable	nllGamma (const df1b2variable &x, const double a, const double b);
df1b2variable	nllGamma (const double x, const df1b2variable &a, const df1b2variable &b);
df1b2variable	nllGamma (const df1b2variable &x, const df1b2variable &a, const double b);
df1b2variable	nllGamma (const df1b2variable &x, const double a, const df1b2variable &b);
df1b2variable	nllGamma (const df1b2variable &x, const df1b2variable &a, const df1b2variable &b);
double	nllGamma (const dvector &x, const double a, const double b);
dvariable	nllGamma (const dvar_vector &x, const double a, const double b);
dvariable	nllGamma (const dvector &x, const dvariable &a, const dvariable &b);
dvariable	nllGamma (const dvar_vector &x, const dvariable &a, const dvariable &b);
df1b2variable	nllGamma (const df1b2vector &x, const double a, const double b);
df1b2variable	nllGamma (const dvector &x, const df1b2variable &a, const df1b2variable &b);
df1b2variable	nllGamma (const df1b2vector &x, const df1b2variable &a, const df1b2variable &b);
double	nllBeta (const double x, const double a, const double b);
dvariable	nllBeta (const dvariable &x, const double a, const double b);
dvariable	nllBeta (const double x, const dvariable &a, const dvariable &b);
dvariable	nllBeta (const dvariable &x, const dvariable &a, const double b);
dvariable	nllBeta (const dvariable &x, const double a, const dvariable &b);
dvariable	nllBeta (const dvariable &x, const dvariable &a, const dvariable &b);
df1b2variable	nllBeta (const df1b2variable &x, const double a, const double b);
df1b2variable	nllBeta (const df1b2variable &x, const df1b2variable &a, const double b);
df1b2variable	nllBeta (const df1b2variable &x, const double a, const df1b2variable &b);
df1b2variable	nllBeta (const double x, const df1b2variable &a, const df1b2variable &b);
df1b2variable	nllBeta (const df1b2variable &x, const df1b2variable &a, const df1b2variable &b);
dvariable	nllBeta (const dvar_vector &x, const double a, const double b);
dvariable	nllBeta (const dvector &x, const dvariable &a, const dvariable &b);
dvariable	nllBeta (const dvar_vector &x, const dvariable &a, const dvariable &b);
df1b2variable	nllBeta (const df1b2vector &x, const double a, const double b);
df1b2variable	nllBeta (const dvector &x, const df1b2variable &a, const df1b2variable &b);
df1b2variable	nllBeta (const df1b2vector &x, const df1b2variable &a, const df1b2variable &b);
double	nllNormal (const double x, const double mu, const double sigma);
dvariable	nllNormal (const dvariable &x, const double mu, const double sigma);
dvariable	nllNormal (const double x, const dvariable &mu, const dvariable &sigma);
dvariable	nllNormal (const dvariable &x, const dvariable &mu, const double sigma);
dvariable	nllNormal (const dvariable &x, const double mu, const dvariable &sigma);
dvariable	nllNormal (const dvariable &x, const dvariable &mu, const dvariable &sigma);
df1b2variable	nllNormal (const df1b2variable &x, const double mu, const double sigma);
df1b2variable	nllNormal (const df1b2variable &x, const df1b2variable &mu, const double sigma);
df1b2variable	nllNormal (const df1b2variable &x, const double mu, const df1b2variable &sigma);
df1b2variable	nllNormal (const double x, const df1b2variable &mu, const df1b2variable &sigma);
df1b2variable	nllNormal (const df1b2variable &x, const df1b2variable &mu, const df1b2variable &sigma);
double	nllNormal (const dvector &x, const double mu, const double sigma);
dvariable	nllNormal (const dvar_vector &x, const double mu, const double sigma);
dvariable	nllNormal (const dvector &x, const dvariable &mu, const dvariable &sigma);
dvariable	nllNormal (const dvar_vector &x, const dvariable &mu, const dvariable &sigma);
df1b2variable	nllNormal (const df1b2vector &x, const double mu, const double sigma);
df1b2variable	nllNormal (const dvector &x, const df1b2variable &mu, const df1b2variable &sigma);
df1b2variable	nllNormal (const df1b2vector &x, const df1b2variable &mu, const df1b2variable &sigma);
dvariable	nllNormal (const dvar_vector &x, const dvector &mu, const double sigma);
dvariable	nllNormal (const dvector &x, const dvar_vector &mu, const dvariable &sigma);
dvariable	nllNormal (const dvar_vector &x, const dvar_vector &mu, const dvariable &sigma);
df1b2variable	nllNormal (const df1b2vector &x, const dvector &mu, const double sigma);
df1b2variable	nllNormal (const dvector &x, const df1b2vector &mu, const df1b2variable &sigma);
df1b2variable	nllNormal (const df1b2vector &x, const df1b2vector &mu, const df1b2variable &sigma);
dvariable	nllNormal2 (const dvariable &x, const double mu, const double tau);
dvariable	nllNormal2 (const double x, const dvariable &mu, const dvariable &tau);
dvariable	nllNormal2 (const dvariable &x, const dvariable &mu, const dvariable &tau);
df1b2variable	nllNormal2 (const df1b2variable &x, const double mu, const double tau);
df1b2variable	nllNormal2 (const double x, const df1b2variable &mu, const df1b2variable &tau);
df1b2variable	nllNormal2 (const df1b2variable &x, const df1b2variable &mu, const df1b2variable &tau);
dvariable	nllNormal2 (const dvar_vector &x, const double mu, const double tau);
dvariable	nllNormal2 (const dvector &x, const dvariable &mu, const dvariable &tau);
dvariable	nllNormal2 (const dvar_vector &x, const dvariable &mu, const dvariable &tau);
df1b2variable	nllNormal2 (const df1b2vector &x, const double mu, const double tau);
df1b2variable	nllNormal2 (const dvector &x, const df1b2variable &mu, const df1b2variable &tau);
df1b2variable	nllNormal2 (const df1b2vector &x, const df1b2variable &mu, const df1b2variable &tau);
dvariable	nllNormal2 (const dvar_vector &x, const dvector &mu, const double tau);
dvariable	nllNormal2 (const dvector &x, const dvar_vector &mu, const dvariable &tau);
dvariable	nllNormal2 (const dvar_vector &x, const dvar_vector &mu, const dvariable &tau);
df1b2variable	nllNormal2 (const df1b2vector &x, const dvector &mu, const double tau);
df1b2variable	nllNormal2 (const dvector &x, const df1b2vector &mu, const df1b2variable &tau);
df1b2variable	nllNormal2 (const df1b2vector &x, const df1b2vector &mu, const df1b2variable &tau);
double	nllBinomial (const double x, const double n, const double p);
dvariable	nllBinomial (const dvariable &x, const double n, const double p);
dvariable	nllBinomial (const double x, const dvariable &n, const dvariable &p);
dvariable	nllBinomial (const dvariable &x, const dvariable &n, const dvariable &p);
df1b2variable	nllBinomial (const df1b2variable &x, const double n, const double p);
df1b2variable	nllBinomial (const double x, const df1b2variable &n, const df1b2variable &p);
df1b2variable	nllBinomial (const df1b2variable &x, const df1b2variable &n, const df1b2variable &p);
dvariable	nllBinomial (const dvar_vector &x, const dvector &n, const double p);
dvariable	nllBinomial (const dvector &x, const dvar_vector &n, const dvariable &p);
dvariable	nllBinomial (const dvar_vector &x, const dvar_vector &n, const dvariable &p);
df1b2variable	nllBinomial (const dvector &x, const df1b2vector &n, const df1b2variable &p);
df1b2variable	nllBinomial (const df1b2vector &x, const dvector &n, const double p);
df1b2variable	nllBinomial (const df1b2vector &x, const df1b2vector &n, const df1b2variable &p);
double	nllLognormal (const double x, const double mu, const double sigma);
dvariable	nllLognormal (const dvariable &x, const double mu, const double sigma);
dvariable	nllLognormal (const double x, const dvariable &mu, const dvariable &sigma);
dvariable	nllLognormal (const dvariable &x, const dvariable &mu, const double sigma);
dvariable	nllLognormal (const dvariable &x, const double mu, const dvariable &sigma);
dvariable	nllLognormal (const dvariable &x, const dvariable &mu, const dvariable &sigma);
df1b2variable	nllLognormal (const df1b2variable &x, const double mu, const double sigma);
df1b2variable	nllLognormal (const double x, const df1b2variable &mu, const df1b2variable &sigma);
df1b2variable	nllLognormal (const df1b2variable &x, const df1b2variable &mu, const double sigma);
df1b2variable	nllLognormal (const df1b2variable &x, const double mu, const df1b2variable &sigma);
df1b2variable	nllLognormal (const df1b2variable &x, const df1b2variable &mu, const df1b2variable &sigma);
dvariable	nllLognormal (const dvar_vector &x, const double mu, const double sigma);
dvariable	nllLognormal (const dvector &x, const dvariable &mu, const dvariable &sigma);
dvariable	nllLognormal (const dvar_vector &x, const dvariable &mu, const dvariable &sigma);
df1b2variable	nllLognormal (const df1b2vector &x, const double mu, const double sigma);
df1b2variable	nllLognormal (const dvector &x, const df1b2variable &mu, const df1b2variable &sigma);
df1b2variable	nllLognormal (const df1b2vector &x, const df1b2variable &mu, const df1b2variable &sigma);
dvariable	nllLognormal (const dvar_vector &x, const dvector &mu, const double sigma);
dvariable	nllLognormal (const dvector &x, const dvar_vector &mu, const dvariable &sigma);
dvariable	nllLognormal (const dvar_vector &x, const dvar_vector &mu, const dvariable &sigma);
df1b2variable	nllLognormal (const df1b2vector &x, const dvector &mu, const double sigma);
df1b2variable	nllLognormal (const dvector &x, const df1b2vector &mu, const df1b2variable &sigma);
df1b2variable	nllLognormal (const df1b2vector &x, const df1b2vector &mu, const df1b2variable &sigma);
dvariable	nllLognormal2 (const double x, const dvariable &mu, const dvariable &tau);
dvariable	nllLognormal2 (const dvariable &x, const double mu, const double tau);
dvariable	nllLognormal2 (const dvariable &x, const dvariable &mu, const dvariable &tau);
df1b2variable	nllLognormal2 (const df1b2variable x, const double mu, const double tau);
df1b2variable	nllLognormal2 (const double x, const df1b2variable &mu, const df1b2variable &tau);
df1b2variable	nllLognormal2 (const df1b2variable x, const df1b2variable &mu, const double tau);
df1b2variable	nllLognormal2 (const df1b2variable x, const double mu, const df1b2variable &tau);
df1b2variable	nllLognormal2 (const df1b2variable x, const df1b2variable &mu, const df1b2variable &tau);
dvariable	nllLognormal2 (const dvar_vector &x, const double mu, const double tau);
dvariable	nllLognormal2 (const dvector &x, const dvariable &mu, const dvariable &tau);
dvariable	nllLognormal2 (const dvar_vector &x, const dvariable &mu, const dvariable &tau);
df1b2variable	nllLognormal2 (const dvector &x, const df1b2variable &mu, const df1b2variable &tau);
df1b2variable	nllLognormal2 (const df1b2vector &x, const double mu, const double tau);
df1b2variable	nllLognormal2 (const df1b2vector &x, const df1b2variable &mu, const double tau);
df1b2variable	nllLognormal2 (const df1b2vector &x, const double mu, const df1b2variable &tau);
df1b2variable	nllLognormal2 (const df1b2vector &x, const df1b2variable &mu, const df1b2variable &tau);
dvariable	nllLognormal2 (const dvar_vector &x, const dvector &mu, const double tau);
dvariable	nllLognormal2 (const dvector &x, const dvar_vector &mu, const dvariable &tau);
dvariable	nllLognormal2 (const dvar_vector &x, const dvar_vector &mu, const dvariable &tau);
df1b2variable	nllLognormal2 (const df1b2vector &x, const dvector &mu, const double tau);
df1b2variable	nllLognormal2 (const dvector &x, const df1b2vector &mu, const df1b2variable &tau);
df1b2variable	nllLognormal2 (const df1b2vector &x, const df1b2vector &mu, const df1b2variable &tau);
double	nllPoisson (const double x, const double lambda);
dvariable	nllPoisson (const dvariable &x, const double lambda);
dvariable	nllPoisson (const double x, const dvariable &lambda);
dvariable	nllPoisson (const dvariable &x, const dvariable &lambda);
df1b2variable	nllPoisson (const df1b2variable &x, const double lambda);
df1b2variable	nllPoisson (const double x, const df1b2variable &lambda);
df1b2variable	nllPoisson (const df1b2variable &x, const df1b2variable &lambda);
dvariable	nllPoisson (const dvar_vector &x, const double lambda);
dvariable	nllPoisson (const dvector &x, const dvariable &lambda);
dvariable	nllPoisson (const dvar_vector &x, const dvariable &lambda);
df1b2variable	nllPoisson (const dvector &x, const df1b2variable &lambda);
df1b2variable	nllPoisson (const df1b2vector &x, const double lambda);
df1b2variable	nllPoisson (const df1b2vector &x, const df1b2variable &lambda);
double	nllInverseGamma (const double x, const double a, const double b);
dvariable	nllInverseGamma (const dvariable &x, const double a, const double b);
dvariable	nllInverseGamma (const double x, const dvariable &a, const dvariable &b);
dvariable	nllInverseGamma (const dvariable &x, const dvariable &a, const dvariable &b);
df1b2variable	nllInverseGamma (const df1b2variable &x, const double a, const double b);
df1b2variable	nllInverseGamma (const double x, const df1b2variable &a, const df1b2variable &b);
df1b2variable	nllInverseGamma (const df1b2variable &x, const df1b2variable &a, const double b);
df1b2variable	nllInverseGamma (const df1b2variable &x, const double a, const df1b2variable &b);
df1b2variable	nllInverseGamma (const df1b2variable &x, const df1b2variable &a, const df1b2variable &b);
dvariable	nllInverseGamma (const dvar_vector &x, const double a, const double b);
dvariable	nllInverseGamma (const dvector &x, const dvariable &a, const dvariable &b);
dvariable	nllInverseGamma (const dvar_vector &x, const dvariable &a, const dvariable &b);
df1b2variable	nllInverseGamma (const dvector &x, const df1b2variable &a, const df1b2variable &b);
df1b2variable	nllInverseGamma (const df1b2vector &x, const double a, const double b);
df1b2variable	nllInverseGamma (const df1b2vector &x, const df1b2variable &a, const df1b2variable &b);
#endif

  /** generate random gamma number, pseudo code see http://en.wikipedia.org/wiki/Gamma_distribution ,
   * Gamma(alpha, belta)=x^(alpha-1)*belta^alpha*exp(-belta*x)/gamma(alpha)
   * \ingroup QFC
   * \param alpha : shape parameter, >0  =1/CV^2
   * \param rng :  admb build in random number generator
   * \return return gamma random number
   */
  double rgamma(double alpha, random_number_generator& rng)
  {
    double  v0, v1, v2, fract, em, qm, tmp, gam_n1;
    int i;

    //calculate Gamma(n,1) integer part first
    tmp = 1.;
    if (int(alpha) == 0) //which means 0<alpha <1
	gam_n1 = 0;
    else{
	for( i = 1;i<=int(alpha);i++)
	    tmp *= randu(rng);	 //using modified rnd()

	gam_n1 = -1. * log(tmp);
    }

    fract = alpha - int(alpha) + EPS;  //fractional part of alpha
    v0 = QFC_M_E / (QFC_M_E + fract);

    //calculate the fractional gamma(fract,1)
    while(1){
	v1 =  randu(rng);
	v2 =  randu(rng);
	if (v1 <= v0){
	    em = pow(v1 / (v0 + EPS), 1. / fract);
	    qm = v2 * pow(em, fract - 1.);
	}else{
	    em = 1. - log((v1 - v0) / (1. - v0 + EPS));
	    qm = v2 * mfexp(-em);
	}
	if (qm <= (pow(em, fract - 1.) * mfexp(-em))) break;
    }

    return (em + gam_n1);
  }

int main()
{
  int n=1000;
  random_number_generator rng(101);
  dvector x(1,n);
  double ssum=0.0;
  double ssum2=0.0;
  for (int i=1;i<=n;i++)
  {
    x(i)=rgamma(1.0,rng);
    ssum+=x(i);
    ssum2+=square(x(i));
  }
  double n1=ssum/n;
  double n2=ssum2/n;

  cout << n1 << endl;
  cout << n2-square(n1) << endl;
}
