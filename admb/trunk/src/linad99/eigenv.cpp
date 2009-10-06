/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB foundation
 */

/** \def EIGEN_VECTORS
   Causes Eigenvectors to be computed
*/
#define EIGEN_VECTORS

#include <fvar.hpp>

#if !defined(EIGEN_VECTORS)
#  define EIGEN_VECTORS
#endif

#ifdef EIGEN_VECTORS
  void tri_dagv(BOR_CONST dmatrix& m,BOR_CONST dvector& d,BOR_CONST dvector& e);
#else
  void tri_dag(BOR_CONST dmatrix& m,BOR_CONST dvector& d,BOR_CONST dvector& e);
#endif
#ifdef EIGEN_VECTORS
  void get_eigenv(const dvector& d,const dvector& e,const dmatrix& z);
#else
  void get_eigen(BOR_CONST dvector& d,BOR_CONST dvector& e,BOR_CONST dmatrix& z);
#endif

/** Eigenvectors.
    Computes eigenvectors of a real square matrix. Input matrix is symmetrized.
    \param m Real square matrix.
    \return Matrix of eigenvectors.
*/
dmatrix eigenvectors(_CONST dmatrix& m)  //,_CONST dvector& diag)
{
  if (m.rowsize()!=m.colsize())
  {
    cerr << "Error -- non square matrix passed to dvector"
           " eigen(_CONST dmatrix& m)" << endl;
    ad_exit(1);
  }

  dmatrix m1=symmetrize(m);
  int n=m1.rowsize();
  int imin=m.colmin();
  m1.colshift(1);     // set minimum column and row indices to 1
  m1.rowshift(1);
  dvector diag(1,n);
  dvector off_diag(1,n);

  #ifdef EIGEN_VECTORS
    tri_dagv(m1,diag,off_diag);
  #else
    tri_dag(m1,diag,off_diag);
  #endif

  #ifdef EIGEN_VECTORS
    get_eigenv(diag,off_diag,m1); // eigenvalues are returned in diag
  #else
    get_eigen(diag,off_diag,m1); // eigenvalues are returned in diag
  #endif
  return m1;
}

/** Eigenvectors.
    Computes eigenvectors of a real square matrix. Input matrix is symmetrized.
    \param m Real square matrix.
    \param _diag
    \return Matrix of eigenvectors.
*/
dmatrix eigenvectors(_CONST dmatrix& m,BOR_CONST dvector& _diag)  //,_CONST dvector& diag)
{
  ADUNCONST(dvector,diag)
  if (m.rowsize()!=m.colsize())
  {
    cerr << "Error -- non square matrix passed to dvector"
           " eigen(_CONST dmatrix& m)" << endl;
    ad_exit(1);
  }

  dmatrix m1=symmetrize(m);
  int n=m1.rowsize();
  int imin=m.colmin();
  m1.colshift(1);     // set minimum column and row indices to 1
  m1.rowshift(1);
  diag.shift(1);
  if (diag.size()!=m.rowsize())
  {
    cerr << "incompatible sizes in vector and matrix passed to"
          " dmatrix eigenvector routine" << endl;
  }
  dvector off_diag(1,n);

  #ifdef EIGEN_VECTORS
    tri_dagv(m1,diag,off_diag);
  #else
    tri_dag(m1,diag,off_diag);
  #endif

  #ifdef EIGEN_VECTORS
    get_eigenv(diag,off_diag,m1); // eigenvalues are returned in diag
  #else
    get_eigen(diag,off_diag,m1); // eigenvalues are returned in diag
  #endif
  return m1;
}


/** Householder transformation for eivenvector computation.
  \param _m Real, symmetric matrix; on return contains the orthogonal
   transformed matrix.
  \param _d On return contains the diagonal elements of the tri-diagonal matrix.
  \param _e On teturn contains the off-diagonal elements.

  \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11

    \deprecated Scheduled for replacement by 2010.
*/
#ifdef EIGEN_VECTORS
  void tri_dagv(BOR_CONST dmatrix& _m,BOR_CONST dvector& _d,BOR_CONST dvector& _e)
#else
  void tri_dagv(BOR_CONST dmatrix& _m,BOR_CONST dvector& _d,BOR_CONST dvector& _e)
#endif
{
  dvector& d = (dvector&) _d;
  dvector& e = (dvector&) _e;
  dmatrix& m = (dmatrix&) _m;
  if (m.rowsize() != m.colsize())
  {
    cerr << "Error -- non square matrix passed to void tridag(_CONST dmatrix& m)\n";
    ad_exit(1);
  }
  if (m.rowsize() != d.size() || m.rowsize() != e.size()
    || d.indexmin() != 1 || e.indexmin() !=1 )
  {
    cerr <<"Error -- incorrect vector size passed to void tridag(_CONST dmatrix& m)\n";
    ad_exit(1);
  }
  int n=m.rowsize();
  int l,k,j,i;
  double scale,hh,h,g,f;

  for (i=n;i>=2;i--)
  {
    l=i-1;
    h=scale=0.0;
    if (l > 1)
    {
      for (k=1;k<=l;k++)
        scale += fabs(m[i][k]);
      if (scale == 0.0)
        e[i]=m[i][l];
      else 
      {
        for (k=1;k<=l;k++)
        {
          m[i][k] /= scale;
          h += m[i][k]*m[i][k];
        }
        f=m[i][l];
        g = f>0 ? -sqrt(h) : sqrt(h);
        e[i]=scale*g;
        h -= f*g;
        m[i][l]=f-g;
        f=0.0;
        for (j=1;j<=l;j++) 
        {
        #ifdef EIGEN_VECTORS
        /* Next statement can be omitted if eigenvectors not wanted */
          m[j][i]=m[i][j]/h;
        #endif
          g=0.0;
          for (k=1;k<=j;k++)
            g += m[j][k]*m[i][k];
          for (k=j+1;k<=l;k++)
            g += m[k][j]*m[i][k];
          e[j]=g/h;
          f += e[j]*m[i][j];
        }
        hh=f/(h+h);
        for (j=1;j<=l;j++) 
        {
          f=m[i][j];
          e[j]=g=e[j]-hh*f;
          for (k=1;k<=j;k++)
            m[j][k] -= (f*e[k]+g*m[i][k]);
        }
      }
    }
    else
    {
      e[i]=m[i][l];
    }
    d[i]=h;
  }
  /* Next statement can be omitted if eigenvectors not wanted */
  d[1]=0.0;
  e[1]=0.0;
  /* Contents of this loop can be omitted if eigenvectors not
      wanted except for statement d[i]=a[i][i]; */
  #ifdef EIGEN_VECTORS
  for (i=1;i<=n;i++) 
  {
    l=i-1;
    if (d[i])
    {
      for (j=1;j<=l;j++)
      {
        g=0.0;
        for (k=1;k<=l;k++)
          g += m[i][k]*m[k][j];
        for (k=1;k<=l;k++)
          m[k][j] -= g*m[k][i];
      }
    }
    d[i]=m[i][i];
    m[i][i]=1.0;
    for (j=1;j<=l;j++) m[j][i]=m[i][j]=0.0;
  }
  #endif
}

/** Change sign.
  \param x Argument to change.
  \param y Argument to test.
  \return The value of x with the sign of y.
*/
double SIGNV( CGNU_DOUBLE x, double y)
{
  if (y<0)
  {
    return -fabs(x);
  }
  else
  {
    return fabs(x);
  }
}

/** Eigenvalues and eigenvectors.
  \param _d Diagonal elements of the matrix computed by Householder transformation.
  \param _e Off-diagonal elements.
  \param _z On output contains eigenvectors of _d.

  \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11

  \deprecated Scheduled for replacement by 2010.
*/
#ifdef EIGEN_VECTORS
  void get_eigenv(const dvector& _d,const dvector& _e,const dmatrix& _z)
#else
  void get_eigen(BOR_CONST dvector& _d,BOR_CONST dvector& _e,BOR_CONST dmatrix& _z)
#endif
{
  dvector& d = (dvector&) _d;
  dvector& e = (dvector&) _e;
  dmatrix& z = (dmatrix&) _z;
  int n=d.size();
  int m,l,iter,i,k;
  double s,r,p,g,f,dd,c,b;

  for (i=2;i<=n;i++) e[i-1]=e[i];
  e[n]=0.0;
  for (l=1;l<=n;l++) {
    iter=0;
    do {
      for (m=l;m<=n-1;m++) {
        dd=fabs(d[m])+fabs(d[m+1]);
        if (fabs(e[m])+dd == dd) break;
      }
      if (m != l)
      {
        if (iter++ == 30)
        {
          cerr << "Maximum number of iterations exceeded in"
          " dvector eigen(_CONST dmatrix& m)\n";
          ad_exit(1);
        }
        g=(d[l+1]-d[l])/(2.0*e[l]);
        r=sqrt((g*g)+1.0);
        g=d[m]-d[l]+e[l]/(g+SIGNV(r,g));
        s=c=1.0;
        p=0.0;
        for (i=m-1;i>=l;i--) {
          f=s*e[i];
          b=c*e[i];
          if (fabs(f) >= fabs(g)) {
            c=g/f;
            r=sqrt((c*c)+1.0);
            e[i+1]=f*r;
            c *= (s=1.0/r);
          } else {
            s=f/g;
            r=sqrt((s*s)+1.0);
            e[i+1]=g*r;
            s *= (c=1.0/r);
          }
          g=d[i+1]-p;
          r=(d[i]-g)*s+2.0*c*b;
          p=s*r;
          d[i+1]=g+p;
          g=c*r-b;
          /* Next loop can be omitted if eigenvectors not wanted */
          #ifdef EIGEN_VECTORS
            for (k=1;k<=n;k++) 
            {
              f=z[k][i+1];
              z[k][i+1]=s*z[k][i]+c*f;
              z[k][i]=c*z[k][i]-s*f;
            }
          #endif
        }
        d[l]=d[l]-p;
        e[l]=g;
        e[m]=0.0;
      }
    } while (m != l);
  }
}

#undef EIGEN_VECTORS




