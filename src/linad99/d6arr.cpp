/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#if (__cplusplus > 199711L)
  #include <algorithm>
  #include <iterator>
#endif
#include "fvar.hpp"
#include "admb_messages.h"

/// Initialize all elments of d6_array to zero.
void d6_array::initialize()
{
#if (__cplusplus <= 199711L)
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i).initialize();
  }
#else
  if (operator!() == false)
  {
    auto begin = &elem(indexmin());
    auto end = begin + size();
    std::for_each(begin, end, [](d5_array& darray)
    {
      darray.initialize();
    });
  }
#endif
}
/// Copy constructor (shallow)
d6_array::d6_array(const d6_array& other)
{
  shallow_copy(other);
}
/**
Shallow copy other data structure pointers.

\param other d3_array
*/
void d6_array::shallow_copy(const d6_array& other)
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
    cerr << "Warning -- Unable to shallow copy an unallocated d6_array.\n";
#endif
    allocate();
  }
}
/// Deallocate d6_array memory.
void d6_array::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
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
#if defined(DIAG)
  else
  {
    cerr << "Warning -- Unable to deallocate an unallocated d6_array.\n";
  }
#endif
}
/// Destructor
d6_array::~d6_array()
{
  deallocate();
}

/**
Assigns element values from other to d6_array.

\param other d6_array
*/
d6_array& d6_array::operator=(const d6_array& other)
{
  int min = indexmin();
  int max = indexmax();
  if (min != other.indexmin() || max != other.indexmax())
  {
     cerr << "Incompatible bounds in"
          << " d6_array& d6_array::operator=(const d6_array&).\n";
     ad_exit(1);
   }
  for (int i = min; i <= max; ++i)
  {
    elem(i) = other.elem(i);
  }
  return *this;
}
/**
Allocate d6_array with same dimensions as other.

\param other d6_array
*/
void d6_array::allocate(const d6_array& other)
{
  allocate(other.indexmin(), other.indexmax());
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i).allocate(other.elem(i));
  }
}
/**
 * Description not yet available.
 * \param
 */
d6_array::d6_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}

/**
 * Description not yet available.
 * \param
 */
d6_array::d6_array(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5,
  const index_type& l6,const index_type& u6)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}
void d6_array::allocate(int hsl, int hsu)
{
  if (hsl > hsu)
  {
    return allocate();
  }
  if ((shape = new vector_shape(hsl, hsu)) == 0)
  {
    cerr << "Error: Unable to allocate d6_array memory in\n"
         << " d6_array::allocate(int, int).\n";
    ad_exit(1);
  }
  if ((t = new d5_array[size()]) == 0)
  {
    cerr << "Error: Unable to allocate d6_array memory in\n"
         << " d6_array::allocate(int, int).\n";
    ad_exit(1);
  }
  t -= indexmin();
  for (int i = hsl; i <= hsu; ++i)
  {
    elem(i).allocate();
  }
}

/**
Allocate d6_array with specified dimensions.
*/
void d6_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6)
{
  if ((shape = new vector_shape(hsl, hsu)) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  unsigned int ss = size();
  if ((t = new d5_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  t -= indexmin();
  for (int i = hsl; i <= hsu; ++i)
  {
    t[i].allocate(sl, sh, nrl, nrh, ncl, nch, l5, u5, l6, u6);
  }
}

/**
Allocate d6_array with specified dimensions.
*/
void d6_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
   const index_type& sl,const index_type& sh,const index_type& nrl,
   const index_type& nrh,const index_type& ncl,const index_type& nch,
   const index_type& l5,const index_type& u5,
   const index_type& l6,const index_type& u6)
{
  if ((shape = new vector_shape (hsl, hsu)) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
  }

  unsigned int ss = size();
  if ( (t = new d5_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  t -= indexmin();
  int i1=hsl;
  int i2=hsu;
  for (int i = i1; i <= i2; ++i)
  {
    (*this)(i).allocate(ad_integer(sl(i)),ad_integer(sh(i)),nrl(i),nrh(i),
       ncl(i),nch(i), l5(i),u5(i),l6(i),u6(i));
  }
}
/**
Return total sum of darray.

\param darray d6_array
*/
double sum(const d6_array& darray)
{
  double total = 0.0;
  for (int i = darray.indexmin(); i <= darray.indexmax(); ++i)
  {
    total += sum(darray.elem(i));
  }
  return total;
}
