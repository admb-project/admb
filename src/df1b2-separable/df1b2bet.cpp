/**
 * $Id: df1b2bet.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California
 */
#include <df1b2fun.h>
#include "../linad99/betacf_val.hpp"

df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, double x, int MAXIT);
df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, const df1b2variable& x, int MAXIT);

df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, const df1b2variable& x, int MAXIT)
{
  typedef tiny_ad::variable<3, 3> Float;
  Float a_ (value(a), 0);
  Float b_ (value(b), 1);
  Float x_ (value(x), 2);
  Float ans = betacf<Float>(a_, b_, x_, MAXIT);  
  double val=ans.value.value.value;
  tiny_vec<double, 3> der1 = ans.value.value.getDeriv();
  tiny_vec<double, 9> der2 = ans.value.getDeriv();
  tiny_vec<double, 27> der3 = ans.getDeriv();

  df1b2variable tmp;
  value(tmp)=val;
  double * xd=a.get_u_dot();
  double * yd=b.get_u_dot();
  double * zd=x.get_u_dot();
  double * tmpd=tmp.get_u_dot();
  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++ + der1[2] * *zd++;
  }
  if (!df1b2_gradlist::no_derivatives)
  {
    f1b2gradlist->write_pass1(&a,&b,&x,&tmp,
     der1[0],der1[1],der1[2],
     der2[0],der2[1],der2[2],der2[4],der2[5],der2[8],
     der3[0],der3[1],der3[2],der3[4],der3[5],der3[8],der3[13],der3[14],der3[17],der3[26]);
  }
  return tmp;
}

/** Incomplete beta function for df1b2variable objects.
    \param a \f$a\f$
    \param b \f$b\f$
    \param x \f$x\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
df1b2variable betai(const df1b2variable & a,const df1b2variable & b,double x, int maxit)
{
  df1b2variable bt;

  if (x < 0.0 || x > 1.0) cerr << "Bad x in routine betai" << endl;
  if (x == 0.0 || x == 1.0) bt=double(0.0);
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (x < (value(a)+1.0)/(value(a)+value(b)+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}

/** beta distribution function for df1b2variable objects (alias of betai).
    \param x \f$x\f$
    \param a \f$a\f$
    \param b \f$b\f$
    \param maxit Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
df1b2variable pbeta(double x, const df1b2variable & a,const df1b2variable & b, int maxit){
  return betai(a,b,x,maxit);
}

/** Incomplete beta function for df1b2variable objects.
    Evaluates the continued fraction for imcomplete beta function.
    \param _a \f$a\f$
    \param _b \f$b\f$
    \param _x \f$x\f$
    \param MAXIT Maximum number of iterations for the continued fraction approximation in betacf.
    \return Incomplete beta function \f$I_x(a,b)\f$

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2
*/
df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, double x, int MAXIT)
{
  df1b2variable xx;
  xx=x;
  return betacf(a,b,xx,MAXIT);
}

df1b2variable pbeta(const df1b2variable & x, const df1b2variable & a, const df1b2variable & b, int maxit)
{
  df1b2variable bt;

  if (value(x) < 0.0 || value(x) > 1.0) cerr << "Bad x in routine betai" << endl;
  if (value(x) == 0.0 || value(x) == 1.0) bt=double(0.0);
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (value(x) < (value(a)+1.0)/(value(a)+value(b)+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}



