/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>


df1b2variable asin(const df1b2variable& _xx)
{
  ADUNCONST(df1b2variable,xx)
  df1b2variable z;

  double x=value(xx);

  double f=asin(x); 

  double t1=1.0/(1-x*x);
  double dfx = sqrt(t1);

  double t2  = t1*dfx;
  double d2f = t2 *x;

  double d3f = t2 + 3.0* d2f*t1*x;

  double * xd=xx.get_u_dot();
  double * zd=z.get_u_dot();
  *z.get_u()=f;
  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ =dfx * *xd++;
  }
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1(&xx,&z,dfx,d2f,d3f);

  return z;
}

