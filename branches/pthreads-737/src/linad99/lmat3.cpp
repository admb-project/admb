/*
 * $Id: lmat3.cpp 542 2012-07-10 21:04:06Z johnoel $
 * 
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

/**
 * Description not yet available.
 * \param
 */
 void lmatrix::initialize (void)
 {
   for (int i=rowmin();i<=rowmax();i++)
   {
     (*this)(i).initialize();
   }
 }
