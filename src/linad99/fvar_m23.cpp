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

void dvdm_prod(void);
void dvcm_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dvar_vector& x, const dvar_matrix& m)
 {
   RETURN_ARRAYS_INCREMENT();

   if (x.indexmin() != m.rowmin() || x.indexmax() != m.rowmax())
   {
     cerr << " Incompatible array bounds in "
     "dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)\n";
     ad_exit(21);
   }

   kkludge_object kkk;
   dvar_vector tmp(m.colmin(),m.colmax(),kkk);
   double sum;
   for (int j=m.colmin(); j<=m.colmax(); j++)
   {
     sum=0.0;
     for (int i=x.indexmin(); i<=x.indexmax(); i++)
     {
       //sum+=x[i]*m[i][j];
       sum+=x.elem_value(i)*(m.elem(i)).elem_value(j);
     }
     tmp.elem_value(j)=sum;
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
      set_gradient_stack(dvdm_prod);
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
void dvdm_prod(void)
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
   for (int j=m.colmax(); j>=m.colmin(); j--)
   {
     //tmp.elem_value(j)=sum;
     dfsum=dftmp.elem(j);
     for (int i=x.indexmax(); i>=x.indexmin(); i--)
     {
       //sum+=x[i]*m[i][j];
       //sum+=x.elem_value(i)*(m.elem(i)).elem_value(j);
       dfm.elem(i,j)+=dfsum*x.elem(i);
       dfx.elem(i)+=dfsum*m.elem(i,j);
     }
     //sum=0.0;
     dfsum=0.0;
   }
   dfx.save_dvector_derivatives(x_pos);
   dfm.save_dmatrix_derivatives(m_pos);
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dvar_vector& x, const dmatrix& m)
 {
   RETURN_ARRAYS_INCREMENT();

   if (x.indexmin() != m.rowmin() || x.indexmax() != m.rowmax())
   {
     cerr << " Incompatible array bounds in "
     "dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)\n";
     ad_exit(21);
   }

   kkludge_object kkk;
   dvar_vector tmp(m.colmin(),m.colmax(),kkk);
   double sum;
   for (int j=m.colmin(); j<=m.colmax(); j++)
   {
     sum=0.0;
     for (int i=x.indexmin(); i<=x.indexmax(); i++)
     {
       //sum+=x[i]*m[i][j];
       sum+=x.elem_value(i)*(m.elem(i)).elem(j);
     }
     tmp.elem_value(j)=sum;
   }

  save_identifier_string("P4");
  x.save_dvar_vector_position();
  save_identifier_string("PLACE3");
  m.save_dmatrix_value();
  m.save_dmatrix_position();
  save_identifier_string("PLACE2");
  tmp.save_dvar_vector_position();
  save_identifier_string("PLACE1");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dvcm_prod);
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
void dvcm_prod(void)
{
  verify_identifier_string("PLACE1");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  verify_identifier_string("PLACE2");
  dvar_matrix_position m_pos=restore_dvar_matrix_position();
  dmatrix m=restore_dvar_matrix_value(m_pos);
  verify_identifier_string("PLACE3");
  dvar_vector_position x_pos=restore_dvar_vector_position();
  verify_identifier_string("P4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  dvector dfx(x_pos.indexmin(),x_pos.indexmax());
  dfx.initialize();

   double dfsum;
   int imax=dfx.indexmax();
   int imin=dfx.indexmin();
   for (int j=m.colmax(); j>=m.colmin(); j--)
   {
     //tmp.elem_value(j)=sum;
     dfsum=dftmp.elem(j);
     for (int i=imax; i>=imin; i--)
     {
       //sum+=x[i]*m[i][j];
       //sum+=x.elem_value(i)*(m.elem(i)).elem_value(j);
       dfx.elem(i)+=dfsum*m.elem(i,j);
     }
     //sum=0.0;
     dfsum=0.0;
   }
   dfx.save_dvector_derivatives(x_pos);
}
