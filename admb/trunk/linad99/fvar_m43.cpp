/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
#include "fvar.hpp"

  dvar_vector VEC(_CONST dvar_matrix& _m)
  {
    dvar_matrix& m= (dvar_matrix&) _m;
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
    dvar_vector tmp(1,ii);
    ii=0;
    for (i=mmin;i<=mmax;i++)
    {
      tmp(io(i-1)+1,io(i)).shift(m(i).indexmin())=m(i);
    }
    return tmp;
  }

  dvar_matrix MAT(_CONST dvar_vector& v, int n,int m)
  {
    dvar_matrix tmp(1,n,1,m);
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



#undef HOME_VERSION
