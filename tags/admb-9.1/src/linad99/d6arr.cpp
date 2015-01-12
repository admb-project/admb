/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"
//#include <d4arr.hpp>

 void d6_array::initialize(void)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i).initialize();
   }
 }


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

 d6_array::~d6_array() 
 {
   deallocate();
 }

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

    d5_array& d6_array::operator ( ) (int i)
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

    d5_array& d6_array::operator [] (int i)
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


    d4_array& d6_array::operator ( ) (int i ,int j)
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

    d3_array& d6_array::operator ( ) (int i,int j,int k)
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
    dmatrix& d6_array::operator ( ) (int i,int j,int k,int l)
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

    dvector& d6_array::operator ( ) (int i,int j,int k,int l,int m)
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

    double& d6_array::operator ( ) (int i,int j,int k,int l,int m,int n)
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

   #ifdef USE_CONST

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



d6_array::d6_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int l5,int u5,int l6,int u6)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}

d6_array::d6_array(const ad_integer& hsl,const ad_integer& hsu,
  const index_type& sl,const index_type& sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch,
  const index_type& l5,const index_type& u5,
  const index_type& l6,const index_type& u6)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch,l5,u5,l6,u6);
}

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

    
double sum(_CONST d6_array& m)
{
  double tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  return tmp;
}
    

