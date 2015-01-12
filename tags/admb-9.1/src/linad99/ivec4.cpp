/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

void ivector::fill(const char * s)
{
  dvector tmp(*this);
  tmp.fill(s);
  *this=ivector(tmp);
}

void lvector::fill(const char * s)
{
  dvector tmp(*this);
  tmp.fill(s);
  *this=lvector(tmp);
}
