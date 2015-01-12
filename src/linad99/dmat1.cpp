/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

 dvector  operator * (_CONST dvector& x,_CONST dmatrix& m)
 {
#ifdef DIAG
     if( heapcheck() == _HEAPCORRUPT )
     {
        if (ad_printf) (*ad_printf)( "Entering dvector * dvec dmat is corrupted.\n" );
     }
     else
     {
        if (ad_printf) (*ad_printf)( "Entering dvector * dvec dmat  Heap is OK.\n" );
     }
#endif

   if (x.indexmin() != m.rowmin() || x.indexmax() != m.rowmax())
   {
     cerr << " Incompatible array bounds in dvector  operator * (_CONST dvector& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }
   dvector tmp(m.colmin(),m.colmax());

   for (int j=m.colmin(); j<=m.colmax(); j++)
   {
     tmp[j]=0;
     for (int i=x.indexmin(); i<=x.indexmax(); i++)
     {
       tmp[j]+=x[i]*m[i][j];
     }
   }
#ifdef DIAG
     if( heapcheck() == _HEAPCORRUPT )
     {
        if (ad_printf) (*ad_printf)( "Leaving dvector * dvec dmat is corrupted.\n" );
     }
     else
     {
        if (ad_printf) (*ad_printf)( "Leaving dvector * dvec dmat  Heap is OK.\n" );
     }
#endif
   return(tmp);
 }      

 dvector  operator * (_CONST dmatrix& m,_CONST dvector& x )
 {
#ifdef DIAG
     if( heapcheck() == _HEAPCORRUPT )
     {
        if (ad_printf) (*ad_printf)( "Entering dvector * dmat dvec is corrupted.\n" );
     }
     else
     {
        if (ad_printf) (*ad_printf)( "Entering dvector * dmat dvec   Heap is OK.\n" );
     }
#endif
   if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
   {
     cerr << " Incompatible array bounds in dvector  operator * (_CONST dvector& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }

   dvector tmp(m.rowmin(),m.rowmax());

   for (int i=m.rowmin(); i<=m.rowmax(); i++)
   {
     tmp[i]=0;
     for (int j=x.indexmin(); j<=x.indexmax(); j++)
     {
       tmp[i]+=m[i][j]*x[j];
     }
   }
#ifdef DIAG
     if( heapcheck() == _HEAPCORRUPT )
     {
        if (ad_printf) (*ad_printf)( "Leaving dvector * dmat dvec is corrupted.\n" );
     }
     else
     {
        if (ad_printf) (*ad_printf)( "Leaving dvector * dmat dvec   Heap is OK.\n" );
     }
#endif
   return(tmp);
 }      

 dmatrix  operator * (const dmatrix& m1,const dmatrix& m2 )
 {
   if (m1.colmin() != m2.rowmin() || m1.colmax() != m2.rowmax())
   {
     cerr << " Incompatible array bounds in dmatrix  operator * (_CONST dmatrix& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }
   dmatrix tmp(m1.rowmin(),m1.rowmax(), m2.colmin(), m2.colmax());
   double sum;
   for (int j=m2.colmin(); j<=m2.colmax(); j++)
   {
     dvector m2col=column(m2,j);
     for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
     {
       sum=0;
       const dvector& temp_row = m1.elem(i);
       sum=m1.elem(i) * m2col;
       tmp.elem(i,j)=sum;
     }
   }
   return(tmp);
 }      

/*

 dmatrix  operator * (_CONST dmatrix& m1,_CONST dmatrix& m2 )
 {
   if (m1.colmin() != m2.rowmin() || m1.colmax() != m2.rowmax())
   {
     cerr << " Incompatible array bounds in dmatrix  operator * (_CONST dmatrix& x,_CONST dmatrix& m)\n";
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

       _CONST dvector& temp_row = m1.elem(i);

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

