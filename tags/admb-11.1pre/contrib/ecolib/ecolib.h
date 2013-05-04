#ifndef __ECOLIB_H__
#define __ECOLIB_H__

#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h> 

dvariable generalized_Ricker1(const double& x,  const prevariable& x0,  const prevariable& A,  const prevariable& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const prevariable& A,  const prevariable& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const prevariable& A,  const prevariable& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const dvar_vector& A,  const prevariable& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const dvar_vector& A,  const prevariable& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const prevariable& A,  const dvar_vector& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const prevariable& A,  const dvar_vector& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const prevariable& x0,  const dvar_vector& A,  const dvar_vector& alpha);
dvar_vector generalized_Ricker1(const dvector& x,  const dvar_vector& x0,  const dvar_vector& A,  const dvar_vector& alpha);
df1b2variable generalized_Ricker1(const double& x,  const df1b2variable& x0,  const df1b2variable& A,  const df1b2variable& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2variable& A,  const df1b2variable& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2variable& A,  const df1b2variable& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2vector& A,  const df1b2variable& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2vector& A,  const df1b2variable& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2variable& A,  const df1b2vector& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2variable& A,  const df1b2vector& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2variable& x0,  const df1b2vector& A,  const df1b2vector& alpha);
df1b2vector generalized_Ricker1(const dvector& x,  const df1b2vector& x0,  const df1b2vector& A,  const df1b2vector& alpha);

dvariable generalized_Ricker2(const double& x,  const prevariable& r,  const prevariable& a,  const prevariable& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const prevariable& a,  const prevariable& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const prevariable& a,  const prevariable& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const dvar_vector& a,  const prevariable& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const dvar_vector& a,  const prevariable& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const prevariable& a,  const dvar_vector& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const prevariable& a,  const dvar_vector& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const prevariable& r,  const dvar_vector& a,  const dvar_vector& alpha);
dvar_vector generalized_Ricker2(const dvector& x,  const dvar_vector& r,  const dvar_vector& a,  const dvar_vector& alpha);
df1b2variable generalized_Ricker2(const double& x,  const df1b2variable& r,  const df1b2variable& a,  const df1b2variable& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2variable& a,  const df1b2variable& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2variable& a,  const df1b2variable& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2vector& a,  const df1b2variable& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2vector& a,  const df1b2variable& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2variable& a,  const df1b2vector& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2variable& a,  const df1b2vector& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2variable& r,  const df1b2vector& a,  const df1b2vector& alpha);
df1b2vector generalized_Ricker2(const dvector& x,  const df1b2vector& r,  const df1b2vector& a,  const df1b2vector& alpha);

dvariable Gompertz(const double& x,  const prevariable& a,  const prevariable& b);
dvar_vector Gompertz(const dvector& x,  const prevariable& a,  const prevariable& b);
dvar_vector Gompertz(const dvector& x,  const dvar_vector& a,  const prevariable& b);
dvar_vector Gompertz(const dvector& x,  const prevariable& a,  const dvar_vector& b);
dvar_vector Gompertz(const dvector& x,  const dvar_vector& a,  const dvar_vector& b);
df1b2variable Gompertz(const double& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Gompertz(const dvector& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Gompertz(const dvector& x,  const df1b2vector& a,  const df1b2variable& b);
df1b2vector Gompertz(const dvector& x,  const df1b2variable& a,  const df1b2vector& b);
df1b2vector Gompertz(const dvector& x,  const df1b2vector& a,  const df1b2vector& b);

dvariable Hassell(const double& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector Hassell(const dvector& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector Hassell(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const prevariable& c);
dvar_vector Hassell(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector Hassell(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector Hassell(const dvector& x,  const prevariable& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector Hassell(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector Hassell(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const dvar_vector& c);
dvar_vector Hassell(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const dvar_vector& c);
df1b2variable Hassell(const double& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Hassell(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Hassell(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Hassell(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector Hassell(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector Hassell(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector Hassell(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector Hassell(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2vector& c);
df1b2vector Hassell(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2vector& c);

dvariable Hill(const double& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector Hill(const dvector& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector Hill(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const prevariable& c);
dvar_vector Hill(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector Hill(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector Hill(const dvector& x,  const prevariable& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector Hill(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector Hill(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const dvar_vector& c);
dvar_vector Hill(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const dvar_vector& c);
df1b2variable Hill(const double& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Hill(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Hill(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Hill(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector Hill(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector Hill(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector Hill(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector Hill(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2vector& c);
df1b2vector Hill(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2vector& c);

dvariable HollingII(const double& x,  const prevariable& alpha,  const prevariable& h);
dvar_vector HollingII(const dvector& x,  const prevariable& alpha,  const prevariable& h);
dvar_vector HollingII(const dvector& x,  const dvar_vector& alpha,  const prevariable& h);
dvar_vector HollingII(const dvector& x,  const prevariable& alpha,  const dvar_vector& h);
dvar_vector HollingII(const dvector& x,  const dvar_vector& alpha,  const dvar_vector& h);
df1b2variable HollingII(const double& x,  const df1b2variable& alpha,  const df1b2variable& h);
df1b2vector HollingII(const dvector& x,  const df1b2variable& alpha,  const df1b2variable& h);
df1b2vector HollingII(const dvector& x,  const df1b2vector& alpha,  const df1b2variable& h);
df1b2vector HollingII(const dvector& x,  const df1b2variable& alpha,  const df1b2vector& h);
df1b2vector HollingII(const dvector& x,  const df1b2vector& alpha,  const df1b2vector& h);

dvariable HollingIII(const double& x,  const prevariable& a,  const prevariable& b);
dvar_vector HollingIII(const dvector& x,  const prevariable& a,  const prevariable& b);
dvar_vector HollingIII(const dvector& x,  const dvar_vector& a,  const prevariable& b);
dvar_vector HollingIII(const dvector& x,  const prevariable& a,  const dvar_vector& b);
dvar_vector HollingIII(const dvector& x,  const dvar_vector& a,  const dvar_vector& b);
df1b2variable HollingIII(const double& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector HollingIII(const dvector& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector HollingIII(const dvector& x,  const df1b2vector& a,  const df1b2variable& b);
df1b2vector HollingIII(const dvector& x,  const df1b2variable& a,  const df1b2vector& b);
df1b2vector HollingIII(const dvector& x,  const df1b2vector& a,  const df1b2vector& b);

dvariable HollingIV(const double& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector HollingIV(const dvector& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector HollingIV(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const prevariable& c);
dvar_vector HollingIV(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector HollingIV(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector HollingIV(const dvector& x,  const prevariable& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector HollingIV(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector HollingIV(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const dvar_vector& c);
dvar_vector HollingIV(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const dvar_vector& c);
df1b2variable HollingIV(const double& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector HollingIV(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector HollingIV(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector HollingIV(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector HollingIV(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector HollingIV(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector HollingIV(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector HollingIV(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2vector& c);
df1b2vector HollingIV(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2vector& c);

dvariable logistic(const double& x,  const prevariable& a,  const prevariable& b);
dvar_vector logistic(const dvector& x,  const prevariable& a,  const prevariable& b);
dvar_vector logistic(const dvector& x,  const dvar_vector& a,  const prevariable& b);
dvar_vector logistic(const dvector& x,  const prevariable& a,  const dvar_vector& b);
dvar_vector logistic(const dvector& x,  const dvar_vector& a,  const dvar_vector& b);
df1b2variable logistic(const double& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector logistic(const dvector& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector logistic(const dvector& x,  const df1b2vector& a,  const df1b2variable& b);
df1b2vector logistic(const dvector& x,  const df1b2variable& a,  const df1b2vector& b);
df1b2vector logistic(const dvector& x,  const df1b2vector& a,  const df1b2vector& b);

dvariable logistic3(const double& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const prevariable& c);
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector logistic3(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const dvar_vector& c);
dvar_vector logistic3(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const dvar_vector& c);
df1b2variable logistic3(const double& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector logistic3(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2vector& c);
df1b2vector logistic3(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2vector& c);

dvariable logisticK( const double& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0);
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0);
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const prevariable& r,  const prevariable& n0);
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const dvar_vector& r,  const prevariable& n0);
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const prevariable& n0);
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const prevariable& r,  const dvar_vector& n0);
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const prevariable& r,  const dvar_vector& n0);
dvar_vector logisticK( const dvector& t,  const prevariable& K,  const dvar_vector& r,  const dvar_vector& n0);
dvar_vector logisticK( const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const dvar_vector& n0);
df1b2variable logisticK( const double& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0);
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0);
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2variable& n0);
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2variable& n0);
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2variable& n0);
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2vector& n0);
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2vector& n0);
df1b2vector logisticK( const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2vector& n0);
df1b2vector logisticK( const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2vector& n0);

dvariable Michaelis_Menten1(const double& x,  const prevariable& a,  const prevariable& b);
dvar_vector Michaelis_Menten1(const dvector& x,  const prevariable& a,  const prevariable& b);
dvar_vector Michaelis_Menten1(const dvector& x,  const dvar_vector& a,  const prevariable& b);
dvar_vector Michaelis_Menten1(const dvector& x,  const prevariable& a,  const dvar_vector& b);
dvar_vector Michaelis_Menten1(const dvector& x,  const dvar_vector& a,  const dvar_vector& b);
df1b2variable Michaelis_Menten1(const double& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2vector& a,  const df1b2variable& b);
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2variable& a,  const df1b2vector& b);
df1b2vector Michaelis_Menten1(const dvector& x,  const df1b2vector& a,  const df1b2vector& b);

dvariable Michaelis_Menten2(const double& x,  const prevariable& a,  const prevariable& b);
dvar_vector Michaelis_Menten2(const dvector& x,  const prevariable& a,  const prevariable& b);
dvar_vector Michaelis_Menten2(const dvector& x,  const dvar_vector& a,  const prevariable& b);
dvar_vector Michaelis_Menten2(const dvector& x,  const prevariable& a,  const dvar_vector& b);
dvar_vector Michaelis_Menten2(const dvector& x,  const dvar_vector& a,  const dvar_vector& b);
df1b2variable Michaelis_Menten2(const double& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Michaelis_Menten2(const dvector& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Michaelis_Menten2(const dvector& x,  const df1b2vector& a,  const df1b2variable& b);
df1b2vector Michaelis_Menten2(const dvector& x,  const df1b2variable& a,  const df1b2vector& b);
df1b2vector Michaelis_Menten2(const dvector& x,  const df1b2vector& a,  const df1b2vector& b);

dvariable monomolecular(const double& x,  const prevariable& a,  const prevariable& b);
dvar_vector monomolecular(const dvector& x,  const prevariable& a,  const prevariable& b);
dvar_vector monomolecular(const dvector& x,  const dvar_vector& a,  const prevariable& b);
dvar_vector monomolecular(const dvector& x,  const prevariable& a,  const dvar_vector& b);
dvar_vector monomolecular(const dvector& x,  const dvar_vector& a,  const dvar_vector& b);
df1b2variable monomolecular(const double& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector monomolecular(const dvector& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector monomolecular(const dvector& x,  const df1b2vector& a,  const df1b2variable& b);
df1b2vector monomolecular(const dvector& x,  const df1b2variable& a,  const df1b2vector& b);
df1b2vector monomolecular(const dvector& x,  const df1b2vector& a,  const df1b2vector& b);

dvariable nonrectangular_hyperbola(const double& x,  const prevariable& theta,  const prevariable& alpha,  const prevariable& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const prevariable& alpha,  const prevariable& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const prevariable& alpha,  const prevariable& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const dvar_vector& alpha,  const prevariable& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const dvar_vector& alpha,  const prevariable& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const prevariable& alpha,  const dvar_vector& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const prevariable& alpha,  const dvar_vector& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const prevariable& theta,  const dvar_vector& alpha,  const dvar_vector& pmax);
dvar_vector nonrectangular_hyperbola(const dvector& x,  const dvar_vector& theta,  const dvar_vector& alpha,  const dvar_vector& pmax);
df1b2variable nonrectangular_hyperbola(const double& x,  const df1b2variable& theta,  const df1b2variable& alpha,  const df1b2variable& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2variable& alpha,  const df1b2variable& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2variable& alpha,  const df1b2variable& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2vector& alpha,  const df1b2variable& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2vector& alpha,  const df1b2variable& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2variable& alpha,  const df1b2vector& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2variable& alpha,  const df1b2vector& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2variable& theta,  const df1b2vector& alpha,  const df1b2vector& pmax);
df1b2vector nonrectangular_hyperbola(const dvector& x,  const df1b2vector& theta,  const df1b2vector& alpha,  const df1b2vector& pmax);

dvariable Ricker(const double& x,  const prevariable& a,  const prevariable& b);
dvar_vector Ricker(const dvector& x,  const prevariable& a,  const prevariable& b);
dvar_vector Ricker(const dvector& x,  const dvar_vector& a,  const prevariable& b);
dvar_vector Ricker(const dvector& x,  const prevariable& a,  const dvar_vector& b);
dvar_vector Ricker(const dvector& x,  const dvar_vector& a,  const dvar_vector& b);
df1b2variable Ricker(const double& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Ricker(const dvector& x,  const df1b2variable& a,  const df1b2variable& b);
df1b2vector Ricker(const dvector& x,  const df1b2vector& a,  const df1b2variable& b);
df1b2vector Ricker(const dvector& x,  const df1b2variable& a,  const df1b2vector& b);
df1b2vector Ricker(const dvector& x,  const df1b2vector& a,  const df1b2vector& b);

dvariable Shepherd(const double& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector Shepherd(const dvector& x,  const prevariable& a,  const prevariable& b,  const prevariable& c);
dvar_vector Shepherd(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const prevariable& c);
dvar_vector Shepherd(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector Shepherd(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const prevariable& c);
dvar_vector Shepherd(const dvector& x,  const prevariable& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector Shepherd(const dvector& x,  const dvar_vector& a,  const prevariable& b,  const dvar_vector& c);
dvar_vector Shepherd(const dvector& x,  const prevariable& a,  const dvar_vector& b,  const dvar_vector& c);
dvar_vector Shepherd(const dvector& x,  const dvar_vector& a,  const dvar_vector& b,  const dvar_vector& c);
df1b2variable Shepherd(const double& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Shepherd(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Shepherd(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2variable& c);
df1b2vector Shepherd(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector Shepherd(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2variable& c);
df1b2vector Shepherd(const dvector& x,  const df1b2variable& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector Shepherd(const dvector& x,  const df1b2vector& a,  const df1b2variable& b,  const df1b2vector& c);
df1b2vector Shepherd(const dvector& x,  const df1b2variable& a,  const df1b2vector& b,  const df1b2vector& c);
df1b2vector Shepherd(const dvector& x,  const df1b2vector& a,  const df1b2vector& b,  const df1b2vector& c);

dvariable theta_logistic(const double& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const prevariable& r,  const prevariable& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const prevariable& r,  const prevariable& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const dvar_vector& r,  const prevariable& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const prevariable& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const prevariable& r,  const dvar_vector& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const prevariable& r,  const dvar_vector& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const prevariable& K,  const dvar_vector& r,  const dvar_vector& n0, const prevariable& theta);
dvar_vector theta_logistic(const dvector& t,  const dvar_vector& K,  const dvar_vector& r,  const dvar_vector& n0, const prevariable& theta);
df1b2variable theta_logistic(const double& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2variable& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2variable& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2variable& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2variable& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2variable& r,  const df1b2vector& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2variable& r,  const df1b2vector& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2variable& K,  const df1b2vector& r,  const df1b2vector& n0, const df1b2variable& theta);
df1b2vector theta_logistic(const dvector& t,  const df1b2vector& K,  const df1b2vector& r,  const df1b2vector& n0, const df1b2variable& theta);

#endif
