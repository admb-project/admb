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
 dvar_matrix& dvar_matrix::operator+= (_CONST dvar_matrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator += (_CONST dvar_vector&)\n";
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
 dvar_matrix& dvar_matrix::operator+= (_CONST dmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator += (_CONST dvar_vector&)\n";
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
 dvar_matrix& dvar_matrix::operator-= (_CONST dvar_matrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator -= (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) -= m1.elem(i);
   }
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix& dvar_matrix::operator-= (_CONST dmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator -= (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) -= m1.elem(i);
   }
   return(*this);
 }
