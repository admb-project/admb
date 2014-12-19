#include "statsLib.h"

/**
* @file eplogis.cpp
* @brief // Exponential logistic
* 
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/13/2011
* @remarks
*/

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

// template <typename t1, typename t2>
// t1 eplogis(const t1& x, const t2& alpha, const t2& beta, const t2& gamma)
// {
// 	//exponential logistic based on Grant Thompson (1994) Paper, CJFAS.
// 	return (1./(1.-gamma))*pow((1.-gamma)/gamma,gamma)*elem_div(exp(alpha*gamma*(beta-x)),1.+exp(alpha*(beta-x)));
// }
