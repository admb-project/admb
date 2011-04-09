/*
 * $Id: compare.cpp 946 2011-01-12 23:52:45Z johnoel $
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
   int operator ==(double v0,_CONST prevariable& v1)
   { 
     return (v0==value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
   int operator <=(double v0,_CONST prevariable& v1)
   { 
     return (v0<=value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
   int operator >=(double v0,_CONST prevariable& v1)
   { 
     return (v0>=value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
   int operator >(double v0,_CONST prevariable& v1)
   { 
     return (v0>value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
   int operator <(double v0,_CONST prevariable& v1)
   { 
     return (v0<value(v1));
   }

/**
 * Description not yet available.
 * \param
 */
   int operator !=(double v0,_CONST prevariable& v1)
   { 
     return (v0!=value(v1));
   }
