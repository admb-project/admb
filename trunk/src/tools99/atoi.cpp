/*
 * $Id: atoi.cpp 948 2011-01-12 23:59:02Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <fvar.hpp>

int atoi(adstring& s)
{
  istrstream is((char*)s);
  int i;
  is >> i;
  return i;
}
