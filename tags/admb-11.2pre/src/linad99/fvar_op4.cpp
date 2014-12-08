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

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    prevariable dvar_vector::operator[] (int i)
    {
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in "
          "prevariable::operator[]";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in "
          "prevariable::operator[]";
          ad_exit(1);
        }
      //((va+i)->nc)++;
      return (va+i);
    }

/**
 * Description not yet available.
 * \param
 */
    prevariable dvar_vector::operator() (int i)
    {
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in "
          "prevariable::operator()";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in "
          "prevariable::operator()";
          ad_exit(1);
        }
      //((va+i)->nc)++;
      return (va+i);
    }

/**
 * Description not yet available.
 * \param
 */
const prevariable dvar_vector::operator[](int i) const
    {
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in "
          "prevariable::operator[]";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in "
          "prevariable::operator[]";
          ad_exit(1);
        }
      //((va+i)->nc)++;
      return (va+i);
    }

/**
 * Description not yet available.
 * \param
 */
const prevariable dvar_vector::operator()(int i) const
    {
        if (i<indexmin())
        {
          cerr << "array bound exceeded -- index too low in "
          "prevariable::operator()";
          ad_exit(1);
        }
        if (i>indexmax())
        {
          cerr << "array bound exceeded -- index too high in "
          "prevariable::operator()";
          ad_exit(1);
        }
      //((va+i)->nc)++;
      return (va+i);
    }
#endif
