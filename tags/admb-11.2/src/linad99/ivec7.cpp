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
#include <stdexcept>

#ifndef OPT_LIB
/**
 * Description not yet available.
 * \param
 */
int& ivector::operator[](int i)
{
  if (!v)
  {
    cerr << "\nattempting to acces non-allocated ivector in "
       "ivector::operator[]\n";
    throw std::bad_alloc();
  }
  else if (i > indexmax())
  {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
     "int& ivector::operator[] (int i)", indexmin(), indexmax(), i);
     throw std::out_of_range("array bound exceeded -- index too high");
  }
  else if (i<indexmin())
  {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
     "int& ivector::operator[] (int i)", indexmin(), indexmax(), i);
     throw std::out_of_range("array bound exceeded -- index too low");
  }
  else
  {
    return *(v+i);
  }
}

/**
 * Description not yet available.
 * \param
 */
int& ivector::operator()(int i)
{
  if (!v)
  {
    cerr << "\nattempting to acces non-allocated ivector in "
     "ivector::operator()\n";
    throw std::bad_alloc();
  }
  else if (i > indexmax())
  {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
     "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
     throw std::out_of_range("array bound exceeded -- index too high");
  }
  else if (i < indexmin())
  {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
     "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
     throw std::out_of_range("array bound exceeded -- index too low");
  }
  else
  {
    return *(v+i);
  }
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
    throw std::bad_alloc();
  }
  else if (i > indexmax())
  {
    cerr << "\narray bound exceeded -- index too high in "
       "ivector::operator[]";
    cerr << "index value " << i << " max value " << indexmax() << endl;
    cerr << endl;
    throw std::out_of_range("array bound exceeded -- index too high");
  }
  else if (i < indexmin())
  {
    cerr << "\narray bound exceeded -- index too low in ivector::operator[]";
    cerr << endl;
    throw std::out_of_range("array bound exceeded -- index too low");
  }
  else
  {
    return *(v+i);
  }
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
    throw std::bad_alloc();
  }
  else if (i>indexmax())
  {
    cerr << "\narray bound exceeded -- index too high in "
       "ivector::operator()";
    cerr << "index value " << i << " max value " << indexmax() << endl;
    throw std::out_of_range("array bound exceeded -- index too high");
  }
  else if (i<indexmin())
  {
    cerr << "\narray bound exceeded -- index too low in ivector::operator[]";
    cerr << endl;
    throw std::out_of_range("array bound exceeded -- index too low");
  }
  else
  {
    return *(v+i);
  }
}
#endif
