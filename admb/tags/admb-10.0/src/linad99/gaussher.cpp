/*
 * $Id$
 * 
 * Author: David Fournier
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * This file has routines used for
 * Gauss-Hermite Quadrature and
 * Gauss-Legendre Quadrature.
 */

#include <fvar.hpp>
static double eps=3.0e-14;
static double pim=0.7511255444649427;
static int maxit=50;

void imtqlx ( const dvector& _d, const dvector& _e, const dvector& _z );

/**
 * The sign of a number
 * \param x Double
 */
double sign ( double x )
{
  double value;

  if ( x < 0.0 )
  {
    value = -1.0;
  } 
  else
  {
    value = 1.0;
  }
  return value;
}

/**
 * Gauss-Hermite quadature.
 * Computes a Gauss-Hermite quadrature formula with simple knots.
 * \param _t array of abscissa
 * \param _wts array of corresponding wights
 */
void gauss_hermite (const dvector& _t,const dvector& _wts)
//
//  Purpose:
//
//    computes a Gauss quadrature formula with simple knots.
//
//  Discussion:
//
//    This routine computes all the knots and weights of a Gauss quadrature
//    formula with a classical weight function with default values for A and B,
//    and only simple knots.
//
//    There are no moments checks and no printing is done.
//
//    Use routine EIQFS to evaluate a quadrature computed by CGQFS.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    September 2010 by Derek Seiple
//
//  Author:
//
//    Original FORTRAN77 version by Sylvan Elhay, Jaroslav Kautsky.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Sylvan Elhay, Jaroslav Kautsky,
//    Algorithm 655: IQPACK, FORTRAN Subroutines for the Weights of 
//    Interpolatory Quadrature,
//    ACM Transactions on Mathematical Software,
//    Volume 13, Number 4, December 1987, pages 399-415.
//
//  Parameters:
//
//    Output, double T[NT], the knots.
//
//    Output, double WTS[NT], the weights.
//
{
  dvector t=(dvector&) _t;
  dvector wts=(dvector&) _wts;

  if( t.indexmax()!=wts.indexmax() )
  {
    cerr << "Incompatible sizes in void "
         << "void gauss_hermite (const dvector& _t,const dvector& _wts)" << endl;
    ad_exit(-1);
  }

  int lb = t.indexmin();
  int ub = t.indexmax();

  dvector aj(lb,ub);
  dvector bj(lb,ub);
  double zemu;
  int i;

  //  Get the Jacobi matrix and zero-th moment.
  zemu = 1.772453850905516;
  for ( i = lb; i <= ub; i++ )
  {
    aj(i) = 0.0;
  }
  for ( i = lb; i <= ub; i++ )
  {
    bj(i) = sqrt((i-lb+1)/2.0);
  }

  //  Compute the knots and weights.
  if ( zemu <= 0.0 ) //  Exit if the zero-th moment is not positive.
  {
    cout << "\n";
    cout << "SGQF - Fatal error!\n";
    cout << "  ZEMU <= 0.\n";
    exit ( 1 );
  }

  //  Set up vectors for IMTQLX.
  for ( i = lb; i <= ub; i++ )
  {
    t(i) = aj(i);
  }
  wts(lb) = sqrt ( zemu );
  for ( i = lb+1; i <= ub; i++ )
  {
    wts(i) = 0.0;
  }

  //  Diagonalize the Jacobi matrix.
  imtqlx ( t, bj, wts );

  for ( i = lb; i <= ub; i++ )
  {
    wts(i) = wts(i) * wts(i);
  }

  return;
}

/**
 * Gauss-Legendre quadature.
 * computes knots and weights of a Gauss-Legendre quadrature formula.
 * \param a Left endpoint of interval
 * \param b Right endpoint of interval
 * \param _t array of abscissa
 * \param _wts array of corresponding wights
 */
void gauss_legendre( double a, double b, const dvector& _t, const dvector& _wts )
//
//  Purpose:
//
//    computes knots and weights of a Gauss-Legendre quadrature formula.
//
//  Discussion:
//
//    The user may specify the interval (A,B).
//
//    Only simple knots are produced.
//
//    Use routine EIQFS to evaluate this quadrature formula.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    September 2010 by Derek Seiple
//
//  Author:
//
//    Original FORTRAN77 version by Sylvan Elhay, Jaroslav Kautsky.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Sylvan Elhay, Jaroslav Kautsky,
//    Algorithm 655: IQPACK, FORTRAN Subroutines for the Weights of 
//    Interpolatory Quadrature,
//    ACM Transactions on Mathematical Software,
//    Volume 13, Number 4, December 1987, pages 399-415.
//
//  Parameters:
//
//    Input, double A, B, the interval endpoints, or
//    other parameters.
//
//    Output, double T[NT], the knots.
//
//    Output, double WTS[NT], the weights.
//
{
  dvector t=(dvector&) _t;
  dvector wts=(dvector&) _wts;

  if( t.indexmax()!=wts.indexmax() )
  {
    cerr << "Incompatible sizes in void "
         << "void mygauss_legendre(double a, double b, const dvector& _t, const dvector& _wts)" << endl;
    ad_exit(-1);
  }

  int lb = t.indexmin();
  t.shift(0);
  wts.shift(0);
  int nt = t.indexmax() + 1;
  int ub = nt-1;

  int i;
  int k;
  int l;
  double al;
  double ab;
  double abi;
  double abj;
  double be;
  double p;
  double shft;
  double slp;
  double temp;
  double tmp;
  double zemu;

  //  Compute the Gauss quadrature formula for default values of A and B.
  dvector aj(0,ub);
  dvector bj(0,ub);

  ab = 0.0;
  zemu = 2.0 / ( ab + 1.0 );
  for ( i = 0; i < nt; i++ )
  {
    aj[i] = 0.0;
  }
  for ( i = 1; i <= nt; i++ )
  {
    abi = i + ab * ( i % 2 );
    abj = 2 * i + ab;
    bj[i-1] = sqrt ( abi * abi / ( abj * abj - 1.0 ) );
  }

  //  Compute the knots and weights. 
  if ( zemu <= 0.0 )  //  Exit if the zero-th moment is not positive.
  {
    cout << "\n";
    cout << "Fatal error!\n";
    cout << "  ZEMU <= 0.\n";
    exit ( 1 );
  }

  //  Set up vectors for IMTQLX.
  for ( i = 0; i < nt; i++ )
  {
    t[i] = aj[i];
  }
  wts[0] = sqrt ( zemu );
  for ( i = 1; i < nt; i++ )
  {
    wts[i] = 0.0;
  }

  //  Diagonalize the Jacobi matrix.
  imtqlx (t, bj, wts );

  for ( i = 0; i < nt; i++ )
  {
    wts[i] = wts[i] * wts[i];
  }

  //  Prepare to scale the quadrature formula to other weight function with 
  //  valid A and B.
  ivector mlt(0,ub);
  for ( i = 0; i < nt; i++ )
  {
    mlt[i] = 1;
  }
  ivector ndx(0,ub);
  for ( i = 0; i < nt; i++ )
  {
    ndx[i] = i + 1;
  }

  dvector st(0,ub);
  dvector swts(0,ub);

  temp = 3.0e-14;
  al = 0.0;
  be = 0.0;
  if ( fabs ( b - a ) <= temp )
  {
    cout << "\n";
    cout << "Fatal error!\n";
    cout << "  |B - A| too small.\n";
    exit ( 1 );
  }
  shft = ( a + b ) / 2.0;
  slp = ( b - a ) / 2.0;

  p = pow ( slp, al + be + 1.0 );

  for ( k = 0; k < nt; k++ )
  {
    st[k] = shft + slp * t[k];
    l = abs ( ndx[k] );

    if ( l != 0 )
    {
      tmp = p;
      for ( i = l - 1; i <= l - 1 + mlt[k] - 1; i++ )
      {
        swts[i] = wts[i] * tmp;
        tmp = tmp * slp;
      }
    }
  }

  for(i=0;i<nt;i++)
  {
    t(i) = st(ub-i);
    wts(i) = swts(ub-i);
  }

  return;
}

/**
 * Gauss-Legendre quadature.
 * \param _x array of abscissa
 * \param _w array of corresponding wights
 */
void gauss_legendre(const dvector& _x, const dvector& _w)
{
  gauss_legendre(0,1,_x,_w);
}

/**
 * Gauss-Hermite quadature.
 * this is normlaized so that standard normal density
 * integrates to 1
 * \param _x array of abscissa
 * \param _w array of corresponding wights
 */
void normalized_gauss_hermite(const dvector& _x, const dvector& _w)
{
  dvector& x=(dvector&) _x;
  dvector& w=(dvector&) _w;
  gauss_hermite(x,w);
  w=elem_prod(w,exp(square(x)));
  x*=sqrt(2.0);
  w*=sqrt(2.0);
}

/**
 * Diagonalizes a symmetric tridiagonal matrix
 * \param _d diagonal entries
 * \param _e the subdiagonals
 * \param _z a vector
 */
void imtqlx( const dvector& _d, const dvector& _e, const dvector& _z )
//
//  Purpose:
//
//    IMTQLX diagonalizes a symmetric tridiagonal matrix.
//
//  Discussion:
//
//    This routine is a slightly modified version of the EISPACK routine to 
//    perform the implicit QL algorithm on a symmetric tridiagonal matrix. 
//
//    The authors thank the authors of EISPACK for permission to use this
//    routine. 
//
//    It has been modified to produce the product Q' * Z, where Z is an input 
//    vector and Q is the orthogonal matrix diagonalizing the input matrix.  
//    The changes consist (essentialy) of applying the orthogonal transformations
//    directly to Z as they are generated.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    September 2010 by Derek Seiple
//
//  Author:
//
//    Original FORTRAN77 version by Sylvan Elhay, Jaroslav Kautsky.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Sylvan Elhay, Jaroslav Kautsky,
//    Algorithm 655: IQPACK, FORTRAN Subroutines for the Weights of 
//    Interpolatory Quadrature,
//    ACM Transactions on Mathematical Software,
//    Volume 13, Number 4, December 1987, pages 399-415.
//
//    Roger Martin, James Wilkinson,
//    The Implicit QL Algorithm,
//    Numerische Mathematik,
//    Volume 12, Number 5, December 1968, pages 377-383.
//
//  Parameters:
//
//    Input/output, double D(N), the diagonal entries of the matrix.
//    On output, the information in D has been overwritten.
//
//    Input/output, double E(N), the subdiagonal entries of the 
//    matrix, in entries E(1) through E(N-1).  On output, the information in
//    E has been overwritten.
//
//    Input/output, double Z(N).  On input, a vector.  On output,
//    the value of Q' * Z, where Q is the matrix that diagonalizes the
//    input symmetric tridiagonal matrix.
//
{
  dvector d=(dvector&) _d;
  dvector e=(dvector&) _e;
  dvector z=(dvector&) _z;
  if( d.indexmax()!=e.indexmax() || d.indexmax()!=z.indexmax() || z.indexmax()!=e.indexmax() )
  {
    cerr << "Incompatible sizes in void "
         << "imtqlx ( const dvector& _d, const dvector& _e, const dvector& _z )" << endl;
    ad_exit(-1);
  }

  int lb = d.indexmin();
  d.shift(0);
  e.shift(0);
  z.shift(0);
  int n = d.indexmax() + 1;

  double b;
  double c;
  double f;
  double g;
  int i;
  int ii;
  int itn = 30;
  int j;
  int k;
  int l;
  int m;
  int mml;
  double p;
  double prec;
  double r;
  double s;

  prec = 3.0e-14;

  if ( n == 1 )
  {
    return;
  }

  e[n-1] = 0.0;

  for ( l = 1; l <= n; l++ )
  {
    j = 0;
    for ( ; ; )
    {
      for ( m = l; m <= n; m++ )
      {
        if ( m == n )
        {
          break;
        }

        if ( fabs ( e[m-1] ) <= prec * ( fabs ( d[m-1] ) + fabs ( d[m] ) ) )
        {
          break;
        }
      }
      p = d[l-1];
      if ( m == l )
      {
        break;
      }
      if ( itn <= j )
      {
        cout << "\n";
        cout << "IMTQLX - Fatal error!\n";
        cout << "  Iteration limit exceeded\n";
        exit ( 1 );
      }
      j = j + 1;
      g = ( d[l] - p ) / ( 2.0 * e[l-1] );
      r =  sqrt ( g * g + 1.0 );
      g = d[m-1] - p + e[l-1] / ( g + fabs ( r ) * sign ( g ) );
      s = 1.0;
      c = 1.0;
      p = 0.0;
      mml = m - l;

      for ( ii = 1; ii <= mml; ii++ )
      {
        i = m - ii;
        f = s * e[i-1];
        b = c * e[i-1];

        if ( fabs ( g ) <= fabs ( f ) )
        {
          c = g / f;
          r =  sqrt ( c * c + 1.0 );
          e[i] = f * r;
          s = 1.0 / r;
          c = c * s;
        }
        else
        {
          s = f / g;
          r =  sqrt ( s * s + 1.0 );
          e[i] = g * r;
          c = 1.0 / r;
          s = s * c;
        }
        g = d[i] - p;
        r = ( d[i-1] - g ) * s + 2.0 * c * b;
        p = s * r;
        d[i] = g + p;
        g = c * r - b;
        f = z[i];
        z[i] = s * z[i-1] + c * f;
        z[i-1] = c * z[i-1] - s * f;
      }
      d[l-1] = d[l-1] - p;
      e[l-1] = g;
      e[m-1] = 0.0;
    }
  }

  //  Sorting.
  for ( ii = 2; ii <= m; ii++ )
  {
    i = ii - 1;
    k = i;
    p = d[i-1];

    for ( j = ii; j <= n; j++ )
    {
      if ( d[j-1] > p )
      {
         k = j;
         p = d[j-1];
      }
    }

    if ( k != i )
    {
      d[k-1] = d[i-1];
      d[i-1] = p;
      p = z[i-1];
      z[i-1] = z[k-1];
      z[k-1] = p;
    }
  }

  d.shift(lb);
  e.shift(lb);
  z.shift(lb);
  return;
}
