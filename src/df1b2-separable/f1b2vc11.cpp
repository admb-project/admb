/*
 * $Id: f1b2vc11.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2012 ADMB Foundation
 */

#include <df1b2fun.h>

df1b2vector df1b2vector::operator() (const ivector & iv)
{
  int lb=iv.indexmin();
  int ub=iv.indexmax();
  df1b2vector tmp;
  if (lb<=ub)
    tmp.noallocate(lb,ub);

  for (int i=lb;i<=ub;i++)
  {
    tmp(i)=(*this)(iv(i));    
    tmp(i).get_ind_index()=(*this)(iv(i)).get_ind_index();    
  }
  return tmp;
}
