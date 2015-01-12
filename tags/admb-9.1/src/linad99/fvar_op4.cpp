/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
// file: fvar_ops.cpp
// operators involving prevariables

//#undef OPT_LIB
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdio.h>
#include <math.h>


void gradfree(dlink *);

int xxx_uuu_a(void)
{
  return 1;
}

#ifndef OPT_LIB
    prevariable dvar_vector::operator[] (int i)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in prevariable::operator[]";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in prevariable::operator[]";
          ad_exit(1);
        }
      #endif
      //((va+i)->nc)++;
      return (va+i);

    }

    prevariable dvar_vector::operator() (int i)
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in prevariable::operator[]";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in prevariable::operator[]";
          ad_exit(1);
        }
      #endif
      //((va+i)->nc)++;
      return (va+i);

    }
#endif

#ifdef USE_CONST
  #ifndef OPT_LIB
    _CONST prevariable dvar_vector::operator[] (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in prevariable::operator[]";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in prevariable::operator[]";
          ad_exit(1);
        }
      #endif
      //((va+i)->nc)++;
      return (va+i);

    }

    _CONST prevariable dvar_vector::operator() (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in prevariable::operator[]";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in prevariable::operator[]";
          ad_exit(1);
        }
      #endif
      //((va+i)->nc)++;
      return (va+i);

    }
  #endif
#endif

