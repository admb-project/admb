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
    return x+t1;
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

    RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("wcbf");
    x.save_prevariable_position(fp);
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=t1.elem_value(i)+value(x);
    }
    tmp.save_dvar_vector_position(fp);
    t1.save_dvar_vector_position(fp);
    save_identifier_string("dduu");
    RETURN_ARRAYS_DECREMENT();
    gs->GRAD_STACK1->set_gradient_stack(DF_dble_dv_add);
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_dble_dv_add(void)
 {
    DF_FILE* fp = gradient_structure::get_fp();

    verify_identifier_string("dduu");
    dvar_vector_position t1_pos=restore_dvar_vector_position(fp);
    dvar_vector_position tmp_pos=restore_dvar_vector_position(fp);
    prevariable_position xpos=restore_prevariable_position(fp);
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("wcbf");
    //double xinv=1./x;
    double dfx=0.;
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
       // tmp.elem_value(i)=value(x)+t1.elem_value(i);
      //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
      dfx+=dftmp(i);
      dft1(i)=dftmp(i);
    }
    save_double_derivative(dfx,xpos);
    dft1.save_dvector_derivatives(t1_pos);
 }
