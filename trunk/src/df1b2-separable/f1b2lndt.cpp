/**
 * $Id: f1b2lndt.cpp 789 2010-10-05 01:01:09Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California
 */
#include <df1b2fun.h>

class df1b2matrix_pair
{
  df1b2matrix a;
  df1b2matrix b;
  ivector index;
public:
  df1b2matrix_pair(const df1b2matrix & _a,const df1b2matrix & _b);
  df1b2matrix get_a(void){return a;}
  df1b2matrix get_b(void){return b;}
};

dmatrix ludcmp(const dmatrix& M,int kludge);
df1b2matrix reorder(const df1b2matrix& M,const ivector& indx);
df1b2vector reorder(const df1b2vector& M,const ivector& indx);
void ludcmp(const df1b2matrix& a,int k);
df1b2matrix_pair ludcmp(const df1b2matrix& a);

/** LU decomposition back susbstitution alogrithm for df1b2matrix object.
    \param a A dmatrix containing LU decomposition of input matrix. \f$a\f$.
    \param indx Permutation vector from ludcmp.
    \param b A dvector containing the RHS, \f$b\f$ of the linear equation
    \f$A\cdot X = B\f$, to be solved, and containing on return the solution vector \f$X\f$.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 2

    \deprecated Scheduled for replacement by 2010.
*/
df1b2vector lubksb(const df1b2matrix&  alpha, const df1b2matrix& beta,
  ivector & ,const df1b2vector& b)
{
  int i,ii=0,ip,j;
  df1b2variable sum;
  int mmin=b.indexmin();
  int mmax=b.indexmax();
  if (mmin !=1)
  {
    cerr << "not implemented" << endl;
    ad_exit(1);
  }
  int n=mmax;
  df1b2vector c(mmin,mmax);
  c=b;

  for (i=1;i<=n;i++)
  {
    sum=c(i);
    if (ii)
    {
      df1b2vector bt=c(ii,i-1);
      df1b2vector at=alpha(i)(ii,i-1);
      sum-=at*bt;
    }
    else
    {
      if (value(sum)) ii=i;
    }
    c(i)=sum;
  }
  for (i=n;i>=1;i--)
  {
    sum=c(i);
    for (j=i+1;j<=n;j++) sum -= beta(j)(i)*c(j);
    c(i)=sum/beta(i)(i);
  }
  return c;
}

df1b2variable get_ln_det(const df1b2matrix& b,int& sgn)
{
  // determinant of a lower triangular matrix
  int i;
  int mmin=b.indexmin();
  int mmax=b.indexmax();
  sgn=1;
  df1b2variable ln_det;
  ln_det=0.0;
  for (i=mmin;i<=mmax;i++)
  {
    if (value(b(i,i))<0.0)
    {
      ln_det+=log(-b(i,i));
      sgn=-sgn;
    }
    else
    {
      ln_det+=log(b(i,i));
    }
  }
  return ln_det;
}

df1b2matrix lubksb(const df1b2matrix&  alpha, const df1b2matrix& beta,
  ivector & ,const df1b2matrix& B)
{
  int i,ii=0,ip,j;
  int rmin=B.indexmin();
  int rmax=B.indexmin();
  df1b2matrix C(rmin,rmax);
  for (int k=rmin;k<=rmax;k++)
  {
    df1b2variable sum;
    int mmin=B(k).indexmin();
    int mmax=B(k).indexmax();
    if (mmin !=1)
    {
      cerr << "not implemented" << endl;
      ad_exit(1);
    }
    int n=mmax;
    df1b2vector c(mmin,mmax);
    c=B(k);

    for (i=1;i<=n;i++) {
      sum=c(i);
      if (ii)
      {
        df1b2vector bt=c(ii,i-1);
        df1b2vector at=alpha(i)(ii,i-1);
        sum-=at*bt;
      }
      else
      {
        if (value(sum)) ii=i;
      }
      c(i)=sum;
    }
    for (i=n;i>=1;i--)
    {
      sum=c(i);
      for (j=i+1;j<=n;j++) sum -= beta(j)(i)*c(j);
      c(i)=sum/beta(i)(i);
    }
    C(i)=c;
  }
  return C;
}

df1b2matrix_pair::df1b2matrix_pair(const df1b2matrix& _a,
  const df1b2matrix& _b) : a(_a), b(_b)
{}

void ludcmp(const df1b2matrix& M,int kludge)
{
  // do lu decomp once to get ordering
  int mmin=M.indexmin();
  int mmax=M.indexmax();

  ivector indx(mmin,mmax);
  ivector indx2(mmin,mmax);
  double d;
  dmatrix MC=value(M);
  ludcmp(MC,indx,d);

  df1b2matrix RM=reorder(M,indx);

  ludcmp(RM);

}

df1b2matrix reorder(const df1b2matrix& M,const ivector& indx)
{
  int i;
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if ( (indx.indexmin() != mmin) || (indx.indexmax() != mmax)
    || (M(mmin).indexmin() != mmin)
    || (M(mmin).indexmax() != mmax) )
  {
    cerr << " Inconsistent sizes in "
      " dmatrix reorder(const dmatrix& M,const ivector& indx) "
      << endl;
    ad_exit(1);
  }
  df1b2matrix RM(mmin,mmax);
  ivector ir(mmin,mmax);
  ir.fill_seqadd(mmin,1);

  for (i=mmin;i<=mmax;i++)
  {
    int tmp=ir(i);
    ir(i)=ir(indx(i));
    ir(indx(i))=tmp;
  }
  //cout << ir << endl;
  for (i=mmin;i<=mmax;i++)
  {
    RM(i)=M(ir(i));
  }
  return RM;
}
df1b2vector reorder(const df1b2vector& M,const ivector& indx)
{
  int i;
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if ( (indx.indexmin() != mmin) || (indx.indexmax() != mmax) )
  {
    cerr << " Inconsistent sizes in "
      " dvector reorder(const dvector& M,const ivector& indx) "
      << endl;
    ad_exit(1);
  }
  df1b2vector RM(mmin,mmax);
  ivector ir(mmin,mmax);
  ir.fill_seqadd(mmin,1);

  for (i=mmin;i<=mmax;i++)
  {
    int tmp=ir(i);
    ir(i)=ir(indx(i));
    ir(indx(i))=tmp;
  }
  //cout << ir << endl;
  for (i=mmin;i<=mmax;i++)
  {
    RM(i)=M(ir(i));
  }
  return RM;
}

df1b2matrix_pair ludcmp(const df1b2matrix& a)
{
  int i,imax,j,k;
  double big,dum,temp;
  double *vv;

  int n=a.indexmax();
  ivector ishape(1,n);
  ishape.fill_seqadd(1,1);
  df1b2matrix alpha(1,n,1,ishape);
  df1b2matrix beta(1,n,1,ishape);
  //df1b2matrix delta(1,n,1,n);
  df1b2vector gamma(1,n);
  alpha.initialize();
  beta.initialize();
  gamma.initialize();

  double d=1.0;
  df1b2variable sum;
  for (j=1;j<=n;j++)
  {
    for (i=1;i<j;i++)
    {
      df1b2vector& ai=alpha(i);
      df1b2vector& bj=beta(j);
      sum=a(i,j);
      //for (k=1;k<i;k++) { sum -= ai(k)*bj(k); }
      sum-=ai(1,i)*bj(1,i);
      beta(j,i)=sum;
    }
    for (i=j;i<=n;i++)
    {
      df1b2vector& ai=alpha(i);
      df1b2vector& bj=beta(j);
      sum=a(i,j);
      //for (k=1;k<j;k++) { sum -= ai(k)*bj(k); }
      sum-=ai(1,j)*bj(1,j);
      if (i==j)
      {
        beta(i,j)=sum;
      }
      else
      {
        if (j !=n)
        {
          //delta(i,j)=sum;
          alpha(i,j)=sum;
        }
        else
        {
          alpha(i,j)=sum;
        }
      }
    }
    if (j != n)
    {
      gamma(j)=1.0/beta(j,j);
      for (i=j+1;i<=n;i++)
      {
        alpha(i,j)*=gamma(j);
        //alpha(i,j) = delta(i,j)*gamma(j);
      }
    }
  }
  return df1b2matrix_pair(alpha,beta);
}
dmatrix reorder(const dmatrix& CM,ivector & indx);
ivector getreindex(ivector & indx);

df1b2variable ln_det(const df1b2matrix& M,int & sgn)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin !=1)
  {
    cerr << "not implemented" << endl;
    ad_exit(1);
  }
  int ssgn=0;
  dmatrix CM=value(M);
  double cld=ln_det(CM,ssgn);
  ssgn=0;
  ivector indx(1,mmax);
  double dd;
  ludcmp(CM,indx,dd);
  ssgn=0;
  ivector reindex=getreindex(indx);
  df1b2matrix RM=reorder(M,indx);
  df1b2matrix_pair p=ludcmp(RM);
  int isg=0;
  df1b2variable ld=get_ln_det(p.get_b(),isg);
  cout << setprecision(16) << cld-value(ld) << "  ";
  //cout << dd << " " << isg << "  "  << dd*isg << endl;
  return ld;
}

df1b2variable ln_det(const df1b2matrix& M)
{
  int sgn;
  return ln_det(M,sgn);
}

dmatrix reorder(const dmatrix& CM,ivector & indx)
{
  int mmin=CM.indexmin();
  int mmax=CM.indexmax();
  dmatrix M(mmin,mmax,mmin,mmax);
  dvector tmp(mmin,mmax);
  int itmp;
  dvector in(mmin,mmax);
  in.fill_seqadd(1,1);
  for (int i=mmin;i<=mmax;i++)
  {
    M(i)=CM(indx(i));
  }
  return M;
}
void xswitch(int & i1,int & i2)
{
  int tmp=i1;
  i1=i2;
  i2=tmp;
}

ivector getreindex(ivector & indx)
{
  int mmin=indx.indexmin();
  int mmax=indx.indexmax();
  ivector in1(mmin,mmax);
  ivector in2(mmin,mmax);
  in1.fill_seqadd(1,1);
  in2.fill_seqadd(1,1);
  for (int i=mmin;i<=mmax;i++)
  {
    xswitch(in1(i),in1(indx(i)));
  }
 return in1;

}

df1b2vector solve(df1b2matrix& M,df1b2vector& v)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin !=1)
  {
    cerr << "not implemented" << endl;
    ad_exit(1);
  }
  dmatrix CM=value(M);
  ivector indx(1,mmax);
  double dd;
  ludcmp(CM,indx,dd);
  df1b2matrix RM=reorder(M,indx);
  df1b2vector rb=reorder(v,indx);
  df1b2matrix_pair p=ludcmp(RM);
  return lubksb(p.get_a(),p.get_b(),indx,rb);
}

df1b2vector solve(df1b2matrix& M,df1b2vector& v,const df1b2variable& _ln_det)
{
  df1b2variable& ln_det = (df1b2variable&) _ln_det;
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin !=1)
  {
    cerr << "not implemented" << endl;
    ad_exit(1);
  }
  dmatrix CM=value(M);
  ivector indx(1,mmax);
  double dd;
  ludcmp(CM,indx,dd);
  df1b2matrix RM=reorder(M,indx);
  df1b2vector rb=reorder(v,indx);
  df1b2matrix_pair p=ludcmp(RM);
  int isg;
  ln_det=get_ln_det(p.get_b(),isg);
  return lubksb(p.get_a(),p.get_b(),indx,rb);
}

df1b2vector solve(df1b2matrix& M,df1b2vector& v,const df1b2variable& _ln_det,
  const int& sgn)
{
  df1b2variable& ln_det = (df1b2variable&) _ln_det;
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (mmin !=1)
  {
    cerr << "not implemented" << endl;
    ad_exit(1);
  }
  dmatrix CM=value(M);
  ivector indx(1,mmax);
  double dd;
  ludcmp(CM,indx,dd);
  df1b2matrix RM=reorder(M,indx);
  df1b2vector rb=reorder(v,indx);
  df1b2matrix_pair p=ludcmp(RM);
  int isg;
  ln_det=get_ln_det(p.get_b(),isg);
  return lubksb(p.get_a(),p.get_b(),indx,rb);
}
