/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>

line_adstring& line_adstring::operator=(const adstring& s)
{
  this->adstring::operator=(s);
  return *this;
}

line_adstring& line_adstring::operator=(const char* s)
{
  this->adstring::operator=(s);
  return *this;
}
