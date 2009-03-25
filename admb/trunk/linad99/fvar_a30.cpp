/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */




#include "fvar.hpp"

void dv_xminuseq(void);

 dvar_vector& dvar_vector::operator-= (_CONST prevariable& d)
 {
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem_value(i) -= value(d);
     }
   }

   save_identifier_string("Pvv");
   save_dvar_vector_position();  // for this->
   d.save_prevariable_position();
   save_identifier_string("Pxx");
    gradient_structure::GRAD_STACK1->
            set_gradient_stack(dv_xminuseq);
   return(*this);
 }

void dv_xminuseq(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("Pxx");
  prevariable_position d_pos=restore_prevariable_position();
  dvar_vector_position this_pos=restore_dvar_vector_position();
  verify_identifier_string("Pvv");
  dvector dfthis=restore_dvar_vector_der_nozero(this_pos);
  double temp=-sum(dfthis);
  save_double_derivative(temp,d_pos);
}



void dv_xpluseq(void);

 dvar_vector& dvar_vector::operator+= (_CONST prevariable& d)
 {
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem_value(i) += value(d);
     }
   }

   save_identifier_string("Qvv");
   save_dvar_vector_position();  // for this->
   d.save_prevariable_position();
   save_identifier_string("Qxx");
    gradient_structure::GRAD_STACK1->
	    set_gradient_stack(dv_xpluseq);
   return(*this);
 }

void dv_xpluseq(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("Qxx");
  prevariable_position d_pos=restore_prevariable_position();
  dvar_vector_position this_pos=restore_dvar_vector_position();
  verify_identifier_string("Qvv");
  dvector dfthis=restore_dvar_vector_der_nozero(this_pos);
  double temp=sum(dfthis);
  save_double_derivative(temp,d_pos);
}

 dvar_vector& dvar_vector::operator-= (double d)
 {
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem_value(i) -= d;
     }
   }

   return(*this);
 }

 dvar_vector& dvar_vector::operator+= (double d)
 {
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem_value(i) += d;
     }
   }

   return(*this);
 }


