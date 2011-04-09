/*
 * $Id: fvar_a13.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#include <stdlib.h>
#if defined(__TURBOC__) && !defined(__linux__)
   #include <alloc.h>
#endif

/**
 * Description not yet available.
 * \param
 */
 dvar_vector::dvar_vector(int ncl,int nch,kkludge_object kg)
 {
   va=NULL;
   allocate(ncl,nch);

   #ifdef DIAG
     cout << " Allocating dvar_vector with ptr_address\n  "
         << &va << "  pointing at  " << (va+indexmin()) << "\n";
   #endif
 }
