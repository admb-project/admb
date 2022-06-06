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

  void DF_v_xdble_diff(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator-(const dvector& t1, const prevariable& x)
  {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    gs->RETURN_ARRAYS_INCREMENT();

    int min = t1.indexmin();
    int max = t1.indexmax();
    dvar_vector tmp(min, max);
    save_identifier_string("zcb");
    fp->save_prevariable_position(x);

    double_and_int* ptmp = tmp.va + min;
    double* pt1 = t1.get_v() + min;
    double value_x = value(x);
    for (int i = min; i <= max; ++i)
    {
      //tmp.elem_value(i)=t1.elem(i)-value(x);
      ptmp->x = *pt1 - value_x;
      ++ptmp;
      ++pt1;
    }
    fp->save_dvar_vector_position(tmp);
    save_identifier_string("ddu");
    gs->GRAD_STACK1->set_gradient_stack(DF_v_xdble_diff);
    gs->RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_v_xdble_diff(void)
 {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    verify_identifier_string("ddu");
    dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
    prevariable_position xpos=fp->restore_prevariable_position();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    verify_identifier_string("zcb");
    //double xinv=1./x;
    int min = tmp_pos.indexmin();
    int max = tmp_pos.indexmax();
    double dfx = 0.0;
    double* pdftmp = dftmp.get_v() + max;
    for (int i = max; i >= min; --i)
    {
      // tmp.elem_value(i)=t1.elem(i)-value(x);
      //dfx -= dftmp(i);
      dfx -= *pdftmp;
      --pdftmp;
    }
    save_double_derivative(dfx,xpos);
 }
