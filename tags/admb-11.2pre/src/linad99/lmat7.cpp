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
#include "admb_messages.h"

/* JCA: Need sum(lvector)
AD_LONG_INT sum(const lmatrix& m)
{
  AD_LONG_INT ssum=0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ssum+=sum(m(i));
  }
  return ssum;
}
*/

/**
 * Description not yet available.
 * \param
 */
AD_LONG_INT colsum(const lmatrix& m,int col)
{
  if (col < m.colmin() || col > m.colmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Row out of bounds",
    "AD_LONG_INT colsum(const lmatrix& m,int col)",
    m.colmin(), m.colmax(), col);
  }
  AD_LONG_INT isum=0;
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    isum+=m(i,col);
  }
  return isum;
}

/**
 * Description not yet available.
 * \param
 */
lvector column(const lmatrix& m,int col)
{
  if (col < m.colmin() || col > m.colmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Row out of bounds",
    "lvector column(const lmatrix& m,int col)",
    m.colmin(), m.colmax(), col);
  }
  int mmin=m.rowmin();
  int mmax=m.rowmax();
  lvector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=m(i,col);
  }
  return tmp;
}
