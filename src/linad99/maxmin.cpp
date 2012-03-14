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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
double max(CGNU_DOUBLE u, CGNU_DOUBLE v)
{
  return u > v ? u : v;
}

/**
 * Description not yet available.
 * \param
 */
double min(CGNU_DOUBLE u, CGNU_DOUBLE v)
{
  return u < v ? u : v;
}

/**
 * Description not yet available.
 * \param
 */
unsigned long max(unsigned long u, unsigned long v)
{
  return u > v ? u : v;
}

/**
 * Description not yet available.
 * \param
 */
unsigned long min(unsigned long u, unsigned long v)
{
  return u < v ? u : v;
}
