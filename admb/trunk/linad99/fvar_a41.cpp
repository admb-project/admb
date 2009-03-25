/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"


  dvar_vector operator + (_CONST dvar_vector& t1, CGNU_DOUBLE x)
  {
    return x+t1;
  }

  void DF_cdble_dv_add(void);

  dvar_vector operator + ( CGNU_DOUBLE x,_CONST dvar_vector& t1)
  {
    RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(t1.indexmin(),t1.indexmax());
    save_identifier_string("wctf");
    for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
    {
      tmp.elem_value(i)=t1.elem_value(i)+x;
    }
    tmp.save_dvar_vector_position();
    t1.save_dvar_vector_position();
    save_identifier_string("ddtu");
    RETURN_ARRAYS_DECREMENT();
    gradient_structure::GRAD_STACK1->
	    set_gradient_stack(DF_cdble_dv_add);
    return(tmp);
  }

 void DF_cdble_dv_add(void)
 {
    verify_identifier_string("ddtu");
    dvar_vector_position t1_pos=restore_dvar_vector_position();
    dvar_vector_position tmp_pos=restore_dvar_vector_position();
    dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
    dvector dft1(t1_pos.indexmin(),t1_pos.indexmax());
    verify_identifier_string("wctf");
    for (int i=t1_pos.indexmax(); i>=t1_pos.indexmin(); i--)
    {
      // tmp.elem_value(i)=x+t1.elem_value(i);
      dft1(i)=dftmp(i);
    }
    dft1.save_dvector_derivatives(t1_pos);
 }

