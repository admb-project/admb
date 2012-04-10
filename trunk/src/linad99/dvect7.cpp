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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
  dvector log(_CONST dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i = t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i) = log(t1.elem(i));
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  dvector exp(_CONST dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i = t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i) = exp(t1.elem(i));
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  dvector fabs(_CONST dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i = t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i) = fabs(t1.elem(i));
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  double max(_CONST dvector& t1)
  {
     double tmp;
     int mmin = t1.indexmin();
     int mmax = t1.indexmax();
     tmp = t1.elem(mmin);
     for (int i = mmin+1; i<=mmax; i++)
     {
       if (tmp<t1.elem(i)) tmp = t1.elem(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  double min(_CONST dvector& t1)
  {
     double tmp;
     int mmin = t1.indexmin();
     int mmax = t1.indexmax();
     tmp = t1.elem(mmin);
     for (int i = mmin+1; i<=mmax; i++)
     {
       if (tmp>t1.elem(i)) tmp = t1.elem(i);
     }
     return(tmp);
  }
