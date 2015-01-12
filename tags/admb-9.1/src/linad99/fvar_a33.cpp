/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"


  void DF_dv_dble_div(void);

  dvar_vector operator / (_CONST dvar_vector& t1,_CONST prevariable& x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("ccbb");
    x.save_prevariable_value();
    x.save_prevariable_position();
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=t1.elem_value(i)/value(x);
    }
    tmp.save_dvar_vector_value();
    tmp.save_dvar_vector_position();
    t1.save_dvar_vector_position();
    save_identifier_string("ddaa");
    RETURN_ARRAYS_DECREMENT();
    gradient_structure::GRAD_STACK1->
	    set_gradient_stack(DF_dv_dble_div);
    return(tmp);
  }

 void DF_dv_dble_div(void)
 {
    verify_identifier_string("ddaa");
    dvar_vector_position t1_pos=restore_dvar_vector_position();
    dvar_vector_position tmp_pos=restore_dvar_vector_position();
    dvector tmp=restore_dvar_vector_value(tmp_pos);
    prevariable_position xpos=restore_prevariable_position();
    double x=restore_prevariable_value();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("ccbb");
    double xinv=1./x;
    double dfx=0.;
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
      //tmp.elem_value(i)=value(x)*t1.elem_value(i)/value(x);
      dfx-=dftmp(i)*tmp(i)*xinv;
      dft1(i)=dftmp(i)*xinv;
    }
    save_double_derivative(dfx,xpos);
    dft1.save_dvector_derivatives(t1_pos);
 }

