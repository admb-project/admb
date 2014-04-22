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
dvar_matrix operator-(const dvar_matrix& m1, const dmatrix& m2 )
 {
   RETURN_ARRAYS_INCREMENT();

   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in "
     "dvar_matrix operator+(const dvar_matrix& x, const dmatrix& m)\n";
     ad_exit(21);
   }

   dvar_matrix tmp;
   tmp.allocate(m1.indexmin(),m1.indexmax());

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp[i]=m1[i]-m2[i];
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix operator-(const dvar_matrix& m1, const dvar_matrix& m2)
 {
   RETURN_ARRAYS_INCREMENT();

   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in "
     "dvar_matrix operator+(const dvar_matrix& x, const dvar_matrix& m)\n";
     ad_exit(21);
   }

   dvar_matrix tmp;
   tmp.allocate(m1.indexmin(),m1.indexmax());

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp[i]=m1[i]-m2[i];
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix operator-(const dmatrix& m1, const dvar_matrix& m2)
 {
   RETURN_ARRAYS_INCREMENT();

   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in "
     "dvar_matrix operator+(const dmatrix& x, const dvar_matrix& m)\n";
     ad_exit(21);
   }

   dvar_matrix tmp;
   tmp.allocate(m2.indexmin(),m2.indexmax());

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp[i]=m1[i]-m2[i];
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }
