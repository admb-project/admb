/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 \file
  More overloads of math library functions for variable arguments.
 */
#include "fvar.hpp"

#include <stdio.h>
#include <cmath>

void gradfree(dlink *);

//extern prevariable * FRETURN;
//extern int RETURN_INDEX;
//extern dlist * GRAD_LIST;          //js
//extern grad_stack  * GRAD_STACK1;

/**
Compute exponential variable

\param v1 is the input value.
\return exponential variable of v1.
*/
prevariable& exp(const prevariable& v1)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
    gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

  double tmp = ::exp(v1.v->x);

#ifndef OPT_LIB
  ///\todo Must remove macros below once support for MSVC++11 and Solaris Studio 12.3 are removed.
  #if !defined(__SUNPRO_CC) && !(defined(_MSC_VER) && (_MSC_VER <= 1700))
  if (!std::isfinite(tmp))
  {
    cerr << "Error: Result of \"exp(prevariable(" << value(v1) << ")) = " << tmp << "\" is not finite.\n";
    ad_exit(1);
  }
  #endif
#endif

  gradient_structure::RETURN_PTR->v->x=tmp;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
    &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),tmp);

  return *gradient_structure::RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& atan(const prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x= ::atan(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x),
        &(v1.v->x),1./(1.+v1.v->x * v1.v->x) );
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& ldexp(const prevariable& v1, const int& exponent)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::ldexp(v1.v->x, exponent);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),pow(2.0,exponent));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& sqrt(const prevariable& v1)
    {
      double tmp=v1.v->x;
      if (tmp==0.0)
      {
        cerr << "Attempting to take the derivative of sqrt(prevariable x)"
         " at x=0\n";
        ad_exit(1);
      }
      tmp=::sqrt(tmp);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=tmp;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),1./(2.*tmp));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& sqr(const prevariable& v1)
    {
      double tmp=v1.v->x;
      if (tmp==0.0)
      {
        cerr << "Attempting to take the derivative of sqrt(prevariable x)"
         " at x=0\n";
        ad_exit(1);
      }
      tmp=::sqrt(tmp);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=tmp;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),1./(2.*tmp));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& tan(const prevariable& v1)
    {
      double t = ::tan(v1.v->x);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x= t;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x), 1+t*t);
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& tanh(const prevariable& v1)
    {
      double t = ::tanh(v1.v->x);
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x= t;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x), 1-t*t);
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& acos(const prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::acos(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x),
        &(v1.v->x),-1./::sqrt(1.- v1.v->x * v1.v->x));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& asin(const prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::asin(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x),
        &(v1.v->x),1./::sqrt(1.- v1.v->x * v1.v->x));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& pow(const prevariable& v1, const prevariable& v2)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      double x=::pow(v1.v->x,(v2.v->x)-1);
      double y=x* v1.v->x;
      gradient_structure::RETURN_PTR->v->x=y;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x),
        &(v1.v->x), v2.v->x * x  ,&(v2.v->x),
        y * ::log(v1.v->x));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& pow(const double u, const prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      double y=::pow(u,(v1.v->x));

      gradient_structure::RETURN_PTR->v->x=y;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x), y * ::log(u));

      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& sinh(const prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::sinh(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),::cosh(v1.v->x));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& cosh(const prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
        gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::cosh(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),::sinh(v1.v->x));
      return(*gradient_structure::RETURN_PTR);
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& atan2(const prevariable& v1, const prevariable& v2)
{
  if (value(v1) == 0 && value(v2) == 0)
  {
    cerr << "Error: The ADMB function \"atan2(y, x)\" is undefined "
    "for y and x equal zero.\n";
    ad_exit(1);
  }
  if (value(v1) == 0 && value(v2) > 0)
  {
    return atan(v1/v2);
  }
  dvariable x = (sqrt(v2 * v2 + v1 * v1) - v2)/v1;
  return atan(x) * 2.0;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& atan2(const prevariable& v1, const double v2)
{
  if (value(v1) == 0 && v2 == 0)
  {
    cerr << "Error: The ADMB function \"atan2(y, x)\" is undefined "
    "for y and x equal zero.\n";
    ad_exit(1);
  }
  if (value(v1) == 0 && v2 > 0)
  {
    return atan(v1/v2);
  }
  dvariable x = (sqrt(v2 * v2 + v1 * v1) - v2)/v1;
  return atan(x) * 2.0;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& atan2(const double v1, const prevariable& v2)
{
  if (v1 == 0 && value(v2) == 0)
  {
    cerr << "Error: The ADMB function \"atan2(y, x)\" is undefined "
    "for y and x equal zero.\n";
    ad_exit(1);
  }
  if (v1 == 0 && value(v2) > 0)
  {
    return atan(v1/v2);
  }
  dvariable x = (sqrt(v2 * v2 + v1 * v1) - v2)/v1;
  return atan(x) * 2.0;
}
