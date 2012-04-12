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
#include "fvar.hpp"
#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
   #include <alloc.h>
#endif

#include <stdlib.h>

/**
 * Description not yet available.
 * \param
 */
 dvar_vector& dvar_vector::operator = (_CONST dvector& t)
 {
   if (indexmin() != t.indexmin() || indexmax() != t.indexmax())
   {
     cerr << " Incompatible bounds in dvar_vector& dvar_vector::operator = (_CONST dvector& t)\n";
     ad_exit(21);
   }

   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     va[i].x=t[i];
   }
   save_identifier_string("b");
   this->save_dvar_vector_position();
   save_identifier_string("a");
   gradient_structure::GRAD_STACK1->
     set_gradient_stack(dv_init);
   return(*this);
 }
