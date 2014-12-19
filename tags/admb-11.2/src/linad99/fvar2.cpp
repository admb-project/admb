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

/**
  Creates an entry in the gradient structure linked list.
  \return Pointer instance of class double_and_int
 */
double_and_int* gradnew()
{
#if !defined(OPT_LIB)
  if (!gradient_structure::instances)
  {
    cerr << "Error -- you are trying to create a dvariable object"
            " when there is " << endl << "no object of type"
            " gradient_structure in scope " << endl;
    ad_exit(1);
  }
#endif
  dlink* tmp = gradient_structure::GRAD_LIST->last_remove();
  if (!tmp)
  {
    tmp = gradient_structure::GRAD_LIST->create();
  }
  //  cout << "In gradnew the address of the double * ptr is "
  //       << _farptr_tolong(tmp) << "\n";
  return (double_and_int*)tmp;
}
/**
 * Description not yet available.
 * \param
 */
void gradfree(dlink* v)
{
  if (gradient_structure::GRAD_LIST)
  {
    if (gradient_structure::instances)
    {
      gradient_structure::GRAD_LIST->append(v);
    }
    else
    {
      delete (double_and_int*)v;
      v = NULL;
    }
  }
}
//prevariable::prevariable(const prevariable& t)
//  {
//     v=t.v;
//     (*v).nc++;
//  }
/**
  Constructor for dvariable object from its base class; deep copy.
  Allocates memory and assigns value of argument to new object.
  \param t constant prevariable object
 */
dvariable::dvariable(const prevariable& t)
{
  v=gradnew();
  //(*v).nc=0;
  v->x=t.v->x;
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(default_evaluation1,&(v->x),&(t.v->x));
}
/**
  Copy constructor for dvariable object; deep copy.
  Allocates memory and assigns value of argument to new object.
  \param t constant devariable object
 */
dvariable::dvariable(const dvariable& t): prevariable()
{
  v=gradnew();
  v->x=t.v->x;
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(default_evaluation1,&(v->x),&(t.v->x));
}
/**
Null constructor.
Creates new dvariable object,
sets value to zero and initializes derivatve information.
 */
dvariable::dvariable()
{
  v=gradnew();
  //(*v).nc=0;
#ifdef SAFE_INITIALIZE
  (*v).x = 0;
  gradient_structure::GRAD_STACK1->set_gradient_stack0(
    default_evaluation0,&((*v).x));
#endif
}
/**
   Specialized constructor that does not create unnecessary entries
   in the gradient structure; see function \ref nograd_assign.
 */
dvariable::dvariable(kkludge_object)
{
  v = gradnew();
  //(*v).nc=0;
}
/**
  Destructor; frees memory on gradient stack.
 */
dvariable::~dvariable()
{
  gradfree((dlink*)v);
}
/**
   Creates dvariable instance from a double constant.
   Creates new dvariable object,
   Sets Value to the argument and initializes derivative information.
   \param t constant double passed by value.
 */
dvariable::dvariable(const double t)
{
  v = gradnew();
  v->x = t;
  //(*v).nc=0;
  gradient_structure::GRAD_STACK1->set_gradient_stack0(default_evaluation0,
    &(v->x));
}
/**
   Creates dvariable instance from a int constant.
   Creates new dvariable object,
   Sets value to the argument and initializes derivatve information.
   \param t constant integer passed by reference.
 */
dvariable::dvariable(const int& t)
{
  v = gradnew();
  v->x = t;
  //(*v).nc=0;
  gradient_structure::GRAD_STACK1->set_gradient_stack0(default_evaluation0,
    &(v->x) );
}
