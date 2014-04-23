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
#include "fvar.hpp"
#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
const dvar_matrix& dvar3_array::operator[] (int i) const
 {
     if (i<slicemin())
     {
       cerr << "matrix bound exceeded -- row index too low in "
       "3d_array::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>slicemax())
     {
       cerr << "matrix bound exceeded -- row index too high in "
       "3d_array::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   return t[i];
 }
#endif
