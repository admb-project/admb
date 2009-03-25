/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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


#include <stdio.h>
#ifndef __SUN__
#endif
#include <math.h>

void gradfree(dlink *);

double_and_int * gradnew()
{
  #if defined (SAFE_ARRAYS)
    if (!gradient_structure::instances)
    {
      cerr << "Error -- you are trying to create a dvariable object"
              " when there is " << endl << "no object of type"
              " gradient_structure in scope " << endl;
      ad_exit(1);
    }
  #endif
  {
    dlink * tmp;
    tmp = gradient_structure::GRAD_LIST->last_remove();
    if (!tmp)
    {
      tmp=gradient_structure::GRAD_LIST->create();
    }

    //  cout << "In gradnew the address of the double * ptr is "
    //       << _farptr_tolong(tmp) << "\n"; 

    return (double_and_int *) tmp;
  }
}


  void gradfree(dlink * v)
  {
    if (gradient_structure::instances)
    { 
      gradient_structure::GRAD_LIST->append(v);
    }
    else
    {
      delete (double_and_int *) v;
      v=NULL;
    }
  }

//  prevariable::prevariable(_CONST prevariable& t)
//  {
//     v=t.v;
//     (*v).nc++;
//  }

    dvariable::dvariable(_CONST prevariable& t)
    {
      v=gradnew();
      //(*v).nc=0;
      v->x=t.v->x;
      gradient_structure::GRAD_STACK1->
	 set_gradient_stack(default_evaluation1,&(v->x),&(t.v->x));
    }


    dvariable::dvariable(_CONST dvariable& t)
    {
      v=gradnew();
      v->x=t.v->x;
      gradient_structure::GRAD_STACK1->
	 set_gradient_stack(default_evaluation1,&(v->x),&(t.v->x));
    }


    dvariable::dvariable()
    {
      v=gradnew();
      //(*v).nc=0;
      #ifdef SAFE_INITIALIZE
	(*v).x=0;
	gradient_structure::GRAD_STACK1->set_gradient_stack0(default_evaluation0,&((*v).x));
      #endif
    }


    dvariable::dvariable(kkludge_object)
    {
      v=gradnew();
      //(*v).nc=0;
    }


   dvariable::~dvariable()
   {
     gradfree( (dlink *) v );
   }



  dvariable::dvariable( CGNU_DOUBLE t)
  {
    v=gradnew();
    v->x=t;
    //(*v).nc=0;
    gradient_structure::GRAD_STACK1->set_gradient_stack0(default_evaluation0, &(v->x) );
  }

  dvariable::dvariable(BOR_CONST int& t)
  {
    v=gradnew();
    v->x=t;
    //(*v).nc=0;
    gradient_structure::GRAD_STACK1->set_gradient_stack0(default_evaluation0, &(v->x) );
  }

