#ifndef __QFCLIB_H__
#define __QFCLIB_H__

#include <math.h>
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 
const double EPS = 1.e-30;          //tiny number to avoid 0 in log

dvar_vector logitProp(const dvar_vector& a);
// Weihei, add the rest of the prototypes here...

#endif
