/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief AD Function operator/(const dvar_vector&, const double)
*/
#include "fvar.hpp"

  void DF_dv_cdble_div(void);

/**
Divides each element of t1 by x, then return result in dvar_vector.

@param t1 dvar_vector
@param x divisor
@return dvar_vector result of operation
*/
dvar_vector operator/(const dvar_vector& t1, const double x)
  {
    gradient_structure* gs = gradient_structure::_instance;
    DF_FILE* fp = gradient_structure::fp;
    gs->RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("ccxb");
    fp->save_double_value(x);
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=t1.elem_value(i)/x;
    }
    fp->save_dvar_vector_value(tmp);
    fp->save_dvar_vector_position(tmp);
    fp->save_dvar_vector_position(t1);
    save_identifier_string("ddba");
    gs->RETURN_ARRAYS_DECREMENT();
    gs->GRAD_STACK1->set_gradient_stack(DF_dv_cdble_div);
    return(tmp);
  }

/**
Adjoint function for dvar_vector operator/(const dvar_vector&, const double)
*/
 void DF_dv_cdble_div(void)
 {
    DF_FILE* fp = gradient_structure::fp;

    verify_identifier_string("ddba");
    dvar_vector_position t1_pos=fp->restore_dvar_vector_position();
    dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
    dvector tmp=restore_dvar_vector_value(tmp_pos);
    double x=fp->restore_prevariable_value();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("ccxb");
    double xinv=1./x;
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
      //tmp.elem_value(i)=value(x)*t1.elem_value(i)/x;
      dft1(i)=dftmp(i)*xinv;
    }
    dft1.save_dvector_derivatives(t1_pos);
 }
