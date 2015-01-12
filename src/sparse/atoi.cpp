/*
 * $Id$
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
