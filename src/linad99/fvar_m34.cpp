/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

void dmcv_prod(void);

 dvar_vector  operator * (_CONST dvar_matrix& m,_CONST dvector& x )
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
     _CONST dvar_vector& tt=m.elem(i);
     for (int j=x.indexmin(); j<=x.indexmax(); j++)
     {
       //sum+=m[i][j]*x[j];
       sum+=tt.elem_value(j)*x.elem(j);
     }
     tmp.elem_value(i)=sum;
   }
  save_identifier_string("PL4");
  x.save_dvector_value();
  x.save_dvector_position();
  m.save_dvar_matrix_position();
  tmp.save_dvar_vector_position();
  save_identifier_string("PLX");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dmcv_prod);
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

void dmcv_prod(void)
{
  verify_identifier_string("PLX");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvar_matrix_position m_pos=restore_dvar_matrix_position();
  dvar_vector_position x_pos=restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
  verify_identifier_string("PL4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  
  dmatrix dfm(m_pos);
  dfm.initialize();
  
   double dfsum;
   int mmin=dfm.rowmin(); 
   int mmax=dfm.rowmax();
   for (int i=mmax; i>=mmin; i--)
   {
     // tmp.elem_value(i)=sum;
     dfsum=dftmp.elem(i);
     dvector& tt=dfm.elem(i);
     for (int j=x.indexmax(); j>=x.indexmin(); j--)
     {
       //sum+=(m.elem(i)).elem_value(j)*x.elem_value(j);
       tt.elem(j)+=dfsum*x.elem(j);
     }
     //sum=0.0;
     dfsum=0.0;
   }
   dfm.save_dmatrix_derivatives(m_pos);
}

