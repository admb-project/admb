/**
 * $Id: df1b2invcumdbeta.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: Unknown
 */
#include <df1b2fun.h>
#include <admodel.h>
#include <df3fun.h>
#include "df33fun.h"
#define MAXIT 100
#define EPS 1.0e-9
//#define EPS 3.0e-7
#define FPMIN 1.0e-30
  df1b2variable inv_cumd_beta_stable(const df1b2variable& a,
    const df1b2variable& b,const df1b2variable& x);
  df1b2variable inv_cumd_beta_stable(const df1b2variable& a,
    const df1b2variable& b,const df1b2variable& x,double eps);

  df3_three_variable gammln(const df3_three_variable& xx);
  df3_three_variable betacf(const df3_three_variable& a,
    const df3_three_variable& b,const df3_three_variable& x);
  df3_three_variable betacf(const df3_three_variable& a,
    const df3_three_variable& b, double x);
  df3_three_variable betai(const df3_three_variable& a,
    const df3_three_variable& b,const df3_three_variable& x,int maxit);
  df3_three_variable betai(const df3_three_variable& a,
    const df3_three_variable& b, double x,int maxit);

/*
  static double lnbeta(double a,double b)
  {
    return gammln(a)+gammln(b)-gammln(a+b);
  }

  static int sgn(double z)
  {
    if (z>=0)
      return 1;
    else
      return -1;
  }
*/

  double inv_cumd_beta(double _a,double _b,double _y);
  double inv_cumd_beta_stable(double _a,double _b,double _y,double eps);

  df1b2variable inv_cumd_beta_stable(const df1b2variable& _a,
    const df1b2variable& _b,const df1b2variable& _y,double eps)
  {
    ADUNCONST(df1b2variable,a);
    ADUNCONST(df1b2variable,b);
    ADUNCONST(df1b2variable,y);

    double eps1=1.0-eps;
    // this gets the inverse without derivatives
    double ca=value(a);
    double cb=value(b);
    double cx=inv_cumd_beta_stable(ca,cb,value(y),eps);

    init_df3_three_variable vx(cx);
    init_df3_three_variable va(_a);
    init_df3_three_variable vb(_b);

    // this gets the derivatives for the function itself

    df3_three_variable z=(betai(va,vb,vx,25)-betai(va,vb,eps,25))/
      (betai(va,vb,eps1,25)-betai(va,vb,eps,25));

    // now solve for the derivatves of the inverse function
    double F_x=1.0/(*z.get_u_x());
    double F_y=-F_x* *z.get_u_y();
    double F_z=-F_x* *z.get_u_z();

    double F_xx=-F_x* *z.get_u_xx()/square(*z.get_u_x());

    double F_xy=-(F_xx * *z.get_u_x() * *z.get_u_y() + F_x * *z.get_u_xy())/
                *z.get_u_x();

    double F_xz=-(F_xx * *z.get_u_x() * *z.get_u_z() + F_x * *z.get_u_xz())/
                *z.get_u_x();
    double F_yy=-(F_xx * square(*z.get_u_y())
                +2.0* F_xy* *z.get_u_y()
                +F_x * *z.get_u_yy());

    double F_yz=-( F_xx * *z.get_u_y() * *z.get_u_z()
                 + F_x * *z.get_u_yz()
                 + F_xy * *z.get_u_z()
                 + F_xz * *z.get_u_y());

    double F_zz=-(F_xx * square(*z.get_u_z())
                +2.0* F_xz* *z.get_u_z()
                +F_x * *z.get_u_zz());

    double F_xxx=-(F_x* *z.get_u_xxx()
                +3.0*F_xx* *z.get_u_x() * *z.get_u_xx())
                /cube(*z.get_u_x());
    double F_xxy=-(F_xxx * square(*z.get_u_x())* *z.get_u_y()
                 + 2.0*F_xx* *z.get_u_x()* *z.get_u_xy()
                 + F_xx* *z.get_u_xx() * *z.get_u_y()
                 + F_xy * *z.get_u_xx()
                 + F_x * *z.get_u_xxy())/
                 square(*z.get_u_x());
    double F_xxz=-(F_xxx * square(*z.get_u_x())* *z.get_u_z()
                 + 2.0*F_xx* *z.get_u_x()* *z.get_u_xz()
                 + F_xx* *z.get_u_xx() * *z.get_u_z()
                 + F_xz * *z.get_u_xx()
                 + F_x * *z.get_u_xxz())/
                 square(*z.get_u_x());
    double F_xyy=-(F_xxx* *z.get_u_x() *square(*z.get_u_y())
                 +2.0* F_xx * *z.get_u_xy() * *z.get_u_y()
                 +2.0*F_xxy * *z.get_u_x() * *z.get_u_y()
                 + 2.0*F_xy * *z.get_u_xy()
                 + F_xx * *z.get_u_x() * *z.get_u_yy()
                 + F_x * *z.get_u_xyy())/
                 *z.get_u_x();
    double F_xyz=-(F_xxx* *z.get_u_x() * *z.get_u_y() * *z.get_u_z()

                 +F_xx * *z.get_u_xy() * *z.get_u_z()
                 +F_xx * *z.get_u_xz() * *z.get_u_y()
                 +F_xx * *z.get_u_x() * *z.get_u_yz()

                 +F_xxy * *z.get_u_x() * *z.get_u_z()
                 +F_xxz * *z.get_u_x() * *z.get_u_y()

                 + F_xy * *z.get_u_xz()
                 + F_xz * *z.get_u_xy()

                 + F_x * *z.get_u_xyz())/
                 *z.get_u_x();

    double F_xzz=-(F_xxx* *z.get_u_x() *square(*z.get_u_z())
                 +2.0* F_xx * *z.get_u_xz() * *z.get_u_z()
                 +2.0*F_xxz * *z.get_u_x() * *z.get_u_z()
                 + 2.0*F_xz * *z.get_u_xz()
                 + F_xx * *z.get_u_x() * *z.get_u_zz()
                 + F_x * *z.get_u_xzz())/
                 *z.get_u_x();
     double F_yyy=-(F_xxx*cube(*z.get_u_y())+
                 +3.0*F_xxy*square(*z.get_u_y())
                 +3.0*F_xx* *z.get_u_y() * *z.get_u_yy()
                 +3.0*F_xy* *z.get_u_yy()
                 +3.0*F_xyy * *z.get_u_y()
                 +F_x * *z.get_u_yyy());

     double F_yyz=-(F_xxx * square(*z.get_u_y())* *z.get_u_z()
                 +2.0*F_xxy * *z.get_u_y() * *z.get_u_z()
                 +2.0*F_xyz* *z.get_u_y()
                 +F_xxz*square(*z.get_u_y())
                 +2.0*F_xx* *z.get_u_y() * *z.get_u_yz()
                 +F_xx* *z.get_u_z() * *z.get_u_yy()
                 +2.0*F_xy* *z.get_u_yz()
                 +F_xz * *z.get_u_yy()
                 +F_xyy * *z.get_u_z()
                 +F_x * *z.get_u_yyz());
     double F_yzz=-(F_xxx * square(*z.get_u_z())* *z.get_u_y()
                 +2.0*F_xxz * *z.get_u_z() * *z.get_u_y()
                 +2.0*F_xyz* *z.get_u_z()
                 +F_xxy*square(*z.get_u_z())
                 +2.0*F_xx* *z.get_u_z() * *z.get_u_yz()
                 +F_xx* *z.get_u_y() * *z.get_u_zz()
                 +2.0*F_xz* *z.get_u_yz()
                 +F_xy * *z.get_u_zz()* *z.get_u_y()
                 +F_xzz * *z.get_u_y()
                 +F_x * *z.get_u_yzz());

     double F_zzz=-(F_xxx*cube(*z.get_u_z())+
                 +3.0*F_xxz*square(*z.get_u_z())
                 +3.0*F_xx* *z.get_u_z() * *z.get_u_zz()
                 +3.0*F_xz* *z.get_u_zz()
                 +3.0*F_xzz * *z.get_u_z()
                 +F_x * *z.get_u_zzz());

     df1b2variable tmp;
     double * xd=_y.get_u_dot();
     double * yd=_a.get_u_dot();
     double * zd=_b.get_u_dot();
     double * tmpd=tmp.get_u_dot();
     *tmp.get_u()=cx;
     for (unsigned int i=0;i<df1b2variable::nvar;i++)
     {
       *tmpd++ = F_x * *xd++ + F_y * *yd++ + F_z * *zd++;
     }
     if (!df1b2_gradlist::no_derivatives)
     {
       f1b2gradlist->write_pass1(&_y,&_a,&_b,&tmp,
        F_x,F_y,F_z,
        F_xx,F_xy,F_xz,F_yy,F_yz,F_zz,F_xxx,F_xxy,F_xxz,F_xyy,F_xyz,
        F_xzz,F_yyy,F_yyz,F_yzz,F_zzz);
     }

    return tmp;
  }

 /** Incomplete beta function for df3_three_variable objects.
    \param a \f$a\f$
    \param b \f$b\f$
    \param x \f$x\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$
`
    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
  df3_three_variable betai(const df3_three_variable& a,
    const df3_three_variable& b,const  df3_three_variable& x,int maxit)
  {
    df3_three_variable bt;

    if (value(x) < 0.0 || value(x) > 1.0)
      cerr << "Bad x in routine betai" << endl;
    if (value(x) == 0.0 || value(x) == 1.0) bt=0.0;
    else
      bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
    if (value(x) < (value(a)+1.0)/(value(a)+value(b)+2.0))
      return bt*betacf(a,b,x)/a;
    else
      return 1.0-bt*betacf(b,a,1.0-x)/b;
  }

  df3_three_variable betai(const df3_three_variable& a,
    const df3_three_variable& b, double x,int maxit)
  {
    df3_three_variable bt;

    if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
    if (x == 0.0 || x == 1.0) bt=0.0;
    else
      bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
    if (x < (value(a)+1.0)/(value(a)+value(b)+2.0))
      return bt*betacf(a,b,x)/a;
    else
      return 1.0-bt*betacf(b,a,1.0-x)/b;
  }

  df3_three_variable betacf(const df3_three_variable& a,
    const  df3_three_variable& b, double x)
  {
    int m,m2;
    df3_three_variable aa,c,d,del,h,qab,qam,qap;

    qab=a+b;
    qap=a+1.0;
    qam=a-1.0;
    c=1.0;
    d=1.0-qab*x/qap;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    d=1.0/d;
    h=d;
    for (m=1;m<=MAXIT;m++)
    {
      m2=2*m;
      aa=m*(b-m)*x/((qam+m2)*(a+m2));
      d=1.0+aa*d;
      if (fabs(value(d)) < FPMIN) d=FPMIN;
      c=1.0+aa/c;
      if (fabs(value(c)) < FPMIN) c=FPMIN;
      d=1.0/d;
      h *= d*c;
      aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
      d=1.0+aa*d;
      if (fabs(value(d)) < FPMIN) d=FPMIN;
      c=1.0+aa/c;
      if (fabs(value(c)) < FPMIN) c=FPMIN;
      d=1.0/d;

      del=d*c;
      h *= del;
      if (fabs(value(del)-1.0) < EPS) break;
    }
    if (m > MAXIT)
    {
      cerr << "mum interations exceeded " << endl;
      ad_exit(1);
    }
    return h;
  }

/** Incomplete beta function for df3_three_variable objects.
    \param a \f$a\f$
    \param b \f$b\f$
    \param x \f$x\f$
    Evaluates the continued fraction approximation for imcomplete beta function.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
  df3_three_variable betacf(const df3_three_variable& a,
    const df3_three_variable& b, const df3_three_variable& x)
  {
    int m,m2;
    df3_three_variable aa,c,d,del,h,qab,qam,qap;

    qab=a+b;
    qap=a+1.0;
    qam=a-1.0;
    c=1.0;
    d=1.0-qab*x/qap;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    d=1.0/d;
    h=d;
    for (m=1;m<=MAXIT;m++)
    {
      m2=2*m;
      aa=m*(b-m)*x/((qam+m2)*(a+m2));
      d=1.0+aa*d;
      if (fabs(value(d)) < FPMIN) d=FPMIN;
      c=1.0+aa/c;
      if (fabs(value(c)) < FPMIN) c=FPMIN;
      d=1.0/d;
      h *= d*c;
      aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
      d=1.0+aa*d;
      if (fabs(value(d)) < FPMIN) d=FPMIN;
      c=1.0+aa/c;
      if (fabs(value(c)) < FPMIN) c=FPMIN;
      d=1.0/d;

      del=d*c;
      h *= del;
      if (fabs(value(del)-1.0) < EPS) break;
    }
    if (m > MAXIT)
    {
      cerr << "mum interations exceeded " << endl;
      ad_exit(1);
    }
    return h;
  }

static df3_three_variable gammlnguts(const df3_three_variable& _z)
{
  df3_three_variable x;
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
  df3_three_variable z=_z-1.0;
  x=c[0];
  for (int i=1;i<=n+1;i++)
  {
    df3_three_variable zinv=1.0/(z+i);
    x+=c[i]*zinv;
  }
  df3_three_variable t=z+n+0.5;
  df3_three_variable ans= lpp + (z+0.5)*log(t) -t + log(x);
  return(ans);
}

df3_three_variable gammln(const df3_three_variable& z)
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


df1b2variable qbeta(df1b2variable x, df1b2variable a, df1b2variable b, double eps){
  return inv_cumd_beta_stable(a,b,x,eps);
}
