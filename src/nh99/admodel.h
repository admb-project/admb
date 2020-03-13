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
#ifndef _ADMODEL_H_
#define _ADMODEL_H_

#define USE_SHARE_FLAGS
//#define DO_PROFILE
#define __MINI_MAX__
#if defined(__GNUC__) && (__GNUC__ < 3)
  #pragma interface
#endif


  class laplace_approximation_calculator;
  void cleanup_laplace_stuff(laplace_approximation_calculator *);

#include <fvar.hpp>

//#include <d4arr.hpp>
#include <cifstrem.h>

#include <adstring.hpp>
class init_xml_doc;

//#define _ADSTD_ std::
#define param_matrix named_dvar_matrix
#define param_vector named_dvar_vector
#define param_number named_dvariable
#define param_3array named_dvar3_array
#define param_4array named_dvar4_array
#define param_5array named_dvar5_array
#define param_6array named_dvar6_array
#define param_7array named_dvar7_array

#define SPparam_matrix SPnamed_dvar_matrix
#define SPparam_vector SPnamed_dvar_vector
#define SPparam_number SPnamed_dvariable
#define SPparam_3array SPnamed_dvar3_array
#define SPparam_4array SPnamed_dvar4_array
  double mfexp(const double);
  dvariable mfexp(const prevariable& v1);
  dvar_vector mfexp(const dvar_vector&);
  dvector mfexp(const dvector&);

  class param_init_bounded_number_vector;
  class model_parameters;
  extern int AD_gaussflag;

  extern function_minimizer * pfm;
  extern int traceflag;
  extern int ADqd_flag;
/*
 void set_value_inv(const dvariable& x, const dvector& v, const int& ii);
 void set_value_inv(const dvar_matrix& x, const dvector& v, const int& ii);
 void set_value_inv(const dvar_vector&, const dvector&, const int &ii);
 void set_value_inv(const dvariable& u, const dvector& x, const int& ii,
   const double fmin, const double fmax);
 void set_value_inv(const dvar_matrix& u, const dvector& x, const int& ii,
  const double fmin,const double fmax);
 void set_value_inv(const dvar3_array& u, const dvector& x, const int& ii,
  const double fmin,const double fmax);
 void set_value_inv(const dvar3_array& u, const dvector& x, const int& ii);
*/

  void copy_value_to_vector(const prevariable& x, const dvector& v,
    const int& ii);
  void copy_value_to_vector(const dvar_vector& x, const dvector& v,
    const int& ii);
  void copy_value_to_vector(const dvar_matrix& x, const dvector& v,
    const int& ii);
  void copy_value_to_vector(const dvar3_array& x, const dvector& v,
    const int& ii);

  void restore_value_from_vector(const prevariable& x, const dvector& v,
    const int& ii);
  void restore_value_from_vector(const dvar_vector& x, const dvector& v,
    const int& ii);
  void restore_value_from_vector(const dvar_matrix& x, const dvector& v,
    const int& ii);
  void restore_value_from_vector(dvar3_array& x, const dvector& v,
    const int& ii);

/**
 * Description not yet available.
 * \param
 */
class AD_matherror
{
public:
#if defined (_BORLANDC_)
  exception * err;
  AD_matherror(exception * _err) : err(_err) {;}
#endif
#if defined (_MSC_VER)
  _exception * err;
  AD_matherror(_exception * _err) : err(_err) {;}
#endif
};

class model_data;

/**
 * Description not yet available.
 * \param
 */
class label_class
{
  const char * name;
  friend ostream& operator<<(const ostream& s, const label_class& lc);
  friend class model_name_tag;
public:
  const char * mychar(void) { return name;}
  label_class(const char * s){name=s;}
};

/**
 * Description not yet available.
 * \param
 */
class model_name_tag
{
protected:
  adstring name;
  //friend ostream& operator<<(const ostream& os, const model_name_tag& mnt);
public:
  model_name_tag(void){;}
  void allocate(const char * s);
  label_class label(void){return (char*)(name);}
  const char * get_name(void) { return name;}
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar_vector : public dvar_vector, public model_name_tag
{
protected:
  named_dvar_vector(void) : dvar_vector(), model_name_tag() {;}
  named_dvar_vector& operator=(const dvar_vector& m);
  named_dvar_vector& operator=(const dvector& m);
  named_dvar_vector& operator=(const double m);
  named_dvar_vector& operator=(const prevariable& m);
  friend class model_parameters;
  void allocate(int mmin,int mmax,const char * s);
  void allocate(const char * s);
};

/**
 * Description not yet available.
 * \param
 */
class equality_constraint_vector : public named_dvar_vector
{
protected:
  equality_constraint_vector(void);
  equality_constraint_vector& operator=(const dvar_vector& m);
  equality_constraint_vector& operator=(const dvector& m);
  equality_constraint_vector& operator=(const double m);
  equality_constraint_vector& operator=(const prevariable& m);
  friend class model_parameters;
  void allocate(int mmin,int mmax,const char * s);
};

/**
 * Description not yet available.
 * \param
 */
class inequality_constraint_vector : public named_dvar_vector
{
protected:
  inequality_constraint_vector(void);
  inequality_constraint_vector& operator=(const dvar_vector& m);
  inequality_constraint_vector& operator=(const dvector& m);
  inequality_constraint_vector& operator=(const double m);
  inequality_constraint_vector& operator=(const prevariable& m);
  friend class model_parameters;
  void allocate(int mmin,int mmax,const char * s);
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_vector : public named_dvar_vector
{
  double * pd;
public:
  ~dll_param_vector();
  void allocate(double *_pd,int mmin,int mmax,const char * s);
  dll_param_vector& operator=(const dvar_vector& m);
  dll_param_vector& operator=(const dvector& m);
  dll_param_vector& operator=(const double m);
  dll_param_vector& operator=(const prevariable& m);
};

/**
 * Description not yet available.
 * \param
 */
class named_dvariable : public dvariable, public model_name_tag
{
  //named_dvariable& operator=(const dvariable& m);
protected:
  named_dvariable(void) : dvariable(), model_name_tag() {;}
  void allocate(const char * s);
  named_dvariable& operator=(const prevariable& m);
  named_dvariable& operator=(const double m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_number : public named_dvariable
{
  double * pd;
protected:
  //named_dvariable(void) : dvariable(), model_name_tag() {;}
  void allocate(double *_d,const char * s);
  dll_param_number& operator=(const prevariable& m);
  dll_param_number& operator=(const double m);
  virtual ~dll_param_number();
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar_matrix : public dvar_matrix, public model_name_tag
{
protected:
  named_dvar_matrix(void) : dvar_matrix(), model_name_tag() {;}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
  void allocate(int rmin,int rmax,const char * s);
  void allocate(const char * s);
  //void allocate(int rmin,int rmax,int,const ivector&, const char * s);
  void allocate(
    int rmin, int rmax,
    const index_type& cmin, const index_type& cmax,
    const char* s);
public:
  named_dvar_matrix& operator=(const double m);
  named_dvar_matrix& operator=(const dmatrix& m);
  named_dvar_matrix& operator=(const dvar_matrix& m);
  named_dvar_matrix& operator=(const dvariable& m);

  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_matrix : public named_dvar_matrix
{
  double * pd;
public:
  //named_dvar_matrix(void) : dvar_matrix(), model_name_tag() {;}
  void allocate(double * ,int rmin,int rmax,int cmin,int cmax,const char * s);
  void allocate(double * ,int rmin,int rmax,const index_type&
     ,const index_type& ,const char * s);
  dll_param_matrix& operator=(const dvariable& m);
  dll_param_matrix & operator = (const double m);
  dll_param_matrix& operator=(const dmatrix& m);
  dll_param_matrix& operator=(const dvar_matrix& m);
  virtual ~dll_param_matrix();
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar3_array : public dvar3_array, public model_name_tag
{
protected:
  named_dvar3_array(void) : dvar3_array(), model_name_tag() {;}
 void allocate(const ad_integer& sl,const ad_integer& sh,
  const index_type& nrl,const index_type& nrh,const index_type& ncl,
    const index_type& nch,const char * s="UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * s="UNNAMED");

  void allocate(int hsl,int hsu,int rmin,int rmax,const char * s="UNNAMED");
  void allocate(int hsl,int hsu,const index_type& rmin,const index_type& rmax,
    const char * s="UNNAMED");
  void allocate(int hsl,int hsu,const char * s="UNNAMED");
  void allocate(const char * s="UNNAMED");


  void allocate(int hsl, int hsu, const ivector& rmin, int rmax,
                int cmin, int cmax, const char *s = "UNNAMED");
  void allocate(int hsl, int hsu, int rmin, const ivector& rmax,
    int cmin,int cmax,const char * s="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, const ivector& rmax,
    int cmin,int cmax,const char * s="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
    int cmax,const char * s="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                const ivector& cmax, const char *s = "UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,
                const ivector& cmax, const char *s = "UNNAMED");
  named_dvar3_array& operator=(const dvar3_array& m);
  named_dvar3_array& operator=(const d3_array& m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar4_array : public dvar4_array, public model_name_tag
{
protected:
  named_dvar4_array(void) : dvar4_array(), model_name_tag() {;}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,const char * s);
  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const index_type&,const index_type&,
    const char *s);

  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const char *s);

  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const char *s);
  void allocate(ad_integer,ad_integer,const char *s);
  void allocate(const char *s);

  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
    const char * s);
  void allocate(int hhsl,int hhsu,int hsl,int hsu,const char * s);
  void allocate(int hhsl,int hhsu,const char * s);

  named_dvar4_array& operator=(const dvar4_array& m);
  named_dvar4_array& operator=(const d4_array& m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar5_array : public dvar5_array, public model_name_tag
{
protected:
  named_dvar5_array(void) : dvar5_array(), model_name_tag() {;}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,
  int l5,int u5,
  const char * s);

  void allocate(const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,
    const char * s);

  named_dvar5_array& operator=(const dvar5_array& m);
  named_dvar5_array& operator=(const d5_array& m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar6_array : public dvar6_array, public model_name_tag
{
protected:
  named_dvar6_array(void) : dvar6_array(), model_name_tag() {;}
  void allocate(int hhsl,int hhsu,
    int hsl,int hsu,
    int rmin,int rmax,
    int cmin,int cmax,
    int l5,int u5,
    int l6,int u6,
    const char * s);

  void allocate(const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,
    const index_type& l5,const index_type& u5,
    const char * s);

  named_dvar6_array& operator=(const dvar6_array& m);
  named_dvar6_array& operator=(const d6_array& m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar7_array : public dvar7_array, public model_name_tag
{
protected:
  named_dvar7_array(void) : dvar7_array(), model_name_tag() {;}
  void allocate(
    int hhsl,int hhsu,
    int hsl,int hsu,
    int rmin,int rmax,
    int cmin,int cmax,
    int l5,int u5,
    int l6,int u6,
    int l7,int u7,
    const char * s);

  void allocate(const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,
    const index_type& l5,const index_type& u5,
    const index_type& l6,const index_type& u6,
    const char * s);

  named_dvar7_array& operator=(const dvar7_array& m);
  named_dvar7_array& operator=(const d7_array& m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvector : public dvector, public model_name_tag
{
protected:
  named_dvector(void) : dvector(), model_name_tag() {;}
  void allocate(int mmin,int mmax,const char * s);
  void allocate(const char * s);
  void allocate(int mmin, const ivector& mmax, const char *s);
  named_dvector& operator=(const dvector& m);
  named_dvector& operator=(const double m);
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class named_ivector : public ivector, public model_name_tag
{
protected:
  named_ivector(void) : ivector(), model_name_tag() {;}
  void allocate(int mmin,int mmax,const char * s);
};

/**
 * Description not yet available.
 * \param
 */
class named_dmatrix : public dmatrix, public model_name_tag
{
protected:
  named_dmatrix(void) : dmatrix(), model_name_tag() {;}
  void allocate(int rmin,int rmax,const char * s);
  void allocate(const char * s);
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
  void allocate(int rmin,int rmax,const ivector& cmin,int cmax,const char * s);
  void allocate(int rmin,int rmax,const ivector& cmin,const ivector& cmax,
    const char * s);
  void allocate(int rmin,int rmax,int cmin,const ivector& cmax,const char * s);
  named_dmatrix& operator=(const dmatrix& m);
  named_dmatrix& operator=(const double m);
};

/**
 * Description not yet available.
 * \param
 */
class named_imatrix : public imatrix, public model_name_tag
{
protected:
  named_imatrix(void) : imatrix(), model_name_tag() {;}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
  void allocate(int rmin, int rmax, const index_type& cmin,
                const index_type& cmax, const char *s);
  named_imatrix& operator=(const imatrix& m);
  named_imatrix& operator=(const int& m);
};

/**
 * Description not yet available.
 * \param
 */
class named_d3_array : public d3_array, public model_name_tag
{
protected:
  named_d3_array(void) : d3_array(), model_name_tag() {;}
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * s);
  void allocate(int hsl, int hsu, const index_type& rmin,
                const index_type& rmax, const index_type& cmin,
                const index_type& cmax, const char *s);
  void allocate(int hsl, int hsu, const ivector& rmin, int rmax,
    int cmin,int cmax,const char * s);
  void allocate(int hsl, int hsu, int rmin, const ivector& rmax,
    int cmin,int cmax,const char * s);
  void allocate(int hsl, int hsu, const ivector& rmin, const ivector& rmax,
    int cmin,int cmax,const char * s);
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
    int cmax, const char * s);
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,
                const ivector& cmax, const char *s);
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                const ivector& cmax, const char *s);
  named_d3_array& operator=(const d3_array& m);

  void allocate(int hsl,int hsu,const index_type& rmin,const index_type& rmax,
    const char * s);
  void allocate(int hsl,int hsu,int rmin,int rmax,const char * s);
  void allocate(int hsl,int hsu,const char * s);
  void allocate(const char * s);
};

/**
 * Description not yet available.
 * \param
 */
class named_i3_array : public i3_array, public model_name_tag
{
protected:
  named_i3_array(void) : i3_array(), model_name_tag() {;}
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * s);
  void allocate(int hsl, int hsu, const index_type& rmin,
                const index_type& rmax, const index_type& cmin,
                const index_type& cmax, const char *s);
  named_i3_array& operator=(const i3_array& m);
};

/**
 * Description not yet available.
 * \param
 */
class named_d4_array : public d4_array, public model_name_tag
{
protected:
  named_d4_array(void) : d4_array(), model_name_tag() {;}
  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const index_type&,const index_type&,
    const char * s);
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,
    int rmax,int cmin,int cmax,const char * s);

  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,
    int rmax,const char * s);
  void allocate(int hhsl,int hhsu,int hsl,int hsu,const char * s);
  void allocate(int hhsl,int hhsu,const char * s);
  void allocate(const char * s);

  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const char * s);
  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const char * s);
  void allocate(ad_integer,ad_integer,const char * s);


  named_d4_array& operator=(const d4_array& m);
};
class named_i4_array : public i4_array, public model_name_tag
{
protected:
  named_i4_array(void) : i4_array(), model_name_tag() {;}
  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const index_type&,const index_type&,
    const char * s);
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,
    int rmax,int cmin,int cmax,const char * s);

  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,
    int rmax,const char * s);
  void allocate(int hhsl,int hhsu,int hsl,int hsu,const char * s);
  void allocate(int hhsl,int hhsu,const char * s);
  void allocate(const char * s);

  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const char * s);
  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const char * s);
  void allocate(ad_integer,ad_integer,const char * s);


  named_i4_array& operator=(const i4_array& m);
};

/**
 * Description not yet available.
 * \param
 */
class named_d5_array : public d5_array, public model_name_tag
{
protected:
  named_d5_array(void) : d5_array(), model_name_tag() {;}
  void allocate(int l5,int u5,int hhsl,int hhsu,int hsl,int hsu,int rmin,
    int rmax,int cmin,int cmax,const char * s);
  void allocate(const ad_integer& hhsl,const ad_integer& hhsu,
    const index_type& hsl,const index_type& hsu, const index_type& sl,
    const index_type& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,const char * s);

  named_d5_array& operator=(const d5_array& m);
};

/**
 * Description not yet available.
 * \param
 */
class named_d6_array : public d6_array, public model_name_tag
{
protected:
  named_d6_array(void) : d6_array(), model_name_tag() {;}
  void allocate(int l6,int u6,int l5,int u5,int hhsl,int hhsu,int hsl,
    int hsu,int rmin,int rmax,int cmin,int cmax,const char * s);
  void allocate(const ad_integer& l6,const ad_integer& u6,
    const index_type& l5,const index_type& u5,
    const index_type& hhsl,const index_type& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const char * s);

  named_d6_array& operator=(const d6_array& m);
};

/**
 * Description not yet available.
 * \param
 */
class named_d7_array : public d7_array, public model_name_tag
{
protected:
  named_d7_array(void) : d7_array(), model_name_tag() {;}
  void allocate(int l7,int u7,int l6,int u6,int l5,int u5,int hhsl,
    int hhsu,int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * s);
  void allocate(const ad_integer& l7,const ad_integer& u7,
    const index_type& l6,const index_type& u6,
    const index_type& l5,const index_type& u5,
    const index_type& hhsl,const index_type& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const char * s);

  named_d7_array& operator=(const d7_array& m);
};


class function_minimizer;

#if defined(USE_ADPVM)
/**
 * Description not yet available.
 * \param
 */
class pvm_params
{
  static pvm_params * varsptr[]; // this should be a resizeable array
  static int num_pvm_params;
  static const int maxnum_pvm_params;
  void add_to_list(void);
  virtual void send_to_slaves(void)=0;
  virtual void get_from_master(void)=0;
public:
  static void pvm_params::send_all_to_slaves(void);
  static void pvm_params::get_all_from_master(void);
  void allocate(const char *);
  void allocate(void);
};

/**
 * Description not yet available.
 * \param
 */
class pvm_number : public pvm_params
{
public:
  virtual void send_to_slaves(void);
  virtual void get_from_master(void);
  dvector v;
  double d;
  operator double();
  void assign(const dvector&);
  void assign(double);
};

/**
 * Description not yet available.
 * \param
 */
class pvm_int : public pvm_params
{
public:
  virtual void send_to_slaves(void);
  virtual void get_from_master(void);
  ivector v;
  int d;
  operator int();
  void assign(const ivector&);
  void assign(int);
};
#endif // #if defined(USE_ADPVM)

class initial_params;
typedef initial_params* pinitial_params;
typedef void* ptovoid;
/**
For storing void pointers in a array.
*/
class adlist_ptr
{
  ptovoid* ptr;
  unsigned int current_size;
  unsigned int current;
  void resize(void);
  void add_to_list(void* p);
public:
  adlist_ptr(unsigned int init_size);
  ~adlist_ptr();

  void initialize();

  pinitial_params& operator[](int i);

  friend class initial_params;
};

#if defined(USE_SHARE_FLAGS)

/**
 * Description not yet available.
 * \param
 */
  class shareinfo
  {
    index_type * sflags;
    index_type * original_sflags;
    index_type * aflags;
    index_type * invflags;
    i3_array * bmap;
    int dimension;
    int maxshare;
    int current_phase;
  public:
    void get_inv_matrix_shared( int _cf);
    void get_inv_vector_shared( int _cf);
    int & get_maxshare(void) { return maxshare; }
    i3_array & get_bmap(void);
    int & get_dimension(void){ return dimension;}
    index_type * get_original_shareflags(void);
    index_type * get_shareflags(void);
    int& get_current_phase(void);
    index_type * get_activeflags(void);
    index_type * get_invflags(void);
    void set_shareflags(const index_type& sf);
    void set_original_shareflags(const index_type& sf);
    void reset_shareflags(const index_type& sf);
    void set_activeflags(const index_type& af);
    void set_bmap(const i3_array& af);
    void reset_bmap(const i3_array& af);
    void set_invflags(const index_type& af);
    shareinfo(const index_type& sf,const index_type& af);
    ~shareinfo();
  };
#endif

/**
 * Description not yet available.
 * \param
 */
class initial_params
{
protected:
#if defined(USE_SHARE_FLAGS)
  shareinfo * share_flags;
#endif
  virtual ~initial_params();
  int active_flag;
  int initial_value_flag;
  double initial_value;
  double scalefactor;
public:
#if defined(USE_SHARE_FLAGS)
  virtual void setshare(const index_type& sf,const index_type& af);
  virtual void shared_set_value_inv(const dvector&,const int&);
  virtual void shared_set_value(const dvar_vector&,const int&,
    const dvariable& pen);
  virtual int shared_size_count(void); // get the number of active parameters
#endif
  double get_scalefactor();
  void set_scalefactor(const double);
  //Resizeable arrays
#if defined(USE_PTR_INIT_PARAMS)
  static initial_params* varsptr[];
#else
  static adlist_ptr varsptr;
#endif
  static int num_initial_params;
  static const int max_num_initial_params;
  static int straight_through_flag;
  static int num_active_initial_params;
  static int max_number_phases;
  static int current_phase;
  static int restart_phase;
  static int sd_phase;
  static int mc_phase;
  static int mceval_phase;
  int phase_start;
  int phase_save;
  int phase_stop;
  virtual void set_random_effects_active();
  void restore_phase_start(void);
  virtual void set_random_effects_inactive();
  virtual void set_only_random_effects_active();
  virtual void set_only_random_effects_inactive();
  virtual void set_value(const dvar_vector&, const int&,
    const dvariable& pen) = 0;
  virtual void dev_correction(const dmatrix&, const int&) = 0;
  void set_initial_value(double x);
  double get_initial_value(void);
  void set_phase_start(int x);
  int get_phase_start(void);
  static void set_all_simulation_bounds(const dmatrix& symbds);
  static void set_all_simulation_bounds(const dmatrix& symbds, const dvector&);
  static void get_jacobian_value(const dvector& y, const dvector& jac);
  static int correct_for_dev_objects(const dmatrix &H);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii) = 0;
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
  //  const int& ii) = 0;
  virtual void set_value_inv(const dvector&, const int&) = 0;
  virtual void add_value(const dvector&, const int&) = 0;
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&) = 0;
  virtual void get_jacobian(const dvector&, const dvector&, const int&) = 0;
  //virtual void check_tightness(const dvector&, const int&) = 0;
  virtual void copy_value_to_vector(const dvector&, const int&) = 0;
  virtual void restore_value_from_vector(const dvector&, const int&) = 0;
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii) = 0;
  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii)=0;
  virtual void mc_scale(const dvector& d, const dvector& x, const int& ii) = 0;
  virtual void curv_scale(const dvector& d, const dvector& x,
    const int& ii) = 0;
  virtual void hess_scale(const dvector& d, const dvector& x,
    const int& ii) = 0;
  virtual unsigned int size_count() const = 0; // get the number of active parameters

  // save the objects value in to a text file
  virtual void save_value(ofstream& ofs) = 0;

  // save the objects value in a binary file
  virtual void bsave_value(uostream& uos) = 0;

  virtual void save_value(const ofstream& ofs, int prec) = 0;
  virtual void save_value(const ofstream& ofs, int prec,const dvector&,
    int& offset)=0;
  virtual const char* label() = 0;
  void allocate(int _phase_start);
  void set_active_flag(void);
  void set_inactive_flag(void);
  friend int active(const initial_params& ip);
  static adstring get_reportfile_name(void);
  initial_params(void);
  static void xinit(const dvector& x); // get the number of active parameters
  // get the number of active parameters
  static void xinit_all(const dvector& x);
  static void save_all(const ofstream& _ofs,int prec,const dvector&g);
  // get the number of active parameters
  static void set_active_random_effects(void);
  // get the number of active parameters
  static void set_active_only_random_effects(void);
  // get the number of active parameters
  static void set_inactive_only_random_effects(void);
  // get the number of active parameters
  static void set_inactive_random_effects(void);
  // get the number of active parameters
  static void restore_start_phase(void);
  static void xinit1(const dvector& x, const dvector& g);
  //save all initial parameter values in a vector
  static void copy_all_values(const dvector& x, const int& ii);
  //get ivalues for all active parameters from a vector
  static void restore_all_values(const dvector& x, const int& ii);
  // get the number of active parameters
  static dvariable reset(const dvar_vector& x);
  // get the number of active parameters
  static dvariable reset(const dvector& x);
  static dvariable reset1(const dvar_vector& x, const dvector& g);
  // get the number of active parameters
  static dvariable reset(const dvar_vector& x, const dvector& pen);
  // get the number of active parameters
  static dvariable reset_all(const dvar_vector& x,const dvector& pen);
  static int nvarcalc();
  static int nvarcalc_all(void);
  static int num_active_calc(void);
  static int stddev_scale(const dvector& d, const dvector& x);
  static int stddev_vscale(const dvar_vector& d,const dvar_vector& x);
  static int montecarlo_scale(const dvector& d, const dvector& x);
  static int stddev_curvscale(const dvector& d, const dvector& x);
  static void read(void);
  static void save(void);
  static void save(const ofstream& ofs, int prec);
  static void restore(const ifstream& ifs);
  static void add_random_vector(const dvector& x);
  static void add_random_vector(const dvector& y, const dvector& x,
    const double& ll, const dvector& diag);
  virtual void restore_value(const ifstream& ifs) = 0;
  virtual void add_to_list(void);
#if defined(USE_ADPVM)
  virtual void pvm_pack(void)=0;
  virtual void pvm_unpack(void)=0;
#endif

  friend class function_minimizer;
};

void pvm_pack(const dvar_vector&);
void pvm_unpack(const dvar_vector&);
void pvm_pack(const prevariable&);
void pvm_unpack(const prevariable&);
void pvm_pack(const dvar_matrix&);
void pvm_unpack(const dvar_matrix&);

/**
 * Description not yet available.
 * \param
 */
class param_init_vector: public named_dvar_vector, public initial_params
{
public:
#if defined(USE_SHARE_FLAGS)
  virtual void setshare(const index_type& sf,const index_type& af);
  virtual void shared_set_value_inv(const dvector&,const int&);
  virtual void shared_set_value(const dvar_vector&,const int&,
    const dvariable& pen);
  virtual int shared_size_count(void); // get the number of active parameters
#endif
  virtual void dev_correction(const dmatrix& H, const int& ii);
  virtual const char * label(void);
  param_init_vector();
#if defined(USE_ADPVM)
  void pvm_pack(void){::pvm_pack(*this);}
  void pvm_unpack(void){::pvm_unpack(*this);}
#endif
private:
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
  //  const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii);

  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual unsigned int size_count() const;
  virtual void sd_scale(const dvector& d, const dvector& x, const int&);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x,const int&);
  virtual void hess_scale(const dvector&, const dvector&, const int&){}
  virtual void save_value(ofstream& ofs);
  virtual void bsave_value(uostream& uos);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void save_value(const ofstream& ofs, int prec,const dvector&,
    int& offset);
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  void allocate(int imin,int imax,int phasestart=1,const char * s="UNNAMED");
  void allocate(const ad_integer& imin,const ad_integer& imax,
    const ad_integer& phasestart=1,const char * s="UNNAMED");
  void allocate(int imin,int imax,const char * s="UNNAMED");
#if defined(USE_SHARE_FLAGS)
  void allocate(int imin,int imax,const ivector& ishare,
    const char * s="UNNAMED");
#endif
  friend class model_parameters;
  friend class param_init_vector_vector;
public:
  param_init_vector& operator = (const dvector&);
  param_init_vector& operator = (const dvar_vector&);
  param_init_vector& operator = (const prevariable&);
  param_init_vector& operator = (const double&);
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_init_vector: public param_init_vector
{
  double* pd;

public:
  virtual ~dll_param_init_vector();

  dll_param_init_vector& operator=(const dvector&);
  dll_param_init_vector& operator=(const dvar_vector&);
  dll_param_init_vector& operator=(const prevariable&);
  dll_param_init_vector& operator=(const double&);

  void allocate(double* _pd,
    int imin, int imax,
    int phasestart = 1,
    const char* s = "UNNAMED");
  void allocate(double* _pd,
    int imin, int imax,
    const char* s="UNNAMED");

  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_vector: public named_dvar_vector, public initial_params
{
  virtual void* parent_this(void){return this;}
public:
  double get_minb(void);
  void set_minb(double b);
  double get_maxb() const;
  void set_maxb(double b);
protected:
  double minb;
  double maxb;
  param_init_bounded_vector();
private:
  virtual void dev_correction(const dmatrix&, const int&);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
  //  const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual unsigned int size_count() const;
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector&, const dvector&, const int&){}
  void allocate(int imin,int imax,double _minb,double _maxb,
    int phasestart=1, const char * name="UNNAMED");
  void allocate(int imin,int imax,double _minb,double _maxb,
    const char * name="UNNAMED");
 //void param_init_bounded_vector::allocate(const ad_integer& imin,
   //const ad_integer& imax,const ad_double& _minb,const ad_double& _maxb,
   //const ad_integer& phase_start,const char * s);
  friend class model_parameters;
  friend class param_init_bounded_vector_vector;
  virtual const char * label(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void save_value(const ofstream& ofs, int prec,const dvector&,
    int& offset);
  virtual void restore_value(const ifstream& ifs);
  virtual void save_value(ofstream& ofs);
  virtual void bsave_value(uostream& uos);
  void report_value(void);
  //virtual void read_value(void);
public:
  param_init_bounded_vector& operator = (const dvector&);
  param_init_bounded_vector& operator = (const dvar_vector&);
  param_init_bounded_vector& operator = (const prevariable&);
  param_init_bounded_vector& operator = (const double&);
#if defined(USE_ADPVM)
  void pvm_pack(void){::pvm_pack(*this);}
  void pvm_unpack(void){::pvm_unpack(*this);}
#endif
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_init_bounded_vector: public param_init_bounded_vector
{
  double * pd;
public:
  void allocate(double * _pd,int imin,int imax,double _minb,double _maxb,
    int phasestart=1, const char * name="UNNAMED");
  void allocate(double * _pd,int imin,int imax,double _minb,double _maxb,
    const char * name="UNNAMED");
  ~dll_param_init_bounded_vector();
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_dev_vector: public param_init_bounded_vector
{
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void dev_correction(const dmatrix& H, const int& ii);
public:
  param_init_bounded_dev_vector& operator = (const dvar_vector& m);
  param_init_bounded_dev_vector& operator = (const dvector& m);
  param_init_bounded_dev_vector& operator = (const prevariable& m);
  param_init_bounded_dev_vector& operator = (const double& m);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_number: public named_dvariable, public initial_params
{
  virtual void dev_correction(const dmatrix&, const int&);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);

#if defined(USE_ADPVM)
  void pvm_pack(void){::pvm_pack(*this);}
  void pvm_unpack(void){::pvm_unpack(*this);}
#endif

//  virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
//    const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual unsigned int size_count() const;
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void save_value(const ofstream& ofs, int prec,const dvector&,
    int& offset);
  virtual void restore_value(const ifstream& ifs);
  virtual void save_value(ofstream& ofs);
  virtual void bsave_value(uostream& uos);
  void report_value(void);
  virtual const char * label(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector&, const dvector&, const int&){}
  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii);
  //virtual void read_value(void);
protected:
  void allocate(int phase_start=1,const char *s="UNNAMED");
  void allocate(const char *s="UNNAMED");
  void allocate(init_xml_doc&, const char *s="UNNAMED");
  friend class model_parameters;
  friend class param_init_number_vector;
  param_init_number();
  param_init_number& operator=(const double m);
  param_init_number& operator=(const prevariable& m);
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_init_number: public param_init_number
{
  double* pd;
public:
  dll_param_init_number(): pd(NULL) {}
  virtual ~dll_param_init_number();

  dll_param_init_number& operator=(const double m);
  dll_param_init_number& operator=(const prevariable& m);

  void allocate(double* pd, int phase_start = 1, const char* s = "UNNAMED");
  void allocate(double* pd, const char *s = "UNNAMED");
};

//forward declaration
class data_vector;
/**
 * Description not yet available.
 * \param
 * \author Dave Founier & Steve Martell
 * Overloaded allocate function to recieve a data_vector from an input file.
 */
class param_init_bounded_number: public param_init_number
{
public:
  double get_minb(void);
  void set_minb(double b);
  double get_maxb() const;
  void set_maxb(double b);
protected:
  double minb;
  double maxb;
  void allocate(double _minb,double _maxb,int phase_start=1,
    const char * s="UNNAMED");
  void allocate(double _minb,double _maxb,const char * s="UNNAMED");
  // Added by Steve Martell for using input data for allocation.
  void allocate(const data_vector& v,const char * s="UNNAMED");
  void allocate(init_xml_doc&, const char * s="UNNAMED");

public:
#if defined(USE_ADPVM)
  void pvm_pack(void){::pvm_pack(*this);}
  void pvm_unpack(void){::pvm_unpack(*this);}
#endif
  param_init_bounded_number();
private:
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
//virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
//  const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector&, const dvector&, const int&){}
  virtual const char * label(void);
  void report_value(void);
  param_init_bounded_number& operator=(const double m);
  param_init_bounded_number& operator=(const prevariable& m);
  friend class model_parameters;
  friend class param_init_bounded_number_vector;
  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii);
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_init_bounded_number: public param_init_bounded_number
{
  double * pd;
public:
  void allocate(double * _pd,double _minb,double _maxb,int phase_start=1,
    const char * s="UNNAMED");
  void allocate(double* _pd,double _minb, double _maxb,const char* s="UNNAMED");
public:
  virtual ~dll_param_init_bounded_number();
  void report_value(void);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_matrix: public named_dvar_matrix,public initial_params
{
#if defined(USE_SHARE_FLAGS)
  virtual void shared_set_value_inv(const dvector& x,const int& ii);
  virtual int shared_size_count(void); // get the number of active parameters
  virtual void shared_set_value(const dvar_vector&,const int&,
    const dvariable& pen);
#endif
  virtual void dev_correction(const dmatrix&, const int&);
  virtual void set_simulation_bounds(const dmatrix& symbds,const int& ii);
#if defined(USE_ADPVM)
  void pvm_pack(void){::pvm_pack(*this);}
  void pvm_unpack(void){::pvm_unpack(*this);}
#endif
//virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
//  const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
public:
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual unsigned int size_count() const;
  virtual void save_value(ofstream& ofs);
  virtual void bsave_value(uostream& uos);
  virtual void save_value(const ofstream& ofs, int prec,const dvector&,
    int& offset);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector&, const dvector&, const int&){}
  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii);

public:
  void allocate(int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
#if defined(USE_SHARE_FLAGS)
  //void allocate(int rmin,int rmax,int cmin,int cmax, const imatrix& jshare,
  // const char * = "UNNAMED");
  virtual void setshare(const index_type& sf,const index_type& af);
#endif
  void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
 void allocate(const ad_integer& imin,const ad_integer&imax,
   const index_type& imin2,const index_type& imax2,
   const ad_integer& phase_start, const char * s);
  void allocate(const ad_integer& rmin, const ad_integer& rmax,
                const index_type& cmin, const index_type& cmax,
                const char * = "UNNAMED");
  void allocate(const ad_integer& rmin, const ad_integer& rmax,
                const index_type& cmin, const index_type& cmax,
                int phase_start = 1, const char * = "UNNAMED");
  param_init_matrix(void);
  param_init_matrix& operator = (const dmatrix& m);
  param_init_matrix& operator = (const dvar_matrix& m);
  param_init_matrix& operator = (const dvariable& m);
  param_init_matrix& operator = (const double& m);
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_init_matrix: public param_init_matrix
{
  double * d;
public:
  void allocate(double* _d,int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(double * _d,int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  virtual ~dll_param_init_matrix();
  dll_param_init_matrix(){d=NULL;}
  dll_param_init_matrix& operator = (const dmatrix& m);
  dll_param_init_matrix& operator = (const dvar_matrix& m);
  dll_param_init_matrix& operator = (const dvariable& m);
  dll_param_init_matrix& operator = (const double& m);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_matrix: public param_init_matrix
{
public:
  double get_minb(void);
  void set_minb(double b);
  double get_maxb() const;
  void set_maxb(double b);
protected:
  double minb;
  double maxb;
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
//virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
//  const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
public:
#if defined(USE_ADPVM)
  void pvm_pack(void){::pvm_pack(*this);}
  void pvm_unpack(void){::pvm_unpack(*this);}
#endif
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
#if defined(USE_SHARE_FLAGS)
  virtual void shared_set_value_inv(const dvector&,const int&);
  virtual void shared_set_value(const dvar_vector&,const int&,
    const dvariable& pen);
#endif
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector&, const dvector&, const int&){}
  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii);

public:
 void allocate(const ad_integer& imin,
   const ad_integer& imax, const ad_integer& imin2,
   const ad_integer& imax2, const ad_double& _bmin,
   const ad_double& _bmax, const ad_integer& phase_start,
   const char * s);

  param_init_bounded_matrix(void);
  void allocate(int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");

  void allocate(const ad_integer& rmin, const ad_integer& rmax,
    const index_type& cmin,
                const index_type& cmax, double _minb, double _maxb,
                const char * = "UNNAMED");
  void allocate(const ad_integer& rmin, const ad_integer& rmax,
    const index_type& cmin,
                const index_type& cmax, double _minb, double _maxb,
                int phase_start = 1, const char * = "UNNAMED");
};

/**
 * Description not yet available.
 * \param
 */
class data_int: public model_name_tag
{
protected:
  int val;

  data_int& operator=(const int);

  void allocate(int n,const char * s="UNNAMED");
  void allocate(const char * s="UNNAMED");
  void allocate(init_xml_doc&, const char * s="UNNAMED");

public:
  ~data_int() { }
  operator int() const { return val; }

  friend class model_data;
  friend class model_parameters;
  friend int operator + (int n,data_int v);
  friend int operator + (data_int v,int n);
  friend int operator + (data_int v,data_int n);
};

/**
 * Description not yet available.
 * \param
 */
class named_adstring : public adstring, public model_name_tag
{
protected:
  void allocate(const char * s1,const char * s="UNNAMED");
  void operator = (const adstring&);
  void operator = (const char *);
};

/**
 * Description not yet available.
 * \param
 */
class named_line_adstring : public line_adstring, public model_name_tag
{
protected:
  void allocate(const char* s1, const char* s = "UNNAMED");
  void operator=(const adstring&);
  void operator=(const char*);
};

/**
 * Description not yet available.
 * \param
 */
class init_adstring: public named_adstring
{
public:
  void allocate(const char * s="UNNAMED");
};

/**
 * Description not yet available.
 * \param
 */
class init_line_adstring: public named_line_adstring
{
public:
  void allocate(const char* s = "UNNAMED");
};

/**
 * Description not yet available.
 * \param
 */
class dll_named_adstring : public named_adstring
{
  char ** d;
public:
  void allocate(char ** ps1,const char * s="UNNAMED");
  void operator = (const adstring&);
  void operator = (const char *);
  ~dll_named_adstring();
  dll_named_adstring(void){d=NULL;}
};

/**
 * Description not yet available.
 * \param
 */
class dll_data_int : public data_int
{
public:
  int *pi;
  void allocate(int *_pi,const char * s);
  virtual ~dll_data_int();
};

/**
 * Description not yet available.
 * \param
 */
class data_matrix : public named_dmatrix
{
public:
  data_matrix(void) : named_dmatrix() {;}
  data_matrix& operator=(const dmatrix& m);
  data_matrix& operator=(const double& m);
private:
  void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  void allocate(int rmin, int rmax, const ivector& cmin, const ivector& cmax,
    const char * = "UNNAMED");
  void allocate(int rmin, int rmax, const ivector& cmin, int cmax,
    const char * = "UNNAMED");
  void allocate(int rmin, int rmax, int cmin, const ivector& cmax,
    const char * = "UNNAMED");
  void allocate(init_xml_doc&, const char * = "UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class dll_data_matrix : public data_matrix
{
  double * d;
public:
  void allocate(double * _d,int rmin,int rmax,int cmin,int cmax,
    const char * _s = "UNNAMED");
  virtual ~dll_data_matrix();
  dll_data_matrix& operator=(const dmatrix &m);
  dll_data_matrix& operator=(const double &m);
};

/**
 * Description not yet available.
 * \param
 */
class data_3array : public named_d3_array
{
public:
  data_3array(void) : named_d3_array() {;}
private:
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * ="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, const ivector& rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, const ivector& rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
    int cmax, const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                const ivector& cmax, const char * ="UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,
                const ivector& cmax, const char * ="UNNAMED");
  void allocate(int hsl,int hsu, const index_type& rmin, const index_type& rmax,
    const index_type& cmin, const index_type& cmax, const char * ="UNNAMED");
  friend class model_data;
};

class data_3iarray : public named_i3_array
{
  data_3iarray(void) : named_i3_array() {;}
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * ="UNNAMED");
  void allocate(int hsl, int hsu,const index_type& rmin, const index_type& rmax,
    const index_type& cmin, const index_type& cmax, const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class dll_data_3array : public data_3array
{
  double * d;
public:
  void allocate(double * _d,int hmin,int hmax,int rmin,int rmax,
    int cmin,int cmax,const char * _s = "UNNAMED");
  dll_data_3array& operator=(const d3_array &);
  virtual ~dll_data_3array();
  friend class model_data;
};


class data_7array : public named_d7_array
{
  data_7array(void) : named_d7_array() {;}
  void allocate(int l7,int u7,int l6,int u6,int l5,int u5,int hhsl,
    int hhsu,int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char* s="UNNAMED");
  void allocate(const ad_integer& l7,const ad_integer& u7,
    const index_type& l6,const index_type& u6,
    const index_type& l5,const index_type& u5,
    const index_type& hhsl,const index_type& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const char* s="UNNAMED");
  friend class model_data;
};

class data_6array : public named_d6_array
{
  data_6array(void) : named_d6_array() {;}
  void allocate(int l6,int u6,int l5,int u5,int hhsl,int hhsu,int hsl,
    int hsu,int rmin,int rmax,int cmin,int cmax,const char * s="UNNAMED");
  void allocate(const ad_integer& l6,const ad_integer& u6,
    const index_type& l5,const index_type& u5,
    const index_type& hhsl,const index_type& hhsu,
    const index_type& hsl,const index_type& hsu,
    const index_type& sl,const index_type& sh,
    const index_type& nrl,const index_type& nrh,
    const char * s="UNNAMED");
  friend class model_data;
};

class data_5array : public named_d5_array
{
  data_5array(void) : named_d5_array() {;}
  void allocate(int hhsl,int hhsu,
    int hhhsl,int hhhsu,
    int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(ad_integer hhhsl, ad_integer hhhsu, const index_type& hhsl,
    const index_type& hhsu, const index_type& hsl, const index_type& hsu,
    const index_type& rmin, const index_type& rmax, const index_type& cmin,
    const index_type& cmax, const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_4array : public named_d4_array
{
  data_4array(void) : named_d4_array() {;}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(ad_integer hhsl, ad_integer hhsu, const index_type& hsl,
    const index_type& hsu, const index_type& rmin, const index_type& rmax,
    const index_type& cmin, const index_type& cmax, const char * ="UNNAMED");
  friend class model_data;
};

class data_4iarray : public named_i4_array
{
  data_4iarray(void) : named_i4_array() {;}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(ad_integer hhsl, ad_integer hhsu, const index_type& hsl,
    const index_type& hsu, const index_type& rmin, const index_type& rmax,
    const index_type& cmin, const index_type& cmax, const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_imatrix : public named_imatrix
{
  data_imatrix(void) : named_imatrix() {;}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int rmin, int rmax, const index_type&, const index_type& cmax,
    const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_vector : public named_dvector
{
public:
  data_vector& operator=(const dvector& m);
  data_vector& operator=(const double m);
  data_vector(void) : named_dvector() {;}
private:
  void allocate(int imin,int imax,const char * ="UNNAMED");
  void allocate(int imin, const ivector& imax, const char * ="UNNAMED");
  void allocate(init_xml_doc&, const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class dll_data_vector : public data_vector
{
public:
  double * pd;
  void allocate(double * pd,int imin,int imax,const char * ="UNNAMED");
  void allocate(double *pd, int imin, const ivector& imax,
    const char * ="UNNAMED");
  virtual ~dll_data_vector();
  dll_data_vector& operator = (const dvector& x);
  dll_data_vector& operator = (const double& x);
};

/**
 * Description not yet available.
 * \param
 */
class data_ivector : public named_ivector
{
public:
  data_ivector(void) : named_ivector() {;}
private:
  void allocate(int imin,int imax,const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_number : public model_name_tag
{
protected:
  double val;
  void allocate(const char * ="UNNAMED");
public:
  void report_value(void);
  operator double() {return val;}
  double& value(void) {return val;}
  void initialize(void) {val=0.0;}
  friend class model_data;
  data_number & operator=(const double& m);
};

/**
 * Description not yet available.
 * \param
 */
class dll_data_number : public data_number
{
public:
  double * pd;
  void allocate(double *_pd,const char * s);
  virtual ~dll_data_number();
  dll_data_number & operator=(const double& m);
};

#include <functional>

typedef dvariable (model_parameters::*PMF) (const dvariable&);
typedef std::function<dvariable(const dvariable&)> _func;
typedef dvariable (model_parameters::*PMFI) (const dvariable&,int n);
typedef dvariable (model_parameters::*PMFVI) (const dvar_vector&,int n);
typedef void (model_parameters::*PMFVIV4) (const dvar_vector&,int n,
  dvariable& f1, const dvariable& f2, const dvariable& f3, const dvariable& f4);

  class init_df1b2vector;
  class df1b2vector;
  class df1b2variable;

/**
 * Description not yet available.
 * \param
 */
class function_minimizer
{
public:
  static int bad_step_flag;
  static int likeprof_flag;
  static int first_hessian_flag;
  static int test_trust_flag;
  static int random_effects_flag;
  dmatrix * negdirections;
  static int negative_eigenvalue_flag;
  static int inner_opt_flag;
  static int inner_opt(void);
  laplace_approximation_calculator * lapprox;
  dvector * multinomial_weights;
  void set_multinomial_weights(dvector&d);
  //init_df1b2vector* py;
  virtual void AD_uf_inner();
  virtual void AD_uf_outer();
  virtual void user_function();
  void pre_user_function(void);
  //void df1b2_pre_user_function(void);
  //virtual void user_function(const init_df1b2vector& x,df1b2variable& f);
  //static int hesstype;
  //int set_hessian_type(int);
  void hess_routine_noparallel_randomeffects(void);
  void other_separable_stuff_begin(void);
  void other_separable_stuff_end(void);
  void begin_df1b2_funnel(void){;}
  void setup_quadprior_calcs(void){;}
  void end_df1b2_funnel(void){;}
  void get_function_difference(void);
  void start_get_importance_sampling_comnponent(void);
  void end_get_importance_sampling_comnponent(void);
  int spminflag;
  int repeatminflag;
  int mcmc2_flag;
  int robust_hybrid_flag;
  int diagonal_metric_flag;
  long ifn;
  int maxfn;
  int iprint;
  double crit;
  int imax;
  double dfn;
  long iexit;
  long ihflag;
  long ihang;
  int scroll_flag;
  int maxfn_flag;
  int quit_flag;
  double min_improve;
  void pre_userfunction(void);
  virtual void userfunction(void)=0;
  virtual void allocate() {}
  virtual void deallocate() {}
  static named_dvar_vector * ph;
  static named_dvar_vector * pg;
protected:
  double ffbest;
private:
  gradient_structure * pgs;
  adstring_array param_labels;
  ivector param_size;
protected:
  void report_function_minimizer_stats(void){;}
  virtual void report(const dvector& gradients){;};
  static dvector convergence_criteria;
  static dvector maximum_function_evaluations;
  static int sd_flag;
  static adstring user_data_file;
  static adstring user_par_file;
  static int have_constraints;
public:
  virtual dvariable user_randeff(const dvar_vector& x);
  virtual dvar_vector user_dfrandeff(const dvar_vector& x);
  virtual dvar_matrix user_d2frandeff(const dvar_vector& x);
  void limited_memory_quasi_newton(const independent_variables&,int);
  void limited_memory_quasi_newton(const independent_variables&,int,int);
  void limited_memory_quasi_newton(double& f, const independent_variables&,
    int, int, int,double);
  function_minimizer(long int sz=0L);
  void likeprof_routine(double global_min);
  virtual ~function_minimizer();
  virtual void other_calculations(void){;}
  virtual void final_calcs(void){;}
  virtual void minimize(void);
  virtual void constraints_minimize(void);
  virtual void between_phases_calculations(void){;}
  void computations(int argc,char * argv[]);
  void computations1(int argc,char * argv[]);
  void computations_np(int argc,char * argv[]);
  void computations(void);
  void hess_routine(void);
  void hess_routine_noparallel(void);
  void hess_routine_master(void);
  void hess_routine_slave(void);
  void constraint_report(void);
  void pvm_slave_likeprof_routine(void);
  void pvm_master_function_evaluation_profile(double& f,
    independent_variables& x,const dvector & g,int nvar,int iprof,double weight,
    double new_value);
  void pvm_slave_prof_minimize(int underflow_flag);
  void pvm_master_prof_minimize(int iprof, double sigma,
    double new_value, const double& _fprof, const int underflow_flag,
    double global_min, const double& _penalties,
    const double& _final_weight);
  //void pvm_master_function_evaluation_profile(double& f,
   // independent_variables& x,dvector & g,int nvar,int iprof);
  void pvm_slave_function_evaluation(void);
  void pvm_slave_function_evaluation_no_derivatives(void);
  void pvm_slave_function_evaluation_noder(void);
  void pvm_master_function_evaluation_no_derivatives(double& f,
    independent_variables& x,int nvar);
  void pvm_master_function_evaluation(double& f,
    independent_variables& x,const dvector & g,int nvar);
  dmatrix dep_hess_routine(const dvariable& dep);
  void top_mcmc_routine(int,int,double,int);
  void mcmc_routine(int,int,double,int);
  void sgibbs_mcmc_routine(int,int,double,int);
  void hybrid_mcmc_routine(int,int,double,int);

  // Functions added by Cole for HMC.
  void add_sample_diag(const int nvar, int& n, dvector& m, dvector& m2,
		       const independent_variables& q);
  void add_sample_dense(const int nvar, int& is2, dvector& m, dmatrix& m2,
			const independent_variables& q);
  dvector rotate_pars(const dvector& m, const dvector& x);
  dvector rotate_pars(const dmatrix& m, const dvector& x);
  dvector rotate_gradient(const dvector& x, const dmatrix& m); 
  int compute_next_window(int i, int anw, int warmup, int w1, int aws, int w3);
  bool slow_phase(int is, int warmup, int w1, int w3);
  std::string get_filename(const char* f);
  double get_hybrid_monte_carlo_value(int nvar,const independent_variables& y,
    dvector& g);
  void read_mle_hmc(int nvar, dvector& mle);
  void rwm_mcmc_routine(int,int, double, int);
  void shmc_mcmc_routine(int,int,double,int);
  void nuts_mcmc_routine(int,int,double,int);
  void print_mcmc_timing(double time_warmup, double time_total, int chain);
  void print_mcmc_progress(int is, int nmcmc, int nwarmup, int chain);
  double find_reasonable_stepsize(int nvar, dvector y, dvector p, dmatrix& chd, bool verbose_adapt_mass, bool verbose_find_epsilon, int chain);
  bool stop_criterion(int nvar, dvector& thetaminus, dvector& thetaplus,
		      dvector& rminus, dvector& rplus);
  void build_tree(int nvar, dvector& gr, dmatrix& chd, double eps, dvector& p,
		  dvector& y, dvector& gr2, double logu, int v, int j, double H0,
		  dvector& _thetaprime, dvector& _thetaplus, dvector& _thetaminus,
		  dvector& _rplus, dvector& _rminus,
		  double& _alphaprime, int& _nalphaprime, bool& _sprime,
		  int& _nprime, int& _nfevals, bool& _divergent,
		  const random_number_generator& rng,
		  dvector& gr2_end, dvector& _grprime, dvector& _gr2prime, double& _nllprime,
		  independent_variables& _parsaveprime);
  double leapfrog(int nvar,dvector& gr, dmatrix& chd,
		  double eps, dvector& p, dvector& x, dvector& gr2);
  double adapt_eps(int ii, double eps, double alpha,
		   double& adapt_delta, double& mu,
		   dvector& epsvec, dvector& epsbar,
		   dvector& Hbar);
  double exprnd(double p);
  // End new functions

  double pvm_master_get_monte_carlo_value(int nvar,
    const dvector& x);
  void pvm_slave_get_monte_carlo_value(int nvar);
  void mcmc_eval(void);
  //void hess_routine_and_constraint(int);
  void hess_routine_and_constraint(int iprof, const dvector& g,
    dvector& fg);
  dmatrix diag_hess_routine(void);
  void hess_inv(void);
  void depvars_routine(void);
  void sd_routine(void);
  int ef_(double * f, double * x);
  int constrained_minimization2(int _n,int _nh, int _ng,dvector& __x);
  static int constraint_exit_number;
  void get_bigS(int ndvar,int nvar1,int nvar,
    dmatrix& S,dmatrix& BS,dvector& scale);

#ifdef CURVE_CORRECT
  void constraint_hess_routine(int ip);
  void get_curvature_correction_factors(int ip,
    dvector& g, const int underflow_flag, const dvector& eigenvals,
    dvector& curvcor);
#endif
  double projected_jacobian(const dvector& g, const dvector& xscale);

  dvariable random_effects_maximization(const dvar_vector& v);
  void prof_minimize_re(int iprof, double sigma,
    double new_value, const double& fprof, const int underflow_flag,
    double global_min, const double& penalties, const double& final_weight);
  void prof_minimize(int iprof, double sigma,
    double new_value, const double& fprof, const int underflow_flag,
    double global_min, const double& penalties, const double& final_weight);
  void begin_gauss_hermite_stuff(void);
  void begin_funnel_stuff(void);
  void end_gauss_hermite_stuff(void);

  void prof_hess_routine(int ip,double new_value,double final_weight);

  void quasi_newton_minimizer1(int nvar,double _crit,
    double& f, const independent_variables& x,const dvector& g);

  double hess_determinant(int underflow_flag);

#ifndef CURVE_CORRECT
  void normalize_posterior_distribution(double udet,
    const dvector& siglevel, const ofstream& ofs2, int num_pp,
    const dvector& all_values, const dmatrix& actual_value, double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet, const dmatrix& xdist,
    const dmatrix& penalties);
  //  dmatrix& penalties, const hdmatrix& lg_jacob);
#else
  void normalize_posterior_distribution(double udet,
    const dvector& siglevel, const ofstream& ofs2, int num_pp,
    const dvector& all_values, const dmatrix& actual_value,
    double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet,
    const dmatrix& xdist,
    const d3_array& eigenvals,d3_array& curvcor);
#endif
  void get_particular_grad(int iprof, int nvar, const dvector& fg,
    const dvector& g);
  double projected_hess_determinant(const dvector& g, const int underflow_flag,
    const dvector& xscale, const double& ln_det_proj_jac);
//  double projected_hess_determinant(const dvector& fg, const dvector& g,
  //const int underflow_flag, const dvector& xscale,
  // const double& ln_det_proj_jac);
  double projected_hess_determinant(const dvector& g,const int underflow_flag);
  double projected_hess_determinant(const dmatrix& hh, const dvector& g,
    const int underflow_flag);
 //double projected_hess_determinant(const dvector& g, const int underflow_flag,
    //dvector& xscale, const double& ln_det_proj_jac);

  double projected_hess_determinant(const dvector& fg, const dvector& g,
    const int underflow_flag, const dvector& curvscale, const dvector& xscale,
    double& ln_det_proj_jac, const double& tmp, const dmatrix& hesses);
  double diag_projected_hess_determinant(const dvector& g,
    const int underflow_flag, dmatrix& dh);
    double unrestricted_hess_determinant(void);
  void monte_carlo_routine(void);
  double get_monte_carlo_value(int nvar, const independent_variables& x);
  double get_monte_carlo_value(int nvar, const independent_variables& x,
    dvector& g);
  void mcmc_computations(void);
#if defined(USE_ADPVM)
  void pvm_slave_mcmc_computations(void);
  void pvm_master_mcmc_computations(void);
#endif
  double get_monte_carlo_value(int nvar, const dvector& x);
  void sob_routine(int nmcmc,double dscale,int restart_flag);
  void sobol_importance_routine(int nmcmc,int iseed0,double dscale,
  int restart_flag);
  void pvm_master_mcmc_routine(int nmcmc,int iseed0,double dscale,
    int restart_flag);
#if defined(USE_ADPVM)
  void pvm_slave_mcmc_routine(void);
#else
  void pvm_slave_mcmc_routine(void) {}
#endif
  void trust_region_update(int nvar,int _crit,
    independent_variables& x,const dvector& _g,const double& _f);

  void multint4(int n, const dvar_vector& a, const dvar_vector& b,
    const dvar_vector& h, double al, int m, const dvariable& e,
    const dvariable& aint1, const dvariable& aint2, dvariable& aint3,
    const dvariable& aint4, const int& key, PMFVIV4 f);

  void multint(int n, const dvar_vector& a, const dvar_vector& b,
    const dvar_vector& h, double al, int m, const dvariable& e,
    const dvariable& aint, const int& key, PMFVI f);

  virtual void set_runtime(void);
  virtual void set_runtime_maxfn(const char *);
  virtual void set_runtime_crit(const char *);
  dvariable adromb(_func func, double a, double b, int ns = 9);
  dvariable adromb(_func func, const dvariable& a, double b, int ns = 9);
  dvariable adromb(_func func, const dvariable& a, const dvariable& b, int ns = 9);
  dvariable adromb(_func func, double a, const dvariable& b, int ns = 9);

  dvariable adrombo(_func func, double a, double b, int ns = 9);
  dvariable adrombo(_func func, const dvariable& a, double b, int ns = 9);
  dvariable adrombo(_func func, const dvariable& a, const dvariable& b, int ns = 9);
  dvariable adrombo(_func func, double a, const dvariable& b, int ns = 9);

  dvariable trapzd(void*, double a, double b, int n);
  dvariable trapzd(_func func, double a, double b, int n);
  dvariable trapzd(_func func, double a, const dvariable& b, int n);
  dvariable trapzd(_func func, const dvariable& a, double b, int n);
  dvariable trapzd(_func func, const dvariable& a, const dvariable& b, int n);

  /*
  //No code for midpnt functions
  //dvariable midpnt(PMF,double a,double b,int n);
  //dvariable midpnt(PMF, double a, const dvariable& b, int n);
  //dvariable midpnt(PMF, const dvariable& a, double b, int n);
  //dvariable midpnt(PMF, const dvariable& a, const dvariable& b, int n);
  //virtual void * mycast() { return (void*)this;}
  */

  void neldmead(int n, dvector& _start, dvector& _xmin, double *ynewlo,
    double reqmin, double delta,int *icount, int *numres, int *ifault);
  void adamoeba(const dmatrix& p, const dvector& y, int ndim, double ftol,
     int maxfn);
  void set_initial_simplex(const dmatrix& p, const dvector& y, int nvar,
    const dvector& x, double delta);
  double amxxx(const dmatrix& p, const dvector& y, const dvector& psum,
    int ndim, int ihi, double fac);
  friend class equality_constraint_vector;
  friend class inequality_constraint_vector;
  void quasi_newton_block(int nvar,int crit,independent_variables& x,
    const dvector& g,const double& f);
  void limited_memory_quasi_newton_block(int nvar,int _crit,
    independent_variables& x,const dvector& _g,const double& _f,
    int nsteps);

  void function_evaluation_block_pvm_slave_random_effects(int nvar,int _crit,
    independent_variables& x,const dvector& g,const double& f);
  void quasi_newton_block_pvm_master_random_effects(int nvar,int _crit,
    independent_variables& x,const dvector& g,const double& f);
  void function_evaluation_block_pvm_slave_random_effects(void);
  void hess_routine_random_effects(void);
  void quasi_newton_block_pvm_master(int nvar,int _crit,
    independent_variables& x,const dvector& g,const double& f);
  void hess_routine_noparallel_random_effects(void);
#if defined(USE_ADPVM)
  void function_evaluation_block_pvm_slave(void);
  void hess_routine_slave_random_effects(void);
#endif
  dvariable do_gauss_hermite_integration(void);
  void end_df1b2_funnel_stuff(void);

private:
  dvariable do_gauss_hermite_integration_multi(void);
};

cifstream& operator>>(const cifstream& s, const param_init_number& x);
cifstream& operator>>(const cifstream& s, const param_init_vector& v);
cifstream& operator>>(const cifstream& s, const param_init_matrix& m);
ostream& operator<<(const ostream& s, const label_class& lc);

/**
 * Description not yet available.
 * \param
 */
class stddev_params
{
public:
  // this should be a resizeable array
  static stddev_params * stddevptr[150];
  // this should be a resizeable array
  static stddev_params * stddev_number_ptr[150];
  static void get_all_sd_values(const dvector& x, const int& ii);
  static int num_stddev_params;
  static int num_stddev_number_params;
  static ivector copy_all_number_offsets(void);
  void allocate(void){;};
  static int num_stddev_calc(void);
  static int num_stddev_number_calc(void);
  static void get_stddev_number_offset(void);
public:
  stddev_params(void){;}
  virtual void setindex(int);
  virtual int getindex(void);

  // get the number of active parameters
  virtual unsigned int size_count() const = 0;

  virtual void set_dependent_variables(void)=0;
  virtual void copy_value_to_vector(const dvector&,const int&) = 0;
  virtual void get_sd_values(const dvector& x, const int& ii) = 0;
  //get the number of active parameters
  static void copy_all_values(const dvector& x, const int& ii);
  //get the number of active parameters
  static void copy_all_number_values(const dvector& x, const int& ii);
  virtual void add_to_list(void);
  virtual void add_to_gui_list(void);
  virtual const char * label()=0;
  friend class function_minimizer;
};

/**
 * Description not yet available.
 * \param
 */
class likeprof_params
{
  double stepsize;
  int    stepnumber;
protected:
public:
  static likeprof_params * likeprofptr[500]; // this should be a
                                               // resizeable array
  static int num_likeprof_params;
  void allocate(void){;};
  static int num_stddev_calc(void);
public:
  likeprof_params(void);
  virtual void add_to_list(void);
  virtual const char * label()=0;
  virtual dvariable variable(void)=0;
  virtual double& get_sigma(void)=0;
  virtual double get_value(void)=0;
  double get_stepsize(void);
  int get_stepnumber(void);
  void set_stepsize(double);
  void set_stepnumber(int);
  friend class function_minimizer;
};

/**
 * Description not yet available.
 * \param
 */
class param_stddev_vector: public named_dvar_vector , stddev_params
{
  dvector sd;

  // get the number of active parameters
  virtual unsigned int size_count() const;

    virtual const char * label(void);
    param_stddev_vector();
    void allocate(int imin,int imax,const char * s="UNNAMED");
    virtual void set_dependent_variables(void);
    friend class model_parameters;
    virtual void copy_value_to_vector(const dvector& x, const int& ii);
    virtual void get_sd_values(const dvector& x, const int& ii);
  param_stddev_vector& operator=(const dvar_vector& m);
  param_stddev_vector& operator=(const dvector& m);
  param_stddev_vector& operator=(const double m);
};

/**
 * Description not yet available.
 * \param
 */
class param_stddev_number: public named_dvariable , public stddev_params
{
  double sd;
  int index;
  void allocate(const char *s="UNNAMED");
  virtual void setindex(int);
  virtual int getindex(void);

  // get the number of active parameters
  virtual unsigned int size_count() const;

  virtual const char * label(void);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void get_sd_values(const dvector& x, const int& ii);
protected:
  param_stddev_number();
  friend class model_parameters;
  virtual void set_dependent_variables(void);
  param_stddev_number& operator=(const prevariable&);
  param_stddev_number& operator=(const double);
};

/**
 * Description not yet available.
 * \param
 */
class param_likeprof_number: public param_stddev_number ,
    public likeprof_params
{
    double sigma;
    void allocate(const char *s="UNNAMED");

  // get the number of active parameters
  virtual unsigned int size_count() const;

    virtual const char * label(void);
    virtual double& get_sigma(void){return sigma;}
    virtual double get_value(void){return value(*this);}
    //void copy_value_to_vector(const dvector& x, const int& ii);
    virtual dvariable variable(void){ return dvariable(*this);}
    param_likeprof_number();
    friend class model_parameters;
public:
    param_likeprof_number& operator=(const prevariable&);
    param_likeprof_number& operator=(const double);
};

/**
 * Description not yet available.
 * \param
 */
class param_stddev_matrix: public named_dvar_matrix , stddev_params
{
  dmatrix sd;
  virtual unsigned int size_count() const;
    //virtual void read_value(void);
    virtual const char * label(void);
    void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * s="UNNAMED");
  param_stddev_matrix(void);
  friend class model_parameters;
  virtual void set_dependent_variables(void);
  virtual void get_sd_values(const dvector& x, const int& ii);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  param_stddev_matrix& operator=(const double m);
  param_stddev_matrix& operator=(const dmatrix& m);
  param_stddev_matrix& operator=(const dvar_matrix& m);
};

/**
 * Description not yet available.
 * \param
 */
  class objective_function_value : public named_dvariable
  {
  public:
    static objective_function_value * pobjfun;
    static double fun_without_pen;
    static double gmax;
    objective_function_value();
    objective_function_value& operator=(const prevariable& v);
    objective_function_value& operator=(const double v);
  };

  int withinbound(int lb,int n,int ub);

double cumd_cauchy(const double& x);
double density_cauchy(const double& x);
double log_density_cauchy(const double& x);
double inv_cumd_cauchy(const double& x);

double cumd_mixture(const double& x);
double inv_cumd_mixture(const double& y);
double cumd_mixture_02(const double& x);
double inv_cumd_mixture_02(const double& y);

#if defined _ADM_HIGHER_ARRAYS__

/**
 * Description not yet available.
 * \param
 */
class param_init_matrix: public named_dvar_matrix, public initial_params
{
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
//virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
//  const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
public:
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual unsigned int size_count() const;
  virtual void save_value(ofstream& ofs);
  virtual void bsave_value(uostream& uos);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){;};

public:
  void allocate(int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  param_init_matrix(void);
  param_init_matrix& operator = (const dmatrix& m);
  param_init_matrix& operator = (const dvar_matrix& m);
  param_init_matrix& operator = (const dvariable& m);
  param_init_matrix& operator = (const double& m);
};
#endif // #if defined _ADM_HIGER_ARRAYS__

/**
 * Description not yet available.
 * \param
 */
class param_init_d3array: public named_dvar3_array, public initial_params
{
public:
#if defined(USE_SHARE_FLAGS)
  virtual void setshare(const index_type& sf,const index_type& af);
  virtual void shared_set_value_inv(const dvector&,const int&);
  virtual void shared_set_value(const dvar_vector&,const int&,
    const dvariable& pen);
  virtual int shared_size_count(void); // get the number of active parameters
#endif

  virtual void sd_vscale(const dvar_vector& d,const dvar_vector& x,
    const int& ii);
  virtual void dev_correction(const dmatrix&, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
//virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds,
//  const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&,
    const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii,
    const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&,const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual unsigned int size_count() const;
  virtual void save_value(ofstream& ofs);
  virtual void bsave_value(uostream& uos);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void save_value(const ofstream& ofs, int prec,const dvector&,
    int& offset){}
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const  int& ii);

public:
#if defined(USE_ADPVM)
  virtual void pvm_pack(void) { cerr << "Error" << endl; ad_exit(1);}
  virtual void pvm_unpack(void) { cerr << "Error" << endl; ad_exit(1);}
#endif

  void allocate(const ad_integer& sl,const ad_integer& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,const char * s="UNNAMED");

  void allocate(const ad_integer& sl,const ad_integer& sh,
    const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch,int phase_start=1,
    const char * s="UNNAMED");

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
class dll_param_init_d3array: public param_init_d3array
{
  double * d;
public:
  void allocate(double* _d,int hmin,int hmax,
    int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(double * _d,int hmin,int hmax,int rmin,int rmax,
    int cmin,int cmax,const char * = "UNNAMED");
  virtual ~dll_param_init_d3array();
  dll_param_init_d3array(){d=NULL;}
  dll_param_init_d3array& operator=(const d3_array&);
  dll_param_init_d3array& operator=(const dvar3_array&);
};

/**
 * Description not yet available.
 * \param
 */
class dll_param_d3array: public named_dvar3_array
{
  double * d;
public:
  void allocate(double* _d,int hmin,int hmax,
    int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(double * _d,int hmin,int hmax,int rmin,int rmax,
    int cmin,int cmax,const char * = "UNNAMED");
  virtual ~dll_param_d3array();
  dll_param_d3array(){d=NULL;}
  dll_param_d3array& operator=(const d3_array&);
  dll_param_d3array& operator=(const dvar3_array&);
};


//double set_value_mc(const double& x, const double fmin, const double fmax);

void set_value_mc(const dvar_vector& x, const dvar_vector& v, const int& ii,
  const double fmin, const double fmax);

double set_value_inv_mc(double v,double fmin,double fmax);

double set_value_inv_mc(const prevariable& v, double fmin, double fmax);

void set_value_inv_mc(const dvar_vector& x, const dvector& v, const int& ii,
  const double fmin, const double fmax);

//double set_value_inv_mc(const dvector&, const dvector& x, int ii, double minb,
//  double maxb);

double set_value_mc(double z,double min,double max);
double ndfboundp( double x, double fmin, double fmax,const double& fpen);
double ndfboundp_mc( double x, double fmin, double fmax,const double& fpen);

void copy_value_from_vector(const double& _sd,const dvector& x,const int & _ii);
void copy_value_from_vector(const dvector& _sd,const dvector& x,
  const int & _ii);
void copy_value_from_vector(const dmatrix& _sd,const dvector& x,
  const int & _ii);

dvector bounded_multivariate_normal(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& _wght,
  const random_number_generator & rng);

void bounded_multivariate_normal_mcmc(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& wght, const dvector& y,
  const random_number_generator & rng);

void bounded_multivariate_uniform_mcmc(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& wght, const dvector& y,
  const random_number_generator & rng);

dvector bounded_multivariate_normal(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& lprob,
  random_number_generator &rng);

dvector bounded_multivariate_normal_sobol(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& lprob,
  const random_number_generator &rng);

dvector probing_bounded_multivariate_normal(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& lprob, double pprobe,
  const random_number_generator &rng);

dvector bounded_multivariate_uniform(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& lprob,
  random_number_generator &rng);

dvector bounded_robust_multivariate_normal(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const dmatrix& ch3, double contaminant,
  const double& _wght, random_number_generator &rng);

void probing_bounded_multivariate_normal_mcmc(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& wght, const dvector& v,
  double pprobe, const random_number_generator &rng);

/*
int option_match(int argc,char * argv[], const char * string);
int option_match(int argc,char * argv[], const char * string, const int& nopt);
int option_match(char * s, const char * string, const int& _nopt);
int option_match(char * s, const char * string);
*/

double inv_cumd_exp(double x);
double cumd_exp(double x);

double ffmax(double a,double b);
double ffmin(double a,double b);

void check_datafile_pointer(void * p);

adstring get_reportfile_name(void);

void ad_make_code_reentrant(void);

char** parse_dll_options(char *pname, const int& argc,
  char * dll_options);

void parse_dll_options(char *pname, const int& argc, char *dll_options,
  char *** pargv);

char** no_dll_options(char *pname, const int& argc);

void cleanup_argv(int nopt,char *** pa);

void get_sp_printf(void);

void do_dll_housekeeping(int argc,char ** argv);

void adwait(double);

int ad_get_commandline_option(const char *option_label, const int &option_value,
  const char * error_message);

/**
 * Description not yet available.
 * \param
 */
class param_init_vector_vector
{
  param_init_vector * v;
  int index_min;
  int index_max;
  double_index_type * it;

public:
  param_init_vector_vector();
  ~param_init_vector_vector();

  void set_scalefactor(double s);
  void set_scalefactor(const dvector& s);
  dvector get_scalefactor(void);

#if defined(OPT_LIB)
  param_init_vector& operator [] (int i) { return v[i];}
  param_init_vector& operator () (int i) { return v[i];}
  prevariable operator () (int i,int j) { return v[i][j];}
#else
  param_init_vector& operator [] (int i);
  param_init_vector& operator () (int i);
  prevariable operator () (int i,int j);
#endif

  void allocate(int min1,int max1,const index_type& min,
     const index_type& max,const index_type& phase_start,
     const char * s);

  void allocate(int min1,int max1,const index_type& min,
     const index_type& max,const char * s);

  bool allocated() const { return v != NULL; }
  int indexmin(void) {return (index_min);}
  int indexmax(void) {return (index_max);}
  void set_initial_value(const double_index_type& it);
  void deallocate(void);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_vector_vector
{
  param_init_bounded_vector* v;
  int index_min;
  int index_max;
  double_index_type* it;
public:
  param_init_bounded_vector_vector();
  ~param_init_bounded_vector_vector();

  void set_scalefactor(double s);
  void set_scalefactor(const dvector& s);
  dvector get_scalefactor(void);
#if defined(OPT_LIB)
  param_init_bounded_vector& operator [] (int i) { return v[i];}
  param_init_bounded_vector& operator () (int i) { return v[i];}
  prevariable operator () (int i,int j) { return v[i][j];}
#else
  param_init_bounded_vector& operator [] (int i);
  param_init_bounded_vector& operator () (int i);
  prevariable operator () (int i,int j);
#endif

  void allocate(int min1,int max1,
    const index_type& min,
    const index_type& max,
    const double_index_type& dmin,
    const double_index_type& dmax,
    const index_type& phase_start,
    const char* s);

  void allocate(int min1,int max1,
    const index_type& min,
    const index_type& max,
    const double_index_type& dmin,
    const double_index_type& dmax,
    const char* s);

  bool allocated() const { return v != NULL; }
  int indexmin() const {return index_min;}
  int indexmax() const {return index_max;}
  void deallocate(void);
  void set_initial_value(const double_index_type& it);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_matrix_vector
{
  param_init_matrix* v;
  int index_min;
  int index_max;
  double_index_type* it;

public:
  param_init_matrix_vector();
   ~param_init_matrix_vector();

  void set_scalefactor(double s);
  void set_scalefactor(const dvector& s);
  dvector get_scalefactor(void);

#if defined(OPT_LIB)
  param_init_matrix& operator [] (int i) { return v[i];}
  param_init_matrix& operator () (int i) { return v[i];}
  dvar_vector& operator () (int i,int j) { return v[i][j];}
  prevariable operator () (int i,int j,int k) { return v[i](j,k);}
#else
  param_init_matrix& operator [] (int i);
  param_init_matrix& operator () (int i);
  dvar_vector& operator () (int i,int j);
  prevariable operator () (int i,int j,int k);
#endif
  void allocate(int min0,int max0,const index_type& min,
     const index_type& max,const index_type& min1,
     const index_type& max1,const index_type& phase_start,
     const char * s);

  void allocate(int min0,int max0,const index_type& min,
     const index_type& max,const index_type& min1,
     const index_type& max1,const char * s);

  bool allocated() const { return v != NULL; }
  int indexmin() const { return index_min;}
  int indexmax() const { return index_max;}
  void set_initial_value(const double_index_type& it);
  void deallocate(void);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_matrix_vector
{
  param_init_bounded_matrix* v;
  int index_min;
  int index_max;
  double_index_type* it;
public:
  param_init_bounded_matrix_vector();
  ~param_init_bounded_matrix_vector();

  void set_scalefactor(double s);
  void set_scalefactor(const dvector& s);
  dvector get_scalefactor();

  void allocate(
    int min1, int max1,
    const index_type& min, const index_type& max,
    const index_type& min2, const index_type& max2,
    const double_index_type& dmin2, const double_index_type& dmax2,
    const index_type& phase_start,
    const char * s);

  void allocate(
    int min1, int max1,
    const index_type& min, const index_type& max,
    const index_type& min2, const index_type& max2,
    const double_index_type& dmin2, const double_index_type& dmax2,
    const char * s);

  param_init_bounded_matrix& operator[](int i);
  param_init_bounded_matrix& operator()(int i);
  dvar_vector& operator()(int i, int j);
  prevariable operator()(int i, int j, int k);

  bool allocated() const { return v != NULL; }
  int indexmin() const { return index_min; }
  int indexmax() const { return index_max; }

  void set_initial_value(const double_index_type& initial_value);
  void deallocate();
};
#if defined(OPT_LIB)
inline param_init_bounded_matrix&
param_init_bounded_matrix_vector::operator[](int i)
  { return v[i]; }
inline param_init_bounded_matrix&
param_init_bounded_matrix_vector::operator()(int i)
  { return v[i]; }
inline dvar_vector&
param_init_bounded_matrix_vector::operator()(int i, int j)
  { return v[i][j]; }
inline prevariable
param_init_bounded_matrix_vector::operator()(int i, int j, int k)
  { return v[i](j,k); }
#endif

/**
 * Description not yet available.
 * \param
 */
class param_init_number_vector
{
  param_init_number* v;
  int index_min;
  int index_max;
  double_index_type* it;
public:
  param_init_number_vector();
  ~param_init_number_vector();

  void set_scalefactor(double s);
  void set_scalefactor(const dvector& s);
  dvector get_scalefactor(void);

#if defined(OPT_LIB)
  param_init_number& operator[](int i) { return v[i];}
  param_init_number& operator()(int i) { return v[i];}
#else
  param_init_number& operator[](int i);
  param_init_number& operator()(int i);
#endif

  void allocate(int min1,int max1,const index_type& phase_start,
     const char * s);

  void allocate(int min1,int max1,const char * s);

  bool allocated() const { return v != NULL; }
  int indexmin() const { return index_min; }
  int indexmax() const { return index_max; }
  void set_initial_value(const double_index_type& it);
  void deallocate(void);
};

class data_matrix;
/**
 * Class object for init_bounded_number vector
 * \author Dave Fournier, addition by Steve Martell
 * \param
 * Steve Martell overloaded the allocate routine to accomodate a matrix object
 * of the form data_matrix that would be read in from an input file.
 */
class param_init_bounded_number_vector
{
  param_init_bounded_number* v;
  int index_min;
  int index_max;
  double_index_type* it;
public:
  param_init_bounded_number_vector();
  ~param_init_bounded_number_vector();

  void set_scalefactor(double s);
  void set_scalefactor(const dvector& s);
  dvector get_scalefactor();

  param_init_bounded_number& operator[](int i);
  param_init_bounded_number& operator()(int i);

  void allocate(int min1,int max1,const double_index_type & bmin,
    const double_index_type & bmax,const index_type& phase_start,
    const char * s);

  void allocate(int min1,int max1,const double_index_type & bmin,
     const double_index_type & bmax,const char * s);

  // Added by Steve Martell, Jan 18, 2014.
  void allocate(const data_matrix &m, const char *s);

  bool allocated() const { return v != NULL; }
  int indexmin() const { return index_min; }
  int indexmax() const { return index_max; }
  void set_initial_value(const double_index_type& it);
  void deallocate();
};
#if defined(OPT_LIB)
inline param_init_bounded_number&
param_init_bounded_number_vector::operator[](int i)
{
  return v[i];
}
inline param_init_bounded_number&
param_init_bounded_number_vector::operator()(int i)
{
  return v[i];
}
#endif
  extern int traceflag;
  void tracing_message(int traceflag,const char *s,int *pn);
  void tracing_message(int traceflag,const char *s,double *pn);
  void set_gauss_covariance_matrix(const dll_data_matrix& m);
  void set_gauss_covariance_matrix(const dmatrix& m);
  void set_covariance_matrix(const dll_data_matrix& m);
  void set_covariance_matrix(const dmatrix& m);

  //ostream& operator<<(const ostream&, const param_init_number_vector);
  //ostream& operator<<(const ostream&, const param_init_bounded_number_vector);
  //ostream& operator<<(const ostream&, const param_init_vector_vector);
  //ostream& operator<<(const ostream&, const param_init_bounded_vector_vector);
  //ostream& operator<<(const ostream&, const param_init_matrix_vector);
  //ostream& operator<<(const ostream&, const param_init_bounded_matrix_vector);

/**
 * Description not yet available.
 * \param
 */
  class vector_kludge : public dvar_vector
  {
    public:
     vector_kludge(const param_init_number_vector &);
     vector_kludge(const param_init_bounded_number_vector &);
  };
/**
 * Description not yet available.
 * \param
 */
  class matrix_kludge : public dvar_matrix
  {
    public:
     matrix_kludge(const param_init_vector_vector &);
     matrix_kludge(const param_init_bounded_vector_vector &);
  };

void read_covariance_matrix(const dmatrix& S, int nvar, int& hbf,
  dvector& sscale);

dvector value(const param_init_number_vector& t);
dvector value(const param_init_bounded_number_vector& t);
//dvector value(const param_init_bounded_number_matrix& t);
//dvector value(const param_init_vector_vector& t);
//dvector value(const param_init_bounded_vector_vector& t);

dvector read_old_scale(int & old_nvar);

int withinbound(int lb,int n,int ub);

#if defined(_MSC_VER)
#  if defined(min)
#    undef min
#  endif
#  if defined(max)
#    undef max
#  endif
#endif

#include "param_init_bounded_number_matrix.h"

#include <Vectorize.hpp>

#endif
