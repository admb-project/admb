/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include "fvar.hpp"

/**
Returns d3_array results with computed log from elements in arr3.

\param arr3 d3_array
*/
d3_array log(const d3_array& arr3)
{
  d3_array results;
  results.allocate(arr3);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = log(arr3(i));
  }
  return results;
}
/**
Returns d3_array results with computed exp from elements in arr3.

\param arr3 d3_array
*/
d3_array exp(const d3_array& arr3)
{
  d3_array results;
  results.allocate(arr3);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = exp(arr3(i));
  }
  return results;
}
/**
Returns d3_array results with computed sin from elements in arr3.

\param arr3 d3_array
*/
d3_array sin(const d3_array& arr3)
{
  d3_array results;
  results.allocate(arr3);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = sin(arr3(i));
  }
  return results;
}
/**
Returns d3_array results with computed cos from elements in arr3.

\param arr3 d3_array
*/
d3_array cos(const d3_array& arr3)
{
  d3_array results;
  results.allocate(arr3);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = cos(arr3(i));
  }
  return results;
}
/**
Returns d3_array results with computed tan from elements in arr3.

\param arr3 d3_array
*/
d3_array tan(const d3_array& arr3)
{
  d3_array results;
  results.allocate(arr3);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = tan(arr3(i));
  }
  return results;
}
/**
Returns d3_array results with computed elements product of 
a(i, j, k) * b(i, j, k).

a and b should be allocated and have the same dimensions.

\param a d3_array
\param b d3_array
*/
d3_array elem_prod(const d3_array& a, const d3_array& b)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = elem_prod(a(i), b(i));
  }
  return results;
}
/**
Returns d3_array results with computed elements division of 
a(i, j, k) / b(i, j, k).

a and b should be allocated and have the same dimensions.
All elements in b should not be zero.

\param a d3_array
\param b d3_array
*/
d3_array elem_div(const d3_array& a, const d3_array& b)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = elem_div(a(i), b(i));
  }
  return results;
}
/**
Returns d3_array results with computed elements addition of 
a(i, j, k) + b(i, j, k).

a and b should be allocated and have the same dimensions.
All elements in b should not be zero.

\param a d3_array
\param b d3_array
*/
d3_array operator+(const d3_array& a, const d3_array& b)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = a(i) + b(i);
  }
  return results;
}
/**
Returns d3_array results with computed elements addition of 
a(i, j, k) + b(i, j, k).

a and b should be allocated and have the same dimensions.
All elements in b should not be zero.

\param a d3_array
\param b d3_array
*/
d3_array operator-(const d3_array& a, const d3_array& b)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = a(i) - b(i);
  }
  return results;
}
/**
Return sum of squared elements in a.

\param a d3_array
*/
double norm2(const d3_array& a)
{
  double sum = 0.0;
  for (int i = a.slicemin(); i <= a.slicemax(); ++i)
  {
    sum += norm2(a(i));
  }
  return sum;
}
/*
Return sum of squared elements in a.

\param a d3_array
*/
double sumsq(const d3_array& a)
{
  return norm2(a);
}
/**
Return computed norm value of a.

\param a d3_array
*/
double norm(const d3_array& a)
{
  return sqrt(norm2(a));
}
/**
Returns d3_array results with adding elements in a to value
value + a(i, j, k).

\param a d3_array
 */
d3_array operator+(double value, const d3_array& a)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = value + a(i);
  }
  return results;
}
/**
Returns d3_array results with subtracting elements in a to value
value - a(i, j, k).

\param a d3_array
 */
d3_array operator-(double value, const d3_array& a)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = value - a(i);
  }
  return results;
}
/**
Returns d3_array results with subtracting elements in a to value
a(i, j, k) + value.

\param a d3_array
*/
d3_array operator+(const d3_array& a, double value)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = a(i) + value;
  }
  return results;
}
/**
Returns d3_array results with subtracting elements in a to value
a(i, j, k) - value.

\param a d3_array
*/
d3_array operator-(const d3_array& a, double value)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = a(i) - value;
  }
  return results;
}
/**
Returns d3_array results of multiplying elements in a with value
a(i, j, k) * value.

\param a d3_array
*/
d3_array operator*(const d3_array& a, double value)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = a(i) * value;
  }
  return results;
}
/**
Returns d3_array results of multiplying value by elements in a
value * a(i, j, k).

\param a d3_array
*/
d3_array operator*(double value, const d3_array& a)
{
  d3_array results;
  results.allocate(a);
  for (int i = results.slicemin(); i <= results.slicemax(); ++i)
  {
    results(i) = value * a(i);
  }
  return results;
}
