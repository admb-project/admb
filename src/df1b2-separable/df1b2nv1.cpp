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
#include <df1b2fun.h>
#include "admb_messages.h"

/**
Default constructor
*/
df1b2_init_bounded_number_vector::df1b2_init_bounded_number_vector():
  v(NULL),
  index_min(1),
  index_max(0),
  it(NULL)
{
}

#if !defined(OPT_LIB)
/**
 * Description not yet available.
 * \param
 */
df1b2_init_bounded_number& df1b2_init_bounded_number_vector::operator[](int i)
 {
   if (i < indexmin() || i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("Index out of range",
     "df1b2_init_bounded_number_vector::operator [] (int i)",
     indexmin(), indexmax(), i);
   }
   return v[i];
 }

/**
 * Description not yet available.
 * \param
 */
df1b2_init_bounded_number& df1b2_init_bounded_number_vector::operator()(int i)
 {
   if (i < indexmin() || i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("Index out of range",
     "df1b2_init_bounded_number_vector::operator () (int i)",
     indexmin(), indexmax(), i);
   }
   return v[i];
 }
#endif

/**
 * Description not yet available.
 * \param
 */
 df1b2_init_bounded_number_vector::~df1b2_init_bounded_number_vector()
 {
   deallocate();
 }

/**
 * Description not yet available.
 * \param
 */
 void df1b2_init_bounded_number_vector::deallocate(void)
 {
   if(it)
   {
     delete it;
     it=NULL;
   }
   if (v)
   {
     v+=indexmin();
     delete [] v;
     v=NULL;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void df1b2_init_bounded_number_vector::allocate(int min1,int max1,
   const double_index_type & bmin,const double_index_type & bmax,const char * s)
 {
   allocate(min1,max1,bmin,bmax,1,s);
 }

/**
 * Description not yet available.
 * \param
 */
 void df1b2_init_bounded_number_vector::allocate(int min1,int max1,
   const double_index_type & bmin,const double_index_type & bmax,
   const index_type& phase_start,const char * s)
 {
   index_min=min1;
   index_max=max1;
   int size=indexmax()-indexmin()+1;
   if (size>0)
   {
     v = new df1b2_init_bounded_number[size];
     if (!v)
     {
        cerr << " error trying to allocate memory in "
          "df1b2_init_bounded_number_vector " << endl;
        exit(1);
     }
     v-=indexmin();
     for (int i=indexmin();i<=indexmax();i++)
     {
       //if (it) v[i].set_initial_value(ad_double((*it)[i]));
       adstring ss=s + adstring("[") + str(i) + adstring("]");
       v[i].allocate(ad_double(bmin[i]),ad_double(bmax[i]),
         ad_integer(phase_start[i]),(char*)(ss) );
     }
   }
   else
     v=NULL;
 }

/*
dvector df1b2_init_number_vector::get_scalefactor(void)
{
  int mmin=indexmin();
  int mmax=indexmax();
  dvector s(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    s(i)=(*this)(i).get_scalefactor();
  }
  return s;
}
void df1b2_init_number_vector::set_scalefactor(const dvector& s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  if (s.indexmin()!=mmin || s.indexmax() != mmax)
  {
    cerr << "non matching vector bounds in"
     " init_number_vector::set_scalefactor" << endl;
    ad_exit(1);
  }

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s(i));
  }
}

void df1b2_init_number_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}

dvector df1b2_init_bounded_number_vector::get_scalefactor(void)
{
  int mmin=indexmin();
  int mmax=indexmax();
  dvector s(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    s(i)=(*this)(i).get_scalefactor();
  }
  return s;
}
void df1b2_init_bounded_number_vector::set_scalefactor(const dvector& s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  if (s.indexmin()!=mmin || s.indexmax() != mmax)
  {
    cerr << "non matching vector bounds in"
     " init_bounded_number_vector::set_scalefactor" << endl;
    ad_exit(1);
  }

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s(i));
  }
}

void df1b2_init_bounded_number_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}

void df1b2_init_bounded_number_vector::set_initial_value(
  const double_index_type& _it)
 {
    it=new double_index_type(_it);
 }
*/
#if !defined(OPT_LIB)
/**
 * Description not yet available.
 * \param
 */
 df1b2_init_number& df1b2_init_number_vector::operator [] (int i)
 {
   if (i < indexmin() || i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("Index out of range",
     "df1b2_init_number_vector::operator [] (int i)",
     indexmin(), indexmax(), i);
   }
   return v[i];
 }

/**
 * Description not yet available.
 * \param
 */
 df1b2_init_number& df1b2_init_number_vector::operator () (int i)
 {
   if (i < indexmin() || i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("Index out of range",
     "df1b2_init_number_vector::operator () (int i)",
     indexmin(), indexmax(), i);
   }
   return v[i];
 }
#endif

/**
Default constructor
*/
df1b2_init_number_vector::df1b2_init_number_vector():
  v(NULL),
  index_min(0),
  index_max(-1),
  it(NULL)
{
}
/**
Destructor
*/
df1b2_init_number_vector::~df1b2_init_number_vector()
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
 void df1b2_init_number_vector::deallocate(void)
 {
   if(it)
   {
     delete it;
     it=NULL;
   }
   if (v)
   {
     v+=indexmin();
     delete [] v;
     v=NULL;
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void df1b2_init_number_vector::allocate(int min1,int max1,
   const char * s)
 {
   allocate(min1,max1,1,s);
 }

/**
 * Description not yet available.
 * \param
 */
 void df1b2_init_number_vector::allocate(int min1,int max1,
   const index_type& phase_start,const char * s)
 {
   index_min=min1;
   index_max=max1;
   int size=indexmax()-indexmin()+1;
   if (size>0)
   {
     v = new df1b2_init_number[size];
     if (!v)
     {
        cerr << " error trying to allocate memory in "
          "df1b2_init_number_vector " << endl;
        exit(1);
     }
     v-=indexmin();
     for (int i=indexmin();i<=indexmax();i++)
     {
       //if (it) v[i].set_initial_value(ad_double((*it)[i]));
       adstring ss=s + adstring("[") + str(i) + adstring("]");
       v[i].allocate(ad_integer(phase_start[i]),(char*)(ss) );
     }
   }
   else
     v=NULL;
 }
