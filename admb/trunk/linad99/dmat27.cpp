


#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"


double colsum(_CONST dmatrix& m,int col)
{ 
  if (col<m.rowmin() || col>m.rowmax())
  {
    cerr << "Row out of bounds in function"
            " colsum(_CONST imatrix& m,int col)" << endl;
    ad_exit(1);
  }
  double isum=0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    isum+=m(i,col);
  }
  return isum;
}

#undef HOME_VERSION
