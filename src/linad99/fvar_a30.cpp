/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Unary functions for dvar_vector operator-= and operator+=
*/
#include "fvar.hpp"

void dv_xminuseq(void);

/**
Substracts d from each element of dvar_vector.

@param d prevariable
*/
dvar_vector& dvar_vector::operator-=(const prevariable& d)
{
  dvar_vector::operator-=(value(d));

  grad_stack* GRAD_STACK1 = gradient_structure::get_GRAD_STACK1();
  DF_FILE* fp = gradient_structure::get_fp();
  save_identifier_string("Pvv");
  fp->save_dvar_vector_position(*this);  // for this->
  fp->save_prevariable_position(d);
  save_identifier_string("Pxx");
  GRAD_STACK1->set_gradient_stack(dv_xminuseq);

  return *this;
}
/**
Adjoint function to compute gradients for dvar_vector::operator-=(const prevariable&)
*/
void dv_xminuseq(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("Pxx");
  prevariable_position d_pos=fp->restore_prevariable_position();
  dvar_vector_position this_pos=fp->restore_dvar_vector_position();
  verify_identifier_string("Pvv");
  dvector dfthis=restore_dvar_vector_der_nozero(this_pos);
  double temp=-sum(dfthis);
  save_double_derivative(temp,d_pos);
}

void dv_xpluseq(void);

/**
Adds d to each element of dvar_vector.

@param d prevariable
*/
dvar_vector& dvar_vector::operator+=(const prevariable& d)
{
  dvar_vector::operator+=(value(d));

  grad_stack* GRAD_STACK1 = gradient_structure::get_GRAD_STACK1();
  DF_FILE* fp = gradient_structure::get_fp();
  save_identifier_string("Qvv");
  fp->save_dvar_vector_position(*this);  // for this->
  fp->save_prevariable_position(d);
  save_identifier_string("Qxx");
  GRAD_STACK1->set_gradient_stack(dv_xpluseq);

  return *this;
}
/**
Adjoint function to compute gradients for dvar_vector::operator+=(const prevariable&).
*/
void dv_xpluseq(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("Qxx");
  prevariable_position d_pos=fp->restore_prevariable_position();
  dvar_vector_position this_pos=fp->restore_dvar_vector_position();
  verify_identifier_string("Qvv");
  dvector dfthis=restore_dvar_vector_der_nozero(this_pos);
  double temp=sum(dfthis);
  save_double_derivative(temp,d_pos);
}
/**
Substracts d from each element of dvar_vector.

@param d double
*/
dvar_vector& dvar_vector::operator-=(double d)
{
  double_and_int* pv = va + index_min;
  for (int i = index_min; i <= index_max; ++i)
  {
    pv->x -= d;
    ++pv;
  }

  return *this;
}
/**
Adds d to each element of dvar_vector.

@param d double
*/
dvar_vector& dvar_vector::operator+=(double d)
{
  double_and_int* pv = va + index_min;
  for (int i = index_min; i <= index_max; ++i)
  {
    pv->x += d;
    ++pv;
  }

  return *this;
}
