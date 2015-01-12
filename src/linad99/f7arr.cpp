/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include "fvar.hpp"

 void dvar7_array::initialize(void)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i).initialize();
   }
 }

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

 dvar7_array::dvar7_array(d7_array& m2)
 {
   allocate(m2);
   (*this)=m2;
 }

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
   else
   { 
#    if defined(SAFE_ALL)
     //cerr << "Warning -- trying to deallocate an unallocated dvar5_array"<<endl;
#    endif
   }
 }

 dvar7_array::~dvar7_array() 
 {
   deallocate();
 }

 dvar7_array& dvar7_array::operator =  (_CONST dvar7_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   { 
     cerr << "Incompatible bounds in"
      " dvar5_array& dvar5_array:: operator =  (_CONST dvar5_array& m)"
      << endl;
     ad_exit(1);
    }
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i)=m(i);
   }
   return *this;
 }

 dvar7_array& dvar7_array::operator =  (_CONST d7_array& m)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   if (mmin!=m.indexmin() || mmax!=m.indexmax())
   { 
     cerr << "Incompatible bounds in"
      " dvar7_array& dvar7_array:: operator =  (_CONST d7_array& m)"
      << endl;
     ad_exit(1);
    }
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i)=m(i);
   }
   return *this;
 }

 void dvar7_array::allocate(_CONST dvar7_array& m1)
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

 void dvar7_array::allocate(_CONST d7_array& m1)
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

    dvar6_array& dvar7_array::operator ( ) (int i)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar6_array& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

    dvar6_array& dvar7_array::operator [] (int i)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar5_array& dvar6_array::operator []" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }


    dvar5_array& dvar7_array::operator ( ) (int i ,int j)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar3_array& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j);
    }

    dvar4_array& dvar7_array::operator ( ) (int i,int j,int k)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
	    "dvar_matrix& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k);
    }
    dvar3_array& dvar7_array::operator ( ) (int i,int j,int k,int l)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar-vector& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l);
    }

    dvar_matrix& dvar7_array::operator ( ) (int i,int j,int k,int l,int m)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m);
    }

    dvar_vector& dvar7_array::operator ( ) (int i,int j,int k,int l,int m,
      int n)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m,n);
    }

    prevariable dvar7_array::operator ( ) (int i,int j,int k,int l,int m,
      int n,int _p)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m,n,_p);
    }

   #ifdef USE_CONST
    _CONST dvar6_array& dvar7_array::operator ( ) (int i) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar6_array& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

     _CONST dvar6_array& dvar7_array::operator [] (int i) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error  index out of bounds in\n"
            "dvar5_array& dvar6_array::operator []" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }


     _CONST dvar5_array& dvar7_array::operator ( ) (int i ,int j) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar3_array& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j);
    }

     _CONST dvar4_array& dvar7_array::operator ( ) (int i,int j,int k) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
	    "dvar_matrix& dvar7_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k);
    }
     _CONST dvar3_array& dvar7_array::operator ( ) (int i,int j,int k,int l) _CONST 
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "dvar-vector& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l);
    }

     _CONST dvar_matrix& dvar7_array::operator ( ) (int i,int j,int k,int l,int m) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m);
    }

     _CONST dvar_vector& dvar7_array::operator ( ) (int i,int j,int k,int l,int m,
      int n) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m,n);
    }

     _CONST prevariable dvar7_array::operator ( ) (int i,int j,int k,int l,int m,  
      int n,int _p) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin()||i>indexmax())
        { cerr << "Error hslice index out of bounds in\n"
            "prevariable& dvar7_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return elem(i)(j,k,l,m,n,_p);
    }


   #endif
  #endif



dvar7_array::dvar7_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6,int l7,int u7)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6,l7,u7);
}

dvar7_array::dvar7_array(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5,
  const index_type& l6,const index_type& u6,
  const index_type& l7,const index_type& u7)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6,l7,u7);
}

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


