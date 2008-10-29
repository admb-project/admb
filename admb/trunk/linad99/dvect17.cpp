#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD

#include "fvar.hpp"

  dvector extract_diagonal(_CONST dmatrix& m)
  {
    if ( (m.rowmin()!=m.colmin()) || (m.rowmax()!=m.colmax()))
    {
      cerr << "Error in extract_diagonal function -- input matrix not square"
       <<endl;
      ad_exit(1);
    }
    dvector tmp(m.rowmin(),m.rowmax());

    for (int i=m.rowmin(); i<=m.rowmax(); i++)
    {
      tmp.elem(i)=m.elem(i,i);
    }
    return(tmp);
  }

#undef HOME_VERSION
