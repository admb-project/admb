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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2function_tweaker::df1b2function_tweaker(double _eps,double _mult):
  mult(_mult), eps(_eps), coffs(1, 3)
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
  y(1)=-mult*eps;
  y(2)=0.0;
  y(3)=0;

  coffs=solve(M,y);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable df1b2function_tweaker::operator () (const df1b2variable& x)
{
  if (value(x)>=eps &&value(x)<=1-eps)
  {
    return x;
  }
  else if (value(x)<eps)
  {
    df1b2variable x2=x*x;
    df1b2variable x3=x2*x;
    df1b2variable x4=x3*x;
    df1b2variable x5=x4*x;
    return mult*eps+x+coffs(3)*x5+coffs(2)*x4+coffs(1)*x3;
  }
  else
  {
    df1b2variable y=1-x;
    df1b2variable y2=y*y;
    df1b2variable y3=y2*y;
    df1b2variable y4=y3*y;
    df1b2variable y5=y4*y;
    double tmp=value(mult*eps+y+coffs(3)*y5+coffs(2)*y4+coffs(1)*y3);
    if (tmp>1.0)
      cout << "H" << endl;
    return 1.0 -(mult*eps+y+coffs(3)*y5+coffs(2)*y4+coffs(1)*y3);
  }
}
