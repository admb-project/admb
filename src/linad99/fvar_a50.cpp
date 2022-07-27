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

  double_and_int* pvtmpi = vtmp.va + mmin;
  double_and_int* pv1i = v1.va + mmin;

  for (int i=mmin;i<=mmax;i++)
  {
    double v1i = pv1i->x;
    if (v1i < 60.0)
    {
      pvtmpi->x = exp(v1i);
    }
    else
    {
      double exp60 = exp(60.0);
      double x = v1i - 60.0;
      pvtmpi->x = exp60 * (1.0 + 2.0 * x)/(1.0 + x);
    }

    ++pvtmpi;
    ++pv1i;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  save_identifier_string("ddt");
  fp->save_dvar_vector_value(v1);
  fp->save_dvar_vector_position(v1);
  fp->save_dvar_vector_value(vtmp);
  fp->save_dvar_vector_position(vtmp);
  save_identifier_string("see");
  gs->GRAD_STACK1->set_gradient_stack(DF_dvmfexp);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void DF_dvmfexp(void)
{
  DF_FILE* fp = gradient_structure::fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("see");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dfvtmp=restore_dvar_vector_derivatives(tmp_pos);
  dvector vtmp=restore_dvar_vector_value(tmp_pos);
  dvar_vector_position v1pos=fp->restore_dvar_vector_position();
  dvector v1=restore_dvar_vector_value(v1pos);
  verify_identifier_string("ddt");
  int min = dfvtmp.indexmin();
  int max = dfvtmp.indexmax();
  dvector dfv1(min, max);

  double* pdfv1i = dfv1.get_v() + min;
  double* pdfvtmpi = dfvtmp.get_v() + min;
  double* pvtmpi = vtmp.get_v() + min;
  double* pv1i = v1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //vtmp.elem(i)=mfexp(value(v1.elem(i))));
    if (*pv1i < 60.0)
    {
      *pdfv1i = *pdfvtmpi * *pvtmpi;
    }
    else
    {
      double exp60 = exp(60.0);
      double b = *pv1i - 60.0;
      *pdfv1i = *pdfvtmpi * exp60 * std::pow(1.0 + b, -2.0);
    }

    ++pdfv1i;
    ++pdfvtmpi;
    ++pvtmpi;
    ++pv1i;
  }
  dfv1.save_dvector_derivatives(v1pos);
  //ierr=fsetpos(gradient_structure::get_fp(),&filepos);
}
