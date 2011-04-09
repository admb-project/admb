/*
 * $Id: model50.cpp 945 2011-01-12 23:03:57Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

//double ndfboundp( double x, double fmin, double fmax,BOR_CONST double& fpen);

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
