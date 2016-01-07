/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB Foundation
 */
#include <df1b2fun.h>
#include "df33fun.h"
  df1b2variable * df3_three_variable::ind_var[3];
  int df3_three_variable::num_ind_var=0;
  int df3_three_variable::num_local_ind_var=0;

/**
Default constructor
*/
df3_three_variable::df3_three_variable()
{
  for (int i = 0; i < 20; ++i)
  {
    v[i] = 0;
  }
}
/**
Copy constructor
*/
df3_three_variable::df3_three_variable(const df3_three_variable& x)
{
  memcpy(&(v[0]),&(x.v[0]),20*sizeof(double));
}
/**
Copy constructor
*/
df3_three_vector::df3_three_vector(const df3_three_vector& m2)
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
df1b2variable& df1b2variable::operator = (const df3_three_variable& v)
{
  df1b2variable * px=df3_three_variable::ind_var[0];
  df1b2variable * py=df3_three_variable::ind_var[1];
  df1b2variable * pv=df3_three_variable::ind_var[2];
  df3_three_variable::num_ind_var=0;
  df3_three_variable::ind_var[0]=0;
  df3_three_variable::ind_var[1]=0;
  df3_three_variable::ind_var[2]=0;
  //df1b2variable * px=0;
  double  dfx= *v.get_u_x();
  double  dfy= *v.get_u_y();
  double  dfz= *v.get_u_z();
  double * xd=px->get_u_dot();
  double * yd=py->get_u_dot();
  double * vd=pv->get_u_dot();
  double * zd=get_u_dot();
  *get_u()=*v.get_u();
  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ = dfx * *xd++ + dfy * *yd++ + dfz * *vd++;
  }

 /*
  cout << *v.get_u()  << " ";
  cout << *v.get_udot()  << " ";
  cout << *v.get_udot2()  << " ";
  cout << *v.get_udot3()  << endl;
  */
  f1b2gradlist->write_pass1(px,
    py,
    pv,
    this,
    *v.get_u_x(),
    *v.get_u_y(),
    *v.get_u_z(),
    *v.get_u_xx(),
    *v.get_u_xy(),
    *v.get_u_xz(),
    *v.get_u_yy(),
    *v.get_u_yz(),
    *v.get_u_zz(),
    *v.get_u_xxx(),
    *v.get_u_xxy(),
    *v.get_u_xxz(),
    *v.get_u_xyy(),
    *v.get_u_xyz(),
    *v.get_u_xzz(),
    *v.get_u_yyy(),
    *v.get_u_yyz(),
    *v.get_u_yzz(),
    *v.get_u_zzz());
  return *this;
}

/**
Intialize values (v) to zero.
*/
void df3_three_variable::initialize(void)
{
  for (int i=0;i<20;i++)
    v[i]=0.0;
}

/**
Destructor
*/
df3_three_vector::~df3_three_vector()
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
 void df3_three_vector::deallocate(void)
 {
   if(shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df3_three_variable*) (shape->trueptr);
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
 dvector value(const df3_three_vector& v)
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
  void df3_three_vector::initialize(void)
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
  df3_three_vector::df3_three_vector(void)
  {
    allocate();
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_vector::df3_three_vector(int min,int max)
  {
    allocate(min,max);
  }

/**
 * Description not yet available.
 * \param
 */
  void df3_three_vector::allocate(int min,int max)
  {
    index_min=min;
    index_max=max;
    v=new df3_three_variable[max-min+1];
    if (v==0)
    {
      cerr << "error allocating memory in df3_three_vector" << endl;
      ad_exit(1);
    }
    if ( (shape=new vector_shapex(min,max,v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df3_three_vector"
           << endl;;
      ad_exit(1);
    }
    v-=min;
  }

/**
 * Description not yet available.
 * \param
 */
  void df3_three_vector::allocate(void)
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
 dmatrix value(const df3_three_matrix& v)
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
 df3_three_matrix::df3_three_matrix(const df3_three_matrix& m2)
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
 df3_three_matrix::~df3_three_matrix()
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 void df3_three_matrix::deallocate(void)
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       v = (df3_three_vector*) (shape->get_pointer());
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
  void df3_three_matrix::initialize(void)
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
  df3_three_matrix::df3_three_matrix(int rmin,int rmax,int cmin,int cmax)
  {
    index_min=rmin;
    index_max=rmax;
    v=new df3_three_vector[rmax-rmin+1];
    if (v==0)
    {
      cerr << "error allocating memory in df3_three_matrix" << endl;
      ad_exit(1);
    }
    if ( (shape=new mat_shapex(v)) == NULL)
    {
      cerr << "Error trying to allocate memory for df3_three_vector"
           << endl;;
    }
    v-=rmin;

    for (int i=rmin;i<=rmax;i++)
    {
      v[i].allocate(cmin,cmax);
    }
  }
/**
Subtract values from _v in df3_three_variable.
*/
df3_three_variable& df3_three_variable::operator-=(const df3_three_variable& _v)
{
  *get_u() -= *_v.get_u();
  *get_u_x() -= *_v.get_u_x();
  *get_u_y() -= *_v.get_u_y();
  *get_u_z() -= *_v.get_u_z();
  *get_u_xx() -= *_v.get_u_xx();
  *get_u_xy() -= *_v.get_u_xy();
  *get_u_xz() -= *_v.get_u_xz();
  *get_u_yy() -= *_v.get_u_yy();
  *get_u_yz() -= *_v.get_u_yz();
  *get_u_zz() -= *_v.get_u_zz();
  *get_u_xxx() -= *_v.get_u_xxx();
  *get_u_xxy() -= *_v.get_u_xxy();
  *get_u_xxz() -= *_v.get_u_xxz();
  *get_u_xyy() -= *_v.get_u_xyy();
  *get_u_xyz() -= *_v.get_u_xyz();
  *get_u_xzz() -= *_v.get_u_xzz();
  *get_u_yyy() -= *_v.get_u_yyy();
  *get_u_yyz() -= *_v.get_u_yyz();
  *get_u_yzz() -= *_v.get_u_yzz();
  *get_u_zzz() -= *_v.get_u_zzz();
  return *this;
}
/**
Subtract value _v from only u in df3_three_variable.  All other values are unchanged.
*/
df3_three_variable& df3_three_variable::operator-=(double _v)
{
  *get_u() -= _v;
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df3_three_variable operator-(const df3_three_variable& v)
{
  df3_three_variable z;

  *z.get_u() = -(*v.get_u());
  *z.get_u_x() = -(*v.get_u_x());
  *z.get_u_y() = -(*v.get_u_y());
  *z.get_u_z() = -(*v.get_u_z());
  *z.get_u_xx() = -(*v.get_u_xx());
  *z.get_u_xy() = -(*v.get_u_xy());
  *z.get_u_xz() = -(*v.get_u_xz());
  *z.get_u_yy() = -(*v.get_u_yy());
  *z.get_u_yz() = -(*v.get_u_yz());
  *z.get_u_zz() = -(*v.get_u_zz());
  *z.get_u_xxx() = -(*v.get_u_xxx());
  *z.get_u_xxy() = -(*v.get_u_xxy());
  *z.get_u_xxz() = -(*v.get_u_xxz());
  *z.get_u_xyy() = -(*v.get_u_xyy());
  *z.get_u_xyz() = -(*v.get_u_xyz());
  *z.get_u_xzz() = -(*v.get_u_xzz());
  *z.get_u_yyy() = -(*v.get_u_yyy());
  *z.get_u_yyz() = -(*v.get_u_yyz());
  *z.get_u_yzz() = -(*v.get_u_yzz());
  *z.get_u_zzz() = -(*v.get_u_zzz());

  return z;
}
/**
Add values of v to df3_three_variable.
*/
df3_three_variable& df3_three_variable::operator+=(const df3_three_variable& _v)
{
  *get_u() += *_v.get_u();
  *get_u_x() += *_v.get_u_x();
  *get_u_y() += *_v.get_u_y();
  *get_u_z() += *_v.get_u_z();
  *get_u_xx() += *_v.get_u_xx();
  *get_u_xy() += *_v.get_u_xy();
  *get_u_xz() += *_v.get_u_xz();
  *get_u_yy() += *_v.get_u_yy();
  *get_u_yz() += *_v.get_u_yz();
  *get_u_zz() += *_v.get_u_zz();
  *get_u_xxx() += *_v.get_u_xxx();
  *get_u_xxy() += *_v.get_u_xxy();
  *get_u_xxz() += *_v.get_u_xxz();
  *get_u_xyy() += *_v.get_u_xyy();
  *get_u_xyz() += *_v.get_u_xyz();
  *get_u_xzz() += *_v.get_u_xzz();
  *get_u_yyy() += *_v.get_u_yyy();
  *get_u_yyz() += *_v.get_u_yyz();
  *get_u_yzz() += *_v.get_u_yzz();
  *get_u_zzz() += *_v.get_u_zzz();
  return *this;
}
/**
Multiply value v to the values of df3_three_variable.
*/
df3_three_variable& df3_three_variable::operator*=(double _v)
{
  *get_u() *= _v;
  *get_u_x() *= _v;
  *get_u_y() *= _v;
  *get_u_z() *= _v;
  *get_u_xx() *= _v;
  *get_u_xy() *= _v;
  *get_u_xz() *= _v;
  *get_u_yy() *= _v;
  *get_u_yz() *= _v;
  *get_u_zz() *= _v;
  *get_u_xxx() *= _v;
  *get_u_xxy() *= _v;
  *get_u_xxz() *= _v;
  *get_u_xyy() *= _v;
  *get_u_xyz() *= _v;
  *get_u_xzz() *= _v;
  *get_u_yyy() *= _v;
  *get_u_yyz() *= _v;
  *get_u_yzz() *= _v;
  *get_u_zzz() *= _v;
  return *this;
}
/**
Multiply values in v to df3_three_variable.
*/
df3_three_variable& df3_three_variable::operator*=(const df3_three_variable& v)
{
  ///\todo needs a test case
  df3_three_variable x = *this * v;
  *this = x;
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df3_three_variable& df3_three_variable::operator/=(const df3_three_variable& v)
  {
    ///\todo needs a test case
    df3_three_variable x=*this / v;
    *this=x;
    return *this;
  }
/**
Add value _v to only df3_three_variable u.  All other values unchanged.
*/
df3_three_variable& df3_three_variable::operator+=(double _v)
{
  *get_u() += _v;
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
void set_derivatives(df3_three_variable& z,const df3_three_variable& x,
  double u, double zp,double zp2,double zp3)
{
    //*z.get_u() = u;

    *z.get_u_x() = zp* *x.get_u_x();

    *z.get_u_y() = zp* *x.get_u_y();

    *z.get_u_z() = zp* *x.get_u_z();

    *z.get_u_xx() = zp2 * square(*x.get_u_x())
                   + zp * *x.get_u_xx();

    *z.get_u_xy() = zp2 * *x.get_u_x() * *x.get_u_y()
                   + zp * *x.get_u_xy();

    *z.get_u_xz() = zp2 * *x.get_u_x() * *x.get_u_z()
                   + zp * *x.get_u_xz();

    *z.get_u_yy() = zp2 * square(*x.get_u_y())
                   + zp * *x.get_u_yy();

    *z.get_u_yz() = zp2 * *x.get_u_y()* *x.get_u_z()
                   + zp * *x.get_u_yz();

    *z.get_u_zz() = zp2 * square(*x.get_u_z())
                   + zp * *x.get_u_zz();

    *z.get_u_xxx() = zp3 * cube(*x.get_u_x())
                   + 3.0 * zp2 * *x.get_u_x() * *x.get_u_xx()
                   + zp * *x.get_u_xxx();

    *z.get_u_xxy() = zp3 * square(*x.get_u_x())* *x.get_u_y()
                   + 2.0* zp2 * *x.get_u_x() * *x.get_u_xy()
                   + zp2 * *x.get_u_y() * *x.get_u_xx()
                   + zp * *x.get_u_xxy();

    *z.get_u_xxz() = zp3 * square(*x.get_u_x())* *x.get_u_z()
                   + 2.0* zp2 * *x.get_u_x() * *x.get_u_xz()
                   + zp2 * *x.get_u_z() * *x.get_u_xx()
                   + zp * *x.get_u_xxz();

    *z.get_u_xyy() = zp3 * square(*x.get_u_y())* *x.get_u_x()
                   + 2.0* zp2 * *x.get_u_y() * *x.get_u_xy()
                   + zp2 * *x.get_u_x() * *x.get_u_yy()
                   + zp * *x.get_u_xyy();

    *z.get_u_xyz() = zp3 * *x.get_u_y()* *x.get_u_x()* *x.get_u_z()
                   + zp2 * *x.get_u_z() * *x.get_u_xy()
                   + zp2 * *x.get_u_y() * *x.get_u_xz()
                   + zp2 * *x.get_u_x() * *x.get_u_yz()
                   + zp * *x.get_u_xyz();

    *z.get_u_xzz() = zp3 * square(*x.get_u_z())* *x.get_u_x()
                   + 2.0* zp2 * *x.get_u_z() * *x.get_u_xz()
                   + zp2 * *x.get_u_x() * *x.get_u_zz()
                   + zp * *x.get_u_xzz();


    *z.get_u_yyy() = zp3 * cube(*x.get_u_y())
                   + 3.0 * zp2 * *x.get_u_y() * *x.get_u_yy()
                   + zp * *x.get_u_yyy();
    *z.get_u_yyz() = zp3 * square(*x.get_u_y())* *x.get_u_z()
                   + 2.0* zp2 * *x.get_u_y() * *x.get_u_yz()
                   + zp2 * *x.get_u_z() * *x.get_u_yy()
                   + zp * *x.get_u_yyz();

    *z.get_u_yzz() = zp3 * square(*x.get_u_z())* *x.get_u_y()
                   + 2.0* zp2 * *x.get_u_z() * *x.get_u_yz()
                   + zp2 * *x.get_u_y() * *x.get_u_zz()
                   + zp * *x.get_u_yzz();

    *z.get_u_zzz() = zp3 * cube(*x.get_u_z())
                   + 3.0 * zp2 * *x.get_u_z() * *x.get_u_zz()
                   + zp * *x.get_u_zzz();
}

/**
 * Description not yet available.
 * \param
 */
void set_derivatives( df3_three_variable& z, const df3_three_variable& x,
  const df3_three_variable& y, double u,
  double f_u,double f_v,double f_uu,double f_uv,double f_vv,double f_uuu,
  double f_uuv,double f_uvv,double f_vvv)
{
    *z.get_u() = u;

    *z.get_u_x() = f_u* *x.get_u_x()
                 + f_v* *y.get_u_x();

    *z.get_u_y() = f_u* *x.get_u_y()
                 + f_v* *y.get_u_y();

    *z.get_u_z() = f_u* *x.get_u_z()
                 + f_v* *y.get_u_z();

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

    *z.get_u_xz() = f_uu * *x.get_u_x() * *x.get_u_z()
                  + f_u  * *x.get_u_xz()
                  + f_vv *  *y.get_u_x() * *y.get_u_z()
                  + f_v  * *y.get_u_xz()
                  + f_uv * (*x.get_u_x() * *y.get_u_z()
                         +  *x.get_u_z() * *y.get_u_x());

    *z.get_u_yy() = f_uu * square(*x.get_u_y())
                  + f_u  * *x.get_u_yy()
                  + f_vv * square(*y.get_u_y())
                  + f_v  * *y.get_u_yy()
            + 2.0 * f_uv * *x.get_u_y() * *y.get_u_y();

    *z.get_u_yz() = f_uu * *x.get_u_y() * *x.get_u_z()
                  + f_u  * *x.get_u_yz()
                  + f_vv *  *y.get_u_y() * *y.get_u_z()
                  + f_v  * *y.get_u_yz()
                  + f_uv * (*x.get_u_y() * *y.get_u_z()
                         +  *x.get_u_z() * *y.get_u_y());

    *z.get_u_zz() = f_uu * *x.get_u_z() * *x.get_u_z()
                  + f_u  * *x.get_u_zz()
                  + f_vv *  *y.get_u_z() * *y.get_u_z()
                  + f_v  * *y.get_u_zz()
                  + f_uv * (*x.get_u_z() * *y.get_u_z()
                         +  *x.get_u_z() * *y.get_u_z());


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

    *z.get_u_xxz() = f_uuu * square(*x.get_u_x())* *x.get_u_z()
                   + 2.0 * f_uu * *x.get_u_x() * *x.get_u_xz()
                   + f_uu * *x.get_u_z() * *x.get_u_xx()
                   + f_u * *x.get_u_xxz()
                   + f_vvv * square(*y.get_u_x())* *y.get_u_z()
                   + 2.0 * f_vv * *y.get_u_x() * *y.get_u_xz()
                   + f_vv * *y.get_u_xx() * *y.get_u_z()
                   + f_v * *y.get_u_xxz()
                   + f_uuv * square(*x.get_u_x()) * *y.get_u_z()
                   + 2.0* f_uuv * *x.get_u_x() * *x.get_u_z() * *y.get_u_x()
                   + f_uvv * *x.get_u_z()* square(*y.get_u_x())
                   + 2.0 * f_uvv * *x.get_u_x()* *y.get_u_x() * *y.get_u_z()
                   + f_uv * *x.get_u_xx() * *y.get_u_z()
                   + f_uv * *x.get_u_z() * *y.get_u_xx()
                   + 2.0* f_uv * *x.get_u_xz() * *y.get_u_x()
                   + 2.0* f_uv * *x.get_u_x() * *y.get_u_xz();

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

    *z.get_u_xyz() = f_uuu * *x.get_u_y()* *x.get_u_x()* *x.get_u_z()
                   + f_uuv * *x.get_u_y() * *x.get_u_x()* *y.get_u_z()
                   + f_uu * *x.get_u_y() * *x.get_u_xz()
                   + f_uu * *x.get_u_x() * *x.get_u_yz()

                   + f_uuv * *y.get_u_y() * *x.get_u_x()* *x.get_u_z()
                   + f_uvv * *y.get_u_y() * *x.get_u_x()* *y.get_u_z()
                   + f_uv * *x.get_u_xz() * *y.get_u_y()
                   + f_uv * *y.get_u_yz() * *x.get_u_x()

                   + f_uu * *x.get_u_xy() * *x.get_u_z()
                   + f_uv * *x.get_u_xy() * *y.get_u_z()
                   + f_u * *x.get_u_xyz()

                   + f_uuv * *x.get_u_y() * *y.get_u_x()* *x.get_u_z()
                   + f_uvv * *x.get_u_y() * *y.get_u_x()* *y.get_u_z()
                   + f_uv * *y.get_u_x() * *x.get_u_yz()
                   + f_uv * *x.get_u_y() * *y.get_u_xz()

                   + f_uvv * *y.get_u_y() * *y.get_u_x()* *x.get_u_z()
                   + f_vvv * *y.get_u_y() * *y.get_u_x()* *y.get_u_z()

                   + f_vv * *y.get_u_xz() * *y.get_u_y()
                   + f_vv * *y.get_u_yz() * *y.get_u_x()
                   + f_vv * *y.get_u_xy() * *y.get_u_z()
                   + f_uv * *y.get_u_xy() * *x.get_u_z()
                   + f_v * *y.get_u_xyz();

    *z.get_u_xzz() = f_uuu * square(*x.get_u_z())* *x.get_u_x()
                   + 2.0 * f_uu * *x.get_u_z() * *x.get_u_xz()
                   + f_uu * *x.get_u_x() * *x.get_u_zz()
                   + f_u * *x.get_u_xzz()
                   + f_vvv * square(*y.get_u_z())* *y.get_u_x()
                   + 2.0 * f_vv * *y.get_u_z() * *y.get_u_xz()
                   + f_vv * *y.get_u_zz() * *y.get_u_x()
                   + f_v * *y.get_u_xzz()
                   + f_uuv * square(*x.get_u_z()) * *y.get_u_x()
                   + 2.0* f_uuv * *x.get_u_z() * *x.get_u_x() * *y.get_u_z()
                   + f_uvv * *x.get_u_x()* square(*y.get_u_z())
                   + 2.0 * f_uvv * *x.get_u_z()* *y.get_u_z() * *y.get_u_x()
                   + f_uv * *x.get_u_zz() * *y.get_u_x()
                   + f_uv * *x.get_u_x() * *y.get_u_zz()
                   + 2.0* f_uv * *x.get_u_xz() * *y.get_u_z()
                   + 2.0* f_uv * *x.get_u_z() * *y.get_u_xz();

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

    *z.get_u_yyz() = f_uuu * square(*x.get_u_y())* *x.get_u_z()
                   + 2.0 * f_uu * *x.get_u_y() * *x.get_u_yz()
                   + f_uu * *x.get_u_z() * *x.get_u_yy()
                   + f_u * *x.get_u_yyz()
                   + f_vvv * square(*y.get_u_y())* *y.get_u_z()
                   + 2.0 * f_vv * *y.get_u_y() * *y.get_u_yz()
                   + f_vv * *y.get_u_yy() * *y.get_u_z()
                   + f_v * *y.get_u_yyz()
                   + f_uuv * square(*x.get_u_y()) * *y.get_u_z()
                   + 2.0* f_uuv * *x.get_u_y() * *x.get_u_z() * *y.get_u_y()
                   + f_uvv * *x.get_u_z()* square(*y.get_u_y())
                   + 2.0 * f_uvv * *x.get_u_y()* *y.get_u_y() * *y.get_u_z()
                   + f_uv * *x.get_u_yy() * *y.get_u_z()
                   + f_uv * *x.get_u_z() * *y.get_u_yy()
                   + 2.0* f_uv * *x.get_u_yz() * *y.get_u_y()
                   + 2.0* f_uv * *x.get_u_y() * *y.get_u_yz();

    *z.get_u_yyz() = f_uuu * square(*x.get_u_y())* *x.get_u_z()
                   + 2.0 * f_uu * *x.get_u_y() * *x.get_u_yz()
                   + f_uu * *x.get_u_z() * *x.get_u_yy()
                   + f_u * *x.get_u_yyz()
                   + f_vvv * square(*y.get_u_y())* *y.get_u_z()
                   + 2.0 * f_vv * *y.get_u_y() * *y.get_u_yz()
                   + f_vv * *y.get_u_yy() * *y.get_u_z()
                   + f_v * *y.get_u_yyz()
                   + f_uuv * square(*x.get_u_y()) * *y.get_u_z()
                   + 2.0* f_uuv * *x.get_u_y() * *x.get_u_z() * *y.get_u_y()
                   + f_uvv * *x.get_u_z()* square(*y.get_u_y())
                   + 2.0 * f_uvv * *x.get_u_y()* *y.get_u_y() * *y.get_u_z()
                   + f_uv * *x.get_u_yy() * *y.get_u_z()
                   + f_uv * *x.get_u_z() * *y.get_u_yy()
                   + 2.0* f_uv * *x.get_u_yz() * *y.get_u_y()
                   + 2.0* f_uv * *x.get_u_y() * *y.get_u_yz();

    *z.get_u_yzz() = f_uuu * square(*x.get_u_z())* *x.get_u_y()
                   + 2.0 * f_uu * *x.get_u_z() * *x.get_u_yz()
                   + f_uu * *x.get_u_y() * *x.get_u_zz()
                   + f_u * *x.get_u_yzz()
                   + f_vvv * square(*y.get_u_z())* *y.get_u_y()
                   + 2.0 * f_vv * *y.get_u_z() * *y.get_u_yz()
                   + f_vv * *y.get_u_zz() * *y.get_u_y()
                   + f_v * *y.get_u_yzz()
                   + f_uuv * square(*x.get_u_z()) * *y.get_u_y()
                   + 2.0* f_uuv * *x.get_u_z() * *x.get_u_y() * *y.get_u_z()
                   + f_uvv * *x.get_u_y()* square(*y.get_u_z())
                   + 2.0 * f_uvv * *x.get_u_z()* *y.get_u_z() * *y.get_u_y()
                   + f_uv * *x.get_u_zz() * *y.get_u_y()
                   + f_uv * *x.get_u_y() * *y.get_u_zz()
                   + 2.0* f_uv * *x.get_u_yz() * *y.get_u_z()
                   + 2.0* f_uv * *x.get_u_z() * *y.get_u_yz();

    *z.get_u_zzz() = f_uuu * cube(*x.get_u_z())
                   + 3.0 * f_uu * *x.get_u_z() * *x.get_u_zz()
                   + f_u * *x.get_u_zzz()
                   + f_vvv * cube(*y.get_u_z())
                   + 3.0 * f_vv * *y.get_u_z() * *y.get_u_zz()
                   + f_v * *y.get_u_zzz()
                   + 3.0 * f_uuv * square(*x.get_u_z()) * *y.get_u_z()
                   + 3.0 * f_uvv * *x.get_u_z()* square(*y.get_u_z())
                   + 3.0 * f_uv * *x.get_u_zz() * *y.get_u_z()
                   + 3.0 * f_uv * *x.get_u_z() * *y.get_u_zz();
}

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable sqrt(const df3_three_variable& x)
  {
    df3_three_variable z;
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
  df3_three_variable atan(const df3_three_variable& x)
  {
    df3_three_variable z;
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
  df3_three_variable pow(const df3_three_variable& x,
    const df3_three_variable& y)
  {
    df3_three_variable z;
    z=exp(y*log(x));
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable square(const df3_three_variable& x)
  {
    df3_three_variable z;
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
  df3_three_variable tan(const df3_three_variable& x)
  {
    df3_three_variable z;
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
  df3_three_variable sin(const df3_three_variable& x)
  {
    df3_three_variable z;
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
  df3_three_variable log(const df3_three_variable& x)
  {
    df3_three_variable z;
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
  df3_three_variable exp(const df3_three_variable& x)
  {
    df3_three_variable z;
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
  df3_three_variable inv(const df3_three_variable& x)
  {
    df3_three_variable z;
    double xinv=1.0/(*x.get_u());
    *z.get_u()=xinv;
    double zp=-xinv*xinv;
    double zp2=-2.0*zp*xinv;
    double zp3=-3.0*zp2*xinv;

    set_derivatives(z,x,xinv,zp,zp2,zp3);

    return z;
  }
/**
Assignment operator sets values from _v to df3_three_variable.
*/
df3_three_variable& df3_three_variable::operator=(const df3_three_variable& _v)
{
  *get_u() =  *_v.get_u();
  *get_u_x() = *_v.get_u_x();
  *get_u_y() = *_v.get_u_y();
  *get_u_z() = *_v.get_u_z();
  *get_u_xx() = *_v.get_u_xx();
  *get_u_xy() = *_v.get_u_xy();
  *get_u_xz() = *_v.get_u_xz();
  *get_u_yy() = *_v.get_u_yy();
  *get_u_yz() = *_v.get_u_yz();
  *get_u_zz() = *_v.get_u_zz();
  *get_u_xxx() = *_v.get_u_xxx();
  *get_u_xxy() = *_v.get_u_xxy();
  *get_u_xxz() = *_v.get_u_xxz();
  *get_u_xyy() = *_v.get_u_xyy();
  *get_u_xyz() = *_v.get_u_xyz();
  *get_u_xzz() = *_v.get_u_xzz();
  *get_u_yyy() = *_v.get_u_yyy();
  *get_u_yyz() = *_v.get_u_yyz();
  *get_u_yzz() = *_v.get_u_yzz();
  *get_u_zzz() = *_v.get_u_zzz();

  return *this;
}
/**
 * Description not yet available.
 * \param
 */
  df3_three_variable& df3_three_variable::operator = (double x)
  {
    *get_u() =x;
    *get_u_x() =0.0;
    *get_u_y() =0.0;
    *get_u_z() =0.0;
    *get_u_xx() =0.0;
    *get_u_xy() =0.0;
    *get_u_xz() =0.0;
    *get_u_yy() =0.0;
    *get_u_yz() =0.0;
    *get_u_zz() =0.0;
    *get_u_xxx() =0.0;
    *get_u_xxy() =0.0;
    *get_u_xxz() =0.0;
    *get_u_xyy() =0.0;
    *get_u_xyz() =0.0;
    *get_u_xzz() =0.0;
    *get_u_yyy() =0.0;
    *get_u_yyz() =0.0;
    *get_u_yzz() =0.0;
    *get_u_zzz() =0.0;

    return *this;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator * (const df3_three_variable& x,
    const df3_three_variable& y)
  {
    df3_three_variable z;
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
  df3_three_variable operator * (double x,
    const df3_three_variable& v)
  {
    df3_three_variable z;

    *z.get_u() = x * *v.get_u();
    *z.get_u_x() = x * *v.get_u_x();
    *z.get_u_y() = x * *v.get_u_y();
    *z.get_u_z() = x * *v.get_u_z();
    *z.get_u_xx() = x * *v.get_u_xx();
    *z.get_u_xy() = x * *v.get_u_xy();
    *z.get_u_xz() = x * *v.get_u_xz();
    *z.get_u_yy() = x * *v.get_u_yy();
    *z.get_u_yz() = x * *v.get_u_yz();
    *z.get_u_zz() = x * *v.get_u_zz();
    *z.get_u_xxx() = x * *v.get_u_xxx();
    *z.get_u_xxy() = x * *v.get_u_xxy();
    *z.get_u_xxz() = x * *v.get_u_xxz();
    *z.get_u_xyy() = x * *v.get_u_xyy();
    *z.get_u_xyz() = x * *v.get_u_xyz();
    *z.get_u_xzz() = x * *v.get_u_xzz();
    *z.get_u_yyy() = x * *v.get_u_yyy();
    *z.get_u_yyz() = x * *v.get_u_yyz();
    *z.get_u_yzz() = x * *v.get_u_yzz();
    *z.get_u_zzz() = x * *v.get_u_zzz();

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable fabs(const df3_three_variable& v)
  {
    df3_three_variable z;
    if (value(v)>=0)
    {
      *z.get_u() = *v.get_u();
      *z.get_u_x() = *v.get_u_x();
      *z.get_u_y() = *v.get_u_y();
      *z.get_u_z() = *v.get_u_z();
      *z.get_u_xx() = *v.get_u_xx();
      *z.get_u_xy() = *v.get_u_xy();
      *z.get_u_xz() = *v.get_u_xz();
      *z.get_u_yy() = *v.get_u_yy();
      *z.get_u_yz() = *v.get_u_yz();
      *z.get_u_zz() = *v.get_u_zz();
      *z.get_u_xxx() = *v.get_u_xxx();
      *z.get_u_xxy() = *v.get_u_xxy();
      *z.get_u_xxz() = *v.get_u_xxz();
      *z.get_u_xyy() = *v.get_u_xyy();
      *z.get_u_xyz() = *v.get_u_xyz();
      *z.get_u_xzz() = *v.get_u_xzz();
      *z.get_u_yyy() = *v.get_u_yyy();
      *z.get_u_yyz() = *v.get_u_yyz();
      *z.get_u_yzz() = *v.get_u_yzz();
      *z.get_u_zzz() = *v.get_u_zzz();
    }
    else
    {
      *z.get_u() = -*v.get_u();
      *z.get_u_x() = -*v.get_u_x();
      *z.get_u_y() = -*v.get_u_y();
      *z.get_u_z() = -*v.get_u_z();
      *z.get_u_xx() = -*v.get_u_xx();
      *z.get_u_xy() = -*v.get_u_xy();
      *z.get_u_xz() = -*v.get_u_xz();
      *z.get_u_yy() = -*v.get_u_yy();
      *z.get_u_yz() = -*v.get_u_yz();
      *z.get_u_zz() = -*v.get_u_zz();
      *z.get_u_xxx() = -*v.get_u_xxx();
      *z.get_u_xxy() = -*v.get_u_xxy();
      *z.get_u_xxz() = -*v.get_u_xxz();
      *z.get_u_xyy() = -*v.get_u_xyy();
      *z.get_u_xyz() = -*v.get_u_xyz();
      *z.get_u_xzz() = -*v.get_u_xzz();
      *z.get_u_yyy() = -*v.get_u_yyy();
      *z.get_u_yyz() = -*v.get_u_yyz();
      *z.get_u_yzz() = -*v.get_u_yzz();
      *z.get_u_zzz() = -*v.get_u_zzz();
    }

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator * (const df3_three_variable& v,
    double x)
  {
    df3_three_variable z;

    *z.get_u() = x * *v.get_u();
    *z.get_u_x() = x * *v.get_u_x();
    *z.get_u_y() = x * *v.get_u_y();
    *z.get_u_z() = x * *v.get_u_z();
    *z.get_u_xx() = x * *v.get_u_xx();
    *z.get_u_xy() = x * *v.get_u_xy();
    *z.get_u_xz() = x * *v.get_u_xz();
    *z.get_u_yy() = x * *v.get_u_yy();
    *z.get_u_yz() = x * *v.get_u_yz();
    *z.get_u_zz() = x * *v.get_u_zz();
    *z.get_u_xxx() = x * *v.get_u_xxx();
    *z.get_u_xxy() = x * *v.get_u_xxy();
    *z.get_u_xxz() = x * *v.get_u_xxz();
    *z.get_u_xyy() = x * *v.get_u_xyy();
    *z.get_u_xyz() = x * *v.get_u_xyz();
    *z.get_u_xzz() = x * *v.get_u_xzz();
    *z.get_u_yyy() = x * *v.get_u_yyy();
    *z.get_u_yyz() = x * *v.get_u_yyz();
    *z.get_u_yzz() = x * *v.get_u_yzz();
    *z.get_u_zzz() = x * *v.get_u_zzz();

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator / (const df3_three_variable& x,
    double y)
  {
    double u=1/y;
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator / (const df3_three_variable& x,
    const df3_three_variable& y)
  {
    df3_three_variable u=inv(y);
    return x*u;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator / (const double x,
    const df3_three_variable& y)
  {
    df3_three_variable u=inv(y);
    return x*u;
  }

 /*
  df3_three_variable operator / (const df3_three_variable& x,
    const df3_three_variable& y)
  {
    df3_three_variable z;
    double yinv =  1.0 / (*y.get_u());
    double yinv2 = yinv * yinv;
    double yinv3 = yinv * yinv2;
    doubl yd = *y.get_udot();

    // *z.get_u() = *x.get_u() /  *y.get_u();
    *z.get_u() = *x.get_u() * yinv;

    *z.get_udot() =  - (*x.get_u()) * yinv2 * yd
                  + *x.get_udot() * yinv;

    *z.get_udot2() = *x.get_udot2() * yinv
                   - 2.0 * *x.get_udot() * yd * yinv2
                   + 2.0 * *x.get_u() * yinv3  * yd *yd
                   -  *x.get_u() * yinv2 * y.get_udot2();

    *z.get_udot3() = *x.get_udot3() * yinv
                   + 3.0 * *x.get_udot2() * *y.get_udot()
                   + 3.0 * *x.get_udot() * *y.get_udot2()
                   +  *x.get_u() * *y.get_udot3();
  }
 */

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator + (const double x,const df3_three_variable& v)
  {
    df3_three_variable z;
    *z.get_u() = x + *v.get_u();
    *z.get_u_x() = *v.get_u_x();
    *z.get_u_y() = *v.get_u_y();
    *z.get_u_z() = *v.get_u_z();
    *z.get_u_xx() = *v.get_u_xx();
    *z.get_u_xy() = *v.get_u_xy();
    *z.get_u_xz() = *v.get_u_xz();
    *z.get_u_yy() = *v.get_u_yy();
    *z.get_u_yz() = *v.get_u_yz();
    *z.get_u_zz() = *v.get_u_zz();
    *z.get_u_xxx() = *v.get_u_xxx();
    *z.get_u_xxy() = *v.get_u_xxy();
    *z.get_u_xxz() = *v.get_u_xxz();
    *z.get_u_xyy() = *v.get_u_xyy();
    *z.get_u_xyz() = *v.get_u_xyz();
    *z.get_u_xzz() = *v.get_u_xzz();
    *z.get_u_yyy() = *v.get_u_yyy();
    *z.get_u_yyz() = *v.get_u_yyz();
    *z.get_u_yzz() = *v.get_u_yzz();
    *z.get_u_zzz() = *v.get_u_zzz();

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator + (const df3_three_variable& v,const double x)
  {
    df3_three_variable z;

    *z.get_u() = x + *v.get_u();
    *z.get_u_x() = *v.get_u_x();
    *z.get_u_y() = *v.get_u_y();
    *z.get_u_z() = *v.get_u_z();
    *z.get_u_xx() = *v.get_u_xx();
    *z.get_u_xy() = *v.get_u_xy();
    *z.get_u_xz() = *v.get_u_xz();
    *z.get_u_yy() = *v.get_u_yy();
    *z.get_u_yz() = *v.get_u_yz();
    *z.get_u_zz() = *v.get_u_zz();
    *z.get_u_xxx() = *v.get_u_xxx();
    *z.get_u_xxy() = *v.get_u_xxy();
    *z.get_u_xxz() = *v.get_u_xxz();
    *z.get_u_xyy() = *v.get_u_xyy();
    *z.get_u_xyz() = *v.get_u_xyz();
    *z.get_u_xzz() = *v.get_u_xzz();
    *z.get_u_yyy() = *v.get_u_yyy();
    *z.get_u_yyz() = *v.get_u_yyz();
    *z.get_u_yzz() = *v.get_u_yzz();
    *z.get_u_zzz() = *v.get_u_zzz();



    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator + (const df3_three_variable& x,
    const df3_three_variable& y)
  {
    df3_three_variable z;
    *z.get_u() = *x.get_u() + *y.get_u();
    *z.get_u_x() = *x.get_u_x() + *y.get_u_x();
    *z.get_u_z() = *x.get_u_z() + *y.get_u_z();
    *z.get_u_y() = *x.get_u_y()+*y.get_u_y();
    *z.get_u_xx() = *x.get_u_xx()+ *y.get_u_xx();
    *z.get_u_xy() = *x.get_u_xy()+ *y.get_u_xy();
    *z.get_u_xz() = *x.get_u_xz()+ *y.get_u_xz();
    *z.get_u_yy() = *x.get_u_yy()+ *y.get_u_yy();
    *z.get_u_yz() = *x.get_u_yz()+ *y.get_u_yz();
    *z.get_u_zz() = *x.get_u_zz()+ *y.get_u_zz();
    *z.get_u_xxx() = *x.get_u_xxx()+ *y.get_u_xxx();
    *z.get_u_xxy() = *x.get_u_xxy()+ *y.get_u_xxy();
    *z.get_u_xxz() = *x.get_u_xxz()+ *y.get_u_xxz();
    *z.get_u_xyy() = *x.get_u_xyy()+ *y.get_u_xyy();
    *z.get_u_xyz() = *x.get_u_xyz()+ *y.get_u_xyz();
    *z.get_u_xzz() = *x.get_u_xzz()+ *y.get_u_xzz();
    *z.get_u_yyy() = *x.get_u_yyy()+ *y.get_u_yyy();
    *z.get_u_yyz() = *x.get_u_yyz()+ *y.get_u_yyz();
    *z.get_u_yzz() = *x.get_u_yzz()+ *y.get_u_yzz();
    *z.get_u_zzz() = *x.get_u_zzz()+ *y.get_u_zzz();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator - (const df3_three_variable& x,
    const df3_three_variable& y)
  {
    df3_three_variable z;
    *z.get_u() = *x.get_u() - *y.get_u();
    *z.get_u_x() = *x.get_u_x() - *y.get_u_x();
    *z.get_u_z() = *x.get_u_z() - *y.get_u_z();
    *z.get_u_y() = *x.get_u_y() - *y.get_u_y();
    *z.get_u_xx() = *x.get_u_xx() - *y.get_u_xx();
    *z.get_u_xy() = *x.get_u_xy() - *y.get_u_xy();
    *z.get_u_xz() = *x.get_u_xz() - *y.get_u_xz();
    *z.get_u_yy() = *x.get_u_yy() - *y.get_u_yy();
    *z.get_u_yz() = *x.get_u_yz() - *y.get_u_yz();
    *z.get_u_zz() = *x.get_u_zz() - *y.get_u_zz();
    *z.get_u_xxx() = *x.get_u_xxx() - *y.get_u_xxx();
    *z.get_u_xxy() = *x.get_u_xxy() - *y.get_u_xxy();
    *z.get_u_xxz() = *x.get_u_xxz() - *y.get_u_xxz();
    *z.get_u_xyy() = *x.get_u_xyy() - *y.get_u_xyy();
    *z.get_u_xyz() = *x.get_u_xyz() - *y.get_u_xyz();
    *z.get_u_xzz() = *x.get_u_xzz() - *y.get_u_xzz();
    *z.get_u_yyy() = *x.get_u_yyy() - *y.get_u_yyy();
    *z.get_u_yyz() = *x.get_u_yyz() - *y.get_u_yyz();
    *z.get_u_yzz() = *x.get_u_yzz() - *y.get_u_yzz();
    *z.get_u_zzz() = *x.get_u_zzz() - *y.get_u_zzz();
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator - (double x,
    const df3_three_variable& v)
  {
    df3_three_variable z;

    *z.get_u() = x - *v.get_u();
    *z.get_u_x() = -*v.get_u_x();
    *z.get_u_y() = -*v.get_u_y();
    *z.get_u_z() = -*v.get_u_z();
    *z.get_u_xx() = -*v.get_u_xx();
    *z.get_u_xy() = -*v.get_u_xy();
    *z.get_u_xz() = -*v.get_u_xz();
    *z.get_u_yy() = -*v.get_u_yy();
    *z.get_u_yz() = -*v.get_u_yz();
    *z.get_u_zz() = -*v.get_u_zz();
    *z.get_u_xxx() = -*v.get_u_xxx();
    *z.get_u_xxy() = -*v.get_u_xxy();
    *z.get_u_xxz() = -*v.get_u_xxz();
    *z.get_u_xyy() = -*v.get_u_xyy();
    *z.get_u_xyz() = -*v.get_u_xyz();
    *z.get_u_xzz() = -*v.get_u_xzz();
    *z.get_u_yyy() = -*v.get_u_yyy();
    *z.get_u_yyz() = -*v.get_u_yyz();
    *z.get_u_yzz() = -*v.get_u_yzz();
    *z.get_u_zzz() = -*v.get_u_zzz();

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df3_three_variable operator - (const df3_three_variable& v,
    double y)
  {
    df3_three_variable z;

    *z.get_u() =  *v.get_u()-y;
    *z.get_u_x() = *v.get_u_x();
    *z.get_u_y() = *v.get_u_y();
    *z.get_u_z() = *v.get_u_z();
    *z.get_u_xx() = *v.get_u_xx();
    *z.get_u_xy() = *v.get_u_xy();
    *z.get_u_xz() = *v.get_u_xz();
    *z.get_u_yy() = *v.get_u_yy();
    *z.get_u_yz() = *v.get_u_yz();
    *z.get_u_zz() = *v.get_u_zz();
    *z.get_u_xxx() = *v.get_u_xxx();
    *z.get_u_xxy() = *v.get_u_xxy();
    *z.get_u_xxz() = *v.get_u_xxz();
    *z.get_u_xyy() = *v.get_u_xyy();
    *z.get_u_xyz() = *v.get_u_xyz();
    *z.get_u_xzz() = *v.get_u_xzz();
    *z.get_u_yyy() = *v.get_u_yyy();
    *z.get_u_yyz() = *v.get_u_yyz();
    *z.get_u_yzz() = *v.get_u_yzz();
    *z.get_u_zzz() = *v.get_u_zzz();

    return z;
  }
/**
Destructor
*/
init_df3_three_variable::~init_df3_three_variable()
{
  num_local_ind_var--;
  if (num_local_ind_var<0)
  {
    cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  if (num_local_ind_var==0)
  {
    num_ind_var=0;
  }
}
/**
Constructor for df1b2variable.
*/
  init_df3_three_variable::init_df3_three_variable(const df1b2variable& _v)
  {
    ADUNCONST(df1b2variable,v)
    if (num_local_ind_var>2)
    {
      cerr << "can only have 3 independent_variables in df3_three_variable"
       " function" << endl;
      ad_exit(1);
    }
    ind_var[num_ind_var++]=&v;
    num_local_ind_var++;
    *get_u() =  *v.get_u();
    *get_u_x() = 0.0;
    *get_u_y() = 0.0;
    *get_u_z() = 0.0;
    switch(num_local_ind_var)
    {
    case 1:
      *get_u_x() = 1.0;
      break;
    case 2:
      *get_u_y() = 1.0;
      break;
    case 3:
      *get_u_z() = 1.0;
      break;
    default:
      cerr << "illegal num_ind_var value of " << num_ind_var
           << " in  df3_three_variable function" << endl;
      ad_exit(1);
    }
    *get_u_xx() = 0.0;
    *get_u_xy() = 0.0;
    *get_u_xz() = 0.0;
    *get_u_yy() = 0.0;
    *get_u_yz() = 0.0;
    *get_u_zz() = 0.0;
    *get_u_xxx() = 0.0;
    *get_u_xxy() = 0.0;
    *get_u_xxz() = 0.0;
    *get_u_xyy() = 0.0;
    *get_u_xyz() = 0.0;
    *get_u_xzz() = 0.0;
    *get_u_yyy() = 0.0;
    *get_u_yyz() = 0.0;
    *get_u_yzz() = 0.0;
    *get_u_zzz() = 0.0;
  }

/**
 * Description not yet available.
 * \param
 */
  init_df3_three_variable::init_df3_three_variable(double v)
  {
    if (num_local_ind_var>2)
    {
      cerr << "can only have 3 independent_variables in df3_three_variable"
       " function" << endl;
      ad_exit(1);
    }
    num_local_ind_var++;
    *get_u() =  v;
    *get_u_x() = 0.0;
    *get_u_y() = 0.0;
    *get_u_z() = 0.0;
    switch(num_local_ind_var)
    {
    case 1:
      *get_u_x() = 1.0;
      break;
    case 2:
      *get_u_y() = 1.0;
      break;
    case 3:
      *get_u_z() = 1.0;
      break;
    default:
      cerr << "illegal num_ind_var value of " << num_ind_var
           << " in  df3_three_variable function" << endl;
      ad_exit(1);
    }
    *get_u_xx() = 0.0;
    *get_u_xy() = 0.0;
    *get_u_xz() = 0.0;
    *get_u_yy() = 0.0;
    *get_u_yz() = 0.0;
    *get_u_zz() = 0.0;
    *get_u_xxx() = 0.0;
    *get_u_xxy() = 0.0;
    *get_u_xxz() = 0.0;
    *get_u_xyy() = 0.0;
    *get_u_xyz() = 0.0;
    *get_u_xzz() = 0.0;
    *get_u_yyy() = 0.0;
    *get_u_yyz() = 0.0;
    *get_u_yzz() = 0.0;
    *get_u_zzz() = 0.0;
  }
/**
 * Description not yet available.
 * \param
 */
df3_three_matrix choleski_decomp(const df3_three_matrix& MM)
{
  // kludge to deal with constantness
  df3_three_matrix & M= (df3_three_matrix &) MM;
  int rmin=M.indexmin();
  int cmin=M(rmin).indexmin();
  int rmax=M.indexmax();
  int cmax=M(rmin).indexmax();
  if (rmin !=1 || cmin !=1)
  {
    cerr << "minimum row and column inidices must equal 1 in "
      "df1b2matrix choleski_decomp(const df3_three_atrix& MM)"
         << endl;
    ad_exit(1);
  }
  if (rmax !=cmax)
  {
    cerr << "Error in df1b2matrix choleski_decomp(const df3_three_matrix& MM)"
      " Matrix not square" << endl;
    ad_exit(1);
  }

  int n=rmax-rmin+1;
  df3_three_matrix L(1,n,1,n);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  df3_three_variable tmp;

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
