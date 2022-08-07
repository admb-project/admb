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
#include <fvar.hpp>

  void DF_ccv_dble_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dvector& t1, const prevariable& x)
{
  gradient_structure* gs = gradient_structure::_instance;
  DF_FILE* fp = gradient_structure::fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = t1.indexmin();
  int max = t1.indexmax();
  dvar_vector tmp(min, max);
  save_identifier_string("xc");
  //x.save_prevariable_value();
  fp->save_prevariable_position(x);
  double_and_int* ptmp = tmp.va + min;
  double* pt1 = t1.get_v() + min;
  double value_x = value(x);
  for (int i = min; i <= max; ++i)
  {
    ptmp->x = *pt1 * value_x;
    ++ptmp;
    ++pt1;
  }
  fp->save_dvector_value(t1);
  fp->save_dvar_vector_position(tmp);
  fp->save_dvector_position(t1);
  save_identifier_string("Da");
  gs->RETURN_ARRAYS_DECREMENT();
  gs->GRAD_STACK1->set_gradient_stack(DF_ccv_dble_prod);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const prevariable& x, const dvector& t1)
{
  gradient_structure* gs = gradient_structure::_instance;
  DF_FILE* fp = gradient_structure::fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = t1.indexmin();
  int max = t1.indexmax();
  dvar_vector tmp(min, max);
  save_identifier_string("xc");
  //x.save_prevariable_value();
  fp->save_prevariable_position(x);
  double_and_int* ptmp = tmp.va + min;
  double* pt1 = t1.get_v() + min;
  double value_x = value(x);
  for (int i = min; i <= max; ++i)
  {
    ptmp->x = value_x * (*pt1);
    ++ptmp;
    ++pt1;
  }
  fp->save_dvector_value(t1);
  fp->save_dvar_vector_position(tmp);
  fp->save_dvector_position(t1);
  save_identifier_string("Da");
  gs->RETURN_ARRAYS_DECREMENT();
  gradient_structure::GRAD_STACK1->set_gradient_stack(DF_ccv_dble_prod);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_ccv_dble_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

  verify_identifier_string("Da");
  dvector_position t1_pos=fp->restore_dvector_position();
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector t1=restore_dvar_vector_value(tmp_pos);
  prevariable_position xpos=fp->restore_prevariable_position();
  //double x=restore_prevariable_value();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  //dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
  verify_identifier_string("xc");
  double dfx=0.;
  int min = t1_pos.indexmin();
  int max = t1_pos.indexmax();
  double* pdftmp = dftmp.get_v() + max;
  double* pt1 = t1.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    //tmp.elem_value(i)=value(x)*t1.elem_value(i)*value(x);
    dfx += *pdftmp * (*pt1);
    --pdftmp;
    --pt1;
    //dft1(i)=dftmp(i)*x;
  }
  save_double_derivative(dfx,xpos);
  //dft1.save_dvector_derivatives(t1_pos);
}
