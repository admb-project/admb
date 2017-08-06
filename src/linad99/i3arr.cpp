/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/// Default constructor
i3_array::i3_array()
{
  allocate();
}
/// Destructor
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
#if defined(DEBUG)
  else
  {
    cerr << "Warning -- trying to deallocate an unallocated i3_array"<<endl;
  }
#endif
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
  allocate(sl, sh);
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
  if (sl > sh)
  {
    return allocate();
  }
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: Unable to allocate memory in "
         << " i3_array::allocate(int, int).\n";
    ad_exit(1);
  }
  if ((t = new imatrix[slicesize()]) == 0)
  {
    cerr << " Error: Unable to allocate memory in "
         << " i3_array::allocate(int, int).\n";
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
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl, nrh, ncl(i), nch(i));
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
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl, nrh(i), ncl, nch);
  }
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
Construct vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh vector of upper matrix row indexes [sl to sh]
\param ncl lower matrix column index
\param nch matrix of upper matrix column indexes [sl to sh] x [ncl to nrh]
*/
i3_array::i3_array(
  int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
{
  allocate(sl, sh, nrl, nrh, ncl, nch);
}
/**
Allocate vector of integer matrices with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower vector index
\param sh upper vector index
\param nrl lower matrix row index
\param nrh vector of upper matrix row indexes [sl to sh]
\param ncl lower matrix column index
\param nch matrix of upper matrix column indexes [sl to sh] x [ncl to nrh]
*/
void i3_array::allocate(
  int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
{
  allocate(sl, sh);
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    t[i].allocate(nrl, nrh(i), ncl, nch(i));
  }
}
/**
Allocate vector [sl to sh] of integer matrices with same dimension as m1. 
\param sl lower vector index
\param sh upper vector index
\param m1 matrix to copy dimensions
*/
i3_array::i3_array(int sl, int sh, const imatrix& m1)
{
  allocate(sl, sh);
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    if (m1.shape)
    {
      t[i].shape = m1.shape;
      (t[i].shape->ncopies)++;
      t[i].m = m1.m;
    }
    else
    {
      t[i].allocate();
    }
  }
}
/**
Allocate i3_array with same dimension as other.

\param other i3_array
*/
void i3_array::allocate(const i3_array& other)
{
  allocate(other.slicemin(), other.slicemax());
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i).allocate(other.elem(i));
  }
}
/// Does NOT allocate, but set empty i3_array.
void i3_array::allocate()
{
  shape = nullptr;
  t = nullptr;
}
/// Initialize all elements of i3_array to zero.
void i3_array::initialize()
{
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i).initialize();
  }
}
/// Copy constructor (shallow)
i3_array::i3_array(const i3_array& other)
{
  shape = other.shape;
  if (shape)
  {
    (shape->ncopies)++;
  }
#if defined(DEBUG)
  else
  {
    cerr << "Making a copy of an unallocated d3_array"<<endl;
  }
#endif
  t = other.t;
}
/**
Deallocate i3_array memory.
*/
void i3_array::deallocate()
{
  if (shape)
  {
    t += slicemin();
    //int ss=slicesize();

    delete [] t;
    delete shape;
    allocate();
  }
#if defined(DEBUG)
  else
  {
    cerr << "Warning -- trying to deallocate an unallocated imatrix"<<endl;
  }
#endif
}
