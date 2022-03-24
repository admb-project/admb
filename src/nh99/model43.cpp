/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

/**
Set the initial_value.
\param initial_value new value
*/
void param_init_vector_vector::set_initial_value(
  const double_index_type& initial_value)
{
  it = new double_index_type(initial_value);
}
/**
Default constructor
*/
param_init_vector_vector::param_init_vector_vector():
  v(NULL),
  index_min(0),
  index_max(-1),
  it(NULL)
{
}
/**
Allocate vector min1 to max2 of param_init_vector with dimensions
min to max using phase_start at 1.

\param min1 lower vector index
\param max1 upper vector index
\param min param_init_vector lower vector index
\param max param_init_vector upper vector index
\param s is the id
*/
void param_init_vector_vector::allocate(
  int min1,
  int max1,
  const index_type& min,
  const index_type& max,
  const char* s)
{
  allocate(min1, max1, min, max, 1, s);
}
/**
Allocate vector min1 to max2 of param_init_vector with dimensions
min to max using specified phase_start.

\param min1 lower vector index
\param max1 upper vector index
\param min param_init_vector lower vector index
\param max param_init_vector upper vector index
\param phase_start specified starting phase
\param s is the id
*/
void param_init_vector_vector::allocate(
  int min1,
  int max1,
  const index_type& min,
  const index_type& max,
  const index_type& phase_start,
  const char* s)
{
  if (max1 >= min1)
  {
    unsigned int size = static_cast<unsigned int>(max1 - min1 + 1);
    v = new param_init_vector[size];
    if (!v)
    {
      cerr << " error trying to allocate memory in "
          "param_init_vector_vector " << endl;
      ad_exit(1);
    }
    index_min = min1;
    index_max = max1;
    v -= indexmin();
    for (int i = indexmin(); i <= indexmax(); ++i)
    {
      if (it) v[i].set_initial_value(ad_double((*it)[i]));
      adstring ss = s + adstring("[") + str(i) + adstring("]");
      v[i].allocate(min[i], max[i], phase_start[i], (char*)(ss));
    }
  }
}
/**
Allocate param_init_vector with dimension imin to imax
using specified phase_start.

Note: May read values from either global parfile or bparfile. 

\param imin lower vector index
\param imax upper vector index
\param phase_start specified starting phase
\param s is the id
*/
void param_init_vector::allocate(
  const ad_integer& imin,
  const ad_integer& imax,
  const ad_integer& _phase_start,
  const char* s)
{
  named_dvar_vector::allocate(imin, imax, s);
  if (!(!(*this)))
  {
    initial_params::allocate(_phase_start);
    if (ad_comm::global_bparfile)
    {
      *(ad_comm::global_bparfile) >> dvar_vector(*this);
    }
    else if (ad_comm::global_parfile)
    {
      *(ad_comm::global_parfile) >> dvar_vector(*this);
    }
    else
    {
      dvar_vector::operator=(initial_value);
    }
  }
  else
  {
    initial_params::allocate(-1);
  }
}
/**
Destructor
*/
param_init_vector_vector::~param_init_vector_vector()
{
  deallocate();
}
/**
Free member allocated memory.
*/
void param_init_vector_vector::deallocate()
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
