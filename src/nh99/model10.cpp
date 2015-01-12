/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

//double ndfboundp( double x, double fmin, double fmax,BOR_CONST double& fpen);


  void param_init_number::sd_scale(BOR_CONST dvector& _d,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& d=(dvector&) _d;
    d(ii)=1;
    if (scalefactor) d(ii)/=scalefactor;
    ii++;
  }


  void param_init_bounded_number::sd_scale(BOR_CONST dvector& _d,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& d=(dvector&) _d;
    double pen=0;
    if(!initial_params::mc_phase)
    {
      if (!scalefactor) 
        d(ii)=ndfboundp(x(ii),minb,maxb,pen);
      else
        d(ii)=ndfboundp(x(ii)/scalefactor,minb,maxb,pen)/scalefactor;
    }
    else
    {
      if (!scalefactor) 
        d(ii)=ndfboundp_mc(x(ii),minb,maxb,pen);
      else
        d(ii)=ndfboundp_mc(x(ii)/scalefactor,minb,maxb,pen)/scalefactor;
    }
	
    //d(ii)=(boundp(x(ii)+1.e-6,minb,maxb,pen)-
	//boundp(x(ii)-1.e-6,minb,maxb,pen))/2.e-6;
    ii++;
  }

  void param_init_vector::sd_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvector& v=(dvector&) _v;
      int mmin=indexmin();
      int mmax=indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        v(ii)=1.;
        if (scalefactor) v(ii)/=scalefactor;
        ii++;
      }
    }
  }


  void param_init_matrix::sd_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvector& v=(dvector&) _v;
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
            v(ii)=1.;
            if (scalefactor) v(ii)/=scalefactor;
            ii++;
          }
	}  
      }
    }
  }


  void param_init_bounded_vector::sd_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvector& v=(dvector&) _v;
      int mmin=indexmin();
      int mmax=indexmax();
      double pen=0;
      if(!initial_params::mc_phase)
      {
        for (int i=mmin;i<=mmax;i++)
        {
          if (!scalefactor) 
            v(ii)=ndfboundp(x(ii),minb,maxb,pen);
          else
            v(ii)=ndfboundp(x(ii)/scalefactor,minb,maxb,pen)/scalefactor;
          ii++;
        }
      }
      else
      {
        for (int i=mmin;i<=mmax;i++)
        {
          v(ii)=ndfboundp_mc(x(ii),minb,maxb,pen);
          ii++;
        }
      }
    }
  }


  void param_init_bounded_matrix::sd_scale(BOR_CONST dvector& _v,BOR_CONST dvector& x,BOR_CONST int& _ii)
  {
    if (allocated(*this))
    {  
      int& ii=(int&) _ii;
      dvector& v=(dvector&) _v;
      int rmin=rowmin();
      int rmax=rowmax();
      double pen=0;
      for (int i=rmin;i<=rmax;i++)
      {
        if (allocated((*this)(i)))
        {  
          int cmin=(*this)(i).indexmin();
          int cmax=(*this)(i).indexmax();
          for (int j=cmin;j<=cmax;j++)
          {
            if (!scalefactor) 
              v(ii)=ndfboundp(x(ii),minb,maxb,pen);
            else
              v(ii)=ndfboundp(x(ii)/scalefactor,minb,maxb,pen)/
                scalefactor;
	    ii++;
          }
        }
      }
    }
  }


  void param_init_bounded_number::set_minb(double x)
  {
    minb=x;
  }

  double param_init_bounded_number::get_minb(void)
  {
    return minb;
  }

  void param_init_bounded_vector::set_minb(double x)
  {
    minb=x;
  }

  double param_init_bounded_vector::get_minb(void)
  {
    return minb;
  }

  void param_init_bounded_matrix::set_minb(double x)
  {
    minb=x;
  }

  double param_init_bounded_matrix::get_minb(void)
  {
    return minb;
  }
