/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions for prevariable to compute cube(const prevariable&) and fourth(const prevariable&).
*/

#include "fvar.hpp"

/**
Returns variable result of v1 cubed.

\ingroup misc
\param v1 variable base
\return \f$v^3\f$
*/
prevariable& cube(const prevariable& v1)
{
  double x=value(v1);
  double x2=x*x;

  gradient_structure* gs = gradient_structure::get();
  dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

  RETURN_PTR->v->x=x2*x;
  gs->GRAD_STACK1->set_gradient_stack(default_evaluation2,
    &(RETURN_PTR->v->x), &(v1.v->x), 3.0*x2);

  return *RETURN_PTR;
}
/**
Returns variable result of v1 raised to the power of four.

\ingroup misc
\param v1 variable base
\return \f$v^4\f$
*/
prevariable& fourth(const prevariable& v1)
{
  double x=value(v1);
  double x2=x*x;

  gradient_structure* gs = gradient_structure::get();
  dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

  RETURN_PTR->v->x=x2*x2;
  gs->GRAD_STACK1->set_gradient_stack(default_evaluation2,
    &(RETURN_PTR->v->x), &(v1.v->x), 4.0*x2*x);

  return *RETURN_PTR;
}
