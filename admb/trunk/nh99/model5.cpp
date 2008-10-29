#include <admodel.h>
 //char cc[40]={"Copyright (c) 1993,1994 Otter Research Ltd"};

  void param_init_bounded_dev_vector::set_value(
    const dvar_vector& x,BOR_CONST int& ii,BOR_CONST dvariable& _pen)
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
