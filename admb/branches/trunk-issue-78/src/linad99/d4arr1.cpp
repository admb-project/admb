/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"
#include <d4arr.hpp>

d4_array sqrt(_CONST d4_array& m)
{
  d4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=sqrt(m(i));
  }
  return tmp;
}

d4_array exp(_CONST d4_array& m)
{
  d4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=exp(m(i));
  }
  return tmp;
}

d4_array mfexp(_CONST d4_array& m)
{
  d4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=mfexp(m(i));
  }
  return tmp;
}

d4_array log(_CONST d4_array& m)
{
  d4_array tmp;
  tmp.allocate(m);
  for (int i=tmp.hslicemin();i<=tmp.hslicemax();i++)
  {
    tmp(i)=log(m(i));
  }
  return tmp;
}

