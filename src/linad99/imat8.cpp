/*
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include <fvar.hpp>

/**
Returns sum of the columns in matrix m.
*/
ivector colsum(const imatrix& m)
{
  int cmin = m.colmin();
  int cmax = m.colmax();
  ivector ret(cmin, cmax);
  ret.initialize();

  int rmin = m.rowmin();
  int rmax = m.rowmax();
  for (int j=cmin; j<=cmax; j++)
  {
    for (int i=rmin; i<=rmax; i++)
    {
      ret(j) += m(i,j);
    }
  }
  return ret;
}
/**
Returns sum of the rows in matrix m.
*/
ivector rowsum(const imatrix& m)
{
  int rmin = m.rowmin();
  int rmax = m.rowmax();
  ivector ret(rmin, rmax);

  for (int i=rmin; i<=rmax; ++i)
  {
    ret(i) = sum(m(i));
  }

  return ret;
}

/**
 * Description not yet available.
 * \param
 */
  void imatrix::fill_seqadd(int i2,int j)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    int ii=i2;
    for (int i=mmin;i<=mmax;i++)
    {
      if (allocated((*this)(i)))
      {
        (*this)(i).fill_seqadd(ii,j);
        int jmax=(*this)(i).indexmax();
        ii=(*this)(i,jmax)+j;
      }
    }
  }
