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
#include "fvar.hpp"

/*
void dvar_matrix::initialize(void)
{
  if (!(!(*this)))  // only initialize allocated objects
  {
    for (int i=rowmin();i<=rowmax();i++)
    {
      elem(i).initialize();
    }
  }
}
*/

/**
 * Adjoint function for dvar_matrix::initialize.
 *
 * Zero initialize a dvar_matrix_position restored from stored adjoint data.
 */
void dfmatinit(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  //verify_identifier_string("q");
  dvar_matrix_position tmp_pos=fp->restore_dvar_matrix_position();
  //verify_identifier_string("p");
  dmatrix tmp(tmp_pos);
  tmp.initialize();
  tmp.save_dmatrix_derivatives_na(tmp_pos);
}
/**
 * Zero initialize allocated dvar_matrix, then saves adjoint function
 * and position data.
 *
 * If dvar_matrix is empty, there are no changes.
 */
void dvar_matrix::initialize(void)
{
  if (!(!(*this)))  // only initialize allocated objects
  {
    int imin = indexmin();
    int imax = indexmax();
    dvar_vector* pmi = m + imin;
    for (int i = imin; i <= imax; ++i)
    {
      if (allocated(*pmi))
      {
        int jmin = pmi->indexmin();
        int jmax = pmi->indexmax();

	double_and_int* pmij = pmi->get_va() + jmin;
        for (int j = jmin; j <= jmax; ++j)
        {
          pmij->x = 0.0;

	  ++pmij;
        }
      }
      ++pmi;
    }
    grad_stack* GRAD_STACK1 = gradient_structure::get_GRAD_STACK1();
    DF_FILE* fp = gradient_structure::get_fp();
    //save_identifier_string("p");
    fp->save_dvar_matrix_position(*this);
    GRAD_STACK1->set_gradient_stack(dfmatinit);
    //save_identifier_string("q");
  }
}
