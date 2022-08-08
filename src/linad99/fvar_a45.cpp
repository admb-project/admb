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


void dvdv_elem_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector elem_prod(const dvar_vector& v1, const dvar_vector& v2)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = v1.indexmin();
  int max = v1.indexmax();
#ifndef OPT_LIB
  if (min != v2.indexmin() || max != v2.indexmax())
  {
    cerr << "Incompatible bounds in "
    "dvar_vector elem_prod(const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
#endif
  dvar_vector tmp(min, max);

  double_and_int* ptmpi = tmp.va + min;
  const double_and_int* pv1i = v1.va + min;
  const double_and_int* pv2i = v2.va + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = pv1i->x * pv2i->x;
    ++ptmpi;
    ++pv1i;
    ++pv2i;
  }

  // The derivative list considerations
  save_identifier_string("b");
  DF_FILE* fp = gradient_structure::fp;
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_value(v2);
  fp->save_dvar_vector_position(v2);
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("a");
  gradient_structure::GRAD_STACK1->set_gradient_stack(dvdv_elem_prod);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvdv_elem_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("a");
  dvar_vector_position tmppos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  dvector cv2=restore_dvar_vector_value(v2pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector cv1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("b");
  int min = cv1.indexmin();
  int max = cv2.indexmax();
  dvector dfv1(min, max);
  dvector dfv2(min, max);

  double* pdfv1i = dfv1.get_v() + min;
  double* pdfv2i = dfv2.get_v() + min;
  double* pdftmpi = dftmp.get_v() + min;
  double* pcv1i = cv1.get_v() + min;
  double* pcv2i = cv2.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //tmp+=cv1(i)*cv2(i);
    *pdfv1i = *pdftmpi * *pcv2i;
    *pdfv2i = *pdftmpi * *pcv1i;

    ++pdfv1i;
    ++pdfv2i;
    ++pdftmpi;
    ++pcv1i;
    ++pcv2i;
  }
  dfv1.save_dvector_derivatives(v1pos);
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void cvdv_elem_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector elem_prod(const dvector& v1, const dvar_vector& v2)
{
  gradient_structure* gs = gradient_structure::_instance;
  DF_FILE* fp = gradient_structure::fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = v1.indexmin();
  int max = v1.indexmax();
#ifndef OPT_LIB
  if (min != v2.indexmin() || max != v2.indexmax())
  {
    cerr << "Incompatible bounds in dvar_vector elem_prod(const dvector&, const dvar_vector&)\n";
    ad_exit(1);
  }
#endif

  dvar_vector tmp(min, max);

  double_and_int* ptmpi = tmp.va + min;
  double* pv1i = v1.get_v() + min;
  double_and_int* pv2i = v2.va + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = *pv1i * pv2i->x;

    ++ptmpi;
    ++pv1i;
    ++pv2i;
  }

  // The derivative list considerations
  save_identifier_string("b");
  fp->save_dvector_value(v1);
  fp->save_dvector_position(v1);
  fp->save_dvar_vector_position(v2);
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("a");
  gs->GRAD_STACK1->set_gradient_stack(cvdv_elem_prod);
  gs->RETURN_ARRAYS_DECREMENT();

  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void cvdv_elem_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("a");
  dvar_vector_position tmppos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  dvector_position v1pos=fp->restore_dvector_position();
  dvector cv1=fp->restore_dvector_value(v1pos);
  verify_identifier_string("b");

  int min = cv1.indexmin();
  int max = cv1.indexmax();
  dvector dfv2(min, max);

  double* pdfv2i = dfv2.get_v() + min;
  double* pdftmpi = dftmp.get_v() + min;
  double* pcv1i = cv1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //tmp+=cv1(i)*cv2(i);
    *pdfv2i = *pdftmpi * *pcv1i;

    ++pdfv2i;
    ++pdftmpi;
    ++pcv1i;
  }
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void dvcv_elem_prod(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector elem_prod(const dvar_vector& v1, const dvector& v2)
{
  gradient_structure* gs = gradient_structure::_instance;
  DF_FILE* fp = gradient_structure::fp;
  gs->RETURN_ARRAYS_INCREMENT();

  int min = v1.indexmin();
  int max = v1.indexmax();
#ifndef OPT_LIB
  if (min != v2.indexmin() || max != v2.indexmax())
  {
    cerr << "Incompatible bounds in dvar_vector elem_prod(const dvar_vector&, const dvector&)\n";
    ad_exit(1);
  }
#endif
  dvar_vector tmp(min, max);

  double_and_int* ptmpi = tmp.va + min;
  double_and_int* pv1i = v1.va + min;
  double* pv2i = v2.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    ptmpi->x = pv1i->x * *pv2i;

    ++ptmpi;
    ++pv1i;
    ++pv2i;
  }

  // The derivative list considerations
  save_identifier_string("b");
  fp->save_dvar_vector_position(v1);
  fp->save_dvector_value(v2);
  fp->save_dvector_position(v2);
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("a");
  gs->GRAD_STACK1->set_gradient_stack(dvcv_elem_prod);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvcv_elem_prod(void)
{
  DF_FILE* fp = gradient_structure::fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("a");
  dvar_vector_position tmppos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  dvector_position v2pos=fp->restore_dvector_position();
  dvector cv2=fp->restore_dvector_value(v2pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  verify_identifier_string("b");

  int min = cv2.indexmin();
  int max = cv2.indexmax();
  dvector dfv1(min, max);
  double* pdfv1i = dfv1.get_v() + min;
  double* pdftmpi = dftmp.get_v() + min;
  double* pcv2i = cv2.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //tmp+=cv1(i)*cv2(i);
    *pdfv1i = *pdftmpi * *pcv2i;

    ++pdfv1i;
    ++pdftmpi;
    ++pcv2i;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
