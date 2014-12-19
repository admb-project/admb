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
#ifndef OPT_LIB
  #include <cassert>
#endif

void dvdv_add(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator+(const dvar_vector& v1, const dvar_vector& v2)
{
  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
    "prevariable operator + (const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
  //dvector cv1=value(v1);
  //dvector cv2=value(v2);
  kkludge_object kkk;
  dvar_vector vtmp(v1.indexmin(),v1.indexmax(),kkk);
#ifdef OPT_LIB
    int mmin=v1.indexmin();
    int mmax=v1.indexmax();
    const double * pv1=&v1.elem_value(mmin);
    const double * pv1m=&v1.elem_value(mmax);
    const double * pv2=&v2.elem_value(mmin);
    double * pt=&vtmp.elem_value(mmin);
    do
    {
      *pt++ = *pv1++ + *pv2++;
    }
    while (pv1<=pv1m);

#else
  #ifndef USE_ASSEMBLER
    int mmin=v1.indexmin();
    int mmax=v1.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      vtmp.elem_value(i)=v1.elem_value(i)+v2.elem_value(i);
    }
  #else
    int min=v1.indexmin();
    int n=v1.indexmax()-min+1;
    dp_vector_add(&(vtmp.elem_value(min)),&(v1.elem_value(min)),
      &(v2.elem_value(min)),n);
  #endif
#endif

  //dvar_vector vtmp=nograd_assign(tmp);

  // The derivative list considerations
  save_identifier_string("bbbb");
  v1.save_dvar_vector_position();
  v2.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("aaaa");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(dvdv_add);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvdv_add(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v2pos=restore_dvar_vector_position();
  dvar_vector_position v1pos=restore_dvar_vector_position();
  verify_identifier_string("bbbb");
  int mmin=dftmp.indexmin();
  int mmax=dftmp.indexmax();
#ifndef OPT_LIB
  assert(mmax >= mmin);
#endif
  dvector dfv1(mmin,mmax);
  dvector dfv2(mmin,mmax);
#ifdef OPT_LIB
  size_t size = (size_t)(mmax - mmin + 1);
  memcpy(&dfv1.elem(mmin),&dftmp.elem(mmin), size * sizeof(double));
  memcpy(&dfv2.elem(mmin),&dftmp.elem(mmin), size * sizeof(double));
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
