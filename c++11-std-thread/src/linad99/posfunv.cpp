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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable posfun(const dvariable &x, const double eps, const prevariable& _pen)
{
  dvariable& pen= (dvariable&) _pen;
  if (x>=eps) 
  {
    return x;
  }
  else
  {
    //dvariable y=1.0-x/eps;
    pen+=.01*square(x-eps);
    return eps/(2-x/eps);
  }
}

/**
 * Description not yet available.
 * \param
 */
dvariable posfun(const dvariable &x, const double eps, const dvariable& _pen)
{
  dvariable& pen= (dvariable&) _pen;
  if (x>=eps) 
  {
    return x;
  }
  else
  {
    //dvariable y=1.0-x/eps;
    pen+=.01*square(x-eps);
    return eps/(2-x/eps);
  }
}

/**
 * Description not yet available.
 * \param
 */
dvariable posfun2(const dvariable &x, const double eps, const prevariable& _pen)
{
  dvariable& pen= (dvariable&) _pen;
  if (x>=eps) 
  {
    return x;
  }
  else
  {
    dvariable y=eps-x;
    dvariable tmp=y/eps;
    dvariable tmp2=tmp*tmp;
    dvariable tmp3=tmp2*tmp;
    pen+=.01*cube(tmp3);
    return eps/(1.0+tmp+tmp2+tmp3);
  }
}

/**
 * Description not yet available.
 * \param
 */
dvariable dfposfun(const prevariable&x,const double eps)
{
  if (x>=eps) 
  {
    return 1;
  }
  else
  {
    //double z=eps/(2-x/eps);
    dvariable dfx=1.0/square(2-x/eps);
    return dfx;
  }
}
