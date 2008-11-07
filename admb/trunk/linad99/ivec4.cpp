/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
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
#undef HOME_VERSION
