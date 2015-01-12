/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
df1b2variable gammlnguts(const df1b2variable _zz)
{
  ADUNCONST(df1b2variable,zz)
  df1b2variable u;
  double  z = value(_zz);
  //double zdot=1.0;
  //double z2dot=0.0;
  //double z3dot=0.0;
  //const double lpi =1.1447298858494001741434272;
  //const double pi =3.1415926535897932384626432;
  const double lpp =0.9189385332046727417803297;
  int n=7;
  const double c[9]={0.99999999999980993, 
    676.5203681218851, 
    -1259.1392167224028,
     771.32342877765313, 
    -176.61502916214059, 
    12.507343278686905,
     -0.13857109526572012, 
    9.9843695780195716e-6, 
    1.5056327351493116e-7};
  z-=1.0;
  double x=c[0];
  double xdot=0.0;
  double x2dot=0.0;
  double x3dot=0.0;
  int i;
  for (i=1;i<=n+1;i++)
  {
    double zinv=1.0/(z+i);
    x+=c[i]*zinv;
    //xdot-=c[i]/square(z+i)*zdot;  since zdot=1.0
    xdot-=c[i]*square(zinv);
    x2dot+=2.0*c[i]*cube(zinv);
    x3dot-=6.0*c[i]*fourth(zinv);
  }    
  double t=z+n+0.5;
  //double tdot=zdot;
  //return lpp + (z+0.5)*log(t) -t + log(x);
  double ans= lpp + (z+0.5)*log(t) -t + log(x);
  //double dfx=zdot*log(t) + (z+0.5)/t*tdot -tdot +xdot/x;
  // since tdot=1.0
  // since zdot=1.0
  double dfx=log(t) + (z+0.5)/t -1.0 +xdot/x;
  double d2f=2.0/t -(z+0.5)/square(t)+x2dot/x
    -square(xdot)/square(x);
  double d3f=-3.0/square(t) + 2.0*(z+0.5)/cube(t)+ x3dot/x
    -3.0*x2dot*xdot/square(x)+2.0*cube(xdot)/cube(x);

  double * xd=zz.get_u_dot();
  double * zd=u.get_u_dot();
  *u.get_u()=ans;
  for (i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ =dfx * *xd++;
  }

  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1(&zz,&u,dfx,d2f,d3f);
  return(u);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable gammln(const df1b2variable& z)
{
  const double lpi =1.1447298858494001741434272;
  const double pi =3.1415926535897932384626432;
  if (value(z)<0.5)
  {
    return lpi - log(sin(pi*z)) - gammlnguts(1.0-z);
  }
  else
  {
    return gammlnguts(z);
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector gammln(const df1b2vector&  z){
  int from=z.indexmin();
  int to=z.indexmax();
  df1b2vector ret(from,to);
  for(int i=from; i<=to; ++i){
    ret(i)=gammln(z(i));
 }
 return(ret);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable log_comb(_CONST df1b2variable& n,double k)
{
  return factln(n)-factln(k)-factln(n-k);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable log_comb(_CONST df1b2variable& n,_CONST df1b2variable& k)
{
  return factln(n)-factln(k)-factln(n-k);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable log_comb(double n,_CONST df1b2variable& k)
{
  return factln(n)-factln(k)-factln(n-k);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable factln(_CONST df1b2variable& n)
{
  return gammln(n+1.0);
}
