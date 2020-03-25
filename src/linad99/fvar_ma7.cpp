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
  verify_identifier_string("q");
  dvar_matrix_position tmp_pos=restore_dvar_matrix_position();
  verify_identifier_string("p");
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
    if (indexmin()>indexmax())
       cout << "error" << endl;
    int imin=indexmin();
    int imax=indexmax();
    for (int i=imin;i<=imax;i++)
    {
      if (allocated(elem(i)))
      {
        dvar_vector& tmp=elem(i);
        int jmin=tmp.indexmin();
        int jmax=tmp.indexmax();
        double * pd=&(tmp.elem_value(jmin));
        for (int j=jmin;j<=jmax;j++)
        {
          *pd++=0.0;
        }
      }
    }
    save_identifier_string("p");
    save_dvar_matrix_position();
    gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfmatinit);
    save_identifier_string("q");
  }
}
