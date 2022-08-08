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

void DF_dv_double_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dvar_vector& t1, const double x)
{
  gradient_structure* gs = gradient_structure::_instance;
  DF_FILE* fp = gradient_structure::fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = t1.indexmin();
  int max = t1.indexmax();
  dvar_vector tmp(min, max);
  save_identifier_string("ccbb");
  fp->save_double_value(x);
  double_and_int* ptmpi = tmp.va + min;
  double_and_int* pt1i = t1.va + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = pt1i->x * x;

    ++pt1i;
    ++ptmpi;
  }

  fp->save_dvar_vector_position(tmp);
  fp->save_dvar_vector_position(t1);
  save_identifier_string("DDaa");
  gradient_structure::GRAD_STACK1->set_gradient_stack(DF_dv_double_prod);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dv_double_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

  verify_identifier_string("DDaa");
  dvar_vector_position t1_pos=fp->restore_dvar_vector_position();
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  double x=fp->restore_double_value();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  int min = t1_pos.indexmin();
  int max = t1_pos.indexmax();
  dvector dft1(min, max);
  verify_identifier_string("ccbb");
  double* pdft1i = dft1.get_v() + max;
  double* pdftmpi = dftmp.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    //tmp.elem_value(i)=value(x)*t1.elem_value(i)*x;
    *pdft1i = *pdftmpi * x;

    --pdft1i;
    --pdftmpi;
  }
  dft1.save_dvector_derivatives(t1_pos);
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const double x, const dvar_vector& t1)
{
  return t1 * x;
}
