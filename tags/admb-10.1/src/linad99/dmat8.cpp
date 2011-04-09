/*
 * $Id: dmat8.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
#  ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "dvector& dmatrix::operator() (int i)", rowmin(), rowmax(), i);
     }
     if (i>rowmax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "dvector& dmatrix::operator() (int i)", rowmin(), rowmax(), i);
     }
#  endif
   return *(m+i);
 }

/**
 * Description not yet available.
 * \param
 */
 double& dmatrix::operator() (int i, int j)
 {
#  ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dmatrix::operator()"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in dmatrix::operator()"
             << "value was" << i;
       ad_exit(22);
     }

     // if (j<colmin())
     if (j<elem(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in dmatrix::operator()"
             << "value was" << j;
       ad_exit(21);
     }

     // if (j>colmax())
     if (j>elem(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in dmatrix::operator()"
             << "value was" << j;
       ad_exit(22);
     }
#  endif
   return( *((m[i]).v+j) );
 }

#  ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
 _CONST double& dmatrix::operator() (int i, int j)  _CONST
 {
#    ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dmatrix::operator()"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in dmatrix::operator()"
             << "value was" << i;
       ad_exit(22);
     }

     // if (j<colmin())
     if (j<elem(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in dmatrix::operator()"
             << "value was" << j;
       ad_exit(21);
     }

     // if (j>colmax())
     if (j>elem(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in dmatrix::operator()"
             << "value was" << j;
       ad_exit(22);
     }
#    endif
   return( *((m[i]).v+j) );
 }
#  endif
#endif
