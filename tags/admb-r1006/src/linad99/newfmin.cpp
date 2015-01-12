/*
 * $Id$
 *
 * Author: Unknown
 * Copyright (c) 2009-2011 ADMB Foundation
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

#include <fvar.hpp>
#if defined(__SPDLL__)
#  if !defined(linux)
#    include <windows.h>
#  endif
#include <admodel.h>
#include <s.h>
#include <newredef.h>
#endif
#if defined(__BORLANDC__)
  #include <signal.h>
#endif
#ifdef __ZTC__
  #include <conio.h>
#endif
#ifdef __GNUDOS__
  #define ADGETCH getch
#endif
#include <fvar.hpp>
extern int ctlc_flag;
#if defined(__TURBOC__) && defined(__linux__)
  void clrscr(void);
#endif
#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
  #include <iostream.h>
  #include <conio.h>
#endif
#if defined (__WAT32__) || defined (__MSVC32__) 
  #include <conio.h>
#endif
#if defined(__CYGWIN__)
  int kbhit(void)
  {
    return 0;
  }
#endif
#ifdef __ZTC__
  #include <iostream.hpp>
  #include <disp.h>
  #define endl "\n"
  void clrscr(void);
#endif
#ifdef __SUN__
  #define getch getchar
  void clrscr(void); 
#endif
#if defined(__GNU__) || defined(UNIXKLUDGE)
  #define getch getchar
#endif
  #include <signal.h>
  extern "C" void onintr(int k)
  {
    signal(SIGINT, exit_handler);
    ctlc_flag = 1;
    if (ad_printf) (*ad_printf)("\npress q to quit or c to invoke derivative checker: ");
  }
#ifdef __NDPX__
  #include <iostream.hxx>
  extern "C" {
    void clrscr();
  };
#endif
#if defined (__MSVC32__)
  void __cdecl clrscr(void);
#endif
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int* pointer_to_phase = 0;

double dafsqrt( double x );
  void tracing_message(int traceflag,const char *s);
  void tracing_message(int traceflag,const char *s,int *pn);
  void tracing_message(int traceflag,const char *s,double *pd);
  void tracing_message(int traceflag,const char *s,double d);

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << endl;
      ofs.close();
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s,int *pn)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << " " << *pn << endl;
      ofs.close();
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s,double *pd)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << " " << *pd << endl;
      ofs.close();
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int traceflag,const char *s,double d)
  {
    if (traceflag)
    {
      ofstream ofs;
      ofs.open("adtrace",ios::app);
      ofs << s << " " << d << endl;
      ofs.close();
    }
  }
int log_values_switch=0;
ofstream logstream("fmin.log");

/**
 * Description not yet available.
 * \param
 */
void print_values(const double& f, const dvector & x,const dvector& g)
{
  logstream << setprecision(13) << f << endl;
  logstream << setprecision(13) << x << endl;
  logstream << setprecision(13) << g << endl;
}
extern adtimer * pfmintime=0;
extern int traceflag;
#pragma warn -sig

/**
 * Description not yet available.
 * \param
 */
void fmm::fmin(BOR_CONST double& _f, const dvector & _x,BOR_CONST dvector& _g)
{
  if (log_values_switch)
  {
    print_values(_f,_x,_g);
  }
  if (pfmintime==0) pfmintime=new adtimer;
  tracing_message(traceflag,"A3");
  dvector& g=(dvector&) _g;
  double& f=(double&) _f;
  independent_variables& x= (independent_variables&) _x;
    #ifdef DIAG
      cout << "On entry to fmin: " << *this << endl;
    #endif
  tracing_message(traceflag,"A4");
#if !defined (__MSVC32__)
    #if defined( __SUN__) && !(defined __GNU__)
      #if defined( __HP__)
        if (ireturn <= 0 )
        {
	   signal(SIGINT, &onintr);
        }
      #else
        if (ireturn <= 0 )
        {
	   signal(SIGINT, (SIG_PF)&onintr);
        }
      #endif
    #endif
 #endif
    #if defined( __GNU__) || defined (__BORLANDC__)
      if (ireturn <= 0 ) 
      {
	 signal(SIGINT, &onintr);
      }
    #endif
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
  tracing_message(traceflag,"A5");
      if (ireturn ==1 && dcheck_flag ==0) 
      {
        ireturn = 3;
      }
      if (ireturn >= 3)
      {
         derch(f, x, g, n, ireturn);
         return;
      }
      if (ireturn == 1) goto call1;
      if (ireturn == 2) goto call2;
      fbest=1.e+100;
  tracing_message(traceflag,"A6");
      if (!h) h.allocate(n);
      w.initialize();
      alpha=1.0;
      ihflag=0;
     if (n==0) 
     { 
       cerr << "Error -- the number of active parameters"
         " fmin must be > 0\n";
       ad_exit(1);
     } 
  tracing_message(traceflag,"A7");
     if (x.indexmin() !=1) 
     { 
       cerr << "Error -- minimum valid index"
         " for independent_variables in fmin must be 1\n"
        << " it is " << x.indexmin() << "\n";
        ad_exit(1);
     } 
     if (x.size() <n) 
     { 
       cerr << "Error -- the size of the independent_variables"
        " which is " << x.size() << " must be >= " << n << "\n"
        << " the number of independent variables in fmin\n";
        ad_exit(1);
     } 
  tracing_message(traceflag,"A8");
     if (g.indexmin() !=1) 
     { 
       cerr << "Error -- minimum valid index"
         " for the gradient vector in fmin must be 1\n"
        << " it is " << g.indexmin() << "\n";
        ad_exit(1);
     } 
     if (g.size() <n) 
     { 
       cerr << "Error -- the size of the gradient vector"
        " which is " << g.size() << " must be >=\n"
        << " the number of independent variables in fmin\n";
        ad_exit(1);
     } 
  tracing_message(traceflag,"A9");
     for (i=1; i<=n; i++)
           xx.elem(i)=x.elem(i); 
  tracing_message(traceflag,"A10");
      itn=0;
      icc=0;
       for (i=1; i< 11; i++)
          funval.elem(i)=0.;
  tracing_message(traceflag,"A11");
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
  tracing_message(traceflag,"A12");
      h.elem(1,1) = 1;
      for (i=2; i<=n; i++)
      {
        for ( j=1; j<i; j++)
        {
           h.elem(i,j)=0;
        }
        h.elem(i,i)=1;
      }
  tracing_message(traceflag,"A13");
      dmin=h.elem(1,1);
      for ( i=2; i<=n; i++)
      {
         if(h.elem(i,i)<dmin)
            dmin=h.elem(i,i);
      }
      if (dmin <= 0.)
         goto label7020;
      if(dfn == 0.)
         z = 0.0; 
  tracing_message(traceflag,"A14");
      for (i=1; i<=n; i++)
      {
        xsave.elem(i)=x.elem(i);
        x.elem(i)=xx.elem(i);
      }
      ireturn=1;
  tracing_message(traceflag,"A15");
      if (h.disk_save())
      {
        cout << "starting hessian save" << endl;
        h.save();
        cout << "finished hessian save" << endl;
      }
  tracing_message(traceflag,"A16");
      return;
  call1:
  tracing_message(traceflag,"A17");
      if (h.disk_save())
      {
        cout << "starting hessian restore" << endl;
        h.restore();
        cout << "finished hessian restore" << endl;
      }
  tracing_message(traceflag,"A18");
      for (i=1; i<=n; i++)
      {
        x.elem(i)=xsave.elem(i);
      }
      ireturn=3;
  tracing_message(traceflag,"A19");
      {
      }
      for ( i=1; i<=n; i++)
         gbest.elem(i)=g.elem(i);
  tracing_message(traceflag,"A20");
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
#if defined(USE_DDOUBLE)
#undef double
      if(fmod(double(itn),double(iprint)) != 0)
         goto label21;
#define double dd_real
#else
      if(fmod(double(itn),double(iprint)) != 0)
         goto label21;
#endif
      if (llog) goto label7010;
#     if   !defined (__MSVC32__)  && !defined (__WAT32__) && !defined(linux)
        if (!scroll_flag) clrscr();
#     endif
label7003:
      if (iprint>0)
      {
	if (ad_printf) 
        {
          (*ad_printf)("%d variables; iteration %ld; function evaluation %ld", n, itn, ifn);
          if (pointer_to_phase)
          {
            (*ad_printf)("; phase %d", *pointer_to_phase);
          }
	  (*ad_printf)("\nFunction value %15.7le; maximum gradient component mag %12.4le\n",
#if defined(USE_DDOUBLE)
#undef double
              double(f), double(gmax));
#define double dd_real
#else
              f, gmax);
#endif
        }
      }
label7002:
      if(iprint>0) 
      {
        fmmdisp(x, g, n, this->scroll_flag,noprintx);
      }
label21 :
      itn=itn+1;
      for (i=1; i<=n; i++)
         x.elem(i)=xx.elem(i);
      w.elem(1)=-g.elem(1);
      pfmintime->get_elapsed_time_and_reset();
      for (i=2; i<=n; i++)
      {
	 i1=i-1;
         z=-g.elem(i);
         double * pd=&(h.elem(i,1));
         double * pw=&(w.elem(1));
         for (j=1; j<=i1; j++)
         {
            z-=*pd++ * *pw++;
         }
         w.elem(i)=z;
      }
      w.elem(is+n)=w.elem(n)/h.elem(n,n);
      {
        dvector tmp(1,n);
        tmp.initialize();
        for (i=1; i<=n1; i++)
        {
          j=i;
          double * pd=&(h.elem(n-j+1,n-1));
          double qd=w.elem(is+np-j);
          double * pt=&(tmp(1));
          for (int ii=1; ii<=n1; ii++)
          {
            *pt++ +=*pd-- * qd;
          }
          w.elem(is+n-i)=w.elem(n-i)/h.elem(n-i,n-i)-tmp(i);
        }
      }
      gs=0.0;
      for (i=1; i<=n; i++)
         gs+=w.elem(is+i)*g.elem(i);
      iexit=2;
      if(gs >= 0.0)
         goto label92;
      gso=gs;
      alpha=-2.0*df/gs;
      if(alpha > 1.0)
        alpha=1.0;
      df=f;
      tot=0.0;
label30:
      iexit=3;
      if (ialph) { goto label92; }
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
      if(quit_flag) goto label92;
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
      if (h.disk_save())
      {
        cout << "starting hessian save" << endl;
        h.save();
        cout << "finished hessian save" << endl;
      }
      return;
  call2:
      if (h.disk_save())
      {
        cout << "starting hessian restore" << endl;
        h.restore();
        cout << "finished hessian restore" << endl;
      }
      for (i=1; i<=n; i++)
      {
        x.elem(i)=xsave.elem(i);
        w.elem(i)=g.elem(i);
        g.elem(i)=gsave.elem(i);
      }
      fy = f;
      f = fsave;
      ireturn=-1;
      if (fy <= fbest)
      {
        fbest=fy;
        for (i=1; i<=n; i++)
        {
          x.elem(i)=xx.elem(i);
          gbest.elem(i)=w.elem(i);
        }
      }
      if (use_control_c==1)         
      {
#if (defined( __SUN__) && !defined(__GNU__)) || defined(UNIXKLUDGE) || defined(linux)
         if(ctlc_flag || ifn == dcheck_flag )
  #elif defined(__BORLANDC__)
         if ( kbhit() || ctlc_flag|| ifn == dcheck_flag )
  #else
         if ( kbhit() || ifn == dcheck_flag )
  #endif
         {
            int c=0;
            if (ifn != dcheck_flag)
            {
            #if !defined(__GNUDOS__)  || defined(UNIXKLUDGE)  || defined(linux) \
  	      || defined(__CYGWIN32__) || defined(__MINGW32__)
              c = toupper(getch());
            #else
              c = toupper(getxkey());
            #endif
            }
            else
              c='C';
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
       }
       if (quit_flag)
       {
	 if (quit_flag==1) quit_flag='Q';
	 if (quit_flag==2) quit_flag='N';
         goto label92;
       }
       icc+=1;
       if( icc >= 5)
          icc=0;
      ic++;
      if( ic >imax)
      {
         if (iprint>0)
         {
           if (ad_printf) (*ad_printf)("  ic > imax  in fminim is answer attained ?\n" );
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
      if(fy>f+fringe)
      {
         goto label40;
      }
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
      if (alpha == 0.)
      {
        ialph=1;
        return;
      }
      z=3.0*(f-fy)/alpha+gys+gs;
      zz=dafsqrt(z*z-gs*gys);
      z=1.0-(gys+zz-z)/(2.0*zz+gys-gs);
      if (fabs(fy-1.e+95) < 1.e-66)
      {
        alpha*=.001;
      }
      else
      {
        if (z>10.0) 
        {
          cout << "large z" << z << endl;
          z=10.0;
        }
        alpha=alpha*z;
      }
      if (alpha == 0.)
      {
         ialph=1;
        if (ialph)
        {
	   if (ad_printf) (*ad_printf)("\nFunction minimizer: Step size"
            "  too small -- ialph=1");
        }
         return;
      }
      goto label30;
label50:
      alpha+=tot;
      f=fy;
      df-=f;
      dgs=gys-gso;
      xxlink=1;
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
      xxlink=2;
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
      w.elem(iv+1)=w.elem(iu+1);
      pfmintime->get_elapsed_time_and_reset();
      for (i=2;i<=n;i++)
      {
         i1=i-1;
         z=w.elem(iu+i);
         double * pd=&(h.elem(i,1));
         double * pw=&(w.elem(iv+1));
         for (j=1;j<=i1;j++)
         {
           z-=*pd++ * *pw++;
         }
         w.elem(iv+i)=z;
      }
      pfmintime->get_elapsed_time_and_reset();
      for (i=1;i<=n;i++)
      {
         z=h.elem(i,i)+sig*w.elem(iv+i)*w.elem(iv+i);
         if(z <= 0.0)
            z=dmin;
         if(z<dmin)
            dmin=z;
         h.elem(i,i)=z;
         w.elem(ib+i)=w.elem(iv+i)*sig/z;
         sig-=w.elem(ib+i)*w.elem(ib+i)*z;
       }
      for (j=2;j<=n;j++)
      {
         double * pd=&(h.elem(j,1));
         double * qd=&(w.elem(iu+j));
         double * rd=&(w.elem(iv+1));
         for (i=1;i<j;i++)
         {
            *qd-=*pd * *rd++;
            *pd++ +=w.elem(ib+i)* *qd;
         }
      }
      if (xxlink == 1) goto label60;
      if (xxlink == 2) goto label65;
label90:
      for (i=1;i<=n;i++)
         g.elem(i)=w.elem(i);
label92:
      if (iprint>0)
      {
        if (ialph)
        {
	   if (ad_printf) (*ad_printf)("\nFunction minimizer: Step size too small -- ialph=1");
        }
        if (ihang == 1)
        {
	   if (ad_printf) (*ad_printf)("Function minimizer not making progress ... is minimum attained?\n");
#if defined(USE_DDOUBLE)
#undef double
           if (ad_printf) (*ad_printf)("Minimprove criterion = %12.4le\n",double(min_improve));
#define double dd_real
#else
           if (ad_printf) (*ad_printf)("Minimprove criterion = %12.4le\n",min_improve);
#endif
        }
      }
      if(iexit == 2)
      {
        if (iprint>0)
        {
          if (ad_printf) (*ad_printf)("*** grad transpose times delta x greater >= 0\n"
           " --- convergence critera may be too strict\n");
          ireturn=-1;
        }
      }
#     if defined (__MSVC32__)  && !defined (__WAT32__)
        if (scroll_flag == 0) clrscr();
#     endif
      if (maxfn_flag == 1)
      {
        if (iprint>0)
        {
	  if (ad_printf) (*ad_printf)("Maximum number of function evaluations exceeded");
        }
      }
      if (iprint>0)
      {
        if (quit_flag == 'Q')
          if (ad_printf) (*ad_printf)("User initiated interrupt");
      }
      if(iprint == 0) goto label777;
      if (ad_printf) (*ad_printf)("\n - final statistics:\n");
      if (ad_printf) (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
	      n, itn, ifn);
#if defined(USE_DDOUBLE)
#undef double
      if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
              double(f), double(gmax));
      if (ad_printf) (*ad_printf)("Exit code = %ld;  converg criter %12.4le\n",iexit,double(crit));
#define double dd_real
#else
      if (ad_printf) (*ad_printf)("Function value %12.4le; maximum gradient component mag %12.4le\n",
              f, gmax);
      if (ad_printf) (*ad_printf)("Exit code = %ld;  converg criter %12.4le\n",iexit,crit);
#endif
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
#     if defined (__MSVC32__)  && !defined (__WAT32__)
        if (!scroll_flag) clrscr();
#endif
        if (ad_printf) (*ad_printf)("\nInitial statistics: ");
      }
      goto label7003;
label7010:
   if (iprint>0)
   {
#     if defined (__MSVC32__)  && !defined (__WAT32__)
     if (!scroll_flag)  clrscr();
#endif
     if (ad_printf) (*ad_printf)("\nIntermediate statistics: ");
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
   double dafsqrt( double x )
   {
   if (x>0)
      return(sqrt(x));
   else
      return(0.);
   }
