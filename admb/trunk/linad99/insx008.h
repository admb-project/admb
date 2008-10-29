 prevariable elem(int i) { return (va+i); }

 double& elem_value(int i) { return (va[i].x); }

 double_and_int * get_va(){return va;}

#ifdef USE_CONST
  prevariable elem(int i) _CONST { return (va+i); }

  double& elem_value(int i) _CONST { return (va[i].x); }

  double_and_int * get_va() _CONST {return va;}
#endif

