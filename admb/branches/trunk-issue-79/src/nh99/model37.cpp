/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>



  dvariable function_minimizer::user_randeff(const dvar_vector& x)
  {
    cout << "You must define the function user_randeff in your TPL"
      " file to use the random effects optimization" << endl;
    ad_exit(1); 
       
    dvariable u; 
    return u;
  }
  dvar_vector function_minimizer::user_dfrandeff(const dvar_vector& x)
  {
    cout << "You must define the function user_dfrandeff in your TPL"
      " file to use the random effects optimization" << endl;
    ad_exit(1); 
    dvar_vector u; 
    return u;
  }
  dvar_matrix function_minimizer::user_d2frandeff(const dvar_vector& x)
  {
    cout << "You must define the function user_d2frandeff in your TPL"
      " file to use the random effects optimization" << endl;
    ad_exit(1); 
    dvar_matrix u; 
    return u;
  }
