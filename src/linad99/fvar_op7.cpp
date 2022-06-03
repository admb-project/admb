/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return the computed square of variable, then set gradient_structure.

\param variable prevariable
*/
dvariable& square(const prevariable& variable)
{
  gradient_structure* gs = gradient_structure::get();
  dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

  double& x = value(variable);
  RETURN_PTR->v->x = x * x;

  gs->GRAD_STACK1->set_gradient_stack(default_evaluation2,
     &(RETURN_PTR->v->x), &(variable.v->x), 2 * x );

  return *RETURN_PTR;
}
/**
Return results of computing the square of variable matrix.

\param matrix variable matrix
*/
dvar_matrix square(const dvar_matrix& matrix)
{
  dvar_matrix results;
  results.allocate(matrix);
  for (int i = matrix.rowmin(); i <= matrix.rowmax(); ++i)
  {
    results(i) = square(matrix(i));
  }
  return results;
}
