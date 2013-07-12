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

void DF_dvmfexp(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector mfexp(const dvar_vector& v1)
{
  //dvector cv1=value(v1);
  int mmin=v1.indexmin();
  int mmax=v1.indexmax();
  dvar_vector vtmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    if (v1.elem_value(i)<60.)
    {
      vtmp.elem_value(i)=exp(v1.elem_value(i));
    }
    else
    {
     double x=v1.elem_value(i)-60.;
     vtmp.elem_value(i)=exp(60.)*(1.+2.*x)/(1.+x);
    }
  }

  save_identifier_string("ddt");
  v1.save_dvar_vector_value();
  v1.save_dvar_vector_position();
  vtmp.save_dvar_vector_value();
  vtmp.save_dvar_vector_position();
  save_identifier_string("see");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(DF_dvmfexp);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvmfexp(void)
{
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("see");
  dvar_vector_position tmp_pos=restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector vtmp=restore_dvar_vector_value(tmp_pos);
  dvar_vector_position v1pos=restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddt");
  dvector dfv1(dfvtmp.indexmin(),dfvtmp.indexmax());
  for (int i=dfvtmp.indexmin();i<=dfvtmp.indexmax();i++)
  {
    //vtmp.elem(i)=mfexp(value(v1.elem(i))));
    if (v1.elem(i)<60)
    {
      dfv1(i)=dfvtmp(i)*vtmp.elem(i);
    }
    else
    {
      double b=v1.elem(i)-60.0;
      dfv1(i)=dfvtmp(i)*exp(60.0)*(1./(1.+b*b));
    }
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
