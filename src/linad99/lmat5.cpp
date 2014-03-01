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
lmatrix& lmatrix::operator=(const lmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() ||
     colmin() != m1.colmin() || colmax() != m1.colmax() )
   {
     cerr << " Incompatible array bounds in "
     "imatrix& operator = (const imatrix&)\n";
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
lmatrix& lmatrix::operator=(const imatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() ||
     colmin() != m1.colmin() || colmax() != m1.colmax() )
   {
     cerr << " Incompatible array bounds in "
     "imatrix& operator=(const imatrix&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     *(m+i) = m1[i];
   }
   return(*this);
 }

