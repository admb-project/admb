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
// file: fvar_ops.cpp
// operators involving prevariables


#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdio.h>
#include <math.h>

/**
 * Description not yet available.
 * \param
 */
prevariable& operator+(const double x, const prevariable& v2)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  RETURN_PTR->v->x = x + (v2.v->x);
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1,
    &(RETURN_PTR->v->x),&(v2.v->x));

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator+(const prevariable& v1, const double x)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  RETURN_PTR->v->x=v1.v->x+ x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1,
    &(RETURN_PTR->v->x), &(v1.v->x));

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator-(const prevariable& v1, const prevariable& v2)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  RETURN_PTR->v->x=v1.v->x - v2.v->x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation4m,
    &(RETURN_PTR->v->x),&(v1.v->x),&(v2.v->x));

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator-(const prevariable& v1, const double x)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  RETURN_PTR->v->x=v1.v->x - x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1,
    &(RETURN_PTR->v->x), &(v1.v->x));

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator-(const double x, const prevariable& v2)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  RETURN_PTR->v->x = x - v2.v->x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1m,
    &(RETURN_PTR->v->x), &(v2.v->x));

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator-(const prevariable& v1)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  RETURN_PTR->v->x = -(v1.v->x);
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1m,
    &(RETURN_PTR->v->x),&(v1.v->x));

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator/(const prevariable& v1, const prevariable& v2)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  double x = 1 / v2.v->x;
  double y = v1.v->x * x;
  RETURN_PTR->v->x = y;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3,
     &(RETURN_PTR->v->x),&(v1.v->x),x,&(v2.v->x),-y*x);

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator/(const double u, const prevariable& v2)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  double x = 1 / v2.v->x;
  double y = u * x;
  RETURN_PTR->v->x = y;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
    &(RETURN_PTR->v->x), &(v2.v->x),-y*x);

  return *RETURN_PTR;
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator/(const prevariable& v1, const double u)
{
  dvariable* RETURN_PTR = gradient_structure::next_RETURN_PTR();

  double x = 1 / u;
  double y = v1.v->x * x;

  RETURN_PTR->v->x = y;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
    &(RETURN_PTR->v->x), &(v1.v->x),x);

  return *RETURN_PTR;
}
