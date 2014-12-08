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
d4_array sqrt(const d4_array& m)
{
  d4_array tmp;
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
d4_array exp(const d4_array& m)
{
  d4_array tmp;
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
d4_array mfexp(const d4_array& m)
{
  d4_array tmp;
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
d4_array log(const d4_array& m)
{
  d4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=log(m(i));
  }
  return tmp;
}
