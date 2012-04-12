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
// this is to get UNIX systems to use getchar
// #define UNIXKLUDGE

#ifdef __ZTC__
  #include <conio.h>
#endif

#ifdef __GNUDOS__
  #define ADGETCH getch
#endif

#include <admodel.h>
extern int ctlc_flag;

#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
  #include <iostream.h>
  #include <conio.h>
#endif

#if defined (__WAT32__) || defined(__MSVC32__)
  #include <conio.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <disp.h>
  #define endl "\n"
//  #define if (ad_printf) (*ad_printf) disp_if (ad_printf) (*ad_printf)
  void clrscr(void);
#endif


#ifdef __SUN__
  #include <iostream.h>
  #include <signal.h>
  #define getch getchar
  void clrscr(void); //{ if (ad_printf) (*ad_printf)("\n"); }
  #ifdef __HP__
  extern "C" void onintr(int k);
  #endif
#endif

#if defined(__GNU__) || defined(UNIXKLUDGE)
  #if (__GNUC__ >3)
     #include <iostream>
     using namespace std;
  #else   
    #include <iostream.h>
  #endif
  #include <signal.h>
  #define getch getchar
  //typedef void (*SignalHandler) ();

#if !defined(UNIXKLUDGE) && !defined(linux)
  extern "C" void onintr(int k);
#else
  extern "C" void onintr(int k);
#endif
#endif

#ifdef __NDPX__
  #include <iostream.hxx>
  extern "C" {
    void clrscr();
  };
#endif


#if defined (__MSVC32__)
  //void __cdecl clrscr(void){}
  void __cdecl clrscr(void);
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * Description not yet available.
 * \param
 */
void do_evaluation(double& f,independent_variables& x,dvector& g,int nvar,
  function_minimizer * pmp)
{
  *objective_function_value::pobjfun=0.0;
  dvariable vf=initial_params::reset(dvar_vector(x));
  pmp->userfunction();
  vf+=*objective_function_value::pobjfun;
  gradcalc(nvar,g);
  f=value(vf);
}

/**
 * Description not yet available.
 * \param
 */
double get_second_derivative(double f,independent_variables& x,
  dvector& g,dvector & r,int nvar,function_minimizer * pmp)
{
  const double stepsize=1.e-5;
  dvector g1(1,nvar);
  dvector g2(1,nvar);
  x+=stepsize*r; 
  do_evaluation(f,x,g1,nvar,pmp); 
  x-=2.*stepsize*r; 
  do_evaluation(f,x,g2,nvar,pmp); 
  double scder=r*(g1-g2)/(2.0*stepsize);
  cout << " f = " << f << endl;
  cout << "  second derivative =  " ;
  cout  << " r*(g1-g)/stepsize  = " << scder << endl;
  return scder;
}


  dvector update1(int nvar,int iter,int m,BOR_CONST dvector& g,BOR_CONST dmatrix& xalpha,
    dmatrix& y,BOR_CONST dvector& x,BOR_CONST dvector& xold,BOR_CONST dvector& gold,BOR_CONST dvector& xrho);
double dafsqrt( double x );

/**
 * Description not yet available.
 * \param
 */
void fmmt1::fmin2(BOR_CONST double& _f, BOR_CONST independent_variables & _x,BOR_CONST dvector& _g, function_minimizer * pmp)
{
  //int itn=0; int bigbreak=0; int smallbreak=0; int midbreak=0;
  int itn=0; int smallbreak=0; int midbreak=0;
  int nvar=initial_params::nvarcalc(); // get the number of active
  //double a,f, curf, rnorm, stepsize,b,epsilon;
  double a,f, curf, stepsize,b,epsilon;
  independent_variables x(1,nvar);
  initial_params::xinit(x);    // get the initial values into the
  dvariable vf=0.0;            // x vector
  epsilon=1.e-2;

  dvector curx(1,nvar), g1(1,nvar), xtry(1,nvar), g(1,nvar), r(1,nvar);
  do_evaluation(f,x,g,nvar,pmp); // get initial vales for f and g
  curf=f; curx=x;
  cout << " f = " << f << endl;
  

  do 
  {
    r=update1(n,itn,xm,g,xstep,xy,x,xold,gold,xrho); // get search 

    cout << "  norm(g) =  " << norm(g) ;
    cout << "  r*g/norm(g) =  " << r*g/norm(g) << endl;
    do
    {
      x=curx;
        
      a=get_second_derivative(f,x,g,r,nvar,pmp);
      b=r*g;
  
      stepsize=-b/a;
      do
      {
        xtry=curx+stepsize*r; x=xtry;
        
        do_evaluation(f,x,g,nvar,pmp);
        cout << " f = " << f << endl;
        cout << "  r*g/norm(g) =  " << r*g/norm(g) << endl;
        
        if (f<curf+1.e-10)
        {
          curx=x; curf=f;
          smallbreak=1;
          if (fabs(g*r)/norm(g)<epsilon)
          {
            midbreak=1;
          }
        }
        else
        {
          cout << setprecision(10) << f-curf << endl;
          stepsize=0.001*stepsize; xtry=curx+stepsize*r; 
        }
      }
      while(!smallbreak);
      smallbreak=0;
    }
    while (!midbreak);
    midbreak=0;
    itn++;
  }
  while (1);

      exit(1);
}

/**
 * Description not yet available.
 * \param
 */
  dvector update1(int nvar,int iter,int m,BOR_CONST dvector& g,BOR_CONST dmatrix& _s,
    dmatrix& y,BOR_CONST dvector& x,BOR_CONST dvector& _xold,BOR_CONST dvector& _gold,BOR_CONST dvector& _xrho)
  {
    dvector& xold= (dvector&) _xold;
    dmatrix& s= (dmatrix&) _s;
    dvector& gold= (dvector&) _gold;
    dvector& xrho=(dvector&)_xrho;
    dvector beta(1,nvar);
    dvector alpha(0,m);
    dvector r(1,nvar);
    dvector t(1,nvar);
    int m1=m+1;
    if (iter<1)
    {
      xold=x;
      gold=g;
      r=g;
    }
    else
    {
      int k=iter-1;
      int k1=k%(m1);
      y(k1)=g-gold;
      s(k1)=x-xold;
      xrho(k1)=1./(y(k1)*s(k1));
      xold=x;
      gold=g;
    
      int i;
      int lb=k-m+1;
      if (lb <0) lb=0;
      t=g;
      for (i=k;i>=lb;i--)
      {
        int i1=i%(m1);
        //int i2=(i+1)%(m1);
        //if (i==k)
        {
          alpha(i-lb)=xrho(i1)*(s(i1)*t);
        }
        //else
        //{
        //  alpha(i-lb)=xrho(i1)*( (s(i1)-(s(i1)*s(i2))*s(i2)) * t);
        //}
        t-=alpha(i-lb)*y(i1);
      }
      r=t;
      for (i=lb;i<=k;i++)
      {
        int i1=i%(m1);
        //r+= (alpha(i1)-xrho(i1)*(y(i1)*r)) * s(i1);
        r+= (alpha(i-lb)-xrho(i1)*(y(i1)*r)) * s(i1);
      }
    }
    //cout << r*g/(norm(r)*norm(g)) << endl;
    r/=norm(r);
    return -1.0*r;
  }
