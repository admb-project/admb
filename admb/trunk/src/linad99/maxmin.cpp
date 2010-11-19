/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include <fvar.hpp>

double max(CGNU_DOUBLE u, CGNU_DOUBLE v)
{
  return u > v ? u : v;
}

double min(CGNU_DOUBLE u, CGNU_DOUBLE v)
{
  return u < v ? u : v;
}
unsigned long max(unsigned long u, unsigned long v)
{
  return u > v ? u : v;
}

unsigned long min(unsigned long u, unsigned long v)
{
  return u < v ? u : v;
}
