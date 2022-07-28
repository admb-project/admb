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

void dv_pluseq(void);

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::operator+=(const dvar_vector& v1)
{
  int min = v1.indexmin();
  int max = v1.indexmax();

#ifndef OPT_LIB
  if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
  {
    cerr << " Incompatible array bounds in dvector& operator+=(const dvar_vector&)\n";
    ad_exit(21);
  }
#endif

  double_and_int* pvai = va + min;
  double_and_int* pv1i = v1.va + min;
  for (int i = min; i <= max; ++i)
  {
    pvai->x += pv1i->x;

    ++pvai;
    ++pv1i;
  }

  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  //save_identifier_string("uuvv");
  fp->save_dvar_vector_position(*this);  // for this->
  fp->save_dvar_vector_position(v1);
  //save_identifier_string("wwxx");
  gs->GRAD_STACK1->set_gradient_stack(dv_pluseq);
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
void dv_pluseq(void)
{
  DF_FILE* fp = gradient_structure::get_fp();

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  //verify_identifier_string("wwxx");
  dvar_vector_position v1_pos=fp->restore_dvar_vector_position();
  dvar_vector_position this_pos=fp->restore_dvar_vector_position();
  //verify_identifier_string("uuvv");
  dvector dfthis=restore_dvar_vector_der_nozero(this_pos);
  dfthis.save_dvector_derivatives(v1_pos);
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::operator+=(const dvector& v1)
{
  int min = v1.indexmin();
  int max = v1.indexmax();
  if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
  {
    cerr << " Incompatible array bounds in dvector& operator+=(const dvar_vector&)\n";
    ad_exit(21);
  }
  double* pv1i = v1.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    elem_value(i) += *pv1i;

    ++pv1i;
  }
  return *this;
}
