/*
 * $Id: d6arr.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
//#include <d4arr.hpp>
#include "admb_messages.h"

/**
 * Description not yet available.
 * \param
 */
 void d6_array::initialize(void)
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
 d6_array::d6_array(const d6_array& _m2)
 {
   d6_array& m2=(d6_array&) _m2;
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
 void d6_array::deallocate()
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
  //   cerr << "Warning -- trying to deallocate an unallocated d4_array"<<endl;
#    endif
   }
 }

/**
 * Description not yet available.
 * \param
 */
 d6_array::~d6_array() 
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 d6_array& d6_array::operator =  (_CONST d6_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   { 
     cerr << "Incompatible bounds in"
      " d6_array& d6_array:: operator =  (_CONST d6_array& m)"
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
 void d6_array::allocate(_CONST d6_array& m1)
 {
   if ( (shape=new vector_shape(m1.indexmin(),m1.indexmax()))
       == 0)
   {
     cerr << " Error allocating memory in d5_array contructor" << endl;
   }
   int ss=size();
   if ( (t = new d5_array[ss]) == 0)
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
    d5_array& d6_array::operator ( ) (int i)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds", "d5_array& d6_array::operator()(int i)", indexmin(), indexmax(), i);
      }
      #endif
      //return t[i];
      return elem(i);
    }

/**
 * Description not yet available.
 * \param
 */
    d5_array& d6_array::operator [] (int i)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("index out of bounds", "d5_array& d6_array::operator[](int i)", indexmin(), indexmax(), i);
      }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    d4_array& d6_array::operator ( ) (int i ,int j)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "d4_array& d6_array::operator()(int i, int j)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    d3_array& d6_array::operator ( ) (int i,int j,int k)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "d3_array& d6_array::operator()(int i, int j, int k)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    dmatrix& d6_array::operator ( ) (int i,int j,int k,int l)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dmatrix& d6_array::operator()(int i, int j, int k, int l)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    dvector& d6_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvector& d6_array::operator()(int i, int j, int k, int l, int m)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
    double& d6_array::operator ( ) (int i,int j,int k,int l,int m,int n)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      { 
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "double& d6_array::operator()(int i, int j, int k, int l, int m, int n)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k,l,m,n);
    }

   #ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
    _CONST d5_array& d6_array::operator ( ) (int i) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "d5_array& d6_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      //return t[i];
      return elem(i);
    }

/**
 * Description not yet available.
 * \param
 */
     _CONST d5_array& d6_array::operator [] (int i) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "d4_array& d6_array::operator []" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
     _CONST d4_array& d6_array::operator ( ) (int i ,int j) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dmatrix& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
     _CONST d3_array& d6_array::operator ( ) (int i,int j,int k) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
	    "dvector& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
     _CONST dmatrix& d6_array::operator ( ) (int i,int j,int k,int l) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
     _CONST dvector& d6_array::operator ( ) (int i,int j,int k,int l,int m) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
     _CONST double& d6_array::operator ( ) (int i,int j,int k,int l,int m,int n) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m,n);
    }


   #endif
  #endif


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

/**
 * Description not yet available.
 * \param
 */
void d6_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6)
 {
   if ( (shape=new vector_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   int ss=size();
   if ( (t = new d5_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=hsl; i<=hsu; i++)
   {
     t[i].allocate(sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void d6_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
   const index_type& sl,const index_type& sh,const index_type& nrl,
   const index_type& nrh,const index_type& ncl,const index_type& nch,
   const index_type& l5,const index_type& u5,
   const index_type& l6,const index_type& u6)
 {
   if ( (shape=new vector_shape (hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
   }

   int ss=size();
   if ( (t = new d5_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   int i1=hsl;
   int i2=hsu;
   for (int i=i1; i<=i2; i++)
   {
     (*this)(i).allocate(ad_integer(sl(i)),ad_integer(sh(i)),nrl(i),nrh(i),ncl(i),nch(i),
       l5(i),u5(i),l6(i),u6(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
double sum(_CONST d6_array& m)
{
  double tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  return tmp;
}
