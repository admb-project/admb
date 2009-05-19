/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include "fvar.hpp"

void dv_pluseq(void);

 dvar_vector& dvar_vector::operator += (_CONST dvar_vector& v1)
 {
   if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
   {
     cerr << " Incompatible array bounds in dvector& operator += (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem_value(i) += v1.elem_value(i);
     }
   }

   save_identifier_string("uuvv");
   save_dvar_vector_position();  // for this->
   v1.save_dvar_vector_position();
   save_identifier_string("wwxx");
    gradient_structure::GRAD_STACK1->
            set_gradient_stack(dv_pluseq);
   return(*this);
 }

void dv_pluseq(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("wwxx");
  dvar_vector_position v1_pos=restore_dvar_vector_position();
  dvar_vector_position this_pos=restore_dvar_vector_position();
  verify_identifier_string("uuvv");
  dvector dfthis=restore_dvar_vector_der_nozero(this_pos);
  dfthis.save_dvector_derivatives(v1_pos);
}

 dvar_vector& dvar_vector::operator += (_CONST dvector& v1)
 {
   if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
   {
     cerr << " Incompatible array bounds in dvector& operator += (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem_value(i) += v1.elem(i);
     }
   }
   return(*this);
 }



