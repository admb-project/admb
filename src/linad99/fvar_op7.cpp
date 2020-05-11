/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

// double upick(double x) { return x*x; } 

/**
Return the computed square of variable, then set gradient_structure.

\param variable prevariable
*/
dvariable& square(const prevariable& variable)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
    gradient_structure::RETURN_PTR = gradient_structure::GRAD_STACK1->MIN_RETURN;

  double& x = value(variable);
  gradient_structure::RETURN_PTR->v->x = x * x;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation2,
     &(gradient_structure::RETURN_PTR->v->x), &(variable.v->x), 2 * x );

  return *gradient_structure::RETURN_PTR;
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
