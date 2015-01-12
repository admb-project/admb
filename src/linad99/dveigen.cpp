/*
 * $Id$
 * Author: Unknown
 */
//#define EIGEN_VECTORS

#include <fvar.hpp>


void tri_dag(BOR_CONST dvar_matrix& ,BOR_CONST dvar_vector& ,BOR_CONST dvar_vector& );
void get_eigen(BOR_CONST dvar_vector& d,BOR_CONST dvar_vector& e,_CONST dvar_matrix& z);


dvar_vector eigenvalues(_CONST dvar_matrix& m)
{
  if (m.rowsize()!=m.colsize())
  {
    cerr << "Error -- non square matrix passed to dvector eigen(_CONST dvar_matrix& m)\n";
    ad_exit(1);
  }
  dvar_matrix m1=symmetrize(m);
  int n=m1.rowsize();
  int cmin=m1.colmin();
  int rmin=m1.rowmin();
  m1.colshift(1);     // set minimum column and row indices to 1
  m1.rowshift(1);
  dvar_vector diag(1,n);
  dvar_vector off_diag(1,n);

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

  \deprecated Scheduled for replacement by 2010.
*/
void tri_dag(BOR_CONST dvar_matrix& _m,BOR_CONST dvar_vector& _d, BOR_CONST dvar_vector& _e)
{
  ADUNCONST(dvar_vector,d)
  ADUNCONST(dvar_vector,e)
  dvar_matrix& m=(dvar_matrix&) _m;
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
  dvariable scale,hh,h,g,f;

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
        g = f>0. ? -sqrt(h) : sqrt(h);
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
  #else
    for (i=1;i<=n;i++) 
    {
      d[i]=m[i][i];
    }
  #endif
}

  dvariable SIGN(_CONST prevariable& x,_CONST prevariable& y)
{
#if defined __SUN__ || defined(__GNU__) 
  if(value(y) < 0)
#else
  if (y<0)
#endif
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
  \param _d Diagonal elements of the matrix computed by Householder transformation.
  \param _e Off-diagonal elements.
  \param _z On output contains nothing useful.

  \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11

  \deprecated Scheduled for replacement by 2010.
*/
void get_eigen(BOR_CONST dvar_vector& _d,BOR_CONST dvar_vector& _e,_CONST dvar_matrix& z)
{
  ADUNCONST(dvar_vector,d)
  ADUNCONST(dvar_vector,e)
  int n=d.size();
  int m,l,iter,i,k;
  dvariable s,r,p,g,f,dd,c,b;

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

/** Eigenvalues and eigenvectors.
  \param _d Diagonal elements of the matrix computed by Householder transformation.
  \param _e Off-diagonal elements.
  \param _z On return containses eigenvectors.
  \return Vector of eigenvalues.

 \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 11

    \deprecated Scheduled for replacement by 2010.
*/
dvar_vector get_eigen_values(const dvar_vector& _ddd,const dvar_vector& _eee)
{
  ADUNCONST(dvar_vector,ddd)
  ADUNCONST(dvar_vector,eee)


  dvar_vector d(ddd.indexmin(),ddd.indexmax());
  dvar_vector e(eee.indexmin(),eee.indexmax());

  d=ddd;
  e=eee;



  int n=d.size();
  int m,l,iter,i,k;
  dvariable s,r,p,g,f,dd,c,b;

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

