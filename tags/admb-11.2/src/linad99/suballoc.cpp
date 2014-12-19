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
  int sub_unallocated(const dvar_vector& m)
  {
    int iflag = 0;
    if (!allocated(m)) iflag=1;
    return iflag;
  }

/**
 * Description not yet available.
 * \param
 */
  int sub_unallocated(const dvar_matrix& m)
  {
    int iflag=0;
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
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
  int sub_unallocated(const dvar3_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
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
  int sub_unallocated(const dvar4_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
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
  int sub_unallocated(const dvar5_array& m)
  {
    int iflag=0;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    if (!allocated(m))
    {
      iflag=1;
      return iflag;
    }
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
