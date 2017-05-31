/**
 * $Id: eigen.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2009, 2010 ADMB foundation
 */

//#define eigen_vectors

#include <fvar.hpp>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

void tri_dag(const dmatrix& m, const dvector& d,const dvector& e);
void get_eigen(const dvector& d, const dvector& e, const dmatrix& z);

/** Eigenvalues.
  \param m Input matrix (unchanged on return).
  \return Vector of eigenvalues.
*/
dvector eigenvalues(const dmatrix& m)
{
  if (m.rowsize()!=m.colsize())
  {
    cerr << "error -- non square matrix passed to "
    "dvector eigen(const dmatrix& m)\n";
    ad_exit(1);
  }
  dmatrix m1=symmetrize(m);
  m1.colshift(1);     // set minimum column and row indices to 1
  m1.rowshift(1);
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  int n = [](unsigned int rowsize) -> int
  {
    assert(rowsize <= INT_MAX);
    return static_cast<int>(rowsize);
  } (m1.rowsize());
#else
  int n = static_cast<int>(m1.rowsize());
#endif
  dvector diag(1,n);
  dvector off_diag(1,n);

  tri_dag(m1,diag,off_diag);

  get_eigen(diag,off_diag,m1); // eigenvalues are returned in diag
           // eigenvalues are returned in columns of z
  return diag;
}

/** Householder transformation for eigenvalue computation.
  \param _m Real, symmetric matrix; on return contains the orthogonal
   transformed matrix.
  \param _d On return contains the diagonal elements of the tri-diagonal matrix.
  \param _e On teturn contains the off-diagonal elements.

  \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11
*/
void tri_dag(const dmatrix& _m, const dvector& _d, const dvector& _e)
{
  dvector& d = (dvector&) _d;
  dvector& e = (dvector&) _e;
  dmatrix& m = (dmatrix&) _m;
  if (m.rowsize() != m.colsize())
  {
    cerr << "Error -- non square matrix passed to "
    "void tridag(const dmatrix& m)\n";
    ad_exit(1);
  }
  if (m.rowsize() != d.size() || m.rowsize() != e.size()
    || d.indexmin() != 1 || e.indexmin() !=1 )
  {
    cerr <<"Error -- incorrect vector size passed to "
    "void tridag(const dmatrix& m)\n";
    ad_exit(1);
  }
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  int n = [](unsigned int rowsize) -> int
  {
    assert(rowsize <= INT_MAX);
    return static_cast<int>(rowsize);
  } (m.rowsize());
#else
  int n = static_cast<int>(m.rowsize());
#endif
  int l,j,i;
  double scale,hh,h,g,f;

  for (i=n;i>=2;i--)
  {
    l=i-1;
    h=scale=0.0;
    if (l > 1)
    {
      for (int k=1;k<=l;k++)
        scale += fabs(m[i][k]);
      if (scale == 0.0)
        e[i]=m[i][l];
      else
      {
        for (int k=1;k<=l;k++)
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
          for (int k=1;k<=j;k++)
            g += m[j][k]*m[i][k];
          for (int k=j+1;k<=l;k++)
            g += m[k][j]*m[i][k];
          e[j]=g/h;
          f += e[j]*m[i][j];
        }
        hh=f/(h+h);
        for (j=1;j<=l;j++)
        {
          f=m[i][j];
          e[j]=g=e[j]-hh*f;
          for (int k=1;k<=j;k++)
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
        for (int k=1;k<=l;k++)
          g += m[i][k]*m[k][j];
        for (int k=1;k<=l;k++)
          m[k][j] -= g*m[k][i];
      }
    }
    d[i]=m[i][i];
    m[i][i]=1.0;
    for (j=1;j<=l;j++) m[j][i]=m[i][j]=0.0;
  }
  #else
  for (i=1;i<=n;i++)
  {
    d[i]=m[i][i];
  }
  #endif
}

double SIGN(const double x, double y)
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
//#define SIGN(a,b) ((b)<0 ? -fabs(a) : fabs(a))

/** Eigenvalues.
  \param _d Diagonal elements of the matrix computed by Householder
  transformation.
  \param _e Off-diagonal elements.
  \param _z On output contains nothing useful.

  \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11
*/
void get_eigen(const dvector& _d, const dvector& _e, const dmatrix& _z)
{
  dvector& d = (dvector&) _d;
  dvector& e = (dvector&) _e;
#ifdef EIGEN_VECTORS
  dmatrix& z = (dmatrix&) _z;
#endif
  int max_iterations=30;
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  int n = [](unsigned int size) -> int
  {
    assert(size <= INT_MAX);
    return static_cast<int>(size);
  } (d.size());
#else
  int n = static_cast<int>(d.size());
#endif
  max_iterations+=10*(n/100);
  int m,l,iter,i;
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
        if (iter++ == max_iterations)
        {
          cerr << "Maximum number of iterations exceeded in"
          " dvector eigen(const dmatrix& m)\n";
          ad_exit(1);
        }
        g=(d[l+1]-d[l])/(2.0*e[l]);
        r=sqrt((g*g)+1.0);
        g=d[m]-d[l]+e[l]/(g+SIGN(r,g));
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
            for (int k=1;k<=n;k++)
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

/** Eigenvalues.
  \param _d Diagonal elements of the matrix computed by Householder
  transformation.
  \param _e Off-diagonal elements.
  \return Vector of eigenvalues.

 \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11
*/
dvector get_eigen_values(const dvector& _d,const dvector& _e)
{
  dvector& d = (dvector&) _d;
  dvector& e = (dvector&) _e;

  int max_iterations=30;
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  int n = [](unsigned int size) -> int
  {
    assert(size <= INT_MAX);
    return static_cast<int>(size);
  } (d.size());
#else
  int n = static_cast<int>(d.size());
#endif
  max_iterations+=10*(n/100);
  int m,l,iter,i;
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
        if (iter++ == max_iterations)
        {
          cerr << "Maximum number of iterations exceeded in"
          " dvector eigen(const dmatrix& m)\n";
          ad_exit(1);
        }
        g=(d[l+1]-d[l])/(2.0*e[l]);
        r=sqrt((g*g)+1.0);
        g=d[m]-d[l]+e[l]/(g+SIGN(r,g));
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
        }
        d[l]=d[l]-p;
        e[l]=g;
        e[m]=0.0;
      }
    } while (m != l);
  }
  return d;
}

/** Eigenvalues and eigenvectors.
  \param _d Diagonal elements of the matrix computed by Householder
  transformation.
  \param _e Off-diagonal elements.
  \param _z On return containses eigenvectors.
  \return Vector of eigenvalues.

 \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11
*/
dvector get_eigen_values(const dvector& _d,const dvector& _e,
  const dmatrix& _z)
  //eigenvectors are returned in z
{
  dvector& xd = (dvector&) _d;
  dvector& xe = (dvector&) _e;
  dmatrix& z = (dmatrix&) _z;

  dvector d(xd.indexmin(),xd.indexmax());
  dvector e(xe.indexmin(),xe.indexmax());

  d=xd;
  e=xe;

  int max_iterations=30;
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  int n = [](unsigned int size) -> int
  {
    assert(size <= INT_MAX);
    return static_cast<int>(size);
  } (d.size());
#else
  int n = static_cast<int>(d.size());
#endif
  max_iterations+=10*(n/100);
  int m,l,iter,i;
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
        if (iter++ == max_iterations)
        {
          cerr << "Maximum number of iterations exceeded in"
          " dvector eigen(const dmatrix& m)\n";
          ad_exit(1);
        }
        g=(d[l+1]-d[l])/(2.0*e[l]);
        r=sqrt((g*g)+1.0);
        g=d[m]-d[l]+e[l]/(g+SIGN(r,g));
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
          for (int k=1;k<=n;k++)
          {
            f=z[k][i+1];
            z[k][i+1]=s*z[k][i]+c*f;
            z[k][i]=c*z[k][i]-s*f;
          }
        }
        d[l]=d[l]-p;
        e[l]=g;
        e[m]=0.0;
      }
    } while (m != l);
  }
  return d;
}
#undef EIGEN_VECTORS
