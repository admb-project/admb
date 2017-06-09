/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

/**
Sets initial value of param_init_bounded_matrix_vector.

\param initial_value new value
*/
void param_init_bounded_matrix_vector::set_initial_value(
  const double_index_type& initial_value)
{
  it = new double_index_type(initial_value);
}
/// Default constructor
param_init_bounded_matrix_vector::param_init_bounded_matrix_vector():
  v(NULL),
  index_min(0),
  index_max(-1),
  it(NULL)
{
}

void param_init_bounded_matrix_vector::allocate(
  int min1,
  int max1,
  const index_type& min,
  const index_type& max,
  const index_type& min2,
  const index_type& max2,
  const double_index_type& dmin,
  const double_index_type& dmax,
  const char* s)
{
  allocate(min1,max1,min,max,min2,max2,dmin,dmax,1,s);
}

void param_init_bounded_matrix_vector::allocate(
  int min,
  int max,
  const index_type& nrl,
  const index_type& nrh,
  const index_type& ncl,
  const index_type& nch,
  const double_index_type& bounds_minimum,
  const double_index_type& bounds_maximum,
  const index_type& phase_start,
  const char* s)
{
  if (max >= min)
  {
    unsigned int size = static_cast<unsigned int>(max - min + 1);
    v = new param_init_bounded_matrix[size];
    if (!v)
    {
      cerr << "Error trying to allocate memory in"
           << " param_init_bounded_matrix_vector::allocate.\n";
      ad_exit(1);
    }
    index_min = min;
    index_max = max;
    v -= indexmin();
    for (int i = indexmin(); i <= indexmax(); ++i)
    {
       if (it) v[i].set_initial_value(ad_double((*it)[i]));
       adstring id = s + adstring("[") + str(i) + adstring("]");
       v[i].allocate(
          nrl[i], nrh[i],
          ncl[i], nch[i],
          bounds_minimum[i], bounds_maximum[i],
          phase_start[i],
          (char*)id);
    }
  }
}
/**
Allocates matrix with row dimensions imin to imax, column dimensions
imin2 to imax2 and bounded by bmin and bmax using specified phase_start.
*/
void param_init_bounded_matrix::allocate(
  const ad_integer& imin, const ad_integer& imax,
  const ad_integer& imin2, const ad_integer& imax2,
  const ad_double& _bmin, const ad_double& _bmax,
  const ad_integer& _phase_start, const char* s)
{
  minb = _bmin;
  maxb = _bmax;
  named_dvar_matrix::allocate(imin,imax,imin2,imax2,s);
  if (!(!(*this)))
  {
    initial_params::allocate(_phase_start);
    if (ad_comm::global_bparfile)
    {
      *(ad_comm::global_bparfile) >> dvar_matrix(*this);
    }
    else if (ad_comm::global_parfile)
    {
      *(ad_comm::global_parfile) >> dvar_matrix(*this);
    }
    else
    {
      if ((!initial_value_flag)
        || initial_value <=minb || initial_value >= maxb)
      {
        //cerr << "Initial value out of bounds -- using halfway value" << endl;
        initial_value=(minb+maxb)/2.;
      }
      dvar_matrix::operator=(initial_value);
    }
  }
  else
  {
    initial_params::allocate(-1);
  }
}
/// Destructor
param_init_bounded_matrix_vector::~param_init_bounded_matrix_vector()
{
  deallocate();
}
/// Frees member allocated memory.
void param_init_bounded_matrix_vector::deallocate()
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
