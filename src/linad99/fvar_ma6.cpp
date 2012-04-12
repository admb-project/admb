/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

void dfempirical_covarv_partial(void);

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix empirical_covariance(_CONST dvar_matrix& _v1,
  _CONST imatrix& _missflags)
 {
   dvar_matrix& v1 = (dvar_matrix&) (_v1);
   imatrix& missflags=(imatrix&) (_missflags);
   int mmin=v1(v1.indexmin()).indexmin();
   int mmax=v1(v1.indexmin()).indexmax();
   dvar_matrix tmp(mmin,mmax,mmin,mmax);
   int rmin=v1.indexmin();
   int rmax=v1.indexmax();
   int nobs=rmax-rmin+1;

   
   tmp.initialize();
   for (int ii=rmin; ii<=rmax; ii++)
   {
     for (int i=mmin; i<=mmax; i++)
     {
       if (!missflags(ii,i))
       {
         for (int j=mmin; j<=mmax; j++)
         {
           if (!missflags(ii,j))
           {
             tmp.elem_value(i,j)+=v1.elem_value(ii,i)*v1.elem_value(ii,j);
           }
         }
       }
     }
   }
   for (int i=mmin; i<=mmax; i++)
   {
     for (int j=mmin; j<=mmax; j++)
     {
       tmp.elem_value(i,j)/=nobs;
     }
   }
  save_identifier_string("ru");
  missflags.save_imatrix_value();
  missflags.save_imatrix_position();
  save_int_value(nobs);
  tmp.save_dvar_matrix_position();
  v1.save_dvar_matrix_value();
  v1.save_dvar_matrix_position();
  save_identifier_string("rv");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfempirical_covarv_partial);
   return(tmp);
 }   

/**
 * Description not yet available.
 * \param
 */   
void dfempirical_covarv_partial(void)
{
  verify_identifier_string("rv");
  dvar_matrix_position v1pos=restore_dvar_matrix_position();
  dmatrix v1=restore_dvar_matrix_value(v1pos);
  dvar_matrix_position tmppos=restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(tmppos);
  int nobs=restore_int_value();
  imatrix_position mfpos=restore_imatrix_position();
  imatrix missflags=restore_imatrix_value(mfpos);
  verify_identifier_string("ru");
  int mmin=v1(v1.indexmin()).indexmin();
  int mmax=v1(v1.indexmin()).indexmax();
  int rmin=v1.indexmin();
  int rmax=v1.indexmax();

  dmatrix dfv1(rmin,rmax,mmin,mmax);
  dfv1.initialize();
  for (int i=mmin; i<=mmax; i++)
  {
    for (int j=mmin; j<=mmax; j++)
    {
      //tmp.elem_value(i,j)/=nobs;
      dftmp(i,j)/=nobs;
    }
  }
  for (int ii=rmin; ii<=rmax; ii++)
  {
    for (int i=mmin; i<=mmax; i++)
    {
      if (!missflags(ii,i))
      {
        for (int j=mmin; j<=mmax; j++)
        {
          if (!missflags(ii,j))
          {
            //tmp.elem_value(i,j)+=v1.elem_value(ii,i)*v1.elem_value(ii,j);
            dfv1(ii,i)+=dftmp(i,j)*v1(ii,j);
            dfv1(ii,j)+=dftmp(i,j)*v1(ii,i);
          }
        }
      }
    }
  }
  dfv1.save_dmatrix_derivatives(v1pos);
}

void dfempirical_covarv(void);

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix empirical_covariance(_CONST dvar_matrix& v1)
 {
   int mmin=v1(v1.indexmin()).indexmin();
   int mmax=v1(v1.indexmin()).indexmax();
   dvar_matrix tmp(mmin,mmax,mmin,mmax);
   int rmin=v1.indexmin();
   int rmax=v1.indexmax();

   
   tmp.initialize();
   int nobs=rmax-rmin+1;
   for (int ii=rmin; ii<=rmax; ii++)
   {
     for (int i=mmin; i<=mmax; i++)
     {
       for (int j=mmin; j<=mmax; j++)
       {
         tmp.elem_value(i,j)+=v1.elem_value(ii,i)*v1.elem_value(ii,j);
       }
     }
   }
   for (int i=mmin; i<=mmax; i++)
   {
     for (int j=mmin; j<=mmax; j++)
     {
       tmp.elem_value(i,j)/=double(nobs);
     }
   }
  save_identifier_string("ru");
  tmp.save_dvar_matrix_position();
  v1.save_dvar_matrix_value();
  v1.save_dvar_matrix_position();
  save_identifier_string("rv");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfempirical_covarv);
   return(tmp);
 }      

/**
 * Description not yet available.
 * \param
 */
void dfempirical_covarv(void)
{
  verify_identifier_string("rv");
  dvar_matrix_position v1pos=restore_dvar_matrix_position();
  dmatrix v1=restore_dvar_matrix_value(v1pos);
  dvar_matrix_position tmppos=restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(tmppos);
  verify_identifier_string("ru");
  int mmin=v1(v1.indexmin()).indexmin();
  int mmax=v1(v1.indexmin()).indexmax();
  int rmin=v1.indexmin();
  int rmax=v1.indexmax();

  dmatrix dfv1(rmin,rmax,mmin,mmax);
  dfv1.initialize();
  int nobs=rmax-rmin+1;
  for (int i=mmin; i<=mmax; i++)
  {
    for (int j=mmin; j<=mmax; j++)
    {
      //tmp.elem_value(i,j)/=double(nobs);
      dftmp(i,j)/=double(nobs);
    }
  }
  for (int ii=rmin; ii<=rmax; ii++)
  {
    for (int i=mmin; i<=mmax; i++)
    {
      for (int j=mmin; j<=mmax; j++)
      {
        //tmp.elem_value(i,j)+=v1.elem_value(ii,i)*v1.elem_value(ii,j);
        dfv1(ii,i)+=dftmp(i,j)*v1(ii,j);
        dfv1(ii,j)+=dftmp(i,j)*v1(ii,i);
      }
    }
  }
  dfv1.save_dmatrix_derivatives(v1pos);
}

void dfouter_prodvv(void);

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix outer_prod(_CONST dvar_vector& v1,_CONST dvar_vector& v2 )
 {
   dvar_matrix tmp(v1.indexmin(),v1.indexmax(), v2.indexmin(), v2.indexmax() );

   for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
   {
     for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
     {
       tmp.elem_value(i,j)=v1.elem_value(i)*v2.elem_value(j);
     }
   }
  save_identifier_string("tu");
  tmp.save_dvar_matrix_position();
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  v2.save_dvar_vector_value();
  v2.save_dvar_vector_position();
  save_identifier_string("tv");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfouter_prodvv);
   return(tmp);
 }      

/**
 * Description not yet available.
 * \param
 */
void dfouter_prodvv(void)
{
  verify_identifier_string("tv");
  dvar_vector_position v2pos=restore_dvar_vector_position();
  dvector v2=restore_dvar_vector_value(v2pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  dvar_matrix_position tmppos=restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(tmppos);
  verify_identifier_string("tu");
  dvector dfv1(v1pos.indexmin(),v1pos.indexmax());
  dvector dfv2(v2pos.indexmin(),v2pos.indexmax());
  dfv1.initialize();
  dfv2.initialize();
  for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
  {
    for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
    {
      //tmp.elem_value(i,j)=v1.elem_value(i)*v2.elem_value(j);
      dfv1(i)+=dftmp(i,j)*v2(j);
      dfv2(j)+=dftmp(i,j)*v1(i);
    }
  }
  dfv1.save_dvector_derivatives(v1pos);
  dfv2.save_dvector_derivatives(v2pos);
}

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix outer_prod(_CONST dvector& v1,_CONST dvar_vector& v2 )
 {
   RETURN_ARRAYS_INCREMENT();

   dvar_matrix tmp(v1.indexmin(),v1.indexmax(), v2.indexmin(), v2.indexmax() );

   for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
   {
     for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
     {
       tmp.elem(i,j)=v1.elem(i)*v2.elem(j);
     }
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }      

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix outer_prod(_CONST dvar_vector& v1,_CONST dvector& v2 )
 {
   RETURN_ARRAYS_INCREMENT();

   dvar_matrix tmp(v1.indexmin(),v1.indexmax(), v2.indexmin(), v2.indexmax() );

   for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
   {
     for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
     {
       tmp.elem(i,j)=v1.elem(i)*v2.elem(j);
     }
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }
