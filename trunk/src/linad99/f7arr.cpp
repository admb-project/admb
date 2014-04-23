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
 void dvar7_array::initialize(void)
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
void dvar7_array::allocate(int l7,int u7)
{
  if ( (shape=new vector_shape(l7,u7)) == 0)
  {
    cerr << " Error allocating memory in d6_array contructor\n";
    ad_exit(21);
  }
  int ss=size();
  if ( (t = new dvar6_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d6_array contructor\n";
    ad_exit(21);
  }
  t -= indexmin();
  for (int i=l7; i<=u7; i++)
  {
    t[i].allocate();
  }
}

/**
 * Description not yet available.
 * \param
 */
 dvar7_array::dvar7_array(dvar7_array& m2)
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
 dvar7_array::dvar7_array(d7_array& m2)
 {
   allocate(m2);
   (*this)=m2;
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar7_array::deallocate()
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
#if defined(ADWARN_DEV)
   else
   {
     cerr << "Warning -- trying to deallocate an unallocated dvar5_array"<<endl;
   }
#endif
 }

/**
 * Description not yet available.
 * \param
 */
 dvar7_array::~dvar7_array()
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 dvar7_array& dvar7_array::operator=(const dvar7_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   {
     cerr << "Incompatible bounds in"
      " dvar5_array& dvar5_array:: operator =  (const dvar5_array& m)"
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
dvar7_array& dvar7_array::operator=(const d7_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   {
     cerr << "Incompatible bounds in"
      " dvar7_array& dvar7_array:: operator =  (const d7_array& m)"
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
void dvar7_array::allocate(const dvar7_array& m1)
 {
   if ( (shape=new vector_shape(m1.indexmin(),m1.indexmax()))
       == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor" << endl;
   }
   int ss=size();
   if ( (t = new dvar6_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor" << endl;
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
void dvar7_array::allocate(const d7_array& m1)
 {
   if ( (shape=new vector_shape(m1.indexmin(),m1.indexmax()))
       == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor" << endl;
   }
   int ss=size();
   if ( (t = new dvar6_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor" << endl;
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
    dvar6_array& dvar7_array::operator ( ) (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar6_array& dvar7_array::operator () (int i)",
        indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar6_array& dvar7_array::operator [] (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar6_array& dvar7_array::operator [] (int i)",
        indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    dvar5_array& dvar7_array::operator ( ) (int i ,int j)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar5_array& dvar7_array::operator ( ) (int i, int j)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar4_array& dvar7_array::operator ( ) (int i,int j,int k)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar4_array& dvar7_array::operator ( ) (int i, int j, int k)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar3_array& dvar7_array::operator ( ) (int i,int j,int k,int l)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
        "dvar3_array& dvar7_array::operator ( ) (int i, int j, int k, int l)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_matrix& dvar7_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
   "dvar_matrix& dvar7_array::operator ( ) (int i, int j, int k, int l, int m)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar7_array::operator ( ) (int i,int j,int k,int l,int m, int n)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
"dvar_vector& dvar7_array::operator()(int i,int j, int k, int l, int m, int n)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m,n);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable dvar7_array::operator()(int i,int j,int k,int l,int m, int n,int _p)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("hslice index out of bounds",
"dvar7_array::operator()(int i, int j, int k, int l, int m, int n, int _p)",
        indexmin(), indexmax(), i);
      }
      return elem(i)(j,k,l,m,n,_p);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar6_array& dvar7_array::operator()(int i) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar6_array& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const dvar6_array& dvar7_array::operator[](int i) const
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
const dvar5_array& dvar7_array::operator()(int i ,int j) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar3_array& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i)(j);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar4_array& dvar7_array::operator()(int i,int j,int k) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
          "dvar_matrix& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      return elem(i)(j,k);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar3_array& dvar7_array::operator()(int i, int j, int k, int l) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar-vector& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar_matrix& dvar7_array::operator()(int i, int j, int k, int l, int m)
  const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m);
    }

/**
 * Description not yet available.
 * \param
 */
const dvar_vector& dvar7_array::operator()(int i, int j, int k, int l, int m,
  int n) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m,n);
    }

/**
 * Description not yet available.
 * \param
 */
const prevariable dvar7_array::operator()(int i, int j, int k, int l, int m,
   int n, int _p) const
    {
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      return elem(i)(j,k,l,m,n,_p);
    }
#endif

/**
 * Description not yet available.
 * \param
 */
dvar7_array::dvar7_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6,int l7,int u7)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6,l7,u7);
}

/**
 * Description not yet available.
 * \param
 */
dvar7_array::dvar7_array(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5,
  const index_type& l6,const index_type& u6,
  const index_type& l7,const index_type& u7)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6,l7,u7);
}

/**
 * Description not yet available.
 * \param
 */
void dvar7_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6,int l7,int u7)
 {
   if ( (shape=new vector_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor\n";
     ad_exit(21);
   }
   int ss=size();
   if ( (t = new dvar6_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=hsl; i<=hsu; i++)
   {
     (*this)(i).allocate(sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6,l7,u7);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void dvar7_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
   const index_type& nrh,const index_type& ncl,const index_type& nch,
   const index_type& l5,const index_type& u5,
   const index_type& l6,const index_type& u6,
   const index_type& l7,const index_type& u7)
 {
   if ( (shape=new vector_shape (hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor\n";
   }

   int ss=size();
   if ( (t = new dvar6_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar6_array contructor\n";
     ad_exit(21);
   }
   t -= indexmin();
   int il=hsl;
   int iu=hsu;
   for (int i=il; i<=iu; i++)
   {
     t[i].allocate(ad_integer(sl(i)),ad_integer(sh(i)),nrl(i),nrh(i),
        ncl(i),nch(i),l5(i),u5(i),l6(i),u6(i),l7(i),u7(i));
   }
 }
