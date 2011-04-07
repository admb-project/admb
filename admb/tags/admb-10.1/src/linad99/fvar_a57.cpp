/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

 void DF_unary_diff(void);

/**
 * Description not yet available.
 * \param
 */
  dvar_vector dvar_vector::operator- (void)
  {
    RETURN_ARRAYS_INCREMENT();
    int mmin=indexmin();
    int mmax=indexmax();
    dvar_vector tmp(mmin,mmax);
    save_identifier_string("ec");
    for (int i=mmin; i<=mmax; i++)
    {
      tmp.elem_value(i)=-elem_value(i);
    }
    tmp.save_dvar_vector_position();
    save_dvar_vector_position();
    save_identifier_string("d");
    RETURN_ARRAYS_DECREMENT();
    gradient_structure::GRAD_STACK1->
	    set_gradient_stack(DF_unary_diff);
    return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_unary_diff(void)
 {
    verify_identifier_string("d");
    dvar_vector_position t1_pos=restore_dvar_vector_position();
    dvar_vector_position tmp_pos=restore_dvar_vector_position();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("ec");
    //double xinv=1./x;
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
       // tmp.elem_value(i)=t1.elem_value(i)-value(x);
      //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
      dft1(i)=-dftmp(i);
    }
    dft1.save_dvector_derivatives(t1_pos);
 }
