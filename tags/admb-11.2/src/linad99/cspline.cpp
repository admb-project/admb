/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB Foundation
 */
/**
 * \file
 * Contains routines for cubic spline interpolation
 * for constant types.
 */
#include <fvar.hpp>

dvector spline(const dvector &x, const dvector&y, double yp1,double ypn);
dvector spline_cubic_set(int n, const dvector& t, const dvector& y, int ibcbeg,
                         double ybcbeg, int ibcend, double ybcend );
double spline_cubic_val(int n, const dvector& t, double tval,
                        const dvector& y, const dvector& ypp);

double splint(const dvector& xa, const dvector& ya, const dvector& y2a,
  double x);

/**
 * Constructor for the cubic spline class.
 * \param _x independent variable
 * \param  _y dependent variable
 * \param yp1 derivative at first spline point
 * \param ypn derivative at last spline point
 */
cubic_spline_function::cubic_spline_function(const dvector & _x,
  const dvector& _y, double yp1, double ypn) : x(_x) , y(_y)
{
  y2.allocate(x);
  y2=spline(x,y,yp1,ypn);
}

/**
 * \brief operator for interpreting a single value at u
 * \param u
 */
double cubic_spline_function::operator () (double u)
{
  // need to deal with u<x(1) or u>x(2)
  return splint(x,y,y2,u);
}

/**
 * Operator for a vector of interpolated points at u
 * \param
 */
dvector cubic_spline_function::operator()(const dvector& u)
{
  int mmin=u.indexmin();
  int mmax=u.indexmax();
  dvector z(mmin,mmax);
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
dvector spline(const dvector& _x, const dvector& _y,double yp1,double ypn)
{
  int ibcbeg, ibcend;
  double ybcbeg, ybcend;
  dvector x = _x;
  x.shift(0);
  dvector y = _y;
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
  dvector ret = spline_cubic_set(x.size(), x, y, ibcbeg, ybcbeg, ibcend,
    ybcend);
  ret.shift(_x.indexmin());
  return ret;
}

/**
 *  Cubic spline interpolation.
 * \ingroup cub_spline
 * \param _xa array of abscissa
 * \param _ya array of corresponding values \f$y_i=f(x_i)\f$
 * \param _y2a array of 2nd derivatives computed from dvector spline()
 * \param x the input coordinate to be used in the interpolation
 * \return a cubic-spline interpolation to \f$f(x)\f$
*/
double splint(const dvector& _xa, const dvector& _ya, const dvector& _y2a,
  double x)
{
  return spline_cubic_val(_xa.size(), _xa, x, _ya, _y2a);
}

/**
 * \ingroup cub_spline
 * Evaluates a piecewise cubic spline at a point
 * \param n the number of knots
 * \param t the knot values
 * \param tval a point, typically between t[0] and t[N-1], at
 *        which the spline is to be evalulated.  If tval lies outside
 *        this range, extrapolation is used.
 * \param y the data values at the knots
 * \param ypp the second derivatives of the spline at the knots
 * \return the value of the spline at tval
 */
double spline_cubic_val(int n, const dvector& t, double tval,
                        const dvector& y, const dvector& ypp)
//
//  Purpose:
//
//    SPLINE_CUBIC_VAL evaluates a piecewise cubic spline at a point.
//
//  Discussion:
//
//    SPLINE_CUBIC_SET must have already been called to define the values of
//      YPP.
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
//    Input, double YPP[N], the second derivatives of the spline at
//    the knots.
//
//    Output, double SPLINE_VAL, the value of the spline at TVAL.
//
{
  double dt;
  double h;
  int i;
  int ival;
  double yval;

  //  Determine the interval [ T(I), T(I+1) ] that contains TVAL.
  //  Values below T[0] or above T[N-1] use extrapolation.
  ival = n - 2;

  for ( i = 0; i < n-1; i++ )
  {
    if ( tval < t[i+1] )
    {
      ival = i;
      break;
    }
  }

  //  In the interval I, the polynomial is in terms of a normalized
  //  coordinate between 0 and 1.
  dt = tval - t[ival];
  h = t[ival+1] - t[ival];

  yval = y[ival]
    + dt * ( ( y[ival+1] - y[ival] ) / h
           - ( ypp[ival+1] / 6.0 + ypp[ival] / 3.0 ) * h
    + dt * ( 0.5 * ypp[ival]
    + dt * ( ( ypp[ival+1] - ypp[ival] ) / ( 6.0 * h ) ) ) );

  /* *ypval = ( y[ival+1] - y[ival] ) / h
    - ( ypp[ival+1] / 6.0 + ypp[ival] / 3.0 ) * h
    + dt * ( ypp[ival]
    + dt * ( 0.5 * ( ypp[ival+1] - ypp[ival] ) / h ) );

  *yppval = ypp[ival] + dt * ( ypp[ival+1] - ypp[ival] ) / h;*/

  return yval;
}

/**
 * \ingroup cub_spline
 * factors and solves a D3 system.
 * \param n the order of the linear system
 * \param _a On input, the nonzero diagonals of the linear system
 * \param _b the right hand side
 * \return the solution of the linear system
 */
double *d3_np_fs(int n, const dvector& _a, const dvector& _b)
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
  ADUNCONST(dvector,a)
  ADUNCONST(dvector,b)
  int i;
  double *x;
  double xmult;

  //  Check.
  for ( i = 0; i < n; i++ )
  {
    if ( a[1+i*3] == 0.0 )
    {
      return NULL;
    }
  }
  x = new double[n];

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

/**
 * \ingroup cub_spline
 * Computes the second derivatives of a piecewise cubic spline
 * \param n The number of data points. \f$n\f$ must be at least 2.
 *        In the special case where \f$n = 2\f$ and ibcend = ibcend = 0,
 *        the spline will actually be linear.
 * \param t The knot values. The knot values should be distinct, and increasing.
 * \param y The data values to be interpolated
 * \param ibcbeg The left boundary flag,
 *        0: the cubic spline should be a quadratic over the first interval;
 *        1: the first derivative at the left endpoint should be ybcbeg;
 *        2: the second derivative at the left endpoint should be ybcbeg.
 * \param ybcbeg The values to be used in the boundary conditions
 * \param ibcend The right boundary flag,
 *        0: the cubic spline should be a quadratic over the last interval;
 *        1: the first derivative at the right endpoint should be YBCEND;
 *        2: the second derivative at the right endpoint should be YBCEND.
 * \param ybcend the values to be used in the boundary conditions
 * \return the second derivatives of the cubic spline
 */
dvector spline_cubic_set(int n, const dvector& t, const dvector& y, int ibcbeg,
  double ybcbeg, int ibcend, double ybcend )
//
//  Purpose:
//
//    SPLINE_CUBIC_SET computes the second derivatives of a piecewise cubic
//      spline.
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
//    Output, double SPLINE_CUBIC_SET[N], the second derivatives of the cubic
//      spline.
//
{
  dvector a(0,3*n-1);
  dvector b(0,n-1);

  //  Check.
  if ( n <= 1 )
  {
    cout << "\n";
    cout << "SPLINE_CUBIC_SET - Fatal error!\n";
    cout << "  The number of data points N must be at least 2.\n";
    cout << "  The input value is " << n << ".\n";
    //return NULL;
  }

  for (int i = 0; i < n - 1; i++ )
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

  //  Set up the first equation.
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

  //  Set up the intermediate equations.
  for (int  i = 1; i < n-1; i++ )
  {
    b[i] = ( y[i+1] - y[i] ) / ( t[i+1] - t[i] )
      - ( y[i] - y[i-1] ) / ( t[i] - t[i-1] );
    a[2+(i-1)*3] = ( t[i] - t[i-1] ) / 6.0;
    a[1+ i   *3] = ( t[i+1] - t[i-1] ) / 3.0;
    a[0+(i+1)*3] = ( t[i+1] - t[i] ) / 6.0;
  }

  //  Set up the last equation.
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

  //  Solve the linear system.
  if ( n == 2 && ibcbeg == 0 && ibcend == 0 )
  {
    dvector ret(0,1);
    ret[0] = 0.0;
    ret[1] = 0.0;
    return ret;
  }
  else
  {
    double* ypp = d3_np_fs( n, a, b );
    dvector ret(0,n-1);
    if (!ypp)
    {
      cout << "\n";
      cout << "SPLINE_CUBIC_SET - Fatal error!\n";
      cout << "  The linear system could not be solved.\n";
    }
    else
    {
      for(int i=0;i<n;i++)
      {
        ret(i) = ypp[i];
      }
    }
    return ret;
  }
}
