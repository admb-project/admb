/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
    double mult;
    double eps;
    dvector coffs;

/**
 * Description not yet available.
 * \param
 */
function_tweaker::function_tweaker(double _eps,double _mult):
  mult(_mult), eps(_eps), coffs(1,3)
{
  double e=eps;
  double e2=e*e;
  double e3=e*e2;
  double e4=e*e3;
  double e5=e*e4;

  dmatrix M(1,3,1,3);
  M(1,1)=e3;
  M(1,2)=e4;
  M(1,3)=e5;

  M(2,1)=3*e2;
  M(2,2)=4*e3;
  M(2,3)=5*e4;

  M(3,1)=6*e;
  M(3,2)=12*e2;
  M(3,3)=20*e3;

  dvector y(1,3);
  y(1)=mult*e;
  y(2)=0.0;
  y(3)=0;

  coffs=solve(M,y);
}

/**
 * Description not yet available.
 * \param
 */
double function_tweaker::operator () (double x)
{
  if (x>=eps &&x<=1-eps)
  {
    return x;
  }
  else if (x<eps)
  {
    double x2=x*x;
    double x3=x2*x;
    double x4=x3*x;
    double x5=x4*x;
    return mult*eps+x+coffs(3)*x5+coffs(2)*x4+coffs(1)*x3;
  }
  else
  {
    double y=1-x;
    double y2=y*y;
    double y3=y2*y;
    double y4=y3*y;
    double y5=y4*y;
    return 1.0 -(mult*eps+y+coffs(3)*y5+coffs(2)*y4+coffs(1)*y3);
  }
}
