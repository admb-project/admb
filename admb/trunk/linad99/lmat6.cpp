

#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"




void lmatrix::allocate(_CONST lmatrix& dm)
{
  int nrl=dm.rowmin();
  int nrh=dm.rowmax();
  int ncl=dm.colmin();
  int nch=dm.colmax();

  if ( (shape = new mat_shape(nrl,nrh,ncl,nch))== 0)
  {
    cerr << " Error allocating memory in imatrix contructor" << endl;
    ad_exit(21);
  }

  int rs=rowsize();
  if ( (m = new lvector [rs]) == 0)
  {
    cerr << " Error allocating memory in imatrix contructor" << endl;
    ad_exit(21);
  }
  m -= rowmin();
  for (int i=rowmin(); i<=rowmax(); i++)
  {
    m[i].allocate(dm(i));
  }
}

#undef HOME_VERSION
