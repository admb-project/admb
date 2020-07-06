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
  {
    double value_d = value(d);
    for (int i = indexmin(); i <= indexmax(); ++i)
    {
      elem_value(i) -= value_d;
    }
  }

  save_identifier_string("Pvv");
  save_dvar_vector_position();  // for this->
  d.save_prevariable_position();
  save_identifier_string("Pxx");
  gradient_structure::GRAD_STACK1->set_gradient_stack(dv_xminuseq);

  return *this;
}
/**
Adjoint function to compute gradients for dvar_vector::operator-=(const prevariable&)
*/
void dv_xminuseq(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("Pxx");
  prevariable_position d_pos=restore_prevariable_position();
  dvar_vector_position this_pos=restore_dvar_vector_position();
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
  {
    double value_d = value(d);
    for (int i = indexmin(); i <= indexmax(); ++i)
    {
      elem_value(i) += value_d;
    }
  }

  save_identifier_string("Qvv");
  save_dvar_vector_position();  // for this->
  d.save_prevariable_position();
  save_identifier_string("Qxx");
  gradient_structure::GRAD_STACK1->set_gradient_stack(dv_xpluseq);

  return *this;
}
/**
Adjoint function to compute gradients for dvar_vector::operator+=(const prevariable&).
*/
void dv_xpluseq(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("Qxx");
  prevariable_position d_pos=restore_prevariable_position();
  dvar_vector_position this_pos=restore_dvar_vector_position();
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
  {
    for (int i = indexmin(); i <= indexmax(); ++i)
    {
      elem_value(i) -= d;
    }
  }

  return*this;
}
/**
Adds d to each element of dvar_vector.

@param d double
*/
dvar_vector& dvar_vector::operator+=(double d)
{
  {
    for (int i = indexmin(); i <= indexmax(); ++i)
    {
      elem_value(i) += d;
    }
  }

  return *this;
}
