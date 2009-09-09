/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

 void dv_subassign(void);

 dvar_vector dvar_vector::operator ()(_CONST ivector& u)
 {
   dvar_vector tmp(u.indexmin(),u.indexmax());

   for (int i=u.indexmin();i<=u.indexmax();i++)
   {
     tmp.elem_value(i)=elem_value(u(i));
   }
   save_identifier_string("by");
   save_dvar_vector_position();
   tmp.save_dvar_vector_position();
   u.save_ivector_value();
   u.save_ivector_position();
   save_identifier_string("ay");
   gradient_structure::GRAD_STACK1->
     set_gradient_stack(dv_subassign);
   return tmp;
 }

void dv_subassign(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("ay");
  ivector_position u_pos=restore_ivector_position();
  ivector u=restore_ivector_value(u_pos);
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position t_pos=restore_dvar_vector_position();
  dvector dft(t_pos.indexmin(),t_pos.indexmax());
  verify_identifier_string("by");
  dft.initialize();
  int mmin=dftmp.indexmin();
  int mmax=dftmp.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
     //tmp.elem_value(i)=this->elem_value(u(i));
     dft.elem(u(i))+=dftmp.elem(i);
  }
  dft.save_dvector_derivatives(t_pos);
}


 dvar_vector dvar_vector::operator ()(_CONST lvector& u)
 {
   dvar_vector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
     tmp(i)=(*this)(u(i));
   }
   return tmp;
 }
