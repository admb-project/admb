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

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator+(const dvar_vector& t1, const prevariable& x)
{
  return x + t1;
}

void DF_dble_dv_add(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator+(const prevariable& x, const dvar_vector& t1)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  gs->RETURN_ARRAYS_INCREMENT();
  int min = t1.indexmin();
  int max = t1.indexmax();
  dvar_vector tmp(min, max);
  save_identifier_string("wcbf");
  x.save_prevariable_position();
  double_and_int* ptmpi = tmp.va + min;
  double_and_int* pt1i = t1.va + min;
  double valuex = value(x);
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = pt1i->x + valuex;

    ++pt1i;
    ++ptmpi;
  }
  tmp.save_dvar_vector_position(fp);
  t1.save_dvar_vector_position(fp);
  save_identifier_string("dduu");
  gs->RETURN_ARRAYS_DECREMENT();
  gs->GRAD_STACK1->set_gradient_stack(DF_dble_dv_add);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dble_dv_add(void)
{
  verify_identifier_string("dduu");
  dvar_vector_position t1_pos=restore_dvar_vector_position();
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  prevariable_position xpos=restore_prevariable_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  int min = t1_pos.indexmin();
  int max = t1_pos.indexmax();
  dvector dft1(min, max);
  verify_identifier_string("wcbf");
  //double xinv=1./x;
  double dfx = 0.0;
  double* pdftmpi = dftmp.get_v() + max;
  double* pdft1i = dft1.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    // tmp.elem_value(i)=value(x)+t1.elem_value(i);
    //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
    dfx += *pdftmpi;
    *pdft1i = *pdftmpi;

    --pdft1i;
    --pdftmpi;
  }
  save_double_derivative(dfx,xpos);
  dft1.save_dvector_derivatives(t1_pos);
}
