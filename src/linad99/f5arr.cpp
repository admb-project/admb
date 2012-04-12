/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
 void dvar5_array::initialize(void)
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
 dvar5_array dvar5_array::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     dvar5_array tmp(nrl,nrh);
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
 * Description not yet available.
 * \param
 */
 dvar5_array::dvar5_array(const dvar5_array& _m2)
 {
   dvar5_array& m2=(dvar5_array&) _m2;
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
 dvar5_array::dvar5_array(const d5_array& _m2)
 {
   d5_array& m2=(d5_array&) _m2;
   allocate(m2);
   (*this)=m2;
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar5_array::deallocate()
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
   //  cerr << "Warning -- trying to deallocate an unallocated dvar4_array"<<endl;
#    endif
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar5_array::~dvar5_array() 
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 dvar5_array& dvar5_array::operator =  (_CONST dvar5_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   { 
     cerr << "Incompatible bounds in"
      " dvar4_array& dvar4_array:: operator =  (_CONST dvar4_array& m)"
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
 dvar5_array& dvar5_array::operator =  (_CONST d5_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   { 
     cerr << "Incompatible bounds in"
      " dvar4_array& dvar4_array:: operator =  (_CONST dvar4_array& m)"
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
 void dvar5_array::allocate(_CONST dvar5_array& m1)
 {
   if ( (shape=new vector_shape(m1.indexmin(),m1.indexmax()))
       == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor" << endl;
   }
   int ss=size();
   if ( (t = new dvar4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor" << endl;
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=indexmin(); i<=indexmax(); i++)
   {
     t[i].allocate(m1[i]);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar5_array::allocate(_CONST d5_array& m1)
 {
   if ( (shape=new vector_shape(m1.indexmin(),m1.indexmax()))
       == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor" << endl;
   }
   int ss=size();
   if ( (t = new dvar4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor" << endl;
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
    dvar4_array& dvar5_array::operator ( ) (int i)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
       ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar3_array& dvar5_array::operator () (int i)", indexmin(), indexmax(), i);
      }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar4_array& dvar5_array::operator [] (int i)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
       ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar3_array& dvar5_array::operator [] (int i)", indexmin(), indexmax(), i);
      }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar3_array& dvar5_array::operator ( ) (int i ,int j)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
       ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar3_array& dvar5_array::operator ( ) (int i,int j)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_matrix& dvar5_array::operator ( ) (int i,int j,int k)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
       ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar_matrix& dvar5_array::operator ( ) (int i,int j,int k)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_vector& dvar5_array::operator ( ) (int i,int j,int k,int l)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
       ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar_vector& dvar5_array::operator ( ) (int i,int j,int k,int l)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable dvar5_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      #ifdef SAFE_ARRAYS
      if (i < indexmin() || i > indexmax())
      {
       ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "prevariable dvar5_array::operator ( ) (int i,int j,int k,int l,int m)", indexmin(), indexmax(), i);
      }
      #endif
      return elem(i)(j,k,l,m);
    }

   #ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar4_array& dvar5_array::operator ( ) (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar4_array& dvar5_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar4_array& dvar5_array::operator [] (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar4_array& dvar5_array::operator []" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar3_array& dvar5_array::operator ( ) (int i ,int j) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error index out of bounds in\n"
            "dvar3_array& dvar5_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar_matrix& dvar5_array::operator ( ) (int i,int j,int k) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error index out of bounds in\n"
            "dvar3_array& dvar5_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar_vector& dvar5_array::operator ( ) (int i,int j,int k,int l) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar_vector& dvar5_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST prevariable dvar5_array::operator ( ) (int i,int j,int k,int l,int m) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar_vector& dvar5_array::operator ( )"  << endl;
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
dvar5_array::dvar5_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5);
}

/**
 * Description not yet available.
 * \param
 */
dvar5_array::dvar5_array(const ad_integer& hsl,const ad_integer& hsu,
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
void dvar5_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5)
 {
   if ( (shape=new vector_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   int ss=size();
   if ( (t = new dvar4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=hsl; i<=hsu; i++)
   {
     (*this)(i).allocate(sl,sh,nrl,nrh,ncl,nch,l5,u5);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar5_array::dvar5_array(int hsl,int hsu)
 {
   allocate(hsl,hsu);
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar5_array::allocate(int hsl,int hsu)
 {
   if ( (shape=new vector_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   int ss=size();
   if ( (t = new dvar4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=indexmin(); i<=indexmax(); i++)
   {
     t[i].allocate();
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar5_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
   const index_type& nrh,const index_type& ncl,const index_type& nch,
   const index_type& l5,const index_type& u5)
 {
   if ( (shape=new vector_shape (hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
   }

   int ss=size();
   if ( (t = new dvar4_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar5_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   int il=hsl;
   int iu=hsu;
   for (int i=il; i<=iu; i++)
   {
     t[i].allocate(ad_integer(sl(i)),ad_integer(sh(i)),nrl(i),nrh(i),
        ncl(i),nch(i),l5(i),u5(i));
   }
 }
