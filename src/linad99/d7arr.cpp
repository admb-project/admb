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
//#include <d5arr.hpp>
#include "admb_messages.h"

/// Initialize all d7_array elements to zero.
void d7_array::initialize()
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i).initialize();
  }
}
/// Copy constructor (shallow)
d7_array::d7_array(d7_array& other)
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
/// Deallocate d7_array memory.
void d7_array::deallocate()
{
  if (shape)
  {
    if (shape->ncopies)
    {
      (shape->ncopies)--;
    }
    else
    {
      t += indexmin();
      delete [] t;
      delete shape;
      allocate();
    }
  }
#if defined(SAFE_ALL)
  else
  {
    cerr << "Warning -- trying to deallocate an unallocated d7_array.\n";
  }
#endif
}
/// Destructor
d7_array::~d7_array()
{
  deallocate();
}
/**
 * Description not yet available.
 * \param
 */
d7_array& d7_array::operator=(const d7_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   {
     cerr << "Incompatible bounds in"
      " d7_array& d7_array:: operator =  (const d7_array& m)"
      << endl;
     ad_exit(1);
    }
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i)=m(i);
   }
   return *this;
 }
/**
Allocate d7_array using the same dimensions as other.

\param other d7_array
*/
void d7_array::allocate(const d7_array& other)
{
  allocate(other.indexmin(), other.indexmax());
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i).allocate(other.elem(i));
  }
}

  #ifndef OPT_LIB

/**
Return d6_array element at index i.
Note: Exits for out of bounds index.

\param i index
*/
d6_array& d7_array::operator()(int i)
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
      "d6_array& d7_array::operator()(int i)", indexmin(), indexmax(), i);
  }
  return elem(i);
}
/**
Return d6_array element at index i.
Note: Exits for out of bounds index.

\param i index
*/
const d6_array& d7_array::operator()(int i) const
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
      "d6_array& d7_array::operator()(int i)", indexmin(), indexmax(), i);
  }
  return elem(i);
}
/**
Return d6_array element at index i.
Note: Exits for out of bounds index.

\param i index
*/
d6_array& d7_array::operator[](int i)
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
      "d6_array& d7_array::operator[](int i)", indexmin(), indexmax(), i);
  }
  return elem(i);
}
/**
Return d6_array element at index i.
Note: Exits for out of bounds index.

\param i index
*/
const d6_array& d7_array::operator[](int i) const
{
  if (i < indexmin() || i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
      "const d6_array& d7_array::operator[](int i) const",
      indexmin(), indexmax(), i);
  }
  return elem(i);
}

/**
 * Description not yet available.
 * \param
 */
    d5_array& d7_array::operator ( ) (int i ,int j)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "d5_array& d7_array::operator()(int i, int j)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    d4_array& d7_array::operator ( ) (int i,int j,int k)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "d4_array& d7_array::operator()(int i, int j, int k)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    d3_array& d7_array::operator ( ) (int i,int j,int k,int l)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "d3_array& d7_array::operator()(int i, int j, int k, int l)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    dmatrix& d7_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dmatrix& d7_array::operator()(int i, int j, int k, int l, int m)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
    dvector& d7_array::operator ( ) (int i,int j,int k,int l,int m,int n)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
      "dvector& d7_array::operator()(int i, int j, int k, int l, int m, int n)",
         indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m,n);
    }

/**
 * Description not yet available.
 * \param
 */
    double& d7_array::operator ( ) (int i,int j,int k,int l,int m,int n,int _p)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
"double& d7_array::operator()(int i, int j,int k,int l, int m, int n, int _p)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m,n,_p);
    }


/**
 * Description not yet available.
 * \param
 */
const d5_array& d7_array::operator()(int i,int j) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "d3_array& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
const d4_array& d7_array::operator()(int i, int j, int k) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
          "dmatrix& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
const d3_array& d7_array::operator()(int i, int j, int k, int l) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
const dmatrix& d7_array::operator()(int i, int j, int k, int l, int m) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
const dvector& d7_array::operator()(int i, int j, int k, int l, int m, int n)
  const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m,n);
    }

/**
 * Description not yet available.
 * \param
 */
const double& d7_array::operator()(int i, int j, int k, int l, int m, int n,
  int _p) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m,n,_p);
    }
#endif

/**
 * Description not yet available.
 * \param
 */
d7_array::d7_array(int l7,int u7,int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6)
{
  allocate(l7,u7,hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}

/**
 * Description not yet available.
 * \param
 */
d7_array::d7_array(const ad_integer& l7,const ad_integer& u7,
  const index_type& hsl,const index_type& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5,
  const index_type& l6,const index_type& u6)
{
  allocate(l7,u7,hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}
/**
Allocate a d7_array with indices.
*/
void d7_array::allocate(int l7, int u7, int hsl, int hsu, int sl, int sh,
  int nrl, int nrh, int ncl, int nch, int l5, int u5, int l6, int u6)
{
  allocate(l7, u7);
  for (int i = l7; i <= u7; ++i)
  {
    elem(i).allocate(hsl, hsu, sl, sh, nrl, nrh, ncl, nch, l5, u5, l6, u6);
  }
}
/**
Allocate a vector of empty d6_arrays.
Note: l7 should be greater or equal to u7.

\param l7 lower index
\param u7 upper index
*/
void d7_array::allocate(int l7, int u7)
{
  if (l7 > u7)
  {
    return allocate();
  }
  if ((shape = new vector_shape(l7, u7)) == 0)
  {
    cerr << "Error: Unable to allocate d7_array memory in "
         << "d7_array::allocate(int, int).\n"; 
    ad_exit(1);
  }
  if ((t = new d6_array[size()]) == 0)
  {
    cerr << "Error: Unable to allocate d7_array memory in "
         << "d7_array::allocate(int, int).\n"; 
    ad_exit(1);
  }
  t -= indexmin();
  for (int i = l7; i <= u7; ++i)
  {
    elem(i).allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
 void d7_array::allocate(const ad_integer& l7,const ad_integer& u7,
   const index_type& hsl,const index_type& hsu,
   const index_type& sl,const index_type& sh,const index_type& nrl,
   const index_type& nrh,const index_type& ncl,const index_type& nch,
   const index_type& l5,const index_type& u5,
   const index_type& l6,const index_type& u6)
 {
   if ( (shape=new vector_shape (l7,u7)) == 0)
   {
     cerr << " Error allocating memory in d6_array contructor\n";
   }

   unsigned int ss = size();
   if ( (t = new d6_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d6_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   int i1=l7;
   int iu=u7;
   for (int i=i1; i<=iu; i++)
   {
     (*this)(i).allocate(ad_integer(hsl(i)),ad_integer(hsu(i)),
       sl(i),sh(i),nrl(i),nrh(i),ncl(i),nch(i),l5(i),u5(i),l6(i),u6(i));
   }
 }
