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
#ifndef OPT_LIB
  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
      "prevariable operator-(const dvector& v1, const dvar_vector& v2)" << endl;
    ad_exit(1);
  }
#endif
  //dvector cv1=value(v1);
  //dvector cv2=value(v2);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=v1.elem(i)-v2.elem_value(i);
  }

  //dvar_vector vtmp=nograd_assign(tmp);

  DF_FILE* fp = gradient_structure::fp;

  // The derivative list considerations
#ifndef OPT_LIB
  save_identifier_string("bbbb");
#endif
  fp->save_dvar_vector_position(v2);
  fp->save_dvar_vector_position(vtmp);
#ifndef OPT_LIB
  save_identifier_string("aaaa");
#endif
  gradient_structure::_instance->GRAD_STACK1->set_gradient_stack(cvdv_sub);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void cvdv_sub(void)
{
  DF_FILE* fp = gradient_structure::fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
#ifndef OPT_LIB
  verify_identifier_string("aaaa");
#endif
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v2pos=fp->restore_dvar_vector_position();
#ifndef OPT_LIB
  verify_identifier_string("bbbb");
#endif
  dvector dfv2(dftmp.indexmin(),dftmp.indexmax());
  for (int i=dftmp.indexmin();i<=dftmp.indexmax();i++)
  {
    //vtmp.elem(i)=v1.elem(i)-value(v2.elem(i));
    dfv2(i)=-dftmp.elem(i);
  }
  dfv2.save_dvector_derivatives(v2pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
