/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

  void likeprof_params::set_stepsize(double x)
  {
    if ( x>0)
    {
      stepsize=x;
    }
    else
    {
      cerr << "Error in likeprof_params::set_stepsize(double x)"
       " stepsize must be >0" << endl;
    }
  }

  void likeprof_params::set_stepnumber(int n)
  {
    if ( n>0)
    {
      stepnumber=n;
    }
    else
    {
      cerr << "Error in likeprof_params::set_stepnumber(int n)"
       " stepnumber must be >0" << endl;
    }
  }

  double likeprof_params::get_stepsize(void)
  {
    return stepsize;
  }

  int likeprof_params::get_stepnumber(void)
  {
    return stepnumber;
  }
