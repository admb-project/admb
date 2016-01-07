/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

/**
Allocates matrix with row dimensions rmin to rmax and column dimensions
cmin to cmax using specified phase_start.
*/
void param_init_matrix::allocate(const ad_integer& rmin,
  const ad_integer& rmax, const index_type& cmin,
  const index_type& cmax, int _phase_start, const char *s)
{
  named_dvar_matrix::allocate(rmin,rmax,cmin,cmax,s);
  initial_params::allocate(_phase_start);
  if (ad_comm::global_bparfile)
  {
    *(ad_comm::global_bparfile) >> dvar_matrix(*this);
  }
  else if (ad_comm::global_parfile)
  {
    if (allocated(*this))
      *(ad_comm::global_parfile) >> dvar_matrix(*this);
  }
  else
  {
    if (allocated(*this))
    for (int i=indexmin();i<=indexmax();i++)
      if (allocated((*this)(i)))
        (*this)(i)=(initial_value);
  }
}
/**
Allocates matrix with row dimensions rmin to rmax and column dimensions
cmin to cmax with phase_start defaulting to 1.
*/
void param_init_matrix::allocate(const ad_integer& rmin,
  const ad_integer& rmax, const index_type& cmin,
  const index_type& cmax, const char *s)
{
  allocate(rmin,rmax,cmin,cmax,1,s);
}
