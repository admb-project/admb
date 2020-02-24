/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

char df12fun_notice[50]="copyright (c) 2006 otter research ltd";

#include "df11fun.h"

prevariable* df1_one_variable::ind_var[1] = { NULL };
int df1_one_variable::num_ind_var = 0;

/**
Default constructor
*/
df1_one_variable::df1_one_variable()
{
  v[0] = 0;
  v[1] = 0;
}
/**
Copy constructor
*/
df1_one_variable::df1_one_variable(const df1_one_variable& x)
{
  v[0] = x.v[0];
  v[1] = x.v[1];
}
/**
Copy constructor
*/
df1_one_vector::df1_one_vector(const df1_one_vector& m2)
{
  index_min = m2.index_min;
  index_max = m2.index_max;
  shape = m2.shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
  v = m2.v;
}
/**
Destructor
*/
df1_one_vector::~df1_one_vector()
{
  deallocate();
}

 void df1_one_vector::deallocate(void)
 {
   if(shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df1_one_variable*) (shape->trueptr);
       delete [] v;
       v = NULL;
       delete shape;
       shape=0;
     }
   }
 }

 dvector value(const df1_one_vector& v)
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

  void df1_one_vector::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)=0.0;
    }
  }

/**
Default constructor
*/
df1_one_vector::df1_one_vector()
{
  allocate();
}

  df1_one_vector::df1_one_vector(int min,int max)
  {
    allocate(min,max);
  }

/**
Allocate vector of df1_one_variable with dimension
[min to max].

\param min lower vector index
\param max upper vector index
*/
void df1_one_vector::allocate(int min, int max)
{
  index_min = min;
  index_max = max;
  v = new df1_one_variable[
    static_cast<unsigned int>(max < min ? 0 : max - min + 1)];
  if (v == 0)
  {
    cerr << "error allocating memory in df1_one_vector" << endl;
    ad_exit(1);
  }
  if ((shape = new vector_shapex(min, max, v)) == NULL)
  {
    cerr << "Error trying to allocate memory for df1_one_vector\n";
    ad_exit(1);
  }
  v -= min;
}

  void df1_one_vector::allocate(void)
  {
    index_min=0;
    index_max=-1;
    v=0;
    shape=0;
  }

 dmatrix value(const df1_one_matrix& v)
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

 df1_one_matrix::df1_one_matrix(const df1_one_matrix& m2)
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

 df1_one_matrix::~df1_one_matrix()
 {
   deallocate();
 }

 void df1_one_matrix::deallocate(void)
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df1_one_vector*) (shape->get_pointer());
       delete [] v;
       v=0;
       delete shape;
       shape=0;
     }
   }
 }


  void df1_one_matrix::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).initialize();
    }
  }


/**
Construct matrix of df1_one_variable with dimensions
[rmin to rmax] x [cmin to cmax].

\param rmin lower row index
\param rmax upper row index
\param cmin lower column index
\param cmax upper column index
*/
df1_one_matrix::df1_one_matrix(int rmin, int rmax, int cmin, int cmax)
{
  index_min = rmin;
  index_max = rmax;
  v = new df1_one_vector[
    static_cast<unsigned int>(rmax < rmin ? 0 : rmax - rmin + 1)];
  if (v == 0)
  {
      cerr << "error allocating memory in df1_one_matrix" << endl;
      ad_exit(1);
  }
  if ((shape = new mat_shapex(v)) == NULL)
  {
    cerr << "Error trying to allocate memory for df1_one_vector\n";
    ad_exit(1);
  }
  v -= rmin;
  for (int i = rmin; i <= rmax; ++i)
  {
    v[i].allocate(cmin, cmax);
  }
}

df1_one_variable& df1_one_variable::operator-=(const df1_one_variable& _v)
{
  *get_u() -= *_v.get_u();
  *get_u_x() -= *_v.get_u_x();

  return *this;
}
df1_one_variable operator-(const df1_one_variable& v)
{
  df1_one_variable z;

  *z.get_u() = -(*v.get_u());
  *z.get_u_x() = -(*v.get_u_x());

  return z;
}
df1_one_variable& df1_one_variable::operator+=(const df1_one_variable& _v)
{
  *get_u() += *_v.get_u();
  *get_u_x() += *_v.get_u_x();

  return *this;
}
df1_one_variable& df1_one_variable::operator*=(const df1_one_variable& _v)
{
  df1_one_variable x = *this * _v;
  *this = x;

  return *this;
}
df1_one_variable& df1_one_variable::operator+=(double _v)
{
  *get_u() += _v;

  return *this;
}
df1_one_variable& df1_one_variable::operator-=(double _v)
{
  *get_u() -= _v;

  return *this;
}

void set_derivatives( df1_one_variable& z,const df1_one_variable& x,double u,
  double zp)
{
    //*z.get_u() = u;
    *z.get_u_x() = zp* *x.get_u_x();
}

void set_derivatives( df1_one_variable& z, const df1_one_variable& x,
  const df1_one_variable& y, double u,
  double f_u,double f_v)
{
    *z.get_u() = u;

    *z.get_u_x() = f_u* *x.get_u_x()
                 + f_v* *y.get_u_x();
}

  df1_one_variable sqrt(const df1_one_variable& x)
  {
    df1_one_variable z;
    double u=::sqrt(*x.get_u());
    *z.get_u()=u;
    //double xinv=1.0/(*x.get_u());
    double zp=0.5/u;

    set_derivatives(z,x,u,zp);

    return z;
  }



  df1_one_variable atan(const df1_one_variable& x)
  {
    df1_one_variable z;
    double cx=value(x);
    double d=1.0/(1+square(cx));
    //double d2=square(d);
    double u=::atan(cx);
    *z.get_u()=u;
    double zp=d;

    set_derivatives(z,x,u,zp);
    return z;
  }

  df1_one_variable square(const df1_one_variable& x)
  {
    df1_one_variable z;
    double u=value(x);
    *z.get_u()=u*u;
    double zp=2.0*u;

    set_derivatives(z,x,u,zp);
    return z;
  }

  df1_one_variable tan(const df1_one_variable& x)
  {
    df1_one_variable z;
    double u=::tan(*x.get_u());
    *z.get_u()=u;
    double v=1.0/::cos(*x.get_u());
    //double w=::sin(*x.get_u());
    double v2=v*v;
    double zp=v2;

    set_derivatives(z,x,u,zp);
    return z;
  }

  df1_one_variable sin(const df1_one_variable& x)
  {
    df1_one_variable z;
    double u=::sin(*x.get_u());
    *z.get_u()=u;
    double zp=::cos(*x.get_u());

    set_derivatives(z,x,u,zp);
    return z;
  }

  df1_one_variable log(const df1_one_variable& x)
  {
    df1_one_variable z;
    double u=::log(*x.get_u());
    *z.get_u()=u;
    double zp=1/(*x.get_u());

    set_derivatives(z,x,u,zp);
    return z;
  }

  df1_one_variable exp(const df1_one_variable& x)
  {
    df1_one_variable z;
    double u=::exp(*x.get_u());
    *z.get_u()=u;
    double zp=u;

    set_derivatives(z,x,u,zp);
    return z;
  }

  df1_one_variable inv(const df1_one_variable& x)
  {
    df1_one_variable z;
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
 dvector first_derivatives(const df1_one_vector& v)
 {
   int mmin=v.indexmin();
   int mmax=v.indexmax();
   dvector cv(mmin,mmax);
   for (int i=mmin;i<=mmax;i++)
   {
     cv(i)=*(v(i).get_udot());
   }
   return cv;
 }

/**
 * Description not yet available.
 * \param
 */
 dmatrix first_derivatives(const df1_one_matrix& v)
 {
   int rmin=v.indexmin();
   int rmax=v.indexmax();
   dmatrix cm(rmin,rmax);
   for (int i=rmin;i<=rmax;i++)
   {
     int cmin=v(i).indexmin();
     int cmax=v(i).indexmax();
     cm(i).allocate(cmin,cmax);
     cm(i)=first_derivatives(v(i));
   }
   return cm;
 }

  df1_one_variable& df1_one_variable::operator = (const df1_one_variable& x)
  {
    *get_u() = *x.get_u();
    *get_u_x() = *x.get_u_x();
    return *this;
  }

  df1_one_variable& df1_one_variable::operator = (double x)
  {
    *get_u() = x;
    *get_u_x() =0.0;
    return *this;
  }


df1_one_variable operator*(
  const df1_one_variable& x,
  const df1_one_variable& y)
{
  df1_one_variable z;
  double u= *x.get_u() * *y.get_u();
  *z.get_u() = u;
  double f_u=*y.get_u();
  double f_v=*x.get_u();
  set_derivatives(z,x,y,u, f_u, f_v);
  return z;
}

  df1_one_variable operator * (double x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_u_x() = x * *y.get_u_x();
    return z;
  }


  df1_one_variable operator * (const df1_one_variable& y,
    double x)
  {
    df1_one_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_u_x() = x * *y.get_u_x();
    return z;
  }



  df1_one_variable operator / (const df1_one_variable& x,
    double y)
  {
    double u=1/y;
    return x*u;
  }

  df1_one_variable operator / (const df1_one_variable& x,
    const df1_one_variable& y)
  {
    df1_one_variable u=inv(y);
    return x*u;
  }

  df1_one_variable operator / (const double x,
    const df1_one_variable& y)
  {
    df1_one_variable u=inv(y);
    return x*u;
  }


  df1_one_variable operator + (const double x,const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() =  x + *y.get_u();
    *z.get_u_x() = *y.get_u_x();
    return z;
  }

  df1_one_variable operator + (const df1_one_variable& x,const double y)
  {
    df1_one_variable z;
    *z.get_u() =  *x.get_u() + y;
    *z.get_u_x() = *x.get_u_x();
    return z;
  }



  df1_one_variable operator + (const df1_one_variable& x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = *x.get_u() + *y.get_u();
    *z.get_u_x() = *x.get_u_x() + *y.get_u_x();
    return z;
  }

  df1_one_variable operator - (const df1_one_variable& x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = *x.get_u() - *y.get_u();
    *z.get_u_x() = *x.get_u_x()  - *y.get_u_x();
    return z;
  }

  df1_one_variable operator - (double x,
    const df1_one_variable& y)
  {
    df1_one_variable z;
    *z.get_u() = x - *y.get_u();
    *z.get_u_x() = - *y.get_u_x();
    return z;
  }

  df1_one_variable operator - (const df1_one_variable& x,
    double y)
  {
    df1_one_variable z;
    *z.get_u() = *x.get_u()-y;
    *z.get_u_x() = *x.get_u_x();
    return z;
  }

/**
Destructor
*/
init_df1_one_variable::~init_df1_one_variable()
{
  deallocate();
}
/**
Resets num_ind_var count to zero.
*/
void init_df1_one_variable::deallocate(void)
{
  num_ind_var=0;
}

/**
Construct init_df1_one_variable with _var.

\param _var sets u.
*/
init_df1_one_variable::init_df1_one_variable(const prevariable& _var)
{
  if (num_ind_var != 0)
  {
    cerr << "can only have 1 independent_variables in df1_one_variable"
       " function" << endl;
    ad_exit(1);
  }

  ADUNCONST(prevariable,var)
  num_ind_var = 1;
  ind_var[0] = &var;
  *get_u() = value(var);
  switch(num_ind_var)
  {
  case 1:
    *get_u_x() = 1.0;
    break;
  default:
    cerr << "illegal num_ind_var value of " << num_ind_var
         << " in  df1_one_variable function" << endl;
    ad_exit(1);
  }
}

  init_df1_one_variable::init_df1_one_variable(double v)
  {
    *get_u() =  v;
    *get_u_x() = 0.0;
  }

df1_one_matrix choleski_decomp(const df1_one_matrix& MM)
{
  // kludge to deal with constantness
  df1_one_matrix & M= (df1_one_matrix &) MM;
  int rmin=M.indexmin();
  int cmin=M(rmin).indexmin();
  int rmax=M.indexmax();
  int cmax=M(rmin).indexmax();
  if (rmin !=1 || cmin !=1)
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df1_one_atrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df1_one_matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }

  int n=rmax-rmin+1;
  df1_one_matrix L(1,n,1,n);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df1_one_variable tmp;

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
