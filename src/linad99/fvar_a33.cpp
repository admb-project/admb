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

  void DF_dv_dble_div(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator/(const dvar_vector& t1, const prevariable& x)
  {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;
    gs->RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("ccbb");
    fp->save_prevariable_value(x);
    fp->save_prevariable_position(x);
    int min = t1.indexmin();
    int max = t1.indexmax();
    double_and_int* ptmp = tmp.va + min;
    double_and_int* pt1 = t1.va + min;
    double value_x = value(x);
    for (int i = min; i <= max; ++i)
    {
      //tmp.elem_value(i)=t1.elem_value(i)/value(x);
      ptmp->x = pt1->x / value_x;
      ++ptmp;
      ++pt1;
    }
    fp->save_dvar_vector_value(tmp);
    fp->save_dvar_vector_position(tmp);
    fp->save_dvar_vector_position(t1);
    save_identifier_string("ddaa");
    gs->GRAD_STACK1->set_gradient_stack(DF_dv_dble_div);
    gs->RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_dv_dble_div(void)
 {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    verify_identifier_string("ddaa");
    dvar_vector_position t1_pos=fp->restore_dvar_vector_position();
    dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
    dvector tmp=restore_dvar_vector_value(tmp_pos);
    prevariable_position xpos=fp->restore_prevariable_position();
    double x=fp->restore_prevariable_value();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("ccbb");
    double xinv=1.0 / x;
    double dfx=0.0;

    int min = t1_pos.indexmin();
    int max = t1_pos.indexmax();
    double* pdftmp = dftmp.get_v() + max;
    double* ptmp = tmp.get_v() + max;
    double* pdft1 = dft1.get_v() + max;
    for (int i = max; i >= min; --i)
    {
      //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
      dfx -= *pdftmp * (*ptmp) * xinv;
      *pdft1 = *pdftmp * xinv;
      --pdftmp;
      --ptmp;
      --pdft1;
    }
    save_double_derivative(dfx,xpos);
    dft1.save_dvector_derivatives(t1_pos);
 }
