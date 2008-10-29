  inline dvar_vector& elem(int i) { return (m[i]); }
  inline prevariable elem(int i, int j) { return (elem(i).elem(j) ) ; }
  #ifdef USE_CONST
    inline dvar_vector& elem(int i) const { return (m[i]); }
    inline prevariable elem(int i, int j) const {return (elem(i).elem(j) ) ; }
  #endif
