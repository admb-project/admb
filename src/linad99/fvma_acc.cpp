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
#include "fvar.hpp"

#ifndef OPT_LIB

/**
Returns variable element at matrix index i and j.
Bounds checking is performed.
\param i row index
\param i column index
*/
prevariable dvar_matrix::operator () (int i, int j)
{
  if (i < rowmin())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is lower than " << rowmin() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is higher than " << rowmax() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (j < elem(i).indexmin())
  {
    cerr << "matrix column bound exceeded -- column index " << i
         << " is lower than " << elem(i).indexmin() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (j > elem(i).indexmax())
  {
    cerr << "matrix column bound exceeded -- column index " << i
         << " is higher than " << elem(i).indexmax() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  return m[i].va + j;
}
/**
Returns a dvar_vector reference to the matrix row at specified location i.
Bounds checking is performed.
\param i index
*/
dvar_vector& dvar_matrix::operator[] (int i)
{
  if (i < rowmin())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is lower than " << rowmin() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is higher than " << rowmax() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  return m[i];
}
/**
Returns variable element at matrix index i and j.
Bounds checking is performed.
\param i row index
\param i column index
*/
const prevariable dvar_matrix::operator()(int i, int j) const
{
  if (i < rowmin())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is lower than " << rowmin() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is higher than " << rowmax() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (j < elem(i).indexmin())
  {
    cerr << "matrix column bound exceeded -- column index " << i
         << " is lower than " << elem(i).indexmin() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (j > elem(i).indexmax())
  {
    cerr << "matrix column bound exceeded -- column index " << i
         << " is higher than " << elem(i).indexmax() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  return m[i].va + j;
}
/**
Returns a const dvar_vector reference to the matrix row at specified location i.
Bounds checking is performed.
\param i index
 */
const dvar_vector& dvar_matrix::operator[](int i) const
{
  if (i < rowmin())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is lower than " << rowmin() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix row bound exceeded -- row index " << i
         << " is higher than " << rowmax() << " in "
         << __FILE__ << ':' << __LINE__ << ".\n";
    ad_exit(1);
  }
  return m[i];
}
#endif
