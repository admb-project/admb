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

/**
 * Description not yet available.
 * \param
 */
dvariable sum(_CONST dvar5_array& m)
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


/**
 * Description not yet available.
 * \param
 */
dvar5_array sqrt(_CONST dvar5_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=sqrt(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar5_array exp(_CONST dvar5_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=exp(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar5_array mfexp(_CONST dvar5_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=mfexp(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar5_array log(_CONST dvar5_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=log(m(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
