/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>

dvar_vector spline(const dvector &x,const dvar_vector&y,double yp1,double ypn);
dvar_vector spline(const dvector &x,const dvar_vector&y,dvariable yp1,
  dvariable ypn);
dvariable spline_cubic_val2(int n, _CONST dvector& t, const prevariable tval,
  _CONST dvar_vector& y, _CONST dvar_vector& ypp);
dvariable spline_cubic_val(int n, _CONST dvector& t, double tval,
  _CONST dvar_vector& y, _CONST dvar_vector& ypp);

dvar_vector spline_cubic_set (int n,_CONST dvector& t,_CONST dvar_vector& y,
  int ibcbeg, dvariable ybcbeg, int ibcend, dvariable ybcend );


/** \ingroup cub_spline
 *  Cubic spline interpolation.
 *
 * \param _xa array of abscissa
 * \param _ya array of corresponding values \f$y_i=f(x_i)\f$
 * \param _y2a array of 2nd derivatives computed from dvar_vector spline()
 * \param x the input coordinate to be used in the interpolation
 * \return a cubic-spline interpolation to \f$f(x)\f$
*/
  dvariable splint(const dvector& _xa,const dvar_vector& _ya,
    const dvar_vector& _y2a,double x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable ret = spline_cubic_val(_xa.size(), _xa, x, _ya, _y2a);
    RETURN_ARRAYS_DECREMENT();
    return ret;
  }

/** \ingroup cub_spline
 *  Cubic spline interpolation.
 *
 * \param _xa array of abscissa
 * \param _ya array of corresponding values \f$y_i=f(x_i)\f$
 * \param _y2a array of 2nd derivatives computed from dvar_vector spline()
 * \param x the input coordinate to be used in the interpolation
 * \return a cubic-spline interpolation to \f$f(x)\f$
*/
  dvariable splint(const dvector& _xa,const dvar_vector& _ya,
    const dvar_vector& _y2a, const prevariable& _x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable ret = spline_cubic_val2(_xa.size(), _xa, _x, _ya, _y2a);
    RETURN_ARRAYS_DECREMENT();
    return ret;
  }



vcubic_spline_function::vcubic_spline_function(const dvector & _x,
  const dvar_vector& _y,dvariable yp1,dvariable ypn) : x(_x) , y(_y)
{
  y2.allocate(x);
  y2=spline(x,y,yp1,ypn);
}

vcubic_spline_function::vcubic_spline_function(const dvector & _x,
  const dvar_vector& _y,double yp1,double ypn) : x(_x) , y(_y)
{
  y2.allocate(x);
  y2=spline(x,y,yp1,ypn);
}

dvariable vcubic_spline_function::operator () (double u)
{
  // need to deal with u<x(1) or u>x(2)
  return splint(x,y,y2,u);
}

dvar_vector vcubic_spline_function::operator () (const dvector& u)
{
  int mmin=u.indexmin();
  int mmax=u.indexmax();
  dvar_vector z(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    z(i)=splint(x,y,y2,u(i));
  }
  return z;
}

dvar_vector vcubic_spline_function::operator () (const dvar_vector& u)
{
  int mmin=u.indexmin();
  int mmax=u.indexmax();
  dvar_vector z(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    z(i)=splint(x,y,y2,u(i));
  }
  return z;
}


/** \ingroup cub_spline
 *  Cubic spline interpolation.
 *
 * \param _x array of abscissa
 * \param _y array of corresponding values \f$y_i=f(x_i)\f$
 * \param yp1 value of the first derivative of \f$f\f$ at the left
 *        end point
 * \param ypn value of the first derivative of \f$f\f$ at the right
 *        end point
 * \return an array containing the second derivatives
*/
  dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
    dvariable ypn)
  {
    int ibcbeg, ibcend;
    dvariable ybcbeg, ybcend;
    dvector x = _x;
    x.shift(0);
    dvar_vector y = _y;
    y.shift(0);
    if(value(yp1) > 0.99e30 )
    {
      ibcbeg = 2;
      ybcbeg = 0.0;
    }
    else
    {
      ibcbeg = 1;
      ybcbeg = yp1;
    }
    if(value(ypn) > 0.99e30 )
    {
      ibcend = 2;
      ybcend = 0.0;
    }
    else
    {
      ibcend = 1;
      ybcend = ypn;
    }

    dvar_vector ret = spline_cubic_set(x.size(), x, y, ibcbeg, ybcbeg, ibcend, ybcend);
    ret.shift(_x.indexmin());
    return ret;
  }

/*dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
  dvariable ypn)
{
  RETURN_ARRAYS_INCREMENT();	
  dvector& x=(dvector&) _x;
  dvar_vector& y=(dvar_vector&) _y;
  int orig_min=x.indexmin();
  x.shift(1);
  y.shift(1);
  // need to check that x is monotone increasing;
  if  ( x.indexmax() != y.indexmax() )
  {
    cerr << " Incompatible bounds in input to spline" << endl;
  }
  int n=x.indexmax();
  dvar_vector y2(1,n);
  int i,k;
  dvariable  p,qn,sig,un;

  dvar_vector u(1,n-1);
  if (yp1 > 0.99e30)
  {
    y2[1]=u[1]=0.0;
  }
  else
  {
    y2[1] = -0.5;
    u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
  }
  for (i=2;i<=n-1;i++)
  {
    sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
    p=sig*y2[i-1]+2.0;
    y2[i]=(sig-1.0)/p;
    u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
    u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
  }
  if (ypn > 0.99e30)
  {
    qn=un=0.0;
  }
  else 
  {
    qn=0.5;
    un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
  }
  y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
  for (k=n-1;k>=1;k--)
  {
    y2[k]=y2[k]*y2[k+1]+u[k];
  }
  x.shift(orig_min);
  y.shift(orig_min);
  y2.shift(orig_min);
  RETURN_ARRAYS_DECREMENT();	
  return y2;
}*/

/** \ingroup cub_spline
 *  Cubic spline interpolation.
 *
 * \param _x array of abscissa
 * \param _y array of corresponding values \f$y_i=f(x_i)\f$
 * \param yp1 value of the first derivative of \f$f\f$ at the left
 *        end point
 * \param ypn value of the first derivative of \f$f\f$ at the right
 *        end point
 * \return an array containing the second derivatives
*/
  dvar_vector spline(const dvector &_x,const dvar_vector&_y,double yp1,
    double ypn)
  {
    int ibcbeg, ibcend;
    dvariable ybcbeg, ybcend;
    dvector x = _x;
    x.shift(0);
    dvar_vector y = _y;
    y.shift(0);
    if(yp1 > 0.99e30 )
    {
      ibcbeg = 2;
      ybcbeg = 0.0;
    }
    else
    {
      ibcbeg = 1;
      ybcbeg = yp1;
    }
    if(ypn > 0.99e30 )
    {
      ibcend = 2;
      ybcend = 0.0;
    }
    else
    {
      ibcend = 1;
      ybcend = ypn;
    }

    dvar_vector ret = spline_cubic_set(x.size(), x, y, ibcbeg, ybcbeg, ibcend, ybcend);
    ret.shift(_x.indexmin());
    return ret;
  }

/*dvar_vector spline(const dvector &_x,const dvar_vector&_y,double yp1,
  double ypn)
{
  RETURN_ARRAYS_INCREMENT();	
  dvector& x=(dvector&) _x;
  dvar_vector& y=(dvar_vector&) _y;
  int orig_min=x.indexmin();
  x.shift(1);
  y.shift(1);
  // need to check that x is monotone increasing;
  if  ( x.indexmax() != y.indexmax() )
  {
    cerr << " Incompatible bounds in input to spline" << endl;
  }
  int n=x.indexmax();
  dvar_vector y2(1,n);
  int i,k;
  dvariable  p,qn,sig,un;

  dvar_vector u(1,n-1);
  if (yp1 > 0.99e30)
  {
    y2[1]=u[1]=0.0;
  }
  else
  {
    y2[1] = -0.5;
    u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
  }
  for (i=2;i<=n-1;i++)
  {
    sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
    p=sig*y2[i-1]+2.0;
    y2[i]=(sig-1.0)/p;
    u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
    u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
  }
  if (ypn > 0.99e30)
  {
    qn=un=0.0;
  }
  else 
  {
    qn=0.5;
    un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
  }
  y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
  for (k=n-1;k>=1;k--)
  {
    y2[k]=y2[k]*y2[k+1]+u[k];
  }
  x.shift(orig_min);
  y.shift(orig_min);
  y2.shift(orig_min);
  RETURN_ARRAYS_DECREMENT();	
  return y2;
}*/

/** \ingroup cub_spline
 *  Cubic spline interpolation.
 *
 * \param _x array of abscissa
 * \param _y array of corresponding values \f$y_i=f(x_i)\f$
 * \param yp1 value of the first derivative of \f$f\f$ at the left
 *        end point
 * \param ypn value of the first derivative of \f$f\f$ at the right
 *        end point
 * \return an array containing the second derivatives
*/
  dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
    double ypn)
  {
    int ibcbeg, ibcend;
    dvariable ybcbeg, ybcend;
    dvector x = _x;
    x.shift(0);
    dvar_vector y = _y;
    y.shift(0);
    if(value(yp1) > 0.99e30 )
    {
      ibcbeg = 2;
      ybcbeg = 0.0;
    }
    else
    {
      ibcbeg = 1;
      ybcbeg = yp1;
    }
    if(ypn > 0.99e30 )
    {
      ibcend = 2;
      ybcend = 0.0;
    }
    else
    {
      ibcend = 1;
      ybcend = ypn;
    }

    dvar_vector ret = spline_cubic_set(x.size(), x, y, ibcbeg, ybcbeg, ibcend, ybcend);
    ret.shift(_x.indexmin());
    return ret;
  }

/*dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
  double ypn)
{
  RETURN_ARRAYS_INCREMENT();	
  dvector& x=(dvector&) _x;
  dvar_vector& y=(dvar_vector&) _y;
  int orig_min=x.indexmin();
  x.shift(1);
  y.shift(1);
  // need to check that x is monotone increasing;
  if  ( x.indexmax() != y.indexmax() )
  {
    cerr << " Incompatible bounds in input to spline" << endl;
  }
  int n=x.indexmax();
  dvar_vector y2(1,n);
  int i,k;
  dvariable  p,qn,sig,un;

  dvar_vector u(1,n-1);
  if (yp1 > 0.99e30)
  {
    y2[1]=u[1]=0.0;
  }
  else
  {
    y2[1] = -0.5;
    u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
  }
  for (i=2;i<=n-1;i++)
  {
    sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
    p=sig*y2[i-1]+2.0;
    y2[i]=(sig-1.0)/p;
    u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
    u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
  }
  if (ypn > 0.99e30)
  {
    qn=un=0.0;
  }
  else 
  {
    qn=0.5;
    un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
  }
  y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
  for (k=n-1;k>=1;k--)
  {
    y2[k]=y2[k]*y2[k+1]+u[k];
  }
  x.shift(orig_min);
  y.shift(orig_min);
  y2.shift(orig_min);
  RETURN_ARRAYS_DECREMENT();	
  return y2;
}*/




/*dvariable splint(const dvector& _xa,const dvar_vector& _ya,
  const dvar_vector& _y2a,double x)
{
  RETURN_ARRAYS_INCREMENT();	
  dvector& xa=(dvector&) _xa;
  dvar_vector& ya=(dvar_vector&) _ya;
  dvar_vector& y2a=(dvar_vector&) _y2a;
  int orig_min=xa.indexmin();
  xa.shift(1);
  ya.shift(1);
  y2a.shift(1);
  dvariable y;
  int n = xa.indexmax();
  int klo,khi,k;
  dvariable h,b,a;

  klo=1;
  khi=n;
  while (khi-klo > 1) 
  {
    k=(khi+klo) >> 1;
    if (xa[k] > x) khi=k;
    else klo=k;
  }
  h=xa[khi]-xa[klo];
  a=(xa[khi]-x)/h;
  b=(x-xa[klo])/h;
  y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
  xa.shift(orig_min);
  ya.shift(orig_min);
  y2a.shift(orig_min);
  RETURN_ARRAYS_DECREMENT();	
  return y;
}*/



/*dvariable splint(const dvector& _xa,const dvar_vector& _ya,
  const dvar_vector& _y2a,const prevariable& _x)
{
  RETURN_ARRAYS_INCREMENT();	
  prevariable& x=(prevariable&)(_x);
  dvector& xa=(dvector&) _xa;
  dvar_vector& ya=(dvar_vector&) _ya;
  dvar_vector& y2a=(dvar_vector&) _y2a;
  int orig_min=xa.indexmin();
  xa.shift(1);
  ya.shift(1);
  y2a.shift(1);
  dvariable y;
  int n = xa.indexmax();
  int klo,khi,k;
  dvariable h,b,a;

  klo=1;
  khi=n;
  while (khi-klo > 1) 
  {
    k=(khi+klo) >> 1;
    if (xa[k] > x) khi=k;
    else klo=k;
  }
  h=xa[khi]-xa[klo];
  a=(xa[khi]-x)/h;
  b=(x-xa[klo])/h;
  dvariable a4=a*a*a*a;
  dvariable b4=b*b*b*b;
  y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
  dvariable y1=a*ya[klo]+b*ya[khi]+((cube(a)-a)*y2a[klo]+(cube(b)-b)*y2a[khi])*(h*h)/6.0;
  xa.shift(orig_min);
  ya.shift(orig_min);
  y2a.shift(orig_min);
  RETURN_ARRAYS_DECREMENT();	
  return y;
}*/




  //****************************************************************************80
  
  dvariable spline_cubic_val(int n, _CONST dvector& t, double tval,
    _CONST dvar_vector& y, _CONST dvar_vector& ypp)
  
  //****************************************************************************80
  //
  //  Purpose:
  //
  //    SPLINE_CUBIC_VAL evaluates a piecewise cubic spline at a point.
  //
  //  Discussion:
  //
  //    SPLINE_CUBIC_SET must have already been called to define the values of YPP.
  //
  //    For any point T in the interval T(IVAL), T(IVAL+1), the form of
  //    the spline is
  //
  //      SPL(T) = A
  //             + B * ( T - T(IVAL) )
  //             + C * ( T - T(IVAL) )**2
  //             + D * ( T - T(IVAL) )**3
  //
  //    Here:
  //      A = Y(IVAL)
  //      B = ( Y(IVAL+1) - Y(IVAL) ) / ( T(IVAL+1) - T(IVAL) )
  //        - ( YPP(IVAL+1) + 2 * YPP(IVAL) ) * ( T(IVAL+1) - T(IVAL) ) / 6
  //      C = YPP(IVAL) / 2
  //      D = ( YPP(IVAL+1) - YPP(IVAL) ) / ( 6 * ( T(IVAL+1) - T(IVAL) ) )
  //
  //  Licensing:
  //
  //    This code is distributed under the GNU LGPL license. 
  //
  //  Modified:
  //
  //    04 February 1999
  //
  //  Author:
  //
  //    John Burkardt
  //
  //  Modified By:
  //
  //    Derek Seiple (20 August 2010)
  //
  //  Parameters:
  //
  //    Input, int N, the number of knots.
  //
  //    Input, double Y[N], the data values at the knots.
  //
  //    Input, double T[N], the knot values.
  //
  //    Input, double TVAL, a point, typically between T[0] and T[N-1], at
  //    which the spline is to be evalulated.  If TVAL lies outside
  //    this range, extrapolation is used.
  //
  //    Input, double Y[N], the data values at the knots.
  //
  //    Input, double YPP[N], the second derivatives of the spline at
  //    the knots.
  //
  //    Output, double *YPVAL, the derivative of the spline at TVAL.
  //
  //    Output, double *YPPVAL, the second derivative of the spline at TVAL.
  //
  //    Output, double SPLINE_VAL, the value of the spline at TVAL.
  //
  {
    dvariable dt;
    dvariable h;
    int i;
    int ival;
    dvariable yval;
  //
  //  Determine the interval [ T(I), T(I+1) ] that contains TVAL.
  //  Values below T[0] or above T[N-1] use extrapolation.
  //
    ival = n - 2;
  
    for ( i = 0; i < n-1; i++ )
    {
      if ( tval < t[i+1] )
      {
        ival = i;
        break;
      }
    }
  //
  //  In the interval I, the polynomial is in terms of a normalized
  //  coordinate between 0 and 1.
  //
    dt = tval - t[ival];
    h = t[ival+1] - t[ival];
  
    yval = y[ival]
      + dt * ( ( y[ival+1] - y[ival] ) / h
             - ( ypp[ival+1] / 6.0 + ypp[ival] / 3.0 ) * h
      + dt * ( 0.5 * ypp[ival]
      + dt * ( ( ypp[ival+1] - ypp[ival] ) / ( 6.0 * h ) ) ) );
  
    /**ypval = ( y[ival+1] - y[ival] ) / h
      - ( ypp[ival+1] / 6.0 + ypp[ival] / 3.0 ) * h
      + dt * ( ypp[ival]
      + dt * ( 0.5 * ( ypp[ival+1] - ypp[ival] ) / h ) );
  
    *yppval = ypp[ival] + dt * ( ypp[ival+1] - ypp[ival] ) / h;*/
  
    return yval;
  }

  //****************************************************************************80
  
  dvariable spline_cubic_val2(int n, _CONST dvector& t, const prevariable tval,
    _CONST dvar_vector& y, _CONST dvar_vector& ypp)
  
  //****************************************************************************80
  //
  //  Purpose:
  //
  //    SPLINE_CUBIC_VAL evaluates a piecewise cubic spline at a point.
  //
  //  Discussion:
  //
  //    SPLINE_CUBIC_SET must have already been called to define the values of YPP.
  //
  //    For any point T in the interval T(IVAL), T(IVAL+1), the form of
  //    the spline is
  //
  //      SPL(T) = A
  //             + B * ( T - T(IVAL) )
  //             + C * ( T - T(IVAL) )**2
  //             + D * ( T - T(IVAL) )**3
  //
  //    Here:
  //      A = Y(IVAL)
  //      B = ( Y(IVAL+1) - Y(IVAL) ) / ( T(IVAL+1) - T(IVAL) )
  //        - ( YPP(IVAL+1) + 2 * YPP(IVAL) ) * ( T(IVAL+1) - T(IVAL) ) / 6
  //      C = YPP(IVAL) / 2
  //      D = ( YPP(IVAL+1) - YPP(IVAL) ) / ( 6 * ( T(IVAL+1) - T(IVAL) ) )
  //
  //  Licensing:
  //
  //    This code is distributed under the GNU LGPL license. 
  //
  //  Modified:
  //
  //    04 February 1999
  //
  //  Author:
  //
  //    John Burkardt
  //
  //  Modified By:
  //
  //    Derek Seiple (20 August 2010)
  //
  //  Parameters:
  //
  //    Input, int N, the number of knots.
  //
  //    Input, double Y[N], the data values at the knots.
  //
  //    Input, double T[N], the knot values.
  //
  //    Input, double TVAL, a point, typically between T[0] and T[N-1], at
  //    which the spline is to be evalulated.  If TVAL lies outside
  //    this range, extrapolation is used.
  //
  //    Input, double Y[N], the data values at the knots.
  //
  //    Input, double YPP[N], the second derivatives of the spline at
  //    the knots.
  //
  //    Output, double *YPVAL, the derivative of the spline at TVAL.
  //
  //    Output, double *YPPVAL, the second derivative of the spline at TVAL.
  //
  //    Output, double SPLINE_VAL, the value of the spline at TVAL.
  //
  {
    dvariable dt;
    dvariable h;
    int i;
    int ival;
    dvariable yval;
  //
  //  Determine the interval [ T(I), T(I+1) ] that contains TVAL.
  //  Values below T[0] or above T[N-1] use extrapolation.
  //
    ival = n - 2;
  
    for ( i = 0; i < n-1; i++ )
    {
      if ( tval < t[i+1] )
      {
        ival = i;
        break;
      }
    }
  //
  //  In the interval I, the polynomial is in terms of a normalized
  //  coordinate between 0 and 1.
  //
    dt = tval - t[ival];
    h = t[ival+1] - t[ival];
  
    yval = y[ival]
      + dt * ( ( y[ival+1] - y[ival] ) / h
             - ( ypp[ival+1] / 6.0 + ypp[ival] / 3.0 ) * h
      + dt * ( 0.5 * ypp[ival]
      + dt * ( ( ypp[ival+1] - ypp[ival] ) / ( 6.0 * h ) ) ) );
  
    /**ypval = ( y[ival+1] - y[ival] ) / h
      - ( ypp[ival+1] / 6.0 + ypp[ival] / 3.0 ) * h
      + dt * ( ypp[ival]
      + dt * ( 0.5 * ( ypp[ival+1] - ypp[ival] ) / h ) );
  
    *yppval = ypp[ival] + dt * ( ypp[ival+1] - ypp[ival] ) / h;*/
  
    return yval;
  }








  //****************************************************************************80
  
  dvar_vector d3_np_fs ( int n, _CONST dvar_vector& _a, _CONST dvar_vector& _b)
  
  //****************************************************************************80
  //
  //  Purpose:
  //
  //    D3_NP_FS factors and solves a D3 system.
  //
  //  Discussion:
  //
  //    The D3 storage format is used for a tridiagonal matrix.
  //    The superdiagonal is stored in entries (1,2:N), the diagonal in
  //    entries (2,1:N), and the subdiagonal in (3,1:N-1).  Thus, the
  //    original matrix is "collapsed" vertically into the array.
  //
  //    This algorithm requires that each diagonal entry be nonzero.
  //    It does not use pivoting, and so can fail on systems that
  //    are actually nonsingular.
  //
  //  Example:
  //
  //    Here is how a D3 matrix of order 5 would be stored:
  //
  //       *  A12 A23 A34 A45
  //      A11 A22 A33 A44 A55
  //      A21 A32 A43 A54  *
  //
  //  Licensing:
  //
  //    This code is distributed under the GNU LGPL license. 
  //
  //  Modified:
  //
  //    15 November 2003
  //
  //  Author:
  //
  //    John Burkardt
  //
  //  Modified By:
  //
  //    Derek Seiple (20 August 2010)
  //
  //  Parameters:
  //
  //    Input, int N, the order of the linear system.
  //
  //    Input/output, double A[3*N].
  //    On input, the nonzero diagonals of the linear system.
  //    On output, the data in these vectors has been overwritten
  //    by factorization information.
  //
  //    Input, double B[N], the right hand side.
  //
  //    Output, double D3_NP_FS[N], the solution of the linear system.
  //    This is NULL if there was an error because one of the diagonal
  //    entries was zero.
  //
  {
    ADUNCONST(dvar_vector,a)
    ADUNCONST(dvar_vector,b)
    int i;
    dvariable xmult;
  //
  //  Check.
  //
    for ( i = 0; i < n; i++ )
    {
      if ( a[1+i*3] == 0.0 )
      {
        return NULL;
      }
    }
    dvar_vector x(0,n-1);
  
    for ( i = 0; i < n; i++ )
    {
      x[i] = b[i];
    }
  
    for ( i = 1; i < n; i++ )
    {
      xmult = a[2+(i-1)*3] / a[1+(i-1)*3];
      a[1+i*3] = a[1+i*3] - xmult * a[0+i*3];
      x[i] = x[i] - xmult * x[i-1];
    }
  
    x[n-1] = x[n-1] / a[1+(n-1)*3];
    for ( i = n-2; 0 <= i; i-- )
    {
      x[i] = ( x[i] - a[0+(i+1)*3] * x[i+1] ) / a[1+i*3];
    }
  
    return x;
  }
  
  //****************************************************************************80
  
  dvar_vector spline_cubic_set (int n,_CONST dvector& t,_CONST dvar_vector& y,
    int ibcbeg, dvariable ybcbeg, int ibcend, dvariable ybcend )
  
  //****************************************************************************80
  //
  //  Purpose:
  //
  //    SPLINE_CUBIC_SET computes the second derivatives of a piecewise cubic spline.
  //
  //  Discussion:
  //
  //    For data interpolation, the user must call SPLINE_SET to determine
  //    the second derivative data, passing in the data to be interpolated,
  //    and the desired boundary conditions.
  //
  //    The data to be interpolated, plus the SPLINE_SET output, defines
  //    the spline.  The user may then call SPLINE_VAL to evaluate the
  //    spline at any point.
  //
  //    The cubic spline is a piecewise cubic polynomial.  The intervals
  //    are determined by the "knots" or abscissas of the data to be
  //    interpolated.  The cubic spline has continous first and second
  //    derivatives over the entire interval of interpolation.
  //
  //    For any point T in the interval T(IVAL), T(IVAL+1), the form of
  //    the spline is
  //
  //      SPL(T) = A(IVAL)
  //             + B(IVAL) * ( T - T(IVAL) )
  //             + C(IVAL) * ( T - T(IVAL) )**2
  //             + D(IVAL) * ( T - T(IVAL) )**3
  //
  //    If we assume that we know the values Y(*) and YPP(*), which represent
  //    the values and second derivatives of the spline at each knot, then
  //    the coefficients can be computed as:
  //
  //      A(IVAL) = Y(IVAL)
  //      B(IVAL) = ( Y(IVAL+1) - Y(IVAL) ) / ( T(IVAL+1) - T(IVAL) )
  //        - ( YPP(IVAL+1) + 2 * YPP(IVAL) ) * ( T(IVAL+1) - T(IVAL) ) / 6
  //      C(IVAL) = YPP(IVAL) / 2
  //      D(IVAL) = ( YPP(IVAL+1) - YPP(IVAL) ) / ( 6 * ( T(IVAL+1) - T(IVAL) ) )
  //
  //    Since the first derivative of the spline is
  //
  //      SPL'(T) =     B(IVAL)
  //              + 2 * C(IVAL) * ( T - T(IVAL) )
  //              + 3 * D(IVAL) * ( T - T(IVAL) )**2,
  //
  //    the requirement that the first derivative be continuous at interior
  //    knot I results in a total of N-2 equations, of the form:
  //
  //      B(IVAL-1) + 2 C(IVAL-1) * (T(IVAL)-T(IVAL-1))
  //      + 3 * D(IVAL-1) * (T(IVAL) - T(IVAL-1))**2 = B(IVAL)
  //
  //    or, setting H(IVAL) = T(IVAL+1) - T(IVAL)
  //
  //      ( Y(IVAL) - Y(IVAL-1) ) / H(IVAL-1)
  //      - ( YPP(IVAL) + 2 * YPP(IVAL-1) ) * H(IVAL-1) / 6
  //      + YPP(IVAL-1) * H(IVAL-1)
  //      + ( YPP(IVAL) - YPP(IVAL-1) ) * H(IVAL-1) / 2
  //      =
  //      ( Y(IVAL+1) - Y(IVAL) ) / H(IVAL)
  //      - ( YPP(IVAL+1) + 2 * YPP(IVAL) ) * H(IVAL) / 6
  //
  //    or
  //
  //      YPP(IVAL-1) * H(IVAL-1) + 2 * YPP(IVAL) * ( H(IVAL-1) + H(IVAL) )
  //      + YPP(IVAL) * H(IVAL)
  //      =
  //      6 * ( Y(IVAL+1) - Y(IVAL) ) / H(IVAL)
  //      - 6 * ( Y(IVAL) - Y(IVAL-1) ) / H(IVAL-1)
  //
  //    Boundary conditions must be applied at the first and last knots.  
  //    The resulting tridiagonal system can be solved for the YPP values.
  //
  //  Licensing:
  //
  //    This code is distributed under the GNU LGPL license. 
  //
  //  Modified:
  //
  //    06 February 2004
  //
  //  Author:
  //
  //    John Burkardt
  //
  //  Modified By:
  //
  //    Derek Seiple (20 August 2010)
  //
  //  Parameters:
  //
  //    Input, int N, the number of data points.  N must be at least 2.
  //    In the special case where N = 2 and IBCBEG = IBCEND = 0, the
  //    spline will actually be linear.
  //
  //    Input, double T[N], the knot values, that is, the points were data is
  //    specified.  The knot values should be distinct, and increasing.
  //
  //    Input, double Y[N], the data values to be interpolated.
  //
  //    Input, int IBCBEG, left boundary condition flag:
  //      0: the cubic spline should be a quadratic over the first interval;
  //      1: the first derivative at the left endpoint should be YBCBEG;
  //      2: the second derivative at the left endpoint should be YBCBEG.
  //
  //    Input, double YBCBEG, the values to be used in the boundary
  //    conditions if IBCBEG is equal to 1 or 2.
  //
  //    Input, int IBCEND, right boundary condition flag:
  //      0: the cubic spline should be a quadratic over the last interval;
  //      1: the first derivative at the right endpoint should be YBCEND;
  //      2: the second derivative at the right endpoint should be YBCEND.
  //
  //    Input, double YBCEND, the values to be used in the boundary
  //    conditions if IBCEND is equal to 1 or 2.
  //
  //    Output, double SPLINE_CUBIC_SET[N], the second derivatives of the cubic spline.
  //
  {
    dvar_vector a(0,3*n-1);
    dvar_vector b(0,n-1);
    int i;
  //
  //  Check.
  //
    if ( n <= 1 )
    {
      cout << "\n";
      cout << "SPLINE_CUBIC_SET - Fatal error!\n";
      cout << "  The number of data points N must be at least 2.\n";
      cout << "  The input value is " << n << ".\n";
      //return NULL;
    }
  
    for ( i = 0; i < n - 1; i++ )
    {
      if ( t[i+1] <= t[i] )
      {
        cout << "\n";
        cout << "SPLINE_CUBIC_SET - Fatal error!\n";
        cout << "  The knots must be strictly increasing, but\n";
        cout << "  T(" << i   << ") = " << t[i]   << "\n";
        cout << "  T(" << i+1 << ") = " << t[i+1] << "\n";
      }
    }
  
  //
  //  Set up the first equation.
  //
    if ( ibcbeg == 0 )
    {
      b[0] = 0.0;
      a[1+0*3] = 1.0;
      a[0+1*3] = -1.0;
    }
    else if ( ibcbeg == 1 )
    {
      b[0] = ( y[1] - y[0] ) / ( t[1] - t[0] ) - ybcbeg;
      a[1+0*3] = ( t[1] - t[0] ) / 3.0;
      a[0+1*3] = ( t[1] - t[0] ) / 6.0;
    }
    else if ( ibcbeg == 2 )
    {
      b[0] = ybcbeg;
      a[1+0*3] = 1.0;
      a[0+1*3] = 0.0;
    }
    else
    {
      cout << "\n";
      cout << "SPLINE_CUBIC_SET - Fatal error!\n";
      cout << "  IBCBEG must be 0, 1 or 2.\n";
      cout << "  The input value is " << ibcbeg << ".\n";
    }
  //
  //  Set up the intermediate equations.
  //
    for ( i = 1; i < n-1; i++ )
    {
      b[i] = ( y[i+1] - y[i] ) / ( t[i+1] - t[i] )
        - ( y[i] - y[i-1] ) / ( t[i] - t[i-1] );
      a[2+(i-1)*3] = ( t[i] - t[i-1] ) / 6.0;
      a[1+ i   *3] = ( t[i+1] - t[i-1] ) / 3.0;
      a[0+(i+1)*3] = ( t[i+1] - t[i] ) / 6.0;
    }
  //
  //  Set up the last equation.
  //
    if ( ibcend == 0 )
    {
      b[n-1] = 0.0;
      a[2+(n-2)*3] = -1.0;
      a[1+(n-1)*3] = 1.0;
    }
    else if ( ibcend == 1 )
    {
      b[n-1] = ybcend - ( y[n-1] - y[n-2] ) / ( t[n-1] - t[n-2] );
      a[2+(n-2)*3] = ( t[n-1] - t[n-2] ) / 6.0;
      a[1+(n-1)*3] = ( t[n-1] - t[n-2] ) / 3.0;
    }
    else if ( ibcend == 2 )
    {
      b[n-1] = ybcend;
      a[2+(n-2)*3] = 0.0;
      a[1+(n-1)*3] = 1.0;
    }
    else
    {
      cout << "\n";
      cout << "SPLINE_CUBIC_SET - Fatal error!\n";
      cout << "  IBCEND must be 0, 1 or 2.\n";
      cout << "  The input value is " << ibcend << ".\n";
    }
  //
  //  Solve the linear system.
  //
    if ( n == 2 && ibcbeg == 0 && ibcend == 0 )
    {
      dvar_vector ret(0,1);
      ret(0) = 0.0;
      ret(1) = 0.0;
      return ret;
    }
    else
    {
      dvar_vector ypp = d3_np_fs ( n, a, b );
      dvar_vector ret(0,n-1);
      if ( !ypp )
      {
        cout << "\n";
        cout << "SPLINE_CUBIC_SET - Fatal error!\n";
        cout << "  The linear system could not be solved.\n";
      }
      ret = ypp;
      return ret;
    }
  
  }




