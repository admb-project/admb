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
#define HOME_VERSION
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
  df1b2variable t_deviate(const df1b2variable& _x,const df1b2variable& _a)
  {
    df1b2variable& x= (df1b2variable&)(_x);
    df1b2variable& a= (df1b2variable&)(_a);

    df1b2variable y=cumd_norm(x);
    y=.9999*y+.00005;

    df1b2variable z=inv_cumd_t(y,a);

    return z;
  }
