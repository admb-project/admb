/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

int operator + (int n,data_int v)
{
  return n+v.val;
}

int operator + (data_int v,int n)
{
  return n+v.val;
}

int operator + (data_int v,data_int n)
{
  return n.val+v.val;
}

data_int& data_int::operator = (_CONST int xx)
{
  val=xx;
  return *this;
}
 

ad_integer::ad_integer(_CONST data_int& _d) : d(int(*(data_int*)(&_d))) {}

/*
index_type::index_type(_CONST data_int& _x)
{
  p = new number_index(int((data_int&)(_x)));
}
*/
