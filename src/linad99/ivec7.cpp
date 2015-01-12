/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdlib.h>

#ifndef OPT_LIB
 int& ivector::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
     if (!v)
     {
       cerr << "\nattempting to acces non-allocated ivector in ivector::operator[]";
       ad_exit(1);
       cerr << endl;
     }
     if (i>indexmax())
     {
       cerr << "\narray bound exceeded -- index too high in ivector::operator[]";
       cerr << "index value " << i << " max value " << indexmax() << endl;
       cerr << endl;
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "\narray bound exceeded -- index too low in ivector::operator[]";
       cerr << endl;
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }

 int& ivector::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
     if (!v)
     {
       cerr << "\nattempting to acces non-allocated ivector in ivector::operator()";
       ad_exit(1);
       cerr << endl;
     }
     if (i>indexmax())
     {
       cerr << "\narray bound exceeded -- index too high in ivector::operator()";
       cerr << "index value " << i << " max value " << indexmax() << endl;
       cerr << endl;
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "\narray bound exceeded -- index too low in ivector::operator[]";
       cerr << endl;
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }


#ifdef USE_CONST
 _CONST int& ivector::operator[] (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (!v)
     {
       cerr << "\nattempting to acces non-allocated ivector in ivector::operator[]";
       ad_exit(1);
       cerr << endl;
     }
     if (i>indexmax())
     {
       cerr << "\narray bound exceeded -- index too high in ivector::operator[]";
       cerr << "index value " << i << " max value " << indexmax() << endl;
       cerr << endl;
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "\narray bound exceeded -- index too low in ivector::operator[]";
       cerr << endl;
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }

  _CONST int& ivector::operator() (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (!v)
     {
       cerr << "\nattempting to acces non-allocated ivector in ivector::operator()";
       ad_exit(1);
       cerr << endl;
     }
     if (i>indexmax())
     {
       cerr << "\narray bound exceeded -- index too high in ivector::operator()";
       cerr << "index value " << i << " max value " << indexmax() << endl;
       cerr << endl;
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "\narray bound exceeded -- index too low in ivector::operator[]";
       cerr << endl;
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }
#endif
#endif

void abcde_f(void) { int i=1;}

