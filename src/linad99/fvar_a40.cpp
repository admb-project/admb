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

void DF_cdble_dv_diff(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator-(const double x, const dvar_vector& t1)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = t1.indexmin();
  int max = t1.indexmax();
  dvar_vector tmp(min, max);
  //save_identifier_string("ecbb");
  double_and_int* ptmpi = tmp.va + min;
  double_and_int* pt1i = t1.va + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = x - pt1i->x;
    ++ptmpi;
    ++pt1i;
  }
  fp->save_dvar_vector_position(tmp);
  fp->save_dvar_vector_position(t1);
  //save_identifier_string("druu");
  gs->GRAD_STACK1->set_gradient_stack(DF_cdble_dv_diff);
  gs->RETURN_ARRAYS_DECREMENT();
  return(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void DF_cdble_dv_diff(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  //verify_identifier_string("druu");
  dvar_vector_position t1_pos=fp->restore_dvar_vector_position();
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  int min = t1_pos.indexmin();
  int max = t1_pos.indexmax();
  dvector dft1(min, max);
  //verify_identifier_string("ecbb");
  //double xinv=1./x;
  double* pdft1i = dft1.get_v() + max;
  double* pdftmpi = dftmp.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    // tmp.elem_value(i)=t1.elem_value(i)-value(x);
    //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
    *pdft1i = -(*pdftmpi);

    --pdft1i;
    --pdftmpi;
  }
  dft1.save_dvector_derivatives(t1_pos);
}

void DF_dv_minus(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator-(const dvar_vector& t1)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = t1.indexmin();
  int max = t1.indexmax();
  dvar_vector tmp(min, max);
  //save_identifier_string("vcbb");
  const double_and_int* pt1i = t1.va + min;
  double_and_int* ptmpi = tmp.va + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = -pt1i->x;

    ++ptmpi;
    ++pt1i;
  }
  fp->save_dvar_vector_position(tmp);
  fp->save_dvar_vector_position(t1);
  //save_identifier_string("tduu");
  gs->RETURN_ARRAYS_DECREMENT();
  gs->GRAD_STACK1->set_gradient_stack(DF_dv_minus);
  return(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void DF_dv_minus(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  //verify_identifier_string("tduu");
  dvar_vector_position t1_pos=fp->restore_dvar_vector_position();
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  int min = t1_pos.indexmin();
  int max = t1_pos.indexmax();
  dvector dft1(min, max);
  //verify_identifier_string("vcbb");
  //double xinv=1./x;
  double* pdft1i = dft1.get_v() + max;
  double* pdftmpi = dftmp.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    // tmp.elem_value(i)=t1.elem_value(i)-value(x);
    //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
    *pdft1i = -(*pdftmpi);
    --pdft1i;
    --pdftmpi;
  }
  dft1.save_dvector_derivatives(t1_pos);
}
