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

void dmcv_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dvar_matrix& m, const dvector& x)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  gs->RETURN_ARRAYS_INCREMENT();

  int imin = m.rowmin();
  int imax = m.rowmax();
  int jmin = x.indexmin();
  int jmax = x.indexmax();

#ifndef OPT_LIB
  if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
  {
    cerr << " Incompatible array bounds in "
     "dvar_vector operator * (const dvar_matrix& m, const dvar_vector& x)\n";
    ad_exit(21);
  }
#endif

  kkludge_object kludge;
  dvar_vector tmp(imin, imax, kludge);

  double_and_int* ptmpi = tmp.va + imin;
  const dvar_vector* pmi = &m(imin);
  for (int i = imin; i <= imax; ++i)
  {
    double sum = 0.0;
    const double_and_int* pmij = pmi->va + jmin;
    double* pxj = x.get_v() + jmin;
    for (int j = jmin; j <= jmax; ++j)
    {
      //sum+=m[i][j]*x[j];
      sum += pmij->x  * *pxj;
      ++pxj;
      ++pmij;
    }
    ptmpi->x = sum;

    ++pmi;
    ++ptmpi;
  }
  save_identifier_string("PL4");
  fp->save_dvector_value(x);
  fp->save_dvector_position(x);
  fp->save_dvar_matrix_position(m);
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("PLX");
  gs->GRAD_STACK1->set_gradient_stack(dmcv_prod);
  gs->RETURN_ARRAYS_DECREMENT();

  return tmp;
 }

/**
 * Description not yet available.
 * \param
 */
void dmcv_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

  verify_identifier_string("PLX");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvar_matrix_position m_pos=fp->restore_dvar_matrix_position();
  dvar_vector_position x_pos=fp->restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
  verify_identifier_string("PL4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  dmatrix dfm(m_pos);
  dfm.initialize();

  int mmin = dfm.rowmin();
  int mmax = dfm.rowmax();
  int jmin = x.indexmin();
  int jmax = x.indexmax();
  double* pdftmpi = dftmp.get_v() + mmax;
  dvector* pdfmi = &dfm(mmax);
  for (int i=mmax; i>=mmin; i--)
  {
     // tmp.elem_value(i)=sum;
     double dfsum = *pdftmpi;
     double* pdfmij = pdfmi->get_v() + jmax;
     double* pxj = x.get_v() + jmax;
     for (int j = jmax; j >= jmin; --j)
     {
       //sum+=(m.elem(i)).elem_value(j)*x.elem_value(j);
       *pdfmij += dfsum * *pxj;

       --pdfmij;
       --pxj;
     }
     //sum=0.0;
     dfsum = 0.0;

     --pdfmi;
     --pdftmpi;
  }
  dfm.save_dmatrix_derivatives(m_pos);
}
