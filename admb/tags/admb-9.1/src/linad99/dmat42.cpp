/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

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
    Not clear that this is used for anything. 
    \param _a
    \return

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2

    \deprecated Scheduled for replacement by 2010.
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
  dmatrix v(1,n,1,m);
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
}


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
  
