/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include <admodel.h>
  int initial_params::nvarcalc_all()
  {
    int nvar=0;
    for (int i=0;i<num_initial_params;i++)
    {
      nvar+= (varsptr[i])->size_count();
    }
    return nvar;
  }


  void initial_params::xinit_all(const dvector& _x)
  {
    dvector& x=(dvector&) _x;
    int ii=1;
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->set_value_inv(x,ii);
    }
  }

  dvariable initial_params::reset_all(const dvar_vector& x,const dvector& __pen)
  {
    dvector& _pen=(dvector&) __pen;
    int ii=1;
    dvariable pen=0.0;
    dvariable pen1;
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->set_value(x,ii,pen1);
      _pen(ii-1)=value(pen1);
      pen+=pen1; 
    }
    return pen;
  }

#undef HOME_VERSION

