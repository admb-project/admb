/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

  dvector operator * (_CONST dvector& t1, CGNU_DOUBLE x)
  {

     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x*t1.elem(i);
     }
     return(tmp);
  }

  dvector operator / ( CGNU_DOUBLE x,_CONST dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x/t1.elem(i);
     }
     return(tmp);
  }

  dvector operator / (_CONST dvector& t1, CGNU_DOUBLE x)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=t1.elem(i)/x;
     }
     return(tmp);
  }

  dvector operator + ( CGNU_DOUBLE x,_CONST dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x+t1.elem(i);
     }
     return(tmp);
  }

  dvector operator + (_CONST dvector& t1, CGNU_DOUBLE x)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=t1.elem(i)+x;
     }
     return(tmp);
  }


  dvector operator - ( CGNU_DOUBLE x,_CONST dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=x-t1.elem(i);
     }
     return(tmp);
  }

  dvector operator - (_CONST dvector& t1, CGNU_DOUBLE x)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=t1.elem(i)-x;
     }
     return(tmp);
  }
