/*
 * $Id: dvect4.cpp 542 2012-07-10 21:04:06Z johnoel $
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
dvector operator*(const dvector& t1, CGNU_DOUBLE x)
  {

     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x*t1.elem(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector operator/(CGNU_DOUBLE x, const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x/t1.elem(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector operator/(const dvector& t1, CGNU_DOUBLE x)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=t1.elem(i)/x;
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector operator+(CGNU_DOUBLE x, const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x+t1.elem(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector operator+(const dvector& t1, CGNU_DOUBLE x)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=t1.elem(i)+x;
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector operator-( CGNU_DOUBLE x, const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x-t1.elem(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector operator-(const dvector& t1, CGNU_DOUBLE x)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=t1.elem(i)-x;
     }
     return(tmp);
  }
