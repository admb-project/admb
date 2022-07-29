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
void cvdv_sub(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator-(const dvector& v1, const dvar_vector& v2)
{
  int min = v1.indexmin();
  int max = v1.indexmax();
#ifndef OPT_LIB
  if (min != v2.indexmin() || max != v2.indexmax())
  {
    cerr << "Incompatible bounds in "
      "prevariable operator-(const dvector& v1, const dvar_vector& v2)" << endl;
    ad_exit(1);
  }
#endif
  //dvector cv1=value(v1);
  //dvector cv2=value(v2);
  dvar_vector vtmp(min, max);
  double_and_int* pvtmp = vtmp.va + min;
  double* pv1 = v1.get_v() + min;
  double_and_int* pv2 = v2.va + min;
  for (int i = min; i <= max; ++i)
  {
    pvtmp->x = *pv1 - pv2->x;
    ++pvtmp;
    ++pv1;
    ++pv2;
  }

  //dvar_vector vtmp=nograd_assign(tmp);

  grad_stack* GRAD_STACK1 = gradient_structure::get_GRAD_STACK1();
  DF_FILE* fp = gradient_structure::get_fp();
  // The derivative list considerations
  save_identifier_string("bbbb");
  fp->save_dvar_vector_position(v2);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("aaaa");
  GRAD_STACK1->set_gradient_stack(cvdv_sub);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void cvdv_sub(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
  verify_identifier_string("bbbb");
  int min = dftmp.indexmin();
  int max = dftmp.indexmax();
  dvector dfv2(min, max);
  double* pdfv2 = dfv2.get_v() + min;
  double* pdftmp = dftmp.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //vtmp.elem(i)=v1.elem(i)-value(v2.elem(i));
    *pdfv2 = -(*pdftmp);
    ++pdfv2;
    ++pdftmp;
  }
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
