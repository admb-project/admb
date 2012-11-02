#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD

#include "fvar.hpp"
#include <math.h>
#ifndef __ZTC__
//#include <iomanip.h>
#endif
#define TINY 1.0e-20;

void lubksb(dmatrix a,_CONST ivector&  indx,dvector b);
void ludcmp(BOR_CONST dmatrix& a,BOR_CONST ivector& indx,BOR_CONST double& d);

dmatrix inv(_CONST dmatrix& m1)
{
  double d;
  if (m1.rowmin()!=m1.colmin() || m1.rowmax() != m1.colmax())
  {
    cerr << " Error in dmatrix inv(_CONST dmatrix&) -- matrix not square \n";
  }
 
  dmatrix a(m1.rowmin(),m1.rowmax(),m1.rowmin(),m1.rowmax());

  int i;
  for (i=m1.rowmin(); i<=m1.rowmax(); i++)
  {
    for (int j=m1.rowmin(); j<=m1.rowmax(); j++)
    {
      a[i][j]=m1[i][j];
    }
  }
  ivector indx(m1.rowmin(),m1.rowmax());
  //int indx[30];

  ludcmp(a,indx,d);

  dmatrix y(m1.rowmin(),m1.rowmax(),m1.rowmin(),m1.rowmax());
  dvector col(m1.rowmin(),m1.rowmax());

  for (int j=m1.rowmin(); j<=m1.rowmax(); j++)
  {
    for (i=m1.rowmin(); i<=m1.rowmax(); i++)
    {
      col[i]=0;
    }
    col[j]=1;

    lubksb(a,indx,col);
  
    for (i=m1.rowmin(); i<=m1.rowmax(); i++)
    {
      y[i][j]=col[i];
    }
  }
  return(y);
}

dmatrix inv(_CONST dmatrix& m1,const double& _ln_det, const int& _sgn)
{
  double d;
  double& ln_det=(double&)(_ln_det);
  ln_det=0.0;
  int& sgn=(int&)(_sgn);
  
  if (m1.rowmin()!=m1.colmin() || m1.rowmax() != m1.colmax())
  {
    cerr << " Error in dmatrix inv(_CONST dmatrix&) -- matrix not square \n";
  }
 
  dmatrix a(m1.rowmin(),m1.rowmax(),m1.rowmin(),m1.rowmax());

  int i;
  for (i=m1.rowmin(); i<=m1.rowmax(); i++)
  {
    for (int j=m1.rowmin(); j<=m1.rowmax(); j++)
    {
      a[i][j]=m1[i][j];
    }
  }
  ivector indx(m1.rowmin(),m1.rowmax());
  //int indx[30];

  ludcmp(a,indx,d);
  if (d>.1) 
  {
    sgn=1;
  }
  else if (d<-0.1)
  {
    sgn=-1;
  }
  else
  {
    sgn=0;
  }
  int j;
  for (j=m1.rowmin();j<=m1.rowmax();j++)
  {
    if (a(j,j)>0)
    {
      ln_det+=log(a[j][j]);
    }
    else if (a(j,j)<0)
    {
      sgn=-sgn;
      ln_det+=log(-a[j][j]);
    }
    else
    {
      sgn=0;
    }
  }

  dmatrix y(m1.rowmin(),m1.rowmax(),m1.rowmin(),m1.rowmax());
  dvector col(m1.rowmin(),m1.rowmax());

  for (j=m1.rowmin(); j<=m1.rowmax(); j++)
  {
    for (i=m1.rowmin(); i<=m1.rowmax(); i++)
    {
      col[i]=0;
    }
    col[j]=1;

    lubksb(a,indx,col);
  
    for (i=m1.rowmin(); i<=m1.rowmax(); i++)
    {
      y[i][j]=col[i];
    }
  }
  return(y);
}


void ludcmp(BOR_CONST dmatrix& _a,BOR_CONST ivector& _indx,BOR_CONST double& _d)
{
  int i=0;
  int imax=0;
  int j=0;
  int k=0;
  int n=0;
  double& d=(double&)_d;
  dmatrix& a=(dmatrix&)_a;
  ivector& indx=(ivector&)_indx;

  n=a.colsize();
  int lb=a.colmin();
  int ub=a.colmax();

  double big,dum,sum,temp;

  dvector vv(lb,ub);


  d=1.0;

  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    for (j=lb;j<=ub;j++)
    {
      temp=fabs(a[i][j]);
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0) 
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
    }
    vv[i]=1.0/big;
  }



  for (j=lb;j<=ub;j++)
  {
    for (i=lb;i<j;i++) 
    {
      sum=a[i][j];
      for (k=lb;k<i;k++)
      {
        sum = sum - a[i][k]*a[k][j];
      }
      a[i][j]=sum;
    }
    big=0.0;
    for (i=j;i<=ub;i++) 
    {
      sum=a[i][j];
      for (k=lb;k<j;k++)
      {
        sum = sum - a[i][k]*a[k][j];
      }
      a[i][j]=sum;
      dum=vv[i]*fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
    }
    if (j != imax)
    {
      for (k=lb;k<=ub;k++)
      {
        dum=a[imax][k];
        a[imax][k]=a[j][k];
        a[j][k]=dum;
      }
      d = -d;
      vv[imax]=vv[j];
    }
    indx[j]=imax;

    if (a[j][j] == 0.0)
    {
      a[j][j]=TINY;
    }

    if (j != n)
    {
      dum=1.0/(a[j][j]);
      for (i=j+1;i<=ub;i++)
      {
        a[i][j] = a[i][j] * dum;
      }
    }
  }
}
#undef TINY 

#define TINY 1.0e-50;

void ludcmp_det(BOR_CONST dmatrix& _a,BOR_CONST ivector& _indx,BOR_CONST double& _d)
{
  int i,imax,j,k,n;
  double& d=(double&)_d;
  dmatrix& a=(dmatrix&)_a;
  ivector& indx=(ivector&)_indx;

  n=a.colsize();
  int lb=a.colmin();
  int ub=a.colmax();

  double big,dum,sum,temp;

  dvector vv(lb,ub);


  d=1.0;

  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    for (j=lb;j<=ub;j++)
    {
      temp=fabs(a[i][j]);
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0) 
    {
      d=0.;
    }
    vv[i]=1.0/big;
  }



  for (j=lb;j<=ub;j++)
  {
    for (i=lb;i<j;i++) 
    {
      sum=a[i][j];
      for (k=lb;k<i;k++)
      {
        sum = sum - a[i][k]*a[k][j];
      }
      a[i][j]=sum;
    }
    big=0.0;
    for (i=j;i<=ub;i++) 
    {
      sum=a[i][j];
      for (k=lb;k<j;k++)
      {
        sum = sum - a[i][k]*a[k][j];
      }
      a[i][j]=sum;
      dum=vv[i]*fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
    }
    if (j != imax)
    {
      for (k=lb;k<=ub;k++)
      {
        dum=a[imax][k];
        a[imax][k]=a[j][k];
        a[j][k]=dum;
      }
      d = -d;
      vv[imax]=vv[j];
    }
    indx[j]=imax;

    if (a[j][j] == 0.0)
    {
      a[j][j]=TINY;
    }

    if (j != n)
    {
      dum=1.0/(a[j][j]);
      for (i=j+1;i<=ub;i++)
      {
        a[i][j] = a[i][j] * dum;
      }
    }
  }
}



void lubksb(dmatrix a,_CONST ivector& indx,dvector b)
{
  int i,ii=0,ip,j,iiflag=0;
  double sum;
  int lb=a.colmin();
  int ub=a.colmax();
  for (i=lb;i<=ub;i++)
  {
    ip=indx[i];
    sum=b[ip];
    b[ip]=b[i];
    if (iiflag)
    {
      for (j=ii;j<=i-1;j++)
      {
        sum -= a[i][j]*b[j];
      }
    }
    else if ( sum )
    {
      ii=i;
      iiflag=1;
    }
    b[i]=sum;
  }
 
  for (i=ub;i>=lb;i--) 
  {
    sum=b[i];
    for (j=i+1;j<=ub;j++) 
    {                        // !!! remove to show bug
      sum -= a[i][j]*b[j];
    }                        // !!! remove to show bug
    b[i]=sum/a[i][i];
  }
}

double det(_CONST dmatrix& m1)
{
  double d;
  dmatrix a(m1.rowmin(),m1.rowmax(),m1.rowmin(),m1.rowmax());

  if (m1.rowmin()!=m1.colmin()||m1.rowmax()!=m1.colmax())
  {
    cerr << "Matrix not square in routine det()" << endl;
    ad_exit(1);
  }

  for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
  {
    for (int j=m1.rowmin(); j<=m1.rowmax(); j++)
    {
      a[i][j]=m1[i][j];
    }
  }

  ivector indx(m1.rowmin(),m1.rowmax());
  ludcmp_det(a,indx,d);
  for (int j=m1.rowmin();j<=m1.rowmax();j++)
  {
      d*=a[j][j];
  }

  return(d);
}

double ln_det(_CONST dmatrix& m1,BOR_CONST int& _sgn)
{
  double d;
  int& sgn=(int&)_sgn;
  dmatrix a(m1.rowmin(),m1.rowmax(),m1.rowmin(),m1.rowmax());

  if (m1.rowmin()!=m1.colmin()||m1.rowmax()!=m1.colmax())
  {
    cerr << "Matrix not square in routine det()" << endl;
    ad_exit(1);
  }

  for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
  {
    for (int j=m1.rowmin(); j<=m1.rowmax(); j++)
    {
      a[i][j]=m1[i][j];
    }
  }

  ivector indx(m1.rowmin(),m1.rowmax());
  ludcmp_det(a,indx,d);
  double ln_det=0.0;
   
  if (d>.1) 
  {
    sgn=1;
  }
  else if (d<-0.1)
  {
    sgn=-1;
  }
  else
  {
    sgn=0;
  }
  for (int j=m1.rowmin();j<=m1.rowmax();j++)
  {
    if (a(j,j)>0)
    {
      ln_det+=log(a[j][j]);
    }
    else if (a(j,j)<0)
    {
      sgn=-sgn;
      ln_det+=log(-a[j][j]);
    }
    else
    {
      sgn=0;
    }
  }
  return(ln_det);
}

void ludcmp_index(BOR_CONST dmatrix& _a,BOR_CONST ivector& _indx,
  BOR_CONST double& _d)
{
  int i=0;
  int imax=0;
  int j=0;
  int k=0;
  int n=0;
  double& d=(double&)_d;
  dmatrix& a=(dmatrix&)_a;
  ivector& indx=(ivector&)_indx;

  n=a.colsize();
  int lb=a.colmin();
  int ub=a.colmax();
  indx.fill_seqadd(lb,1);

  double big,dum,sum,temp;

  dvector vv(lb,ub);


  d=1.0;

  for (i=lb;i<=ub;i++)
  {
    big=0.0;
    for (j=lb;j<=ub;j++)
    {
      temp=fabs(a[i][j]);
      if (temp > big)
      {
        big=temp;
      }
    }
    if (big == 0.0) 
    {
      cerr << "Error in matrix inverse -- matrix singular in inv(dmatrix)\n";
    }
    vv[i]=1.0/big;
  }



  for (j=lb;j<=ub;j++)
  {
    for (i=lb;i<j;i++) 
    {
      sum=a[i][j];
      for (k=lb;k<i;k++)
      {
        sum = sum - a[i][k]*a[k][j];
      }
      a[i][j]=sum;
    }
    big=0.0;
    for (i=j;i<=ub;i++) 
    {
      sum=a[i][j];
      for (k=lb;k<j;k++)
      {
        sum = sum - a[i][k]*a[k][j];
      }
      a[i][j]=sum;
      dum=vv[i]*fabs(sum);
      if ( dum >= big)
      {
        big=dum;
        imax=i;
      }
    }
    if (j != imax)
    {
      for (k=lb;k<=ub;k++)
      {
        dum=a[imax][k];
        a[imax][k]=a[j][k];
        a[j][k]=dum;
      }
      d = -d;
      vv[imax]=vv[j];
      int itemp=indx.elem(imax);
      indx.elem(imax)=indx.elem(j);
      indx.elem(j)=itemp;
    }

    if (a[j][j] == 0.0)
    {
      a[j][j]=TINY;
    }

    if (j != n)
    {
      dum=1.0/(a[j][j]);
      for (i=j+1;i<=ub;i++)
      {
        a[i][j] = a[i][j] * dum;
      }
    }
  }
}
#undef TINY
#undef HOME_VERSION


