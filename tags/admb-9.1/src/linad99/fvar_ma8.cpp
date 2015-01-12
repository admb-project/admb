/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
//#undef OPT_LIB
#include "fvar.hpp"

#if !defined(OPT_LIB)
 dvar_vector& dvar_matrix::operator() (int i)
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


