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
  if (++gs->RETURN_PTR > gs->MAX_RETURN)
    gs->RETURN_PTR = gs->MIN_RETURN;

  double& x = value(variable);
  gs->RETURN_PTR->v->x = x * x;

  gs->GRAD_STACK1->set_gradient_stack(default_evaluation2,
     &(gs->RETURN_PTR->v->x), &(variable.v->x), 2 * x );

  return *gs->RETURN_PTR;
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
