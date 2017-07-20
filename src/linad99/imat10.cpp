/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return vector diagonal of matrix.

\param matrix imatrix
*/
ivector diagonal(const imatrix& matrix)
{
  if (matrix.indexmin() != matrix.colmin()
      || matrix.indexmax() != matrix.colmax())
  {
    cerr << "Error: imatrix is not square"
         << " in diagonal(const imatrix&).\n";
    ad_exit(1);
  }
  int min = matrix.indexmin();
  int max = matrix.indexmax();
  ivector vector(min, max);
  for (int i = min; i <= max; ++i)
  {
    vector(i) = matrix(i,i);
  }
  return vector;
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
    cerr << "Index bounds do not match"
         << " in operator*(const ivector&, const ivector&)\n";
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
Returns results of integer matrix multiplication (a x b).

\param a imatrix
\param b imatrix
*/
imatrix operator*(const imatrix& a, const imatrix& b)
{
  if (a.colmin() != b.rowmin() || a.colmax() != b.rowmax())
  {
    cerr << " Incompatible array bounds"
         << " in operator*(const imatrix&, const imatrix&)\n";
    ad_exit(1);
  }
  imatrix results(a.rowmin(),a.rowmax(), b.colmin(), b.colmax());
  for (int j = b.colmin(); j <= b.colmax(); ++j)
  {
    ivector col = column(b, j);
    for (int i = a.rowmin(); i <= a.rowmax(); ++i)
    {
      results(i, j) = a(i) * col;
    }
  }
  return results;
}
