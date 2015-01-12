/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
#if !defined(OPT_LIB)
 dvector& dmatrix::operator() (int i)
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
#  endif
   return *(m+i);
 }

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

