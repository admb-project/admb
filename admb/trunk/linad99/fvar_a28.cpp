

#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD

#include "fvar.hpp"

  dvar_vector extract_diagonal(_CONST dvar_matrix& m)
  {
    if ( (m.rowmin()!=m.colmin()) || (m.rowmax()!=m.colmax()))
    {
      cerr << "Error in extract_diagonal function -- input matrix not square"
       <<endl;
      ad_exit(1);
    }
    RETURN_ARRAYS_INCREMENT();
    dvar_vector tmp(m.rowmin(),m.rowmax());

    for (int i=m.rowmin(); i<=m.rowmax(); i++)
    {
      tmp.elem(i)=m.elem(i,i);
    }
    RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }

#undef HOME_VERSION
