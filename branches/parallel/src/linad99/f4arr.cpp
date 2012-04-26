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
#include <d4arr.hpp>
#include "admb_messages.h"

/**
 * Description not yet available.
 * \param
 */
 dvar4_array::dvar4_array(int nrl,int nrh)
 {
   allocate(nrl,nrh);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar4_array::dvar4_array(const dvar4_array& m2)
 {
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
 void dvar4_array::shallow_copy(const dvar4_array& m2)
 {
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

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::deallocate()
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       t += hslicemin();
       delete [] t;
       t=NULL;
       delete shape;
       shape=NULL;
     }
   }
   else
   { 
#    if defined(SAKE_ARRAYS)
       //cerr << "Warning -- trying to deallocate an unallocated d4_array"<<endl;
#    endif
   }
 }

/**
 * Description not yet available.
 * \param
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
      #ifdef SAFE_ARRAYS
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar3_array& dvar4_array::operator() (int i)", hslicemin(), hslicemax(), i);
      }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar3_array& dvar4_array::operator [] (int i)
    {
      #ifdef SAFE_ARRAYS
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar3_array& dvar4_array::operator[] (int i)", hslicemin(), hslicemax(), i);
      }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_matrix& dvar4_array::operator ( ) (int i ,int j)
    {
      #ifdef SAFE_ARRAYS
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar_matrix& dvar4_array::operator() (int i, int j)", hslicemin(), hslicemax(), i);
      }
      #endif
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_vector& dvar4_array::operator ( ) (int i,int j,int k)
    {
      #ifdef SAFE_ARRAYS
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "dvar_vector& dvar4_array::operator() (int i, int j, int k)", hslicemin(), hslicemax(), i);
      }
      #endif
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable dvar4_array::operator ( ) (int i,int j,int k,int l)
    {
      #ifdef SAFE_ARRAYS
      if (i < hslicemin() || i > hslicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds", "prevariable& dvar4_array::operator() (int i, int j, int k)", hslicemin(), hslicemax(), i);
      }
      #endif
      return ( ((*this)(i,j,k))(l));
    }

    #ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar3_array& dvar4_array::operator ( ) (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
	if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar3_array& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar3_array& dvar4_array::operator [] (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar3_array& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar_matrix& dvar4_array::operator ( ) (int i ,int j) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvarmatrix& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST dvar_vector& dvar4_array::operator ( ) (int i,int j,int k) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
	    "dvarvector& dvar4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
    _CONST prevariable dvar4_array::operator ( ) (int i,int j,int k,int l) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& dvar4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return ( ((*this)(i,j,k))(l));
    }

   #endif
  #endif

/**
 * Description not yet available.
 * \param
 */
 dvar4_array& dvar4_array:: operator =  (_CONST d4_array& m)
 {
   int mmin=hslicemin();
   int mmax=hslicemax();
   if (mmin!=m.hslicemin() || mmax!=m.hslicemax())
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
 dvar4_array& dvar4_array:: operator =  (_CONST dvar4_array& m)
 {
   int mmin=hslicemin();
   int mmax=hslicemax();
   if (mmin!=m.hslicemin() || mmax!=m.hslicemax())
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
void dvar4_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch)
 {
   if ( (shape=new four_array_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar3_array contructor\n";
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
     (*this)(i).allocate(sl,sh,nrl,nrh,ncl,nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
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
     (*this)(i).allocate(sl,sh,nrl,nrh,ncl,nch);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(ad_integer hsl,ad_integer hsu,const index_type& sl,
   const index_type& sh,const index_type& nrl,
   const index_type& nrh, const index_type& ncl,const index_type& nch)
 {
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
   int il=hsl;
   int iu=hsu;
   for (int i=il; i<=iu; i++)
   {
     (*this)(i).allocate(sl(i),sh(i),nrl(i),nrh(i),ncl(i),nch(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(ad_integer hsl,ad_integer hsu,const index_type& sl,
   const index_type& sh,const index_type& nrl,
   const index_type& nrh)
 {
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
   int il=hsl;
   int iu=hsu;
   for (int i=il; i<=iu; i++)
   {
     (*this)(i).allocate(sl(i),sh(i),nrl(i),nrh(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(ad_integer hsl,ad_integer hsu,const index_type& sl,
   const index_type& sh)
 {
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
   int il=hsl;
   int iu=hsu;
   for (int i=il; i<=iu; i++)
   {
     (*this)(i).allocate(sl(i),sh(i));
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(ad_integer hsl,ad_integer hsu)
 {
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
   int il=hsl;
   int iu=hsu;
   for (int i=il; i<=iu; i++)
   {
     (*this)(i).allocate();
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(int hsl,int hsu,int sl,int sh,_CONST ivector& nrl,
   _CONST ivector& nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
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
     (*this)(i).allocate(sl,sh,nrl(i),nrh(i),ncl(i),nch(i));
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
 dvar4_array::dvar4_array(ad_integer hsl,ad_integer hsu,const index_type& sl,const index_type& sh,
   const index_type& nrl,const index_type& nrh,const index_type& ncl,const index_type& nch)
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
 dvar4_array::dvar4_array(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch)
 {
   //int rmin=nrh.rowmin();
   //int cmin=nrh(rmin).indexmin();
   if ( (shape=new four_array_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d4_array contructor\n";
   }

   int ss=hslicesize();
   if ( (t = new dvar3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hsl; i<=hsu; i++)
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
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(_CONST d4_array& m1)
 {
   if ( (shape=new four_array_shape(m1.hslicemin(),m1.hslicemax()))
       == 0)
   {
     cerr << " Error allocating memory in dvar4_array contructor" << endl;
   }
   int ss=hslicesize();
   if ( (t = new dvar3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar4_array contructor" << endl;
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hslicemin(); i<=hslicemax(); i++)
   {
     t[i].allocate(m1[i]);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar4_array::allocate(_CONST dvar4_array& m1)
 {
   if ( (shape=new four_array_shape(m1.hslicemin(),m1.hslicemax()))
       == 0)
   {
     cerr << " Error allocating memory in dvar4_array contructor" << endl;
   }
   int ss=hslicesize();
   if ( (t = new dvar3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar4_array contructor" << endl;
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hslicemin(); i<=hslicemax(); i++)
   {
     t[i].allocate(m1[i]);
   }
 }

/*
  dvar4_array::dvar4_array(int hsl,int hsu, int sl,_CONST ivector& sh,int nrl,
    _CONST imatrix& nrh,int ncl,int nch)
  {
    allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
  }

  void dvar4_array::allocate(int hsl,int hsu, int sl,_CONST ivector& sh,int nrl,
    _CONST imatrix& nrh,int ncl,int nch)
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

