/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <fvar.hpp>


dfunction_tweaker::dfunction_tweaker(double _eps,double _mult) : coffs(1,3), 
  eps(_eps) , mult(mult)  
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
  y(1)=mult*eps;
  y(2)=0.0;
  y(3)=0;

  coffs=solve(M,y);
}


dvariable dfunction_tweaker::operator () (const prevariable& x)
{
  if (x>=eps &&x<=1-eps)
  {
    return x;
  }
  else if (x<eps)
  {
    dvariable x2=x*x;
    dvariable x3=x2*x;
    dvariable x4=x3*x;
    dvariable x5=x4*x;
    return mult*eps+x+coffs(3)*x5+coffs(2)*x4+coffs(1)*x3;
  }
  else
  {
    dvariable y=1-x;
    dvariable y2=y*y;
    dvariable y3=y2*y;
    dvariable y4=y3*y;
    dvariable y5=y4*y;
    return 1.0 -(mult*eps+y+coffs(3)*y5+coffs(2)*y4+coffs(1)*y3);
  }
}
