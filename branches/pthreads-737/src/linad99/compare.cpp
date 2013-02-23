/*
 * $Id: compare.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
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
int operator==(double v0, const prevariable& v1)
   { 
     return (v0==value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
int operator<=(double v0, const prevariable& v1)
   { 
     return (v0<=value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
int operator>=(double v0, const prevariable& v1)
   { 
     return (v0>=value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
int operator>(double v0, const prevariable& v1)
   { 
     return (v0>value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
int operator<(double v0, const prevariable& v1)
   { 
     return (v0<value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
int operator!=(double v0, const prevariable& v1)
   { 
     return (v0!=value(v1));
   }
