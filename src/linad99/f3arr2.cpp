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
dvariable norm(const dvar3_array& m)
    {
      RETURN_ARRAYS_INCREMENT();
      dvariable tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
        tmp+=norm2(m(k));
      }
      tmp=sqrt(tmp);
      RETURN_ARRAYS_DECREMENT();
      return tmp;
    }

/**
 * Description not yet available.
 * \param
 */
dvariable norm2(const dvar3_array& m)
    {
      RETURN_ARRAYS_INCREMENT();
      dvariable tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
        tmp+=norm2(m(k));
      }
      RETURN_ARRAYS_DECREMENT();
      return tmp;
    }
dvariable sumsq(const dvar3_array& m) {return(norm2(m));}

/**
Computes exp of each element in m to a dvar3_array.

@param m dvar3_array
*/
dvar3_array exp(const dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=exp(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Computes log of each element in m to a dvar3_array.

@param m dvar3_array
*/
dvar3_array log(const dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=log(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Computes sin of each element in m to a dvar3_array.

@param m dvar3_array
*/
dvar3_array sin(const dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=sin(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Computes cos of each element in m to a dvar3_array.

@param m dvar3_array
*/
dvar3_array cos(const dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=cos(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Computes square root of each element in m to a dvar3_array.

@param m dvar3_array
*/
dvar3_array sqrt(const dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=sqrt(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
/**
Computes square of each element in m to a dvar3_array.

@param m dvar3_array
 */
dvar3_array sqr(const dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar3_array tmp;
  tmp.allocate(m);
  for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
  {
    tmp(i)=sqr(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar3_array tan(const dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=tan(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array elem_prod(const dvar3_array& m1, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_prod(m1(i),m2(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array elem_div(const dvar3_array& m1, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_div(m1(i),m2(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator+(const dvar3_array& m1,const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator-(const dvar3_array& m1, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array elem_prod(const d3_array& m1, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_prod(m1(i),m2(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array elem_div(const d3_array& m1, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_div(m1(i),m2(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator+(const d3_array& m1, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar3_array operator-(const d3_array& m1, const dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }
