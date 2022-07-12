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
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  gs->RETURN_ARRAYS_INCREMENT();

  int min = t1.indexmin();
  int max = t1.indexmax();
  dvar_vector tmp(t1.indexmin(),t1.indexmax());
  //save_identifier_string("xc");
  //x.save_prevariable_value();
  x.save_prevariable_position();
  double valuex = value(x);
  double* pt1i = t1.get_v() + min;
  double_and_int* ptmpi = tmp.va + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = *pt1i * valuex;

    ++ptmpi;
    ++pt1i;
  }
  t1.save_dvector_value();
  tmp.save_dvar_vector_position(fp);
  t1.save_dvector_position();
  //save_identifier_string("Da");
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
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  gs->RETURN_ARRAYS_INCREMENT();

  int min = t1.indexmin();
  int max = t1.indexmax();

  dvar_vector tmp(min, max);
  //save_identifier_string("xc");
  //x.save_prevariable_value();
  x.save_prevariable_position();

  double valuex = value(x);
  double* pt1i = t1.get_v() + min;
  double_and_int* ptmpi = tmp.va + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = *pt1i * valuex;

    ++pt1i;
    ++ptmpi;
  }

  t1.save_dvector_value();
  tmp.save_dvar_vector_position(fp);
  t1.save_dvector_position();
  //save_identifier_string("Da");
  gs->RETURN_ARRAYS_DECREMENT();
  gs->GRAD_STACK1->set_gradient_stack(DF_ccv_dble_prod);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_ccv_dble_prod(void)
{
  //verify_identifier_string("Da");
  dvector_position t1_pos=restore_dvector_position();
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector t1=restore_dvar_vector_value(tmp_pos);
  prevariable_position xpos=restore_prevariable_position();
  //double x=restore_prevariable_value();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  //dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
  //verify_identifier_string("xc");

  int max = t1_pos.indexmax();
  int min = t1_pos.indexmin();
  double dfx=0.0;

  double* pt1i = t1.get_v() + max;
  double* pdftmpi =dftmp.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    //tmp.elem_value(i)=value(x)*t1.elem_value(i)*value(x);
    dfx += *pdftmpi * *pt1i;
    //dft1(i)=dftmp(i)*x;
    --pt1i;
    --pdftmpi;
  }
  save_double_derivative(dfx,xpos);
  //dft1.save_dvector_derivatives(t1_pos);
}
