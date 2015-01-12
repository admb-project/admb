/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>



  void param_init_number::curv_scale(BOR_CONST dvector& _d,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    dvector& d=(dvector&) _d;
    int& ii=(int&) _ii;
    d(ii)=0;
    ii++;
  }

  void param_init_bounded_number::curv_scale(BOR_CONST dvector& _d,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    dvector& d=(dvector&) _d;
    int& ii=(int&) _ii;
    double pen=0;
    d(ii)=nd2fboundp(x(ii),minb,maxb,pen);

    //d(ii)=(boundp(x(ii)+1.e-6,minb,maxb,pen)-
      //      2.*boundp(x(ii),minb,maxb,pen)+
	//boundp(x(ii)-1.e-6,minb,maxb,pen))/1.e-12;
    ii++;
  }

  void param_init_vector::curv_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& v=(dvector&) _v;
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      v(ii++)=0.;
    }
  }

  void param_init_matrix::curv_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& v=(dvector&) _v;
    int mmin=rowmin();
    int mmax=rowmax();
    for (int i=mmin;i<=mmax;i++)
    {
      int cmin=((*this)(i)).indexmin();
      int cmax=((*this)(i)).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        v(ii++)=0.;
      }
    }
  }

  void param_init_bounded_vector::curv_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& v=(dvector&) _v;
    int mmin=indexmin();
    int mmax=indexmax();
    double pen=0;
    for (int i=mmin;i<=mmax;i++)
    {
      v(ii)=nd2fboundp(x(ii),minb,maxb,pen);
      ii++;
    }
  }

  void param_init_bounded_matrix::curv_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& v=(dvector&) _v;
    int rmin=rowmin();
    int rmax=rowmax();
    double pen=0;
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        v(ii)=nd2fboundp(x(ii),minb,maxb,pen);
	ii++;
      }
    }
  }

