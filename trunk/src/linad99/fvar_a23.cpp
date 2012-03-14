/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
dvar_vector operator - (_CONST dvar_vector& v1,_CONST dvector& v2)
{
  if (v1.indexmin()!=v2.indexmin()||v1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
      "prevariable operator - (_CONST dvar_vector& v1,_CONST dvector& v2)" << endl;
    ad_exit(1);
  }
  //dvector cv1=value(v1);
  //dvector cv2=value(v2);
  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    vtmp.elem_value(i)=v1.elem_value(i)-v2.elem(i);
  }

  //dvar_vector vtmp=nograd_assign(tmp);

  // The derivative list considerations
  save_identifier_string("bbbb");
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("aaaa");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(dvcv_sub);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvcv_sub(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("aaaa");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  verify_identifier_string("bbbb");
  dvector dfv1(dftmp.indexmin(),dftmp.indexmax());
  for (int i=dftmp.indexmin();i<=dftmp.indexmax();i++)
  {
    //vtmp.elem(i)=value(v1.elem(i))+v2.elem(i);
    dfv1.elem(i)=dftmp.elem(i);
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
