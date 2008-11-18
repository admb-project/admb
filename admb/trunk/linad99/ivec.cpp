/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
#include <fvar.hpp>


ivector& ivector::shift(int min)
{
  v += indexmin()-min;
  index_max=index_max+min-index_min;
  index_min=min;
  shape->shift(min);
  return *this;
}

void lvector::shift(int min)
{
  v += indexmin()-min;
  shape->shift(min);
}

#undef HOME_VERSION
