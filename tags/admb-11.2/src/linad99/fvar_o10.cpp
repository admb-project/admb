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

  void df_eq_pvdoub(void);
  void df_eq_pvpv(void);

#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540)
/**
 * Description not yet available.
 * \param
 */
prevariable& prevariable::operator=(const double t) const
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
prevariable& prevariable::operator=(const prevariable& t) const
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return((prevariable&)(*this));
    }
#  endif
#endif

/**
  Assigns a value to a prevariable object.
  \param t constant reference to an object of type prevariable.
  \return prevariable reference
 */
prevariable& prevariable::operator=(const prevariable& t)
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return(*this);
    }

/**
  Assigns a value to a dvariable object.
  \param t constant reference to an object of type prevariable.
  \return dvariable reference
 */
dvariable& dvariable::operator=(const prevariable& t)
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return(*this);
    }

/**
  Assigns a value to a dvariable object.
  \param t constant object of type double.
  \return prevariable reference
 */
dvariable& dvariable::operator=(const double t)
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return(*this);
    }

/**
  Assigns a value to a prevariable object.
  \param t constant object of type double.
  \return prevariable reference
 */
prevariable& prevariable::operator=(const double t)
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return(*this);
    }

/**
  ?
 */
  void df_eq_pvdoub(void)
  {
    * gradient_structure::GRAD_STACK1->ptr->dep_addr=0.;
  }

