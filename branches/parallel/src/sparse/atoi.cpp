/*
 * $Id: atoi.cpp 947 2011-01-12 23:56:42Z johnoel $
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
