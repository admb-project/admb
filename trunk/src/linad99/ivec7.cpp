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
   if (!v)
   {
       cerr << "\nattempting to acces non-allocated ivector in "
       "ivector::operator[]\n";
       ad_exit(1);
   }
   if (i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
     "int& ivector::operator[] (int i)", indexmin(), indexmax(), i);
   }
   if (i<indexmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
     "int& ivector::operator[] (int i)", indexmin(), indexmax(), i);
   }
   return(*(v+i));
 }

/**
 * Description not yet available.
 * \param
 */
 int& ivector::operator() (int i)
 {
   if (!v)
   {
     cerr << "\nattempting to acces non-allocated ivector in "
     "ivector::operator()\n";
     ad_exit(1);
   }
   if (i > indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
     "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
   }
   if (i < indexmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
     "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
   }
   return(*(v+i));
 }

/**
 * Description not yet available.
 * \param
 */
const int& ivector::operator[](int i) const
 {
     if (!v)
     {
       cerr << "\nattempting to acces non-allocated ivector in "
       "ivector::operator[]\n";
       ad_exit(1);
     }
     if (i>indexmax())
     {
       cerr << "\narray bound exceeded -- index too high in "
       "ivector::operator[]";
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
   return(*(v+i));
 }

/**
 * Description not yet available.
 * \param
 */
const int& ivector::operator()(int i) const
 {
     if (!v)
     {
       cerr << "\nattempting to acces non-allocated ivector in "
       "ivector::operator()\n";
       ad_exit(1);
     }
     if (i>indexmax())
     {
       cerr << "\narray bound exceeded -- index too high in "
       "ivector::operator()";
       cerr << "index value " << i << " max value " << indexmax() << endl;
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "\narray bound exceeded -- index too low in ivector::operator[]";
       cerr << endl;
       ad_exit(1);
     }
   return(*(v+i));
 }
#endif
