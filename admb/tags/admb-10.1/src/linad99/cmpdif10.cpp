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
#ifdef __TURBOC__
  #pragma hdrstop
#endif

/**
 * Description not yet available.
 * \param
 */
imatrix_position::imatrix_position(BOR_CONST imatrix& m)
  : lb(m.rowmin(),m.rowmax()), ub(m.rowmin(),m.rowmax()),
  ptr(m.rowmin(),m.rowmax())
{
  row_min=m.rowmin();
  row_max=m.rowmax();
  for (int i=row_min;i<=row_max;i++)
  {
    lb(i)=m(i).indexmin();
    ub(i)=m(i).indexmax();
    ptr(i)=m(i).get_v();
  }
}

/**
 * Description not yet available.
 * \param
 */
imatrix_position::imatrix_position(int min,int max)
  : lb(min,max), ub(min,max), ptr(min,max)
{
  row_min=min;
  row_max=max;
  for (int i=row_min;i<=row_max;i++)
  {
    lb(i)=0;
    ub(i)=-1;
    ptr(i)=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
imatrix_position::imatrix_position(BOR_CONST imatrix_position& p)
  : lb(p.row_min,p.row_max), ub(p.row_min,p.row_max),
    ptr(p.row_min,p.row_max)
{
  row_min=p.row_min;
  row_max=p.row_max;
  lb=p.lb;
  ub=p.ub;
  ptr=p.ptr;
  // cout << "ptr= " << ptr ;
}
