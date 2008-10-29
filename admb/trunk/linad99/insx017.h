          dvar_matrix& elem(int k) { return( t[k] ); }
          prevariable elem(int i,int j,int k) { return( t[k].elem(i,j) ); }
       #ifdef USE_CONST
          _CONST dvar_matrix& elem(int k) _CONST { return( t[k] ); }
          _CONST prevariable elem(int i,int j,int k) _CONST { return( t[k].elem(i,j) ); }
       #endif
