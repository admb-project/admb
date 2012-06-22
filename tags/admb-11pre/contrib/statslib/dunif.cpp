#include "statsLib.h"

/**
* @file dunif.cpp
* @brief Uniform distribution
* 
* This file contains the uniform distribution functions
* \ingroup STATLIB
* @author Chris Grandin, Steve Martell
* 
* @date 12/12/2011
* @remarks
*/

//uniform distribution
dvariable dunif(const dvariable& x, const double min, const double max)
{
	return log(max-min);
}
