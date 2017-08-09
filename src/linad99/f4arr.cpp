/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
#include "admb_messages.h"

/**
Construct vector of dvar4_array with dimension nrl to nrh.

\param nrl lower index
\param nrh upper index
*/
dvar4_array::dvar4_array(int nrl, int nrh)
{
  allocate(nrl, nrh);
}
/// Copy constructor
dvar4_array::dvar4_array(const dvar4_array& other)
{
  shallow_copy(other);
}
/**
Shallow copy other data structure pointers.

\param other dvar4_array
*/
void dvar4_array::shallow_copy(const dvar4_array& other)
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
    cerr << "Warning -- Unable to shallow copy an unallocated i3_array.\n";
#endif
    allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
 dvar4_array dvar4_array::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     dvar4_array tmp(nrl,nrh);
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
/// Deallocate dvar4_array memory.
void dvar4_array::deallocate()
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
#ifdef DEBUG
  else
  {
    cerr << "Warning -- Unable to deallocate an unallocated dvar4_array.\n";
  }
#endif
}

/**
Destructor
*/
dvar4_array::~dvar4_array()
{
  deallocate();
}

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    dvar3_array& dvar4_array::operator ( ) (int i)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar3_array& dvar4_array::operator() (int i)",
        hslicemin(), hslicemax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar3_array& dvar4_array::operator [] (int i)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar3_array& dvar4_array::operator[] (int i)",
        hslicemin(), hslicemax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_matrix& dvar4_array::operator ( ) (int i ,int j)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar_matrix& dvar4_array::operator() (int i, int j)",
        hslicemin(), hslicemax(), i);
      }
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_vector& dvar4_array::operator ( ) (int i,int j,int k)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar_vector& dvar4_array::operator() (int i, int j, int k)",
        hslicemin(), hslicemax(), i);
      }
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable dvar4_array::operator ( ) (int i,int j,int k,int l)
    {
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "prevariable& dvar4_array::operator() (int i, int j, int k)",
        hslicemin(), hslicemax(), i);
      }
      return ( ((*this)(i,j,k))(l));
    }

/**
 * Description not yet available.
 * \param
 */
const dvar3_array& dvar4_array::operator()(int i) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar3_array& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const dvar3_array& dvar4_array::operator[](int i) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar3_array& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const dvar_matrix& dvar4_array::operator()(int i, int j) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvarmatrix& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar_vector& dvar4_array::operator()(int i, int j, int k) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvarvector& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
const prevariable dvar4_array::operator()(int i, int j, int k, int l) const
    {
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& dvar4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return ( ((*this)(i,j,k))(l));
    }
#endif

/**
 * Description not yet available.
 * \param
 */
dvar4_array& dvar4_array::operator=(const d4_array& m)
 {
   int mmin=hslicemin();
   int mmax=hslicemax();
   if (mmin!=m.hslicemin() || mmax!=m.hslicemax())
   {
     cerr << "Incompatible bounds in"
      " dvar4_array& dvar4_array:: operator =  (const dvar4_array& m)"
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
 * Description not yet available.
 * \param
 */
 dvar4_array& dvar4_array::operator=(const dvar4_array& m)
 {
   int mmin=hslicemin();
   int mmax=hslicemax();
   if (mmin!=m.hslicemin() || mmax!=m.hslicemax())
   {
     cerr << "Incompatible bounds in"
      " dvar4_array& dvar4_array:: operator =  (const dvar4_array& m)"
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
Allocate variable array with dimensions
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower i4_array index
\param hsu upper i4_array index
\param sl lower i3_array index
\param su upper i3_array index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl lower matrix column index
\param nch upper matrix column index
*/
void dvar4_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  int nrl, int nrh,
  int ncl, int nch)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl, sh, nrl, nrh, ncl, nch);
  }
}
/**
Allocate variable array with dimensions
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower i4_array index
\param hsu upper i4_array index
\param sl lower i3_array index
\param su upper i3_array index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl vector of lower matrix column indexes
\param nch vector upper matrix column indexes
*/
void dvar4_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  int nrl, int nrh,
  const ivector& ncl, const ivector& nch)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i=hsl; i<=hsu; i++)
  {
    (*this)(i).allocate(sl, sh, nrl, nrh, ncl, nch);
  }
}

/**
Allocate variable array with dimensions
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower i4_array index
\param hsu upper i4_array index
\param sl lower i3_array index
\param su upper i3_array index
\param nrl lower matrix row index
\param nrh upper matrix row index
\param ncl lower matrix column index
\param nch upper matrix column index
*/
void dvar4_array::allocate(
  ad_integer hsl, ad_integer hsu,
  const index_type& sl, const index_type& sh,
  const index_type& nrl, const index_type& nrh,
  const index_type& ncl,const index_type& nch)
{
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }

  t -= hslicemin();

  int il = hsl;
  int iu = hsu;
  for (int i = il; i <= iu; ++i)
  {
    (*this)(i).allocate(sl(i), sh(i), nrl(i), nrh(i), ncl(i), nch(i));
  }
}
/**
 * Description not yet available.
 * \param
 */
void dvar4_array::allocate(
  ad_integer hsl, ad_integer hsu,
  const index_type& sl, const index_type& sh,
  const index_type& nrl, const index_type& nrh)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  int il = hsl;
  int iu = hsu;
  for (int i = il; i <= iu; ++i)
  {
    (*this)(i).allocate(sl(i), sh(i), nrl(i), nrh(i));
  }
}
/**
 * Description not yet available.
 * \param
 */
void dvar4_array::allocate(
  ad_integer hsl, ad_integer hsu,
  const index_type& sl, const index_type& sh)
{
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ( (t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  int il=hsl;
  int iu=hsu;
  for (int i = il; i <= iu; ++i)
  {
    (*this)(i).allocate(sl(i), sh(i));
  }
}
/**
Allocate vector of empty dvar3_array with dimension [hsl to hsu].
\param hsl lower vector index
\param hsu upper vector index
*/
void dvar4_array::allocate(ad_integer hsl, ad_integer hsu)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }

  t -= hslicemin();

  int il = hsl;
  int iu = hsu;
  for (int i = il; i <= iu; ++i)
  {
    (*this)(i).allocate();
  }
}
/**
Allocate array with dimensions
[hsl to hsu] x [sl to sh] x [nrl to nrh] x [ncl to nch].

\param hsl lower i4_array index
\param hsu upper i4_array index
\param sl lower i3_array index
\param su upper i3_array index
\param nrl vector of lower matrix row indexes
\param nrh vector of upper matrix row indexes
\param ncl vector of lower matrix column indexes
\param nch vector of upper matrix column indexes
*/
void dvar4_array::allocate(
  int hsl, int hsu,
  int sl, int sh,
  const ivector& nrl, const ivector& nrh,
  const ivector& ncl, const ivector& nch)
{
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl, sh, nrl(i), nrh(i), ncl(i), nch(i));
  }
}
/**
 * Description not yet available.
 * \param
 */
 dvar4_array::dvar4_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar4_array::dvar4_array(ad_integer hsl,ad_integer hsu,const index_type& sl,
   const index_type& sh, const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar4_array::dvar4_array(int hsl,int hsu, int sl,int sh,ivector nrl,
   ivector nrh,ivector ncl,ivector nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::initialize()
 {
   if (!(!(*this)))  // only initialize allocated objects
   {
     for (int i=hslicemin();i<=hslicemax();i++)
     {
       elem(i).initialize();
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
dvar4_array::dvar4_array(int hsl, int hsu, int sl, const ivector& sh,
  int nrl, const imatrix& nrh, int ncl, int nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }

/**
*/
void dvar4_array::allocate(
  int hsl, int hsu,
  int sl, const ivector& sh,
  int nrl, const imatrix& nrh,
  int ncl, int nch)
{
  //int rmin=nrh.rowmin();
  //int cmin=nrh(rmin).indexmin();
  if ((shape = new four_array_shape(hsl, hsu)) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hsl; i <= hsu; ++i)
  {
    (*this)(i).allocate(sl,sh(i),nrl,nrh(i),ncl,nch);
  }
}

/**
 * Description not yet available.
 * \param
 */
 dvar4_array::dvar4_array(const d4_array& m1)
 {
   allocate(m1);
   for (int i=hslicemin(); i<=hslicemax(); i++)
   {
     t[i]=m1[i];
   }
 }

/**
Allocate dvar4_array with same dimensions as m1.
*/
void dvar4_array::allocate(const d4_array& m1)
{
  if ((shape = new four_array_shape(m1.hslicemin(), m1.hslicemax())) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hslicemin(); i <= hslicemax(); ++i)
  {
     t[i].allocate(m1[i]);
  }
}
/**
Allocate dvar4_array with same dimensions as m1.
*/
void dvar4_array::allocate(const dvar4_array& m1)
{
  if ((shape = new four_array_shape(m1.hslicemin(),m1.hslicemax())) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  if ((t = new dvar3_array[hslicesize()]) == 0)
  {
    cerr << " Error: dvar4_array unable to allocate memory in "
         << __FILE__ << ':' << __LINE__ << '\n';
    ad_exit(1);
  }
  t -= hslicemin();
  for (int i = hslicemin(); i <= hslicemax(); ++i)
  {
    t[i].allocate(m1[i]);
  }
}

/*
dvar4_array::dvar4_array(int hsl,int hsu, int sl, const ivector& sh,int nrl,
    const imatrix& nrh,int ncl,int nch)
  {
    allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
  }

  void dvar4_array::allocate(int hsl,int hsu, int sl, const ivector& sh,int nrl,
    const imatrix& nrh,int ncl,int nch)
  {
   int rmin=nrh.rowmin();
   int cmin=nrh(nrh.rowmin()).indexmin;
   if ( (shape=new four_array_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar4_array contructor\n";
   }
   int ss=hslicesize();
   if ( (t = new dvar3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor\n";
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hsl; i<=hsu; i++)
   {
     (*this)(i).allocate(sl,sh(i),nrl,nrh(i),ncl,nch(i));
   }
 }
*/
