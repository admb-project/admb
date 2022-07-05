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

  void DF_cdble_dv_diveq(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::operator/=(const double x)
  {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    gs->RETURN_ARRAYS_INCREMENT();
    save_identifier_string("wctf");
    double xinv = 1.0 / x;
    int min = index_min;
    int max = index_max;
    double_and_int* pva = va + min;
    for (int i = min; i <= max; ++i)
    {
      pva->x *=xinv;
      ++pva;
    }
    fp->save_dvar_vector_position(*this);
    fp->save_double_value(x);
    save_identifier_string("cmtu");
    gs->GRAD_STACK1->set_gradient_stack(DF_cdble_dv_diveq);
    gs->RETURN_ARRAYS_DECREMENT();
    return(*this);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_cdble_dv_diveq(void)
 {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;
    verify_identifier_string("cmtu");
    double x=fp->restore_double_value();
    dvar_vector_position this_pos=fp->restore_dvar_vector_position();
    dvector dfthis=restore_dvar_vector_derivatives(this_pos);
    verify_identifier_string("wctf");
    double xinv=1./x;
    int max = dfthis.indexmax();
    int min = dfthis.indexmin();
    double* pdfthis = dfthis.get_v() + max;
    for (int i = max; i >= min; --i)
    {
      // elem_value(i)=elem_value(i)/x;
      //dfthis(i)*=xinv;
      *pdfthis *= xinv;
      --pdfthis;
    }
    dfthis.save_dvector_derivatives(this_pos);
 }


  void DF_vdble_dv_diveq(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::operator/=(const prevariable& x)
  {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    gs->RETURN_ARRAYS_INCREMENT();
    double xinv = 1.0 / value(x);
    int min = index_min;
    int max = index_max;
    double_and_int* pva = va + min;
    for (int i = min; i <= max; ++i)
    {
      //elem_value(i)=elem_value(i)*xinv;
      pva->x *= xinv;
      ++pva;
    }
    save_identifier_string("wctg");
    fp->save_dvar_vector_value(*this);
    fp->save_dvar_vector_position(*this);
    fp->save_prevariable_value(x);
    fp->save_prevariable_position(x);
    save_identifier_string("cmtu");
    gs->RETURN_ARRAYS_DECREMENT();
    gs->GRAD_STACK1->set_gradient_stack(DF_vdble_dv_diveq);
    return(*this);
  }

/**
 * Description not yet available.
 * \param
 */
 void DF_vdble_dv_diveq(void)
 {
    gradient_structure* gs = gradient_structure::get();
    DF_FILE* fp = gs->fp;

    verify_identifier_string("cmtu");
    prevariable_position x_pos=fp->restore_prevariable_position();
    double dfx=restore_prevariable_derivative(x_pos);
    double x=fp->restore_prevariable_value();
    dvar_vector_position this_pos=fp->restore_dvar_vector_position();
    dvector tmp=restore_dvar_vector_value(this_pos);
    dvector dfthis=restore_dvar_vector_derivatives(this_pos);
    verify_identifier_string("wctg");
    double tmp1=0.0;
    double xinv=1.0/x;
    int max = dfthis.indexmax();
    int min = dfthis.indexmin();
    double* pdfthis = dfthis.get_v() + max;
    double* ptmp = tmp.get_v() + max;
    for (int i = max; i >= min; --i)
    {
      // elem_value(i)=elem_value(i)/x;
      //tmp1+=dfthis(i)*tmp(i);
      tmp1 += *pdfthis * *ptmp;
      --pdfthis;
      --ptmp;
    }
    tmp1*=-xinv;

    pdfthis = dfthis.get_v() + max;
    for (int i = max; i >= min; --i)
    {
      // elem_value(i)=elem_value(i)/x;
      *pdfthis *= xinv;
      --pdfthis;
    }
    dfthis.save_dvector_derivatives(this_pos);
    save_double_derivative(dfx+tmp1,x_pos);
 }
