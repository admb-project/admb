/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#define HOME_VERSION
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

 void lmatrix::initialize (void)
 {
   for (int i=rowmin();i<=rowmax();i++)
   {
     (*this)(i).initialize();
   }
 }
#undef HOME_VERSION
