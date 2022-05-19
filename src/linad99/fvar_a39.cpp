/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function operator-(const dvar_vector&, const double)
*/
#include "fvar.hpp"

void DF_dv_cdble_diff(void);

/**
Subtracts x from each element of t1 into a dvar_vector.

@param t1 dvar_vector
@param x double
@returns dvar_vector result
*/
dvar_vector operator-(const dvar_vector& t1, const double x)
{
  RETURN_ARRAYS_INCREMENT();
  dvar_vector tmp(t1.indexmin(),t1.indexmax());
  save_identifier_string("ucbb");
  for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
  {
    tmp.elem_value(i)=t1.elem_value(i)-x;
  }
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  tmp.save_dvar_vector_position(fp);
  t1.save_dvar_vector_position(fp);
  save_identifier_string("dduu");
  RETURN_ARRAYS_DECREMENT();
  gs->GRAD_STACK1->set_gradient_stack(DF_dv_cdble_diff);
  return(tmp);
}

/**
Adjoint function for operator-(const dvar_vector&, const double)
*/
void DF_dv_cdble_diff(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  verify_identifier_string("dduu");
  dvar_vector_position t1_pos=restore_dvar_vector_position(fp);
  dvar_vector_position tmp_pos=restore_dvar_vector_position(fp);
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
  verify_identifier_string("ucbb");
  //double xinv=1./x;
  for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
  {
    // tmp.elem_value(i)=t1.elem_value(i)-value(x);
    //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
    dft1(i)=dftmp(i);
  }
  dft1.save_dvector_derivatives(t1_pos);
}
