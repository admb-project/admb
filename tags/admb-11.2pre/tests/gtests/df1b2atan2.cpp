/*
$Id$

Author: David Fournier
Copyright (c) 2013 ADMB Foundation
*/
#include <df1b2fun.h>

/**
Computes arc tangent with df1b2variables y and x. 

\param y y-coordinate
\param x x-coordinate
\return Return arc tangent value in radians. 
*/
df1b2variable atan2(const df1b2variable& y, const df1b2variable& x)
{
  df1b2variable z;
  double xu=*x.get_u();
  double yu=*y.get_u();
  double r2=square(xu)+square(yu);
  double zu=::atan2(yu,xu);
  *z.get_u()=zu;

  double dfx=-yu/r2;
  double dfy=xu/r2;
  double dfxx=2.0*yu*xu/square(r2);
  double dfxy=-1.0/r2+2.0*square(yu)/square(r2);
  double dfyy=-2.0*xu*yu/square(r2);
  double dfxxx=2.0*yu/square(r2)-8.0*yu*square(xu)/cube(r2);
  double dfxxy=2.0*xu/square(r2)-8.0*square(yu)*xu/cube(r2);
  double dfxyy=-2.0*yu/square(r2)+8.0*square(xu)*yu/cube(r2);
  double dfyyy=-2.0*xu/square(r2)+8.0*xu*square(yu)/cube(r2);

  double* xd=x.get_u_dot();
  double* yd=y.get_u_dot();
  double* zd=z.get_u_dot();

  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * (*xd++) + dfy * (*yd++);
  }

  f1b2gradlist->write_pass1(&y,&x,&z,
      dfy,
      dfx,
      dfyy,dfxy,dfxx,
      dfyyy,dfxyy,dfxxy,dfxxx);

  return z;
}
