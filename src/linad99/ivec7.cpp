/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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
Return element of ivector at index i.

\param i index
*/
int& ivector::operator[](int i)
{
  if (!v)
  {
    cerr << "\nError: Unable to access unallocated ivector"
         << " in ivector::operator[]\n";
    ad_exit(1);
  }
  else if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
     "int& ivector::operator[](int i)", indexmin(), indexmax(), i);
  }
  else if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
     "int& ivector::operator[](int i)", indexmin(), indexmax(), i);
  }

  return *(v + i);
}
/**
Return element of ivector at index i.

\param i index
*/
int& ivector::operator()(int i)
{
  if (!v)
  {
    cerr << "\nError: Unable to access unallocated ivector"
         << " in ivector::operator()\n";
    ad_exit(1);
  }
  else if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high",
      "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
  }
  else if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low",
      "int& ivector::operator() (int i)", indexmin(), indexmax(), i);
  }
  return *(v + i);
}
/**
Return element of ivector at index i.

\param i index
*/
const int& ivector::operator[](int i) const
{
  if (!v)
  {
    cerr << "\nError: Unable to access unallocated ivector"
         << " in ivector::operator[]\n";
    ad_exit(1);
  }
  else if (i > indexmax())
  {
    cerr << "\narray bound exceeded -- index too high"
         << " in ivector::operator[]";
    ad_exit(1);
  }
  else if (i < indexmin())
  {
    cerr << "\narray bound exceeded -- index too low"
         << " in ivector::operator[]";
    ad_exit(1);
  }
  return *(v + i);
}
/**
Return element of ivector at index i.

\param i index
*/
const int& ivector::operator()(int i) const
{
  if (!v)
  {
    cerr << "\nError: Unable to access unallocated ivector"
         << " in ivector::operator()\n";
    ad_exit(1);
  }
  else if (i > indexmax())
  {
    cerr << "\narray bound exceeded -- index too high"
         << " in ivector::operator()";
    ad_exit(1);
  }
  else if (i < indexmin())
  {
    cerr << "\narray bound exceeded -- index too low"
         << " in ivector::operator()";
    ad_exit(1);
  }
  return *(v + i);
}
#endif
