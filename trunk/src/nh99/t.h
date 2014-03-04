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
//#define DO_PROFILE
#if defined(__GNUC__)
  #if (__GNUC__ < 3)
    #pragma interface
  #endif
#else
  #pragma interface
#endif

//#include <admodhd.h>
#ifndef _ADMODEL_H_
  #define  _ADMODEL_H_
#ifdef __GNUDOS__
  #define CGNU_DOUBLE double
#else
  #define CGNU_DOUBLE const double&
#endif
#include <fvar.hpp>
//#include <d4arr.hpp>
#include <cifstrem.h>
#include <iomanip.h>
#include <adstring.hpp>

#if defined(UNIXKLUDGE)
#include <unistd.h>
#endif

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
  double mfexp(CGNU_DOUBLE );
  dvariable mfexp(const prevariable& v1);
  dvar_vector mfexp(const dvar_vector& );
  dvector mfexp(const dvector& );

/*
 void set_value_inv(const dvariable& x, const dvector& v, const int& ii);
 void set_value_inv(const dvar_matrix& x, const dvector& v, const int& ii);
 void set_value_inv(const dvar_vector&, const dvector&, const int &ii);
 void set_value_inv(const dvariable& u, const dvector& x, const int& ii,CGNU_DOUBLE fmin,
  CGNU_DOUBLE fmax);
 void set_value_inv(const dvar_matrix& u, const dvector& x, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax);
 void set_value_inv(const dvar3_array& u, const dvector& x, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax);
 void set_value_inv(const dvar3_array& u, const dvector& x, const int& ii);
*/

  void copy_value_to_vector(const prevariable& x, const dvector& v, const int& ii);
  void copy_value_to_vector(const dvar_vector& x, const dvector& v, const int& ii);
  void copy_value_to_vector(const dvar_matrix& x, const dvector& v, const int& ii);
  void copy_value_to_vector(const dvar3_array& x, const dvector& v, const int& ii);

  void restore_value_from_vector(const prevariable& x, const dvector& v, const int& ii);
  void restore_value_from_vector(const dvar_vector& x, const dvector& v, const int& ii);
  void restore_value_from_vector(const dvar_matrix& x, const dvector& v, const int& ii);
  void restore_value_from_vector(dvar3_array& x, const dvector& v, const int& ii);

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

class label_class
{
  const char * name;
  friend ostream& operator<<(const ostream& s, const label_class& lc);
  friend class model_name_tag;
public:
  const char * mychar(void) { return name;}
  label_class(const char * s){name=s;}
};

class model_name_tag
{
protected:
  const char * name;
  //friend ostream& operator<<(const ostream& os, const model_name_tag& mnt);
public:
  model_name_tag(void){;}
  void allocate(const char * s);
  label_class label(void){return name;}
};

class named_dvar_vector : public dvar_vector, public model_name_tag
{
protected:
  named_dvar_vector(void) : dvar_vector(), model_name_tag() {;}
  named_dvar_vector& operator=(const dvar_vector& m);
  named_dvar_vector& operator=(const dvector& m);
  named_dvar_vector& operator = (CGNU_DOUBLE m);
  named_dvar_vector& operator=(const prevariable& m);
  friend class model_parameters;
  void allocate(int mmin,int mmax,const char * s);
};

class dll_param_vector : public named_dvar_vector
{
  double * pd;
public:
  ~dll_param_vector();
  void allocate(double *_pd,int mmin,int mmax,const char * s);
  dll_param_vector& operator=(const dvar_vector& m);
  dll_param_vector& operator=(const dvector& m);
  dll_param_vector& operator = (CGNU_DOUBLE m);
  dll_param_vector& operator=(const prevariable& m);
};


class named_dvariable : public dvariable, public model_name_tag
{
  //named_dvariable& operator=(const dvariable& m);
protected:
  named_dvariable(void) : dvariable(), model_name_tag() {;}
  void allocate(const char * s);
  named_dvariable& operator=(const prevariable& m);
  named_dvariable& operator = (CGNU_DOUBLE m);
  friend class model_parameters;
};

class dll_param_number : public named_dvariable
{
  double * pd;
protected:
  //named_dvariable(void) : dvariable(), model_name_tag() {;}
  void allocate(double *_d,const char * s);
  dll_param_number& operator=(const prevariable& m);
  dll_param_number& operator = (CGNU_DOUBLE m);
  virtual ~dll_param_number();
  friend class model_parameters;
};

class named_dvar_matrix : public dvar_matrix, public model_name_tag
{
protected:
  named_dvar_matrix(void) : dvar_matrix(), model_name_tag() {;}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
  void allocate(int rmin,int rmax,const index_type&
     ,const index_type& ,const char * s);
public:
  named_dvar_matrix& operator = (CGNU_DOUBLE m);
  named_dvar_matrix& operator=(const dmatrix& m);
  named_dvar_matrix& operator=(const dvar_matrix& m);
  named_dvar_matrix& operator=(const dvariable& m);
  friend class model_parameters;
};

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

class named_dvar3_array : public dvar3_array, public model_name_tag
{
protected:
  named_dvar3_array(void) : dvar3_array(), model_name_tag() {;}
 void allocate(const ad_integer& sl,const ad_integer& sh,
  const index_type& nrl,const index_type& nrh,const index_type& ncl,
    const index_type& nch,const char * s="UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * s="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, int rmax,
    int cmin,int cmax,const char * s="UNNAMED");
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

class named_dvar4_array : public dvar4_array, public model_name_tag
{
protected:
  named_dvar4_array(void) : dvar4_array(), model_name_tag() {;}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,const char * s);
  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const index_type&,const index_type&,
    const char *s);
  named_dvar4_array& operator=(const dvar4_array& m);
  named_dvar4_array& operator=(const d4_array& m);
  friend class model_parameters;
};

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


class named_dvector : public dvector, public model_name_tag
{
protected:
  named_dvector(void) : dvector(), model_name_tag() {;}
  void allocate(int mmin,int mmax,const char * s);
  void allocate(int mmin, const ivector& mmax, const char *s);
  named_dvector& operator=(const dvector& m);
  named_dvector& operator = (CGNU_DOUBLE m);
};


class named_ivector : public ivector, public model_name_tag
{
protected:
  named_ivector(void) : ivector(), model_name_tag() {;}
  void allocate(int mmin,int mmax,const char * s);
};

class named_dmatrix : public dmatrix, public model_name_tag
{
protected:
  named_dmatrix(void) : dmatrix(), model_name_tag() {;}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
  void allocate(int rmin,int rmax,const ivector& cmin,int cmax,const char * s);
  void allocate(int rmin,int rmax,const ivector& cmin,const ivector& cmax,const char * s);
  void allocate(int rmin,int rmax,int cmin,const ivector& cmax,const char * s);
  named_dmatrix& operator=(const dmatrix& m);
  named_dmatrix& operator = (CGNU_DOUBLE m);
};

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
                int cmin, int cmax, const char *s);
  void allocate(int hsl, int hsu, int rmin, const ivector& rmax,
                int cmin, int cmax, const char *s);
  void allocate(int hsl, int hsu, const ivector& rmin, const ivector& rmax,
                int cmin, int cmax, const char *s);
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                int cmax, const char *s);
  void allocate(int hsl, int hsu, int rmin, int rmax, int cmin,
                const ivector& cmax, const char *s);
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                const ivector& cmax, const char *s);
  named_d3_array& operator=(const d3_array& m);
};

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

class named_d4_array : public d4_array, public model_name_tag
{
protected:
  named_d4_array(void) : d4_array(), model_name_tag() {;}
  void allocate(ad_integer,ad_integer,const index_type&,const index_type&,
    const index_type&,const index_type&,const index_type&,const index_type&,
    const char * s);
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,
    int rmax,int cmin,int cmax,const char * s);
  named_d4_array& operator=(const d4_array& m);
};

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

class initial_params
{
protected:
  int active_flag;
  int initial_value_flag;
  double initial_value;
public:
  static initial_params * varsptr[120]; // this should be a resizeable array
  static int num_initial_params;
  static int num_active_initial_params;
  static int max_number_phases;
  static int current_phase;
  static int restart_phase;
  static int sd_phase;
  static int mc_phase;
  static int mceval_phase;
  int phase_start;
  int phase_stop;
  virtual void set_value(const dvar_vector&, const int&, const dvariable& pen) = 0;
  virtual void dev_correction(const dmatrix&, const int&) = 0;
  void set_initial_value(double x);
  static void set_all_simulation_bounds(const dmatrix& symbds);
  static void set_all_simulation_bounds(const dmatrix& symbds, const dvector&);
  static void get_jacobian_value(const dvector& y, const dvector& jac);
  static int correct_for_dev_objects(const dmatrix &H);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii) = 0;
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii) = 0;
  virtual void set_value_inv(const dvector&, const int&) = 0;
  virtual void add_value(const dvector&, const int&) = 0;
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&) = 0;
  virtual void get_jacobian(const dvector&, const dvector&, const int&) = 0;
  //virtual void check_tightness(const dvector&, const int&) = 0;
  virtual void copy_value_to_vector(const dvector&, const int&) = 0;
  virtual void restore_value_from_vector(const dvector&, const int&) = 0;
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii) = 0;
  virtual void mc_scale(const dvector& d, const dvector& x, const int& ii) = 0;
  virtual void curv_scale(const dvector& d, const dvector& x, const int& ii) = 0;
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii) = 0;
  virtual int size_count(void)=0; // get the number of active parameters
  virtual void save_value(void)=0; // save the objects value in a ascii file
  virtual void bsave_value(void)=0; // save the objects value in a binary file
  virtual void save_value(const ofstream& ofs, int prec) = 0;
  //virtual void bsave_value(const uostream& ofs) = 0;
  virtual const char * label()=0;
  void allocate(int _phase_start);
  void set_active_flag(void);
  void set_inactive_flag(void);
  friend int active(const initial_params& ip);
  static adstring get_reportfile_name(void);
  initial_params(void);
  static void xinit(const dvector& x); // get the number of active parameters
  static void xinit1(const dvector& x, const dvector& g);
  static void copy_all_values(const dvector& x, const int& ii); //save all initial parameter
                                                   // values in a vector
  static void restore_all_values(const dvector& x, const int& ii); //get ivalues for all
                                    // active parameters from a vector
  static dvariable reset(const dvar_vector& x); // get the number of active parameters
  static dvariable reset1(const dvar_vector& x, const dvector& g);
  static dvariable reset(const dvar_vector& x,const dvector& pen); // get the number of active parameters
  static int nvarcalc(void);
  static int num_active_calc(void);
  static int stddev_scale(const dvector& d,const dvector& x);
  static int montecarlo_scale(const dvector& d,const dvector& x);
  static int stddev_curvscale(const dvector& d, const dvector& x);
  static void read(void);
  static void save(void);
  static void save(const ofstream& ofs, int prec);
  static void restore(const ifstream& ifs);
  static void add_random_vector(const dvector& x);
  static void add_random_vector(const dvector& y, const dvector& x, const double& ll, const dvector& diag);
  virtual void restore_value(const ifstream& ifs) = 0;
  virtual void add_to_list(void);
  friend class function_minimizer;
};

class param_init_vector: public named_dvar_vector , public initial_params
{
public:
  virtual void dev_correction(const dmatrix& H, const int& ii);
  virtual const char * label(void);
  param_init_vector();
private:
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual int size_count(void);
  virtual void sd_scale(const dvector& d,const dvector& x,const int&);
  virtual void mc_scale(const dvector& d,const dvector& x,const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d,const dvector& x,const int&){;};
  virtual void save_value(void);
  virtual void bsave_value(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  void allocate(int imin,int imax,int phasestart=1,const char * s="UNNAMED");
  void allocate(int imin,int imax,const char * s="UNNAMED");
  friend class model_parameters;
public:
  param_init_vector& operator = (const dvector&);
  param_init_vector& operator = (const dvar_vector&);
  param_init_vector& operator = (const prevariable&);
  param_init_vector& operator = (const double&);
};

class dll_param_init_vector: public param_init_vector
{
  double * pd;
public:
  dll_param_init_vector& operator = (const dvector&);
  dll_param_init_vector& operator = (const dvar_vector&);
  dll_param_init_vector& operator = (const prevariable&);
  dll_param_init_vector& operator = (const double&);
  void allocate(double * _pd,int imin,int imax,
    int phasestart=1,const char * s="UNNAMED");
  void allocate(double * _pd,int imin,int imax,
    const char * s="UNNAMED");

  virtual ~dll_param_init_vector();
  friend class model_parameters;
};

class param_init_bounded_vector: public named_dvar_vector,public initial_params
{
  virtual void* parent_this(void){return this;}
protected:
  double minb;
  double maxb;
  param_init_bounded_vector();
private:
  virtual void dev_correction(const dmatrix&, const int&);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x,const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual int size_count(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){;};
  void allocate(int imin,int imax,double _minb,double _maxb,
    int phasestart=1, const char * name="UNNAMED");
  void allocate(int imin,int imax,double _minb,double _maxb,
    const char * name="UNNAMED");
  friend class model_parameters;
  virtual const char * label(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  virtual void save_value(void);
  virtual void bsave_value(void);
  void report_value(void);
  //virtual void read_value(void);
public:
  param_init_bounded_vector& operator = (const dvector&);
  param_init_bounded_vector& operator = (const dvar_vector&);
  param_init_bounded_vector& operator = (const prevariable&);
  param_init_bounded_vector& operator = (const double&);
};

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

class param_init_bounded_dev_vector: public param_init_bounded_vector
{
  virtual void set_value(const dvar_vector& x,const int& ii, const dvariable& pen);
  virtual void dev_correction(const dmatrix& H, const int& ii);
public:
  param_init_bounded_dev_vector& operator = (const dvar_vector& m);
  param_init_bounded_dev_vector& operator = (const dvector& m);
  param_init_bounded_dev_vector& operator = (const prevariable& m);
  param_init_bounded_dev_vector& operator = (const double& m);
};

class param_init_number: public named_dvariable , public initial_params
{
  virtual void dev_correction(const dmatrix&, const int&);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual int size_count(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  virtual void save_value(void);
  virtual void bsave_value(void);
  void report_value(void);
  virtual const char * label(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){;};
  //virtual void read_value(void);
protected:
  void allocate(int phase_start=1,const char *s="UNNAMED");
  void allocate(const char *s="UNNAMED");
  friend class model_parameters;
  param_init_number();
  param_init_number& operator = (CGNU_DOUBLE m);
  param_init_number& operator=(const prevariable& m);
};

class dll_param_init_number: public param_init_number
{
  double * pd;
public:
  void allocate(double * pd,int phase_start=1,const char *s="UNNAMED");
  void allocate(double *pd,const char *s="UNNAMED");
  virtual ~dll_param_init_number();
  dll_param_init_number& operator = (CGNU_DOUBLE m);
  dll_param_init_number& operator=(const prevariable& m);
};

class param_init_bounded_number: public param_init_number
{
protected:
  double minb;
  double maxb;
  void allocate(double _minb,double _maxb,int phase_start=1,
    const char * s="UNNAMED");
  void allocate(double _minb,double _maxb,const char * s="UNNAMED");
public:
  param_init_bounded_number();
private:
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x,const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){;};
  virtual const char * label(void);
  void report_value(void);
  param_init_bounded_number& operator = (CGNU_DOUBLE m);
  param_init_bounded_number& operator=(const prevariable& m);
  friend class model_parameters;
};


class dll_param_init_bounded_number: public param_init_bounded_number
{
  double * pd;
public:
  void allocate(double * _pd,double _minb,double _maxb,int phase_start=1,
    const char * s="UNNAMED");
  void allocate(double * _pd,double _minb,double _maxb,const char * s="UNNAMED");
public:
  virtual ~dll_param_init_bounded_number();
  void report_value(void);
};


class param_init_matrix: public named_dvar_matrix,public initial_params
{
  virtual void dev_correction(const dmatrix&, const int&);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const  dvector&, const int&);
public:

  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x,const nint& ii);
  virtual int size_count(void);
  virtual void save_value(void);
  virtual void bsave_value(void);
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
  void allocate(const ad_integer& rmin, const ad_integer& rmax, const index_type& cmin,
                const index_type& cmax, const char * = "UNNAMED");
  void allocate(const ad_integer& rmin, const ad_integer& rmax, const index_type& cmin,
    const index_type& cmax, int phase_start = 1,const char * = "UNNAMED");
  param_init_matrix(void);
  param_init_matrix& operator = (const dmatrix& m);
  param_init_matrix& operator = (const dvar_matrix& m);
  param_init_matrix& operator = (const dvariable& m);
  param_init_matrix& operator = (const double& m);
};

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

class param_init_bounded_matrix: public param_init_matrix
{
  double minb;
  double maxb;
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
  //virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
public:

  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){;};

public:

  param_init_bounded_matrix(void);
  void allocate(int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");

  void allocate(const ad_integer& rmin, const ad_integer& rmax, const index_type& cmin,
                const index_type& cmax, double _minb, double _maxb,
    const char * = "UNNAMED");
  void allocate(const ad_integer& rmin, const ad_integer& rmax, const index_type& cmin,
                const index_type& cmax, double _minb, double _maxb,
    int phase_start=1,const char * = "UNNAMED");
};

class data_int : public model_name_tag
{
protected:
  int val;
  data_int& operator=(const int);
  void allocate(int n,const char * s="UNNAMED");
  void allocate(const char * s="UNNAMED");
  friend class model_data;
  friend class model_parameters;
  friend int operator + (int n,data_int v);
  friend int operator + (data_int v,int n);
  friend int operator + (data_int v,data_int n);
public:
  operator int() {return val;}
#if !defined (__BORLANDC__)
  //operator const int() const {return val;}
#endif
  virtual ~data_int(){;}
};

class named_adstring : public adstring, public model_name_tag
{
protected:
  void allocate(const char * s1,const char * s="UNNAMED");
  void operator = (const adstring&);
  void operator = (const char *);
public:
};

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



class dll_data_int : public data_int
{
public:
  int *pi;
  void allocate(int *_pi,const char * s);
  virtual ~dll_data_int();
};

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
  friend class model_data;
};

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

class data_3array : public named_d3_array
{
public:
  data_3array(void) : named_d3_array() {;}
private:
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * ="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, int rmax,
                int cmin, int cmax, const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, const ivector& rmax,
                int cmin, int cmax, const char * ="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, const ivector& rmax,
                int cmin, int cmax, const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin, int cmax,
                const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                const ivector& cmax, const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, int cmin,
                const ivector& cmax, const char * ="UNNAMED");
  void allocate(int hsl, int hsu, index_type& rmin, const index_type& rmax, const index_type& cmin,
                const index_type& cmax,const char * ="UNNAMED");
  friend class model_data;
};

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

class data_3iarray : public named_i3_array
{
  data_3iarray(void) : named_i3_array() {;}
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * ="UNNAMED");
  void allocate(int hsl, int hsu, const index_type& rmin, const index_type& rmax, const index_type& cmin,
                const index_type& cmax, const char * ="UNNAMED");
  friend class model_data;
};

class data_5array : public named_d5_array
{
  data_5array(void) : named_d5_array() {;}
  void allocate(int hhsl,int hhsu,
    int hhhsl,int hhhsu,
    int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(ad_integer hhhsl,ad_integer hhhsu,
                const index_type& hhsl, const index_type& hhsu,
                const index_type& hsl, const index_type& hsu, const index_type& rmin, const index_type& rmax,
                const index_type& cmin, const index_type& cmax, const char * ="UNNAMED");
  friend class model_data;
};

class data_4array : public named_d4_array
{
  data_4array(void) : named_d4_array() {;}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(ad_integer hhsl, ad_integer hhsu, const index_type& hsl, const index_type& hsu, const index_type& rmin, const index_type& rmax,
     const index_type& cmin, const index_type& cmax,const char * ="UNNAMED");
  friend class model_data;
};

class data_imatrix : public named_imatrix
{
  data_imatrix(void) : named_imatrix() {;}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int rmin, int rmax, const index_type&, const index_type& cmax,
    const char * ="UNNAMED");
  friend class model_data;
};

class data_vector : public named_dvector
{
public:
  data_vector& operator=(const dvector& m);
  data_vector& operator = (CGNU_DOUBLE m);
  data_vector(void) : named_dvector() {;}
private:
  void allocate(int imin,int imax,const char * ="UNNAMED");
  void allocate(int imin, const ivector& imax,const char * ="UNNAMED");
  friend class model_data;
};

class dll_data_vector : public data_vector
{
public:
  double * pd;
  void allocate(double * pd,int imin,int imax,const char * ="UNNAMED");
  void allocate(double *pd,int imin, const ivector& imax, const char * ="UNNAMED");
  virtual ~dll_data_vector();
  dll_data_vector& operator = (const dvector& x);
  dll_data_vector& operator = (const double& x);
};

class data_ivector : public named_ivector
{
public:
  data_ivector(void) : named_ivector() {;}
private:
  void allocate(int imin,int imax,const char * ="UNNAMED");
  friend class model_data;
};

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

class dll_data_number : public data_number
{
public:
  double * pd;
  void allocate(double *_pd,const char * s);
  virtual ~dll_data_number();
  dll_data_number & operator=(const double& m);
};

typedef dvariable (model_parameters::*PMF) (const dvariable&);
typedef dvariable (model_parameters::*PMFI) (const dvariable&,int n);
typedef dvariable (model_parameters::*PMFVI) (const dvar_vector&,int n);
typedef void (model_parameters::*PMFVIV4) (const dvar_vector&,int n,
  dvariable& f1, const dvariable& f2, const dvariable& f3, const dvariable& f4);

class function_minimizer
{
public:
  int ifn;
  int maxfn;
  int iprint;
  double crit;
  int imax;
  double dfn;
  int iexit;
  int ihflag;
  int ihang;
  int scroll_flag;
  int maxfn_flag;
  int quit_flag;
  double min_improve;
protected:
  double ffbest;
private:
  gradient_structure * pgs;
  adstring_array param_labels;
  ivector param_size;
protected:
  void report_function_minimizer_stats(void){;}
  virtual void userfunction(void)=0;
  virtual void report(void){;};
  static dvector convergence_criteria;
  static dvector maximum_function_evaluations;
  static int sd_flag;
  static adstring user_data_file;
  static adstring user_par_file;
public:
  void limited_memory_quasi_newton(const independent_variables&,int);
  function_minimizer(long int sz=0L);
  void likeprof_routine(double global_min);
  virtual ~function_minimizer();
  virtual void other_calculations(void){;}
  virtual void minimize(void);
  virtual void between_phases_calculations(void){;}
  void computations(int argc,char * argv[]);
  void computations1(int argc,char * argv[]);
  void computations_np(int argc,char * argv[]);
  void computations(void);
  void hess_routine(void);
  dmatrix dep_hess_routine(const dvariable& dep);
  void mcmc_routine(int,int,double,int);
  void mcmc_eval(void);
  //void hess_routine_and_constraint(int);
  void function_minimizer::hess_routine_and_constraint(int iprof,const dvector& g,
    dvector& fg);
  dmatrix diag_hess_routine(void);
  void hess_inv(void);
  void depvars_routine(void);
  void sd_routine(void);

#ifdef CURVE_CORRECT
  void constraint_hess_routine(int ip);
  void get_curvature_correction_factors(int ip,
    dvector& g, const int underflow_flag, const dvector& eigenvals,
    dvector& curvcor);
#endif
  double projected_jacobian(const dvector& g, const dvector& xscale);

  void prof_minimize(int iprof, double sigma,
    double new_value, const double& fprof, const int underflow_flag,
    double global_min, const double& penalties, const double& final_weight);

  void prof_hess_routine(int ip,double new_value,double final_weight);

  void quasi_newton_minimizer1(int nvar,double _crit,
    double& f, const independent_variables& x, const dvector& g);

  double hess_determinant(int underflow_flag);

#ifndef CURVE_CORRECT
  void normalize_posterior_distribution(double udet,
    dvector& siglevel, const ofstream& ofs2, int num_pp,
    const dvector& all_values, const dmatrix& actual_value, double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet, const dmatrix& xdist,
    const dmatrix& penalties);
  //  dmatrix& penalties, const dmatrix& lg_jacob);
#else
  void normalize_posterior_distribution(double udet,
    const dvector& siglevel, const ofstream& ofs2, int num_pp,
    const dvector& all_values, const dmatrix& actual_value,
    double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet,
    const dmatrix& xdist,
    const d3_array& eigenvals, d3_array& curvcor);
#endif
  void get_particular_grad(int iprof, int nvar, const dvector& fg, const dvector& g);
  double projected_hess_determinant(const dvector& g, const int underflow_flag,
    const dvector& xscale, const double& ln_det_proj_jac);
/double projected_hess_determinant(const dvector& fg, const dvector& g,
  //const int underflow_flag, const dvector& xscale, const double& ln_det_proj_jac);
  double projected_hess_determinant(const dvector& g, const int underflow_flag);
  double projected_hess_determinant(const dmatrix& hh, const dvector& g,
    const int underflow_flag);
  //double projected_hess_determinant(const dvector& g,const int underflow_flag,
    //dvector& xscale, const double& ln_det_proj_jac);

  double projected_hess_determinant(const dvector& fg, const dvector& g,
    const int underflow_flag, const dvector& curvscale, const dvector& xscale,
    double& ln_det_proj_jac, const double& tmp, const dmatrix& hesses);
  double diag_projected_hess_determinant(const dvector& g, const int underflow_flag,
    dmatrix& dh);
  double unrestricted_hess_determinant(void);
  void monte_carlo_routine(void);
  double get_monte_carlo_value(int nvar, const independent_variables& x);
  double get_monte_carlo_value(int nvar, const dvector& x);
  void sob_routine(int nmcmc,double dscale,int restart_flag);
  void sobol_importance_routine(int nmcmc,int iseed0,double dscale,
  int restart_flag);

  void multint4(int n, const dvar_vector& a, const dvar_vector& b, const dvar_vector& h,
    double al, int m, const dvariable& e, const dvariable& aint1, const dvariable& aint2,
    dvariable& aint3, const dvariable& aint4, const int& key, PMFVIV4 f);

  void multint(int n, const dvar_vector& a, const dvar_vector& b, const dvar_vector& h,
    double al, int m, const dvariable& e, const dvariable& aint, const int& key, PMFVI f);

  static void set_runtime(void);
  dvariable adromb(PMF,double a,double b,int ns=9);
  dvariable adromb(PMF, const dvariable& a, double b,int ns = 9);
  dvariable adromb(PMF, const dvariable& a, const dvariable& b, int ns = 9);
  dvariable adromb(PMF, double a, const dvariable& b, int ns = 9);

  dvariable adrombo(PMF, double a, double b, int ns = 9);
  dvariable adrombo(PMF, const dvariable& a, double b, int ns=9);
  dvariable adrombo(PMF, const dvariable& a, const dvariable& b, int ns = 9);
  dvariable adrombo(PMF, double a, const dvariable& b, int ns = 9);

  dvariable trapzd(void*,double a,double b,int n);
  dvariable trapzd(PMF,double a,double b,int n);
  dvariable trapzd(PMF, double a, const dvariable& b, int n);
  dvariable trapzd(PMF, const dvariable& a, double b, int n);
  dvariable trapzd(PMF, const dvariable& a, const dvariable& b, int n);

  dvariable midpnt(PMF,double a,double b,int n);
  dvariable midpnt(PMF, double a, const dvariable& b, int n);
  dvariable midpnt(PMF, const dvariable& a, double b, int n);
  dvariable midpnt(PMF, const dvariable& a, const dvariable& b, int n);

  virtual void * mycast() { return (void*)this;}

  void adamoeba(const dmatrix& p, const dvector& y, int ndim, double ftol, int maxfn);
  void set_initial_simplex(const dmatrix& p, const dvector& y,int nvar, const dvector& x,
    double delta);
  double amxxx(const dmatrix& p, const dvector& y, const dvector& psum, int ndim,
    int ihi, double fac);
};

cifstream& operator>>(const cifstream& s, const param_init_number& x);
cifstream& operator>>(const cifstream& s, const param_init_vector& v);
cifstream& operator>>(const cifstream& s, const param_init_matrix& m);
ostream& operator<<(const ostream& s, const label_class& lc);

class stddev_params
{
protected:
public:
  static stddev_params * stddevptr[100]; // this should be a resizeable array
  static int num_stddev_params;
  void allocate(void){;};
  static int num_stddev_calc(void);
public:
  stddev_params(void){;}
  virtual int size_count(void)=0; // get the number of active parameters
  virtual void set_dependent_variables(void)=0;
  virtual void copy_value_to_vector(const dvector&, const int&) = 0;
  static void copy_all_values(const dvector& x, const int& ii);//get the number of active parameters
  virtual void add_to_list(void);
  virtual const char * label()=0;
  friend class function_minimizer;
};

class likeprof_params
{
  double stepsize;
  int    stepnumber;
protected:
public:
  static likeprof_params * likeprofptr[50]; // this should be a
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

class param_stddev_vector: public named_dvar_vector , stddev_params
{
  virtual int size_count(void); // get the number of active parameters
  virtual const char * label(void);
  param_stddev_vector();
  void allocate(int imin,int imax,const char * s="UNNAMED");
  virtual void set_dependent_variables(void);
  friend class model_parameters;
  void copy_value_to_vector(const dvector& x, const int& ii);
  param_stddev_vector& operator=(const dvar_vector& m);
  param_stddev_vector& operator=(const dvector& m);
  param_stddev_vector& operator = (CGNU_DOUBLE m);
};

class param_stddev_number: public named_dvariable , public stddev_params
{
  void allocate(const char *s="UNNAMED");
  virtual int size_count(void); // get the number of active parameters
  virtual const char * label(void);
  void copy_value_to_vector(const dvector& x, const int& ii);
protected:
  param_stddev_number();
  friend class model_parameters;
  virtual void set_dependent_variables(void);
  param_stddev_number& operator=(const prevariable&);
  param_stddev_number& operator = (CGNU_DOUBLE);
};

class param_likeprof_number: public param_stddev_number,
  public likeprof_params
{
  double sigma;
  void allocate(const char *s="UNNAMED");
  virtual int size_count(void); // get the number of active parameters
  virtual const char * label(void);
  virtual double& get_sigma(void){return sigma;}
  virtual double get_value(void){return value(*this);}
  //void copy_value_to_vector(const dvector& x, const int& ii);
  virtual dvariable variable(void){ return dvariable(*this);}
  param_likeprof_number();
  friend class model_parameters;
public:
  param_likeprof_number& operator=(const prevariable&);
    param_likeprof_number& operator = (CGNU_DOUBLE);
};

class param_stddev_matrix: public named_dvar_matrix , stddev_params
{
  virtual int size_count(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * s="UNNAMED");
  param_stddev_matrix(void);
  friend class model_parameters;
  virtual void set_dependent_variables(void);
  void copy_value_to_vector(const dvector& x, const int& ii);
  param_stddev_matrix& operator = (CGNU_DOUBLE m);
  param_stddev_matrix& operator=(const dmatrix& m);
  param_stddev_matrix& operator=(const dvar_matrix& m);
};

class ad_comm
{
protected:
  ad_comm(int argc,char * argv[]);
  ad_comm(void);
  void allocate(void);
  ~ad_comm();
public:
  static streampos change_datafile_name(const adstring& s, const streampos& off = 0);
  static streampos change_pinfile_name(const adstring& s, const streampos& off = 0);
  static cifstream * global_datafile;
  static cifstream * global_parfile;
  static ofstream *  global_savefile;
  static ofstream *  global_logfile;
  static uostream *  global_bsavefile;
  static uistream * global_bparfile;
  static adstring adprogram_name;
  static adstring working_directory_path;
  static char option_flags[];
  static int argc;
  static unsigned int wd_flag;
  static unsigned char directory_prefix;
  static char ** argv;
};



  class objective_function_value : public named_dvariable
  {
  public:
    static objective_function_value * pobjfun;
    static double gmax;
    objective_function_value();
    objective_function_value& operator=(const prevariable& v);
    objective_function_value& operator = (CGNU_DOUBLE v);
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
class param_init_matrix: public named_dvar_matrix,public initial_params
{
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
//virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
public:

  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual int size_count(void);
  virtual void save_value(void);
  virtual void bsave_value(void);
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

class param_init_d3array: public named_dvar3_array,public initial_params
{
public:

  virtual void dev_correction(const dmatrix&, const int&);
  virtual void curv_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void set_simulation_bounds(const dmatrix& symbds, const int& ii);
//  virtual void set_simulation_bounds(const dmatrix&, const dvector& symbds, const int& ii);
  virtual void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&);
  virtual void add_value(const dvector&, const int&);
  virtual void get_jacobian(const dvector&, const dvector&, const int&);
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual int size_count(void);
  virtual void save_value(void);
  virtual void bsave_value(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void mc_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii);

public:

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


//double set_value_mc(const double& x,CGNU_DOUBLE fmin,CGNU_DOUBLE fmax);

void set_value_mc(const dvar_vector& x, const dvar_vector& v, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax);

double set_value_inv_mc(double v,double fmin,double fmax);

double set_value_inv_mc(const prevariable& v, double fmin, double fmax);

void set_value_inv_mc(const dvar_vector& x, const dvector& v, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax);

//double set_value_inv_mc(const dvector&, const dvector& x, int ii, double minb, double maxb);

double set_value_mc(double z,double min,double max);
double ndfboundp(double x, double fmin, double fmax, const double& fpen);
double ndfboundp_mc(double x, double fmin, double fmax, const double& fpen);

void bounded_multivariate_normal_mcmc(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& wght, const dvector& y, const random_number_generator& rng);

void bounded_multivariate_uniform_mcmc(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& wght, const dvector& y, const random_number_generator& rng);

dvector bounded_multivariate_normal(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& lprob, const random_number_generator& rng);

dvector bounded_multivariate_normal_sobol(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& lprob, const random_number_generator& rng);

dvector probing_bounded_multivariate_normal(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& lprob,double pprobe, const random_number_generator& rng);

dvector bounded_multivariate_uniform(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& lprob, const random_number_generator& rng);

void probing_bounded_multivariate_normal_mcmc(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& wght, const dvector& v,double pprobe, const random_number_generator& rng);

int option_match(int argc,char * argv[], char * string);
int option_match(int argc, char *argv[], char *string, const int& nopt);

double inv_cumd_exp(double x);
double cumd_exp(double x);

double ffmax(double a,double b);
double ffmin(double a,double b);

void check_datafile_pointer(void * p);

#if (defined(__GNUDOS__))
#  if (defined(linux)) || (defined(__ADSGI__))
#    define IOS_BINARY 0
#  else
#    define IOS_BINARY ios::bin
#  endif
#endif

#if (defined(__BORLANDC__))
#  define IOS_BINARY ios::binary
#endif

adstring get_reportfile_name(void);

void ad_make_code_reentrant(void);

char** parse_sp_options(char *pname, const int& argc, char *sp_options);

void cleanup_argv(int nopt,char *** pa);

void get_sp_printf(void);

void do_dll_housekeeping(int argc,char ** argv);

void adwait(double);

int ad_get_commandline_option(const char * option_label, const int & option_value,
  const char * error_message);

#endif

