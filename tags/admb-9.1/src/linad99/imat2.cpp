/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
#endif

#if !defined(OPT_LIB)
 int& imatrix::operator() (int i,int j)
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in imatrix::operator()(int, int)"
             << "\nvalue was " << i << endl;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in imatrix::operator()(int, int)"
             << "\nvalue was " << i << endl;
       ad_exit(22);
     }
     if (j<(*this)(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in imatrix::operator()(int, int)"
	     << "\nvalue was " << j << endl;
       ad_exit(21);
     }
     if (j>(*this)(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in imatrix::operator()(int, int)"
	     << "\nvalue was " << j << endl;
       ad_exit(22);
     }
   #endif
   return(*((*(m+i)).v+j));
 }

#ifdef USE_CONST
 _CONST int& imatrix::operator() (int i,int j) _CONST 
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in imatrix::operator()(int, int)"
             << "\nvalue was " << i << endl;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in imatrix::operator()(int, int)"
             << "\nvalue was " << i << endl;
       ad_exit(22);
     }
     if (j<(*this)(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in imatrix::operator()(int, int)"
	     << "\nvalue was " << j << endl;
       ad_exit(21);
     }
     if (j>(*this)(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in imatrix::operator()(int, int)"
	     << "\nvalue was " << j << endl;
       ad_exit(22);
     }
   #endif
   return(*((*(m+i)).v+j));
 }
#endif
#endif
