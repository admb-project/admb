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

void dv_pluseq(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::operator+=(const dvar_vector& v1)
 {
   if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
   {
     cerr << " Incompatible array bounds in "
     "dvector& operator += (const dvar_vector&)\n";
     ad_exit(21);
   }

   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem_value(i) += v1.elem_value(i);
     }
   }

   DF_FILE* fp = gradient_structure::get_fp();
   save_identifier_string("uuvv");
   save_dvar_vector_position(fp);  // for this->
   v1.save_dvar_vector_position(fp);
   save_identifier_string("wwxx");
    gradient_structure::get()->GRAD_STACK1->
            set_gradient_stack(dv_pluseq);
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
void dv_pluseq(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("wwxx");
  dvar_vector_position v1_pos=restore_dvar_vector_position(fp);
  dvar_vector_position this_pos=restore_dvar_vector_position(fp);
  verify_identifier_string("uuvv");
  dvector dfthis=restore_dvar_vector_der_nozero(this_pos);
  dfthis.save_dvector_derivatives(v1_pos);
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::operator+=(const dvector& v1)
 {
   if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
   {
     cerr << " Incompatible array bounds in "
     "dvector& operator += (const dvar_vector&)\n";
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
