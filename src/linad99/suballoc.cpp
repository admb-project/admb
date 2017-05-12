/**
Author: David Fournier
Copyright (c) 2008-2017 Regents of the University of California
*/
#include "fvar.hpp"

/**
Returns true if varvec was not allocated,
otherwise false.

\param v variable vector
*/
int sub_unallocated(const dvar_vector& v)
{
  return !allocated(v);
}
/**
Returns true if any of the sub vectors of matrix m was not allocated,
otherwise false.

\param m variable dvar_matrix
*/
int sub_unallocated(const dvar_matrix& m)
{
  int isallocated = allocated(m);
  if (isallocated)
  {
    int mmin = m.indexmin();
    int mmax = m.indexmax();
    for (int i = mmin; i <= mmax; ++i)
    {
      if (sub_unallocated(m(i)))
      {
        isallocated = false;
        break;
      }
    }
  }
  return !isallocated;
}
/**
Returns true if any of the sub vectors of arr3 was not allocated,
otherwise false.

\param arr3 variable dvar3_array
*/
int sub_unallocated(const dvar3_array& arr3)
{
  int isallocated = allocated(arr3);
  if (isallocated)
  {
    int mmin = arr3.indexmin();
    int mmax = arr3.indexmax();
    for (int i = mmin; i <= mmax; ++i)
    {
      if (sub_unallocated(arr3(i)))
      {
        isallocated = false;
        break;
      }
    }
  }
  return !isallocated;
}
/**
Returns true if any of the sub vectors of arr4 was not allocated,
otherwise false.

\param arr4 variable dvar4_array
*/
int sub_unallocated(const dvar4_array& arr4)
{
  int isallocated = allocated(arr4);
  if (isallocated)
  {
    int mmin = arr4.indexmin();
    int mmax = arr4.indexmax();
    for (int i = mmin; i <= mmax; ++i)
    {
      if (sub_unallocated(arr4(i)))
      {
        isallocated = false;
        break;
      }
    }
  }
  return !isallocated;
}
/**
Returns true if any of the sub vectors of arr5 was not allocated,
otherwise false.

\param arr5 variable dvar5_array
*/
int sub_unallocated(const dvar5_array& arr5)
{
  int isallocated = allocated(arr5);
  if (isallocated)
  {
    int mmin = arr5.indexmin();
    int mmax = arr5.indexmax();
    for (int i = mmin; i <= mmax; ++i)
    {
      if (sub_unallocated(arr5(i)))
      {
        isallocated = false;
        break;
      }
    }
  }
  return !isallocated;
}
/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const dvector& m)
  {
    int iflag = 0;
    if (!allocated(m)) iflag=1;
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const dmatrix& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
    for (int i=mmin;i<=mmax;i++)
    {
      if (!allocated(m(i)))
      {
        iflag=1;
        break;
      }
    }
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const d3_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
    for (int i=mmin;i<=mmax;i++)
    {
      if (sub_unallocated(m(i)))
      {
        iflag=1;
        break;
      }
    }
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const d4_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
    for (int i=mmin;i<=mmax;i++)
    {
      if (sub_unallocated(m(i)))
      {
        iflag=1;
        break;
      }
    }
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const d5_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
    for (int i=mmin;i<=mmax;i++)
    {
      if (sub_unallocated(m(i)))
      {
        iflag=1;
        break;
      }
    }
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
int sub_unallocated(const ivector& m)
{
  int iflag = 0;
  if (!allocated(m)) iflag=1;
  return iflag;
}

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const imatrix& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
    for (int i=mmin;i<=mmax;i++)
    {
      if (!allocated(m(i)))
      {
        iflag=1;
        break;
      }
    }
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const i3_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
    for (int i=mmin;i<=mmax;i++)
    {
      if (sub_unallocated(m(i)))
      {
        iflag=1;
        break;
      }
    }
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const i4_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
    for (int i=mmin;i<=mmax;i++)
    {
      if (sub_unallocated(m(i)))
      {
        iflag=1;
        break;
      }
    }
    return iflag;
  }
