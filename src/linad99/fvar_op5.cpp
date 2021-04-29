/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

/**
\file
prevariable operations
*/

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
#if !defined(OPT_LIB)

/**
 * Description not yet available.
 * \param
 */
void grad_stack::set_gradient_stack(void (* func)(void), double * dep_addr,
  double * ind_addr1, double mult1, double * ind_addr2, double mult2)
{
#ifdef NO_DERIVS
  if (!gradient_structure::no_derivatives)
  {
#endif
#if defined(MYDEBUG)
    int wrote_buffer=0;
    if (ptr < ptr_first)
    {
      cerr << "Illegal ptr value" << endl;
      ad_exit(1);
    }
#endif
    if (ptr > ptr_last)
    {
      // current buffer is full -- write it to disk and reset pointer
      // and counter
      this->write_grad_stack_buffer();
#if defined(MYDEBUG)
      wrote_buffer=1;
#endif
    }
    ptr->func = func;
    ptr->dep_addr = dep_addr;
    ptr->ind_addr1 = ind_addr1;
    ptr->mult1=mult1;
    ptr->ind_addr2 = ind_addr2;
    ptr->mult2=mult2;
    ptr++;
#ifdef NO_DERIVS
  }
#endif
}
#endif
/**
 * Description not yet available.
 * \param
 */
prevariable& operator*(double x, const prevariable& v2)
{
  if (++gradient_structure::GRAD_STACK1->RETURN_PTR > gradient_structure::GRAD_STACK1->MAX_RETURN)
    gradient_structure::GRAD_STACK1->RETURN_PTR = gradient_structure::GRAD_STACK1->MIN_RETURN;
  gradient_structure::GRAD_STACK1->RETURN_PTR->v->x = x * v2.v->x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation2,
    &(gradient_structure::GRAD_STACK1->RETURN_PTR->v->x),&(v2.v->x),x);
  return (*gradient_structure::GRAD_STACK1->RETURN_PTR);
}
/**
 * Description not yet available.
 * \param
 */
prevariable& operator*(const prevariable& v1, double x)
{
  if (++gradient_structure::GRAD_STACK1->RETURN_PTR > gradient_structure::GRAD_STACK1->MAX_RETURN)
    gradient_structure::GRAD_STACK1->RETURN_PTR = gradient_structure::GRAD_STACK1->MIN_RETURN;
  gradient_structure::GRAD_STACK1->RETURN_PTR->v->x = v1.v->x * x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation2,
    &(gradient_structure::GRAD_STACK1->RETURN_PTR->v->x),&(v1.v->x),x);
  return (*gradient_structure::GRAD_STACK1->RETURN_PTR);
}
/**
 * Description not yet available.
 * \param
 */
void prevariable::operator/=(const prevariable& v1)
{
  double tmp=1./(v1.v->x);
  v->x *= tmp;
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,&(v->x), &(v->x), tmp,&(v1.v->x), -(v->x)*tmp);
}
/**
 * Description not yet available.
 * \param
 */
void prevariable::operator/=(double v1)
{
  double tmp=1./v1;
  v->x *= tmp;
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,&(v->x), &(v->x), tmp);
}
/**
 * Description not yet available.
 * \param
 */
void prevariable::operator*=(const prevariable& v1)
{
  double* tmp=&((v1.v)->x);
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,&(v->x), &(v->x), *tmp, tmp, v->x);
  v->x *= *tmp;
}
/**
 * Description not yet available.
 * \param
 */
void prevariable::operator*=(double v1)
{
  gradient_structure::GRAD_STACK1->set_gradient_stack(
    default_evaluation,&(v->x), &(v->x), v1);
  v->x *= v1;
}
