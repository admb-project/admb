#include "statsLib.h"

/**
* @file rmvlogistic.cpp
* @brief Random multivariate logistic negative log likelihood
* 
* This file contains the Random multivariate logistic negative log likelihood functions
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/13/2011
* @remarks
*/

dvector rmvlogistic(const dvector& p, const double& tau2, const int& seed)
{
	int a=p.indexmin();
	int A=p.indexmax();
	random_number_generator rng(seed);
	dvector epsilon(a,A);
	epsilon.fill_randn(rng);
	dvector x = log(p)+tau2*epsilon;
	x -= mean(x);
	return exp(x)/sum(exp(x));
}
