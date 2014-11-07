/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */

#include <df1b2fun.h>
#include <admodel.h>

#ifdef ISZERO
  #undef ISZERO
#endif
#define ISZERO(d) ((d)==0.0)

//double ndfboundp( double x, double fmin, double fmax,const double& fpen);

/**
 * Description not yet available.
 * \param
 */
  int initial_df1b2params::stddev_scale(const dvector& d,const dvector& x)
  {
    int ii=1;
    for (int i=0;i<num_initial_df1b2params;i++)
    {
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
        (varsptr[i])->sd_scale(d,x,ii);
    }
    return ii-1;
  }

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_number::sd_scale(const dvector& _d,const dvector& x,
  const int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& d=(dvector&) _d;
    d(ii)=1;
    if (!ISZERO(scalefactor)) d(ii)/=scalefactor;
    ii++;
  }

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_number::sd_scale(const dvector& _d,const dvector& x,
  const int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& d=(dvector&) _d;
    double pen=0;
    if(!initial_params::mc_phase)
    {
      if (ISZERO(scalefactor))
        d(ii)=ndfboundp(x(ii),minb,maxb,pen);
      else
        d(ii)=ndfboundp(x(ii)/scalefactor,minb,maxb,pen)/scalefactor;
    }
    else
    {
      if (ISZERO(scalefactor))
        d(ii)=ndfboundp_mc(x(ii),minb,maxb,pen);
      else
        d(ii)=ndfboundp_mc(x(ii)/scalefactor,minb,maxb,pen)/scalefactor;
    }

    //d(ii)=(boundp(x(ii)+1.e-6,minb,maxb,pen)-
    //boundp(x(ii)-1.e-6,minb,maxb,pen))/2.e-6;
    ii++;
  }

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_vector::sd_scale(const dvector& _v,const dvector& x,
  const int& _ii)
  {
    if (allocated())
    {
      int& ii=(int&) _ii;
      dvector& v=(dvector&) _v;
      int mmin=indexmin();
      int mmax=indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        v(ii)=1.;
        if (!ISZERO(scalefactor)) v(ii)/=scalefactor;
        ii++;
      }
    }
  }

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_matrix::sd_scale(const dvector& _v,const dvector& x,
  const int& _ii)
  {
    if (allocated())
    {
      int& ii=(int&) _ii;
      dvector& v=(dvector&) _v;
      int mmin=indexmin();
      int mmax=indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        if (::allocated((*this)(i)))
        {
          int cmin=((*this)(i)).indexmin();
          int cmax=((*this)(i)).indexmax();
          for (int j=cmin;j<=cmax;j++)
          {
            v(ii)=1.;
            if (!ISZERO(scalefactor)) v(ii)/=scalefactor;
            ii++;
          }
        }
      }
    }
  }

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_vector::sd_scale(const dvector& _v,const dvector& x,
  const int& _ii)
  {
    if (allocated())
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
          if (ISZERO(scalefactor))
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

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::sd_scale(const dvector& _v,const dvector& x,
  const int& _ii)
  {
    if (allocated())
    {
      int& ii=(int&) _ii;
      dvector& v=(dvector&) _v;
      int rmin=indexmin();
      int rmax=indexmax();
      double pen=0;
      for (int i=rmin;i<=rmax;i++)
      {
        if (::allocated((*this)(i)))
        {
          int cmin=(*this)(i).indexmin();
          int cmax=(*this)(i).indexmax();
          for (int j=cmin;j<=cmax;j++)
          {
            if (ISZERO(scalefactor))
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

/**
 * Description not yet available.
 * \param
 */
int allocated(const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x)
  return x.allocated();
}

/**
 * Description not yet available.
 * \param
 */
int allocated(const df1b2_init_vector& _x)
{
  ADUNCONST(df1b2_init_vector,x)
  return x.allocated();
}

/**
 * Description not yet available.
 * \param
 */
int allocated(const df1b2_init_matrix& _x)
{
  ADUNCONST(df1b2_init_matrix,x)
  return x.allocated();
}

/**
 * Description not yet available.
 * \param
 */
int allocated(const df1b2matrix& _x)
{
  ADUNCONST(df1b2matrix,x)
  return x.allocated();
}
