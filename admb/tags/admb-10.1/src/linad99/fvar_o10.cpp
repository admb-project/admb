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

  void df_eq_pvdoub(void);
  void df_eq_pvpv(void);

#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
/**
 * Description not yet available.
 * \param
 */
    prevariable& prevariable::operator=( CGNU_DOUBLE t) _CONST
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return((prevariable&)(*this));
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& prevariable::operator=(_CONST prevariable& t) _CONST
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return((prevariable&)(*this));
    }
#  endif
#endif

/**
 * Description not yet available.
 * \param
 */
    prevariable& prevariable::operator=(_CONST prevariable& t)
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return(*this);
    }

/**
 * Description not yet available.
 * \param
 */
    dvariable& dvariable::operator=(_CONST prevariable& t)
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return(*this);
    }

/**
 * Description not yet available.
 * \param
 */
    dvariable& dvariable::operator=( CGNU_DOUBLE t)
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return(*this);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable& prevariable::operator=( CGNU_DOUBLE t)
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return(*this);
    }

/**
 * Description not yet available.
 * \param
 */
  void df_eq_pvdoub(void)
  {
    * gradient_structure::GRAD_STACK1->ptr->dep_addr=0.;
  }

