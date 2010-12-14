/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>
   int operator ==(double v0,_CONST prevariable& v1)
   { 
     return (v0==value(v1));
   }

   int operator <=(double v0,_CONST prevariable& v1)
   { 
     return (v0<=value(v1));
   }

   int operator >=(double v0,_CONST prevariable& v1)
   { 
     return (v0>=value(v1));
   }

   int operator >(double v0,_CONST prevariable& v1)
   { 
     return (v0>value(v1));
   }

   int operator <(double v0,_CONST prevariable& v1)
   { 
     return (v0<value(v1));
   }

   int operator !=(double v0,_CONST prevariable& v1)
   { 
     return (v0!=value(v1));
   }




