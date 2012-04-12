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
ivector diagonal(const imatrix& m)
{
  if (m.indexmin() != m.colmin() || m.indexmax() != m.colmax())
  {
    cerr << "Error matrix not square in function diagonal" << endl;
    exit(21);
  }
  int mmin=m.indexmin();
  int mmax=m.indexmax();
  ivector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
    tmp(i)=m(i,i);
  return tmp;
} 

/**
 * Description not yet available.
 * \param
 */
 imatrix  operator * (const imatrix& m1,const imatrix& m2 )
 {
   if (m1.colmin() != m2.rowmin() || m1.colmax() != m2.rowmax())
   {
     cerr << " Incompatible array bounds in imatrix  operator * (_CONST imatrix& x,_CONST imatrix& m)\n";
     ad_exit(21);
   }
   imatrix tmp(m1.rowmin(),m1.rowmax(), m2.colmin(), m2.colmax());
   //double sum;
   for (int j=m2.colmin(); j<=m2.colmax(); j++)
   {
     dvector m2col=column(m2,j);
     for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
     {
       tmp(i,j)=m1(i) * m2col;
     }
   }
   return(tmp);
 }      
