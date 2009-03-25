/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <admodel.h>

//double ndfboundp( double x, double fmin, double fmax,BOR_CONST double& fpen);



  void param_init_number::sd_vscale(const dvar_vector& _d,const dvar_vector& x,
    const int& _ii)
  {
    int& ii=(int&) _ii;
    dvar_vector& d=(dvar_vector&) _d;
    d(ii)=1.0;
    ii++;
  }

  void param_init_bounded_number::sd_vscale(const dvar_vector& _d,
    const dvar_vector& x,const int& _ii)
  {
    int& ii=(int&) _ii;
    dvar_vector& d=(dvar_vector&) _d;
    d(ii)=dfboundp(x(ii),minb,maxb);
    ii++;
  }

  void param_init_vector::sd_vscale(const dvar_vector& _d,
    const dvar_vector& x,const int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvar_vector& d=(dvar_vector&) _d;
      int mmin=indexmin();
      int mmax=indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        d(ii)=1.0;
        ii++;
      }
    }
  }


  void param_init_matrix::sd_vscale(const dvar_vector& _d,
    const dvar_vector& x,const int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvar_vector& d=(dvar_vector&) _d;
      int mmin=rowmin();
      int mmax=rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        if (allocated((*this)(i)))
        {
          int cmin=((*this)(i)).indexmin();
          int cmax=((*this)(i)).indexmax();
          for (int j=cmin;j<=cmax;j++)
          {
            d(ii)=1.0;
            ii++;
          }
	}  
      }
    }
  }

  void param_init_bounded_vector::sd_vscale(const dvar_vector& _v,
    const dvar_vector& x,const int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvar_vector& v=(dvar_vector&) _v;
      int mmin=indexmin();
      int mmax=indexmax();
      double pen=0;
      for (int i=mmin;i<=mmax;i++)
      {
        v(ii)=dfboundp(x(ii),minb,maxb);
        ii++;
      }
    }
  }

  void param_init_bounded_matrix::sd_vscale(const dvar_vector& _d,
    const dvar_vector& x,const int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvar_vector& d=(dvar_vector&) _d;
      int mmin=rowmin();
      int mmax=rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        if (allocated((*this)(i)))
        {
          int cmin=((*this)(i)).indexmin();
          int cmax=((*this)(i)).indexmax();
          for (int j=cmin;j<=cmax;j++)
          {
            d(ii)=dfboundp(x(ii),minb,maxb);
            ii++;
          }
	}  
      }
    }
  }
