/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

 const double simbdsmax=1.e+90;
 ofstream ofss("variance");

 double ssmin(double x,double y)
 {
   if (x<y) return x;
   return y;
 }
 double ssmax(double y,double x)
 {
   if (x>y) return x;
   return y;
 }

  void initial_params::set_all_simulation_bounds(BOR_CONST dmatrix& symbds)
  {
    int ii=1;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
	(varsptr[i])->set_simulation_bounds(symbds,ii);
    }
  }

  void param_init_number::set_simulation_bounds(BOR_CONST dmatrix& _symbds,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    dmatrix& symbds=(dmatrix&) _symbds;
    symbds(1,ii)= -simbdsmax;
    symbds(2,ii)= simbdsmax;
    ii++;
  }

  void param_init_bounded_number::set_simulation_bounds(BOR_CONST dmatrix& _symbds,BOR_CONST int& _ii)
  {
    dmatrix& symbds=(dmatrix&) _symbds;
    int& ii=(int&) _ii;
    symbds(1,ii)= minb-value(*this);
    symbds(2,ii)= maxb-value(*this);
    ii++;
  }

  void param_init_vector::set_simulation_bounds(BOR_CONST dmatrix& _symbds,BOR_CONST int& _ii)
  {
    dmatrix& symbds=(dmatrix&) _symbds;
    int& ii=(int&) _ii;
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      symbds(1,ii)= -simbdsmax;
      symbds(2,ii)= simbdsmax;
      ii++;
    }
  }

  void param_init_bounded_vector::set_simulation_bounds(BOR_CONST dmatrix& _symbds,BOR_CONST int& _ii)
  {
    dmatrix& symbds=(dmatrix&) _symbds;
    int& ii=(int&) _ii;
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      symbds(1,ii)= minb-value((*this)(i));
      symbds(2,ii)= maxb-value((*this)(i));
      ii++;
    }
  }


  void param_init_matrix::set_simulation_bounds(BOR_CONST dmatrix& _symbds,BOR_CONST int& _ii)
  {
    dmatrix& symbds=(dmatrix&) _symbds;
    int& ii=(int&) _ii;
    int rmin=rowmin();
    int rmax=rowmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        symbds(1,ii)= -simbdsmax;
        symbds(2,ii)= simbdsmax;
        ii++;
      }
    }
  }


  void param_init_bounded_matrix::set_simulation_bounds(BOR_CONST dmatrix& _symbds,BOR_CONST int& _ii)
  {
    dmatrix& symbds=(dmatrix&) _symbds;
    int& ii=(int&) _ii;
    int rmin=rowmin();
    int rmax=rowmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        symbds(1,ii)= minb-value((*this)(i,j));
        symbds(2,ii)= maxb-value((*this)(i,j));
        ii++;
      }
    }
  }

  void param_init_number::add_value(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii,BOR_CONST double& s,
    BOR_CONST dvector& diag)
  {
    int& ii=(int&) _ii;
    (*this)+=diag(ii)*ndev(ii);
    ii++;
  }

double new_value_mc(BOR_CONST double& _jac,double x,double min,double max,double eps,
  double sig)
{
  double& jac=(double&) _jac;
  double y;
  double y1;
  double mult;
  double z;
  double z1;
  if (eps>0)
  {
    double d=max-x;
    double d2=.5*d;
    if (sig>d2)
    {
      mult=d2;
    }
    else
    {
      mult=sig;
    }
    y=mult*eps;
    y1=mult*(eps+1.e-6);
    if (y>0.9*d)
    {
      z=y-0.9*d;
      z1=y1-0.9*d;
      y=0.9*d+0.1*d*z/(1.+z);
      y1=0.9*d+0.1*d*z1/(1.+z1);
    }
    y+=x;
    y1+=x;
  } 
  else
  {
    double d=x-min;
    double d2=.5*d;
    if (sig>d2)
    {
      mult=d2;
    }
    else
    {
      mult=sig;
    }
    y=-mult*eps;
    y1=-mult*(eps+1.e-6);
    if (y>0.9*d)
    {
      z=y-0.9*d;
      z1=y1-0.9*d;
      y=0.9*d+0.1*d*z/(1.+z);
      y1=0.9*d+0.1*d*z1/(1.+z1);
    }
    y=x-y;
    y1=x-y1;
  } 
  jac=(y1-y)*1.e+6;
  return y;
}

  void param_init_bounded_number::add_value(BOR_CONST dvector& _y,BOR_CONST dvector& ndev,BOR_CONST int& _ii,
    BOR_CONST double& s,BOR_CONST dvector& diag)
  {
    int& ii=(int&) _ii;
    *this = new_value_mc(_y(ii),value(*this),minb,maxb,ndev(ii),diag(ii));
    ii++;
  }

  void param_init_vector::add_value(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii,
    BOR_CONST double& s,BOR_CONST dvector& diag)
  {
    int& ii=(int&) _ii;
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)+=diag(ii)*ndev(ii);
      ii++;
    }
  }

  void param_init_bounded_vector::add_value(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii,
    BOR_CONST double& s,BOR_CONST dvector& diag)
  {
    int& ii=(int&) _ii;
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)= new_value_mc(y(ii),value((*this)(i)),minb,maxb,ndev(ii),
        diag(ii));
      ii++;
    }
  }


/*
  void param_init_bounded_vector::add_value(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& ii,BOR_CONST double& s)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    dvector tmp(mmin,mmax);
    int jj=1;
    set_value_inv(tmp,jj);
    double hpi=.5*3.14159;
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=atan(y(ii)+ndev(ii))/hpi;
      s-= log(1./(hpi*(1.0+square(y(ii)+ndev(ii))))); 
      ii++;
    }
    jj=1;
    dvariable pen=0.0;
    set_value(tmp,jj,pen);
  }
*/


  void param_init_matrix::add_value(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii,BOR_CONST double& s,
    BOR_CONST dvector& diag)
  {
    int& ii=(int&) _ii;
    int rmin=rowmin();
    int rmax=rowmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        (*this)(i,j)+=diag(ii)*ndev(ii); 
        ii++;
      }
    }
  }

  void param_init_bounded_matrix::add_value(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii,
    BOR_CONST double& s,BOR_CONST dvector& diag)
  {
    int& ii=(int&) _ii;
    int rmin=rowmin();
    int rmax=rowmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        (*this)(i,j)= new_value_mc(y(ii),value((*this)(i,j)),minb,maxb,
          ndev(ii),diag(ii));
        ii++;
      }
    }
  }

void param_init_d3array::add_value(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii,
  BOR_CONST double& s,BOR_CONST dvector& diag)
{
  int& ii=(int&) _ii;
  int smin=indexmin();
  int smax=indexmax();
  for (int k=smin;k<=smax;k++)
  {
    int rmin=(*this)(k).indexmin();
    int rmax=(*this)(k).indexmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(k,i).indexmin();
      int cmax=(*this)(k,i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        (*this)(k,i,j)+=diag(ii)*ndev(ii);
        ii++;
      }
    }
  }
}

void param_init_d3array::add_value(BOR_CONST dvector& ndev,BOR_CONST int& _ii)
{
  int& ii=(int&) _ii;
  int smin=indexmin();
  int smax=indexmax();
  for (int k=smin;k<=smax;k++)
  {
    int rmin=(*this)(k).indexmin();
    int rmax=(*this)(k).indexmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(k,i).indexmin();
      int cmax=(*this)(k,i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        (*this)(k,i,j)+=ndev(ii);
        ii++;
      }
    }
  }
}


  void param_init_number::get_jacobian(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    (*this)+=ndev(ii);
    ii++;
  }

  void param_init_bounded_number::get_jacobian(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    (*this)+=ndev(ii);
    ii++;
  }

  void param_init_vector::get_jacobian(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)+=ndev(ii);
      ii++;
    }
  }

  void param_init_matrix::get_jacobian(BOR_CONST dvector& y,BOR_CONST dvector& ndev,BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    int rmin=rowmin();
    int rmax=rowmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        (*this)(i,j)+=ndev(ii); 
        ii++;
      }
    }
  }

  void param_init_bounded_matrix::get_jacobian(BOR_CONST dvector& y,BOR_CONST dvector& ndev,
    BOR_CONST int& _ii)
  {
    int& ii=(int&) _ii;
    int rmin=rowmin();
    int rmax=rowmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        (*this)(i,j)+=ndev(ii);
        ii++;
      }
    }
  }


  void param_init_bounded_vector::get_jacobian(BOR_CONST dvector& _y,BOR_CONST dvector& _jac,
    BOR_CONST int& _ii)
  {
    dvector& y=(dvector&) _y;
    dvector& jac=(dvector&) _jac;
    int& ii=(int&) _ii;
    int mmin=indexmin();
    int mmax=indexmax();
    dvector tmp(mmin,mmax);
    int jj=1;
    set_value_inv(tmp,jj);
    double hpi=.5*3.14159;
    for (int i=mmin;i<=mmax;i++)
    {
      y(ii)=tan(hpi*tmp(i));
      jac(ii) = 1./(hpi*(1.0+square(y(ii)))); 
      ii++;
    }
  }

void param_init_d3array::set_simulation_bounds(BOR_CONST dmatrix& _symbds,
  BOR_CONST int& _ii)
{
  dmatrix& symbds=(dmatrix&) _symbds;
  int& ii=(int&) _ii;
  int smin=indexmin();
  int smax=indexmax();
  for (int k=smin;k<=smax;k++)
  {
    int rmin=(*this)(k).indexmin();
    int rmax=(*this)(k).indexmax();
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(k,i).indexmin();
      int cmax=(*this)(k,i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
        symbds(1,ii)= -simbdsmax;
        symbds(2,ii)= simbdsmax;
        ii++;
      }
    }
  }

}

