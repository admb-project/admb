/*
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include "fvar.hpp"

void DF_first_diference(void);

/**
Returns a dvector containing the differences of an x(i) and  x(i + 1) for i = 1 to x.indexmax() - 1.

\param x input.
*/
dvar_vector first_difference(const dvar_vector& x)
{
  if (x.size() <= 1)
  {
    cerr << "Error -- vector size too small"
             " in first_difference(const dvar_vector&)" << endl;
    ad_exit(1);
  }

  RETURN_ARRAYS_INCREMENT();
  int mmin=x.indexmin();
  int mmax=x.indexmax()-1;
  dvar_vector tmp(mmin,mmax);
  for (int i=mmin; i<=mmax; i++)
  {
    tmp.elem_value(i)=x.elem_value(i+1)-x.elem_value(i);
  }
  save_identifier_string("CE4");
  x.save_dvar_vector_position();
  tmp.save_dvar_vector_position();
  save_identifier_string("CE1");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(DF_first_diference);
  RETURN_ARRAYS_DECREMENT();
  return(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void DF_first_diference(void)
{
  verify_identifier_string("CE1");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvar_vector_position x_pos=restore_dvar_vector_position();
  verify_identifier_string("CE4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector dfx(x_pos.indexmin(),x_pos.indexmax());
  dfx.initialize();
  for (int i=dfx.indexmax()-1; i>=dfx.indexmin(); i--)
  {
    // tmp.elem_value(i)=x.elem_value(i+1)-x.elem_value(i);
       dfx.elem(i+1)+=dftmp.elem(i);
       dfx.elem(i)-=dftmp.elem(i);
  }
  dfx.save_dvector_derivatives(x_pos);
}
