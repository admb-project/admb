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
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    gs->RETURN_ARRAYS_INCREMENT();

    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("ccbb");
    save_double_value(x);
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=t1.elem_value(i)*x;
    }
    tmp.save_dvar_vector_position(fp);
    t1.save_dvar_vector_position(fp);
    save_identifier_string("DDaa");
    gs->GRAD_STACK1->set_gradient_stack(DF_dv_double_prod);
    gs->RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_dv_double_prod(void)
 {
    verify_identifier_string("DDaa");
    dvar_vector_position t1_pos=restore_dvar_vector_position();
    dvar_vector_position tmp_pos=restore_dvar_vector_position();
    double x=restore_double_value();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("ccbb");
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
      //tmp.elem_value(i)=value(x)*t1.elem_value(i)*x;
      dft1(i)=dftmp(i)*x;
    }
    dft1.save_dvector_derivatives(t1_pos);
 }

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const double x, const dvar_vector& t1)
  {
    return t1*x;
  }
