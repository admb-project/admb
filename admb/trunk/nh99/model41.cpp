/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <admodel.h>



  void stddev_params::get_all_sd_values(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    for (int i=0;i< stddev_params::num_stddev_params;i++)
    {
      (stddevptr[i])->get_sd_values(x,ii);
    }
  }

  void param_stddev_number::get_sd_values(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::copy_value_from_vector(sd,x,ii);
  }

  void param_stddev_vector::get_sd_values(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::copy_value_from_vector(sd,x,ii);
  }

  void param_stddev_matrix::get_sd_values(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    ::copy_value_from_vector(sd,x,ii);
  }


  

