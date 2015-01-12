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
   d3_array operator / (_CONST d3_array& m, CGNU_DOUBLE d)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   void d3_array::operator /= ( CGNU_DOUBLE d)
   {
     for (int i=slicemin();i<=slicemax();i++)
     {
       (*this)(i)/=d;
     }
   }
