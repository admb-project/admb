/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

   dvar3_array pow(_CONST dvar3_array& m, int e)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=pow(m(i),e);
     }
     return tmp;
   }


