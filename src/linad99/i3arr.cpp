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
//#include "i3_array.h"

/**
Default constructor
*/
i3_array::i3_array()
{
  allocate();
}
/**
Destructor
*/
i3_array::~i3_array()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      deallocate();
    }
  }
/*
  else
  {
    cerr << "Warning -- trying to deallocate an unallocated i3_array"<<endl;
  }
*/
}
/**
Allocate vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl lower matrix column index
\param nch upper matrix column index
*/
void i3_array::allocate(
  int sl, int sh,
  int nrl, int nrh,
  int ncl, int nch)
{
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new imatrix[slicesize()]) == 0)
  {
     ad_exit(21);
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(nrl, nrh, ncl, nch);
  }
}
/**
Allocate vector of empty matrices with dimension
[sl to sh].
\param sl lower vector index
\param sh upper vector index
*/
void i3_array::allocate(int sl, int sh)
{
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new imatrix[slicesize()]) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate();
  }
}
/**
Construct vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl vector of lower matrix column indexes
\param nch vector of upper matrix column indexes
*/
i3_array::i3_array(
  int sl, int sh,
  int nrl, int nrh,
  const ivector& ncl, const ivector& nch)
{
  allocate(sl, sh, nrl, nrh, ncl, nch);
}
/**
Construct vector of empty matrices with dimension
[sl to sh].
\param sl lower vector index
\param sh upper vector index
*/
i3_array::i3_array(int sl, int sh)
{
  allocate(sl, sh);
}
/**
Construct vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh vector of upper matrix row indexes
\param ncl lower matrix column index
\param nch upper matrix column index
*/
i3_array::i3_array(
  int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, int nch)
{
  allocate(sl, sh, nrl, nrh, ncl, nch);
}
/**
Allocate vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl vector of lower matrix column indexes
\param nch vector of upper matrix column indexes
*/
void i3_array::allocate(
  int sl, int sh,
  int nrl, int nrh,
  const ivector& ncl, const ivector& nch)
{
  if ( (shape=new three_array_shape(sl,sh)) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ( (t = new imatrix[slicesize()]) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(nrl, nrh, ncl(i), nch(i));
  }
}
/**
Allocate vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh vector of upper matrix row indexes
\param ncl lower matrix column index
\param nch upper matrix column index
*/
 void i3_array::allocate(
  int sl,int sh,
  int nrl,const ivector& nrh,
  int ncl, int nch)
{
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new imatrix[slicesize()]) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(nrl, nrh(i), ncl, nch);
  }
}

/**
 * Description not yet available.
 * \param
 */
i3_array::i3_array(
  int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
{
  allocate(sl,sh,nrl,nrh,ncl,nch);
}

/**
Allocate vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl lower matrix column index
\param nch upper matrix column index
*/
i3_array::i3_array(
  int sl, int sh,
  int nrl, int nrh,
  int ncl, int nch)
{
  allocate(sl, sh, nrl, nrh, ncl, nch);
}

/**
 * Description not yet available.
 * \param
 */
void i3_array::allocate(
  int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
{
  //int imin=nrh.indexmin();
  //int rmin=nch.rowmin();
  //int cmin=nch(rmin).indexmin();
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new imatrix[slicesize()]) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(nrl, nrh(i), ncl, nch(i));
  }
}
/**
Allocate vector [_sl to _sh] of integer matrices with same dimension as m1. 
\param _sl lower vector index
\param _sh upper vector index
\param m1 matrix to copy dimensions
*/
i3_array::i3_array(int _sl, int _sh, const imatrix& m1)
{
  int sl = _sl;
  int sh = _sh;
  //int nrl = m1.rowmin();
  //int nrh = m1.rowmax();
  //int ncl = m1.colmin();
  //int nch = m1.colmax();
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new imatrix[slicesize()]) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    if (m1.shape)
    {
      t[i].shape = m1.shape;
      (t[i].shape->ncopies)++;
      t[i].m = m1.m;
    }
    else
    {
      t[i].shape = NULL;
      t[i].m = NULL;
    }
  }
}
/**
Allocate i3_array with same dimension as i3v.
*/
void i3_array::allocate(const i3_array& i3v)
{
  int sl = i3v.slicemin();
  int sh = i3v.slicemax();
  //int nrl=i3v.rowmin();
  //int nrh=i3v.rowmax();
  //int ncl=i3v.colmin();
  //int nch=i3v.colmax();
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new imatrix[slicesize()]) == 0)
  {
    cerr << " Error: i3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(i3v[i]);
    //elem(i).initialize();
  }
}

/**
Does NOT allocate, but set empty i3_array.
*/
void i3_array::allocate(void)
{
  shape = NULL;
  t = NULL;
}

/**
 * Description not yet available.
 * \param
 */
 void i3_array::initialize()
 {
   if (!(!(*this)))  // only initialize allocated objects
   {
     for (int i=slicemin();i<=slicemax();i++)
     {
       elem(i).initialize();
     }
   }
 }

/**
Copy constructor
*/
i3_array::i3_array(const i3_array& m2)
{
  shape = m2.shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
/*
  else
  {
    cerr << "Making a copy of an unallocated d3_array"<<endl;
  }
*/
  t = m2.t;
}
/**
Deallocate memory for i3_array.
*/
void i3_array::deallocate()
{
  if (shape)
  {
    t += slicemin();
    //int ss=slicesize();

    delete [] t;
    t = NULL;

    delete shape;
    shape = NULL;
  }
/*
  else
  {
    cerr << "Warning -- trying to deallocate an unallocated imatrix"<<endl;
  }
*/
}
