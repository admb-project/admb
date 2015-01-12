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
#include <d4arr.hpp>

/**
 * Description not yet available.
 * \param
 */
dvar4_array sqrt(_CONST dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=sqrt(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar4_array exp(_CONST dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=exp(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar4_array mfexp(_CONST dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=mfexp(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar4_array log(_CONST dvar4_array& m)
{
  dvar4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=log(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvariable sum(_CONST dvar4_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
