/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

  dvector VEC(_CONST dmatrix& _m)
  {
    dmatrix& m= (dmatrix&) _m;
    int i;
    int mmin=m.indexmin();
    int mmax=m.indexmax();
    int ii=0;
    ivector io(mmin-1,mmax);
    io(mmin-1)=0;
    for (i=mmin;i<=mmax;i++)
    {
      ii+=m(i).indexmax()-m(i).indexmin()+1;
      io(i)=ii;
    }
    dvector tmp(1,ii);
    ii=0;
    for (i=mmin;i<=mmax;i++)
    {
      tmp(io(i-1)+1,io(i)).shift(m(i).indexmin())=m(i);
    }
    return tmp;
  }

  dmatrix MAT(_CONST dvector& v, int n,int m)
  {
    dmatrix tmp(1,n,1,m);
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    int ii=mmin;
    if ( mmax-mmin+1 != n*m)
    {
      cerr << " Vector and Matrix sizes don't match in function MAT" << endl;
      tmp.initialize();
      return tmp;
    }  	  
    for (int i=1;i<=n;i++)
    {
      for (int j=1;j<=m;j++)
      {
	tmp(i,j)=v(ii++);
      }
    }
    return tmp;
  }



