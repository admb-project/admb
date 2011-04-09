/*
 * $Id: d3arr3.cpp 946 2011-01-12 23:52:45Z johnoel $
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
   double mean(_CONST d3_array& m)
   {
     double tmp;
     tmp=sum(m)/size_count(m);
     return tmp;
   }  
