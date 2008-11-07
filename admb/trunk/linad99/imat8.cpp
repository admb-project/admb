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
#include <fvar.hpp>


  ivector colsum(_CONST imatrix&v)
  {
    int cmin=v.colmin();
    int cmax=v.colmax();
    int rmin=v.rowmin();
    int rmax=v.rowmax();

    ivector tmp(cmin,cmax);
    tmp.initialize();
    for (int j=cmin; j<=cmax; j++)
    {
      for (int i=rmin; i<=rmax; i++)
      {
        tmp(j)+=v(i,j);
      }
    }
    return tmp;
  }

  ivector rowsum(_CONST imatrix&v)
  {
    int rmin=v.rowmin();
    int rmax=v.rowmax();

    ivector tmp(rmin,rmax);
    for (int i=rmin; i<=rmax; i++)
    {
      tmp(i)=sum(v(i));
    }
    return tmp;
  }

  void imatrix::fill_seqadd(int i2,int j)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    int ii=i2;
    for (int i=mmin;i<=mmax;i++)
    {
      if (allocated((*this)(i)))
      {
        (*this)(i).fill_seqadd(ii,j);
        int jmax=(*this)(i).indexmax();
        ii=(*this)(i,jmax)+j;
      }
    }
  }
      
    

#undef HOME_VERSION

