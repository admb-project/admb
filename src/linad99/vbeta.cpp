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
dvariable beta(const prevariable& a,const prevariable& b )
{
  return exp(gammln(a)+gammln(b)-gammln(a+b));
}
