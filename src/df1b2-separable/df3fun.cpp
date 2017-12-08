/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <df1b2fun.h>
//#include "df3fun.h"
  df1b2variable * df3_one_variable::ind_var=0;

/**
Default constructor
*/
df3_one_variable::df3_one_variable()
{
  v[0] = 0;
  v[1] = 0;
  v[2] = 0;
  v[3] = 0;
}
/**
Copy constructor
*/
df3_one_variable::df3_one_variable(const df3_one_variable& x)
{
  v[0] = x.v[0];
  v[1] = x.v[1];
  v[2] = x.v[2];
  v[3] = x.v[3];
}
/**
Copy constructor
*/
df3_one_vector::df3_one_vector(const df3_one_vector& m2)
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
df3_one_vector::~df3_one_vector()
{
  deallocate();
}

 void df3_one_vector::deallocate(void)
 {
   if(shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df3_one_variable*) (shape->trueptr);
       delete [] v;
       v = NULL;
       delete shape;
       shape=0;
     }
   }
 }

 dvector value(const df3_one_vector& v)
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

 dvector first_derivatives(const df3_one_vector& v)
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

 dvector second_derivatives(const df3_one_vector& v)
 {
   int mmin=v.indexmin();
   int mmax=v.indexmax();
   dvector cv(mmin,mmax);
   for (int i=mmin;i<=mmax;i++)
   {
     cv(i)=*(v(i).get_udot2());
   }
   return cv;
 }

 dvector third_derivatives(const df3_one_vector& v)
 {
   int mmin=v.indexmin();
   int mmax=v.indexmax();
   dvector cv(mmin,mmax);
   for (int i=mmin;i<=mmax;i++)
   {
     cv(i)=*(v(i).get_udot3());
   }
   return cv;
 }

  void df3_one_vector::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)=0.0;
    }
  }

/**
Default constructor.
*/
df3_one_vector::df3_one_vector()
{
  allocate();
}

  df3_one_vector::df3_one_vector(int min,int max)
  {
    allocate(min,max);
  }

/**
Allocate vector of df3_one_variable with dimension
[min to max].

\param min lower index
\param max upper index
*/
void df3_one_vector::allocate(int min,int max)
{
  index_min = min;
  index_max = max;
  v = new df3_one_variable[
    static_cast<unsigned int>(max < min ? 0 : max - min + 1)];
  if (v == 0)
  {
    cerr << "error allocating memory in df3_one_vector\n";
    ad_exit(1);
  }
  if ((shape = new vector_shapex(min, max, v)) == NULL)
  {
    cerr << "Error trying to allocate memory for df3_one_vector\n";
    ad_exit(1);
  }
  v -= min;
}
/**
Does NOT allocate, but initializes empty df3_one_vector.
*/
void df3_one_vector::allocate(void)
{
  index_min = 0;
  index_max = -1;
  v = 0;
  shape = 0;
}

 dmatrix value(const df3_one_matrix& v)
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

 dmatrix first_derivatives(const df3_one_matrix& v)
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

 dmatrix second_derivatives(const df3_one_matrix& v)
 {
   int rmin=v.indexmin();
   int rmax=v.indexmax();
   dmatrix cm(rmin,rmax);
   for (int i=rmin;i<=rmax;i++)
   {
     int cmin=v(i).indexmin();
     int cmax=v(i).indexmax();
     cm(i).allocate(cmin,cmax);
     cm(i)=second_derivatives(v(i));
   }
   return cm;
 }

 dmatrix third_derivatives(const df3_one_matrix& v)
 {
   int rmin=v.indexmin();
   int rmax=v.indexmax();
   dmatrix cm(rmin,rmax);
   for (int i=rmin;i<=rmax;i++)
   {
     int cmin=v(i).indexmin();
     int cmax=v(i).indexmax();
     cm(i).allocate(cmin,cmax);
     cm(i)=third_derivatives(v(i));
   }
   return cm;
 }


 df3_one_matrix::df3_one_matrix(const df3_one_matrix& m2)
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

 df3_one_matrix::~df3_one_matrix()
 {
   deallocate();
 }

 void df3_one_matrix::deallocate(void)
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df3_one_vector*) (shape->get_pointer());
       delete [] v;
       v=0;
       delete shape;
       shape=0;
     }
   }
 }


  void df3_one_matrix::initialize(void)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).initialize();
    }
  }


/*
Construct matrix of df3_one_variable with dimension
[min to max] x [cmin to cmax].

\param rmin lower row index
\param rmax upper row index
\param cmin lower column index
\param cmax upper column index
*/
df3_one_matrix::df3_one_matrix(int rmin, int rmax, int cmin,int cmax)
{
  index_min = rmin;
  index_max = rmax;
  v = new df3_one_vector[
    static_cast<unsigned int>(rmax < rmin ? 0 : rmax - rmin + 1)];
  if (v == 0)
  {
    cerr << "error allocating memory in df3_one_matrix" << endl;
    ad_exit(1);
  }
  if ((shape = new mat_shapex(v)) == NULL)
  {
    cerr << "Error trying to allocate memory for df3_one_vector\n";
    ad_exit(1);
  }
  v-=rmin;
  for (int i = rmin; i<= rmax; ++i)
  {
    v[i].allocate(cmin, cmax);
  }
}

/*
  df3_one_variable operator F(const df3_one_variable& x)
  {
    df3_one_variable z;

    *z.get_u() = ::F(*x.get_u());

    *z.get_udot() = ::D1F(*x.get_u())* *x.get_udot();

    *z.get_udot2() = ::D2F(*x.get_u())* square(*x.get_udot())
                   + ::D1F(*x.get_u())* *x.get_udot2();

    *z.get_udot3() = ::D3F(*x.get_u()) * cube(*x.get_udot())
                   + 3.0 * ::D2F(*x.get_u()) * *x.get_udot() * *x.get_udot2()
                   + ::D1F(*x.get_u()) * *x.get_udot3();
    return z;
  }

*/

/**
Subtract d from the value at u.
*/
df3_one_variable& df3_one_variable::operator-=(double d)
{
  *get_u() -= d;
  return *this;
}
/**
Subtract _v values from df3_one_variable u, udot, udot2 and udot3.
*/
df3_one_variable& df3_one_variable::operator-=(const df3_one_variable& _v)
{
  *get_u() -= *_v.get_u();
  *get_udot() -= *_v.get_udot();
  *get_udot2() -= *_v.get_udot2();
  *get_udot3() -= *_v.get_udot3();
  return *this;
}

df3_one_variable operator-(const df3_one_variable& v)
{
  df3_one_variable z;
  *z.get_u() = -(*v.get_u());

  *z.get_udot() = -(*v.get_udot());
  *z.get_udot2() = -(*v.get_udot2());
  *z.get_udot3() = -(*v.get_udot3());
  return z;
}
/**
Subtract v values from df3_one_variable u, udot, udot2 and udot3.
*/
df3_one_variable& df3_one_variable::operator+=(const df3_one_variable& _v)
{
  *get_u() += *_v.get_u();
  *get_udot() += *_v.get_udot();
  *get_udot2() += *_v.get_udot2();
  *get_udot3() += *_v.get_udot3();
  return *this;
}

  df3_one_variable sqrt(const df3_one_variable& x)
  {
    df3_one_variable z;
    double u=::sqrt(*x.get_u());
    double xinv=1.0/(*x.get_u());
    double zp=0.5/u;
    double zp2=-0.5*zp*xinv;
    double zp3=-1.5*zp2*xinv;

    *z.get_u() = u;

    *z.get_udot() = zp* *x.get_udot();

    *z.get_udot2() = zp2 * square(*x.get_udot())
                   + zp * *x.get_udot2();

    *z.get_udot3() = zp3 * cube(*x.get_udot())
                   + 3.0 * zp2 * *x.get_udot() * *x.get_udot2()
                   + zp * *x.get_udot3();

    return z;
  }



  df3_one_variable exp(const df3_one_variable& x)
  {
    df3_one_variable z;

    *z.get_u() = ::exp(*x.get_u());

    *z.get_udot() = ::exp(*x.get_u())* *x.get_udot();

    *z.get_udot2() = ::exp(*x.get_u())* square(*x.get_udot())
                   + ::exp(*x.get_u())* *x.get_udot2();

    *z.get_udot3() = ::exp(*x.get_u()) * cube(*x.get_udot())
                   + 3.0 * ::exp(*x.get_u()) * *x.get_udot() * *x.get_udot2()
                   + ::exp(*x.get_u()) * *x.get_udot3();
    return z;
  }

  df3_one_variable log(const df3_one_variable& x)
  {
    df3_one_variable z;

    double xp=1.0/(*x.get_u());
    double xp2=-square(xp);
    double xp3=-2.0*xp*xp2;

    *z.get_u() = ::log(*x.get_u());

    *z.get_udot() = xp * *x.get_udot();

    *z.get_udot2() = xp2* square(*x.get_udot())
                   + xp * *x.get_udot2();

    *z.get_udot3() = xp3 * cube(*x.get_udot())
                   + 3.0 * xp2 * *x.get_udot() * *x.get_udot2()
                   + xp * *x.get_udot3();
    return z;
  }

  df3_one_variable inv(const df3_one_variable& x)
  {
    df3_one_variable z;
    double xinv=1.0/(*x.get_u());
    double zp=-xinv*xinv;
    double zp2=-2.0*zp*xinv;
    double zp3=-3.0*zp2*xinv;

    *z.get_u() = xinv;
    *z.get_udot() = zp * *x.get_udot();

    *z.get_udot2() = zp2 * square(*x.get_udot())
                   + zp * *x.get_udot2();

    *z.get_udot3() = zp3 * cube(*x.get_udot())
                   + 3.0 * zp2 * *x.get_udot() * *x.get_udot2()
                   + zp * *x.get_udot3();

    return z;
  }

  df3_one_variable& df3_one_variable::operator = (const df3_one_variable& x)
  {
    *get_u() = *x.get_u();
    *get_udot() = *x.get_udot();
    *get_udot2() = *x.get_udot2();
    *get_udot3() = *x.get_udot3();
    return *this;
  }

  df3_one_variable& df3_one_variable::operator = (double x)
  {
    *get_u() = x;
    *get_udot() = 0.0;
    *get_udot2() = 0.0;
    *get_udot3() = 0.0;
    return *this;
  }


  df3_one_variable operator * (const df3_one_variable& x,
    const df3_one_variable& y)
  {
    df3_one_variable z;
    *z.get_u() = *x.get_u() *  *y.get_u();
    *z.get_udot() = *x.get_u() * *y.get_udot()
                 + *x.get_udot() * *y.get_u();

    *z.get_udot2() = *x.get_udot2() * *y.get_u()
                   + 2.0 * *x.get_udot() * *y.get_udot()
                   +  *x.get_u() * *y.get_udot2();

    *z.get_udot3() = *x.get_udot3() * *y.get_u()
                   + 3.0 * *x.get_udot2() * *y.get_udot()
                   + 3.0 * *x.get_udot() * *y.get_udot2()
                   +  *x.get_u() * *y.get_udot3();
    return z;
  }

  df3_one_variable operator * (double x,
    const df3_one_variable& y)
  {
    df3_one_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_udot() = x * *y.get_udot();

    *z.get_udot2() = x * *y.get_udot2();

    *z.get_udot3() = x * *y.get_udot3();
    return z;
  }

  df3_one_variable operator * (const df3_one_variable& x,
    double y)
  {
    df3_one_variable z;
    *z.get_u() = *x.get_u() *  y;
    *z.get_udot() =  *x.get_udot() * y;

    *z.get_udot2() = *x.get_udot2() * y;

    *z.get_udot3() = *x.get_udot3() * y;
    return z;
  }


  df3_one_variable operator / (const df3_one_variable& x,
    const df3_one_variable& y)
  {
    df3_one_variable u=inv(y);
    return x*u;
  }

  df3_one_variable operator / (double x,
    const df3_one_variable& y)
  {
    df3_one_variable u=inv(y);
    return x*u;
  }

  df3_one_variable operator + (double x,const df3_one_variable& y)
  {
    df3_one_variable z;
    *z.get_u() =  x + *y.get_u();
    *z.get_udot() =  *y.get_udot();
    *z.get_udot2() = *y.get_udot2();
    *z.get_udot3() = *y.get_udot3();
    return z;
  }

 //
 //   df3_one_variable operator / (const df3_one_variable& x,
 //     const df3_one_variable& y)
 //   {
 //     df3_one_variable z;
 //     double yinv =  1.0 / (*y.get_u());
 //     double yinv2 = yinv * yinv;
 //     double yinv3 = yinv * yinv2;
 //     doubl yd = *y.get_udot();
 //
 //     //*z.get_u() = *x.get_u() /  *y.get_u();
 //     *z.get_u() = *x.get_u() * yinv;
 //
 //     *z.get_udot() =  - (*x.get_u()) * yinv2 * yd
 //                   + *x.get_udot() * yinv;
 //
 //     *z.get_udot2() = *x.get_udot2() * yinv
 //                    - 2.0 * *x.get_udot() * yd * yinv2
 //                    + 2.0 * *x.get_u() * yinv3  * yd *yd
 //                    -  *x.get_u() * yinv2 * y.get_udot2();
 //
 //     *z.get_udot3() = *x.get_udot3() * yinv
 //                    + 3.0 * *x.get_udot2() * *y.get_udot()
 //                    + 3.0 * *x.get_udot() * *y.get_udot2()
 //                    +  *x.get_u() * *y.get_udot3();
 //   }
 //


  df3_one_variable operator + (const df3_one_variable& y,
    const double x)
  {
    df3_one_variable z;
    *z.get_u() =   x + *y.get_u();
    *z.get_udot() =  *y.get_udot();
    *z.get_udot2() = *y.get_udot2();
    *z.get_udot3() = *y.get_udot3();
    return z;
  }

  df3_one_variable operator + (const df3_one_variable& x,
    const df3_one_variable& y)
  {
    df3_one_variable z;
    *z.get_u() = *x.get_u() + *y.get_u();
    *z.get_udot() = *x.get_udot() + *y.get_udot();
    *z.get_udot2() = *x.get_udot2() + *y.get_udot2();
    *z.get_udot3() = *x.get_udot3() + *y.get_udot3();
    return z;
  }

  df3_one_variable operator - (const df3_one_variable& x,
    const df3_one_variable& y)
  {
    df3_one_variable z;
    *z.get_u() = *x.get_u() - *y.get_u();
    *z.get_udot() = *x.get_udot() - *y.get_udot();
    *z.get_udot2() = *x.get_udot2() - *y.get_udot2();
    *z.get_udot3() = *x.get_udot3() - *y.get_udot3();
    return z;
  }

  df3_one_variable operator - (const df3_one_variable& x,
    double y)
  {
    df3_one_variable z;
    *z.get_u() = *x.get_u() - y;
    *z.get_udot() = *x.get_udot();
    *z.get_udot2() = *x.get_udot2();
    *z.get_udot3() = *x.get_udot3();
    return z;
  }

/**
Construct init_df3_one_variable from _var.
\param _var value for u.
*/
init_df3_one_variable::init_df3_one_variable(const df1b2variable& _var)
{
  ADUNCONST(df1b2variable,var)
/*
    if (num_ind_var>0)
    {
      cerr << "can only have 1 independent_variables in df3_one_variable"
       " function" << endl;
      ad_exit(1);
   }
*/
  ind_var = &var;
  *get_u() =  *var.get_u();
  *get_udot() = 1.0;
  *get_udot2() = 0.0;
  *get_udot3() = 0.0;
}
/**
Constructs init_df3_one_variable setting member u with value _u.
\param _u value for u
*/
init_df3_one_variable::init_df3_one_variable(double _u)
{
  *get_u() = _u;
  *get_udot() = 1.0;
  *get_udot2() = 0.0;
  *get_udot3() = 0.0;
}

df3_one_matrix choleski_decomp(const df3_one_matrix& MM)
{
  // kludge to deal with constantness
  df3_one_matrix & M= (df3_one_matrix &) MM;
  int rmin=M.indexmin();
  int cmin=M(rmin).indexmin();
  int rmax=M.indexmax();
  int cmax=M(rmin).indexmax();
  if (rmin !=1 || cmin !=1)
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df3_one_atrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df3_one_matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }

  int n=rmax-rmin+1;
  df3_one_matrix L(1,n,1,n);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df3_one_variable tmp;

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

df1b2matrix& df1b2matrix::operator = (const df3_one_matrix& M)
{
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != indexmin() || rmax != indexmax())
  {
    cerr << "unequal shape in "
     "df1b2matrix& df1b2matrix::operator = (const df3_one_matrix& M)"
      << endl;
    ad_exit(1);
  }

  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}

df1b2vector& df1b2vector::operator = (const df3_one_vector& M)
{
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != indexmin() || rmax != indexmax())
  {
    cerr << "unequal shape in "
     "df1b2vector& df1b2vector::operator = (const df3_one_vector& M)"
      << endl;
    ad_exit(1);
  }

  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}

df1b2variable& df1b2variable::operator = (const df3_one_variable& v)
{
  df1b2variable * px=df3_one_variable::ind_var;
  //df3_one_variable::ind_var=0;
  //df1b2variable * px=0;
  double  df= *v.get_udot();
  double * xd=px->get_u_dot();
  double * zd=get_u_dot();
  *get_u()=*v.get_u();
  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = df * *xd++;
  }

 /*
  cout << *v.get_u()  << " ";
  cout << *v.get_udot()  << " ";
  cout << *v.get_udot2()  << " ";
  cout << *v.get_udot3()  << endl;
  */
  f1b2gradlist->write_pass1(px,this,*v.get_udot(),*v.get_udot2(),

    *v.get_udot3());
  return *this;
}


df1b2variable cumd_norm(const df1b2variable& _x)
{
  df1b2variable z;
  init_df3_one_variable x(_x);

  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double p=.2316419;

  if (value(x)>=0)
  {
    df3_one_variable u1=p*x;
    df3_one_variable u2=1.+u1;
    df3_one_variable u=1./u2;
    df3_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df3_one_variable tmp1=-0.3989422804*exp(-.5*x*x);
    z=1.0+tmp1*y;
  }
  else
  {
    df3_one_variable w=-x;
    df3_one_variable u=1./(1+p*w);
    df3_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df3_one_variable tmp1=0.3989422804*exp(-.5*x*x);
    z=tmp1*y;
  }
  return z;
}

df1b2variable bounded_cumd_norm(const df1b2variable& _x, double beta)
{
  df1b2variable z;
  init_df3_one_variable x(_x);

  const double b1=0.319381530;
  const double b2=-0.356563782;
  const double b3=1.781477937;
  const double b4=-1.821255978;
  const double b5=1.330274429;
  const double p=.2316419;

  if (value(x)>=0)
  {
    df3_one_variable u1=p*x;
    df3_one_variable u2=1.+u1;
    df3_one_variable u=1./u2;
    df3_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df3_one_variable tmp1=-0.3989422804*exp(-.5*x*x);
    z=1.0+tmp1*y;
  }
  else
  {
    df3_one_variable w=-x;
    df3_one_variable u=1./(1+p*w);
    df3_one_variable y=  ((((b5*u+b4)*u+b3)*u+b2)*u+b1)*u;
    df3_one_variable tmp1=0.3989422804*exp(-.5*x*x);
    z=tmp1*y;
  }
  z=beta*(z-0.5)+0.5;
  return z;
}


