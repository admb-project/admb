/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

 dmatrix  operator - (_CONST dmatrix& m1,_CONST dmatrix& m2 )
 {
   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in dmatrix  operator + (_CONST dmatrix& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }

   dmatrix tmp;
   tmp.allocate(m1.rowmin(),m1.rowmax());

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp.elem(i)=m1.elem(i)-m2.elem(i);
   }
   return(tmp);
 }      

 dmatrix  operator + (_CONST dmatrix& m1,_CONST dmatrix& m2 )
 {
   if (m1.colmin() != m2.colmin() || m1.colmax() != m2.colmax())
   {
     cerr << " Incompatible array bounds in dmatrix  operator + (_CONST dmatrix& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }

   dmatrix tmp;
   tmp.allocate(m1.rowmin(),m1.rowmax());

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp.elem(i)=m1.elem(i)+m2.elem(i);
   }
   return(tmp);
 }      

 dmatrix  operator + ( CGNU_DOUBLE d,_CONST dmatrix& m2 )
 {
   dmatrix tmp;
   tmp.allocate(m2.rowmin(),m2.rowmax());
   for (int i=m2.rowmin(); i<=m2.rowmax(); i++)
   {
     tmp.elem(i)=d+m2.elem(i);
   }
   return(tmp);
 }      

 dmatrix  operator - ( CGNU_DOUBLE d,_CONST dmatrix& m2 )
 {
   dmatrix tmp;
   tmp.allocate(m2.rowmin(),m2.rowmax());
   for (int i=m2.rowmin(); i<=m2.rowmax(); i++)
   {
     tmp.elem(i)=d-m2.elem(i);
   }
   return(tmp);
 }      

 dmatrix  operator * ( CGNU_DOUBLE d,_CONST dmatrix& m2 )
 {
   dmatrix tmp;
   tmp.allocate(m2.rowmin(),m2.rowmax());
   for (int i=m2.rowmin(); i<=m2.rowmax(); i++)
   {
     tmp.elem(i)=d*m2.elem(i);
   }
   return(tmp);
 }      

 dmatrix  operator + (_CONST dmatrix& m1, CGNU_DOUBLE d )
 {
   dmatrix tmp;
   tmp.allocate(m1.rowmin(),m1.rowmax());
   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp.elem(i)=m1.elem(i)+d;
   }
   return(tmp);
 }      

 dmatrix  operator - (_CONST dmatrix& m1, CGNU_DOUBLE d )
 {
   dmatrix tmp;
   tmp.allocate(m1.rowmin(),m1.rowmax());
   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp.elem(i)=m1.elem(i)-d;
   }
   return(tmp);
 }      

 dmatrix  operator * (_CONST dmatrix& m1, CGNU_DOUBLE d )
 {
   dmatrix tmp;
   tmp.allocate(m1.rowmin(),m1.rowmax());
   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     tmp.elem(i)=m1.elem(i)*d;
   }
   return(tmp);
 }      

