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
double mean(const d3_array& m)
   {
     double tmp;
     tmp=sum(m)/size_count(m);
     return tmp;
   }
