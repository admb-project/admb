/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

void dfmattrans(void);

dvar_matrix trans(_CONST dvar_matrix& m1)
{
  int rmin=m1.indexmin();
  int rmax=m1.indexmax();
  int cmin=m1.colmin();
  int cmax=m1.colmax();
  dvar_matrix t1(cmin,cmax,rmin,rmax);

  for (int i=rmin; i<=rmax; i++)
  {
    for (int j=cmin; j<=cmax; j++)
    {
      t1.elem_value(j,i)=m1.elem_value(i,j);
    }
  }
  save_identifier_string("uu");
  m1.save_dvar_matrix_position();
  t1.save_dvar_matrix_position();
  save_identifier_string("vv");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfmattrans);
  return (t1);
}

void dfmattrans(void)
{
  verify_identifier_string("vv");
  dvar_matrix_position t1pos=restore_dvar_matrix_position();
  dvar_matrix_position m1pos=restore_dvar_matrix_position();
  verify_identifier_string("uu");
  dmatrix dftmp=restore_dvar_matrix_derivatives(t1pos);
  dmatrix dfm1(m1pos);
  int rmin=dfm1.indexmin();
  int rmax=dfm1.indexmax();
  int cmin=dfm1.colmin();
  int cmax=dfm1.colmax();

  for (int i=rmin; i<=rmax; i++)
  {
    for (int j=cmin; j<=cmax; j++)
    {
      //t1.elem_value(j,i)=m1.elem_value(i,j);
      dfm1(i,j)=dftmp(j,i);
    }
  }
  dfm1.save_dmatrix_derivatives(m1pos);
}



