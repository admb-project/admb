#include "statsLib.h"

/**
* 
* \file studentT.cpp
* \brief Student T density functions.
* \ingroup STATLIB
* \author Steven Martell
* \date 24/06/2011
* 
* 
* This file contains the negative loglikelihood 
* functions for the Students'-T distribution. The function
* dstudent_t is overloaded to accommodate variable and data objects. 
* 
* The negative log likelihood function is implemented as:
* \f[
*  -\ln\left(\Gamma\left(\frac{\nu+1}{2}\right)\right)
*  +0.5\ln(\nu\pi)+\ln\left(\Gamma\left(\frac{\nu}{2}\right)\right)
*  +\frac{\nu+1}{2}\ln\left(1+\frac{t^2}{\nu}\right)
* \f]
* where \f$\nu\f$ is the degrees of freedom and \f$t\f$
* is the residual.
* 
* 
* 
*/

/**	
	\author Steven James Dean Martell UBC Fisheries Centre
	\date 2011-06-24
	\param  residual dvar_vector vector of residual differences
	\param  df       dvar_vector for the degrees of freedom
	\return returns the negative loglikelihood of the students's-t density function.
	\sa
**/

dvariable dstudent_t( const dvar_vector& residual, const dvar_vector& df)
{
	RETURN_ARRAYS_INCREMENT();
	double pi =  3.141593;
	dvar_vector t1 = 0.5*(df+1);
	dvar_vector t2 = gammln(t1);
	dvar_vector t3 = 0.5*log(df*pi)+gammln(0.5*df);
	dvar_vector t4 = elem_prod(t1,log(1+elem_div(square(residual),df)));
	dvariable pdf = sum(t3+t4-t2);
	RETURN_ARRAYS_DECREMENT();
	return( pdf );
}
