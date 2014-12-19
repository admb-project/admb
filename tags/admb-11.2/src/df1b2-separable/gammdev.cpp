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
#include "df1b2fun.h"
  df3_two_variable cumd_exponential(const df3_two_variable& x,
    const df3_two_variable& a);

df3_two_variable cumd_cauchy(const df3_two_variable& x,
  const df3_two_variable& a);

  df1b2variable inv_cumd_gamma(const df1b2variable& _y,const df1b2variable& _a);
  double inv_cumd_gamma(double y,double _a);

  df3_two_variable cumd_gamma(const df3_two_variable& x,
    const df3_two_variable& a);

/**
 * Description not yet available.
 * \param
 */
  df1b2variable gamma_deviate(const df1b2variable& _x,const df1b2variable& _a)
  {
    df1b2variable& x= (df1b2variable&)(_x);
    df1b2variable& a= (df1b2variable&)(_a);

    df1b2variable y=cumd_norm(x);
    y=.9999*y+.00005;

    //df1b2variable z=inv_cumd_gamma(y,a);
    df1b2variable z=inv_cumd_gamma(y,a);

    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1b2variable inv_cumd_gamma(const df1b2variable& _y,const df1b2variable& _a)
  {
    df1b2variable& y= (df1b2variable&)(_y);
    df1b2variable& a= (df1b2variable&)(_a);
    // get the inverse values
    double x=inv_cumd_gamma(value(y),value(_a));

    init_df3_two_variable xx(value(x));
    init_df3_two_variable aa(value(a));
    //init_df3_two_variable xx(1.0);
    //init_df3_two_variable aa(2.0);
    *xx.get_u_x()=1.0;
    *aa.get_u_y()=1.0;

    df3_two_variable z=cumd_gamma(xx,aa);

    // now use the derivatives of z to get the
    //derivatives of x wrt y,a and save them

    //double ca=value(a);

    double F_x=1.0/(*z.get_u_x());

    double F_y=-F_x* *z.get_u_y();
    double F_xx=-F_x* *z.get_u_xx()/square(*z.get_u_x());

    double F_xy=-(F_xx * *z.get_u_x() * *z.get_u_y() + F_x * *z.get_u_xy())/
                *z.get_u_x();

    double F_yy=-(F_xx * square(*z.get_u_y())
                +2.0* F_xy* *z.get_u_y()
                +F_x * *z.get_u_yy());

    double F_xxx=-(F_x* *z.get_u_xxx()
                +3.0*F_xx* *z.get_u_x() * *z.get_u_xx())
                /cube(*z.get_u_x());

    double F_xxy=-(F_xxx * square(*z.get_u_x())* *z.get_u_y()
                 + 2.0*F_xx* *z.get_u_x()* *z.get_u_xy()
                 + F_xx* *z.get_u_xx() * *z.get_u_y()
                 + F_xy * *z.get_u_xx()
                 + F_x * *z.get_u_xxy())/
                 square(*z.get_u_x());

    double F_xyy=-(F_xxx* *z.get_u_x() *square(*z.get_u_y())
                 +2.0* F_xx * *z.get_u_xy() * *z.get_u_y()
                 +2.0*F_xxy * *z.get_u_x() * *z.get_u_y()
                 + 2.0*F_xy * *z.get_u_xy()
                 + F_xx * *z.get_u_x() * *z.get_u_yy()
                 + F_x * *z.get_u_xyy())/
                 *z.get_u_x();
     double F_yyy=-(F_xxx*cube(*z.get_u_y())+
                 +3.0*F_xxy*square(*z.get_u_y())
                 +3.0*F_xx* *z.get_u_y() * *z.get_u_yy()
                 +3.0*F_xy* *z.get_u_yy()
                 +3.0*F_xyy * *z.get_u_y()
                 +F_x * *z.get_u_yyy());

     df1b2variable zz;
     double * xd=_y.get_u_dot();
     double * yd=_a.get_u_dot();
     double * zd=zz.get_u_dot();
     *zz.get_u()=x;

     for (unsigned int i=0;i<df1b2variable::nvar;i++)
     {
       *zd++ = F_x * *xd++ + F_y * *yd++;
     }
     if (!df1b2_gradlist::no_derivatives)
     {
       f1b2gradlist->write_pass1(&_y,&_a,&zz,
        F_x,F_y,
        F_xx,F_xy,F_yy,
        F_xxx,F_xxy,F_xyy,F_yyy);
     }
     return zz;
  }
