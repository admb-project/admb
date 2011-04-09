/*
 * $Id: model48.cpp 945 2011-01-12 23:03:57Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

 void param_init_bounded_number_vector::set_initial_value(const double_index_type& _it)
 {
    it=new double_index_type(_it);
 }

 param_init_bounded_number_vector::param_init_bounded_number_vector(): v(NULL), it(NULL)
 {
 }
     
 param_init_bounded_number_vector::~param_init_bounded_number_vector()
 {
   deallocate();
 }

 void param_init_bounded_number_vector::deallocate(void)
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

 void param_init_bounded_number_vector::allocate(int min1,int max1,
   const double_index_type & bmin,const double_index_type & bmax,const char * s)
 {
   allocate(min1,max1,bmin,bmax,1,s);
 }

 void param_init_bounded_number_vector::allocate(int min1,int max1,
   const double_index_type & bmin,const double_index_type & bmax,
   const index_type& phase_start,const char * s)
 {
   index_min=min1;
   index_max=max1;
   int size=indexmax()-indexmin()+1;
   if (size>0)
   {
     if (!(v=new param_init_bounded_number[size]))
     {
        cerr << " error trying to allocate memory in "
          "param_init_bounded_number_vector " << endl;
        exit(1);
     }
     v-=indexmin();
     for (int i=indexmin();i<=indexmax();i++)
     {
       if (it) v[i].set_initial_value(ad_double((*it)[i]));
       adstring ss=s + adstring("[") + str(i) + adstring("]");
       v[i].allocate(ad_double(bmin[i]),ad_double(bmax[i]),
         ad_integer(phase_start[i]),(char*)(ss) );
     }
   }
   else
     v=NULL;
 }

dvector param_init_number_vector::get_scalefactor(void)
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
void param_init_number_vector::set_scalefactor(const dvector& s)
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

void param_init_number_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}



dvector param_init_vector_vector::get_scalefactor(void)
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
void param_init_vector_vector::set_scalefactor(const dvector& s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  if (s.indexmin()!=mmin || s.indexmax() != mmax)
  {
    cerr << "non matching vector bounds in" 
     " init_vector_vector::set_scalefactor" << endl;
    ad_exit(1);
  }

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s(i));
  }
}

void param_init_vector_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}




dvector param_init_matrix_vector::get_scalefactor(void)
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
void param_init_matrix_vector::set_scalefactor(const dvector& s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  if (s.indexmin()!=mmin || s.indexmax() != mmax)
  {
    cerr << "non matching vector bounds in" 
     " init_matrix_vector::set_scalefactor" << endl;
    ad_exit(1);
  }

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s(i));
  }
}

void param_init_matrix_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}



dvector param_init_bounded_number_vector::get_scalefactor(void)
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
void param_init_bounded_number_vector::set_scalefactor(const dvector& s)
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

void param_init_bounded_number_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}



dvector param_init_bounded_vector_vector::get_scalefactor(void)
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
void param_init_bounded_vector_vector::set_scalefactor(const dvector& s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  if (s.indexmin()!=mmin || s.indexmax() != mmax)
  {
    cerr << "non matching vector bounds in" 
     " init_bounded_vector_vector::set_scalefactor" << endl;
    ad_exit(1);
  }

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s(i));
  }
}

void param_init_bounded_vector_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}




dvector param_init_bounded_matrix_vector::get_scalefactor(void)
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
void param_init_bounded_matrix_vector::set_scalefactor(const dvector& s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  if (s.indexmin()!=mmin || s.indexmax() != mmax)
  {
    cerr << "non matching vector bounds in" 
     " init_bounded_matrix_vector::set_scalefactor" << endl;
    ad_exit(1);
  }

  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s(i));
  }
}

void param_init_bounded_matrix_vector::set_scalefactor(double s)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i).set_scalefactor(s);
  }
}


