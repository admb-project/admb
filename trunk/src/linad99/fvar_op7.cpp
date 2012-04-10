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

/**
 * Description not yet available.
 * \param
 */
double upick(double x)
{
  return x*x;
}
  
/**
 * Description not yet available.
 * \param
 */
dvariable& square(_CONST prevariable& v1)
{
  double& x = value(v1);
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x = x*x;
   gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation2,
     &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),2*x );
   return(*gradient_structure::RETURN_PTR);
 }

/**
 * Description not yet available.
 * \param
 */
   dvar_matrix square(_CONST dvar_matrix& m)
   {
     dvar_matrix tmp;
     tmp.allocate(m);
     for (int i = tmp.rowmin();i<=tmp.rowmax();i++)
     {
       tmp(i) = square(m(i));
     }
     return tmp;
   }  
