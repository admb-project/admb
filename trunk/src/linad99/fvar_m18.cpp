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

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#ifndef OPT_LIB
  #include <cassert>
#endif

void cmdm_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const dmatrix& cm1, const dvar_matrix& m2)
 {
   if (cm1.colmin() != m2.rowmin() || cm1.colmax() != m2.rowmax())
   {
     cerr << " Incompatible array bounds in "
     "dmatrix operator*(const dmatrix& x, const dvar_matrix& m)\n";
     ad_exit(21);
   }
   dmatrix cm2=value(m2);
   dmatrix tmp(cm1.rowmin(),cm1.rowmax(), m2.colmin(), m2.colmax());

#ifdef OPT_LIB
   const size_t rowsize = (size_t)m2.rowsize();
#else
   const int _rowsize = m2.rowsize();
   assert(_rowsize > 0);
   const size_t rowsize = (size_t)_rowsize;
#endif
   double* temp_col=(double*)malloc(rowsize * sizeof(double));
   if (!temp_col)
   {
     cerr << "Error: Unable to allocate array.\n";
     ad_exit(21);
   }
   temp_col-=cm2.rowmin();

   for (int j=cm2.colmin(); j<=cm2.colmax(); j++)
   {
     for (int k=cm2.rowmin(); k<=cm2.rowmax(); k++)
     {
       temp_col[k] = cm2.elem(k,j);
     }

     for (int i=cm1.rowmin(); i<=cm1.rowmax(); i++)
     {
       double sum=0.0;
       const dvector& temp_row = cm1(i);
       for (int k=cm1.colmin(); k<=cm1.colmax(); k++)
       {
          sum+=temp_row(k) * (temp_col[k]);
         // sum+=temp_row(k) * cm2(k,j);
       }
       tmp(i,j)=sum;
     }
   }

   temp_col+=cm2.rowmin();
   free ((char*)temp_col);
   dvar_matrix vtmp=nograd_assign(tmp);
   save_identifier_string("TEST1");
   cm1.save_dmatrix_value();
   cm1.save_dmatrix_position();
   // m2.save_dvar_matrix_value();
   m2.save_dvar_matrix_position();
   vtmp.save_dvar_matrix_position();
   save_identifier_string("TEST6");
   gradient_structure::GRAD_STACK1->
            set_gradient_stack(cmdm_prod);
   return vtmp;
 }

/**
 * Description not yet available.
 * \param
 */
void cmdm_prod(void)
{
  verify_identifier_string("TEST6");
  dvar_matrix_position vpos=restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(vpos);
  dvar_matrix_position m2pos=restore_dvar_matrix_position();
  //dmatrix cm2=restore_dvar_matrix_value(m2pos);
  dmatrix_position m1pos=restore_dmatrix_position();
  dmatrix cm1=restore_dmatrix_value(m1pos);
  verify_identifier_string("TEST1");
  //dmatrix dfm1(m1pos);
  dmatrix dfm2(m2pos);
  double dfsum;
  dfm2.initialize();
  for (int j=dfm2.colmin(); j<=dfm2.colmax(); j++)
  {
    for (int i=cm1.rowmin(); i<=cm1.rowmax(); i++)
    {
      //tmp.elem(i,j)=sum;
      dfsum=dftmp.elem(i,j);
      for (int k=cm1.colmin(); k<=cm1.colmax(); k++)
      {
        //sum+=cm1(i,k) * cm2(k,j);
       //dfm1.elem(i,k)+=dfsum * cm2.elem(k,j);
        dfm2.elem(k,j)+=dfsum * cm1.elem(i,k);
      }
    }
  }
  //dfm1.save_dmatrix_derivatives(m1pos);
  dfm2.save_dmatrix_derivatives(m2pos);
  // cout << "leaving dmdm_prod"<<endl;
}
