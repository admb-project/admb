/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

 void imatrix::initialize (void)
 {
   for (int i=rowmin();i<=rowmax();i++)
   {
     (*this)(i).initialize();
   }
 }


 imatrix trans(const imatrix& m1)
 {
   imatrix tmp(m1.colmin(),m1.colmax(),m1.rowmin(),m1.rowmax());

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     for (int j=m1.colmin(); j<=m1.colmax(); j++)
     {
       tmp[j][i]=m1[i][j];
     }
   }
   return (tmp);
 }


