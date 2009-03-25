/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <fvar.hpp>

dvariable t_deviate(const prevariable& _x,const prevariable& _a)
{
  prevariable& x= (prevariable&)(_x);
  prevariable& a= (prevariable&)(_a);

  dvariable y=cumd_norm(x);

  y=.9999*y+.00005;

  dvariable z=inv_cumd_t(a,y);

  return z;
}

