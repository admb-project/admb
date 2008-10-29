       inline double * xadr() { return( &(v->x) ); }
       inline double& xval() { return( (v->x) ); }

       inline double_and_int * & get_v()
       {
         return v;
       }
       #ifdef USE_CONST
         inline double_and_int *  get_v() _CONST 
         {
           return v;
         }
       #endif
