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

#include <fvar.hpp>

dvariable beta(const prevariable& a,const prevariable& b )
{
  return exp(gammln(a)+gammln(b)-gammln(a+b));
}
