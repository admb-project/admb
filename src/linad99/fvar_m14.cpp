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
// constructors, destructors and misc functions involving class prevariable

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

/*
 dvar_matrix  operator*(const dvar_matrix& m1, const dvar_matrix& m2 )
 {
   if (m1.colmin() != m2.rowmin() || m1.colmax() != m2.rowmax())
   {
     cerr << " Incompatible array bounds in dmatrix  operator * (const dmatrix& x, const dmatrix& m)\n";
     ad_exit(21);
   }
   //dmatrix cm1=value(m1);
   //dmatrix cm2=value(m2);
   dmatrix tmp(m1.rowmin(),m1.rowmax(), m2.colmin(), m2.colmax());
   double sum;
   double ** temp_col=(double **) malloc(m2.rowsize()*sizeof(double*));
   temp_col-=m2.rowmin();


   for (int j=m2.colmin(); j<=m2.colmax(); j++)
   {

     for (int k=m2.rowmin(); k<=m2.rowmax(); k++)
     {
       temp_col[k] = (double*) &m2.elem_value(k,j);
     }

     for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
     {
       sum=0.0;
       const dvar_vector& temp_row = m1(i);
       for (int k=m1.colmin(); k<=m1.colmax(); k++)
       {
          sum+=temp_row.elem_value(k) * (*temp_col[k]);
         // sum+=temp_row(k) * cm2(k,j);
       }
       tmp(i,j)=sum;
     }
   }


   temp_col+=m2.rowmin();
   free ((char*)temp_col);
   dvar_matrix vtmp=nograd_assign(tmp);
   gradient_structure* gs = gradient_structure::get();
   DF_FILE* fp = gs->fp;
   save_identifier_string("TEST1");
   m1.save_dvar_matrix_value(fp);
   m1.save_dvar_matrix_position(fp);
   m2.save_dvar_matrix_value(fp);
   m2.save_dvar_matrix_position(fp);
   vtmp.save_dvar_matrix_position(fp);
   save_identifier_string("TEST6");
   gs->GRAD_STACK1->set_gradient_stack(dmdm_prod);
   return vtmp;
 }
*/

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix operator*(const dvar_matrix& m1, const dvar_matrix& m2)
 {
   if (m1.colmin() != m2.rowmin() || m1.colmax() != m2.rowmax())
   {
     cerr << " Incompatible array bounds in "
     "dmatrix operator*(const dmatrix& x, const dmatrix& m)\n";
     ad_exit(21);
   }
   //dmatrix cm1=value(m1);
   //dmatrix cm2=value(m2);
   dmatrix tmp(m1.rowmin(),m1.rowmax(), m2.colmin(), m2.colmax());
   double sum;


   for (int j=m2.colmin(); j<=m2.colmax(); j++)
   {
     dvector m2col=column_value(m2,j);

     for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
     {
       sum=value(m1(i))*m2col;
       tmp(i,j)=sum;
     }
   }

   dvar_matrix vtmp=nograd_assign(tmp);
   gradient_structure* gs = gradient_structure::_instance;
   DF_FILE* fp = gradient_structure::fp;
   save_identifier_string("TEST1");
   fp->save_dvar_matrix_value(m1);
   fp->save_dvar_matrix_position(m1);
   fp->save_dvar_matrix_value(m2);
   fp->save_dvar_matrix_position(m2);
   fp->save_dvar_matrix_position(vtmp);
   save_identifier_string("TEST6");
   gs->GRAD_STACK1->set_gradient_stack(dmdm_prod);
   return vtmp;
 }

/**
 * Description not yet available.
 * \param
 */
void dmdm_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

  verify_identifier_string("TEST6");
  dvar_matrix_position vpos=fp->restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(vpos);
  dvar_matrix_position m2pos=fp->restore_dvar_matrix_position();
  dmatrix cm2=fp->restore_dvar_matrix_value(m2pos);
  dvar_matrix_position m1pos=fp->restore_dvar_matrix_position();
  dmatrix cm1=fp->restore_dvar_matrix_value(m1pos);
  verify_identifier_string("TEST1");
  dmatrix dfm1(m1pos);
  dmatrix dfm2(m2pos);
  double dfsum;
  dfm1.initialize();
  dfm2.initialize();
  for (int j=cm2.colmin(); j<=cm2.colmax(); j++)
  {
    for (int i=cm1.rowmin(); i<=cm1.rowmax(); i++)
    {
      //tmp.elem(i,j)=sum;
      dfsum=dftmp.elem(i,j);
      for (int k=cm1.colmin(); k<=cm1.colmax(); k++)
      {
        //sum+=cm1(i,k) * cm2(k,j);
        dfm1.elem(i,k)+=dfsum * cm2.elem(k,j);
        dfm2.elem(k,j)+=dfsum * cm1.elem(i,k);
      }
    }
  }
  dfm1.save_dmatrix_derivatives(m1pos);
  dfm2.save_dmatrix_derivatives(m2pos);
  // cout << "leaving dmdm_prod"<<endl;
}
