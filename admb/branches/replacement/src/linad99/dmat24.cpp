/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"
 double mean(_CONST dmatrix& m)
 {
   double tmp;
   tmp=sum(m)/size_count(m);
   return tmp;
 }
