/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifdef DIAG
  int heapcheck();
  #define _HEAPCORRUPT 1
#endif

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

#ifndef OPT_LIB
  if (A.indexmin() != B.rowmin() || A.indexmax() != B.rowmax())
  {
    cerr << " Incompatible array bounds in "
         << "dvector operator*(const dvector& A, const dmatrix& B)\n";
    ad_exit(1);
  }
#endif

  int imin = A.indexmin();
  int imax = A.indexmax();
  int jmin = B.colmin();
  int jmax = B.colmax();

  dvector results(jmin, jmax);

  double* presultsj = results.get_v() + jmin;
  for (int j = jmin; j <= jmax; ++j)
  {
    *presultsj = 0.0;

    const double* pAi = A.get_v() + imin;
    const dvector* pBi = &B(imin);
    for (int i = imin; i <= imax; ++i)
    {
      *presultsj += *pAi * *(pBi->get_v() + j);

      ++pAi;
      ++pBi;
    }
    ++presultsj;
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

  int imin = A.rowmin();
  int imax = A.rowmax();
  int jmin = B.indexmin();
  int jmax = B.indexmax();

#ifndef OPT_LIB
   if (jmin != A.colmin() || jmax != A.colmax())
   {
     cerr << " Incompatible array bounds in "
          << "dvector operator*(const dmatrix& A, const dvector& B)\n";
     ad_exit(1);
   }
#endif

   dvector results(imin, imax);

   double* presultsi = results.get_v() + imin;
   const dvector* pAi = &A(imin);
   for (int i = imin; i <= imax; ++i)
   {
     *presultsi = 0.0;

     double* pBj = B.get_v() + jmin;
     double* pAij = pAi->get_v() + jmin;
     for (int j = jmin; j <= jmax; ++j)
     {
       *presultsi += *pAij * *pBj;

       ++pBj;
       ++pAij;
     }
     ++presultsi;
     ++pAi;
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
  int imin = A.rowmin();
  int imax = A.rowmax();
  int jmin = B.colmin();
  int jmax = B.colmax();
#ifndef OPT_LIB
  //if (imin != jmin || imax != jmax)
  if (A.colmin() != B.rowmin() || A.colmax() != B.rowmax())
  {
     cerr << " Incompatible array bounds in "
          << "dmatrix operator*(const dmatrix& A, const dmatrix& B)\n";
     ad_exit(1);
  }
#endif

  dmatrix results(imin, imax, jmin, jmax);
  for (int j = jmin; j <= jmax; ++j)
  {
    dvector col = column(B, j);
    const dvector* pAi = &A(imin);
    dvector* presultsi = &results(imin);
    for (int i = imin; i <= imax; ++i)
    {
      *(presultsi->get_v() + j) = *pAi * col;

      ++pAi;
      ++presultsi;
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
