/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

/**
 * Constructor to copy dimensions and row data pointers from m.
 *
 * \param m imatrix
 */
imatrix_position::imatrix_position(const imatrix& m)
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
 * Constructor to allocate empty valued rows and pointers to data
 * with dimension min to max.
 *
 * \param min minimum index
 * \param max maximum index
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
 * Copy constructor
 *
 * \param p other imatrix_position to copy
 */
imatrix_position::imatrix_position(const imatrix_position& p)
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
