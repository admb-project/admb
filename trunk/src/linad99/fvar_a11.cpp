/*
 * $Id: fvar_a11.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Functions to compute minimum and maximum of a dvar_vector.
 */
#include "fvar.hpp"

/**
 * \ingroup misc
 * Maximum of a dvar_vector. 
 * \param A dvar_vector 
 * \returns The maximum of the vector 
 */
  dvariable max(_CONST dvar_vector& t1)
  {
     dvariable tmp;
     int mmin=t1.indexmin();
     int mmax=t1.indexmax();
     tmp=t1.elem(mmin);
     for (int i=mmin+1; i<=mmax; i++)
     {
       if (tmp<t1.elem(i)) tmp=t1.elem(i);
     }
     return(tmp);
  }


/**
 * \ingroup misc
 * Minimum of a dvar_vector. 
 * \param A dvar_vector 
 * \returns The minimum of the vector 
 */
  dvariable min(_CONST dvar_vector& t1)
  {
     dvariable tmp;
     int mmin=t1.indexmin();
     int mmax=t1.indexmax();
     tmp=t1.elem(mmin);
     for (int i=mmin+1; i<=mmax; i++)
     {
       if (tmp>t1.elem(i)) tmp=t1.elem(i);
     }
     return(tmp);
  }
