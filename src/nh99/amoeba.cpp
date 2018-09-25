/**
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB foundation
 */
#include <admodel.h>
#include <math.h>
#define NRANSI
//#include "nrutil.h"
#define NMAX 5000

/** \def GET_PSUM
  Computes psum.
*/
#define GET_PSUM \
          for (j=1;j<=ndim;j++) {\
          for (sum=0.0,i=1;i<=mpts;i++) sum += p[i][j];\
          psum[j]=sum;}

/** \def SWAP(a,b)
  Reverses a and b
*/
#define SWAP(a,b) {swap=(a);(a)=(b);(b)=swap;}


/** Nelder-Mead simplex alogrithm.
  \param _p Matrix
  \param _y Vector
  \param ndim Integer
  \param ftol Double
  \param nfunk Integer

  \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 10

  \deprecated User should use the neldmead function
*/
void function_minimizer::adamoeba(const dmatrix& _p, const dvector& _y,
  int ndim, double ftol,int nfunk)
{
  dmatrix& p=(dmatrix&) _p;
  dvector& y=(dvector&) _y;
  int i,ihi,ilo,inhi,j,mpts=ndim+1;
  double rtol,sum,swap,ysave,ytry;

  dvector psum(1,ndim);
  nfunk=0;
  GET_PSUM
  for (;;) {
    ilo=1;
    ihi = y[1]>y[2] ? (inhi=2,1) : (inhi=1,2);
    for (i=1;i<=mpts;i++) {
      if (y[i] <= y[ilo]) ilo=i;
      if (y[i] > y[ihi]) {
        inhi=ihi;
        ihi=i;
      } else if (y[i] > y[inhi] && i != ihi) inhi=i;
    }
    rtol=2.0*fabs(y[ihi]-y[ilo])/(fabs(y[ihi])+fabs(y[ilo]));
    if (rtol < ftol) {
      SWAP(y[1],y[ilo])
      for (i=1;i<=ndim;i++) SWAP(p[1][i],p[ilo][i])
      break;
    }
    if (nfunk >= NMAX)
    {
      cerr << "NMAX exceeded" << endl;
    }
    nfunk += 2;
    ytry=amxxx(p,y,psum,ndim,ihi,-1.0);
    if (ytry <= y[ilo])
      ytry=amxxx(p,y,psum,ndim,ihi,2.0);
    else if (ytry >= y[inhi]) {
      ysave=y[ihi];
      ytry=amxxx(p,y,psum,ndim,ihi,0.5);
      if (ytry >= ysave) {
        for (i=1;i<=mpts;i++) {
          if (i != ilo) {
            for (j=1;j<=ndim;j++)
              p[i][j]=psum[j]=0.5*(p[i][j]+p[ilo][j]);

            dvariable vf=0.0;
            vf=initial_params::reset(dvar_vector(psum));
            *objective_function_value::pobjfun=0.0;
            userfunction();
            vf+=*objective_function_value::pobjfun;

            y[i]=value(vf);
          }
        }
        nfunk += ndim;
        GET_PSUM
      }
    } else --(nfunk);
  }
}
#undef SWAP
#undef GET_PSUM
#undef NMAX
#undef NRANSI
#define NRANSI

/**
 * Description not yet available.
 * \param
 */
double function_minimizer::amxxx(const dmatrix& _p, const dvector& _y,
  const dvector& _psum, int ndim, int ihi, double fac)
{
  dmatrix& p=(dmatrix&) _p;
  dvector& y=(dvector&) _y;
  dvector& psum=(dvector&) _psum;
  int j;
  double fac1,fac2,ytry;

  dvector ptry(1,ndim);
  fac1=(1.0-fac)/ndim;
  fac2=fac1-fac;
  for (j=1;j<=ndim;j++) ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;

  dvariable vf=0.0;
  vf=initial_params::reset(dvar_vector(ptry));
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  ytry=value(vf);

  if (ytry < y[ihi]) {
    y[ihi]=ytry;
    for (j=1;j<=ndim;j++) {
      psum[j] += ptry[j]-p[ihi][j];
      p[ihi][j]=ptry[j];
      }
  }
  return ytry;
}
#undef NRANSI

/** Nelder-Mead simplex alogrithm.
  \param n Integer
  \param _start Vector
  \param _xmin Vector
  \param ynewlo Double
  \param reqmin Double
  \param delta Double
  \param icount Integer pointer
  \param numres Integer pointer
  \param ifault Integer pointer
*/
void function_minimizer::neldmead(int n, dvector& _start, dvector& _xmin,
  double *ynewlo, double reqmin, double delta,int *icount, int *numres,
  int *ifault)
//
//  Purpose:
//
//    NELMIN minimizes a function using the Nelder-Mead algorithm.
//
//  Discussion:
//
//    This routine seeks the minimum value of a user-specified function.
//
//    Simplex function minimisation procedure due to Nelder+Mead(1965),
//    as implemented by O'Neill(1971, Appl.Statist. 20, 338-45), with
//    subsequent comments by Chambers+Ertel(1974, 23, 250-1), Benyon(1976,
//    25, 97) and Hill(1978, 27, 380-2)
//
//    This routine does not include a termination test using the
//    fitting of a quadratic surface.
//
//  Modified:
//
//    October 2010 by Derek Seiple
//
//  Author:
//
//    FORTRAN77 version by R ONeill
//    C++ version by John Burkardt
//
//  Reference:
//
//    John Nelder, Roger Mead,
//    A simplex method for function minimization,
//    Computer Journal,
//    Volume 7, 1965, pages 308-313.
//
//    R ONeill,
//    Algorithm AS 47:
//    Function Minimization Using a Simplex Procedure,
//    Applied Statistics,
//    Volume 20, Number 3, 1971, pages 338-345.
//
//  Parameters:
//
//    Input, int N, the number of variables.
//
//    Input/output, double START[N].  On input, a starting point
//    for the iteration.  On output, this data may have been overwritten.
//
//    Output, double XMIN[N], the coordinates of the point which
//    is estimated to minimize the function.
//
//    Output, double YNEWLO, the minimum value of the function.
//
//    Input, double REQMIN, the terminating limit for the variance
//    of function values.
//
//    Input, int KONVGE, the convergence check is carried out
//    every KONVGE iterations.
//
//    Input, int KCOUNT, the maximum number of function
//    evaluations.
//
//    Output, int *ICOUNT, the number of function evaluations
//    used.
//
//    Output, int *NUMRES, the number of restarts.
//
//    Output, int *IFAULT, error indicator.
//    0, no errors detected.
//    1, REQMIN, N, or KONVGE has an illegal value.
//    2, iteration terminated because KCOUNT was exceeded without convergence.
//
{
  dvector& start=(dvector&) _start;
  dvector& xmin=(dvector&) _xmin;
  int slb = start.indexmin();
  int xlb = xmin.indexmin();
  start.shift(0);
  xmin.shift(0);

  int i;
  dvector step(0,n-1);
  for(i=0;i<n;i++)
  {
    step(i)=delta;
  }

  int konvge = 10;
  int kcount = 5000;
  double ccoeff = 0.5;
  double del;
  double dn;
  double dnn;
  double ecoeff = 2.0;
  double eps = 0.001;

  int ihi;
  int ilo;
  int j;
  int jcount;
  int l;
  int nn;
  double rcoeff = 1.0;
  double rq;
  double x;
  double y2star;
  double ylo;
  double ystar;
  double z;

  // Check the input parameters.
  if ( reqmin <= 0.0 )
  {
    *ifault = 1;
    return;
  }

  if ( n < 1 )
  {
    *ifault = 1;
    return;
  }

  if ( konvge < 1 )
  {
    *ifault = 1;
    return;
  }

  dvector p(0,n*(n+1)-1);
  dvector pstar(0,n-1);
  dvector p2star(0,n-1);
  dvector pbar(0,n-1);
  dvector y(0,n);

  *icount = 0;
  *numres = 0;

  jcount = konvge;
  dn = ( double ) ( n );
  nn = n + 1;
  dnn = ( double ) ( nn );
  del = 1.0;
  rq = reqmin * dn;

  // Initial or restarted loop.
  dvariable vf=0.0;

  for ( ; ; )
  {
    for ( i = 0; i < n; i++ )
    {
      p[i+n*n] = start[i];
    }
    start.shift(1);
    vf=0.0;
    vf=initial_params::reset(dvar_vector(start));
    *objective_function_value::pobjfun=0.0;
    userfunction();
    vf+=*objective_function_value::pobjfun;
    y[n] = value(vf);
    start.shift(0);

    *icount = *icount + 1;

    for ( j = 0; j < n; j++ )
    {
      x = start[j];
      start[j] = start[j] + step[j] * del;
      for ( i = 0; i < n; i++ )
      {
        p[i+j*n] = start[i];
      }
      start.shift(1);
      vf=0.0;
      vf=initial_params::reset(dvar_vector(start));
      *objective_function_value::pobjfun=0.0;
      userfunction();
      vf+=*objective_function_value::pobjfun;
      y[j]=value(vf);
      start.shift(0);

      *icount = *icount + 1;
      start[j] = x;
    }
    // The simplex construction is complete.

    // Find highest and lowest Y values.  YNEWLO = Y(IHI) indicates
    // the vertex of the simplex to be replaced.
    ylo = y[0];
    ilo = 0;

    for ( i = 1; i < nn; i++ )
    {
      if ( y[i] < ylo )
      {
        ylo = y[i];
        ilo = i;
      }
    }

    // Inner loop.
    for ( ; ; )
    {
      if ( kcount <= *icount )
      {
        break;
      }
      *ynewlo = y[0];
      ihi = 0;

      for ( i = 1; i < nn; i++ )
      {
        if ( *ynewlo < y[i] )
        {
          *ynewlo = y[i];
          ihi = i;
        }
      }

      // Calculate PBAR, the centroid of the simplex vertices
      // excepting the vertex with Y value YNEWLO.
      for ( i = 0; i < n; i++ )
      {
        z = 0.0;
        for ( j = 0; j < nn; j++ )
        {
          z = z + p[i+j*n];
        }
        z = z - p[i+ihi*n];
        pbar[i] = z / dn;
      }

      // Reflection through the centroid.
      for ( i = 0; i < n; i++ )
      {
        pstar[i] = pbar[i] + rcoeff * ( pbar[i] - p[i+ihi*n] );
      }
      pstar.shift(1);
      vf=0.0;
      vf=initial_params::reset(dvar_vector(pstar));
      *objective_function_value::pobjfun=0.0;
      userfunction();
      vf+=*objective_function_value::pobjfun;
      ystar = value(vf);
      pstar.shift(0);

      *icount = *icount + 1;

      // Successful reflection, so extension.
      if ( ystar < ylo )
      {
        for ( i = 0; i < n; i++ )
        {
          p2star[i] = pbar[i] + ecoeff * ( pstar[i] - pbar[i] );
        }
        p2star.shift(1);
        vf=0.0;
        vf=initial_params::reset(dvar_vector(p2star));
        *objective_function_value::pobjfun=0.0;
        userfunction();
        vf+=*objective_function_value::pobjfun;
        y2star = value(vf);
        p2star.shift(0);

        *icount = *icount + 1;

        // Check extension.
        if ( ystar < y2star )
        {
          for ( i = 0; i < n; i++ )
          {
            p[i+ihi*n] = pstar[i];
          }
          y[ihi] = ystar;
        }

        // Retain extension or contraction.
        else
        {
          for ( i = 0; i < n; i++ )
          {
            p[i+ihi*n] = p2star[i];
          }
          y[ihi] = y2star;
        }
      }

      // No extension.
      else
      {
        l = 0;
        for ( i = 0; i < nn; i++ )
        {
          if ( ystar < y[i] )
          {
            l = l + 1;
          }
        }

        if ( 1 < l )
        {
          for ( i = 0; i < n; i++ )
          {
            p[i+ihi*n] = pstar[i];
          }
          y[ihi] = ystar;
        }

        // Contraction on the Y(IHI) side of the centroid.
        else if ( l == 0 )
        {
          for ( i = 0; i < n; i++ )
          {
            p2star[i] = pbar[i] + ccoeff * ( p[i+ihi*n] - pbar[i] );
          }
          p2star.shift(1);
          vf=0.0;
          vf=initial_params::reset(dvar_vector(p2star));
          *objective_function_value::pobjfun=0.0;
          userfunction();
          vf+=*objective_function_value::pobjfun;
          y2star = value(vf);
          p2star.shift(0);

          *icount = *icount + 1;

          // Contract the whole simplex.
          if ( y[ihi] < y2star )
          {
            for ( j = 0; j < nn; j++ )
            {
              for ( i = 0; i < n; i++ )
              {
                p[i+j*n] = ( p[i+j*n] + p[i+ilo*n] ) * 0.5;
                xmin[i] = p[i+j*n];
              }
              xmin.shift(1);
              vf=0.0;
              vf=initial_params::reset(dvar_vector(xmin));
              *objective_function_value::pobjfun=0.0;
              userfunction();
              vf+=*objective_function_value::pobjfun;
              y[j] = value(vf);
              xmin.shift(0);

              *icount = *icount + 1;
            }
            ylo = y[0];
            ilo = 0;

            for ( i = 1; i < nn; i++ )
            {
              if ( y[i] < ylo )
              {
                ylo = y[i];
                ilo = i;
              }
            }
            continue;
          }

          //  Retain contraction.
          else
          {
            for ( i = 0; i < n; i++ )
            {
              p[i+ihi*n] = p2star[i];
            }
            y[ihi] = y2star;
          }
        }

        // Contraction on the reflection side of the centroid.
        else if ( l == 1 )
        {
          for ( i = 0; i < n; i++ )
          {
            p2star[i] = pbar[i] + ccoeff * ( pstar[i] - pbar[i] );
          }
          p2star.shift(1);
          vf=0.0;
          vf=initial_params::reset(dvar_vector(p2star));
          *objective_function_value::pobjfun=0.0;
          userfunction();
          vf+=*objective_function_value::pobjfun;
          y2star = value(vf);
          p2star.shift(0);

          *icount = *icount + 1;

          // Retain reflection?
          if ( y2star <= ystar )
          {
            for ( i = 0; i < n; i++ )
            {
              p[i+ihi*n] = p2star[i];
            }
            y[ihi] = y2star;
          }
          else
          {
            for ( i = 0; i < n; i++ )
            {
              p[i+ihi*n] = pstar[i];
            }
            y[ihi] = ystar;
          }
        }
      }

      // Check if YLO improved.
      if ( y[ihi] < ylo )
      {
        ylo = y[ihi];
        ilo = ihi;
      }
      jcount = jcount - 1;

      if ( 0 < jcount )
      {
        continue;
      }

      // Check to see if minimum reached.
      if ( *icount <= kcount )
      {
        jcount = konvge;

        z = 0.0;
        for ( i = 0; i < nn; i++ )
        {
          z = z + y[i];
        }
        x = z / dnn;

        z = 0.0;
        for ( i = 0; i < nn; i++ )
        {
          z = z + pow ( y[i] - x, 2 );
        }

        if ( z <= rq )
        {
          break;
        }
      }
    }

    // Factorial tests to check that YNEWLO is a local minimum.
    for ( i = 0; i < n; i++ )
    {
      xmin[i] = p[i+ilo*n];
    }
    *ynewlo = y[ilo];

    if ( kcount < *icount )
    {
      *ifault = 2;
      break;
    }

    *ifault = 0;

    for ( i = 0; i < n; i++ )
    {
      del = step[i] * eps;
      xmin[i] = xmin[i] + del;
      xmin.shift(1);
      vf=0.0;
      vf=initial_params::reset(dvar_vector(xmin));
      *objective_function_value::pobjfun=0.0;
      userfunction();
      vf+=*objective_function_value::pobjfun;
      z = value(vf);
      xmin.shift(0);

      *icount = *icount + 1;
      if ( z < *ynewlo )
      {
        *ifault = 2;
        break;
      }
      xmin[i] = xmin[i] - del - del;
      xmin.shift(1);
      vf=0.0;
      vf=initial_params::reset(dvar_vector(xmin));
      *objective_function_value::pobjfun=0.0;
      userfunction();
      vf+=*objective_function_value::pobjfun;
      z = value(vf);
      xmin.shift(0);

      *icount = *icount + 1;
      if ( z < *ynewlo )
      {
        *ifault = 2;
        break;
      }
      xmin[i] = xmin[i] + del;
    }

    if ( *ifault == 0 )
    {
      break;
    }

    // Restart the procedure.
    for ( i = 0; i < n; i++ )
    {
      start[i] = xmin[i];
    }
    del = eps;
    *numres = *numres + 1;
  }

  start.shift(slb);
  xmin.shift(xlb);

  return;
}
