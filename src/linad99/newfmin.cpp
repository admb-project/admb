/*
 * $Id$
 *
 * Author: Unknown
 * Copyright (c) 2009-2012 ADMB Foundation
 *
 * This file was originally written in FORTRAN II by an unknown author.
 * In the 1980s, it was ported to C and C++ and extensively modified by
 * David Fournier.
 *
 */
/**
  \file newfmin.cpp
  Source code for quasi-Newton function minimizer.
 */

#include <fvar.hpp>
#if defined(_WIN32)
  #include <windows.h>
  #include <admodel.h>
#endif
#if defined(__BORLANDC__)
  #include <signal.h>
#endif
#ifdef __ZTC__
  #include <conio.h>
#endif
#include <fvar.hpp>
extern int ctlc_flag;

#if defined (__WAT32__) || defined (_MSC_VER)
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
#endif
  #include <signal.h>
#ifdef __NDPX__
  #include <iostream.hxx>
#endif

#if defined (_MSC_VER)
  void __cdecl clrscr();
#else
  extern "C" void clrscr();
  #define getch getchar
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#ifdef _MSC_VER
BOOL CtrlHandler(DWORD fdwCtrlType)
{
  if (fdwCtrlType == CTRL_C_EVENT)
  {
    //Should exit if CTRL_C_EVENT occurs again.
    if (ctlc_flag) ad_exit(1);

    ctlc_flag = 1;
    if (ad_printf)
      (*ad_printf)("\npress q to quit or c to invoke derivative checker: ");
    return true;
  }
  return false;
}
#else
extern "C" void onintr(int k)
{
  signal(SIGINT, exit_handler);
  ctlc_flag = 1;
  if (ad_printf)
    (*ad_printf)("\npress q to quit or c to invoke derivative checker"
                 " or s to stop optimizing: ");
}
#endif

int* pointer_to_phase = 0;

double dafsqrt( double x );

/**
 * Description not yet available.
 * \param
 */
  void tracing_message(int _traceflag,const char *s)
  {
    if (_traceflag)
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
  void tracing_message(int _traceflag,const char *s,int *pn)
  {
    if (_traceflag)
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
  void tracing_message(int _traceflag,const char *s,double *pd)
  {
    if (_traceflag)
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
  void tracing_message(int _traceflag,const char *s,double d)
  {
    if (_traceflag)
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
extern int traceflag;
//#pragma warn -sig


/**
* Function fmin contains Quasi-Newton function minimizer with
* inexact line search using Wolfe conditions and
* BFGS correction formula for Hessian update.
*
* The algorithm consists of the following steps (in the order of execution):
* - Initial step with Hessian being an identity matrix (see call1)
* - Line search test for step length satisfying Wolfe conditions (beginning of
*   call2)
* - Line search backtracking and reducing alpha (label40) if the current
*   direction
*   is not a gradient descent one or the function value has increased
* - Hessian update (labels 50-70) once all conditions are satisfied to assure
*   its
*   positive-definiteness
* - Update of a vector of independent variables (label30)
*
* Convergence is detected if the maximal gradient component falls below small
* constant (see label20)
*
* Requires:
*    \param _f Value of function to be minimized.
*    \param _x Vector of independent variables.
*    \param _g Vector containing the partial derivatives of _f with respect to
*    each independent variable. The gradient vector returned by \ref gradcalc.
* Pre:
*    Some class member variables can be initialized by user prior to calling
*    this function.
*    These control variables may change the behavior of fmin, they are:
*        maxfn  (maximal number of function evaluations, after which
*                minimization stops)
*        crit   (convergence criterion constant)
*        imax   (maximal number of function evaluations within one linear search*                before to stop)
*        iprint (flag to allow (=1) or supress (=0) printing intermediate
*                statistics
*        min_improve (stop after 10 iterations with overall function decrease
*                     less than this value)
*    The default values can be found in function set_defaults of class
*    fmm_control
* Modifies:
*    The Hessian matrix (and not its inverse) h
* Returns (via parameter vector x):
*    A vector x after a step of linear search in the direction of gradient
*    descent
\ingroup FMM
*/
void fmm::fmin(const double& _f, const dvector &_x, const dvector& _g)
{
  if (log_values_switch)
  {
    print_values(_f,_x,_g);
  }

#ifdef DEBUG
  adtimer fmintime;
#endif

  tracing_message(traceflag,"A3");

  /* Remember gradient and function values
     resulted from previous function evaluation */
  dvector& g=(dvector&) _g;
  double& f=(double&) _f;

  /* Create local vector x as a pointer to the argument vector _x */
  independent_variables& x= (independent_variables&) _x;
    #ifdef DIAG
      cout << "On entry to fmin: " << *this << endl;
    #endif
  tracing_message(traceflag,"A4");

#ifdef _MSC_VER
  SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
#else
  /* Check the value of control variable ireturn:
        -1 (exit status)
         0 (initialization of function minimizer)
         1 (call1 - x update and convergence check)
         2 (call2 - line search and Hessian update)
         >=3 (derivative check)
  */
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
         /* Entering derivative check */
         derch(f, x, g, n, ireturn);
         return;
      }
      if (ireturn == 1) goto call1;
      if (ireturn == 2) goto call2;

     /* we are here because ireturn=0
        Start initializing function minimizer variables */
      fbest=1.e+100;
  tracing_message(traceflag,"A6");

      /* allocate Hessian
         h - object of class dfsdmat, the memory is allocated
             only for elements of lower triagonal matrix */
      if (!h) h.allocate(n);

      /* initialize w, the dvector of size 4*n:
         w(1,n) contains gradient vector in the point x_new = x_old + alpha*p_k
         w(n+1,2n) contains direction of linear search, i.e. transpose(p_k)
         w(2n+1,4n) are used for Hessian updating terms */
      w.initialize();

      /* alpha - the Newton step size */
      alpha=1.0; /* full Newton step at the beginning */
      ihflag=0;

      /* validity check for dimensions and indexing of
         independent vector and gradient vector
         Note, this function will work correctly only if
         indices start at 1  */
     if (n <= 0)
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
     if (x.size() < static_cast<unsigned int>(n))
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
     if (g.size() < static_cast<unsigned int>(n))
     {
       cerr << "Error -- the size of the gradient vector"
        " which is " << g.size() << " must be >=\n"
        << " the number of independent variables in fmin\n";
        ad_exit(1);
     }
     /* end of validity check */
  tracing_message(traceflag,"A9");

     /* xx is reserved for the updated values of independent variables,
        at the moment put the current values */
     for (i=1; i<=n; i++)
           xx.elem(i)=x.elem(i);
  tracing_message(traceflag,"A10");

      /* itn - iteration counter */
      itn=0;
      /* icc - obsolete calls counter? */
      icc=0;

       /* initialize funval vector,
          it will contain last 10 function values (10-th is the most recent)
          needed to stop minimization in case if f(1)-f(10)<min_improve  */
       for (i=1; i< 11; i++)
          funval.elem(i)=0.;
  tracing_message(traceflag,"A11");
      ihang = 0;  /* flag, =1 when function minimizer is not making progress */
      llog=1;
      np=n+1;
      n1=n-1;
      nn=n*np/2;
      is=n;
      iu=n;
      iv=n+n;
      ib=iv+n;
      iexit=0;    /* exit code */
  tracing_message(traceflag,"A12");

      /* Initialize hessian to the unit matrix */
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

      /* dmin - minimal element of hessian used to
         verify its positive definiteness */
      dmin=h.elem(1,1);
      for ( i=2; i<=n; i++)
      {
         if(h.elem(i,i)<dmin)
            dmin=h.elem(i,i);
      }
      if (dmin <= 0.)    /* hessian is not positive definite? */
         goto label7020; /* exit */
      if(dfn == 0.)
         z = 0.0;
  tracing_message(traceflag,"A14");
      for (i=1; i<=n; i++)
      {
        xsave.elem(i)=x.elem(i);
        x.elem(i)=xx.elem(i);
      }
      ireturn=1; /* upon next entry will go to call1 */
  tracing_message(traceflag,"A15");
      if (h.disk_save())
      {
        cout << "starting hessian save" << endl;
        h.save();
        cout << "finished hessian save" << endl;
      }
  tracing_message(traceflag,"A16");
      return;
      /* End of initialization */
  call1: /* first line search step and x update */
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
label20: /* check for convergence */
      ic=0; /* counter for number of calls */
      iconv = 1; /* convergence flag: 1 - convergence, 2 - not yet */
      for ( i=1; i<=9; i++)
         funval.elem(i)= funval.elem(i+1);
      funval.elem(10) = f;
      /* check if function value is improving */
      if ( itn>15 && fabs( funval.elem(1)-funval.elem(10))< min_improve )
         ihang = 1;
      gmax = 0;
      /* satisfy convergence criterion? */
      for ( i=1; i<=n; i++)
      {
        if(fabs(g.elem(i)) > crit) iconv = 2;
        if(fabs(g.elem(i)) > fabs(gmax) ) gmax = g.elem(i);
      }
      /* exit if either convergence or no improvement has been achieved
         during last 10 iterations */
      if( iconv == 1 || ihang == 1)
      {
         ireturn=-1;
         goto label92;
      }
      /* otherwise proceed to the Newton step (label21) */
      if(iprint == 0)
         goto label21; /* without printing */
      if(itn == 0)
         goto label7000; /* printing Initial statistics first */
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
#if defined (_MSC_VER) && !defined (__WAT32__)
        if (!scroll_flag) clrscr();
#endif
label7003: /* Printing table header */
      if (iprint>0)
      {
        if (ad_printf)
        {
          (*ad_printf)("%d variables; iteration %ld; function evaluation %ld",
           n, itn, ifn);
          if (pointer_to_phase)
          {
            (*ad_printf)("; phase %d", *pointer_to_phase);
          }
          (*ad_printf)(
           "\nFunction value %15.7le; maximum gradient component mag %12.4le\n",
#if defined(USE_DDOUBLE)
  #undef double
              double(f), double(gmax));
  #define double dd_real
#else
              f, gmax);
#endif
        }
      }
/*label7002:*/
      /* Printing Statistics table */
      if(iprint>0)
      {
        fmmdisp(x, g, n, this->scroll_flag,noprintx);
      }
label21 : /* Calculating Newton step */
      /* found good search direction, increment iteration number */
      itn=itn+1;
      for (i=1; i<=n; i++)
         x.elem(i)=xx.elem(i);
      w.elem(1)=-g.elem(1);

#ifdef DEBUG
      cout << __FILE__ << ':' << __LINE__ << ' '
	   << fmintime.get_elapsed_time_and_reset() << endl;
#endif

      /* solving system of linear equations H_(k+1) * (x_(k+1)-x(k)) = -g_k
         to get next search direction
         p_k = (x_(k+1)-x(k)) = - inv(H_(k+1)) * g_k */
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
      }/* w(n+1,2n) now contains search direction
          with current Hessian approximation */
      gs=0.0;
      for (i=1; i<=n; i++)
         gs+=w.elem(is+i)*g.elem(i);/* gs = -inv(H_k)*g_k*df(x_k+alpha_k*p_k) */
      iexit=2;
      if(gs >= 0.0)
         goto label92; /* exit with error */
      gso=gs;
      /* compute new step length 0 < alpha <= 1 */
      alpha=-2.0*df/gs;
      if(alpha > 1.0)
        alpha=1.0;
      df=f;
      tot=0.0;
label30: /* Taking a step, updating x */
      iexit=3;
      if (ialph) { goto label92; } /* exit if step size too small */
      /* exit if number of function evaluations exceeded maxfn */
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
        /* w(n+1,2n) has the next direction to go */
        z=alpha*w.elem(is+i);
        /* new independent vector values */
        xx.elem(i)+=z;
      }
      for (i=1; i<=n; i++)
      { /* save previous values and update x return value */
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
      return; // end of call1
  call2: /* Line search and Hessian update */
      if (h.disk_save())
      {
        cout << "starting hessian restore" << endl;
        h.restore();
        cout << "finished hessian restore" << endl;
      }
      /* restore x_k, g(x_k) and g(x_k+alpha*p_k) */
      for (i=1; i<=n; i++)
      {
        x.elem(i)=xsave.elem(i); //x_k
        w.elem(i)=g.elem(i);     //g(x_k+alpha*p_k)
        g.elem(i)=gsave.elem(i); //g(x_k)
      }
      fy = f;
      f = fsave; /* now fy is a new function value, f is the old one */
      ireturn=-1;
      /* remember current best function value, gradient and parameter values */
      if (fy <= fbest)
      {
        fbest=fy;
        for (i=1; i<=n; i++)
        {
          x.elem(i)=xx.elem(i);
          gbest.elem(i)=w.elem(i);
        }
      }
      /* what to do if CTRL-C keys were pressed */
      if (use_control_c==1)
      {
#if defined(__BORLANDC__)
         if ( kbhit() || ctlc_flag|| ifn == dcheck_flag )
#elif defined(_MSC_VER)
         //if ( kbhit() || ifn == dcheck_flag )
         if ( _kbhit() || ctlc_flag || ifn == dcheck_flag )
#else
         if(ctlc_flag || ifn == dcheck_flag )
#endif
         {
            int c=0;
            if (ifn != dcheck_flag)
            {
            #if defined(__DJGPP__)
              c = toupper(getxkey());
            #else
              c = toupper(getch());
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
            else if(c=='S')
            {
              //set convergence criteria to something high to stop now
              crit=100000.0;
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
      /* Otherwise, continue */
       /* Note, icc seems to be unused */
       icc+=1;
       if( icc >= 5)
          icc=0;
      /* ic - counter of calls without x update */
      ic++;
      if( ic >imax)
      {
         if (iprint>0)
         {
           if (ad_printf)
             (*ad_printf)("  ic > imax  in fminim is answer attained ?\n");
           fmmdisp(x, g, n, this->scroll_flag,noprintx);
         }
         ihflag=1;
         ihang=1;
         goto label92;
      }
      /* new function value was passed to fmin, will increment ifn */
      ifn++;

      gys=0.0;

      /* gys = transpose(p_k) * df(x_k+alpha_k*p_k) */
      for (i=1; i<= n; i++)
         gys+=w.elem(i)*w.elem(is+i);

      /* bad step; unless modified by the user, fringe default = 0 */
      if(fy>f+fringe)
      {
         goto label40; /* backtrack */
      }
      /* Otherwise verify if the search step length satisfies
         strong Wolfe condition */
      if(fabs(gys/gso)<=.9)
         goto label50; /* proceed to Hessian update */
/* or slightly modified constant in Wolfe condition for the number of
 calls > 4 */
      if(fabs(gys/gso)<=.95 && ic > 4)
         goto label50; /* proceed to Hessian update */
      if(gys>0.0) /* not a descent direction */
         goto label40; /* backtrack */
      tot+=alpha;
      z=10.0;
      if(gs<gys)
         z=gys/(gs-gys);
      if(z>10.0)
         z=10.0;
      /* increase step length */
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
      goto label30; /* update x with new alpha */
label40: /* new step is not acceptable, stepping back and
            start backtracking along the Newton direction
            trying a smaller value of alpha */
      for (i=1;i<=n;i++)
         xx.elem(i)-=alpha*w.elem(is+i);
      if (alpha == 0.)
      {
        ialph=1;
        return;
      }
      /* compute new alpha */
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
      goto label30; /* update x with new alpha */
label50: /* compute Hessian updating terms */
      alpha+=tot;
      f=fy;
      df-=f;
      dgs=gys-gso;
      xxlink=1;
      if(dgs+alpha*gso>0.0)
         goto label52;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=w.elem(i)-g.elem(i);
      /* now w(n+1,2n) = df(x_k+alpha_k*p_k)-df(x_k) */
      sig=1.0/(alpha*dgs);
      goto label70;
label52: /* compute Hessian updating terms */
      zz=alpha/(dgs-alpha*gso);
      z=dgs*zz-1.0;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=z*g.elem(i)+w.elem(i);
      sig=1.0/(zz*dgs*dgs);
      goto label70;
label60: /* compute Hessian updating terms */
      xxlink=2;
      for (i=1;i<=n;i++)
         w.elem(iu+i)=g.elem(i);
      if(dgs+alpha*gso>0.0)
         goto label62;
      sig=1.0/gso;
      goto  label70;
label62: /* compute Hessian updating terms */
      sig=-zz;
      goto label70;
label65: /* save in g the gradient df(x_k+alpha*p_k) */
      for (i=1;i<=n;i++)
         g.elem(i)=w.elem(i);
      goto  label20; //convergence check
label70:  // Hessian update
      w.elem(iv+1)=w.elem(iu+1);

#ifdef DEBUG
      cout << __FILE__ << ':' << __LINE__ << ' '
	   << fmintime.get_elapsed_time_and_reset() << endl;
#endif

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

#ifdef DEBUG
      cout << __FILE__ << ':' << __LINE__ << ' '
	   << fmintime.get_elapsed_time_and_reset() << endl;
#endif

      for (i=1;i<=n;i++)
      {  /* BFGS updating formula */
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
/*label90:*/
      for (i=1;i<=n;i++)
         g.elem(i)=w.elem(i);
label92: /* Exit with error */
      if (iprint>0)
      {
        if (ialph)
        {
          if (ad_printf)
           (*ad_printf)("\nFunction minimizer: Step size too small -- ialph=1");
        }
        if (ihang == 1)
        {
          if (ad_printf)
            (*ad_printf)(
           "Function minimizer not making progress ... is minimum attained?\n");
#if defined(USE_DDOUBLE)
#undef double
           if (ad_printf)
           (*ad_printf)("Minimprove criterion = %12.4le\n",double(min_improve));
#define double dd_real
#else
           if (ad_printf)
             (*ad_printf)("Minimprove criterion = %12.4le\n",min_improve);
#endif
        }
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
#if defined (_MSC_VER) && !defined (__WAT32__)
        if (scroll_flag == 0) clrscr();
#endif
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
        if (quit_flag == 'Q')
          if (ad_printf) (*ad_printf)("User initiated interrupt");
      }
      if(iprint == 0) goto label777;
      if (ad_printf) (*ad_printf)("\n - final statistics:\n");
      if (ad_printf)
        (*ad_printf)("%d variables; iteration %ld; function evaluation %ld\n",
                       n, itn, ifn);
#if defined(USE_DDOUBLE)
#undef double
      if (ad_printf)
        (*ad_printf)(
             "Function value %12.4le; maximum gradient component mag %12.4le\n",
             double(f), double(gmax));
      if (ad_printf)
        (*ad_printf)(
          "Exit code = %ld;  converg criter %12.4le\n",iexit,double(crit));
#define double dd_real
#else
      if (ad_printf)
        (*ad_printf)(
          "Function value %12.4le; maximum gradient component mag %12.4le\n",
          f, gmax);
      if (ad_printf)
        (*ad_printf)(
          "Exit code = %ld;  converg criter %12.4le\n",iexit,crit);
#endif
      fmmdisp(x, g, n, this->scroll_flag,noprintx);
label777: /* Printing final Hessian approximation */
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
label7000:/* Printing Initial statistics */
      if (iprint>0)
      {
#if defined (_MSC_VER) && !defined (__WAT32__)
        if (!scroll_flag) clrscr();
#endif
        if (ad_printf) (*ad_printf)("\nInitial statistics: ");
      }
      goto label7003;
label7010:/* Printing Intermediate statistics */
   if (iprint>0)
   {
#if defined (_MSC_VER) && !defined (__WAT32__)
     if (!scroll_flag) clrscr();
#endif
     if (ad_printf) (*ad_printf)("\nIntermediate statistics: ");
   }
   llog=0;
   goto label7003;
label7020:/* Exis because Hessian is not positive definite */
  if (iprint > 0)
  {
    if (ad_printf) (*ad_printf)("*** hessian not positive definite\n");
  }
#ifdef __ZTC__
  if (ireturn <= 0)
  {
    disp_close();
  }
#endif
}
/**
Robust square root.
\param x Double precision argument \f$x; x \ge 0\f$.
\return \f$\sqrt{x}\f$ for \f$x>0\f$, 0 otherwise.
*/
double dafsqrt(double x)
{
  return x > 0 ? sqrt(x) : 0.0;
}
