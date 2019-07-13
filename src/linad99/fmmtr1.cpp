/*
 * $Id$
 *
 * Author: Unknown
 * Copyright (c) 2009-2012 ADMB Foundation
 *
 * This file was originally written in FORTRAN II by and unknown author.
 * In the 1980s, it was ported to C and C++ and extensively modified by
 * David Fournier.
 *
 */
/**
 * \file
 * Description not yet available.
 */
#ifdef __ZTC__
  #include <conio.h>
#endif
#include <fvar.hpp>
extern int ctlc_flag;
#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <conio.h>
#endif
#if defined (__WAT32__) || defined(_MSC_VER)
  #include <conio.h>
#endif
#ifdef __ZTC__
  #include <iostream.hpp>
  #include <disp.h>
  #define endl "\n"
#endif
#ifdef __SUN__
  #include <iostream.h>
  #include <signal.h>
  #define getch getchar
  #ifdef __HP__
  extern "C" void onintr(int k);
  #endif
#endif
#ifdef __NDPX__
  #include <iostream.hxx>
#endif
#if defined (_MSC_VER)
  void __cdecl clrscr();
#endif
#if defined (_WIN32)
  #include <conio.h>
  BOOL CtrlHandler(DWORD fdwCtrlType);
#else
  #include <iostream>
  #include <signal.h>
  #define getch getchar
  extern "C" void onintr(int k);
  extern "C" void clrscr();
#endif
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
dvector update(int nvar, int iter, int m, const dvector& g,
  const dmatrix& xalpha, dmatrix& y, const dvector& x, const dvector& xold,
  const dvector& gold, const dvector& xrho);
double dafsqrt( double x );

/**
 * Description not yet available.
 * \param
 */
void fmmt1::fmin(const double& _f, const dvector & _x, const dvector& _g)
{
  double& f=(double&) _f;
  independent_variables & x=(independent_variables &) _x;
  dvector& g=(dvector&) _g;
    #ifdef DIAG
      cout << "On entry to fmin: " << *this << endl;
    #endif
  if (use_control_c)
  {
#if defined (_WIN32)
  SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
#else
    if (ireturn <= 0 )
    {
  #if defined(__GNUC__)
      signal(SIGINT, &onintr);
  #else
      signal(SIGINT, (SIG_PF)&onintr);
  #endif
    }
#endif
  }
    #ifdef __ZTC__
      if (ireturn <= 0 )
      {
        if (disp_inited == 0)
        {
          disp_open();
          disp_usebios();
        }
      }
    #endif
      if (ireturn >= 3)
      {
         derch(f, x, g, n, ireturn);
         return;
      }
      if (ireturn == 1) goto call1;
      if (ireturn == 2) goto call2;
      ihflag=0;
     if (n <= 0)
     {
       cerr << "Error -- the number of active parameters"
         " fmin must be > 0\n";
       ad_exit(1);
     }
     if (x.indexmin() !=1)
     {
       cerr << "Error -- minimum valid index"
         " for independent_variables in fmin must be 1\n"
        << " it is " << x.indexmin() << "\n";
        ad_exit(1);
     }
     if (x.size() < static_cast<unsigned int>(n))
     {
       cerr << "Error -- the size of the independent_variables"
        " which is " << x.size() << " must be >= " << n << "\n"
        << " the number of independent variables in fmin\n";
        ad_exit(1);
     }
     if (g.indexmin() !=1)
     {
       cerr << "Error -- minimum valid index"
         " for the gradient vector in fmin must be 1\n"
        << " it is " << g.indexmin() << "\n";
        ad_exit(1);
     }
     if (g.size() < static_cast<unsigned int>(n))
     {
       cerr << "Error -- the size of the gradient vector"
        " which is " << g.size() << " must be >=\n"
        << " the number of independent variables in fmin\n";
        ad_exit(1);
     }
     for (i=1; i<=n; i++)
           xx.elem(i)=x.elem(i);
      itn=0;
      icc=0;
       for (i=1; i< 11; i++)
          funval.elem(i)=0.;
      ihang = 0;
      llog=1;
      np=n+1;
      n1=n-1;
      nn=n*np/2;
      is=n;
      iu=n;
      iv=n+n;
      ib=iv+n;
      iexit=0;
      dmin=1;
      if (dmin <= 0.)
         goto label7020;
      if(dfn == 0.)
         z = 0.0;
      for (i=1; i<=n; i++)
      {
        xsave.elem(i)=x.elem(i);
        x.elem(i)=xx.elem(i);
      }
      ireturn=1;
      return;
  call1:
      for (i=1; i<=n; i++)
      {
        x.elem(i)=xsave.elem(i);
      }
      ireturn=3;
      fbest = f;
      for ( i=1; i<=n; i++)
         gbest.elem(i)=g.elem(i);
      funval.elem(10) = f;
      df=dfn;
      if(dfn == 0.0)
         df = f - z;
      if(dfn < 0.0)
         df=fabs(df * f);
      if(df <= 0.0)
         df=1.;
label20:
      ic=0;
      iconv = 1;
      for ( i=1; i<=9; i++)
         funval.elem(i)= funval.elem(i+1);
      funval.elem(10) = f;
      if ( itn>15 && fabs( funval.elem(1)-funval.elem(10))< min_improve )
         ihang = 1;
      gmax = 0;
      for ( i=1; i<=n; i++)
      {
        if(fabs(g.elem(i)) > crit) iconv = 2;
        if(fabs(g.elem(i)) > fabs(gmax) ) gmax = g.elem(i);
      }
      if( iconv == 1 || ihang == 1)
      {
         ireturn=-1;
         goto label92;
      }
      if(iprint == 0)
         goto label21;
      if(itn == 0)
         goto label7000;
      if( (itn%iprint) != 0)
         goto label21;
      if (llog) goto label7010;
#if !defined (_MSC_VER)  && !defined (__GNUC__)
        if (!scroll_flag) clrscr();
#endif
label7003:
      if (iprint!=0)
      {
        if (ad_printf)
          (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
              n, itn, ifn);
        if (ad_printf)
(*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
            f, gmax);
      }
/*label7002:*/
      /* Printing Statistics table */
      if(iprint>0)
      {
        fmmdisp(x, g, n, this->scroll_flag,noprintx);
      }
label21 :
      itn++;
      rrr=update(n,itn-1,xm,g,xstep,xy,x,xold,gold,xrho);
      for (i=1; i<=n; i++)
         x.elem(i)=xx.elem(i);
      for (i=1; i<=n; i++)
      {
        w.elem(i)=-g.elem(i);
      }
      for (i=1; i<=n; i++)
      {
        w(n+i)=rrr(i);
      }
      gs=0.0;
      for (i=1; i<=n; i++)
         gs+=w.elem(is+i)*g.elem(i);
      iexit=2;
      if(gs >= 0.0)
      {
        double a=1.1*gs/norm2(g);
        for (i=1; i<=n; i++)
           w.elem(is+i)-=a*g.elem(i);
        gs=0.0;
        for (i=1; i<=n; i++)
          gs+=w.elem(is+i)*g.elem(i);
        if(gs >= 0.0)
        {
          cout << "Kludge didn't work" << endl;
          goto label92;
        }
      }
      gso=gs;
      alpha=-2.0*df/gs;
      if(alpha > 1.0)
        alpha=1.0;
      df=f;
      tot=0.0;
label30:
      iexit=3;
      if( ifn >= maxfn)
      {
         maxfn_flag=1;
         goto label92;
      }
      else
      {
         maxfn_flag=0;
         iexit=1;
      }
      if(quit_flag && use_control_c) goto label92;
      for (i=1; i<=n; i++)
      {
        z=alpha*w.elem(is+i);
        xx.elem(i)+=z;
      }
      for (i=1; i<=n; i++)
      {
        xsave.elem(i)=x.elem(i);
        gsave.elem(i)=g.elem(i);
        x.elem(i)=xx.elem(i);
        fsave = f;
      }
      fsave = f;
      ireturn=2;
      return;
  call2:
      for (i=1; i<=n; i++)
      {
        x.elem(i)=xsave.elem(i);
        w.elem(i)=g.elem(i);
        g.elem(i)=gsave.elem(i);
      }
      fy = f;
      f = fsave;
      ireturn=-1;
      if (fy < fbest)
      {
        fbest=fy;
        for (i=1; i<=n; i++)
        {
          x.elem(i)=xx.elem(i);
          gbest.elem(i)=w.elem(i);
        }
      }
#if defined(_MSC_VER)
       if (kbhit())
#else
       if(ctlc_flag && use_control_c)
#endif
       {
          #if defined(__DJGPP__)
            int c = toupper(getxkey());
          #else
            int c = toupper(getch());
          #endif
          if ( c == 'C')
          {
            for (i=1; i<=n; i++)
            {
              x.elem(i)=xx.elem(i);
            }
            ireturn = 3;
            derch(f, x , w, n, ireturn);
            return;
          }
          else
          {
            if ( c == 'Q'|| c == 'N')
            {
              quit_flag=c;
              goto label92;
            }
            else
            {
              quit_flag=0;
            }
          }
       }
       icc+=1;
       if( icc >= 5)
          icc=0;
      ic++;
      if( ic >imax)
      {
         if (iprint>0)
         {
           if (ad_printf)
             (*ad_printf)("  ic > imax  in fminim is answer attained ?\n" );
           fmmdisp(x, g, n, this->scroll_flag,noprintx);
         }
         ihflag=1;
         ihang=1;
         goto label92;
      }
      ifn++;
      gys=0.0;
      for (i=1; i<= n; i++)
         gys+=w.elem(i)*w.elem(is+i);
      if(fy>=f)
         goto label40;
      if(fabs(gys/gso)<=.9)
         goto label50;
      if(fabs(gys/gso)<=.95 && ic > 4)
         goto label50;
      if(gys>0.0)
         goto  label40;
      tot+=alpha;
      z=10.0;
      if(gs<gys)
         z=gys/(gs-gys);
      if(z>10.0)
         z=10.0;
      alpha=alpha*z;
      if (alpha == 0.)
      {
         ialph=1;
         #ifdef __ZTC__
         if (ireturn <= 0)
         {
           disp_close();
         }
         #endif
         return;
      }
      f=fy;
      gs=gys;
      goto label30;
label40:
      for (i=1;i<=n;i++)
         xx.elem(i)-=alpha*w.elem(is+i);
      z=3.0*(f-fy)/alpha+gys+gs;
      zz=dafsqrt(z*z-gs*gys);
      z=1.0-(gys+zz-z)/(2.0*zz+gys-gs);
      if (fabs(fy-1.e+95) < 1.e-66)
      {
        alpha*=.001;
      }
      else
      {
        alpha=alpha*z;
      }
      if (alpha == 0.)
      {
         ialph=1;
         #ifdef __ZTC__
         if (ireturn <= 0)
         {
           disp_close();
         }
         #endif
         return;
      }
      goto label30;
label50:
      alpha+=tot;
      f=fy;
      df-=f;
      dgs=gys-gso;
      link=1;
      if(dgs+alpha*gso>0.0)
         goto label52;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=w.elem(i)-g.elem(i);
      sig=1.0/(alpha*dgs);
      goto label70;
label52:
      zz=alpha/(dgs-alpha*gso);
      z=dgs*zz-1.0;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=z*g.elem(i)+w.elem(i);
      sig=1.0/(zz*dgs*dgs);
      goto label70;
label60:
      link=2;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=g.elem(i);
      if(dgs+alpha*gso>0.0)
         goto label62;
      sig=1.0/gso;
      goto  label70;
label62:
      sig=-zz;
      goto label70;
label65:
      for (i=1;i<=n;i++)
         g.elem(i)=w.elem(i);
      goto  label20;
label70:
      if (link == 1) goto label60;
      if (link == 2) goto label65;
/*label90:*/
      for (i=1;i<=n;i++)
         g.elem(i)=w.elem(i);
label92:
      if (iprint>0)
      {
        if (ihang == 1)
          if (ad_printf)
            (*ad_printf)(
           "Function minimizer not making progress ... is minimum attained?\n");
      }
      if(iexit == 2)
      {
        if (iprint>0)
        {
          if (ad_printf)
            (*ad_printf)("*** grad transpose times delta x greater >= 0\n"
           " --- convergence critera may be too strict\n");
          ireturn=-1;
        }
      }
#     if defined (_MSC_VER)  && !defined (__WAT32__)
        if (scroll_flag == 0) clrscr();
#     endif
      if (maxfn_flag == 1)
      {
        if (iprint>0)
        {
          if (ad_printf)
            (*ad_printf)("Maximum number of function evaluations exceeded");
        }
      }
      if (iprint>0)
      {
        if (quit_flag == 'Q' && use_control_c)
          if (ad_printf) (*ad_printf)("User initiated interrupt");
      }
      if(iprint == 0) goto label777;
      if (ad_printf) (*ad_printf)(" - final statistics:\n");
      if (ad_printf)
        (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
          n, itn, ifn);
      if (ad_printf)
        (*ad_printf)(
        "Function value %12.4le; maximum gradient component mag %12.4le\n",
        f, gmax);
      if (ad_printf)
        (*ad_printf)("Exit code = %ld;  converg criter %12.4le\n",iexit,crit);

      fmmdisp(x, g, n, this->scroll_flag,noprintx);
label777:
         if (ireturn <= 0)
         #ifdef DIAG
           if (ad_printf) (*ad_printf)("Final values of h in fmin:\n");
           cout << h << "\n";
         #endif
         #ifdef __ZTC__
         {
           disp_close();
         }
         #endif
         return;
label7000:
      if (iprint>0)
      {
#     if defined (_MSC_VER)  && !defined (__WAT32__)
        if (!scroll_flag) clrscr();
#endif
        if (ad_printf) (*ad_printf)("Initial statistics: ");
      }
      goto label7003;
label7010:
   if (iprint>0)
   {
#     if defined (_MSC_VER)  && !defined (__WAT32__)
     if (!scroll_flag)  clrscr();
#endif
     if (ad_printf) (*ad_printf)("Intermediate statistics: ");
   }
   llog=0;
   goto label7003;
label7020:
   if (iprint>0)
   {
     if (ad_printf) (*ad_printf)("*** hessian not positive definite\n");
   }
         #ifdef __ZTC__
         if (ireturn <= 0)
         {
           disp_close();
         }
         #endif
         return;
   }

/**
 * Description not yet available.
 * \param
 */
dvector update(int nvar, int iter, int m, const dvector& g, const dmatrix& _s,
  dmatrix& y, const dvector& x, const dvector& _xold, const dvector& _gold,
  const dvector& _xrho)
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
        {
          alpha(i-lb)=xrho(i1)*(s(i1)*t);
        }
        t-=alpha(i-lb)*y(i1);
      }
      r=t;
      for (i=lb;i<=k;i++)
      {
        int i1=i%(m1);
        r+= (alpha(i-lb)-xrho(i1)*(y(i1)*r)) * s(i1);
      }
    }
    return -1.0*r;
  }
