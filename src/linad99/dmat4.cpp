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
 struct dvec_ptr_ptr
 {
   void ** m;
 };

/**
 * Description not yet available.
 * \param
 */
 dmatrix& dmatrix::operator= (_CONST dmatrix& m1)
 {
   if (allocated(*this))
   {
     if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() ||
       colmin() != m1.colmin() || colmax() != m1.colmax() )
     {
       cerr << " Incompatible array bounds in dmatrix& operator = (_CONST dmatrix&)\n";
       ad_exit(21);
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
 * Description not yet available.
 * \param
 */
 dmatrix& dmatrix::operator+= (_CONST dmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dmatrix& operator += (_CONST dmatrix&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) += m1.elem(i);
   }
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
 dmatrix& dmatrix::operator-= (_CONST dmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dmatrix& operator -= (_CONST dmatrix&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) -= m1.elem(i);
   }
   return(*this);
 }
