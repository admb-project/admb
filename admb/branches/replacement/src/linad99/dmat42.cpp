/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

int svd(int m,int n,int withu,int withv,double eps,double tol,
        _CONST dmatrix& a,BOR_CONST dvector& _q,
        BOR_CONST dmatrix& _u,BOR_CONST dmatrix& _v);
int svd_nlm(int m,int n,int withu,int withv,double eps,double tol,
        _CONST dmatrix& aa,BOR_CONST dvector& _q,
        BOR_CONST dmatrix& _u,BOR_CONST dmatrix& _v);
int svd_mln(int m,int n,int withu,int withv,double eps,double tol,
        _CONST dmatrix& aa,BOR_CONST dvector& _q,
        BOR_CONST dmatrix& _u,BOR_CONST dmatrix& _v);


static const int  maxiter = 40;

static double pythag(double a, double b)
{
  double fa=fabs(a);
  double fb=fabs(b);
  if (fa>fb)
    return fa*sqrt(1.0+square(fb/fa));
  else
    return fb*sqrt(1.0+square(fa/fb));
}

/*
class sing_val_decomp 
{
  dmatrix a;
  dvector w;
  dmatrix v;
public:
  sing_val_decomp(const dmatrix& _a, const dvector & _w,const dmatrix& _v);
  dmatrix get_u(void){return a;}
  dvector get_w(void){return w;}
  dmatrix get_v(void){return v;}
};
*/

sing_val_decomp::sing_val_decomp(const dmatrix& _a, const dvector & _w,
  const dmatrix& _v) :
    a(_a), w(_w), v(_v)
{}

/** Singular value decomposition.
*/
sing_val_decomp singval_decomp(const dmatrix &_a)
{
  if (_a.indexmin() !=1 )
  {
    cerr << "index error in singval_decomp" << endl;
    ad_exit(1);
  }
  int m=_a.indexmax();
  int n=_a(1).indexmax();
  dmatrix a(1,m,1,n);
  a=_a;
  dvector w(1,n);
  dmatrix u(1,m,1,n);
  dmatrix v(1,n,1,n);

  int k;
  double eps, tol;
  eps = tol = 1.e-12;
  k = svd(m,n,1,1,eps,tol,a,w,u,v);
  if(k!=0)
  {
    cerr << "Error in singval_decomp in iteration " << k << endl;
    ad_exit(1);
  }
  return sing_val_decomp(u,w,v);
}







/** Singular value decomposition.
 * \ingroup svd
 *
 * \param m \f$m\f$ the number of rows of \f$A\f$
 * \param n \f$n\f$ the number of columns of \f$A\f$
 * \param withu true if the \f$U\f$-part is wanted
 * \param withv true if the \f$V\f$-part is wanted
 * \param eps
 * \param tol
 * \param aa \f$A\f$
 * \param _q \f$q\f$
 * \param _u \f$U\f$
 * \param _v \f$V\f$
 * \return an error code = 0, if no errors and 'k' if a failure to
 *         converge at the 'kth' singular value.
 *
 * On return \f$q\f$ will contain the singular values of \f$A\f$
 *           and \f$U\f$ and \f$V\f$ will be a column-orthogonal matrices
 *           so that \f$A = U\cdot\mbox{diag(q)}\cdot V^{T} \f$
 */
int svd(int m,int n,int withu,int withv,double eps,double tol,
        _CONST dmatrix& aa,BOR_CONST dvector& _q,
        BOR_CONST dmatrix& _u,BOR_CONST dmatrix& _v)
{
  ADUNCONST(dmatrix,u)
  ADUNCONST(dmatrix,v)
  ADUNCONST(dvector,q)

  int urlb=u.rowmin();
  int uclb=u.colmin();
  u.rowshift(0);
  u.colshift(0);
  int vrlb=v.rowmin();
  int vclb=v.colmin();
  v.rowshift(0);
  v.colshift(0);
  int qlb=q.indexmin();
  q.shift(0);
  dmatrix a=aa;
  int arlb=a.rowmin();
  int aclb=a.colmin();
  a.rowshift(0);
  a.colshift(0);

  int k;
  if(m>=n)
    k = svd_nlm(m,n,withu,withv,eps,tol,a,q,u,v);
  else
    k = svd_mln(m,n,withu,withv,eps,tol,a,q,u,v);

  u.rowshift(urlb);
  u.colshift(uclb);
  v.rowshift(vrlb);
  v.colshift(vclb);
  q.shift(qlb);
  a.rowshift(arlb);
  a.colshift(aclb);

  return k;
}

/**  Singular value decomposition.
 * \ingroup svd
 *
 * Used to find the svd of a matrix when \f$m<n\f$.
 *
 * \n\n Modified from svd.c (http://www.crbond.com/download/misc/svd.c),
 *      an algorithm that was translated by C. Bond
 *      to 'C' from the original Algol code in "Handbook for
 *      Automatic Computation, vol. II, Linear Algebra", Springer-Verlag.
 */
int svd_mln(int m,int n,int withu,int withv,double eps,double tol,
        _CONST dmatrix& aa,BOR_CONST dvector& _q,
        BOR_CONST dmatrix& _u,BOR_CONST dmatrix& _v)
{
  ADUNCONST(dmatrix,u)
  ADUNCONST(dmatrix,v)
  ADUNCONST(dvector,q)

  int i,j,k,l,l1,iter,retval;
  double c,f,g,h,s,x,y,z;
  double *e;

  e = (double *)calloc(n,sizeof(double));
  retval = 0;

  u=aa;

/* Householder's reduction to bidiagonal form. */
  g = x = 0.0;    
  for (i=0;i<n;i++)
  {
    e[i] = g;
    s = g = 0.0;
    l = i+1;
    if( i<m )
    {
      for (j=i;j<m;j++)
      {
        s += (u[j][i]*u[j][i]);
      }
      if (s < tol)
        g = 0.0;
      else
      {
        f = u[i][i];
        g = (f < 0) ? sqrt(s) : -sqrt(s);
        h = f * g - s;
        u[i][i] = f - g;
        for (j=l;j<n;j++)
        {
          s = 0.0;
          for (k=i;k<m;k++)
          {
            s += (u[k][i] * u[k][j]);
          }
          f = s / h;
          for (k=i;k<m;k++)
          {
            u[k][j] += (f * u[k][i]);
          }
        } /* end j */
      } /* end s */
    }
    q[i] = g;
    s = g = 0.0;
    if( i<m && i!=n-1 )
    {
      for (j=l;j<n;j++)
      {
        s += (u[i][j] * u[i][j]);
      }
      if (s < tol)
        g = 0.0;
      else
      {
        f = u[i][i+1];
        g = (f < 0) ? sqrt(s) : -sqrt(s);
        h = f * g - s;
        u[i][i+1] = f - g;
        for (j=l;j<n;j++)
        {
          e[j] = u[i][j]/h;
        }
        for (j=l;j<m;j++)
        {
          s = 0.0;
          for (k=l;k<n;k++)
          {
            s += (u[j][k] * u[i][k]);
          }
          for (k=l;k<n;k++)
          {
            u[j][k] += (s * e[k]);
          }
        } /* end j */
      } /* end s */
    } /* end if*/
    y = fabs(q[i]) + fabs(e[i]);
    if (y > x)
    {
      x = y;
    }
  } /* end i */

/* accumulation of right-hand transformations */
  if (withv)
  {
    for (i=n-1;i>=0;i--)
    {
      if ( i < n-2 )
      {
        if (g != 0.0)
        {
          h = u[i][i+1] * g;
          for (j=l;j<n;j++)
          {
            v[j][i] = u[i][j]/h;
          }
          for (j=l;j<n;j++)
          {
            s = 0.0;
            for (k=l;k<n;k++)
            {
              s += (u[i][k] * v[k][j]);
            }
            for (k=l;k<n;k++)
            {
              v[k][j] += (s * v[k][i]);
            }

          } /* end j */
        } /* end g */
        for (j=l;j<n;j++)
        {
          v[i][j] = v[j][i] = 0.0;
        }
      }
      v[i][i] = 1.0;
      g = e[i];
      l = i;
    } /* end i */
 
  } /* end withv, parens added for clarity */

/* accumulation of left-hand transformations */
  if (withu) {
    for (i=min(m,n)-1;i>=0;i--) {
      l = i + 1;
      g = q[i];
      for (j=l;j<n;j++)  /* upper limit was 'n' */
        u[i][j] = 0.0;
      if (g != 0.0) {
        h = u[i][i] * g;
        for (j=l;j<n;j++) { /* upper limit was 'n' */
          s = 0.0;
          for (k=l;k<m;k++)
            s += (u[k][i] * u[k][j]);
          f = s / h;
          for (k=i;k<m;k++) 
            u[k][j] += (f * u[k][i]);
        } /* end j */
        for (j=i;j<m;j++) 
          u[j][i] /= g;
      } /* end g */
      else {
        for (j=i;j<m;j++)
          u[j][i] = 0.0;
      }
      u[i][i] += 1.0;
    } /* end i*/
  } /* end withu, parens added for clarity */

/* diagonalization of the bidiagonal form */
  eps *= x;
  for (k=n-1;k>=0;k--) {
    iter = 0;
test_f_splitting:
    for (l=k;l>=0;l--) {
      if (fabs(e[l]) <= eps) goto test_f_convergence;
      if (fabs(q[l-1]) <= eps) goto cancellation;
    } /* end l */

/* cancellation of e[l] if l > 0 */
cancellation:
    c = 0.0;
    s = 1.0;
    l1 = l - 1;
    for (i=l;i<=k;i++) {
      f = s * e[i];
      e[i] *= c;
      if (fabs(f) <= eps) goto test_f_convergence;
      g = q[i];
      h = q[i] = sqrt(f*f + g*g);
      c = g / h;
      s = -f / h;
      if (withu) {
        for (j=0;j<m;j++) {
          y = u[j][l1];
          z = u[j][i];
          u[j][l1] = y * c + z * s;
          u[j][i] = -y * s + z * c;
        } /* end j */
      } /* end withu, parens added for clarity */
    } /* end i */
test_f_convergence:
    z = q[k];
    if (l == k) goto convergence;

/* shift from bottom 2x2 minor */
    iter++;
    if (iter > 30) {
      retval = k;
      break;
    }
    x = q[l];
    y = q[k-1];
    g = e[k-1];
    h = e[k];
    f = ((y-z)*(y+z) + (g-h)*(g+h)) / (2*h*y);
    g = sqrt(f*f + 1.0);
    f = ((x-z)*(x+z) + h*(y/((f<0)?(f-g):(f+g))-h))/x;
/* next QR transformation */
    c = s = 1.0;
    for (i=l+1;i<=k;i++) {
      g = e[i];
      y = q[i];
      h = s * g;
      g *= c;
      e[i-1] = z = sqrt(f*f+h*h);
      c = f / z;
      s = h / z;
      f = x * c + g * s;
      g = -x * s + g * c;
      h = y * s;
      y *= c;
      if (withv) {
        for (j=0;j<n;j++) {
          x = v[j][i-1];
          z = v[j][i];
          v[j][i-1] = x * c + z * s;
          v[j][i] = -x * s + z * c;
        } /* end j */
      } /* end withv, parens added for clarity */
      q[i-1] = z = sqrt(f*f + h*h);
      c = f/z;
      s = h/z;
      f = c * g + s * y;
      x = -s * g + c * y;
      if (withu) {
        for (j=0;j<m;j++) {
          y = u[j][i-1];
          z = u[j][i];
          u[j][i-1] = y * c + z * s;
          u[j][i] = -y * s + z * c;
        } /* end j */
      } /* end withu, parens added for clarity */
    } /* end i */
    e[l] = 0.0;
    e[k] = f;
    q[k] = x;
    goto test_f_splitting;
convergence:
    if (z < 0.0) {
/* q[k] is made non-negative */
      q[k] = - z;
      if (withv) {
        for (j=0;j<n;j++)
          v[j][k] = -v[j][k];
      } /* end withv, parens added for clarity */
    } /* end z */
  } /* end k */
  
  free(e);

  return retval;
}

/** \ingroup svd
 * Singular value decomposition.
 *
 * Used to find the svd of a matrix when \f$m\ge n\f$.
 *
 * \n\n Modified from svd.c (http://www.crbond.com/download/misc/svd.c),
 *      an algorithm that was translated by C. Bond
 *      to 'C' from the original Algol code in "Handbook for
 *      Automatic Computation, vol. II, Linear Algebra", Springer-Verlag.
 */
int svd_nlm(int m,int n,int withu,int withv,double eps,double tol,
        _CONST dmatrix& aa,BOR_CONST dvector& _q,
        BOR_CONST dmatrix& _u,BOR_CONST dmatrix& _v)
{

  ADUNCONST(dmatrix,u)
  ADUNCONST(dmatrix,v)
  ADUNCONST(dvector,q)

  int i,j,k,l,l1,iter,retval;
  double c,f,g,h,s,x,y,z;
  double *e;

  e = (double *)calloc(n,sizeof(double));
  retval = 0;

  u=aa;
/* Householder's reduction to bidiagonal form. */
  g = x = 0.0;    
  for (i=0;i<n;i++)
  {
    e[i] = g;
    s = 0.0;
    l = i+1;
    for (j=i;j<m;j++)
    {
      s += (u[j][i]*u[j][i]);
    }
    if (s < tol)
      g = 0.0;
    else
    {
      f = u[i][i];
      g = (f < 0) ? sqrt(s) : -sqrt(s);
      h = f * g - s;
      u[i][i] = f - g;
      for (j=l;j<n;j++)
      {
        s = 0.0;
        for (k=i;k<m;k++)
        {
          s += (u[k][i] * u[k][j]);
        }
        f = s / h;
        for (k=i;k<m;k++)
        {
          u[k][j] += (f * u[k][i]);
        }
      } /* end j */
    } /* end s */
    q[i] = g;
    s = 0.0;
    for (j=l;j<n;j++)
    {
      s += (u[i][j] * u[i][j]);
    }
    if (s < tol)
      g = 0.0;
    else
    {
      f = u[i][i+1];
      g = (f < 0) ? sqrt(s) : -sqrt(s);
      h = f * g - s;
      u[i][i+1] = f - g;
      for (j=l;j<n;j++)
      {
        e[j] = u[i][j]/h;
      }
      for (j=l;j<m;j++)
      {
        s = 0.0;
        for (k=l;k<n;k++)
        {
          s += (u[j][k] * u[i][k]);
        }
        for (k=l;k<n;k++)
        {
          u[j][k] += (s * e[k]);
        }
      } /* end j */
    } /* end s */
    y = fabs(q[i]) + fabs(e[i]);
    if (y > x)
    {
      x = y;
    }
  } /* end i */

/* accumulation of right-hand transformations */
  if (withv)
  {
    for (i=n-1;i>=0;i--)
    {
      if (g != 0.0)
      {
        h = u[i][i+1] * g;
        for (j=l;j<n;j++)
        {
          v[j][i] = u[i][j]/h;
        }
        for (j=l;j<n;j++)
        {
          s = 0.0;
          for (k=l;k<n;k++)
          {
            s += (u[i][k] * v[k][j]);
          }
          for (k=l;k<n;k++)
          {
            v[k][j] += (s * v[k][i]);
          }

        } /* end j */
      } /* end g */
      for (j=l;j<n;j++)
      {
        v[i][j] = v[j][i] = 0.0;
      }
      v[i][i] = 1.0;
      g = e[i];
      l = i;
    } /* end i */
 
  } /* end withv, parens added for clarity */

/* accumulation of left-hand transformations */
  if (withu) {
    for (i=n-1;i>=0;i--) {
      l = i + 1;
      g = q[i];
      for (j=l;j<n;j++)  /* upper limit was 'n' */
        u[i][j] = 0.0;
      if (g != 0.0) {
        h = u[i][i] * g;
        for (j=l;j<n;j++) { /* upper limit was 'n' */
          s = 0.0;
          for (k=l;k<m;k++)
            s += (u[k][i] * u[k][j]);
          f = s / h;
          for (k=i;k<m;k++) 
            u[k][j] += (f * u[k][i]);
        } /* end j */
        for (j=i;j<m;j++) 
          u[j][i] /= g;
      } /* end g */
      else {
        for (j=i;j<m;j++)
          u[j][i] = 0.0;
      }
      u[i][i] += 1.0;
    } /* end i*/
  } /* end withu, parens added for clarity */

/* diagonalization of the bidiagonal form */
  eps *= x;
  for (k=n-1;k>=0;k--) {
    iter = 0;
test_f_splitting:
    for (l=k;l>=0;l--) {
      if (fabs(e[l]) <= eps) goto test_f_convergence;
      if (fabs(q[l-1]) <= eps) goto cancellation;
    } /* end l */

/* cancellation of e[l] if l > 0 */
cancellation:
    c = 0.0;
    s = 1.0;
    l1 = l - 1;
    for (i=l;i<=k;i++) {
      f = s * e[i];
      e[i] *= c;
      if (fabs(f) <= eps) goto test_f_convergence;
      g = q[i];
      h = q[i] = sqrt(f*f + g*g);
      c = g / h;
      s = -f / h;
      if (withu) {
        for (j=0;j<m;j++) {
          y = u[j][l1];
          z = u[j][i];
          u[j][l1] = y * c + z * s;
          u[j][i] = -y * s + z * c;
        } /* end j */
      } /* end withu, parens added for clarity */
    } /* end i */
test_f_convergence:
    z = q[k];
    if (l == k) goto convergence;

/* shift from bottom 2x2 minor */
    iter++;
    if (iter > 30) {
      retval = k;
      break;
    }
    x = q[l];
    y = q[k-1];
    g = e[k-1];
    h = e[k];
    f = ((y-z)*(y+z) + (g-h)*(g+h)) / (2*h*y);
    g = sqrt(f*f + 1.0);
    f = ((x-z)*(x+z) + h*(y/((f<0)?(f-g):(f+g))-h))/x;
/* next QR transformation */
    c = s = 1.0;
    for (i=l+1;i<=k;i++) {
      g = e[i];
      y = q[i];
      h = s * g;
      g *= c;
      e[i-1] = z = sqrt(f*f+h*h);
      c = f / z;
      s = h / z;
      f = x * c + g * s;
      g = -x * s + g * c;
      h = y * s;
      y *= c;
      if (withv) {
        for (j=0;j<n;j++) {
          x = v[j][i-1];
          z = v[j][i];
          v[j][i-1] = x * c + z * s;
          v[j][i] = -x * s + z * c;
        } /* end j */
      } /* end withv, parens added for clarity */
      q[i-1] = z = sqrt(f*f + h*h);
      c = f/z;
      s = h/z;
      f = c * g + s * y;
      x = -s * g + c * y;
      if (withu) {
        for (j=0;j<m;j++) {
          y = u[j][i-1];
          z = u[j][i];
          u[j][i-1] = y * c + z * s;
          u[j][i] = -y * s + z * c;
        } /* end j */
      } /* end withu, parens added for clarity */
    } /* end i */
    e[l] = 0.0;
    e[k] = f;
    q[k] = x;
    goto test_f_splitting;
convergence:
    if (z < 0.0) {
/* q[k] is made non-negative */
      q[k] = - z;
      if (withv) {
        for (j=0;j<n;j++)
          v[j][k] = -v[j][k];
      } /* end withv, parens added for clarity */
    } /* end z */
  } /* end k */
  
  free(e);

  return retval;
}

























/*sing_val_decomp singval_decomp(const dmatrix &_a)
{
  if (_a.indexmin() !=1 )
  {
    cerr << "index error in singval_decomp" << endl;
    ad_exit(1);
  }
  int m=_a.indexmax();
  int n=_a(1).indexmax();
  dmatrix a(1,m,1,n);
  a=_a;
  dvector w(1,n);
  //dmatrix v(1,n,1,m);
  dmatrix v(1,n,1,n);
  int flag,i,its,j,jj,k,l,nm;
  double anorm,c,f,g,h,s,scale,x,y,z;

  dvector rv1(1,n);
  g=scale=anorm=0.0;
  for (i=1;i<=n;i++) {
    l=i+1;
    rv1[i]=scale*g;
    g=s=scale=0.0;
    if (i <= m) {
      for (k=i;k<=m;k++) scale += fabs(a[k][i]);
      if (scale) {
        for (k=i;k<=m;k++) {
          a[k][i] /= scale;
          s += a[k][i]*a[k][i];
        }
        f=a[i][i];
        g = -SIGN(sqrt(s),f);
        h=f*g-s;
        a[i][i]=f-g;
        for (j=l;j<=n;j++) {
          for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];
          f=s/h;
          for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
        }
        for (k=i;k<=m;k++) a[k][i] *= scale;
      }
    }
    w[i]=scale *g;
    g=s=scale=0.0;
    if (i <= m && i != n) {
      for (k=l;k<=n;k++) scale += fabs(a[i][k]);
      if (scale) {
        for (k=l;k<=n;k++) {
          a[i][k] /= scale;
          s += a[i][k]*a[i][k];
        }
        f=a[i][l];
        g = -SIGN(sqrt(s),f);
        h=f*g-s;
        a[i][l]=f-g;
        for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;
        for (j=l;j<=m;j++) {
          for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];
          for (k=l;k<=n;k++) a[j][k] += s*rv1[k];
        }
        for (k=l;k<=n;k++) a[i][k] *= scale;
      }
    }
    anorm=max(anorm,(fabs(w[i])+fabs(rv1[i])));
  }

  for (i=n;i>=1;i--) {
    if (i < n) {
      if (g) {
        for (j=l;j<=n;j++)
          v[j][i]=(a[i][j]/a[i][l])/g;
        for (j=l;j<=n;j++) {
          for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];
          for (k=l;k<=n;k++) v[k][j] += s*v[k][i];
        }
      }
      for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;
    }
    v[i][i]=1.0;
    g=rv1[i];
    l=i;
  }
  for (i=min(m,n);i>=1;i--) {
    l=i+1;
    g=w[i];
    for (j=l;j<=n;j++) a[i][j]=0.0;
    if (g) {
      g=1.0/g;
      for (j=l;j<=n;j++) {
        for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];
        f=(s/a[i][i])*g;
        for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
      }
      for (j=i;j<=m;j++) a[j][i] *= g;
    } else for (j=i;j<=m;j++) a[j][i]=0.0;
    ++a[i][i];
  }
  for (k=n;k>=1;k--) {
    for (its=1;its<=30;its++) {
      flag=1;
      for (l=k;l>=1;l--) {
        nm=l-1;
        if ((double)(fabs(rv1[l])+anorm) == anorm) {
          flag=0;
          break;
        }
        if ((double)(fabs(w[nm])+anorm) == anorm) break;
      }
      if (flag) {
        c=0.0;
        s=1.0;
        for (i=l;i<=k;i++) {
          f=s*rv1[i];
          rv1[i]=c*rv1[i];
          if ((double)(fabs(f)+anorm) == anorm) break;
          g=w[i];
          h=pythag(f,g);
          w[i]=h;
          h=1.0/h;
          c=g*h;
          s = -f*h;
          for (j=1;j<=m;j++) {
            y=a[j][nm];
            z=a[j][i];
            a[j][nm]=y*c+z*s;
            a[j][i]=z*c-y*s;
          }
        }
      }
      z=w[k];
      if (l == k) {
        if (z < 0.0) {
          w[k] = -z;
          for (j=1;j<=n;j++) v[j][k] = -v[j][k];
        }
        break;
      }
      if (its == maxiter) 
      {
        cerr << "convergence failure " << maxiter << " tries" << endl;
        ad_exit(1);
      }
      x=w[l];
      nm=k-1;
      y=w[nm];
      g=rv1[nm];
      h=rv1[k];
      f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
      g=pythag(f,1.0);
      f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
      c=s=1.0;
      for (j=l;j<=nm;j++) {
        i=j+1;
        g=rv1[i];
        y=w[i];
        h=s*g;
        g=c*g;
        z=pythag(f,h);
        rv1[j]=z;
        c=f/z;
        s=h/z;
        f=x*c+g*s;
        g = g*c-x*s;
        h=y*s;
        y *= c;
        for (jj=1;jj<=n;jj++) {
          x=v[jj][j];
          z=v[jj][i];
          v[jj][j]=x*c+z*s;
          v[jj][i]=z*c-x*s;
        }
        z=pythag(f,h);
        w[j]=z;
        if (z) {
          z=1.0/z;
          c=f*z;
          s=h*z;
        }
        f=c*g+s*y;
        x=c*y-s*g;
        for (jj=1;jj<=m;jj++) {
          y=a[jj][j];
          z=a[jj][i];
          a[jj][j]=y*c+z*s;
          a[jj][i]=z*c-y*s;
        }
      }
      rv1[l]=0.0;
      rv1[k]=f;
      w[k]=x;
    }
  }

  return sing_val_decomp(a,w,v);
}*/


/*
main()
{
  int n=50;
  dmatrix M(1,n,1,n);
  dmatrix N(1,n,1,n);
  dvector r(1,n);
  random_number_generator rng(1211);
  M.fill_randu(rng);
  
  sing_val_decomp svd=singval_decomp(M);
  dmatrix U=trans(svd.get_u());
  dmatrix prod(0,n,1,n);
  for (int j=1;j<=n;j++)
  {
    prod(0,j)=norm(U(j));
  }
  for (int i=1;i<=n;i++)
  {
    for (int j=1;j<=n;j++)
    {
      prod(i,j)=U(i)*U(j);
    }
  }
  cout << prod << endl;
} 
*/
  
