/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>

df1b2variable sin(const df1b2variable& _xx)
{
  ADUNCONST(df1b2variable,xx)
  df1b2variable z;
  double x=value(_xx);
  double f=sin(x);
  double dfx=cos(x);
  double d2f=-f;
  double d3f=-dfx;
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

df1b2variable cos(const df1b2variable& _xx)
{
  ADUNCONST(df1b2variable,xx)
  df1b2variable z;
  double x=value(_xx);
  double f=cos(x);
  double dfx=-sin(x);
  double d2f=-f;
  double d3f=-dfx;
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
