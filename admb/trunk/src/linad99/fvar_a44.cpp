/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"


void DF_dvsquare(void);

dvar_vector square(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);

  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    double x=v1.elem_value(i);
    vtmp.elem_value(i)=x*x;
  }

  save_identifier_string("sddd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("eee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvsquare);
  return vtmp;
}

void DF_dvsquare(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("eee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("sddd");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=sin(value(v1.elem(i))));
    double x=v1.elem(i);
    dfv1(i)=dfvtmp(i)*2*x;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}


void DF_dvcube(void);

dvar_vector cube(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);

  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    double x=v1.elem_value(i);
    vtmp.elem_value(i)=x*x*x;
  }

  save_identifier_string("sssd");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("tee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvcube);
  return vtmp;
}

void DF_dvcube(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("tee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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

dvar_vector fourth(_CONST dvar_vector& v1)
{
  //dvector cv1=value(v1);

  dvar_vector vtmp(v1.indexmin(),v1.indexmax());
  for (int i=v1.indexmin();i<=v1.indexmax();i++)
  {
    double x=v1.elem_value(i);
    double x2=x*x;
    vtmp.elem_value(i)=x2*x2;
  }

  save_identifier_string("ssf");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_position();
  save_identifier_string("gee");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvfourth);
  return vtmp;
}

void DF_dvfourth(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("gee");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
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


