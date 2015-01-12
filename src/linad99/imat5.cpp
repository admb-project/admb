/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
 imatrix& imatrix::operator= (_CONST imatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() ||
     colmin() != m1.colmin() || colmax() != m1.colmax() )
   {
     cerr << rowmin() << endl;
     cerr << rowmax() << endl;
     cerr << m1.rowmin() << endl;
     cerr << m1.rowmax() << endl;
     cerr << colmin() << endl;
     cerr << colmax() << endl;
     cerr << m1.colmin() << endl;
     cerr << m1.colmax() << endl;
     cerr << " Incompatible array bounds in imatrix& operator = (_CONST imatrix&)\n";
     ad_exit(21);
   }

   if (m != m1.m)            // check for condition that both matrices
   {                         // point to the same object
     for (int i=rowmin();i<=rowmax();i++)
     {
       *(m+i) = m1[i];
     }
   }
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix& imatrix::operator= (const int n)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   for (int i=mmin;i<=mmax;i++)
   {
     (*this)(i) = n;
   }
   return(*this);
 }
