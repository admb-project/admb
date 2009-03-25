/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include "fvar.hpp"


  void DF_v_xdble_diff(void);

  dvar_vector operator - (_CONST dvector& t1,_CONST prevariable& x)
  {
    RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("zcb");
    x.save_prevariable_position();
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=t1.elem(i)-value(x);
    }
    tmp.save_dvar_vector_position();
    save_identifier_string("ddu");
    RETURN_ARRAYS_DECREMENT();
    gradient_structure::GRAD_STACK1->
	    set_gradient_stack(DF_v_xdble_diff);
    return(tmp);
  }

 void DF_v_xdble_diff(void)
 {
    verify_identifier_string("ddu");
    dvar_vector_position tmp_pos=restore_dvar_vector_position();
    prevariable_position xpos=restore_prevariable_position();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    verify_identifier_string("zcb");
    //double xinv=1./x;
    double dfx=0.;
    for (int i=tmp_pos.indexmax(); i>=tmp_pos.indexmin(); i--)
    {
      // tmp.elem_value(i)=t1.elem(i)-value(x);
      dfx-=dftmp(i);
    }
    save_double_derivative(dfx,xpos);
 }

