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
// file fvar_fn.cpp
// math.h functions involving prevariables
#include "fvar.hpp"

#include <stdio.h>
#include <math.h>

void gradfree(dlink *);

/**
 * Description not yet available.
 * \param
 */
dvariable avg( const prevariable& x,const prevariable& y)
{
  return 0.5*(x+y);
}

/**
 * Description not yet available.
 * \param
 */
  prevariable& daves_kludge1(const prevariable& v1)
  {
    if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
      gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

    double cx=value(v1);
    double fval;
    double tmp;
    double dftmp;
    double tmp2;
    double tmp3;
    int i=cx;
    if (cx-i <= 0.5)
    {
      tmp=cx-i;
      tmp2=tmp*tmp;
      tmp3=tmp*tmp*tmp;
      fval= 24*tmp3-64*tmp3*tmp+48*tmp3*tmp2;
    }
    else
    {
      tmp=1-(cx-i);
      tmp2=tmp*tmp;
      tmp3=tmp*tmp*tmp;
      fval=1.-24*tmp3+64*tmp3*tmp-48*tmp3*tmp2;
    } 
  
    if (cx-i <= 0.5)
    {
      //fval= 24*tmp3-64*tmp3*tmp+48*tmp3*tmp2;
      double dftmp3=24-64*tmp+48*tmp2;
      dftmp=-64*tmp3;
      double dftmp2=48*tmp3;
      //double tmp3=tmp*tmp*tmp;
      dftmp+=3.*tmp2*dftmp3;
      //double tmp2=tmp*tmp;
      dftmp+=2.*tmp*dftmp2;
    }
    else
    {
      //fval=1.-24*tmp3+64*tmp3*tmp-48*tmp3*tmp2;
      double dftmp3=-24+64*tmp-48*tmp2;
      dftmp=+64*tmp3;
      double dftmp2=-48*tmp3;
      //double tmp3=tmp*tmp*tmp;
      dftmp+=3.*tmp2*dftmp3;
      //double tmp2=tmp*tmp;
      dftmp+=2.*tmp*dftmp2;
      //double tmp=1-(cx-i);
      dftmp=-dftmp;
    } 

    gradient_structure::RETURN_PTR->v->x=fval;
    gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
      &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),dftmp);
   return(*gradient_structure::RETURN_PTR);
 }
