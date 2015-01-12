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
  ivector operator + (int v,_CONST ivector& w)
  {
     int mmin=w.indexmin();
     int mmax=w.indexmax();
     ivector tmp(mmin,mmax);
     for (int i=mmin; i<=mmax; i++)
     {
       tmp(i)=v+w(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  ivector operator - (int v,_CONST ivector& w)
  {
     int mmin=w.indexmin();
     int mmax=w.indexmax();
     ivector tmp(mmin,mmax);
     for (int i=mmin; i<=mmax; i++)
     {
       tmp(i)=v-w(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  ivector operator + (_CONST ivector& v,_CONST ivector& w)
  {
     int mmin=v.indexmin();
     int mmax=v.indexmax();
     ivector tmp(mmin,mmax);
     for (int i=mmin; i<=mmax; i++)
     {
       tmp(i)=v(i)+w(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  ivector operator - (_CONST ivector& v,_CONST ivector& w)
  {
     int mmin=v.indexmin();
     int mmax=v.indexmax();
     ivector tmp(mmin,mmax);
     for (int i=mmin; i<=mmax; i++)
     {
       tmp(i)=v(i)-w(i);
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  ivector operator + (_CONST ivector& v,int w)
  {
     int mmin=v.indexmin();
     int mmax=v.indexmax();
     ivector tmp(mmin,mmax);
     for (int i=mmin; i<=mmax; i++)
     {
       tmp(i)=v(i)+w;
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  ivector operator - (_CONST ivector& v,int w)
  {
     int mmin=v.indexmin();
     int mmax=v.indexmax();
     ivector tmp(mmin,mmax);
     for (int i=mmin; i<=mmax; i++)
     {
       tmp(i)=v(i)-w;
     }
     return(tmp);
  }
