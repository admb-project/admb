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

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdlib.h>
#include "admb_messages.h"

#ifndef OPT_LIB
/**
 * Description not yet available.
 * \param
 */
 int& ivector::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
   if (!v)
   {
       cerr << "\nattempting to acces non-allocated ivector in ivector::operator[]";
       ad_exit(1);
       cerr << endl;
   }
   if (i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high", "int& ivector::operator[] (int i)", indexmin(), indexmax(), i);
   }
   if (i<indexmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low", "int& ivector::operator[] (int i)", indexmin(), indexmax(), i);
   }
   #endif
   return(*(v+i));
 }

/**
 * Description not yet available.
 * \param
 */
 int& ivector::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
   if (!v)
   {
       cerr << "\nattempting to acces non-allocated ivector in ivector::operator()";
       ad_exit(1);
       cerr << endl;
   }
   if (i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high", "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
   }
   if (i < indexmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low", "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
   }
   #endif
   return(*(v+i));
 }


#ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
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

void abcde_f(void) { /*int i=1;*/ }
