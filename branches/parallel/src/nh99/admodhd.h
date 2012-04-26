/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
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
#ifndef __ADMOD3D__
#define __ADMOD3D__

#if defined(__GNUC__)
  #if (__GNUC__ < 3)
    #pragma interface
  #endif
#else
  #pragma interface
#endif

#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
class param_init_d3array: public named_dvar3_array,public initial_params
{
public:

  virtual void set_value(const dvar_vector& x,BOR_CONST int& ii,BOR_CONST dvariable& pen);
  virtual void copy_value_to_vector(BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void restore_value_from_vector(BOR_CONST dvector&,BOR_CONST int&);
  virtual void set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual int size_count(void);
  virtual void save_value(void);
  virtual void save_value(BOR_CONST ofstream& ofs,int prec);
  virtual void restore_value(BOR_CONST ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  virtual void sd_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void hess_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii){};

public:

  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,
    int cmin,int cmax,int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,
    int cmin,int cmax, const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,
    int cmax,int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,
    int cmax,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,
    int cmax,int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,
    int cmax,const char * = "UNNAMED");
  param_init_d3array(void);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_d3array: public param_init_d3array
{
  double minb;
  double maxb;
public:

  virtual void set_value(const dvar_vector& x,BOR_CONST int& ii,BOR_CONST dvariable& pen);
  virtual void set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void sd_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii);
  virtual void hess_scale(BOR_CONST dvector& d,BOR_CONST dvector& x,BOR_CONST int& ii){};

public:

  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,_CONST ivector& rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int smin,int smax,int rmin,_CONST ivector& rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");

  param_init_bounded_d3array(void);
};
#endif

