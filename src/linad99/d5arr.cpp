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
double sum(const d5_array& m)
{
  double tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
 d5_array::d5_array(const d5_array& _m2)
 {
   d5_array& m2=(d5_array&)_m2;
   if (m2.shape)
   {
     shape=m2.shape;
     (shape->ncopies)++;
     t = m2.t;
   }
   else
   {
     shape=NULL;
     t=NULL;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d5_array::deallocate()
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
       t=NULL;
       delete shape;
       shape=NULL;
     }
   }
#if defined(SAFE_ALL)
   else
   {
     cerr << "Warning -- trying to deallocate an unallocated d4_array"<<endl;
   }
#endif
 }

/**
Destructor
*/
d5_array::~d5_array()
{
  deallocate();
}
/**
 * Description not yet available.
 * \param
 */
d5_array& d5_array::operator=(const d5_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   {
     cerr << "Incompatible bounds in"
      " d4_array& d4_array:: operator =  (const d4_array& m)"
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
 void d5_array::initialize(void)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i).initialize();
   }
 }

/**
Allocate d5_array using other dimensions.

\param other d5_array
*/
void d5_array::allocate(const d5_array& other)
{
  allocate(other.indexmin(), other.indexmax());
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i).allocate(other.elem(i));
  }
}

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    d4_array& d5_array::operator ( ) (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
        "d4_array& d5_array::operator()(int i)", indexmin(), indexmax(), i);
      }
      //return t[i];
      return elem(i);
    }

/**
 * Description not yet available.
 * \param
 */
    d4_array& d5_array::operator [] (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds",
        "d4_array& d5_array::operator[](int i)", indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    d3_array& d5_array::operator ( ) (int i, int j)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "d3_array& d5_array::operator[](int i, int j)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dmatrix& d5_array::operator ( ) (int i,int j,int k)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dmatrix& d5_array::operator[](int i, int j, int k)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    dvector& d5_array::operator ( ) (int i,int j,int k,int l)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvector& d5_array::operator[](int i, int j, int k, int l)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    double& d5_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "double& d5_array::operator[](int i, int j, int k, int l, int m)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
const d4_array& d5_array::operator()(int i) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "d4_array& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const d4_array& d5_array::operator[](int i) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "d4_array& d5_array::operator []" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const d3_array& d5_array::operator()(int i, int j) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error index out of bounds in\n"
            "d3_array& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i).elem(j);
    }

/**
 * Description not yet available.
 * \param
 */
const dmatrix& d5_array::operator()(int i, int j, int k) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error index out of bounds in\n"
            "d3_array& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
const dvector& d5_array::operator()(int i, int j, int k, int l) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvector& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
const double& d5_array::operator()(int i, int j, int k, int l, int m) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvector& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m);
    }

#endif

/**
 * Description not yet available.
 * \param
 */
d5_array::d5_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5);
}

/**
 * Description not yet available.
 * \param
 */
d5_array::d5_array(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5);
}

/**
Allocate d5_array with specified dimensions.
*/
void d5_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5)
{
  if ((shape = new vector_shape(hsl, hsu)) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  unsigned int ss = size();
  if ((t = new d4_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  t -= indexmin();
  for (int i = hsl; i <= hsu; ++i)
  {
    t[i].allocate(sl, sh, nrl, nrh, ncl, nch, l5, u5);
  }
}

/**
 * Description not yet available.
 * \param
 */
 d5_array::d5_array(int hsl,int hsu)
 {
   allocate(hsl,hsu);
 }

/**
Allocate vector of d4_array with range [hsl, hsu].

\param hsl lower index
\param hsu upper index
*/
void d5_array::allocate(int hsl, int hsu)
{
  if ( (shape=new vector_shape(hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  unsigned int ss = size();
  if ( (t = new d4_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  t -= indexmin();
}

/**
Allocate d5_array with specified dimensions.
*/
void d5_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5)
{
  if ((shape = new vector_shape (hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
  }
  unsigned int ss = size();
  if ((t = new d4_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d5_array contructor\n";
    ad_exit(21);
  }
  t -= indexmin();
  int il = hsl;
  int iu = hsu;
  for (int i = il; i <= iu; ++i)
  {
    (*this)(i).allocate(ad_integer(sl(i)),ad_integer(sh(i)),nrl(i),nrh(i),
       ncl(i),nch(i), l5(i),u5(i));
  }
}
