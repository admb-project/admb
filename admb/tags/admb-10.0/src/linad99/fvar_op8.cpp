/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/** Cube of a number; variable object.
Optimized for derivative computations.
\ingroup misc
\param m number to be cubed
\return \f$m^3\f$
*/
prevariable& cube(_CONST prevariable& v1)
{
  double x=value(v1);
  double x2=x*x;
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x=x2*x;
   gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation2,
     &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),3*x2 );
   return(*gradient_structure::RETURN_PTR);
 }

/** Cube of a number; variable object.
Optimized for derivative computations.
\ingroup misc
\param m number to be cubed
\return \f$m^4\f$
*/
prevariable& fourth(_CONST prevariable& v1)
{
  double x=value(v1);
  double x2=x*x;
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x=x2*x2;
   gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation2,
     &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),4*x2*x );
   return(*gradient_structure::RETURN_PTR);
 }
