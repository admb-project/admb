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
   void d4_array::operator /= (CGNU_DOUBLE d)
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
   }  

/**
 * Description not yet available.
 * \param
 */
   d4_array operator / (_CONST d4_array& m, CGNU_DOUBLE d)
   {
     d4_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d4_array operator / ( CGNU_DOUBLE d,_CONST d4_array& m)
   {
     d4_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }  
