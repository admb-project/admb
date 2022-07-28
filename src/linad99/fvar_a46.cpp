/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Member functions dvar_vector::elem_div for various types.
*/

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif


void dvdv_elem_div(void);

/**
Element-wise division of v1 by v2 into a dvar_vector.

@param v1 dvar_vector of numerators
@param v2 dvar_vector of denominators
*/
dvar_vector elem_div(const dvar_vector& v1, const dvar_vector& v2)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

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
  dvector tmp_inv(min, max);

  double_and_int* pv1 = v1.va + min;
  double_and_int* pv2 = v2.va + min;
  double* ptmp_inv = tmp_inv.get_v() + min;
  double_and_int* ptmp = tmp.va + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmp_inv = 1.0 / pv2->x;
    ptmp->x = pv1->x * *ptmp_inv;
    ++pv2;
    ++pv1;
    ++ptmp_inv;
    ++ptmp;
  }

  // The derivative list considerations
  save_identifier_string("bbbb");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  save_identifier_string("wwww");
  fp->save_dvector_value(tmp_inv);
  fp->save_dvector_position(tmp_inv);
  save_identifier_string("vvvv");
  fp->save_dvar_vector_position(v2);
  save_identifier_string("uuuu");
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("aaaa");
  gs->GRAD_STACK1->set_gradient_stack(dvdv_elem_div);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Adjoint gradient computation of elem_div(const dvar_vector&, const dvar_vector&)
*/
void dvdv_elem_div(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmppos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  verify_identifier_string("uuuu");
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  verify_identifier_string("vvvv");
  dvector_position tmp_divpos=fp->restore_dvector_position();
  dvector tmp_div=fp->restore_dvector_value(tmp_divpos);
  verify_identifier_string("wwww");
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector cv1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("bbbb");

  int min = cv1.indexmin();
  int max = cv1.indexmax();
  dvector dfv1(min, max);
  int min2 = tmp_div.indexmin();
  int max2 = tmp_div.indexmax();
  dvector dfv2(min2, max2);

  double* ptmp_div = tmp_div.get_v() + min;
  double* pdftmp = dftmp.get_v() + min;
  double* pcv1 = cv1.get_v() + min;
  double* pdfv1 = dfv1.get_v() + min;
  double* pdfv2 = dfv2.get_v() + min2;
  for (int i = min; i <= max; ++i)
  {
    //tmp+=cv1(i)*cv2(i);

    //double& xx=tmp_div.elem(i);
    double xx = *ptmp_div;
    //dfv1(i)=dftmp.elem(i)*xx;
    *pdfv1 = *pdftmp * xx;
    //dfv2(i)=-dftmp.elem(i)*cv1.elem(i)*xx*xx;
    *pdfv2 = -(*pdftmp) * *pcv1 * xx * xx;
    ++ptmp_div;
    ++pdftmp;
    ++pcv1;
    ++pdfv1;
    ++pdfv2;
  }
  dfv1.save_dvector_derivatives(v1pos);
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void dvcv_elem_div(void);

/**
Element-wise division of v1 by v2 into a dvar_vector.

@param v1 dvar_vector of numerators
@param v2 dvector of denominators
*/
dvar_vector elem_div(const dvar_vector& v1, const dvector& v2)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
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
  dvector tmp_inv(min, max);

  double_and_int* pv1 = v1.va + min;
  double* pv2 = v2.get_v() + min;
  double* ptmp_inv = tmp_inv.get_v() + min;
  double_and_int* ptmp = tmp.va + min;
  for (int i = min; i <= max; ++i)
  {
    //tmp_inv.elem(i)=1./v2.elem(i);
    //tmp.elem_value(i)=v1.elem_value(i)*tmp_inv.elem(i);
    *ptmp_inv = 1.0 / *pv2;
    ptmp->x = pv1->x * *ptmp_inv;
    ++ptmp_inv;
    ++ptmp;
    ++pv1;
    ++pv2;
  }

  // The derivative list considerations
  save_identifier_string("bbbb");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  save_identifier_string("wwww");
  fp->save_dvector_value(tmp_inv);
  fp->save_dvector_position(tmp_inv);
  save_identifier_string("vvvv");
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("aaaa");
  gs->GRAD_STACK1->set_gradient_stack(dvcv_elem_div);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Adjoint gradient computation of elem_div(const dvar_vector&, const dvector&)
*/
void dvcv_elem_div(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmppos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  verify_identifier_string("vvvv");
  dvector_position tmp_divpos=fp->restore_dvector_position();
  dvector tmp_div=fp->restore_dvector_value(tmp_divpos);
  verify_identifier_string("wwww");
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector cv1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("bbbb");
  dvector dfv1(cv1.indexmin(),cv1.indexmax());
  for (int i=cv1.indexmin();i<=cv1.indexmax();i++)
  {
    dfv1(i)=dftmp.elem(i)*tmp_div.elem(i);
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void cvdv_elem_div(void);

/**
Element-wise division of v1 by v2 into a dvar_vector.

@param v1 dvector of numerators
@param v2 dvar_vector of denominators
*/
dvar_vector elem_div(const dvector& v1, const dvar_vector& v2)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  gs->RETURN_ARRAYS_INCREMENT();

  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
    "dvar_vector elem_prod(const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
  dvar_vector tmp(v1.indexmin(),v1.indexmax());
  dvector tmp_inv(v1.indexmin(),v1.indexmax());

  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    double x=1./v2.elem_value(i);
    tmp.elem_value(i)=v1.elem(i)*x;
    tmp_inv.elem(i)=-tmp.elem_value(i)*x;
  }

  // The derivative list considerations
  save_identifier_string("bbbb");
  fp->save_dvector_value(tmp_inv);
  fp->save_dvector_position(tmp_inv);
  save_identifier_string("vvvv");
  fp->save_dvar_vector_position(v2);
  save_identifier_string("uuuu");
  fp->save_dvar_vector_position(tmp);
  save_identifier_string("aaaa");
  gs->GRAD_STACK1->set_gradient_stack(cvdv_elem_div);
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Adjoint gradient computation of elem_div(const dvector&, const dvar_vector&)
*/
void cvdv_elem_div(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmppos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  verify_identifier_string("uuuu");
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  verify_identifier_string("vvvv");
  dvector_position tmp_divpos=fp->restore_dvector_position();
  dvector tmp_div=fp->restore_dvector_value(tmp_divpos);
  verify_identifier_string("bbbb");
  dvector dfv2(tmp_div.indexmin(),tmp_div.indexmax());
  for (int i=dfv2.indexmin();i<=dfv2.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    dfv2(i)=dftmp.elem(i)*tmp_div.elem(i);
  }
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
