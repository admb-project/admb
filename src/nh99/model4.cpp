/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>


  void stddev_params::copy_all_values(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    for (int i=0;i< stddev_params::num_stddev_params;i++)
    {
      (stddevptr[i])->copy_value_to_vector(x,ii);
    }
  }

  void stddev_params::copy_all_number_values(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    for (int i=0;i< stddev_params::num_stddev_number_params;i++)
    {
      (stddev_number_ptr[i])->copy_value_to_vector(x,ii);
    }
  }

  void param_stddev_number::copy_value_to_vector(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

  void param_stddev_vector::copy_value_to_vector(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

  void param_stddev_matrix::copy_value_to_vector(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

