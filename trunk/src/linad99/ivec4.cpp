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
void ivector::fill(const char * s)
{
  dvector tmp(*this);
  tmp.fill(s);
  *this=ivector(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void lvector::fill(const char * s)
{
  dvector tmp(*this);
  tmp.fill(s);
  *this=lvector(tmp);
}
