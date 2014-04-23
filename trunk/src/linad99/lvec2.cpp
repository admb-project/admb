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

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
const AD_LONG_INT& lvector::operator[](int i) const
 {
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in lvector::operator[]";
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in lvector::operator[]";
       ad_exit(1);
     }
   return(*(v+i));
 }

/**
 * Description not yet available.
 * \param
 */
const AD_LONG_INT& lvector::operator()(int i) const
 {
     if (i>indexmax())
     {
       cerr << "array bound exceeded -- index too high in lvector::operator[]";
       ad_exit(1);
     }

     if (i<indexmin())
     {
       cerr << "array bound exceeded -- index too low in lvector::operator[]";
       ad_exit(1);
     }
   return(*(v+i));
 }
#endif
