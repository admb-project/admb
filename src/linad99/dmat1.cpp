/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns product of AB where A is a vector and B is a matrix.

\param vec dvector
\param mat dmatrix
*/
dvector operator*(const dvector& A, const dmatrix& B)
{
#ifdef DIAG
  if(heapcheck() == _HEAPCORRUPT && ad_printf)
  {
    (*ad_printf)( "Entering dvector * dvec dmat is corrupted.\n" );
  }
  else
  {
    (*ad_printf)( "Entering dvector * dvec dmat  Heap is OK.\n" );
  }
#endif

  if (A.indexmin() != B.rowmin() || A.indexmax() != B.rowmax())
  {
    cerr << " Incompatible array bounds in "
         << "dvector operator*(const dvector& A, const dmatrix& B)\n";
    ad_exit(1);
  }

  dvector results(B.colmin(), B.colmax());
  results.initialize();

  for (int j = B.colmin(); j <= B.colmax(); ++j)
  {
    for (int i = A.indexmin(); i <= A.indexmax(); ++i)
    {
       results[j] += A[i] * B[i][j];
    }
  }
#ifdef DIAG
  if (heapcheck() == _HEAPCORRUPT && ad_printf)
  {
    (*ad_printf)( "Leaving dvector * dvec dmat is corrupted.\n" );
  }
  else
  {
    (*ad_printf)( "Leaving dvector * dvec dmat  Heap is OK.\n" );
  }
#endif

  return results;
}
/**
Returns product of AB where A is a dmatrix and B is a dvector.

\param A dmatrix
\param B dvector
*/
dvector operator*(const dmatrix& A, const dvector& B)
{
#ifdef DIAG
  if (heapcheck() == _HEAPCORRUPT && ad_printf)
  {
    (*ad_printf)("Entering dvector * dmat dvec is corrupted.\n");
  }
  else
  {
    (*ad_printf)("Entering dvector * dmat dvec   Heap is OK.\n");
  }
#endif
   if (B.indexmin() != A.colmin() || B.indexmax() != A.colmax())
   {
     cerr << " Incompatible array bounds in "
          << "dvector operator*(const dmatrix& A, const dvector& B)\n";
     ad_exit(1);
   }

   dvector results(A.rowmin(), A.rowmax());
   results.initialize();

   for (int i = A.rowmin(); i <= A.rowmax(); ++i)
   {
     for (int j = B.indexmin(); j <= B.indexmax(); ++j)
     {
       results[i] += A[i][j] * B[j];
     }
   }

#ifdef DIAG
  if (heapcheck() == _HEAPCORRUPT && ad_printf)
  {
    (*ad_printf)("Leaving dvector * dmat dvec is corrupted.\n");
  }
  else
  {
    (*ad_printf)("Leaving dvector * dmat dvec   Heap is OK.\n");
  }
#endif

  return results;
}
/**
Returns product of AB where A is a dmatrix and B is a dmatrix.

\param A dmatrix
\param B dmatrix
*/
dmatrix operator*(const dmatrix& A, const dmatrix& B)
{
   if (A.colmin() != B.rowmin() || A.colmax() != B.rowmax())
   {
     cerr << " Incompatible array bounds in "
          << "dmatrix operator*(const dmatrix& A, const dmatrix& B)\n";
     ad_exit(1);
   }
   dmatrix results(A.rowmin(), A.rowmax(), B.colmin(), B.colmax());
   for (int j= B.colmin(); j<= B.colmax(); j++)
   {
     dvector col = column(B, j);
     for (int i= A.rowmin(); i<= A.rowmax(); i++)
     {
       results.elem(i,j) = A.elem(i) * col;
     }
   }
   return results;
 }
/*
dmatrix operator*(const dmatrix& m1, const dmatrix& m2 )
 {
   if (m1.colmin() != m2.rowmin() || m1.colmax() != m2.rowmax())
   {
     cerr << " Incompatible array bounds in "
     "dmatrix  operator * (const dmatrix& x, const dmatrix& m)\n";
     ad_exit(21);
   }

   dmatrix tmp(m1.rowmin(),m1.rowmax(), m2.colmin(), m2.colmax());

   double sum;
   const double ** temp_col=
         (const double **) malloc(m2.rowsize() * sizeof(double **));
   temp_col-=m2.rowmin();


   for (int j=m2.colmin(); j<=m2.colmax(); j++)
   {
     for (int k=m2.rowmin(); k<=m2.rowmax(); k++)
     {
       temp_col[k]=&(m2.elem(k,j));
     }

     for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
     {
       sum=0;

       const dvector& temp_row = m1.elem(i);

       for (k=m1.colmin(); k<=m1.colmax(); k++)
       {
         sum+=temp_row.elem(k) * *(temp_col[k]);
       }
       tmp.elem(i,j)=sum;
     }
   }
   temp_col+=m2.rowmin();
   free ((char*)temp_col);
   return(tmp);
 }
*/
