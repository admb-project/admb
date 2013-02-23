/*
 * $Id: fvar_o11.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
// file: fvar_ops.cpp
// operators involving prevariables

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdio.h>
#include <math.h>

  void df_minus_eq_pvpv(void);

/**
 * Description not yet available.
 * \param
 */
void prevariable::operator-=(const prevariable& v1)
    {
      (*v).x-=(*v1.v).x;
      gradient_structure::GRAD_STACK1->set_gradient_stack(df_minus_eq_pvpv,&(v->x),
        &(v1.v->x));
    }

/**
 * Description not yet available.
 * \param
 */
  void df_minus_eq_pvpv(void)
  {
    * gradient_structure::GRAD_STACK1->ptr->ind_addr1
               -= * gradient_structure::GRAD_STACK1->ptr->dep_addr;
  }
