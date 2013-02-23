/*
 * $Id: atoi.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
#include <sstream>
using std::istringstream;

#include <fvar.hpp>

int atoi(adstring& s)
{
  istringstream is((char*)s);
  int i;
  is >> i;
  return i;
}
