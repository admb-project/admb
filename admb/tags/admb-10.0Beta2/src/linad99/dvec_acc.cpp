/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
//#undef OPT_LIB
#include "fvar.hpp"
#include "admb_messages.h"

#if !defined(OPT_LIB)
 double& dvector::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
   if (i > indexmax())
   {
#if defined(USE_EXCEPTIONS)
     throw vector_range_exception(i,indexmin(),indexmax());
#else
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high", "double& dvector::operator[] (int i)", indexmin(), indexmax(), i);
#endif
   }
   if (i < indexmin())
   {
#if defined(USE_EXCEPTIONS)
       throw vector_range_exception(i,indexmin(),indexmax());
#else
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low", "double& dvector::operator[] (int i)", indexmin(), indexmax(), i);
#endif
   }
   #endif
   return(*(v+i));
 }

 double& dvector::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
   if (i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high", "double& dvector::operator() (int i)", indexmin(), indexmax(), i);
   }
   if (i < indexmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low", "double& dvector::operator() (int i)", indexmin(), indexmax(), i);
   }
   #endif
   return(*(v+i));
 }


#ifdef USE_CONST
 _CONST double& dvector::operator[] (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in dvector::operator[]"
         << "\n";
       cerr << " index value is " << i << " indexmax() is "<< indexmax() <<"\n";
       ad_exit(1);
     }
     
     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in dvector::operator[]";
       cerr << " index value is " << i << " indexmin() is "<< indexmin() <<"\n";
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }

 _CONST double& dvector::operator() (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in dvector::operator()"
         << "\n";
       cerr << " index value is " << i << " indexmax() is "<< indexmax() <<"\n";
       ad_exit(1);
     }
     
     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in dvector::operator[]";
       cerr << " index value is " << i << " indexmin() is "<< indexmin() <<"\n";
       ad_exit(1);
     }
   #endif
   return(*(v+i));
 }

 #endif
#endif
