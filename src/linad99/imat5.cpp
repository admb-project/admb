/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
imatrix& imatrix::operator=(const imatrix& m1)
 {
   if (allocated(*this))
   {
     if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() ||
       colmin() != m1.colmin() || colmax() != m1.colmax() )
     {
       cerr << " Incompatible array bounds in "
       "imatrix& operator=(const imatrix&)\n";
       ad_exit(1);
     }

     if (m != m1.m)            // check for condition that both matrices
     {                         // point to the same object
       for (int i=rowmin();i<=rowmax();i++)
       {
         *(m+i) = m1[i];
       }
     }
   }
   else
   {
     index_min=m1.index_min;
     index_max=m1.index_max;
     shape=m1.shape;
     if (shape)
     {
       (shape->ncopies)++;
     }
     m = m1.m;
   }
   return(*this);
 }
/**
Assigns value to all elements of imatrix.

\param value integer
*/
imatrix& imatrix::operator=(const int value)
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) = value;
  }
  return *this;
}
