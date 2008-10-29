
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#define HOME_VERSION
#include "fvar.hpp"

dvariable trace(_CONST dvar_matrix& M)
{
  dvariable tmp;
  tmp=0.0;
  if (M.colmin()!=M.rowmin() || M.colmax()!=M.rowmax() )
  {
    cerr << " Matrix not square in trace\n";
    ad_exit(1);
  }
  for (int i=M.colmin();i<=M.colmax();i++)
  {
    tmp+=M.elem(i,i);
  }
  return tmp;
}

#undef HOME_VERSION
