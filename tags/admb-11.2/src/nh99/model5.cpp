/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void param_init_bounded_dev_vector::set_value(const dvar_vector& x,
  const int& ii, const dvariable& _pen)
  {
    dvariable& pen= (dvariable&) _pen;
    if (initial_params::mc_phase)
    {
      set_value_mc(*this,x,ii,minb,maxb);
    }
    else
    {
      ::set_value(*this,x,ii,minb,maxb,pen);
    }
    dvariable s=mean(*this);
    pen+=10000.0*s*s;
    if (!initial_params::mc_phase)
    {
      (*this)-=s;
    }
  }
