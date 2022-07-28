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

void DF_dvsquare(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector square(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  int min = v1.indexmin();
  int max = v1.indexmax();

  dvar_vector vtmp(min, max);

  double_and_int* pvtmp = vtmp.va + min;
  double_and_int* pv1 = v1.va + min;
  for (int i = min; i <= max; ++i)
  {
    //double x = v1.elem_value(i);
    double x = pv1->x;
    //vtmp.elem_value(i) = x * x;
    pvtmp->x = x * x;

    ++pv1;
    ++pvtmp;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("sddd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("eee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvsquare);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvsquare(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("sddd");

  int min = dfvtmp.indexmin();
  int max = dfvtmp.indexmax();
  dvector dfv1(min, max);

  double* pv1 = v1.get_v() + min;
  double* pdfv1 = dfv1.get_v() + min;
  double* pdfvtmp = dfvtmp.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    //double x=v1.elem(i);
    double x = *pv1;
    //dfv1(i)=dfvtmp(i)*2*x;
    *pdfv1 = *pdfvtmp * 2.0 * x;
    ++pv1;
    ++pdfvtmp;
    ++pdfv1;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}


void DF_dvcube(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector cube(const dvar_vector& v1)
{
  //dvector cv1=value(v1);

  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    double x=v1.elem_value(i);
    vtmp.elem_value(i)=x*x*x;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("sssd");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("tee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvcube);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvcube(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("tee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("sssd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    double x=v1.elem(i);
    dfv1(i)=dfvtmp(i)*3*x*x;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}

void DF_dvfourth(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector fourth(const dvar_vector& v1)
{
  //dvector cv1=value(v1);

  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    double x=v1.elem_value(i);
    double x2=x*x;
    vtmp.elem_value(i)=x2*x2;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  save_identifier_string("ssf");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("gee");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvfourth);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvfourth(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("gee");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ssf");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    double x=v1.elem(i);
    dfv1(i)=dfvtmp(i)*4*x*x*x;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
