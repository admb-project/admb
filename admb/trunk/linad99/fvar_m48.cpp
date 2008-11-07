/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
//#undef OPT_LIB
#include "fvar.hpp"

#if !defined(OPT_LIB)

#ifdef USE_CONST
 _CONST dvar_vector& dvar_matrix::operator() (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dvar_matrix::operator()"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in dvar_matrix::operator()"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return (m[i]);
 }
#endif
#endif
#undef HOME_VERSION


