/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
Return computed column(col) sum for dmatrix m.
*/
double colsum(const dmatrix& m, int col)
{
  int mmin = m.rowmin();
  int mmax = m.rowmax();
  if (col < mmin || col > mmax)
  {
    cerr << "Row out of bounds in function"
            " colsum(const imatrix& m,int col)" << endl;
    ad_exit(1);
  }
  double sum = 0;
  for (int i = mmin; i <= mmax; ++i)
  {
    sum += m(i, col);
  }
  return sum;
}
