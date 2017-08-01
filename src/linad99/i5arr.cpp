/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include "admb_messages.h"

/// Default constructor
i5_array::i5_array()
{
  allocate();
}
/// Copy constructor
i5_array::i5_array(const i5_array& other)
{
  if (other.shape)
  {
    shape = other.shape;
    (shape->ncopies)++;
    t = other.t;
  }
  else
  {
    allocate();
  }
}
/// Destructor
i5_array::~i5_array()
{
  deallocate();
}
/// Does NOT allocate, but initializes i5_array members.
void i5_array::allocate()
{
  t = nullptr;
  shape = nullptr;
}
/**
Construct vector of i4_array with dimensions [hsl to hsu].

\param hsl lower vector index
\param hsu upper vector index
*/
i5_array::i5_array(int hsl, int hsu)
{
  allocate(hsl,hsu);
}
/**
Allocate vector of i4_array with dimensions [hsl to hsu].

\param hsl lower vector index
\param hsu upper vector index
*/
void i5_array::allocate(int hsl, int hsu)
{
  if (hsl > hsu)
  {
    return allocate();
  }
  if ((t = new i4_array[static_cast<unsigned int>(hsu - hsl + 1)]) == 0)
  {
    cerr << " Error allocating memory in i5_array::allocate\n";
    ad_exit(1);
  }
  if ((shape = new vector_shapex(hsl, hsu, t)) == 0)
  {
    cerr << " Error allocating memory in i5_array::allocate\n";
    ad_exit(1);
  }
  t -= indexmin();
  for (int i = hsl; i <= hsu; ++i)
  {
    t[i].allocate();
  }
}
/**
 * Description not yet available.
 * \param
 */
void i5_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  int nrl, int nrh,
  int ncl, int nch,
  int aa, int bb)
{
  allocate(hsl, hsu);
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    t[i].allocate(sl,sh,nrl,nrh,ncl,nch,aa,bb);
  }
}

/**
 * Description not yet available.
 * \param
 */
 void i5_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
   const index_type& sl,const index_type& sh,
   const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch,
   const index_type& aa,const index_type& bb)
 {
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
   if (ss>0)
   {
     if ( (t = new i4_array[ss]) == 0)
     {
       cerr << " Error allocating memory in i5_array contructor\n";
       ad_exit(21);
     }
     if ( (shape=new vector_shapex(hsl,hsu,t)) == 0)
     {
       cerr << " Error allocating memory in i5_array contructor\n";
       ad_exit(21);
     }
     t -= indexmin();
     for (int i=hsl; i<=hsu; i++)
     {
       (*this)(i).allocate(ad_integer(sl),ad_integer(sh),nrl(i),nrh(i),
         ncl(i),nch(i),aa(i),bb(i));
     }
   }
   else
   {
     t=0;
     shape=0;
   }
 }
/// Deallocates i5_array memory if no copies exists.
void i5_array::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      t = static_cast<i4_array*>(shape->get_truepointer());
      delete [] t;
      delete shape;
      allocate();
    }
  }
}

#if !defined (OPT_LIB)

/// Returns reference to i4_array element at i5_array(i).
i4_array& i5_array::operator()(int i)
{
  return elem(i);
}
/// Returns reference to i4_array element at i5_array[i].
i4_array& i5_array::operator[](int i)
{
  return elem(i);
}
/// Returns reference to i3_array element at i5_array(i, j).
i3_array& i5_array::operator()(int i, int j)
{
  return elem(i)(j);
}
/// Returns reference to imatrix element at i5_array(i, j, k).
imatrix& i5_array::operator()(int i, int j, int k)
{
  return elem(i)(j, k);
}
/// Returns reference to ivector element at i5_array(i, j, k, l).
ivector& i5_array::operator()(int i, int j, int k, int l)
{
  return elem(i)(j, k, l);
}
/// Returns reference to integer element at i5_array(i, j, k, l, m).
int& i5_array::operator()(int i, int j, int k, int l, int m)
{
  return elem(i)(j, k, l, m);
}
/// Returns reference to const i5_array element at i5_array(i).
const i4_array& i5_array::operator()(int i) const
{
  return elem(i);
}
/// Returns reference to const i5_array element at i5_array[i].
const i4_array& i5_array::operator[](int i) const
{
  return elem(i);
}
/// Returns reference to const i3_array element at i5_array(i, j).
const i3_array& i5_array::operator()(int i, int j) const
{
  return elem(i)(j);
}
/// Returns reference to const imatrix element at i5_array(i, j, k).
const imatrix& i5_array::operator()(int i, int j, int k) const
{
  return elem(i)(j, k);
}
/// Returns reference to const ivector element at i5_array(i, j, k, l).
const ivector& i5_array::operator()(int i, int j, int k, int l) const
{
  return elem(i)(j, k, l);
}
/// Returns reference to const integer element at i5_array(i, j, k, l, m).
const int& i5_array::operator()(int i, int j, int k, int l, int m) const
{
  return elem(i)(j, k, l, m);
}
#endif
