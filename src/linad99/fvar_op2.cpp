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


void gradfree(dlink *);

//extern prevariable * FRETURN;
//extern int RETURN_INDEX;
//extern dlist * GRAD_LIST; //js
//extern grad_stack  * gradient_structure::GRAD_STACK1; //js

/**
 * Description not yet available.
 * \param
 */
prevariable& operator +( CGNU_DOUBLE x,_CONST prevariable& v2)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

 gradient_structure::RETURN_PTR->v->x = x + (v2.v->x);
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1,&(gradient_structure::RETURN_PTR->v->x),&(v2.v->x));
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator +(_CONST prevariable& v1, CGNU_DOUBLE x)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

  gradient_structure::RETURN_PTR->v->x=v1.v->x+ x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1,&(gradient_structure::RETURN_PTR->v->x),&(v1.v->x));
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator -(_CONST prevariable& v1,_CONST prevariable& v2)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x=v1.v->x - v2.v->x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation4m,
    &(gradient_structure::RETURN_PTR->v->x),&(v1.v->x),&(v2.v->x));
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator -(_CONST prevariable& v1, CGNU_DOUBLE x)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x=v1.v->x - x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1,&(gradient_structure::RETURN_PTR->v->x),
                                     &(v1.v->x));
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator -( CGNU_DOUBLE x,_CONST prevariable& v2)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x = x - v2.v->x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1m,&(gradient_structure::RETURN_PTR->v->x), 
                                           &(v2.v->x));
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator -(_CONST prevariable& v1)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x = -(v1.v->x);
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation1m,
    &(gradient_structure::RETURN_PTR->v->x),&(v1.v->x));
  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator /(_CONST prevariable& v1,_CONST prevariable& v2)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  double x,y;
  x = 1 / v2.v->x;
  y = v1.v->x * x;
  gradient_structure::RETURN_PTR->v->x = y;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3,
     &(gradient_structure::RETURN_PTR->v->x),&(v1.v->x),x,&(v2.v->x),-y*x);

  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator /( CGNU_DOUBLE u,_CONST prevariable& v2)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  double x,y;

  x = 1 / v2.v->x;

  y = u * x;

  gradient_structure::RETURN_PTR->v->x = y;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
				      &(v2.v->x),-y*x);

  return(*gradient_structure::RETURN_PTR);
}

/**
 * Description not yet available.
 * \param
 */
prevariable& operator /(_CONST prevariable& v1, CGNU_DOUBLE u)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  double x,y;

  x = 1 / u;

  y = v1.v->x * x;

  gradient_structure::RETURN_PTR->v->x = y;

  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
                                           &(v1.v->x),x);

  return(*gradient_structure::RETURN_PTR);
}
