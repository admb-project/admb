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

/**
 * Description not yet available.
 * \param
 */
ivector diagonal(const imatrix& m)
{
  if (m.indexmin() != m.colmin() || m.indexmax() != m.colmax())
  {
    cerr << "Error matrix not square in function diagonal" << endl;
    exit(21);
  }
  int mmin=m.indexmin();
  int mmax=m.indexmax();
  ivector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
    tmp(i)=m(i,i);
  return tmp;
}
/** Compute the dot product of two vectors. The minimum and maxium
legal subscripts of the arguments must agree; otherwize an error message
is printed and execution terminates.
\ingroup matop
\param t1 A %ivector, \f$a\f$.
\param t2 A %ivector, \f$b\f$.
\return A int, \f$z = a\cdot b = \sum_i a_i\cdot b_i\f$  containing
the value of the dot product of the two arguments.
*/
int operator*(const ivector& t1, const ivector& t2)
{
  if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())
  {
    cerr << "Index bounds do not match in "
      "ivector operator*(const ivector&, const ivector&)\n";
    ad_exit(1);
  }
  int tmp = 0;
#ifdef OPT_LIB
  const int* pt1=&t1[t1.indexmin()];
  const int* pt1m=&t1[t1.indexmax()];
  const int* pt2=&t2[t2.indexmin()];
  do
  {
    tmp+=*pt1++ * *pt2++;
  }
  while (pt1<=pt1m);

#else
  #ifndef USE_ASSEMBLER
    int min=t1.indexmin();
    int max=t1.indexmax();
    for (int i=min; i<=max; i++)
    {
      tmp+=t1[i]*t2[i];
    }
  #else
    int min=t1.indexmin();
    int n=t1.indexmax()-min+1;
    dp_dotproduct(&tmp,&(t1(min)),&(t2(min)),n);
  #endif
#endif

  return tmp;
}

/**
Returns matrix multiplication (m1 x m2).

\param m1
\param m2
*/
imatrix operator*(const imatrix& m1, const imatrix& m2 )
{
  if (m1.colmin() != m2.rowmin() || m1.colmax() != m2.rowmax())
  {
    cerr << " Incompatible array bounds in "
      "imatrix  operator * (const imatrix& x, const imatrix& m)\n";
    ad_exit(21);
  }
  imatrix tmp(m1.rowmin(),m1.rowmax(), m2.colmin(), m2.colmax());
  for (int j=m2.colmin(); j<=m2.colmax(); j++)
  {
    ivector m2col=column(m2,j);
    for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
    {
      tmp(i,j) = m1(i) * m2col;
    }
  }
  return tmp;
}
