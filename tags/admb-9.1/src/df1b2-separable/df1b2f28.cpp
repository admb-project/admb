/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>

df1b2variable pow(const df1b2variable& x,const df1b2variable& y)
{
  df1b2variable z;
  double xu=*x.get_u();
  double yu=*y.get_u();
  double xpy3=::pow(xu,yu-3.0);
  double xpy2=xu*xpy3;
  double xpy1=xu*xpy2;
  *z.get_u()=xu*xpy1;
  double zu=*z.get_u();
  double logx=log(xu);
  double y1=yu-1.0;
  double y2=yu-2.0;
  double yy1=yu*y1;

  double dfx= yu*xpy1;
  double dfy= zu*logx;
  double dfxx=yy1*xpy2; 
  double dfxy=xpy1*(1.0+yu*logx);
  double dfyy=dfy*logx;
  double dfxxx=yy1*y2*xpy3;
  double dfxxy=xpy2*(yy1*logx+2.0*yu-1.0);
  double dfxyy=xpy1*logx*(yu*logx*logx+2.0);
  double dfyyy=dfyy*logx;

  double * xd=x.get_u_dot();
  double * yd=y.get_u_dot();
  double * zd=z.get_u_dot();

  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ + dfy * *yd++;
  }
      
  f1b2gradlist->write_pass1(&x,&y,&z,
    dfx,
    dfy,
    dfxx,dfxy,dfyy,
    dfxxx,dfxxy,dfxyy,dfyyy); 
  return z;
}

df1b2variable pow(double x,const df1b2variable& y)
{
  df1b2variable z;
  double yu=*y.get_u();
  double zu=::pow(x,yu);
  *z.get_u()=zu;
  double logx=log(x);

  double dfy= zu*logx;
  double dfyy=dfy*logx;
  double dfyyy=dfyy*logx;

  double * yd=y.get_u_dot();
  double * zd=z.get_u_dot();

  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ =  dfy * *yd++;
  }
      
  f1b2gradlist->write_pass1(&y,&z,
    dfy,
    dfyy,
    dfyyy); 
  return z;
}

df1b2variable operator / (const df1b2variable& x,const df1b2variable& y)
{
  df1b2variable z;
  double xu=*x.get_u();
  double yu=*y.get_u();
  double yinv=1.0/yu;
  *z.get_u()=xu*yinv;
  double zu=*z.get_u();
  double yinv2=yinv*yinv;
  double yinv3=yinv2*yinv;

  double dfx= yinv;
  double dfy= -xu*yinv2;
  double dfxx= 0.0;
  double dfxy=-yinv2;
  double dfyy=2.0*xu*yinv3;
  double dfxxx= 0.0;
  double dfxxy= 0.0;
  double dfxyy=2.0*yinv3;
  double dfyyy=-6.0*xu*yinv3*yinv;

  double * xd=x.get_u_dot();
  double * yd=y.get_u_dot();
  double * zd=z.get_u_dot();

  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ + dfy * *yd++;
  }
      
  f1b2gradlist->write_pass1(&x,&y,&z,
    dfx,
    dfy,
    dfxx,dfxy,dfyy,
    dfxxx,dfxxy,dfxyy,dfyyy); 
  return z;
}

df1b2variable operator / (double x,const df1b2variable& y)
{
  df1b2variable z;
  double yu=*y.get_u();
  double yinv=1.0/yu;
  *z.get_u()=x*yinv;
  double zu=*z.get_u();

 /*
  double dfy= -x*yinv*yinv;
  double dfyy=2.0*x*yinv*yinv*yinv;
  double dfyyy=-6.0*x*yinv*yinv*yinv*yinv;
 */
  double dfy=-zu*yinv;
  double dfyy=-2.0*dfy*yinv;
  double dfyyy=-3.0*dfyy*yinv;

  double * yd=y.get_u_dot();
  double * zd=z.get_u_dot();

  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ =  dfy * *yd++;
  }
      
  f1b2gradlist->write_pass1(&y,&z,
    dfy,
    dfyy,
    dfyyy); 
  return z;
}


df1b2variable pow(const df1b2variable& x,double y)
{
  df1b2variable z;
  double xu=*x.get_u();
  *z.get_u()=::pow(xu,y);
  double zu=*z.get_u();

  double dfx= y*::pow(xu,y-1.0);
  double dfxx= y*(y-1.0)*::pow(xu,y-2.0);
  double dfxxx= y*(y-1.0)*(y-2.0)*::pow(xu,y-3.0);
  double * xd=x.get_u_dot();
  double * zd=z.get_u_dot();

  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ ;
  }
      
  f1b2gradlist->write_pass1(&x,&z,
    dfx,
    dfxx,
    dfxxx);
  return z;
}

/*
df1b2variable square(const df1b2variable& x)
{
  df1b2variable z;
  double xu=*x.get_u();
  *z.get_u()=xu*xu
  double zu=*z.get_u();

  double dfx=2.0*xu 
  double dfxx=2.0; 
  double dfxxx=0.0;
  double * xd=x.get_u_dot();
  double * zd=z.get_u_dot();

  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ ;
  }
      
  f1b2gradlist->write_pass1(&x,&z,
    dfx,
    dfxx,
    dfxxx);
  return z;
}
*/
