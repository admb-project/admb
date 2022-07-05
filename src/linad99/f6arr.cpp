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
#include "admb_messages.h"

/**
 * Description not yet available.
 * \param
 */
void dvar6_array::initialize(void)
{
  int mmin=indexmin();
  int mmax=indexmax();
  dvar5_array* pti = t + mmin;
  for (int i=mmin; i<=mmax; ++i)
  {
    pti->initialize();
    ++pti;
  }
}
/// Copy constructor
dvar6_array::dvar6_array(const dvar6_array& other)
{
  shallow_copy(other);
}
/**
Shallow copy other data structure pointers.

\param other dvar6_array
*/
void dvar6_array::shallow_copy(const dvar6_array& other)
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
    cerr << "Warning -- Unable to shallow copy an unallocated dvar6_array.\n";
#endif
    allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
 dvar6_array::dvar6_array(const d6_array& _m2)
 {
   d6_array& m2=(d6_array&) _m2;
   allocate(m2);
   operator=(m2);
 }
/// Deallocate dvar6_array memory.
void dvar6_array::deallocate()
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
#if defined(DIAG)
  else
  {
    cerr << "Warning -- Unable to deallocate an unallocated dvar6_array.\n";
  }
#endif
}
/// Destructor
dvar6_array::~dvar6_array()
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
dvar6_array& dvar6_array::operator=(const dvar6_array& m)
{
  int mmin=indexmin();
  int mmax=indexmax();
#ifndef OPT_LIB
  if (mmin!=m.indexmin() || mmax!=m.indexmax())
  {
     cerr << "Incompatible bounds in dvar6_array& dvar6_array::operator=(const dvar6_array&)\n";
     ad_exit(1);
  }
#endif
  dvar5_array* pti = t + mmin;
  const dvar5_array* pmi = &m(mmin);
  for (int i=mmin; i<=mmax; ++i)
  {
    *pti = *pmi;
    ++pti;
    ++pmi;
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
dvar6_array& dvar6_array::operator=(const d6_array& m)
{
  int mmin=indexmin();
  int mmax=indexmax();
#ifndef OPT_LIB
  if (mmin!=m.indexmin() || mmax!=m.indexmax())
  {
    cerr << "Incompatible bounds in dvar6_array& dvar6_array::operator=(const d6_array&)\n";
    ad_exit(1);
  }
#endif
  dvar5_array* pti = t + mmin;
  const d5_array* pmi = &m(mmin);
  for (int i=mmin; i<=mmax; i++)
  {
    *pti = *pmi;
    ++pti;
    ++pmi;
  }
  return *this;
}

/**
Allocate dvar6_array using dimensions from m1.
*/
void dvar6_array::allocate(const dvar6_array& m1)
{
  int min = m1.indexmin();
  int max = m1.indexmax();
  if ((shape=new vector_shape(min, max)) == 0)
  {
    cerr << " Error allocating memory in dvar6_array::allocate" << endl;
    ad_exit(1);
  }
  if ((t = new dvar5_array[size()]) == 0)
  {
    cerr << " Error allocating memory in dvar6_array::allocate" << endl;
    ad_exit(1);
  }
  t -= min;
  dvar5_array* pti = t + min;
  const dvar5_array* pm1i = &m1(min);
  for (int i = min; i <= max; ++i)
  {
    pti->allocate(*pm1i);
    ++pti;
    ++pm1i;
  }
}
/**
Allocate dvar6_array using dimensions from m1.
*/
void dvar6_array::allocate(const d6_array& m1)
{
  int min = m1.indexmin();
  int max = m1.indexmax();
  if ((shape=new vector_shape(min, max)) == 0)
  {
    cerr << "Error allocating memory in dvar5_array contructor" << endl;
    ad_exit(1);
  }
  if ((t = new dvar5_array[size()]) == 0)
  {
    cerr << "Error allocating memory in dvar5_array contructor" << endl;
    ad_exit(21);
  }
  t -= min;
  dvar5_array* pti = t + min;
  const d5_array* pm1i = &m1(min);
  for (int i = min; i <= max; ++i)
  {
    pti->allocate(*pm1i);
    ++pti;
    ++pm1i;
  }
}

  #ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    dvar5_array& dvar6_array::operator ( ) (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
        "dvar5_array& dvar6_array::operator()(int i)",
        indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar5_array& dvar6_array::operator [] (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
        "dvar5_array& dvar6_array::operator[](int i)",
        indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar4_array& dvar6_array::operator ( ) (int i ,int j)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar5_array& dvar6_array::operator()(int i, int j)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar3_array& dvar6_array::operator ( ) (int i,int j,int k)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar5_array& dvar6_array::operator()(int i, int j, int k)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_matrix& dvar6_array::operator ( ) (int i,int j,int k,int l)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar_matrix& dvar6_array::operator()(int i, int j, int k, int l)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_vector& dvar6_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
      "dvar_vector& dvar6_array::operator()(int i, int j, int k, int l, int m)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable dvar6_array::operator ( ) (int i,int j,int k,int l,int m,
      int n)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
"prevariable dvar6_array::operator()(int i, int j, int k, int l, int m, int n)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m,n);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar5_array& dvar6_array::operator()(int i) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar5_array& dvar6_array::operator ( )" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const dvar5_array& dvar6_array::operator[](int i) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar5_array& dvar6_array::operator []" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const dvar4_array& dvar6_array::operator()(int i ,int j) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar_matrix& dvar6_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar3_array& dvar6_array::operator()(int i, int j, int k) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
          "dvar_vector& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar_matrix& dvar6_array::operator()(int i, int j, int k, int l) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar-vector& dvar4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar_vector& dvar6_array::operator()(int i, int j, int k, int l, int m)
  const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
const prevariable dvar6_array::operator()(int i, int j, int k, int l, int m,
  int n) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m,n);
    }
#endif

/**
 * Description not yet available.
 * \param
 */
dvar6_array::dvar6_array(int hsl,int hsu)
{
  allocate(hsl,hsu);
}


/**
 * Description not yet available.
 * \param
 */
dvar6_array::dvar6_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}

/**
 * Description not yet available.
 * \param
 */
dvar6_array::dvar6_array(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5,
  const index_type& l6,const index_type& u6)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}

/**
 * Description not yet available.
 * \param
 */
void dvar6_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6)
 {
   if ( (shape=new vector_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   if ( (t = new dvar5_array[size()]) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   t -= hsl;
   dvar5_array* pti = t + hsl;
   for (int i=hsl; i<=hsu; i++)
   {
     pti->allocate(sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
     ++pti;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar6_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
   const index_type& nrh,const index_type& ncl,const index_type& nch,
   const index_type& l5,const index_type& u5,
   const index_type& l6,const index_type& u6)
 {
   if ( (shape=new vector_shape (hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
   }

   if ( (t = new dvar5_array[size()]) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   t -= hsl;
   dvar5_array* pti = t + hsl;
   for (int i = hsl; i <= hsu; ++i)
   {
     pti->allocate(ad_integer(sl(i)),ad_integer(sh(i)),nrl(i),nrh(i),
        ncl(i),nch(i),l5(i),u5(i),l6(i),u6(i));
     ++pti;
   }
 }

/**
Allocate vector of dvar5_array with dimension
[hsl to hsu].
\param hsl lower vector index
\param hsu upper vector index
*/
void dvar6_array::allocate(int hsl, int hsu)
{
  if ((shape = new vector_shape(hsl, hsu)) == 0)
  {
    cerr << " Error allocating memory in dvar5_array contructor\n";
    ad_exit(1);
  }
  if ((t = new dvar5_array[size()]) == 0)
  {
    cerr << " Error allocating memory in dvar5_array contructor\n";
    ad_exit(1);
  }
  t -= hsl;
  dvar5_array* pti = t + hsl;
  for (int i = hsl; i <= hsu; ++i)
  {
    pti->allocate();
    ++pti;
  }
}
