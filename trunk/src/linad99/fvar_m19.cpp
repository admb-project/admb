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
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable

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

void dmcm_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_matrix operator*(const dvar_matrix& m1, const dmatrix& cm2)
 {
   if (m1.colmin() != cm2.rowmin() || m1.colmax() != cm2.rowmax())
   {
     cerr << " Incompatible array bounds in "
     "dmatrix operator*(const dvar_matrix& x, const dmatrix& m)\n";
     ad_exit(21);
   }
   dmatrix cm1=value(m1);
   //dmatrix cm2=value(m2);
   dmatrix tmp(m1.rowmin(),m1.rowmax(), cm2.colmin(), cm2.colmax());
#ifdef OPT_LIB
   const size_t rowsize = (size_t)cm2.rowsize();
#else
   const int _rowsize = cm2.rowsize();
   assert(_rowsize > 0);
   const size_t rowsize = (size_t)_rowsize;
#endif
   try
   {
     double* temp_col = new double[rowsize];
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
         dvector& temp_row = cm1(i);
         for (int k=cm1.colmin(); k<=cm1.colmax(); k++)
         {
           sum+=temp_row(k) * (temp_col[k]);
           // sum+=temp_row(k) * cm2(k,j);
         }
         tmp(i,j)=sum;
       }
     }
     temp_col+=cm2.rowmin();
     delete [] temp_col;
     temp_col = 0;
   }
   catch (std::bad_alloc& e)
   {
     cerr << "Error: Unable to allocate array.\n";
     ad_exit(21);
   }
   dvar_matrix vtmp=nograd_assign(tmp);
   save_identifier_string("TEST1");
   //m1.save_dvar_matrix_value();
   m1.save_dvar_matrix_position();
   cm2.save_dmatrix_value();
   cm2.save_dmatrix_position();
   vtmp.save_dvar_matrix_position();
   save_identifier_string("TEST6");
   gradient_structure::GRAD_STACK1->
            set_gradient_stack(dmcm_prod);
   return vtmp;
 }

/**
 * Description not yet available.
 * \param
 */
void dmcm_prod(void)
{
  verify_identifier_string("TEST6");
  dvar_matrix_position vpos=restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(vpos);
  dmatrix_position m2pos=restore_dmatrix_position();
  dmatrix cm2=restore_dmatrix_value(m2pos);
  dvar_matrix_position m1pos=restore_dvar_matrix_position();
  //dmatrix cm1=restore_dvar_matrix_value(m1pos);
  verify_identifier_string("TEST1");
  dmatrix dfm1(m1pos);
  double dfsum;
  dfm1.initialize();
  for (int j=cm2.colmin(); j<=cm2.colmax(); j++)
  {
    for (int i=dfm1.rowmin(); i<=dfm1.rowmax(); i++)
    {
      //tmp.elem(i,j)=sum;
      dfsum=dftmp.elem(i,j);
      for (int k=dfm1.colmin(); k<=dfm1.colmax(); k++)
      {
        //sum+=cm1(i,k) * cm2(k,j);
        dfm1.elem(i,k)+=dfsum * cm2.elem(k,j);
        //dfm2.elem(k,j)+=dfsum * cm1.elem(i,k);
      }
    }
  }
  dfm1.save_dmatrix_derivatives(m1pos);
  //dfm2.save_dmatrix_derivatives(m2pos);
  // cout << "leaving dmdm_prod"<<endl;
}
