#ifndef __ECOLIB_H__
#define __ECOLIB_H__

#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

df1b2vector pow(const dvector& x,  const df1b2variable& a);
df1b2vector pow(const dvector& x,  const df1b2vector& a);
dvar_vector pow(const dvector& x,const dvar_vector& a);

#endif
