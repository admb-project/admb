/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#define HOME_VERSION
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
             << "\nvalue was " << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in imatrix::operator()(int, int)"
             << "\nvalue was " << i;
       ad_exit(22);
     }
     if (j<(*this)(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in imatrix::operator()(int, int)"
	     << "\nvalue was " << j;
       ad_exit(21);
     }
     if (j>(*this)(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in imatrix::operator()(int, int)"
	     << "\nvalue was " << j;
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
             << "\nvalue was " << i;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in imatrix::operator()(int, int)"
             << "\nvalue was " << i;
       ad_exit(22);
     }
     if (j<(*this)(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in imatrix::operator()(int, int)"
	     << "\nvalue was " << j;
       ad_exit(21);
     }
     if (j>(*this)(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in imatrix::operator()(int, int)"
	     << "\nvalue was " << j;
       ad_exit(22);
     }
   #endif
   return(*((*(m+i)).v+j));
 }
#endif
#endif
#undef HOME_VERSION
