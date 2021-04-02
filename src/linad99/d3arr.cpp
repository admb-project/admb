/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#if (__cplusplus > 199711L)
  #include <iterator>
  #include <algorithm>
#endif

#include "fvar.hpp"
#ifdef DEBUG
  #include <cassert>
#endif

/**
Return total sum of the elements in darray.

\param darray d3_array
*/
double sum(const d3_array& darray)
{
  double total = 0.0;
#if (__cplusplus <= 199711L)
  for (int i = darray.indexmin(); i <= darray.indexmax(); ++i)
  {
    total += sum(darray.elem(i));
  }
#else
  std::for_each(darray.begin(), darray.end(), [&total](dmatrix& matrix) {
    total += sum(matrix);
  });
#endif
  return total;
}
/**
 * Description not yet available.
 * \param
 */
 d3_array d3_array::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     d3_array tmp(nrl,nrh);
     for (int i=nrl; i<=nrh; i++)
     {
       tmp[i].shallow_copy((*this)(i));
     }
     return tmp;
   }
   else
   {
     return *this;
   }
 }
/**
Construct d3_array with a vector of empty dmatrix using position.

\param position d3_array_position
*/
d3_array::d3_array(const d3_array_position& position)
#if defined(__INTEL_COMPILER) || defined(__OPENCC__)
  { allocate(position.indexmin(), position.indexmax()); }
#else
  :d3_array(position.indexmin(), position.indexmax()) { }
#endif
/**
Construct d3_array with a vector of empty dmatrix with dimension
[nrl to nrh].

\param nrl lower vector index
\param nrh upper vector index
*/
d3_array::d3_array(int nrl, int nrh)
{
  allocate(nrl, nrh);
}

/**
 * Description not yet available.
 * \param
 */
 d3_array::d3_array(int sl,int sh,int nrl,int nrh,int ncl,int nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, int nrh, const ivector& ncl,
  int nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, int nrh, const ivector& ncl,
  const ivector& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
#ifndef OPT_LIB
   initialize();
#endif
 }

/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where ncl is a vector of indexes.
\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh upper row index for matrix
\param ncl vector of lower column indexes for matrix
\param nch upper column index for matrix
*/
void d3_array::allocate(int sl, int sh, int nrl, int nrh,
  const ivector& ncl, int nch)
{
#ifdef DIAG
  myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
#endif
  if (sl != ncl.indexmin() || sh != ncl.indexmax())
  {
     cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
  }
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl, nrh, ncl(i), nch);
  }
}
/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where nrh is a vector of indexes.
\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh upper row index for matrix
\param ncl lower column index for matrix
\param nch vector of upper column indexes for matrix
*/
void d3_array::allocate(
  int sl, int sh,
  int nrl, int nrh,
  int ncl, const ivector& nch)
{
#ifdef DIAG
  myheapcheck("Entering d3_array matrix(sl,sh,nrl,nrh,ncl,nch)" );
#endif
  if (sl != nch.indexmin() || sh != nch.indexmax())
  {
     cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
  }
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl, nrh, ncl, nch(i));
  }
}
/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh upper row index for matrix
\param ncl lower column index for matrix
\param nch upper column index for matrix
*/
void d3_array::allocate(int sl, int sh, int nrl, int nrh, int ncl, int nch)
{
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl, nrh, ncl, nch);
  }
}
/**
Allocate vector of matrices having empty columns and with dimensions
[sl to sh] x [nrl to nrh].

\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh upper row index for matrix
*/
void d3_array::allocate(int sl, int sh, int nrl, int nrh)
{
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl, nrh);
  }
}
/**
Allocate vector of matrices having empty columns and with dimensions
[sl to sh] x [nrl to nrh].

\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh upper row index for matrix
*/
void d3_array::allocate(
  int sl, int sh,
  const index_type& nrl,const index_type& nrh)
{
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl(i), nrh(i));
  }
}
/**
Allocate vector [sl to sh] of empty matrices.
Note: sl should be less than or equal to sh.

\param sl lower index of vector
\param sh upper index of vector
*/
void d3_array::allocate(int sl, int sh)
{
  if (sl > sh)
  {
    return allocate();
  }
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: d3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dmatrix[slicesize()]) == 0)
  {
    cerr << " Error: d3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate();
  }
}
/**
Allocate d3_array with the same dimensions as other.

\param other d3_array
*/
void d3_array::allocate(const d3_array& other)
{
  allocate(other.slicemin(), other.slicemax());
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    elem(i).allocate(other(i));
  }
}
/**
*/
void d3_array::allocate(
  int sl, int sh,
  const ivector& nrl, const ivector& nrh,
  const imatrix& ncl, const imatrix& nch)
{
  if (sl !=nrl.indexmin() || sh !=nrl.indexmax()
      || sl !=nrh.indexmin() || sh !=nrh.indexmax())
  {
     cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
  }
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: d3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dmatrix[slicesize()]) == 0)
  {
    cerr << " Error: d3_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= slicemin();
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(nrl(i), nrh(i), ncl(i), nch(i));
  }
}
/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where nrh and nrl are vectors of indexes.
\param sl lower index of vector
\param sh upper index of vector
\param nrl vector of lower row indexes for matrix
\param nrh vector of upper row indexes for matrix
\param ncl lower column index for matrix
\param nch upper column index for matrix
*/
void d3_array::allocate(
  int sl, int sh,
  const ivector& nrl, const ivector& nrh,
  int ncl, int nch)
{
  if (sl != nrl.indexmin() || sh != nrl.indexmax()
      || sl != nrh.indexmin() || sh != nrh.indexmax())
  {
     cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
  }
  allocate(sl, sh);
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    t[i].allocate(nrl(i), nrh(i), ncl, nch);
  }
}
/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where nrh and nrl are vectors of indexes.
\param sl lower index of vector
\param sh upper index of vector
\param nrl vector of lower row indexes for matrix
\param nrh upper row index for matrix
\param ncl lower column index for matrix
\param nch upper column index for matrix
*/
void d3_array::allocate(
  int sl, int sh,
  const ivector& nrl, int nrh,
  int ncl, int nch)
{
  allocate(sl, sh);
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    t[i].allocate(nrl(i), nrh, ncl, nch);
  }
}
/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where nrh and nrl are vectors of indexes.
\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh vector of upper row indexes for matrix
\param ncl lower column index for matrix
\param nch upper column index for matrix
*/
void d3_array::allocate(
  int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, int nch)
{
  allocate(sl, sh);
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    t[i].allocate(nrl, nrh(i), ncl, nch);
  }
}
/**
 * Description not yet available.
 * \param
 */
void d3_array::allocate(int sl, int sh, const ivector& nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
 {
   if (sl !=nrl.indexmin() || sh !=nrl.indexmax() ||
       sl !=nrh.indexmin() || sh !=nrh.indexmax())
   {
     cerr << "Incompatible d3_array bounds in "
          << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
   }
   if ((shape=new three_array_shape(sl, sh)) == 0)
   {
     cerr << " Error: d3_array unable to allocate memory in "
          << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
   }
   if ( (t = new dmatrix[slicesize()]) == 0)
   {
     cerr << " Error: d3_array unable to allocate memory in "
          << __FILE__ << ':' << __LINE__ << '\n';
     ad_exit(1);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh(i),ncl,nch(i));
   }
 }

/**
Allocate d3_array with dimensions
[sl to sh] x [nrl to nrh] x [ncl to nch].
\param sl lower index of vector
\param sh upper index of vector
\param nrl vector of lower row indexes for matrix
\param nrh vector of upper row indexes for matrix
\param ncl vector of lower column indexes for matrix
\param nch vector of upper column indexes for matrix
*/
void d3_array::allocate(
  int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
{
  if (sl != nrh.indexmin() || sh != nrh.indexmax())
  {
    cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error: d3_array unable to allocate memory in "
           << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ( (t = new dmatrix[slicesize()]) == 0)
  {
    cerr << " Error: d3_array unable to allocate memory in "
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
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where nrh and nrl are vectors of indexes.
\param sl lower index of vector
\param sh upper index of vector
\param nrl vector of lower row indexes for matrix
\param nrh vector of upper row indexes for matrix
\param ncl vector of lower column indexes for matrix
\param nch vector of upper column indexes for matrix
*/
void d3_array::allocate(int sl, int sh,
  const ivector& nrl, const ivector& nrh,
  const ivector& ncl, const ivector& nch)
{
  if (sl != nrl.indexmin() || sh != nrl.indexmax()
      || sl != nrh.indexmin() || sh != nrh.indexmax())
  {
    cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    elem(i).allocate(nrl(i), nrh(i), ncl(i), nch(i));
  }
}
/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where nrh and nrl are vectors of indexes with
dimensions [sl to sh].
\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh upper row index for matrix
\param ncl vector of lower column indexes for matrix
\param nch vector of upper column indexes for matrix
*/
void d3_array::allocate(
  int sl, int sh,
  int nrl, int nrh,
  const ivector& ncl, const ivector& nch)
{
  if (sl != ncl.indexmin() || sh != ncl.indexmax()
      || sl != nch.indexmin() || sh != nch.indexmax())
  {
    cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  allocate(sl, sh);
  for (int i = slicemin(); i <= slicemax(); ++i)
  {
    t[i].allocate(nrl, nrh, ncl(i), nch(i));
  }
}
/**
Allocate vector of matrices with dimensions
[sl to sh] x ([nrl to nrh] x [ncl to nch])
where nrh and nrl are vectors of indexes.
\param sl lower index of vector
\param sh upper index of vector
\param nrl lower row index for matrix
\param nrh vector of upper row indexes for matrix
\param ncl upper column index for matrix
\param nch vector of upper column indexes for matrix
*/
void d3_array::allocate(int sl, int sh,
  int nrl, const ivector& nrh,
  int ncl, const ivector& nch)
{
  if (sl != nrh.indexmin() || sh != nrh.indexmax()
      || sl != nch.indexmin() || sh != nch.indexmax())
  {
    cerr << "Incompatible d3_array bounds in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  allocate(sl, sh);
  for (int i = sl; i <= sh; ++i)
  {
    t[i].allocate(nrl, nrh(i), ncl, nch(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  const ivector& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, const ivector& nrl, const ivector& nrh,
  const imatrix& ncl, const imatrix& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, const ivector& nrl, const ivector& nrh,
  int ncl, const imatrix& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  const imatrix& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(int sl, int sh, int nrl, const ivector& nrh, int ncl,
  int nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

/**
Copy constructor
*/
d3_array::d3_array(const d3_array& other)
{
  shallow_copy(other);
}
/**
Shallow copy other data structure pointers.

\param other d3_array
*/
void d3_array::shallow_copy(const d3_array& other)
{
  if (other.shape)
  {
    shape = other.shape;
    ++(shape->ncopies);
    t = other.t;
  }
  else
  {
#ifdef DEBUG
    cerr << "Warning -- Unable to shallow copy an unallocated d3_array.\n";
#endif
    allocate();
  }
}
/// Initializes all elements of d3_array to zero.
void d3_array::initialize()
{
  // only initialize allocated objects
  if (t)
  {
#if (__cplusplus <= 199711L)
    for (int i = slicemin(); i <= slicemax(); ++i)
    {
      t[i].initialize();
    }
#else
    std::for_each(begin(), end(), [](dmatrix& matrix) {
      matrix.initialize();
    });
#endif
  }
}
/// Deallocates d3_array memory.
void d3_array::deallocate()
{
  if (shape)
  {
    if (shape->ncopies > 0)
    {
      --(shape->ncopies);
    }
    else
    {
      t += indexmin();
      delete [] t;
      delete shape;
    }
    allocate();
  }
#if defined(DEBUG)
  else
  {
    cerr << "Warning -- Unable to deallocate an unallocated d3_array.\n";
    //ad_exit(1);
  }
#endif
}
/// Destructor
d3_array::~d3_array()
{
  deallocate();
}
/**
Stores dimensions for dvar3_array.

\param sl slicemin
\param su slicemax
*/
three_array_shape::three_array_shape(int sl, int su)
: ncopies(0), slice_min(sl), slice_max(su)
{
}
