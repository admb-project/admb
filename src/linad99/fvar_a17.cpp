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
#ifdef _MSC_VER
  #include <memory.h>
#endif

#ifdef DEBUG
  #include <cassert>
#endif

void dvdv_add(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator+(const dvar_vector& v1, const dvar_vector& v2)
{
  int mmin=v1.indexmin();
  int mmax=v1.indexmax();
#ifndef OPT_LIB
  if (mmin != v2.indexmin() || mmax != v2.indexmax())
  {
    cerr << "Incompatible bounds in "
	 << "dvar_vector operator+(const dvar_vector&, const dvar_vector&).\n";
    ad_exit(1);
  }
#endif
  //dvector cv1=value(v1);
  //dvector cv2=value(v2);
  kkludge_object kkk;
  dvar_vector vtmp(mmin, mmax, kkk);

#ifdef USE_ASSEMBLER
  int min=v1.indexmin();
  int n=v1.indexmax()-min+1;
  dp_vector_add(&(vtmp.elem_value(min)),&(v1.elem_value(min)),
    &(v2.elem_value(min)),n);
#else
  double_and_int* pvtmp = vtmp.va;
  double_and_int* pv1 = v1.va;
  double_and_int* pv2 = v2.va;
  for (int i = mmin; i <= mmax; ++i)
  {
    //vtmp.elem_value(i)=v1.elem_value(i)+v2.elem_value(i);
    pvtmp[i].x = pv1[i].x + pv2[i].x;
  }
#endif

  //dvar_vector vtmp=nograd_assign(tmp);

  grad_stack* GRAD_STACK1 = gradient_structure::GRAD_STACK1;
  DF_FILE* fp = gradient_structure::fp;
  // The derivative list considerations
  save_identifier_string("bbbb");
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(v2);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("aaaa");
  GRAD_STACK1->set_gradient_stack(dvdv_add);

  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvdv_add(void)
{
  DF_FILE* fp = gradient_structure::fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  verify_identifier_string("bbbb");
  int mmin=dftmp.indexmin();
  int mmax=dftmp.indexmax();
#ifdef DEBUG
  assert(mmax >= mmin);
#endif
  dvector dfv1(mmin,mmax);
  dvector dfv2(mmin,mmax);
#ifdef OPT_LIB
  constexpr size_t sizeofdouble = sizeof(double);
  size_t size = (size_t)(mmax - mmin + 1) * sizeofdouble;
  memcpy(&dfv1.elem(mmin),&dftmp.elem(mmin), size);
  memcpy(&dfv2.elem(mmin),&dftmp.elem(mmin), size);
#else
  for (int i=dftmp.indexmin();i<=dftmp.indexmax();i++)
  {
    //vtmp.elem(i)=value(v1.elem(i))+value(v2.elem(i));
    dfv1(i)=dftmp.elem(i);
    dfv2(i)=dftmp.elem(i);
  }
#endif
  dfv1.save_dvector_derivatives(v1pos);
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
