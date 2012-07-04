#include "statsLib.h"

/**
* @file dinvgamma.cpp
* @brief Inverse gamma distribution
* 
* This file contains the inverse gamma distribution functions
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/2/2011
* @remarks
**/

//inverse-gamma
dvariable dinvgamma(const dvariable& x, const double a, const double b)
{
	return -a*log(b)+gammln(a)+(a+1)*log(x)+b/x;
}
