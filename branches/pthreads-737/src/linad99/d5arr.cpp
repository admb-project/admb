/*
 * $Id: d5arr.cpp 542 2012-07-10 21:04:06Z johnoel $
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
//#include <d4arr.hpp>

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
   else
   { 
#    if defined(SAFE_ALL)
    // cerr << "Warning -- trying to deallocate an unallocated d4_array"<<endl;
#    endif
   }
 }

/**
 * Description not yet available.
 * \param
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
 * Description not yet available.
 * \param
 */
void d5_array::allocate(const d5_array& m1)
 {
   if ( (shape=new vector_shape(m1.indexmin(),m1.indexmax()))
       == 0)
   {
     cerr << " Error allocating memory in d5_array contructor" << endl;
   }
   int ss=size();
   if ( (t = new d4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor" << endl;
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=indexmin(); i<=indexmax(); i++)
   {
     t[i].allocate(m1[i]);
   }
 }

  #ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    d4_array& d5_array::operator ( ) (int i)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds", "d4_array& d5_array::operator()(int i)", indexmin(), indexmax(), i);
      }
      #endif
      //return t[i];
      return elem(i);
    }

/**
 * Description not yet available.
 * \param
 */
    d4_array& d5_array::operator [] (int i)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds", "d4_array& d5_array::operator[](int i)", indexmin(), indexmax(), i);
      }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    d3_array& d5_array::operator ( ) (int i, int j)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "d3_array& d5_array::operator[](int i, int j)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dmatrix& d5_array::operator ( ) (int i,int j,int k)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dmatrix& d5_array::operator[](int i, int j, int k)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    dvector& d5_array::operator ( ) (int i,int j,int k,int l)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvector& d5_array::operator[](int i, int j, int k, int l)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    double& d5_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "double& d5_array::operator[](int i, int j, int k, int l, int m)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k,l,m);
    }

   #ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
const d4_array& d5_array::operator()(int i) const
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "d4_array& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const d4_array& d5_array::operator[](int i) const
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "d4_array& d5_array::operator []" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const d3_array& d5_array::operator()(int i, int j) const
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error index out of bounds in\n"
            "d3_array& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i).elem(j);
    }

/**
 * Description not yet available.
 * \param
 */
const dmatrix& d5_array::operator()(int i, int j, int k) const
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error index out of bounds in\n"
            "d3_array& d5_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
const dvector& d5_array::operator()(int i, int j, int k, int l) const
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvector& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
const double& d5_array::operator()(int i, int j, int k, int l, int m) const
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvector& d5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m);
    }

   #endif
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
 * Description not yet available.
 * \param
 */
void d5_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5)
 {
   if ( (shape=new vector_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   int ss=size();
   if ( (t = new d4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=hsl; i<=hsu; i++)
   {
     t[i].allocate(sl,sh,nrl,nrh,ncl,nch,l5,u5);
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
 * Description not yet available.
 * \param
 */
 void d5_array::allocate(int hsl,int hsu)
 {
   if ( (shape=new vector_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   int ss=size();
   if ( (t = new d4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
 }

/**
 * Description not yet available.
 * \param
 */
 void d5_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
   const index_type& sl,const index_type& sh,const index_type& nrl,
   const index_type& nrh,const index_type& ncl,const index_type& nch,
   const index_type& l5,const index_type& u5)
 {
   if ( (shape=new vector_shape (hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
   }

   int ss=size();
   if ( (t = new d4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   int il=hsl;
   int iu=hsu;
   for (int i=il; i<=iu; i++)
   {
     (*this)(i).allocate(ad_integer(sl(i)),ad_integer(sh(i)),nrl(i),nrh(i),ncl(i),nch(i),
       l5(i),u5(i));
   }
 }
