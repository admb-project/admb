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

//extern prevariable * FRETURN;
//extern int RETURN_INDEX;
//extern dlist * GRAD_LIST;          //js
//extern grad_stack  * GRAD_STACK1;

/**
 * Description not yet available.
 * \param
 */
    prevariable& exp(_CONST prevariable& v1)
    {
      double tmp;
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      tmp=::exp(v1.v->x);
      gradient_structure::RETURN_PTR->v->x=tmp;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                    &(v1.v->x),tmp );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& atan(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x= ::atan(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                    &(v1.v->x),1./(1.+v1.v->x * v1.v->x) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& ldexp(_CONST prevariable& v1, BOR_CONST int& exponent)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::ldexp(v1.v->x, exponent);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                    &(v1.v->x),pow(2.0,exponent) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& sqrt(_CONST prevariable& v1)
    {
      double tmp=v1.v->x;
      if (tmp==0.0) 
      {
        cerr << "Attempting to take the derivative of sqrt(prevariable x)"
         " at x=0\n";
        ad_exit(1);
      }
      tmp=::sqrt(tmp);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=tmp;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                    &(v1.v->x),1./(2.*tmp) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& sqr(_CONST prevariable& v1)
    {
      double tmp=v1.v->x;
      if (tmp==0.0) 
      {
        cerr << "Attempting to take the derivative of sqrt(prevariable x)"
         " at x=0\n";
        ad_exit(1);
      }
      tmp=::sqrt(tmp);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=tmp;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                    &(v1.v->x),1./(2.*tmp) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& tan(_CONST prevariable& v1)
    {
      double t = ::tan(v1.v->x);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x= t;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                          &(v1.v->x), 1+t*t);
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& tanh(_CONST prevariable& v1)
    {
      double t = ::tanh(v1.v->x);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x= t;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                          &(v1.v->x), 1-t*t);
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& acos(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::acos(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                          &(v1.v->x),-1./::sqrt(1.- v1.v->x * v1.v->x));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& asin(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::asin(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                          &(v1.v->x),1./::sqrt(1.- v1.v->x * v1.v->x));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& pow(_CONST prevariable& v1,_CONST prevariable& v2)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      double x,y;
      x=::pow(v1.v->x,(v2.v->x)-1);
      y=x* v1.v->x;
      gradient_structure::RETURN_PTR->v->x=y;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                            &(v1.v->x), v2.v->x * x  ,&(v2.v->x), 
                                     y * ::log(v1.v->x) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& pow( CGNU_DOUBLE u,_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      double y;
      y=::pow(u,(v1.v->x));

      gradient_structure::RETURN_PTR->v->x=y;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                       &(v1.v->x), y * ::log(u) );
 
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& sinh(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::sinh(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                    &(v1.v->x),::cosh(v1.v->x) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& cosh(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::cosh(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                    &(v1.v->x),::sinh(v1.v->x) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& atan2(_CONST prevariable& v1,_CONST prevariable& v2)
    {
  dvariable x = v1/v2;
      return atan(x);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& atan2(_CONST prevariable& v1, CGNU_DOUBLE v2)
    {
  dvariable x = v1/v2;
      return atan(x);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& atan2( CGNU_DOUBLE v1,_CONST prevariable& v2)
    {
  dvariable x = v1/v2;
      return atan(x);
    }
