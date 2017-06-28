/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

/**
Returns true if ivector is allocated, otherwise false.

\param ivec ivector
*/
int allocated(const ivector& ivec)
{
  return !(!(ivec));
}
/**
Returns true if lvector is allocated, otherwise false.

\param lvec lvector
*/
int allocated(const lvector& lvec)
{
  return !(!(lvec));
}
/**
Returns true if lvector is allocated, otherwise false.

\param lvec lvector
*/
int allocated(const dvector& dvec)
{
  return !(!(dvec));
}
/**
Returns true if variables is allocated, otherwise false.

\param variables dvar_vector
*/
int allocated(const dvar_vector& variables)
{
  return !(!(variables));
}
/**
Returns true if imat is allocated, otherwise false.

\param imat imatrix
*/
int allocated(const imatrix& imat)
{
  return !(!(imat));
}
/**
Returns true if dmat is allocated, otherwise false.

\param dmat dmatrix
*/
int allocated(const dmatrix& dmat)
{
  return !(!(dmat));
}
/**
Returns true if vmat is allocated, otherwise false.

\param vmat dvar_matrix
*/
int allocated(const dvar_matrix& vmat)
{
  return !(!(vmat));
}
/**
Returns true if iarr3 is allocated, otherwise false.

\param iarr3 i3_array
*/
int allocated(const i3_array& iarr3)
{
  return !(!(iarr3));
}
/**
Returns true if arr3 is allocated, otherwise false.

\param arr3 d3_array
*/
int allocated(const d3_array& arr3)
{
  return !(!(arr3));
}
/**
Returns true if varr3 is allocated, otherwise false.

\param varr3 dvar3_array
*/
int allocated(const dvar3_array& varr3)
{
  return !(!(varr3));
}
/**
Returns true if iarr4 is allocated, otherwise false.

\param iarr4 i4_array
*/
int allocated(const i4_array& iarr4)
{
  return !(!(iarr4));
}
/**
Returns true if arr4 is allocated, otherwise false.

\param arr4 d4_array
*/
int allocated(const d4_array& arr4)
{
  return !(!(arr4));
}
/**
Returns true if varr4 is allocated, otherwise false.

\param varr4 dvar4_array
*/
int allocated(const dvar4_array& varr4)
{
  return !(!(varr4));
}
/**
Returns true if arr5 is allocated, otherwise false.

\param arr5 d5_array
*/
int allocated(const d5_array& arr5)
{
  return !(!(arr5));
}
/**
Returns true if iarr5 is allocated, otherwise false.

\param iarr5 i5_array
*/
int allocated(const i5_array& iarr5)
{
  return !(!(iarr5));
}
/**
Returns true if varr5 is allocated, otherwise false.

\param varr5 dvar5_array
*/
int allocated(const dvar5_array& varr5)
{
  return !(!(varr5));
}
/**
Returns true if arr6 is allocated, otherwise false.

\param arr6 d6_array
*/
int allocated(const d6_array& arr6)
{
  return !(!(arr6));
}
/**
Returns true if varr6 is allocated, otherwise false.

\param varr6 dvar6_array
*/
int allocated(const dvar6_array& varr6)
{
  return !(!(varr6));
}
/**
Returns true if arr7 is allocated, otherwise false.

\param arr7 d7_array
*/
int allocated(const d7_array& arr7)
{
  return !(!(arr7));
}
/**
Returns true if varr7 is allocated, otherwise false.

\param varr6 dvar7_array
*/
int allocated(const dvar7_array& varr7)
{
  return !(!(varr7));
}
