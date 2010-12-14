/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"


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

