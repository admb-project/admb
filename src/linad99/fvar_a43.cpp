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

 void DF_cdble_dv_div(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator/(const double x, const dvar_vector& t1)
  {
    gradient_structure* gs = gradient_structure::_instance;
    DF_FILE* fp = gradient_structure::fp;
    gs->RETURN_ARRAYS_INCREMENT();

    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("cffb");
    fp->save_double_value(x);
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=x/t1.elem_value(i);
    }
    fp->save_dvar_vector_value(t1);
    fp->save_dvar_vector_position(tmp);
    fp->save_dvar_vector_position(t1);
    save_identifier_string("dffa");
    gs->RETURN_ARRAYS_DECREMENT();
    gradient_structure::GRAD_STACK1->set_gradient_stack(DF_cdble_dv_div);
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_cdble_dv_div(void)
 {
    DF_FILE* fp = gradient_structure::fp;

    verify_identifier_string("dffa");
    dvar_vector_position t1_pos=fp->restore_dvar_vector_position();
    dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
    dvector t1=restore_dvar_vector_value(t1_pos);
    double x=fp->restore_double_value();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("cffb");
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
      //tmp.elem_value(i)=value(x)/t1.elem_value(i);
      double t1inv=1./t1.elem(i);
      dft1(i)=-dftmp(i)*x*t1inv*t1inv;
    }
    dft1.save_dvector_derivatives(t1_pos);
 }
