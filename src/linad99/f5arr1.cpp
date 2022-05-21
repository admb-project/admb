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
dvariable sum(const dvar5_array& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();

  dvariable tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}


/**
 * Description not yet available.
 * \param
 */
dvar5_array sqrt(const dvar5_array& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=sqrt(m(i));
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar5_array exp(const dvar5_array& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=exp(m(i));
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar5_array mfexp(const dvar5_array& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=mfexp(m(i));
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar5_array log(const dvar5_array& m)
{
  gradient_structure* gs = gradient_structure::get();
  gs->RETURN_ARRAYS_INCREMENT();
  dvar5_array tmp;
  tmp.allocate(m);
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tmp(i)=log(m(i));
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
