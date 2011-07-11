/*
 * $Id: f3arr13.cpp 946 2011-01-12 23:52:45Z johnoel $
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
 dvar3_array& dvar3_array::operator= (_CONST d3_array& m1)
 {
   if (slicemin() != m1.slicemin() || slicemax() != m1.slicemax())
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator = (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=slicemin();i<=slicemax();i++)
   {
     elem(i)=m1.elem(i);
   }
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar3_array& dvar3_array::operator= (double x)
 {
   for (int i=slicemin();i<=slicemax();i++)
   {
     elem(i)=x;
   }
   return(*this);
 }
