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




