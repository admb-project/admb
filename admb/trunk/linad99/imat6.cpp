
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"




void imatrix::allocate(_CONST imatrix& dm)
{
  int nrl=dm.rowmin();
  int nrh=dm.rowmax();
  int ncl=dm.colmin();
  int nch=dm.colmax();
  index_min=nrl;
  index_max=nrh;

  int rs=rowsize();
  if ( (m = new ivector [rs]) == 0)
  {
    cerr << " Error allocating memory in imatrix contructor" << endl;
    ad_exit(21);
  }
  if ( (shape = new mat_shapex(m))== 0)
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
