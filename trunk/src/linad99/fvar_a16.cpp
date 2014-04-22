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
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

void dvcv_dot(void);

/**
 * Description not yet available.
 * \param
 */
dvariable operator*(const dvar_vector& v2, const dvector& cv1)
{
  if (cv1.indexmin()!=v2.indexmin()||cv1.indexmax()!=v2.indexmax())
  {
    cerr << "Incompatible bounds in "
    "prevariable operator*(const dvar_vector& v1, const dvar_vector& v2)"
    << endl;
    ad_exit(1);
  }
  //dvector cv1;
  //dvector cv2=value(v2);
  double tmp=0;

#ifdef OPT_LIB
    int mmin=cv1.indexmin();
    int mmax=cv1.indexmax();
    const double * pt1=&cv1.elem(mmin);
    const double * pt1m=&cv1.elem(mmax);
    const double * pt2=&v2.elem_value(mmin);
    do
    {
      tmp+= *pt1++ * *pt2++;
    }
    while (pt1<=pt1m);
#else
  #ifndef USE_ASSEMBLER
    int mmin=cv1.indexmin();
    int mmax=cv1.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      tmp+=cv1.elem(i)*v2.elem_value(i);
    }
  #else
    int min=cv1.indexmin();
    int n=cv1.indexmax()-min+1;
    dp_dotproduct(&tmp,&(cv1.elem(min)),&(v2.elem_value(min)),n);
  #endif
#endif

  dvariable vtmp=nograd_assign(tmp);

  // The derivative list considerations
  save_identifier_string("yyyy");
  cv1.save_dvector_value();
  cv1.save_dvector_position();
  v2.save_dvar_vector_position();
  vtmp.save_prevariable_position();
  save_identifier_string("uuuu");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(dvcv_dot);
  return vtmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvcv_dot(void)
{
  verify_identifier_string("uuuu");
  double dftmp=restore_prevariable_derivative();
  dvar_vector_position v2pos=restore_dvar_vector_position();
  dvector_position dpos=restore_dvector_position();
  dvector cv1=restore_dvector_value(dpos);
  verify_identifier_string("yyyy");

  dvector dfv2(cv1.indexmin(),cv1.indexmax());

#ifdef OPT_LIB
  double * pc1=&cv1.elem(cv1.indexmin());
  double * pc1m=&cv1(cv1.indexmax());
  double * pdf=&dfv2.elem(cv1.indexmin());
  do
  {
    *pdf++=dftmp* *pc1++;
  }
  while (pc1 <=pc1m);
#else
  for (int i=cv1.indexmin();i<=cv1.indexmax();i++)
  {
    //tmp+=cv1(i)*cv2(i);
    dfv2.elem(i)=dftmp*cv1.elem(i);
  }
#endif
  dfv2.save_dvector_derivatives(v2pos);
}
