/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>
void i5_array::allocate(void)
{
  t=0;
  shape=0;
}
i5_array::i5_array(void)
{
  allocate();
}

i5_array::i5_array(int hsl,int hsu)
{
  allocate(hsl,hsu);
}

void i5_array::allocate(int hsl,int hsu)
{
  int ss=hsu-hsl+1;
  if (ss>0)
  {
    if ( (t = new i4_array[ss]) == 0)
    {
      cerr << " Error allocating memory in i5_array contructor\n";
      ad_exit(21);
    }
    if ( (shape=new vector_shapex(hsl,hsu,t)) == 0)
    {
      cerr << " Error allocating memory in i5_array contructor\n";
      ad_exit(21);
    }
    t -= indexmin();
    for (int i=hsl; i<=hsu; i++)
    {
      (*this)(i).allocate();
    }
  }
  else
  {
    t=0;
    shape=0;
  }
}

void i5_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int aa,int bb)
 {
   int ss=hsu-hsl+1;
   if (ss>0)
   {
     if ( (t = new i4_array[ss]) == 0)
     {
       cerr << " Error allocating memory in i5_array contructor\n";
       ad_exit(21);
     }
     if ( (shape=new vector_shapex(hsl,hsu,t)) == 0)
     {
       cerr << " Error allocating memory in i5_array contructor\n";
       ad_exit(21);
     }
     t -= indexmin();
     for (int i=hsl; i<=hsu; i++)
     {
       (*this)(i).allocate(sl,sh,nrl,nrh,ncl,nch,aa,bb);
     }
   }
   else
   {
     t=0;
     shape=0;
   }
 }
 void i5_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
   const index_type& sl,const index_type& sh,
   const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch,
   const index_type& aa,const index_type& bb)
 {
   int ss=hsu-hsl+1;
   if (ss>0)
   {
     if ( (t = new i4_array[ss]) == 0)
     {
       cerr << " Error allocating memory in i5_array contructor\n";
       ad_exit(21);
     }
     if ( (shape=new vector_shapex(hsl,hsu,t)) == 0)
     {
       cerr << " Error allocating memory in i5_array contructor\n";
       ad_exit(21);
     }
     t -= indexmin();
     for (int i=hsl; i<=hsu; i++)
     {
       (*this)(i).allocate(ad_integer(sl),ad_integer(sh),nrl(i),nrh(i),
         ncl(i),nch(i),aa(i),bb(i));
     }
   }
   else
   {
     t=0;
     shape=0;
   }
 }


 i5_array::i5_array(_CONST i5_array& m2)
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

 i5_array::~i5_array()
 {
   deallocate();
 }

 void i5_array::deallocate()
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       t= (i4_array*) (shape->get_truepointer());
       delete [] t;
       t=NULL;
       delete shape;
       shape=NULL;
     }
   }
 }

#if !defined (OPT_LIB)
    i4_array& i5_array::operator ( ) (int i)
    {
#     if defined(SAFE_ARRAYS)
      if (i<indexmin() || i>indexmax())
      {
	cerr << "Index out of bounds in i5_array::operator () (int)"
	     << endl;
        ad_exit(1);
      }
#     endif
      return t[i];
    }

    i4_array& i5_array::operator [] (int i)
    {
#     if defined(SAFE_ARRAYS)
      if (i<indexmin() || i>indexmax())
      {
	cerr << "Index out of bounds in i5_array::operator () (int)"
	     << endl;
        ad_exit(1);
      }
#     endif
      return t[i];
    }
    i3_array& i5_array::operator ( ) (int i ,int j)
    {
      return ((*this)(i))(j);
    }

    imatrix& i5_array::operator ( ) (int i,int j,int k)
    {
      return (((*this)(i,j))(k));
    }
    ivector& i5_array::operator ( ) (int i,int j,int k,int l)
    {
      return ( ((*this)(i,j,k))(l));
    }

    int& i5_array::operator ( ) (int i,int j,int k,int l,int ll)
    {
      return ( ((*this)(i,j,k))(l,ll));
    }

#if defined(USE_CONST)
    _CONST i4_array& i5_array::operator ( ) (int i)   _CONST 
    {
#     if defined(SAFE_ARRAYS)
      if (i<indexmin() || i>indexmax())
      {
	cerr << "Index out of bounds in i5_array::operator () (int)"
	     << endl;
        ad_exit(1);
      }
#     endif
      return t[i];
    }

    _CONST i4_array& i5_array::operator [] (int i) _CONST
    {
#     if defined(SAFE_ARRAYS)
      if (i<indexmin() || i>indexmax())
      {
	cerr << "Index out of bounds in i5_array::operator () (int)"
	     << endl;
        ad_exit(1);
      }
#     endif
      return t[i];
    }
     _CONST i3_array& i5_array::operator ( ) (int i ,int j) _CONST
    {
      return ((*this)(i))(j);
    }
    _CONST imatrix& i5_array::operator ( ) (int i,int j,int k) _CONST
    {
      return (((*this)(i,j))(k));
    }
    _CONST ivector&  i5_array::operator ( ) (int i,int j,int k,int l) _CONST
    {
      return ( ((*this)(i,j,k))(l));
    }
    _CONST int&  i5_array::operator ( ) (int i,int j,int k,int l,int ll) _CONST
    {
      return ( ((*this)(i,j,k))(l,ll));
    }
#endif
#endif

