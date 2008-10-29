#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

dvar_matrix operator - (_CONST dvar_matrix & m)
{
  return -1.0*m;
}

#undef HOME_VERSION

