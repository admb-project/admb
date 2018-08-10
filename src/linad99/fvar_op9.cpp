/*
 * $Id$
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

void df_plus_eq_pvpv(void);
  //extern ofstream gradlog;

/**
Prevariable addition assignment operator.

\param other add to prevariable
*/
prevariable& prevariable::operator+=(const prevariable& other)
{
  (*v).x += (*other.v).x;

  gradient_structure::GRAD_STACK1->set_gradient_stack1
    (df_plus_eq_pvpv,&(v->x),&(other.v->x));

  return *this;
}
/**
Computes gradients for prevariable addition assignment operator.
*/
void df_plus_eq_pvpv(void)
{
  //cout << setprecision(13) <<
  //  *gradient_structure::GRAD_STACK1->ptr->ind_addr1 << endl;

  //cout << setprecision(13) <<
  //  *gradient_structure::GRAD_STACK1->ptr->dep_addr << endl;

  //gradlog << setprecision(13) <<
  //  *gradient_structure::GRAD_STACK1->ptr->ind_addr1 << endl;

  *gradient_structure::GRAD_STACK1->ptr->ind_addr1
    += *gradient_structure::GRAD_STACK1->ptr->dep_addr;

  //gradlog << setprecision(13) <<
  //  *gradient_structure::GRAD_STACK1->ptr->ind_addr1 << endl;
}
