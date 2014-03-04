/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 *
 * License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
class param_init_d3array: public named_dvar3_array,public initial_params
{
public:
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual int size_count(void);
  virtual void save_value(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){};

public:
  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  param_init_d3array(void);
};

/**
 * Description not yet available.
 * \param
 */
  void param_init_d3array::copy_value_to_vector(const dvector& x, const int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

/**
 * Description not yet available.
 * \param
 */
void param_init_d3array::restore_value_from_vector(const dvector& x,
  const int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

/**
 * Description not yet available.
 * \param
 */
  void param_init_d3array::save_value(const ofstream& ofs,int prec)
  {
    ofs << setw(prec+6) << setprecision(prec) << dvar3_array(*this) << endl;
  }

/**
 * Description not yet available.
 * \param
 */
  void param_init_d3array::allocate(int smin,int smax,int rmin,int rmax,
    int cmin,int cmax,const char * s)
  {
    allocate(smin,smax,rmin,rmax,cmin,cmax,phase_start,s);
  }

/**
 * Description not yet available.
 * \param
 */
  void param_init_d3array::allocate(int smin,int smax,int rmin,int rmax,
    int cmin,int cmax,int phase_start, const char * s)
  {
    named_dvar3_array::allocate(smin,smax,rmin,rmax,cmin,cmax,s);
    initial_params::allocate(phase_start);
    if (ad_comm::global_parfile)
    {
      *(ad_comm::global_parfile) >> dvar3_array(*this);
    }
    else
    {
      dvar3_array::operator=(initial_value);
    }
  }

/**
 * Description not yet available.
 * \param
 */
void param_init_d3array::hess_scale(const dvector& v, const dvector& x,
  const int& ii)
  {
    int smin=slicemin();
    int smax=slicemax();
    for (int k=smin;k<=smax;i++)
    {
      int mmin=(*this(k)).rowmin();
      int mmax=(*this(k)).rowmax();
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

/**
 * Description not yet available.
 * \param
 */
void param_init_d3array::sd_scale(const dvector& v, const dvector& x,
  const int& ii)
  {
    int smin=slicemin();
    int smax=slicemax();
    for (int k=smin;k<=smax;i++)
    {
      int mmin=(*this(k)).rowmin();
      int mmax=(*this(k)).rowmax();
      for (int i=mmin;i<=mmax;i++)
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

/**
 * Description not yet available.
 * \param
 */
cifstream& operator>>(const cifstream& s, param_init_3darray& m)
{
  s >> dvar3_array(m);
  return s;
}

/**
 * Description not yet available.
 * \param
 */
void param_init_d3array::restore_value(const ifstream& ofs)
{
  ofs  >> dvar3_array(*this);
}
