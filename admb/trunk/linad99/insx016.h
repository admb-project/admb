   dmatrix& elem(int k) { return(t[k]); }
#ifdef USE_CONST
   _CONST dmatrix& elem(int k) _CONST { return(t[k]); }
#endif
