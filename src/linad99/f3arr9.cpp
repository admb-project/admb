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
Returns dvar3_array with each element equal to the element product
m1(i, j, k) * m2(i, j, k). 

\param m1 left side variable array
\param m2 right side variable array
*/
dvar3_array elem_prod(const dvar3_array& m1, const d3_array& m2)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array result;
  result.allocate(m1);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = elem_prod(m1(i), m2(i));
  }
  RETURN_ARRAYS_DECREMENT();

  return result;
}
/**
Returns dvar3_array with each element equal to the element product
m1(i, j, k) / m2(i, j, k). 

\param m1 left side variable array
\param m2 right side variable array
*/
dvar3_array elem_div(const dvar3_array& m1, const d3_array& m2)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array result;
  result.allocate(m1);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = elem_div(m1(i), m2(i));
  }
  RETURN_ARRAYS_DECREMENT();

  return result;
}
/**
Returns dvar3_array with each element equal to m1(i, j, k) + m2(i, j, k). 

\param m1 left side variable array
\param m2 right side variable array
*/
dvar3_array operator+(const dvar3_array& m1, const d3_array& m2)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array result;
  result.allocate(m1);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = m1(i) + m2(i);
  }
  RETURN_ARRAYS_DECREMENT();

  return result;
}
/**
Returns dvar3_array with each element equal to m1(i, j, k) - m2(i, j, k). 

\param m1 left side variable array
\param m2 right side variable array
*/
dvar3_array operator-(const dvar3_array& m1, const d3_array& m2)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array result;
  result.allocate(m1);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = m1(i) - m2(i);
  }
  RETURN_ARRAYS_DECREMENT();

  return result;
}
/**
Returns dvar3_array with each element equal to d + m2(i, j, k). 

\param d left side variable
\param m2 right side variable array
*/
dvar3_array operator+(const dvariable& d, const d3_array& m2)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array result;
  result.allocate(m2);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = d + m2(i);
  }
  RETURN_ARRAYS_DECREMENT();

  return result;
}
/**
Returns dvar3_array with each element equal to d + m2(i, j, k). 

\param d left side variable
\param m2 right side variable array
*/
dvar3_array operator-(const dvariable& d, const d3_array& m2)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array result;
  result.allocate(m2);
  for (int i = result.slicemin(); i <= result.slicemax(); ++i)
  {
    result(i) = d - m2(i);
  }
  RETURN_ARRAYS_DECREMENT();

  return result;
}

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator*(const dvariable& d, const d3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator*(const dvariable& d, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator*(double d, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator-(const dvar3_array& m1, const dvariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator+(const dvar3_array& m1, const dvariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator+(double d, const dvar3_array& m1)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d+m1(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator*(const dvar3_array& m1, const dvariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)*d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator+(const dvariable& d1, const dvar3_array& m1)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);

     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+d1;
     }

     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }
