/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
  \file
 Overloads of arithmetic operators for variable arguments.
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


/**
 * Description not yet available.
 * \param
 */
void prevariable::operator+=(const double uu)
 {
   (*v).x+=uu;
 }

/**
 * Description not yet available.
 * \param
 */
void prevariable::operator-=(const double uu)
 {
   (*v).x-=uu;
 }

/**
 * Description not yet available.
 * \param
 */
prevariable& operator+(const prevariable& v1, const prevariable& v2)
{
  if (++gradient_structure::GRAD_STACK1->RETURN_PTR > gradient_structure::GRAD_STACK1->MAX_RETURN)
    gradient_structure::GRAD_STACK1->RETURN_PTR = gradient_structure::GRAD_STACK1->MIN_RETURN;

 gradient_structure::GRAD_STACK1->RETURN_PTR->v->x =(*v1.v).x+ (*v2.v).x;
 gradient_structure::GRAD_STACK1->set_gradient_stack4(default_evaluation4,
    &(gradient_structure::GRAD_STACK1->RETURN_PTR->v->x),&((*v1.v).x), &((*v2.v).x));
  return(*gradient_structure::GRAD_STACK1->RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator*(const prevariable& v1, const prevariable& v2)
{
  if (++gradient_structure::GRAD_STACK1->RETURN_PTR > gradient_structure::GRAD_STACK1->MAX_RETURN)
    gradient_structure::GRAD_STACK1->RETURN_PTR = gradient_structure::GRAD_STACK1->MIN_RETURN;
  gradient_structure::GRAD_STACK1->RETURN_PTR->v->x= (*v1.v).x * (*v2.v).x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3,
    &(gradient_structure::GRAD_STACK1->RETURN_PTR->v->x),
    &((*v1.v).x),(*v2.v).x,&((*v2.v).x),(*v1.v).x );
  return(*gradient_structure::GRAD_STACK1->RETURN_PTR);
 }

/**
 * Description not yet available.
 * \param
 */
int prevariable::operator==(const prevariable& v1) const
    {
      return(v->x==value(v1));
    }

/**
 * Description not yet available.
 * \param
 */
int prevariable::operator <=(const prevariable& v1) const
    {
      return(v->x<=value(v1));
    }

/**
 * Description not yet available.
 * \param
 */
int prevariable::operator<(const prevariable& v1) const
    {
      return(v->x<value(v1));
    }

/**
 * Description not yet available.
 * \param
 */
int prevariable::operator>(const prevariable& v1) const
    {
      return(v->x>value(v1));
    }

/**
 * Description not yet available.
 * \param
 */
int prevariable::operator>=(const prevariable& v1) const
    {
      return(v->x >=value(v1));
    }

/**
 * Description not yet available.
 * \param
 */
int prevariable::operator!=(const prevariable& v1) const
    {
      return(v->x!=value(v1));
    }
