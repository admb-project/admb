/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>
/*
void param_init_d3array::set_simulation_bounds(const dmatrix& symbds,
  const int& ii)
{
 cerr << " Error -- void param_init_d3array::set_simulation_bounds"
   " (const dmatrix& symbds, const int& ii) has not yet been defined" << endl;
 exit(1);
}
*/

void param_init_d3array::get_jacobian(const dvector& y, const dvector& ndev,
  const int& ii)
{
 cerr << " Error -- "
   " void param_init_number::add_value(const dvector& ndev, const int& ii)"
   " has not yet been defined" << endl;
 exit(1);
}

const char * param_init_d3array::label(void)
{
  return model_name_tag::label().mychar();
}

param_init_d3array::param_init_d3array() : named_dvar3_array() ,
  initial_params()
{
  //add_to_list();
}

int param_init_d3array::size_count(void)
{
  return ::size_count(*this);
}

void param_init_d3array::save_value(ofstream& ofs)
{
  if (!(!(*this)))
    ofs << label_class(this->label()) << dvar3_array(*this) << endl;
}

void param_init_d3array::bsave_value(uostream& uos)
{
  if (!(!(*this)))
  {
    dvar3_array& tmp = *this;
    uos << tmp;
  }
}

void param_init_d3array::set_value(const dvar_vector& x,
  const int& ii, const dvariable& pen)
  {
    ::set_value(*this,x,ii);
  }

void param_init_d3array::set_value_inv(const dvector& x, const int& ii)
  {
    ::set_value_inv(*this,x,ii);
  }

void param_init_d3array::copy_value_to_vector(const dvector& x, const int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

void param_init_d3array::restore_value_from_vector(const dvector& x,
  const int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

void param_init_d3array::save_value(const ofstream& _ofs,int prec)
  {
    ofstream& ofs=(ofstream&) _ofs;
    ofs << setw(prec+6) << setprecision(prec) << dvar3_array(*this) << endl;
  }

  void param_init_d3array::allocate(int smin,int smax,int rmin,int rmax,
    int cmin,int cmax,const char * s)
  {
    allocate(smin,smax,rmin,rmax,cmin,cmax,1,s);
  }

  void param_init_d3array::allocate(const ad_integer& sl,
    const ad_integer& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,const char * s)
  {
    allocate(sl,sh,nrl,nrh,ncl,nch,1,s);
  }

  void param_init_d3array::allocate(const ad_integer& sl,
    const ad_integer& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,int phase_start,
    const char * s)
  {
    named_dvar3_array::allocate(sl,sh,nrl,nrh,ncl,nch,s);
    initial_params::allocate(phase_start);
    if (!(!(*this)))
    {
      for (int i=indexmin();i<=indexmax();i++)
      {
        if (allocated((*this)(i)))
        {
          for (int j=(*this)(i).indexmin();j<=(*this)(i).indexmax();j++)
          {
            if (allocated((*this)(i,j)))
            {
              if (ad_comm::global_bparfile)
              {
                *(ad_comm::global_bparfile) >> (*this)(i,j);
              }
              else if (ad_comm::global_parfile)
              {
                *(ad_comm::global_parfile) >> (*this)(i,j);
              }
              else
              {
                (*this)(i,j)=(initial_value);
              }
            }
          }
        }
      }
    }
  }

  void param_init_d3array::allocate(int smin,int smax,int rmin,int rmax,
    int cmin,int cmax,int phase_start, const char * s)
  {
    named_dvar3_array::allocate(smin,smax,rmin,rmax,cmin,cmax,s);
    initial_params::allocate(phase_start);
    if (!(!(*this)))
    {
      for (int i=indexmin();i<=indexmax();i++)
      {
        if (allocated((*this)(i)))
        {
          if (ad_comm::global_bparfile)
          {
            *(ad_comm::global_bparfile) >> (*this)(i);
          }
          else if (ad_comm::global_parfile)
          {
            *(ad_comm::global_parfile) >> (*this)(i);
          }
          else
          {
            (*this)(i)=(initial_value);
          }
        }
      }
    }
  }

void param_init_d3array::curv_scale(const dvector& _v, const dvector& x,
  const int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& v=(dvector&) _v;
    int smin=slicemin();
    int smax=slicemax();
    for (int k=smin;k<=smax;k++)
    {
      int mmin=(*this)(k).rowmin();
      int mmax=(*this)(k).rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        int cmin=((*this)(k,i)).indexmin();
        int cmax=((*this)(k,i)).indexmax();
        for (int j=cmin;j<=cmax;j++)
        {
          v(ii++)=0.;
        }
      }
    }
  }

void param_init_d3array::hess_scale(const dvector& _v, const dvector& x,
  const int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& v=(dvector&) _v;
    int smin=slicemin();
    int smax=slicemax();
    for (int k=smin;k<=smax;k++)
    {
      int mmin=(*this)(k).rowmin();
      int mmax=(*this)(k).rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        int cmin=((*this)(k,i)).indexmin();
        int cmax=((*this)(k,i)).indexmax();
        for (int j=cmin;j<=cmax;j++)
        {
          v(ii++)=0.;
        }
      }
    }
  }

void param_init_d3array::sd_scale(const dvector& _v, const dvector& x,
  const int& _ii)
  {
    int& ii=(int&) _ii;
    dvector& v=(dvector&) _v;
    if (allocated(*this))
    {
      int smin=slicemin();
      int smax=slicemax();
      for (int k=smin;k<=smax;k++)
      {
        if (allocated((*this)(k)))
        {
          int mmin=(*this)(k).rowmin();
          int mmax=(*this)(k).rowmax();
          for (int i=mmin;i<=mmax;i++)
          {
            if (allocated((*this)(k,i)))
            {
              int cmin=((*this)(k,i)).indexmin();
              int cmax=((*this)(k,i)).indexmax();
              for (int j=cmin;j<=cmax;j++)
              {
                v(ii++)=1.;
              }
            }
          }
        }
      }
    }
  }

cifstream& operator>>(const cifstream& _s, param_init_d3array& m)
{
  cifstream&  s=(cifstream&) _s;
  s >> dvar3_array(m);
  return s;
}

void param_init_d3array::restore_value(const ifstream& ofs)
{
  ofs  >> dvar3_array(*this);
}
