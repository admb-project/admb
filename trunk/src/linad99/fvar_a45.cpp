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
  RETURN_ARRAYS_INCREMENT();
  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
    "dvar_vector elem_prod(const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
  dvar_vector tmp(v1.indexmin(),v1.indexmax());

  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    tmp.elem_value(i)=v1.elem_value(i)*v2.elem_value(i);
  }

  // The derivative list considerations
  save_identifier_string("b");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  v2.save_dvar_vector_value();
  v2.save_dvar_vector_position();
  tmp.save_dvar_vector_position();
  save_identifier_string("a");
  gradient_structure::GRAD_STACK1->set_gradient_stack(dvdv_elem_prod);
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvdv_elem_prod(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("a");
  dvar_vector_position tmppos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  dvar_vector_position v2pos=restore_dvar_vector_position();
  dvector cv2=restore_dvar_vector_value(v2pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector cv1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("b");
  dvector dfv1(cv1.indexmin(),cv1.indexmax());
  dvector dfv2(cv2.indexmin(),cv2.indexmax());
  for (int i=cv1.indexmin();i<=cv1.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    dfv1(i)=dftmp.elem(i)*cv2.elem(i);
    dfv2(i)=dftmp.elem(i)*cv1.elem(i);
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
  RETURN_ARRAYS_INCREMENT();
  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
    "dvar_vector elem_prod(const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
  dvar_vector tmp(v1.indexmin(),v1.indexmax());

  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    tmp.elem_value(i)=v1.elem(i)*v2.elem_value(i);
  }

  // The derivative list considerations
  save_identifier_string("b");
  v1.save_dvector_value();
  v1.save_dvector_position();
  v2.save_dvar_vector_position();
  tmp.save_dvar_vector_position();
  save_identifier_string("a");
  gradient_structure::GRAD_STACK1->set_gradient_stack(cvdv_elem_prod);
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void cvdv_elem_prod(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("a");
  dvar_vector_position tmppos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  dvar_vector_position v2pos=restore_dvar_vector_position();
  dvector_position v1pos=restore_dvector_position();
  dvector cv1=restore_dvector_value(v1pos);
  verify_identifier_string("b");
  dvector dfv2(cv1.indexmin(),cv1.indexmax());
  for (int i=cv1.indexmin();i<=cv1.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    dfv2(i)=dftmp.elem(i)*cv1.elem(i);
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
  RETURN_ARRAYS_INCREMENT();
  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
    "dvar_vector elem_prod(const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
  dvar_vector tmp(v1.indexmin(),v1.indexmax());

  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    tmp.elem_value(i)=v1.elem_value(i)*v2.elem(i);
  }

  // The derivative list considerations
  save_identifier_string("b");
  v1.save_dvar_vector_position();
  v2.save_dvector_value();
  v2.save_dvector_position();
  tmp.save_dvar_vector_position();
  save_identifier_string("a");
  gradient_structure::GRAD_STACK1->set_gradient_stack(dvcv_elem_prod);
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvcv_elem_prod(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("a");
  dvar_vector_position tmppos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmppos);
  dvector_position v2pos=restore_dvector_position();
  dvector cv2=restore_dvector_value(v2pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  verify_identifier_string("b");
  dvector dfv1(cv2.indexmin(),cv2.indexmax());
  for (int i=cv2.indexmin();i<=cv2.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    dfv1(i)=dftmp.elem(i)*cv2.elem(i);
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
