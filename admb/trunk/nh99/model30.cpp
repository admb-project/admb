/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>



  void param_init_matrix::allocate(const ad_integer& rmin,
    const ad_integer& rmax,_CONST index_type& cmin,
    _CONST index_type& cmax, int phase_start,const char *s)
  {
    named_dvar_matrix::allocate(rmin,rmax,cmin,cmax,s);
    initial_params::allocate(phase_start);
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


  void param_init_matrix::allocate(const ad_integer& rmin,
    const ad_integer& rmax,_CONST index_type& cmin,
    _CONST index_type& cmax,const char * s)
  {
    allocate(rmin,rmax,cmin,cmax,1,s);
  }

