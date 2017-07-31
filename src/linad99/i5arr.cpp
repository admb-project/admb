/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include "admb_messages.h"

/// Default constructor
i5_array::i5_array()
{
  allocate();
}
/// Does NOT allocate, but initializes i5_array members.
void i5_array::allocate()
{
  t = nullptr;
  shape = nullptr;
}
/**
Construct vector of i4_array with dimension
[hsl to hsu].
\param lower vector index
\param upper vector index
*/
i5_array::i5_array(int hsl, int hsu)
{
  allocate(hsl,hsu);
}
/**
Allocate vector of i4_array with dimension
[hsl to hsu].
\param lower vector index
\param upper vector index
*/
void i5_array::allocate(int hsl, int hsu)
{
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
  if (ss > 0)
  {
    if ((t = new i4_array[ss]) == 0)
    {
      cerr << " Error allocating memory in i5_array::allocate\n";
      ad_exit(1);
    }
    if ((shape = new vector_shapex(hsl, hsu, t)) == 0)
    {
      cerr << " Error allocating memory in i5_array::allocate\n";
      ad_exit(1);
    }
    t -= indexmin();
    for (int i = hsl; i <= hsu; ++i)
    {
      (*this)(i).allocate();
    }
  }
  else
  {
    t = 0;
    shape = 0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void i5_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch,int aa,int bb)
 {
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
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

/**
 * Description not yet available.
 * \param
 */
 void i5_array::allocate(const ad_integer& hsl,const ad_integer& hsu,
   const index_type& sl,const index_type& sh,
   const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch,
   const index_type& aa,const index_type& bb)
 {
  unsigned int ss =
    static_cast<unsigned int>(hsu < hsl ? 0 : hsu - hsl + 1);
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

/**
 * Description not yet available.
 * \param
 */
i5_array::i5_array(const i5_array& m2)
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
 i5_array::~i5_array()
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
    i4_array& i5_array::operator ( ) (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
        "i4_array& i5_array::operator ( ) (int i)", indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    i4_array& i5_array::operator [] (int i)
    {
      if (i < indexmin() || i > indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("Index out of bounds",
        "i4_array& i5_array::operator [] (int i)", indexmin(), indexmax(), i);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
    i3_array& i5_array::operator ( ) (int i ,int j)
    {
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
    imatrix& i5_array::operator ( ) (int i,int j,int k)
    {
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
    ivector& i5_array::operator ( ) (int i,int j,int k,int l)
    {
      return ( ((*this)(i,j,k))(l));
    }

/**
 * Description not yet available.
 * \param
 */
    int& i5_array::operator ( ) (int i,int j,int k,int l,int ll)
    {
      return ( ((*this)(i,j,k))(l,ll));
    }

/**
 * Description not yet available.
 * \param
 */
const i4_array& i5_array::operator()(int i) const
    {
      if (i<indexmin() || i>indexmax())
      {
        cerr << "Index out of bounds in i5_array::operator () (int)"
             << endl;
        ad_exit(1);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const i4_array& i5_array::operator[](int i) const
    {
      if (i<indexmin() || i>indexmax())
      {
        cerr << "Index out of bounds in i5_array::operator () (int)"
             << endl;
        ad_exit(1);
      }
      return t[i];
    }

/**
 * Description not yet available.
 * \param
 */
const i3_array& i5_array::operator()(int i, int j) const
    {
      return ((*this)(i))(j);
    }

/**
 * Description not yet available.
 * \param
 */
const imatrix& i5_array::operator()(int i, int j, int k) const
    {
      return (((*this)(i,j))(k));
    }

/**
 * Description not yet available.
 * \param
 */
const ivector& i5_array::operator()(int i, int j, int k, int l) const
    {
      return ( ((*this)(i,j,k))(l));
    }

/**
 * Description not yet available.
 * \param
 */
const int& i5_array::operator()(int i, int j, int k, int l, int ll) const
    {
      return ( ((*this)(i,j,k))(l,ll));
    }
#endif
