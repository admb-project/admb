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
d3_array value(const dvar3_array& ar)
 {
   d3_array tmp;
   tmp.allocate(ar);
   for (int i=tmp.slicemin(); i<=tmp.slicemax(); i++)
   {
     tmp[i]=value(ar(i));
   }
   return tmp;
 }
/**
Allocate dvar3_array with the same dimensions as d3v.
*/
void d3_array::allocate(const dvar3_array& d3v)
{
  int sl = d3v.slicemin();
  int sh = d3v.slicemax();
  if ((shape = new three_array_shape(sl, sh)) == 0)
  {
    cerr << " Error allocating memory in d3_array::allocate.\n";
  }
  if ((t = new dmatrix[slicesize()]) == 0)
  {
    cerr << " Error allocating memory in d3_array::allocate.\n";
    ad_exit(21);
  }
  t -= slicemin();
  for (int i=sl; i<=sh; i++)
  {
    t[i].allocate(d3v(i));
  }
}
