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
 dvariable mean(_CONST dvar_matrix& m)
 {
   dvariable tmp;
   tmp=sum(m)/double(size_count(m));
   return tmp;
 }
#undef HOME_VERSION
