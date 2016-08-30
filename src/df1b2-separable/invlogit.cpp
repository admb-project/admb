/*
 * $Id$
 *
 * Authors: Anders Nielsen <anders@nielsensweb.org>
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * invlogit function.
 */

#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2variable invlogit(df1b2variable x){
  return 1/(1+exp(-x));
} 
