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
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  double& x = value(variable);
  RETURN_PTR->v->x = x * x;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation2,
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

  int min = matrix.rowmin();
  int max = matrix.rowmax();
  const dvar_vector* pmatrixi = &matrix(min);
  dvar_vector* presultsi = &results(min);
  for (int i = min; i <= max; ++i)
  {
    *presultsi = square(*pmatrixi);

    ++pmatrixi;
    ++presultsi;
  }
  return results;
}
