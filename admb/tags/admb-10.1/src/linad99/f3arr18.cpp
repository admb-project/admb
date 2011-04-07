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
#ifdef USE_CONST
  #ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
  _CONST dvar_matrix& dvar3_array::operator() (int i) _CONST 
 {
   #ifdef SAFE_ARRAYS
     if (i<slicemin())
     {
       cerr << "matrix bound exceeded -- row index too low in 3d_array::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>slicemax())
     {
       cerr << "matrix bound exceeded -- row index too high in 3d_array::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return( t[i]);
 }
  #endif
#endif
