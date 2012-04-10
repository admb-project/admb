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
// file: fvar_ops.cpp
// operators involving prevariables
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <math.h>
#include <stdio.h>

void gradfree(dlink *);

/**
 * Description not yet available.
 * \param
 */
    int prevariable::operator ==( CGNU_DOUBLE v1) _CONST
    {
      return(v->x==v1);
    }

/**
 * Description not yet available.
 * \param
 */
    int prevariable::operator <=( CGNU_DOUBLE v1) _CONST
    {
      return(v->x<=v1);
    }

/**
 * Description not yet available.
 * \param
 */
    int prevariable::operator <( CGNU_DOUBLE v1) _CONST
    {
      return(v->x<v1);
    }

/**
 * Description not yet available.
 * \param
 */
    int prevariable::operator >( CGNU_DOUBLE v1) _CONST
    {
      return(v->x>v1);
    }

/**
 * Description not yet available.
 * \param
 */
    int prevariable::operator >=( CGNU_DOUBLE v1) _CONST
    {
      return(v->x >=v1);
    }

/**
 * Description not yet available.
 * \param
 */
    int prevariable::operator !=( CGNU_DOUBLE v1) _CONST
    {
      return(v->x!=v1);
    }
