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
#if !defined(OPT_LIB)
/**
 * Description not yet available.
 * \param
 */
const dvector& dmatrix::operator()(int i) const
 {
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in "
       "dmatrix::operator()" << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in "
       "dmatrix::operator()" << "value was" << i;
       ad_exit(22);
     }
   return *(m+i);
 }
#endif
