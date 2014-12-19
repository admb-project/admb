/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#include <cassert>
#include <climits>

//class banded_symmetric_dmatrix;

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& ofs1, const banded_symmetric_dmatrix& S1)
{
  std::streamsize width = ofs1.width();
  assert(width <= INT_MAX);
  int w= (int)width;
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
