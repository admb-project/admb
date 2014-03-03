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


void dvdv_elem_div(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector elem_div(const dvar_vector& v1, const dvar_vector& v2)
{
  RETURN_ARRAYS_INCREMENT();
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
    tmp_inv.elem(i)=1./v2.elem_value(i);
    tmp.elem_value(i)=v1.elem_value(i)*tmp_inv.elem(i);
  }

  // The derivative list considerations
  save_identifier_string("bbbb");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  save_identifier_string("wwww");
  tmp_inv.save_dvector_value();
  tmp_inv.save_dvector_position();
  save_identifier_string("vvvv");
  v2.save_dvar_vector_position();
  save_identifier_string("uuuu");
  tmp.save_dvar_vector_position();
  save_identifier_string("aaaa");
  gradient_structure::GRAD_STACK1->set_gradient_stack(dvdv_elem_div);
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvdv_elem_div(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmppos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  verify_identifier_string("uuuu");
  dvar_vector_position v2pos=restore_dvar_vector_position();
  verify_identifier_string("vvvv");
  dvector_position tmp_divpos=restore_dvector_position();
  dvector tmp_div=restore_dvector_value(tmp_divpos);
  verify_identifier_string("wwww");
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector cv1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("bbbb");
  dvector dfv1(cv1.indexmin(),cv1.indexmax());
  dvector dfv2(tmp_div.indexmin(),tmp_div.indexmax());
  for (int i=cv1.indexmin();i<=cv1.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    double& xx=tmp_div.elem(i);
    dfv1(i)=dftmp.elem(i)*xx;
    dfv2(i)=-dftmp.elem(i)*cv1.elem(i)*xx*xx;
  }
  dfv1.save_dvector_derivatives(v1pos);
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void dvcv_elem_div(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector elem_div(const dvar_vector& v1, const dvector& v2)
{
  RETURN_ARRAYS_INCREMENT();
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
    tmp_inv.elem(i)=1./v2.elem(i);
    tmp.elem_value(i)=v1.elem_value(i)*tmp_inv.elem(i);
  }

  // The derivative list considerations
  save_identifier_string("bbbb");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  save_identifier_string("wwww");
  tmp_inv.save_dvector_value();
  tmp_inv.save_dvector_position();
  save_identifier_string("vvvv");
  tmp.save_dvar_vector_position();
  save_identifier_string("aaaa");
  gradient_structure::GRAD_STACK1->set_gradient_stack(dvcv_elem_div);
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvcv_elem_div(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmppos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  verify_identifier_string("vvvv");
  dvector_position tmp_divpos=restore_dvector_position();
  dvector tmp_div=restore_dvector_value(tmp_divpos);
  verify_identifier_string("wwww");
  dvar_vector_position v1pos=restore_dvar_vector_position();
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
 * Description not yet available.
 * \param
 */
dvar_vector elem_div(const dvector& v1, const dvar_vector& v2)
{
  RETURN_ARRAYS_INCREMENT();
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
  tmp_inv.save_dvector_value();
  tmp_inv.save_dvector_position();
  save_identifier_string("vvvv");
  v2.save_dvar_vector_position();
  save_identifier_string("uuuu");
  tmp.save_dvar_vector_position();
  save_identifier_string("aaaa");
  gradient_structure::GRAD_STACK1->set_gradient_stack(cvdv_elem_div);
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void cvdv_elem_div(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmppos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  verify_identifier_string("uuuu");
  dvar_vector_position v2pos=restore_dvar_vector_position();
  verify_identifier_string("vvvv");
  dvector_position tmp_divpos=restore_dvector_position();
  dvector tmp_div=restore_dvector_value(tmp_divpos);
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

