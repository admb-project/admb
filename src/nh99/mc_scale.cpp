/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

double set_value_mc(double z,double min,double max);
//double ndfboundp( double x, double fmin, double fmax,const double& fpen);
//double ndfboundp_mc( double x, double fmin, double fmax,const double& fpen);

/**
 * Description not yet available.
 * \param
 */
int initial_params::montecarlo_scale(const dvector& d, const dvector& x)
{
  int ii = 1;
  for (int i = 0; i < num_initial_params; i++)
  {
    //if ((varsptr[i])->phase_start <= current_phase)
    if (withinbound(0, (varsptr[i])->phase_start, current_phase))
      (varsptr[i])->mc_scale(d,x,ii);
  }
  return ii - 1;
}

/**
 * Description not yet available.
 * \param
 */
void param_init_number::mc_scale(const dvector& _d, const dvector& x,
  const int& _ii)
{
  dvector& d=(dvector&) _d;
  int& ii=(int&) _ii;
  d(ii)=1;
  ii++;
}

/**
 * Description not yet available.
 * \param
 */
void param_init_bounded_number::mc_scale(const dvector& _d, const dvector& x,
  const int& _ii)
{
  dvector& d=(dvector&) _d;
  int& ii=(int&) _ii;
  double pen=0;
  //double var;
  double xx=set_value_inv_mc(*this,minb,maxb);
  double yy=boundpin(*this,minb,maxb);
  double a=ndfboundp(yy,minb,maxb,pen);
  double b=ndfboundp_mc(xx,minb,maxb,pen);
  d(ii)=b/a;
  ii++;
}

/**
 * Description not yet available.
 * \param
 */
double ndfboundp_mc(double x, double fmin, double fmax,const double& fpen)
{
  if (x<-0.99999)
  {
    double df1=(set_value_mc(x+1.e-6,fmin,fmax)-
      set_value_mc(x,fmin,fmax))/1.e-6;
    double df2=(set_value_mc(x+2.e-6,fmin,fmax)
      -set_value_mc(x,fmin,fmax))/2.e-6;
    return 2.*df1-df2;
  }
  else if (x>0.99999)
  {
    double df1=(set_value_mc(x,fmin,fmax)
      -set_value_mc(x-1.e-6,fmin,fmax))/1.e-6;
    double df2=(set_value_mc(x,fmin,fmax)-
      set_value_mc(x-2.e-6,fmin,fmax))/2.e-6;
    return 2.*df1-df2;
  }
  else
  {
    return (set_value_mc(x+1.e-6,fmin,fmax)-
      set_value_mc(x-1.e-6,fmin,fmax))/2.e-6;
  }
}

/**
 * Description not yet available.
 * \param
 */
void param_init_vector::mc_scale(const dvector& _v, const dvector& x,
  const int& _ii)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    v(ii++)=1.;
  }
}

/**
 * Description not yet available.
 * \param
 */
void param_init_matrix::mc_scale(const dvector& _v, const dvector& x,
  const int& _ii)
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
      v(ii++)=1.;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void param_init_d3array::mc_scale(const dvector& _v, const dvector& x,
  const int& _ii)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int mmin=slicemin();
  int mmax=slicemax();
  for (int i=mmin;i<=mmax;i++)
  {
    int rmin=((*this)(i)).rowmin();
    int rmax=((*this)(i)).rowmax();
    for (int j=rmin;j<=rmax;j++)
    {
      int cmin=((*this)(i))(j).indexmin();
      int cmax=((*this)(i))(j).indexmax();
      for (int k=cmin;k<=cmax;k++)
      {
        v(ii++)=1.;
      }
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void param_init_bounded_vector::mc_scale(const dvector& _v, const dvector& x,
  const int& _ii)
{
  int& ii=(int&) _ii;
  dvector& v=(dvector&) _v;
  int mmin=indexmin();
  int mmax=indexmax();
  double pen=0;
  for (int i=mmin;i<=mmax;i++)
  {
    double var=set_value_mc(x(ii),minb,maxb);
    double xx=boundpin(var,minb,maxb);
    double a=ndfboundp(xx,minb,maxb,pen);
    double b=ndfboundp_mc(x(ii),minb,maxb,pen);
    v(ii)=b/a;
    ii++;
  }
}

/**
 * Description not yet available.
 * \param
 */
void param_init_bounded_matrix::mc_scale(const dvector& _v, const dvector& x,
  const int& _ii)
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
      v(ii)=ndfboundp(x(ii),minb,maxb,pen);
      double var=set_value_mc(x(ii),minb,maxb);
      double xx=set_value_inv_mc(var,minb,maxb);
      double a=ndfboundp(xx,minb,maxb,pen);
      double b=ndfboundp_mc(xx,minb,maxb,pen);
      v(ii)=b/a;
      ii++;
    }
  }
}
