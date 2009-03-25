/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"
 dvariable mean(_CONST dvar_matrix& m)
 {
   dvariable tmp;
   tmp=sum(m)/double(size_count(m));
   return tmp;
 }
