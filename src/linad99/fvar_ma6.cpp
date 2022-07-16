/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions for empirical_covariance and outer_prod.
*/

#include "fvar.hpp"

void dfempirical_covarv_partial(void);

/**
 * Description not yet available.
 * \param
 */
dvar_matrix empirical_covariance(const dvar_matrix& _v1,
  const imatrix& _missflags)
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
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  save_identifier_string("ru");
  fp->save_imatrix_value(missflags);
  fp->save_imatrix_position(missflags);
  fp->save_int_value(nobs);
  fp->save_dvar_matrix_position(tmp);
  fp->save_dvar_matrix_value(v1);
  fp->save_dvar_matrix_position(v1);
  save_identifier_string("rv");
  gs->GRAD_STACK1->set_gradient_stack(dfempirical_covarv_partial);
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
void dfempirical_covarv_partial(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  verify_identifier_string("rv");
  dvar_matrix_position v1pos=fp->restore_dvar_matrix_position();
  dmatrix v1=fp->restore_dvar_matrix_value(v1pos);
  dvar_matrix_position tmppos=fp->restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(tmppos);
  int nobs=fp->restore_int_value();
  imatrix_position mfpos=fp->restore_imatrix_position();
  imatrix missflags=fp->restore_imatrix_value(mfpos);
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
dvar_matrix empirical_covariance(const dvar_matrix& v1)
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
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  save_identifier_string("ru");
  fp->save_dvar_matrix_position(tmp);
  fp->save_dvar_matrix_value(v1);
  fp->save_dvar_matrix_position(v1);
  save_identifier_string("rv");
  gs->GRAD_STACK1->set_gradient_stack(dfempirical_covarv);
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
void dfempirical_covarv(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  verify_identifier_string("rv");
  dvar_matrix_position v1pos=fp->restore_dvar_matrix_position();
  dmatrix v1=fp->restore_dvar_matrix_value(v1pos);
  dvar_matrix_position tmppos=fp->restore_dvar_matrix_position();
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
dvar_matrix outer_prod(const dvar_vector& v1, const dvar_vector& v2)
{
  int imin = v1.indexmin();
  int imax = v1.indexmax();
  int jmin = v2.indexmin();
  int jmax = v2.indexmax();

  dvar_matrix tmp(imin, imax, jmin, jmax);

  dvar_vector* ptmpi = &tmp(imin);
  double_and_int* pv1i = v1.va + imin;
  for (int i = imin; i <= imax; ++i)
  {
    double_and_int* ptmpij = ptmpi->va + jmin;
    double_and_int* pv2j = v2.va + jmin;
    for (int j = jmin; j <= jmax; ++j)
    {
      ptmpij->x = pv1i->x * pv2j->x;

      ++ptmpij;
      ++pv2j;
    }
    ++ptmpi;
    ++pv1i;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  save_identifier_string("tu");
  fp->save_dvar_matrix_position(tmp);
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_value(v2);
  fp->save_dvar_vector_position(v2);
  save_identifier_string("tv");
  gs->GRAD_STACK1->set_gradient_stack(dfouter_prodvv);

  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dfouter_prodvv(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  verify_identifier_string("tv");
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  dvector v2=restore_dvar_vector_value(v2pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  dvar_matrix_position tmppos=fp->restore_dvar_matrix_position();
  dmatrix dftmp=restore_dvar_matrix_derivatives(tmppos);
  verify_identifier_string("tu");

  int imin = v1.indexmin();
  int imax = v1.indexmax();
  int jmin = v2.indexmin();
  int jmax = v2.indexmax();
  dvector dfv1(imin, imax);
  dvector dfv2(jmin, jmax);
  dfv1.initialize();
  dfv2.initialize();

  double* pv1i = v1.get_v() + imin;
  double* pdfv1i = dfv1.get_v() + imin;
  dvector* pdftmpi = &dftmp(imin);
  for (int i = imin; i <= imax; ++i)
  {
    double* pv2j = v2.get_v() + jmin;
    double* pdfv2j = dfv2.get_v() + jmin;
    double* pdftmpij = pdftmpi->get_v() + jmin;
    for (int j = jmin; j <= jmax; ++j)
    {
      //tmp.elem_value(i,j)=v1.elem_value(i)*v2.elem_value(j);
      *pdfv1i += *pdftmpij * *pv2j;
      *pdfv2j += *pdftmpij * *pv1i;

      ++pv2j;
      ++pdfv2j;
      ++pdftmpij;
    }
    ++pv1i;
    ++pdfv1i;
    ++pdftmpi;
  }
  dfv1.save_dvector_derivatives(v1pos);
  dfv2.save_dvector_derivatives(v2pos);
}

/**
Compute the outer product of v1 and v2 vectors into dvar_matrix.

@param v1 dvector
@param v2 dvar_vector
*/
dvar_matrix outer_prod(const dvector& v1, const dvar_vector& v2)
 {
   gradient_structure* gs = gradient_structure::get();
   gs->RETURN_ARRAYS_INCREMENT();

   dvar_matrix tmp(v1.indexmin(),v1.indexmax(), v2.indexmin(), v2.indexmax() );

   for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
   {
     for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
     {
       tmp.elem(i,j)=v1.elem(i)*v2.elem(j);
     }
   }
   gs->RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }
/**
Compute the outer product of v1 and v2 vectors into dvar_matrix.

@param v1 dvar_vector
@param v2 dvector
*/
dvar_matrix outer_prod(const dvar_vector& v1, const dvector& v2)
 {
   gradient_structure* gs = gradient_structure::get();
   gs->RETURN_ARRAYS_INCREMENT();

   dvar_matrix tmp(v1.indexmin(),v1.indexmax(), v2.indexmin(), v2.indexmax() );

   for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
   {
     for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
     {
       tmp.elem(i,j)=v1.elem(i)*v2.elem(j);
     }
   }
   gs->RETURN_ARRAYS_DECREMENT();

   return(tmp);
 }
