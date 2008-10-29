

//#define HOME_VERSION
#include <admodel.h>

//double ndfboundp( double x, double fmin, double fmax,BOR_CONST double& fpen);

// char cc[40]={"Copyright (c) 2001 Otter Research Ltd"};

  void param_init_bounded_number::set_maxb(double x)
  {
    maxb=x;
  }

  double param_init_bounded_number::get_maxb(void)
  {
    return maxb;
  }

  void param_init_bounded_vector::set_maxb(double x)
  {
    maxb=x;
  }

  double param_init_bounded_vector::get_maxb(void)
  {
    return maxb;
  }

  void param_init_bounded_matrix::set_maxb(double x)
  {
    maxb=x;
  }

  double param_init_bounded_matrix::get_maxb(void)
  {
    return maxb;
  }

#undef HOME_VERSION
