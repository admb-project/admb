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
void dvcv_sub(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator-(const dvar_vector& v1, const dvector& v2)
{
  int min = v1.indexmin();
  int max = v1.indexmax();

#ifndef OPT_LIB
  if (min != v2.indexmin() || max != v2.indexmax())
  {
    cerr << "Incompatible bounds in prevariable operator-(const dvar_vector&, const dvector&)\n";
    ad_exit(1);
  }
#endif

  //dvector cv1=value(v1);
  //dvector cv2=value(v2);
  dvar_vector vtmp(min, max);

  double_and_int* pvtmp = vtmp.va;
  double_and_int* pv1 = v1.va;
  double* pv2 = v2.get_v();
  for (int i = min; i <= max; ++i)
  {
    pvtmp[i].x = pv1[i].x - pv2[i];
  }

  //dvar_vector vtmp=nograd_assign(tmp);
  grad_stack* GRAD_STACK1 = gradient_structure::GRAD_STACK1;
  DF_FILE* fp = gradient_structure::fp;
  // The derivative list considerations
  save_identifier_string("bbbb");
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("aaaa");
  GRAD_STACK1->set_gradient_stack(dvcv_sub);

  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvcv_sub(void)
{
  DF_FILE* fp = gradient_structure::fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  verify_identifier_string("bbbb");

  int min = dftmp.indexmin();
  int max = dftmp.indexmax();
  dvector dfv1(min, max);
  double* pdfv1 = dfv1.get_v();
  double* pdftmp = dftmp.get_v();
  for (int i = min; i <= max; ++i)
  {
    //vtmp.elem(i)=value(v1.elem(i))+v2.elem(i);
    pdfv1[i] = pdftmp[i];
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
