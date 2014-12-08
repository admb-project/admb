/*
 * $Id$
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
  int i = 0;
  is >> i;
  return i;
}
