/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#define HOME_VERSION
#include "fvar.hpp"


//class banded_symmetric_dmatrix;

ostream& operator << (const ostream& ofs1,const banded_symmetric_dmatrix& S1)
{
  int w=ofs1.width();
  ostream& ofs=(ostream&) ofs1;
  banded_symmetric_dmatrix& S=(banded_symmetric_dmatrix&)(S1);
  int imin=S.indexmin();
  int imax=S.indexmax();
  int bw=S.bandwidth();
  int i1;
  int j1;
  for (int i=imin;i<=imax;i++)
  {
    for (int j=imin;j<=imax;j++)
    {
      if (j<=i)
      {
	j1=j;
	i1=i;
      }
      else
      {
	j1=i;
	i1=j;
      }
      if ( (i1-j1) < bw)
        ofs << setw(w) << S(i1,j1) << " ";
      else
        ofs << setw(w) << 0.0 << " ";
    }
    ofs << endl;
  }
  return ofs;
}
#undef HOME_VERSION
