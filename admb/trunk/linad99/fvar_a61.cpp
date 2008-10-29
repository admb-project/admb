//COPYRIGHT (c) 2003 OTTER RESEARCH LTD
#include <admodel.h>
 dvar_vector::dvar_vector(const param_init_number_vector& _t)
 {
   param_init_number_vector& t=(param_init_number_vector&) (_t);
   int i;
   va=NULL;
   allocate(t.indexmin(),t.indexmax());
   initialize();
   for ( i=indexmin(); i<=indexmax(); i++)
   {
     (*this)(i)=t(i);
   }
 }


 dvar_vector::dvar_vector(const param_init_bounded_number_vector& _t)
 {
   param_init_bounded_number_vector& t=(param_init_bounded_number_vector&) (_t);
   int i;
   va=NULL;
   allocate(t.indexmin(),t.indexmax());
   initialize();
   for ( i=indexmin(); i<=indexmax(); i++)
   {
     (*this)(i)=t(i);
   }
 }


