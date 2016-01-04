/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
//class df1b2matrix;

#include "df12fun.h"

prevariable* df1_two_variable::ind_var[2];

int df1_two_variable::num_ind_var=0;

/**
Default constructor
*/
df1_two_variable::df1_two_variable()
{
  v[0] = 0;
  v[1] = 0;
  v[2] = 0;
}

/**
Copy constructor
*/
df1_two_variable::df1_two_variable(const df1_two_variable& x)
{
  v[0] = x.v[0];
  v[1] = x.v[1];
  v[2] = x.v[2];
}
/**
Copy constructor
*/
df1_two_vector::df1_two_vector(const df1_two_vector& m2)
{
  index_min = m2.index_min;
  index_max = m2.index_max;
  shape  =m2.shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
  v = m2.v;
}
/**
Destructor
*/
df1_two_vector::~df1_two_vector()
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
 void df1_two_vector::deallocate(void)
 {
   if(shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df1_two_variable*) (shape->trueptr);
       delete [] v;
       v = NULL;
       delete shape;
       shape=0;
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvector value(const df1_two_vector& v)
 {
   int mmin=v.indexmin();
   int mmax=v.indexmax();
   dvector cv(mmin,mmax);
   for (int i=mmin;i<=mmax;i++)
   {
     cv(i)=value(v(i));
   }
   return cv;
 }

/**
 * Description not yet available.
 * \param
 */
  void df1_two_vector::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)=0.0;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_vector::df1_two_vector(void)
  {
    allocate();
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_vector::df1_two_vector(int min,int max)
  {
    allocate(min,max);
  }

/**
 * Description not yet available.
 * \param
 */
  void df1_two_vector::allocate(int min,int max)
  {
    index_min=min;
    index_max=max;
    v=new df1_two_variable[max-min+1];
    if (v==0)
    {
      cerr << "error allocating memory in df1_two_vector" << endl;
      ad_exit(1);
    }
    if ( (shape=new vector_shapex(min,max,v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df1_two_vector"
           << endl;;
      ad_exit(1);
    }
    v-=min;
  }

/**
 * Description not yet available.
 * \param
 */
  void df1_two_vector::allocate(void)
  {
    index_min=0;
    index_max=-1;
    v=0;
    shape=0;
  }

/**
 * Description not yet available.
 * \param
 */
 dmatrix value(const df1_two_matrix& v)
 {
   int rmin=v.indexmin();
   int rmax=v.indexmax();
   dmatrix cm(rmin,rmax);
   for (int i=rmin;i<=rmax;i++)
   {
     int cmin=v(i).indexmin();
     int cmax=v(i).indexmax();
     cm(i).allocate(cmin,cmax);
     for (int j=cmin;j<=cmax;j++)
     {
       cm(i,j)=value(v(i,j));
     }
   }
   return cm;
 }

/**
 * Description not yet available.
 * \param
 */
 df1_two_matrix::df1_two_matrix(const df1_two_matrix& m2)
 {
   index_min=m2.index_min;
   index_max=m2.index_max;
   shape=m2.shape;
   if (shape)
   {
     (shape->ncopies)++;
   }
   v = m2.v;
 }

/**
 * Description not yet available.
 * \param
 */
 df1_two_matrix::~df1_two_matrix()
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 void df1_two_matrix::deallocate(void)
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df1_two_vector*) (shape->get_pointer());
       delete [] v;
       v=0;
       delete shape;
       shape=0;
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
  void df1_two_matrix::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).initialize();
    }
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_matrix::df1_two_matrix(int rmin,int rmax,int cmin,int cmax)
  {
    index_min=rmin;
    index_max=rmax;
    v=new df1_two_vector[rmax-rmin+1];
    if (v==0)
    {
      cerr << "error allocating memory in df1_two_matrix" << endl;
      ad_exit(1);
    }
    if ( (shape=new mat_shapex(v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df1_two_vector"
           << endl;;
    }
    v-=rmin;

    for (int i=rmin;i<=rmax;i++)
    {
      v[i].allocate(cmin,cmax);
    }
  }

/**
 * Description not yet available.
 * \param
 */
df1_two_variable& df1_two_variable::operator-=(const df1_two_variable& _v)
{
  *get_u() -= *_v.get_u();
  *get_u_x() -= *_v.get_u_x();
  *get_u_y() -= *_v.get_u_y();

  return *this;
}

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable& df1_two_variable::operator /= (const df1_two_variable& y)
  {
   /*
    df1_three_variable x=*this * inv(y);
    *this=x;
    return *this;
   */
   // properly optimized code
    double tmp=1.0/value(y);
    *get_u()*=tmp;
    *get_u_x() = *get_u_x()*tmp- *get_u()*tmp* *y.get_u_x();
    *get_u_y() = *get_u_y()*tmp- *get_u()*tmp* *y.get_u_y();
    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
df1_two_variable operator-(const df1_two_variable& v)
{
  df1_two_variable z;

  *z.get_u() = -(*v.get_u());
  *z.get_u_x() = -(*v.get_u_x());
  *z.get_u_y() = -(*v.get_u_y());

  return z;
}

/**
 * Description not yet available.
 * \param
 */
df1_two_variable& df1_two_variable::operator += (const df1_two_variable& _v)
{
  *get_u() += *_v.get_u();
  *get_u_x() += *_v.get_u_x();
  *get_u_y() += *_v.get_u_y();
  return *this;
}

  df1_two_variable& df1_two_variable::operator *= (double v)
  {
   /*
    df1_three_variable x=*this * v;
    *this=x;
    return *this;
   */
    *get_u()*=v;
    *get_u_x() = *get_u_x()*v;
    *get_u_y() = *get_u_y()*v;
    return *this;
  }


/**
 * Description not yet available.
 * \param
 */
  df1_two_variable& df1_two_variable::operator *= (const df1_two_variable& v)
  {
    df1_two_variable x=*this * v;
    *this=x;
    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
df1_two_variable& df1_two_variable::operator+=(double _v)
{
  *get_u() += _v;

  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1_two_variable& df1_two_variable::operator-=(double _v)
{
  *get_u() -= _v;

  return *this;
}

/**
 * Description not yet available.
 * \param
 */
void set_derivatives( df1_two_variable& z,const df1_two_variable& x,double u,
  double zp)
{
    //*z.get_u() = u;
    *z.get_u_x() = zp* *x.get_u_x();
    *z.get_u_y() = zp* *x.get_u_y();
}

/**
 * Description not yet available.
 * \param
 */
void set_derivatives( df1_two_variable& z, const df1_two_variable& x,
  const df1_two_variable& y, double u,
  double f_u,double f_v)
{
    *z.get_u() = u;

    *z.get_u_x() = f_u* *x.get_u_x()
                 + f_v* *y.get_u_x();

    *z.get_u_y() = f_u* *x.get_u_y()
                 + f_v* *y.get_u_y();
}

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable sqrt(const df1_two_variable& x)
  {
    df1_two_variable z;
    double u=::sqrt(*x.get_u());
    *z.get_u()=u;
    //double xinv=1.0/(*x.get_u());
    double zp=0.5/u;


    set_derivatives(z,x,u,zp);

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable atan(const df1_two_variable& x)
  {
    df1_two_variable z;
    double cx=value(x);
    double d=1.0/(1+square(cx));
    //double d2=square(d);
    double u=::atan(cx);
    *z.get_u()=u;
    double zp=d;

    set_derivatives(z,x,u,zp);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable square(const df1_two_variable& x)
  {
    df1_two_variable z;
    double u=value(x);
    *z.get_u()=u*u;
    double zp=2.0*u;

    set_derivatives(z,x,u,zp);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable tan(const df1_two_variable& x)
  {
    df1_two_variable z;
    double u=::tan(*x.get_u());
    *z.get_u()=u;
    double v=1.0/::cos(*x.get_u());
    //double w=::sin(*x.get_u());
    double v2=v*v;
    double zp=v2;

    set_derivatives(z,x,u,zp);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable sin(const df1_two_variable& x)
  {
    df1_two_variable z;
    double u=::sin(*x.get_u());
    *z.get_u()=u;
    double zp=::cos(*x.get_u());

    set_derivatives(z,x,u,zp);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable log(const df1_two_variable& x)
  {
    df1_two_variable z;
    double u=::log(*x.get_u());
    *z.get_u()=u;
    double zp=1/(*x.get_u());

    set_derivatives(z,x,u,zp);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable exp(const df1_two_variable& x)
  {
    df1_two_variable z;
    double u=::exp(*x.get_u());
    *z.get_u()=u;
    double zp=u;

    set_derivatives(z,x,u,zp);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable pow(const df1_two_variable& x,const df1_two_variable& y)
  {
    return exp(y*log(x));
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable pow(double x,const df1_two_variable& y)
  {
    return exp(y*log(x));
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable inv(const df1_two_variable& x)
  {
    df1_two_variable z;
    double xinv=1.0/(*x.get_u());
    *z.get_u()=xinv;
    double zp=-xinv*xinv;
    set_derivatives(z,x,xinv,zp);

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable& df1_two_variable::operator = (const df1_two_variable& x)
  {
    *get_u() = *x.get_u();
    *get_u_x() = *x.get_u_x();
    *get_u_y() = *x.get_u_y();
    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable& df1_two_variable::operator = (double x)
  {
    *get_u() = x;
    *get_u_x() =0.0;
    *get_u_y() =0.0;
    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator * (const df1_two_variable& x,
    const df1_two_variable& y)
  {
    df1_two_variable z;
    double u= *x.get_u() * *y.get_u();
    *z.get_u() = u;
    double f_u=*y.get_u();
    double f_v=*x.get_u();
    set_derivatives(z,x,y,u, f_u, f_v);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator * (double x,
    const df1_two_variable& y)
  {
    df1_two_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_u_x() = x * *y.get_u_x();
    *z.get_u_y() = x * *y.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator * (const df1_two_variable& y,
    double x)
  {
    df1_two_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_u_x() = x * *y.get_u_x();
    *z.get_u_y() = x * *y.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator / (const df1_two_variable& x,
    double y)
  {
    double u=1/y;
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator / (const df1_two_variable& x,
    const df1_two_variable& y)
  {
    df1_two_variable u=inv(y);
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator / (const double x,
    const df1_two_variable& y)
  {
    df1_two_variable u=inv(y);
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator + (const double x,const df1_two_variable& y)
  {
    df1_two_variable z;
    *z.get_u() =  x + *y.get_u();
    *z.get_u_x() = *y.get_u_x();
    *z.get_u_y() = *y.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator + (const df1_two_variable& x,const double y)
  {
    df1_two_variable z;
    *z.get_u() =  *x.get_u() + y;
    *z.get_u_x() = *x.get_u_x();
    *z.get_u_y() = *x.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator + (const df1_two_variable& x,
    const df1_two_variable& y)
  {
    df1_two_variable z;
    *z.get_u() = *x.get_u() + *y.get_u();
    *z.get_u_x() = *x.get_u_x() + *y.get_u_x();
    *z.get_u_y() = *x.get_u_y()+*y.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator - (const df1_two_variable& x,
    const df1_two_variable& y)
  {
    df1_two_variable z;
    *z.get_u() = *x.get_u() - *y.get_u();
    *z.get_u_x() = *x.get_u_x()  - *y.get_u_x();
    *z.get_u_y() = *x.get_u_y() - *y.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator - (double x,
    const df1_two_variable& y)
  {
    df1_two_variable z;
    *z.get_u() = x - *y.get_u();
    *z.get_u_x() = - *y.get_u_x();
    *z.get_u_y() = - *y.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1_two_variable operator - (const df1_two_variable& x,
    double y)
  {
    df1_two_variable z;
    *z.get_u() = *x.get_u()-y;
    *z.get_u_x() = *x.get_u_x();
    *z.get_u_y() = *x.get_u_y();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  init_df1_two_variable::~init_df1_two_variable()
  {
    deallocate();
  }

/**
 * Description not yet available.
 * \param
 */
  void init_df1_two_variable::deallocate(void)
  {
    num_ind_var=0;
  }

/**
 * Description not yet available.
 * \param
 */
init_df1_two_variable::init_df1_two_variable(const prevariable& _v)
{
  if (num_ind_var > 1)
  {
    cerr << "can only have 2 independent_variables in df1_two_variable"
       " function" << endl;
    ad_exit(1);
  }
  else
  {
    ADUNCONST(prevariable,v)
    ind_var[num_ind_var++]=&v;
    *get_u() =  value(v);
    switch(num_ind_var)
    {
    case 1:
      *get_u_x() = 1.0;
      *get_u_y() = 0.0;
      break;
    case 2:
      *get_u_x() = 0.0;
      *get_u_y() = 1.0;
      break;
    default:
      cerr << "illegal num_ind_var value of " << num_ind_var
           << " in  df1_two_variable function" << endl;
      ad_exit(1);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
  init_df1_two_variable::init_df1_two_variable(double v)
  {
    *get_u() =  v;
    *get_u_x() = 0.0;
    *get_u_y() = 0.0;
  }


/**
 * Description not yet available.
 * \param
 */
df1_two_matrix choleski_decomp(const df1_two_matrix& MM)
{
  // kludge to deal with constantness
  df1_two_matrix & M= (df1_two_matrix &) MM;
  int rmin=M.indexmin();
  int cmin=M(rmin).indexmin();
  int rmax=M.indexmax();
  int cmax=M(rmin).indexmax();
  if (rmin !=1 || cmin !=1)
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df1_two_atrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df1_two_matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }

  int n=rmax-rmin+1;
  df1_two_matrix L(1,n,1,n);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df1_two_variable tmp;

    if (value(M(1,1))<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }

  L(1,1)=sqrt(M(1,1));
  for (i=2;i<=n;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    for (j=2;j<=i-1;j++)
    {
      tmp=M(i,j);
      for (k=1;k<=j-1;k++)
      {
        tmp-=L(i,k)*L(j,k);
      }
      L(i,j)=tmp/L(j,j);
    }
    tmp=M(i,i);
    for (k=1;k<=i-1;k++)
    {
      tmp-=L(i,k)*L(i,k);
    }

    if (value(tmp)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      ad_exit(1);
    }

    L(i,i)=sqrt(tmp);
  }

  return L;
}

  df1_two_variable fabs(const df1_two_variable& x)
  {
    df1_two_variable z;
    if (value(x)>=0.0)
      z=x;
    else
      z=-x;
    return z;
  }
