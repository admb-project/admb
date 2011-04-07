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
 dvar_matrix  operator + (_CONST dvar_matrix& m1,_CONST dmatrix& m2 )
 {
   RETURN_ARRAYS_INCREMENT();

   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in dvar_matrix  operator + (_CONST dvar_matrix& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }

   kkludge_object kk;
   dvar_matrix tmp(m1.rowmin(),m1.rowmax(),kk);

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp(i)=m1(i)+m2(i);
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }      

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix  operator + (_CONST dvar_matrix& m1,_CONST dvar_matrix& m2 )
 {
   RETURN_ARRAYS_INCREMENT();

   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in dvar_matrix  operator + (_CONST dvar_matrix& x,_CONST dvar_matrix& m)\n";
     ad_exit(21);
   }
   kkludge_object kk;
   dvar_matrix tmp(m1.rowmin(),m1.rowmax(),kk);
   //dvar_matrix tmp;
   //tmp.allocate(m1);

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp(i)=m1(i)+m2(i);
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix  operator + (_CONST dmatrix& m1,_CONST dvar_matrix& m2 )
 {
   RETURN_ARRAYS_INCREMENT();

   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in dvar_matrix  operator + (_CONST dmatrix& x,_CONST dvar_matrix& m)\n";
     ad_exit(21);
   }
   kkludge_object kk;
   dvar_matrix tmp(m1.rowmin(),m1.rowmax(),kk);
   
   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp(i)=m1(i)+m2(i);
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }
