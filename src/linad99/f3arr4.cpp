/**
\file
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator-(const double d, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d-m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }
/**
Return computed variable mean of variable 3-dimensional array m.
*/
dvariable mean(const dvar3_array& m)
{
  dvariable tmp;
  const int count = size_count(m);
  if (count > 0)
  {
    tmp = sum(m) / count;
  }
  else
  {
    cerr << "Error[" << __FILE__ << ':' << __LINE__ << "]:"
            "Division by zero in mean(dvar3_array)."
         << '\n';
    ad_exit(1);
  }
  return tmp;
}
