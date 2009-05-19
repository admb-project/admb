/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

void dmdv_prod(void);
void cmdv_prod(void);

 dvar_vector  operator * (_CONST dvar_matrix& m,_CONST dvar_vector& x )
 {
   RETURN_ARRAYS_INCREMENT();

   if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
   {
     cerr << " Incompatible array bounds in dvar_vector  operator * (_CONST dvar_matrix& m,_CONST dvar_vector& x)\n";
     ad_exit(21);
   }

   kkludge_object kkk;
   dvar_vector tmp(m.rowmin(),m.rowmax(),kkk);
   double sum;

   for (int i=m.rowmin(); i<=m.rowmax(); i++)
   {
     sum=0.0;
     for (int j=x.indexmin(); j<=x.indexmax(); j++)
     {
       //sum+=m[i][j]*x[j];
       sum+=(m.elem(i)).elem_value(j)*x.elem_value(j);
     }
     tmp.elem_value(i)=sum;
   }
  save_identifier_string("PLACE4");
  x.save_dvar_vector_value();
  x.save_dvar_vector_position();
  save_identifier_string("PLACE3");
  m.save_dvar_matrix_value();
  m.save_dvar_matrix_position();
  save_identifier_string("PLACE2");
  tmp.save_dvar_vector_position();
  save_identifier_string("PLACE1");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dmdv_prod);
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

void dmdv_prod(void)
{
  verify_identifier_string("PLACE1");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  verify_identifier_string("PLACE2");
  dvar_matrix_position m_pos=restore_dvar_matrix_position();
  dmatrix m=restore_dvar_matrix_value(m_pos);
  verify_identifier_string("PLACE3");
  dvar_vector_position x_pos=restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
  verify_identifier_string("PLACE4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  
  dmatrix dfm(m_pos);
  dvector dfx(x_pos.indexmin(),x_pos.indexmax());
  dfm.initialize();
  dfx.initialize();
  
   double dfsum;
   for (int i=m.rowmax(); i>=m.rowmin(); i--)
   {
     // tmp.elem_value(i)=sum;
     dfsum=dftmp.elem(i);
     for (int j=x.indexmax(); j>=x.indexmin(); j--)
     {
       //sum+=(m.elem(i)).elem_value(j)*x.elem_value(j);
       dfm.elem(i,j)+=dfsum*x.elem(j);
       dfx.elem(j)+=dfsum*m.elem(i,j);
     }
     //sum=0.0;
     dfsum=0.0;
   }
   dfx.save_dvector_derivatives(x_pos);
   dfm.save_dmatrix_derivatives(m_pos);
}

dvar_vector  operator * (_CONST dmatrix& m,_CONST dvar_vector& x )
 {
   RETURN_ARRAYS_INCREMENT();

   if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
   {
     cerr << " Incompatible array bounds in dvar_vector  operator * (_CONST dvar_matrix& m,_CONST dvar_vector& x)\n";
     ad_exit(21);
   }

   kkludge_object kkk;
   dvar_vector tmp(m.rowmin(),m.rowmax(),kkk);
   double sum;

   for (int i=m.rowmin(); i<=m.rowmax(); i++)
   {
     sum=0.0;
     for (int j=x.indexmin(); j<=x.indexmax(); j++)
     {
       //sum+=m[i][j]*x[j];
       sum+=(m.elem(i)).elem(j)*x.elem_value(j);
     }
     tmp.elem_value(i)=sum;
   }
  save_identifier_string("PLACE4");
  x.save_dvar_vector_value();
  x.save_dvar_vector_position();
  m.save_dmatrix_value();
  m.save_dmatrix_position();
  save_identifier_string("PLACE2");
  tmp.save_dvar_vector_position();
  save_identifier_string("PLACE1");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(cmdv_prod);
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

void cmdv_prod(void)
{
  verify_identifier_string("PLACE1");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  verify_identifier_string("PLACE2");
  dmatrix_position m_pos=restore_dmatrix_position();
  dmatrix m=restore_dmatrix_value(m_pos);
  dvar_vector_position x_pos=restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
  verify_identifier_string("PLACE4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  
  dvector dfx(x_pos.indexmin(),x_pos.indexmax());
  dfx.initialize();
  
   double dfsum;
   for (int i=m.rowmax(); i>=m.rowmin(); i--)
   {
     // tmp.elem_value(i)=sum;
     dfsum=dftmp.elem(i);
     for (int j=x.indexmax(); j>=x.indexmin(); j--)
     {
       //sum+=(m.elem(i)).elem(j)*x.elem_value(j);
       dfx.elem(j)+=dfsum*m.elem(i,j);
     }
     //sum=0.0;
     dfsum=0.0;
   }
   dfx.save_dvector_derivatives(x_pos);
}

