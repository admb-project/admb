

#include <admodel.h>

 //char cc[40]={"Copyright (c) 1993,1994 Otter Research Ltd"};


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


  

#undef HOME_VERSION
