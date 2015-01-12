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


void gradfree(dlink *);

 void prevariable::operator +=( CGNU_DOUBLE uu)
 {
   (*v).x+=uu;
 }

 void prevariable::operator -=( CGNU_DOUBLE uu)
 {
   (*v).x-=uu;
 }


prevariable& operator +(_CONST prevariable& v1,_CONST prevariable& v2)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

 gradient_structure::RETURN_PTR->v->x =(*v1.v).x+ (*v2.v).x;
 gradient_structure::GRAD_STACK1->set_gradient_stack4(default_evaluation4, 
    &(gradient_structure::RETURN_PTR->v->x),&((*v1.v).x),
	     &((*v2.v).x));
  return(*gradient_structure::RETURN_PTR);
}

prevariable& operator *(_CONST prevariable& v1,_CONST prevariable& v2)
{
  if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN) gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
  gradient_structure::RETURN_PTR->v->x= (*v1.v).x * (*v2.v).x;
  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation3, &(gradient_structure::RETURN_PTR->v->x),
	       &((*v1.v).x),(*v2.v).x,&((*v2.v).x),(*v1.v).x );
  return(*gradient_structure::RETURN_PTR);
 }

    int prevariable::operator ==(_CONST prevariable& v1) _CONST
    {
      return(v->x==value(v1));
    }

    int prevariable::operator <=(_CONST prevariable& v1) _CONST
    {
      return(v->x<=value(v1));
    }

    int prevariable::operator <(_CONST prevariable& v1) _CONST
    {
      return(v->x<value(v1));
    }

    int prevariable::operator >(_CONST prevariable& v1) _CONST
    {
      return(v->x>value(v1));
    }

    int prevariable::operator >=(_CONST prevariable& v1) _CONST
    {
      return(v->x >=value(v1));
    }


    int prevariable::operator !=(_CONST prevariable& v1) _CONST
    {
      return(v->x!=value(v1));
    }

