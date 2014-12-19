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
#include "admb_messages.h"

#if !defined(OPT_LIB)

/**
 * Description not yet available.
 * \param
 */
 dvector& dmatrix::operator() (int i)
 {
     if (i<rowmin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
       "dvector& dmatrix::operator() (int i)", rowmin(), rowmax(), i);
     }
     if (i>rowmax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
       "dvector& dmatrix::operator() (int i)", rowmin(), rowmax(), i);
     }
   return *(m+i);
 }
#endif

#if !defined(OPT_LIB) || defined(__INTEL_COMPILER)
/**
 * Description not yet available.
 * \param
 */
 double& dmatrix::operator() (int i, int j)
 {
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in "
               "dmatrix::operator()"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in "
               "dmatrix::operator()"
             << "value was" << i;
       ad_exit(22);
     }

     // if (j<colmin())
     if (j<elem(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in "
               "dmatrix::operator()"
             << "value was" << j;
       ad_exit(21);
     }

     // if (j>colmax())
     if (j>elem(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in "
               "dmatrix::operator()"
             << "value was" << j;
       ad_exit(22);
     }
   return( *((m[i]).v+j) );
 }

/**
 * Description not yet available.
 * \param
 */
const double& dmatrix::operator()(int i, int j) const
 {
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in "
               "dmatrix::operator()"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in "
               "dmatrix::operator()"
             << "value was" << i;
       ad_exit(22);
     }

     // if (j<colmin())
     if (j<elem(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in "
               "dmatrix::operator()"
             << "value was" << j;
       ad_exit(21);
     }

     // if (j>colmax())
     if (j>elem(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in "
               "dmatrix::operator()"
             << "value was" << j;
       ad_exit(22);
     }
   return( *((m[i]).v+j) );
 }
#endif
