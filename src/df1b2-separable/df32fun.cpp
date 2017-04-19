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
#include <df1b2fun.h>
df1b2variable* df3_two_variable::ind_var[2];
int df3_two_variable::num_ind_var = 0;

/**
Copy constructor
*/
df3_two_variable::df3_two_variable(const df3_two_variable& x)
{
  v[0] = x.v[0];
  v[1] = x.v[1];
  v[2] = x.v[2];
  v[3] = x.v[3];
  v[4] = x.v[4];
  v[5] = x.v[5];
  v[6] = x.v[6];
  v[7] = x.v[7];
  v[8] = x.v[8];
  v[9] = x.v[9];
}

/**
 * Description not yet available.
 * \param
 */
 df3_two_vector::df3_two_vector(const df3_two_vector& m2)
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
Destructor
*/
df3_two_vector::~df3_two_vector()
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
 void df3_two_vector::deallocate(void)
 {
   if(shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df3_two_variable*) (shape->trueptr);
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
 dvector value(const df3_two_vector& v)
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
Initialize df3_two_vector to zero.
*/
void df3_two_vector::initialize()
{
  int mmin = indexmin();
  int mmax = indexmax();
  for (int i = mmin; i <= mmax; ++i)
  {
    (*this)(i) = 0.0;
  }
}
/**
Default constructor
*/
df3_two_vector::df3_two_vector()
{
  allocate();
}

/**
 * Description not yet available.
 * \param
 */
  df3_two_vector::df3_two_vector(int min,int max)
  {
    allocate(min,max);
  }

/**
Allocate vector of df3_two_variable with dimension
[min to max].

\param min lower index
\param max upper index
*/
void df3_two_vector::allocate(int min, int max)
{
  index_min = min;
  index_max = max;
  v = new df3_two_variable[
    static_cast<unsigned int>(max < min ? 0 : max - min + 1)];
  if (v == 0)
  {
    cerr << "error allocating memory in df3_two_vector\n";
    ad_exit(1);
  }
  if ((shape = new vector_shapex(min, max, v)) == NULL)
  {
    cerr << "Error trying to allocate memory for df3_two_vector\n";
    ad_exit(1);
  }
  v -= min;
}
/**
Does NOT allocate, but initializes empty df3_two_vector.
*/
void df3_two_vector::allocate()
{
  index_min = 0;
  index_max = -1;
  v = 0;
  shape = 0;
}

/**
 * Description not yet available.
 * \param
 */
 dmatrix value(const df3_two_matrix& v)
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
 df3_two_matrix::df3_two_matrix(const df3_two_matrix& m2)
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
 df3_two_matrix::~df3_two_matrix()
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 void df3_two_matrix::deallocate(void)
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df3_two_vector*) (shape->get_pointer());
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
  void df3_two_matrix::initialize(void)
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
  df3_two_matrix::df3_two_matrix(int rmin,int rmax,int cmin,int cmax)
  {
    index_min=rmin;
    index_max=rmax;
    v=new df3_two_vector[rmax-rmin+1];
    if (v==0)
    {
      cerr << "error allocating memory in df3_two_matrix" << endl;
      ad_exit(1);
    }
    if ( (shape=new mat_shapex(v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df3_two_vector"
           << endl;;
    }
    v-=rmin;

    for (int i=rmin;i<=rmax;i++)
    {
      v[i].allocate(cmin,cmax);
    }
  }
/**
Subtract values in _v from df3_two_variable.
*/
df3_two_variable& df3_two_variable::operator-=(const df3_two_variable& _v)
{
  *get_u() -= *_v.get_u();
  *get_u_x() -= *_v.get_u_x();
  *get_u_y() -= *_v.get_u_y();
  *get_u_xx() -= *_v.get_u_xx();
  *get_u_xy() -= *_v.get_u_xy();
  *get_u_yy() -= *_v.get_u_yy();
  *get_u_xxx() -= *_v.get_u_xxx();
  *get_u_xxy() -= *_v.get_u_xxy();
  *get_u_xyy() -= *_v.get_u_xyy();
  *get_u_yyy() -= *_v.get_u_yyy();
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df3_two_variable operator-(const df3_two_variable& v)
{
  df3_two_variable z;

  *z.get_u() = - *v.get_u();

  *z.get_u_x() = -(*v.get_u_x());
  *z.get_u_y() = -(*v.get_u_y());
  *z.get_u_xx() = -(*v.get_u_xx());
  *z.get_u_xy() = -(*v.get_u_xy());
  *z.get_u_yy() = -(*v.get_u_yy());
  *z.get_u_xxx() = -(*v.get_u_xxx());
  *z.get_u_xxy() = -(*v.get_u_xxy());
  *z.get_u_xyy() = -(*v.get_u_xyy());
  *z.get_u_yyy() = -(*v.get_u_yyy());

  return z;
}
/**
Add values from _v to df3_two_variable.
*/
df3_two_variable& df3_two_variable::operator+=(const df3_two_variable& _v)
{
  *get_u() += *_v.get_u();
  *get_u_x() += *_v.get_u_x();
  *get_u_y() += *_v.get_u_y();
  *get_u_xx() += *_v.get_u_xx();
  *get_u_xy() += *_v.get_u_xy();
  *get_u_yy() += *_v.get_u_yy();
  *get_u_xxx() += *_v.get_u_xxx();
  *get_u_xxy() += *_v.get_u_xxy();
  *get_u_xyy() += *_v.get_u_xyy();
  *get_u_yyy() += *_v.get_u_yyy();

  return *this;
}
/**
Add value _v to only df3_two_variable u with the rest of the values unchanged.
*/
df3_two_variable& df3_two_variable::operator+=(double _v)
{
  *get_u() += _v;

  return *this;
}
/**
Subtract value _v from only df3_two_variable u with the rest of the values unchanged.
*/
df3_two_variable& df3_two_variable::operator-=(double _v)
{
  *get_u() -= _v;
  return *this;
}
/**
Multiply df3_two_variable and v which calls set_derivatives. 
*/
df3_two_variable& df3_two_variable::operator*=(const df3_two_variable& _v)
{
  df3_two_variable x = *this * _v;
  *this = x;
  return *this;
}
/**
Multiply value _v to value in df3_two_variable.
*/
df3_two_variable& df3_two_variable::operator*=(double _v)
{
  *get_u() *= _v;
  *get_u_x() *= _v;
  *get_u_y() *= _v;
  *get_u_xx() *= _v;
  *get_u_xy() *= _v;
  *get_u_yy() *= _v;
  *get_u_xxx() *= _v;
  *get_u_xxy() *= _v;
  *get_u_xyy() *= _v;
  *get_u_yyy() *= _v;

  return *this;
}

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable& df3_two_variable::operator /= (const df3_two_variable& y)
  {
    df3_two_variable x=*this / y;
    *this=x;
    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
int operator <(const df3_two_variable & x, double n)
{
   return value(x) < n;
}

/**
 * Description not yet available.
 * \param
 */
int operator >(const df3_two_variable & x, double n)
{
   return value(x) > n;
}

/**
 * Description not yet available.
 * \param
 */
int operator >=(const df3_two_variable & x, double n)
{
   return value(x) >= n;
}

/**
 * Description not yet available.
 * \param
 */
int operator ==(const df3_two_variable & x, const df3_two_variable & n)
{
   return value(x) == value(n);
}

/**
 * Description not yet available.
 * \param
 */
int operator ==(const df3_two_variable & x, double n)
{
   return value(x) == n;
}

/**
 * Description not yet available.
 * \param
 */
int operator ==(double x, const df3_two_variable & n)
{
   return x == value(n);
}

/**
 * Description not yet available.
 * \param
 */
int operator <(const df3_two_variable & x, const df3_two_variable & n)
{
   return value(x) < value(n);
}

/**
 * Description not yet available.
 * \param
 */
int operator >(const df3_two_variable & x, const df3_two_variable & n)
{
   return value(x) > value(n);
}

/**
 * Description not yet available.
 * \param
 */
void set_derivatives( df3_two_variable& z,const df3_two_variable& x,double u,
  double zp,double zp2,double zp3)
{
    //*z.get_u() = u;

    *z.get_u_x() = zp* *x.get_u_x();

    *z.get_u_y() = zp* *x.get_u_y();

    *z.get_u_xx() = zp2 * square(*x.get_u_x())
                   + zp * *x.get_u_xx();

    *z.get_u_xy() = zp2 * *x.get_u_x() * *x.get_u_y()
                   + zp * *x.get_u_xy();

    *z.get_u_yy() = zp2 * square(*x.get_u_y())
                   + zp * *x.get_u_yy();

    *z.get_u_xxx() = zp3 * cube(*x.get_u_x())
                   + 3.0 * zp2 * *x.get_u_x() * *x.get_u_xx()
                   + zp * *x.get_u_xxx();

    *z.get_u_xxy() = zp3 * square(*x.get_u_x())* *x.get_u_y()
                   + 2.0* zp2 * *x.get_u_x() * *x.get_u_xy()
                   + zp2 * *x.get_u_y() * *x.get_u_xx()
                   + zp * *x.get_u_xxy();

    *z.get_u_xyy() = zp3 * square(*x.get_u_y())* *x.get_u_x()
                   + 2.0* zp2 * *x.get_u_y() * *x.get_u_xy()
                   + zp2 * *x.get_u_x() * *x.get_u_yy()
                   + zp * *x.get_u_xyy();


    *z.get_u_yyy() = zp3 * cube(*x.get_u_y())
                   + 3.0 * zp2 * *x.get_u_y() * *x.get_u_yy()
                   + zp * *x.get_u_yyy();
}

/**
 * Description not yet available.
 * \param
 */
void set_derivatives( df3_two_variable& z, const df3_two_variable& x,
  const df3_two_variable& y, double u,
  double f_u,double f_v,double f_uu,double f_uv,double f_vv,double f_uuu,
  double f_uuv,double f_uvv,double f_vvv)
{
    *z.get_u() = u;

    *z.get_u_x() = f_u* *x.get_u_x()
                 + f_v* *y.get_u_x();

    *z.get_u_y() = f_u* *x.get_u_y()
                 + f_v* *y.get_u_y();

    *z.get_u_xx() = f_uu * square(*x.get_u_x())
                  + f_u  * *x.get_u_xx()
                  + f_vv * square(*y.get_u_x())
                  + f_v  * *y.get_u_xx()
            + 2.0 * f_uv * *x.get_u_x() * *y.get_u_x();

    *z.get_u_xy() = f_uu * *x.get_u_x() * *x.get_u_y()
                  + f_u  * *x.get_u_xy()
                  + f_vv *  *y.get_u_x() * *y.get_u_y()
                  + f_v  * *y.get_u_xy()
                  + f_uv * (*x.get_u_x() * *y.get_u_y()
                         +  *x.get_u_y() * *y.get_u_x());

    *z.get_u_yy() = f_uu * square(*x.get_u_y())
                  + f_u  * *x.get_u_yy()
                  + f_vv * square(*y.get_u_y())
                  + f_v  * *y.get_u_yy()
            + 2.0 * f_uv * *x.get_u_y() * *y.get_u_y();


    *z.get_u_xxx() = f_uuu * cube(*x.get_u_x())
                   + 3.0 * f_uu * *x.get_u_x() * *x.get_u_xx()
                   + f_u * *x.get_u_xxx()
                   + f_vvv * cube(*y.get_u_x())
                   + 3.0 * f_vv * *y.get_u_x() * *y.get_u_xx()
                   + f_v * *y.get_u_xxx()
                   + 3.0 * f_uuv * square(*x.get_u_x()) * *y.get_u_x()
                   + 3.0 * f_uvv * *x.get_u_x()* square(*y.get_u_x())
                   + 3.0* f_uv * *x.get_u_xx() * *y.get_u_x()
                   + 3.0* f_uv * *x.get_u_x() * *y.get_u_xx();

    *z.get_u_xxy() = f_uuu * square(*x.get_u_x())* *x.get_u_y()
                   + 2.0 * f_uu * *x.get_u_x() * *x.get_u_xy()
                   + f_uu * *x.get_u_y() * *x.get_u_xx()
                   + f_u * *x.get_u_xxy()
                   + f_vvv * square(*y.get_u_x())* *y.get_u_y()
                   + 2.0 * f_vv * *y.get_u_x() * *y.get_u_xy()
                   + f_vv * *y.get_u_xx() * *y.get_u_y()
                   + f_v * *y.get_u_xxy()
                   + f_uuv * square(*x.get_u_x()) * *y.get_u_y()
                   + 2.0* f_uuv * *x.get_u_x() * *x.get_u_y() * *y.get_u_x()
                   + f_uvv * *x.get_u_y()* square(*y.get_u_x())
                   + 2.0 * f_uvv * *x.get_u_x()* *y.get_u_x() * *y.get_u_y()
                   + f_uv * *x.get_u_xx() * *y.get_u_y()
                   + f_uv * *x.get_u_y() * *y.get_u_xx()
                   + 2.0* f_uv * *x.get_u_xy() * *y.get_u_x()
                   + 2.0* f_uv * *x.get_u_x() * *y.get_u_xy();

    *z.get_u_xyy() = f_uuu * square(*x.get_u_y())* *x.get_u_x()
                   + 2.0 * f_uu * *x.get_u_y() * *x.get_u_xy()
                   + f_uu * *x.get_u_x() * *x.get_u_yy()
                   + f_u * *x.get_u_xyy()
                   + f_vvv * square(*y.get_u_y())* *y.get_u_x()
                   + 2.0 * f_vv * *y.get_u_y() * *y.get_u_xy()
                   + f_vv * *y.get_u_yy() * *y.get_u_x()
                   + f_v * *y.get_u_xyy()
                   + f_uuv * square(*x.get_u_y()) * *y.get_u_x()
                   + 2.0* f_uuv * *x.get_u_y() * *x.get_u_x() * *y.get_u_y()
                   + f_uvv * *x.get_u_x()* square(*y.get_u_y())
                   + 2.0 * f_uvv * *x.get_u_y()* *y.get_u_y() * *y.get_u_x()
                   + f_uv * *x.get_u_yy() * *y.get_u_x()
                   + f_uv * *x.get_u_x() * *y.get_u_yy()
                   + 2.0* f_uv * *x.get_u_xy() * *y.get_u_y()
                   + 2.0* f_uv * *x.get_u_y() * *y.get_u_xy();


    *z.get_u_yyy() = f_uuu * cube(*x.get_u_y())
                   + 3.0 * f_uu * *x.get_u_y() * *x.get_u_yy()
                   + f_u * *x.get_u_yyy()
                   + f_vvv * cube(*y.get_u_y())
                   + 3.0 * f_vv * *y.get_u_y() * *y.get_u_yy()
                   + f_v * *y.get_u_yyy()
                   + 3.0 * f_uuv * square(*x.get_u_y()) * *y.get_u_y()
                   + 3.0 * f_uvv * *x.get_u_y()* square(*y.get_u_y())
                   + 3.0 * f_uv * *x.get_u_yy() * *y.get_u_y()
                   + 3.0 * f_uv * *x.get_u_y() * *y.get_u_yy();
}

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable sqrt(const df3_two_variable& x)
  {
    df3_two_variable z;
    double u=::sqrt(*x.get_u());
    *z.get_u()=u;
    double xinv=1.0/(*x.get_u());
    double zp=0.5/u;
    double zp2=-0.5*zp*xinv;
    double zp3=-1.5*zp2*xinv;


    set_derivatives(z,x,u,zp,zp2,zp3);

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable atan(const df3_two_variable& x)
  {
    df3_two_variable z;
    double cx=value(x);
    double d=1.0/(1+square(cx));
    double d2=square(d);
    double u=::atan(cx);
    *z.get_u()=u;
    double zp=d;
    double zp2=-2.0*cx*d2;
    double zp3=-2.0*d2+8*cx*cx*d*d2;

    set_derivatives(z,x,u,zp,zp2,zp3);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable square(const df3_two_variable& x)
  {
    df3_two_variable z;
    double u=value(x);
    *z.get_u()=u*u;
    double zp=2.0*u;
    double zp2=2.0;
    double zp3=0.0;

    set_derivatives(z,x,u,zp,zp2,zp3);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable tan(const df3_two_variable& x)
  {
    df3_two_variable z;
    double u=::tan(*x.get_u());
    *z.get_u()=u;
    double v=1.0/::cos(*x.get_u());
    double w=::sin(*x.get_u());
    double v2=v*v;
    double zp=v2;
    double zp2=2.0*w*v2*v;
    double zp3=(4.0*w*w+2.0)*v2*v2;

    set_derivatives(z,x,u,zp,zp2,zp3);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable sin(const df3_two_variable& x)
  {
    df3_two_variable z;
    double u=::sin(*x.get_u());
    *z.get_u()=u;
    double zp=::cos(*x.get_u());
    double zp2=-u;
    double zp3=-zp;

    set_derivatives(z,x,u,zp,zp2,zp3);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable fabs(const df3_two_variable& v)
  {
    df3_two_variable z;
    if (value(v)>=0)
    {
      *z.get_u() = *v.get_u();
      *z.get_u_x() = *v.get_u_x();
      *z.get_u_y() = *v.get_u_y();
      *z.get_u_xx() = *v.get_u_xx();
      *z.get_u_xy() = *v.get_u_xy();
      *z.get_u_yy() = *v.get_u_yy();
      *z.get_u_xxx() = *v.get_u_xxx();
      *z.get_u_xxy() = *v.get_u_xxy();
      *z.get_u_xyy() = *v.get_u_xyy();
      *z.get_u_yyy() = *v.get_u_yyy();
    }
    else
    {
      *z.get_u() = -*v.get_u();
      *z.get_u_x() = -*v.get_u_x();
      *z.get_u_y() = -*v.get_u_y();
      *z.get_u_xx() = -*v.get_u_xx();
      *z.get_u_xy() = -*v.get_u_xy();
      *z.get_u_yy() = -*v.get_u_yy();
      *z.get_u_xxx() = -*v.get_u_xxx();
      *z.get_u_xxy() = -*v.get_u_xxy();
      *z.get_u_xyy() = -*v.get_u_xyy();
      *z.get_u_yyy() = -*v.get_u_yyy();
    }

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable log(const df3_two_variable& x)
  {
    df3_two_variable z;
    double u=::log(*x.get_u());
    *z.get_u()=u;
    double zp=1/(*x.get_u());
    double zp2=-zp*zp;
    double zp3=-2.0*zp*zp2;

    set_derivatives(z,x,u,zp,zp2,zp3);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable exp(const df3_two_variable& x)
  {
    df3_two_variable z;
    double u=::exp(*x.get_u());
    *z.get_u()=u;
    double zp=u;
    double zp2=u;
    double zp3=u;

    set_derivatives(z,x,u,zp,zp2,zp3);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable pow(const df3_two_variable& x,
                       const df3_two_variable& y)
  {
    df3_two_variable z;
    z=exp(y*log(x));
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable inv(const df3_two_variable& x)
  {
    df3_two_variable z;
    double xinv=1.0/(*x.get_u());
    *z.get_u()=xinv;
    double zp=-xinv*xinv;
    double zp2=-2.0*zp*xinv;
    double zp3=-3.0*zp2*xinv;

    set_derivatives(z,x,xinv,zp,zp2,zp3);

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable& df3_two_variable::operator = (const df3_two_variable& x)
  {
    *get_u() = *x.get_u();
    *get_u_x() = *x.get_u_x();
    *get_u_y() = *x.get_u_y();
    *get_u_xx() = *x.get_u_xx();
    *get_u_xy() = *x.get_u_xy();
    *get_u_yy() = *x.get_u_yy();
    *get_u_xxx() = *x.get_u_xxx();
    *get_u_xxy() = *x.get_u_xxy();
    *get_u_xyy() = *x.get_u_xyy();
    *get_u_yyy() = *x.get_u_yyy();
    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable& df3_two_variable::operator = (double x)
  {
    *get_u() = x;
    *get_u_x() =0.0;
    *get_u_y() =0.0;
    *get_u_xx() =0.0;
    *get_u_xy() =0.0;
    *get_u_yy() =0.0;
    *get_u_xxx() =0.0;
    *get_u_xxy() =0.0;
    *get_u_xyy() =0.0;
    *get_u_yyy() =0.0;
    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator * (const df3_two_variable& x,
    const df3_two_variable& y)
  {
    df3_two_variable z;
    double u= *x.get_u() * *y.get_u();
    *z.get_u() = u;
    double f_u=*y.get_u();
    double f_v=*x.get_u();
    double f_uu=0.0;
    double f_uv=1.0;
    double f_vv=0.0;
    double f_uuu=0.0;
    double f_uuv=0.0;
    double f_uvv=0.0;
    double f_vvv=0.0;
    set_derivatives(z,x,y,u,
      f_u, f_v,
      f_uu, f_uv, f_vv,
      f_uuu, f_uuv, f_uvv, f_vvv);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator * (double x,
    const df3_two_variable& y)
  {
    df3_two_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_u_x() = x * *y.get_u_x();
    *z.get_u_y() = x * *y.get_u_y();
    *z.get_u_xx() = x * *y.get_u_xx();
    *z.get_u_xy() = x * *y.get_u_xy();
    *z.get_u_yy() = x * *y.get_u_yy();
    *z.get_u_xxx() = x * *y.get_u_xxx();
    *z.get_u_xxy() = x * *y.get_u_xxy();
    *z.get_u_xyy() = x * *y.get_u_xyy();
    *z.get_u_yyy() = x * *y.get_u_yyy();

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator * (const df3_two_variable& y,
    double x)
  {
    df3_two_variable z;
    *z.get_u() = x *  *y.get_u();
    *z.get_u_x() = x * *y.get_u_x();
    *z.get_u_y() = x * *y.get_u_y();
    *z.get_u_xx() = x * *y.get_u_xx();
    *z.get_u_xy() = x * *y.get_u_xy();
    *z.get_u_yy() = x * *y.get_u_yy();
    *z.get_u_xxx() = x * *y.get_u_xxx();
    *z.get_u_xxy() = x * *y.get_u_xxy();
    *z.get_u_xyy() = x * *y.get_u_xyy();
    *z.get_u_yyy() = x * *y.get_u_yyy();

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator / (const df3_two_variable& x,
    double y)
  {
    double u=1/y;
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator / (const df3_two_variable& x,
    const df3_two_variable& y)
  {
    df3_two_variable u=inv(y);
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator / (const double x,
    const df3_two_variable& y)
  {
    df3_two_variable u=inv(y);
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator + (const double x,const df3_two_variable& y)
  {
    df3_two_variable z;
    *z.get_u() =  x + *y.get_u();
    *z.get_u_x() = *y.get_u_x();
    *z.get_u_y() = *y.get_u_y();
    *z.get_u_xx() = *y.get_u_xx();
    *z.get_u_xy() = *y.get_u_xy();
    *z.get_u_yy() = *y.get_u_yy();
    *z.get_u_xxx() = *y.get_u_xxx();
    *z.get_u_xxy() = *y.get_u_xxy();
    *z.get_u_xyy() = *y.get_u_xyy();
    *z.get_u_yyy() = *y.get_u_yyy();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator + (const df3_two_variable& x,const double y)
  {
    df3_two_variable z;
    *z.get_u() =  *x.get_u() + y;
    *z.get_u_x() = *x.get_u_x();
    *z.get_u_y() = *x.get_u_y();
    *z.get_u_xx() = *x.get_u_xx();
    *z.get_u_xy() = *x.get_u_xy();
    *z.get_u_yy() = *x.get_u_yy();
    *z.get_u_xxx() = *x.get_u_xxx();
    *z.get_u_xxy() = *x.get_u_xxy();
    *z.get_u_xyy() = *x.get_u_xyy();
    *z.get_u_yyy() = *x.get_u_yyy();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator + (const df3_two_variable& x,
    const df3_two_variable& y)
  {
    df3_two_variable z;
    *z.get_u() = *x.get_u() + *y.get_u();
    *z.get_u_x() = *x.get_u_x() + *y.get_u_x();
    *z.get_u_y() = *x.get_u_y()+*y.get_u_y();
    *z.get_u_xx() = *x.get_u_xx()+ *y.get_u_xx();
    *z.get_u_xy() = *x.get_u_xy()+ *y.get_u_xy();
    *z.get_u_yy() = *x.get_u_yy()+ *y.get_u_yy();
    *z.get_u_xxx() = *x.get_u_xxx()+ *y.get_u_xxx();
    *z.get_u_xxy() = *x.get_u_xxy()+ *y.get_u_xxy();
    *z.get_u_xyy() = *x.get_u_xyy()+ *y.get_u_xyy();
    *z.get_u_yyy() = *x.get_u_yyy()+ *y.get_u_yyy();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator - (const df3_two_variable& x,
    const df3_two_variable& y)
  {
    df3_two_variable z;
    *z.get_u() = *x.get_u() - *y.get_u();
    *z.get_u_x() = *x.get_u_x()  - *y.get_u_x();
    *z.get_u_y() = *x.get_u_y() - *y.get_u_y();
    *z.get_u_xx() = *x.get_u_xx() - *y.get_u_xx();
    *z.get_u_xy() = *x.get_u_xy() - *y.get_u_xy();
    *z.get_u_yy() = *x.get_u_yy() - *y.get_u_yy();
    *z.get_u_xxx() = *x.get_u_xxx() - *y.get_u_xxx();
    *z.get_u_xxy() = *x.get_u_xxy() - *y.get_u_xxy();
    *z.get_u_xyy() = *x.get_u_xyy() - *y.get_u_xyy();
    *z.get_u_yyy() = *x.get_u_yyy() - *y.get_u_yyy();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator - (double x,
    const df3_two_variable& y)
  {
    df3_two_variable z;
    *z.get_u() = x - *y.get_u();
    *z.get_u_x() = - *y.get_u_x();
    *z.get_u_y() = - *y.get_u_y();
    *z.get_u_xx() = - *y.get_u_xx();
    *z.get_u_xy() = - *y.get_u_xy();
    *z.get_u_yy() = - *y.get_u_yy();
    *z.get_u_xxx() = - *y.get_u_xxx();
    *z.get_u_xxy() = - *y.get_u_xxy();
    *z.get_u_xyy() = - *y.get_u_xyy();
    *z.get_u_yyy() = - *y.get_u_yyy();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_two_variable operator - (const df3_two_variable& x,
    double y)
  {
    df3_two_variable z;
    *z.get_u() = *x.get_u()-y;
    *z.get_u_x() = *x.get_u_x();
    *z.get_u_y() = *x.get_u_y();
    *z.get_u_xx() = *x.get_u_xx();
    *z.get_u_xy() = *x.get_u_xy();
    *z.get_u_yy() = *x.get_u_yy();
    *z.get_u_xxx() = *x.get_u_xxx();
    *z.get_u_xxy() = *x.get_u_xxy();
    *z.get_u_xyy() = *x.get_u_xyy();
    *z.get_u_yyy() = *x.get_u_yyy();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
init_df3_two_variable::init_df3_two_variable(const df1b2variable& _v)
{
  /*
  if (ind_var != 0)
  {
    cerr << " can only have 1 independent_variable in a reverse funnel"
           << endl;
    ad_exit(1);
  }
  */
  if (num_ind_var>1)
  {
    cerr << "can only have 2 independent_variables in df3_two_variable"
       " function" << endl;
    ad_exit(1);
  }
  else
  {
    ADUNCONST(df1b2variable,v)

    ind_var[num_ind_var++]=&v;
    *get_u() =  *v.get_u();
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
           << " in  df3_two_variable function" << endl;
      ad_exit(1);
    }
    *get_u_xx() = 0.0;
    *get_u_xy() = 0.0;
    *get_u_yy() = 0.0;
    *get_u_xxx() = 0.0;
    *get_u_xxy() = 0.0;
    *get_u_xyy() = 0.0;
    *get_u_yyy() = 0.0;
  }
}

/**
 * Description not yet available.
 * \param
 */
  init_df3_two_variable::init_df3_two_variable(double v)
  {
    *get_u() =  v;
    *get_u_x() = 0.0;
    *get_u_y() = 0.0;
    *get_u_xx() = 0.0;
    *get_u_xy() = 0.0;
    *get_u_yy() = 0.0;
    *get_u_xxx() = 0.0;
    *get_u_xxy() = 0.0;
    *get_u_xyy() = 0.0;
    *get_u_yyy() = 0.0;
  }

  df3_two_variable::df3_two_variable(void)
  {
  }

/**
 * Description not yet available.
 * \param
 */
df3_two_matrix choleski_decomp(const df3_two_matrix& MM)
{
  // kludge to deal with constantness
  df3_two_matrix & M= (df3_two_matrix &) MM;
  int rmin=M.indexmin();
  int cmin=M(rmin).indexmin();
  int rmax=M.indexmax();
  int cmax=M(rmin).indexmax();
  if (rmin !=1 || cmin !=1)
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df3_two_atrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df3_two_matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }

  int n=rmax-rmin+1;
  df3_two_matrix L(1,n,1,n);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df3_two_variable tmp;

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

/**
 * Description not yet available.
 * \param
 */
df1b2matrix& df1b2matrix::operator = (const df3_two_matrix& M)
{
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != indexmin() || rmax != indexmax())
  {
    cerr << "unequal shape in "
     "df1b2matrix& df1b2matrix::operator = (const df3_two_matrix& M)"
      << endl;
    ad_exit(1);
  }

  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::operator = (const df3_two_vector& M)
{
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  if (rmin != indexmin() || rmax != indexmax())
  {
    cerr << "unequal shape in "
     "df1b2vector& df1b2vector::operator = (const df3_two_vector& M)"
      << endl;
    ad_exit(1);
  }

  for (int i=rmin;i<=rmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b2variable::operator = (const df3_two_variable& v)
{
  df1b2variable * px=df3_two_variable::ind_var[0];
  df1b2variable * py=df3_two_variable::ind_var[1];
  df3_two_variable::num_ind_var=0;
  df3_two_variable::ind_var[0]=0;
  df3_two_variable::ind_var[1]=0;
  //df1b2variable * px=0;
  double  dfx= *v.get_u_x();
  double  dfy= *v.get_u_y();
  double * xd=px->get_u_dot();
  double * yd=py->get_u_dot();
  double * zd=get_u_dot();
  *get_u()=*v.get_u();
  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ + dfy * *yd++;
  }

  f1b2gradlist->write_pass1(px,py,this,
    *v.get_u_x(),
    *v.get_u_y(),
    *v.get_u_xx(),
    *v.get_u_xy(),
    *v.get_u_yy(),
    *v.get_u_xxx(),
    *v.get_u_xxy(),
    *v.get_u_xyy(),
    *v.get_u_yyy());
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable div(const df1b2variable& x,const df1b2variable& y)
{
  df1b2variable z;
  double xu=*x.get_u();
  double yu=*y.get_u();
  double yinv=1.0/yu;
  *z.get_u()=xu*yinv;

  double dfx= yinv;
  double dfy= -xu*yinv*yinv;
  double dfxx= 0.0;
  double dfxy=-yinv*yinv;
  double dfyy=2.0*xu*yinv*yinv*yinv;
  double dfxxx= 0.0;
  double dfxxy= 0.0;
  double dfxyy=2.0*yinv*yinv*yinv;
  double dfyyy=-6.0*xu*yinv*yinv*yinv*yinv;

  double * xd=x.get_u_dot();
  double * yd=y.get_u_dot();
  double * zd=z.get_u_dot();

  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ + dfy * *yd++;
  }

  f1b2gradlist->write_pass1(&x,&y,&z,
    dfx,
    dfy,
    dfxx,dfxy,dfyy,
    dfxxx,dfxxy,dfxyy,dfyyy);
  return z;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable mypow(const df1b2variable& x,double y)
{
  df1b2variable z;
  double xu=*x.get_u();
  *z.get_u()=::pow(xu,y);

  double dfx= y*::pow(xu,y-1.0);
  double dfxx= y*(y-1.0)*::pow(xu,y-2.0);
  double dfxxx= y*(y-1.0)*(y-2.0)*::pow(xu,y-3.0);
  double * xd=x.get_u_dot();
  double * zd=z.get_u_dot();

  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ ;
  }

  f1b2gradlist->write_pass1(&x,&z,
    dfx,
    dfxx,
    dfxxx);
  return z;
}
