/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void param_init_bounded_vector_vector::set_initial_value(
  const double_index_type& _it)
 {
    it=new double_index_type(_it);
 }

/**
Default constructor
*/
param_init_bounded_vector_vector::param_init_bounded_vector_vector():
  v(NULL),
  index_min(0),
  index_max(0),
  it(NULL)
{
}

void param_init_bounded_vector_vector::allocate(
  int min1,
  int max1,
  const index_type& min,
  const index_type& max,
  const double_index_type& dmin,
  const double_index_type& dmax,
  const char* s)
{
  allocate(min1,max1,min,max,dmin,dmax,1,s);
}

void param_init_bounded_vector_vector::allocate(
  int min1,
  int max1,
  const index_type& min,
  const index_type& max,
  const double_index_type& dmin,
  const double_index_type& dmax,
  const index_type& phase_start,
  const char* s)
{
  int size = max1 - min1 + 1;
  if (size > 0)
  {
    v = new param_init_bounded_vector[size];
    if (!v)
    {
        cerr << " error trying to allocate memory in "
          "param_init_vector_vector " << endl;
        exit(1);
    }

    index_min=min1;
    index_max=max1;
    v-=indexmin();
    for (int i=indexmin();i<=indexmax();i++)
    {
      if (it) v[i].set_initial_value(ad_double((*it)[i]));
      adstring ss=s + adstring("[") + str(i) + adstring("]");
      v[i].allocate(ad_integer(min[i]),ad_integer(max[i]),
         ad_double(dmin[i]),ad_double(dmax[i]),
         ad_integer(phase_start[i]),(char*)(ss) );
    }
  }
}
/**
Destructor
*/
param_init_bounded_vector_vector::~param_init_bounded_vector_vector()
{
  deallocate();
}
/**
Free member allocated memory.
*/
void param_init_bounded_vector_vector::deallocate(void)
{
  if (it)
  {
    delete it;
    it = NULL;
  }
  if (v)
  {
    v += indexmin();
    delete [] v;
    v = NULL;
  }
}
