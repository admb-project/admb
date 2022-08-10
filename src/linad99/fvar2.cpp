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
#if !defined(OPT_LIB)
#include <cassert>
#endif

/**
Creates an entry in the gradient structure linked list.
\return Pointer instance of class double_and_int
*/
double_and_int* gradnew()
{
#if !defined(OPT_LIB)
  if (!gradient_structure::_instance)
  {
    cerr << "Error -- you are trying to create a dvariable object"
            " when there is " << endl << "no object of type"
            " gradient_structure in scope " << endl;
    ad_exit(1);
  }
#endif
  return gradient_structure::_instance->GRAD_LIST->gradnew();
}

double_and_int* dlist::gradnew()
{
  dlink* tmp = last_remove();
  if (!tmp)
  {
    tmp = create();
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
  if (gradient_structure::_instance)
  {
    gradient_structure::_instance->GRAD_LIST->append(v);
  }
  v = NULL;
}
//prevariable::prevariable(const prevariable& t)
//  {
//     v=t.v;
//     (*v).nc++;
//  }

