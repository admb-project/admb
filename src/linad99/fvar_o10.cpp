/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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
    prevariable& prevariable::operator=( CGNU_DOUBLE t) _CONST
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return((prevariable&)(*this));
    }

    prevariable& prevariable::operator=(_CONST prevariable& t) _CONST
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return((prevariable&)(*this));
    }
#  endif
#endif

    prevariable& prevariable::operator=(_CONST prevariable& t)
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return(*this);
    }

    dvariable& dvariable::operator=(_CONST prevariable& t)
    {
      (*v).x=(*t.v).x;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack1(default_evaluation1,&(v->x),&(t.v->x));
      return(*this);
    }

    dvariable& dvariable::operator=( CGNU_DOUBLE t)
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return(*this);
    }

    prevariable& prevariable::operator=( CGNU_DOUBLE t)
    {
      (*v).x=t;
      gradient_structure::GRAD_STACK1->
        set_gradient_stack0(df_eq_pvdoub,&(v->x));
      return(*this);
    }


  void df_eq_pvdoub(void)
  {
    * gradient_structure::GRAD_STACK1->ptr->dep_addr=0.;
  }

