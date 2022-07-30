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

void dmdv_prod(void);
void cmdv_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  gs->RETURN_ARRAYS_INCREMENT();

  int imin = m.rowmin();
  int imax = m.rowmax();
  int jmin = x.indexmin();
  int jmax = x.indexmax();
#ifndef OPT_LIB
  if (jmin != m.colmin() || jmax != m.colmax())
  {
     cerr << " Incompatible array bounds in "
     "dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)\n";
     ad_exit(21);
  }
#endif

  kkludge_object kkk;
  dvar_vector tmp(imin, imax, kkk);
  double_and_int* ptmp = tmp.va + imin;
  for (int i = imin; i <= imax; ++i)
  {
    double_and_int* px = x.va + jmin;
    dvar_vector& mi = m.elem(i);
    double_and_int* pmi = mi.va + jmin;

    double sum = 0.0;
    for (int j = jmin; j <= jmax; ++j)
    {
       //sum+=m[i][j]*x[j];
       sum += pmi->x * px->x;
       ++px;
       ++pmi;
    }
    ptmp->x = sum;
    ++ptmp;
  }
  save_identifier_string("PLACE4");
  fp->save_dvar_vector_value(x);
  fp->save_dvar_vector_position(x);
  save_identifier_string("PLACE3");
  fp->save_dvar_matrix_value(m);
  fp->save_dvar_matrix_position(m);
  save_identifier_string("PLACE2");
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("PLACE1");
  gs->GRAD_STACK1->set_gradient_stack(dmdv_prod);
  gs->RETURN_ARRAYS_DECREMENT();
  return(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void dmdv_prod(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  verify_identifier_string("PLACE1");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  verify_identifier_string("PLACE2");
  dvar_matrix_position m_pos=fp->restore_dvar_matrix_position();
  dmatrix m=fp->restore_dvar_matrix_value(m_pos);
  verify_identifier_string("PLACE3");
  dvar_vector_position x_pos=fp->restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
  verify_identifier_string("PLACE4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  dmatrix dfm(m_pos);
  dvector dfx(x_pos.indexmin(),x_pos.indexmax());
  dfm.initialize();
  dfx.initialize();

  int imax = m.rowmax();
  int imin = m.rowmin();
  int jmax = x.indexmax();
  int jmin = x.indexmin();
  double* pdftmp = dftmp.get_v() + imax;
  for (int i = imax; i >= imin; --i)
  {
    //tmp.elem_value(i)=sum;
    double dfsum = *pdftmp;
    double* px = x.get_v() + jmax;
    double* pdfx = dfx.get_v() + jmax;
    double* pdfmi = dfm(i).get_v() + jmax;
    double* pmi = m(i).get_v() + jmax;
    for (int j = jmax; j >= jmin; --j)
    {
      //sum+=(m.elem(i)).elem_value(j)*x.elem_value(j);
      *pdfmi += dfsum * *px;
      *pdfx += dfsum * *pmi;
      --px;
      --pdfx;
      --pdfmi;
      --pmi;
    }
    //sum=0.0;
    dfsum=0.0;

    --pdftmp;
  }
  dfx.save_dvector_derivatives(x_pos);
  dfm.save_dmatrix_derivatives(m_pos);
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator*(const dmatrix& m, const dvar_vector& x)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int imin = m.rowmin();
  int imax = m.rowmax();
  int jmin = x.indexmin();
  int jmax = x.indexmax();

#ifndef OPT_LIB
  if (jmin != m.colmin() || jmax != m.colmax())
  {
    cerr << " Incompatible array bounds in "
    "dvar_vector operator*(const dvar_matrix& m, const dvar_vector& x)\n";
    ad_exit(21);
  }
#endif

  kkludge_object kkk;
  dvar_vector tmp(imin, imax, kkk);

  double_and_int* ptmpi = tmp.va + imin;
  const dvector* pmi = &m(imin);
  for (int i = imin; i <= imax; ++i)
  {
    double sum = 0.0;
    double_and_int* pxj  = x.va + jmin;
    double* pmij = pmi->get_v() + jmin;
    for (int j = jmin; j <= jmax; ++j)
    {
      //sum+=m[i][j]*x[j];
      sum += *pmij * pxj->x;

      ++pxj;
      ++pmij;
    }
    //tmp.elem_value(i) = sum;
    ptmpi->x = sum;

    ++ptmpi;
    ++pmi;
  }

  //save_identifier_string("PLACE4");
  fp->save_dvar_vector_value(x);
  fp->save_dvar_vector_position(x);
  fp->save_dmatrix_value(m);
  fp->save_dmatrix_position(m);
  //save_identifier_string("PLACE2");
  fp->save_dvar_vector_position(tmp);
  //save_identifier_string("PLACE1");
  gs->GRAD_STACK1->set_gradient_stack(cmdv_prod);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void cmdv_prod(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  //verify_identifier_string("PLACE1");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  //verify_identifier_string("PLACE2");
  dmatrix_position m_pos=fp->restore_dmatrix_position();
  dmatrix m=fp->restore_dmatrix_value(m_pos);
  dvar_vector_position x_pos=fp->restore_dvar_vector_position();
  dvector x=restore_dvar_vector_value(x_pos);
  //verify_identifier_string("PLACE4");
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);

  int jmax = x.indexmax();
  int jmin = x.indexmin();
  dvector dfx(jmin, jmax);
  dfx.initialize();

  int imax = m.rowmax();
  int imin = m.rowmin();
  dvector* pmi = &m(imax);
  double* pdftmpi = dftmp.get_v() + imax;
  for (int i = imax; i >= imin; --i)
  {
    // tmp.elem_value(i)=sum;
    double dfsum = *pdftmpi;
    double* pmij = pmi->get_v() + jmax;
    double* pdfxj = dfx.get_v() + jmax;
    for (int j = jmax; j >= jmin; --j)
    {
      //sum+=(m.elem(i)).elem(j)*x.elem_value(j);
      *pdfxj += dfsum * *pmij;

      --pmij;
      --pdfxj;
    }
    //sum=0.0;
    dfsum = 0.0;

    --pmi;
    --pdftmpi;
  }
  dfx.save_dvector_derivatives(x_pos);
}
