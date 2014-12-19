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
   void d4_array::operator /= (double d)
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
d4_array operator/(const d4_array& m, double d)
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
d4_array operator/(double d, const d4_array& m)
{
  d4_array tmp;
  tmp.allocate(m);
  for (int i = tmp.indexmin(); i <= tmp.indexmax(); i++)
  {
    for (int j=tmp(i).indexmin(); j <= tmp(i).indexmax(); j++)
    {
      tmp(i, j) = d / m(i, j);
    }
  }
  return tmp;
}
