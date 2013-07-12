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
#if defined(__GNUC__)
  #if (__GNUC__ < 3)
    #pragma interface
  #endif
#else
  #pragma interface
#endif

#ifndef _ADMODEL_H_
  #define  _ADMODEL_H_
#ifdef __GNUDOS__
  #define CGNU_DOUBLE double
#else
  #define CGNU_DOUBLE const double&
#endif
#include <fvar.hpp>
#include <d4arr.hpp>
#include <cifstrem.h>
#include <iomanip.h>
#include <adstring.hpp>
#define param_matrix named_dvar_matrix
#define param_vector named_dvar_vector
#define param_number named_dvariable
#define param_3array named_dvar3_array
#define param_4array named_dvar4_array
#define MAX_NUM_DATA_FILES 10
#define MAX_NUM_PAR_FILES 10

  double mfexp(CGNU_DOUBLE );
  dvariable mfexp(const prevariable& v1);
  dvar_vector mfexp(const dvar_vector& );
  dvector mfexp(const dvector& );


 void set_value_inv(const dvariable& x, const dvector& v, const int& ii);
 void set_value_inv(const dvar_matrix& x, const dvector& v, const int& ii);
 void set_value_inv(const dvar_vector&, const dvector&, const int &ii);
 void set_value_inv(const dvariable& u, const dvector& x, const int& ii,CGNU_DOUBLE fmin,
  CGNU_DOUBLE fmax);
 void set_value_inv(const  dvar_matrix& u, const dvector& x, const int& ii,
  CGNU_DOUBLE fmin,CGNU_DOUBLE fmax);

  void copy_value_to_vector(const prevariable& x,const dvector& v,const int& ii);
  void copy_value_to_vector(const dvar_vector& x,const dvector& v,const int& ii);
  void copy_value_to_vector(const dvar_matrix& x,const dvector& v,const int& ii);
  void copy_value_to_vector(const dvar3_array& x,const dvector& v,const int& ii);

  void restore_value_from_vector(const prevariable& x, const dvector& v, const int& ii);
  void restore_value_from_vector(const dvar_vector& x, const dvector& v, const int& ii);
  void restore_value_from_vector(const dvar_matrix& x, const dvector& v, const int& ii);
  void restore_value_from_vector(dvar3_array& x, const dvector& v, const int& ii);


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
  operator const char * () { return name;}
  label_class(const char * s){name=s;}
};

/**
 * Description not yet available.
 * \param
 */
class model_name_tag
{
  const char * name;
  //friend ostream& operator<<(const ostream& os, const model_name_tag& mnt);
public:
  model_name_tag(void){}
  void allocate(const char * s);
  label_class label(void){return name;}
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar_vector : public dvar_vector, public model_name_tag
{
protected:
  named_dvar_vector(void) : dvar_vector(), model_name_tag() {}
  named_dvar_vector& operator=(const dvar_vector& m);
  named_dvar_vector& operator=(const dvector& m);
  named_dvar_vector& operator = (CGNU_DOUBLE m);
  named_dvar_vector& operator=(const prevariable& m);
  friend class model_parameters;
  void allocate(int mmin,int mmax,const char * s);
};

/**
 * Description not yet available.
 * \param
 */
class named_dvariable : public dvariable, public model_name_tag
{
  //named_dvariable& operator=(const dvariable& m);
protected:
  named_dvariable(void) : dvariable(), model_name_tag() {}
  void allocate(const char * s);
  named_dvariable& operator=(const prevariable& m);
  named_dvariable& operator = (CGNU_DOUBLE m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar_matrix : public dvar_matrix, public model_name_tag
{
protected:
  named_dvar_matrix(void) : dvar_matrix(), model_name_tag() {}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
public:
  named_dvar_matrix& operator = (CGNU_DOUBLE m);
  named_dvar_matrix& operator=(const dmatrix& m);
  named_dvar_matrix& operator=(const dvar_matrix& m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvar3_array : public dvar3_array, public model_name_tag
{
protected:
  named_dvar3_array(void) : dvar3_array(), model_name_tag() {}
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * s);
  void allocate(int hsl, int hsu, const ivector& rmin, int rmax,
    int cmin,int cmax,const char * s);
  void allocate(int hsl, int hsu, int rmin, const ivector& rmax,
    int cmin, int cmax, const char * s);
  void allocate(int hsl, int hsu, const ivector& rmin, const ivector& rmax,
    int cmin,int cmax,const char * s);
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
    int cmax,const char * s);
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                const ivector& cmax, const char *s);
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,
                const ivector& cmax, const char *s);
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
  named_dvar4_array(void) : dvar4_array(), model_name_tag() {}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,const char * s);
  named_dvar4_array& operator=(const dvar4_array& m);
  named_dvar4_array& operator=(const d4_array& m);
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class named_dvector : public dvector, public model_name_tag
{
protected:
  named_dvector(void) : dvector(), model_name_tag() {}
  void allocate(int mmin,int mmax,const char * s);
  named_dvector& operator=(const dvector& m);
  named_dvector& operator = (CGNU_DOUBLE m);
};

/**
 * Description not yet available.
 * \param
 */
class named_ivector : public ivector, public model_name_tag
{
protected:
  named_ivector(void) : ivector(), model_name_tag() {}
  void allocate(int mmin,int mmax,const char * s);
};

/**
 * Description not yet available.
 * \param
 */
class named_dmatrix : public dmatrix, public model_name_tag
{
protected:
  named_dmatrix(void) : dmatrix(), model_name_tag() {}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
  named_dmatrix& operator=(const dmatrix& m);
  named_dmatrix& operator = (CGNU_DOUBLE m);
};

/**
 * Description not yet available.
 * \param
 */
class named_imatrix : public imatrix, public model_name_tag
{
protected:
  named_imatrix(void) : imatrix(), model_name_tag() {}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * s);
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
  named_d3_array(void) : d3_array(), model_name_tag() {}
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * s);
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
};

/**
 * Description not yet available.
 * \param
 */
class named_d4_array : public d4_array, public model_name_tag
{
protected:
  named_d4_array(void) : d4_array(), model_name_tag() {}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,
    int rmax,int cmin,int cmax,const char * s);
  named_d4_array& operator=(const d4_array& m);
};

class function_minimizer;

/**
 * Description not yet available.
 * \param
 */
class initial_params
{
protected:
  int active_flag;
  int initial_value_flag;
  double initial_value;
public:
  static initial_params * varsptr[120]; // this should be a resizeable array
  static num_initial_params;
  static num_active_initial_params;
  static int max_number_phases;
  static int current_phase;
  static int sd_phase;
  int phase_start;
  int phase_stop;
  virtual void set_value(const dvar_vector&, const int&, const dvariable& pen) = 0;
  void set_initial_value(double x);
  virtual void set_value_inv(const dvector&, const int&) = 0;
  virtual void copy_value_to_vector(const dvector&, const int&) = 0;
  virtual void restore_value_from_vector(const dvector&, const int&) = 0;
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii) = 0;
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii)=0;
  virtual int size_count(void)=0; // get the number of active parameters
  virtual void save_value(void)=0; // save the objects value in a file
  virtual void save_value(const ofstream& ofs, int prec)=0;
	virtual const char * label()=0;
  void allocate(int _phase_start);
  void set_active_flag(void);
  void set_inactive_flag(void);
  friend int active(const initial_params& ip);
public:
  initial_params(void);
  static void xinit(const dvector& x); // get the number of active parameters
  static void copy_all_values(const dvector& x, const int& ii); //save all initial parameter
                                                   // values in a vector
  static void restore_all_values(const dvector& x, const int& ii); //get ivalues for all
                                    // active parameters from a vector
  static dvariable reset(const dvar_vector& x); // get the number of active parameters
  static int nvarcalc(void);
  static int num_active_calc(void);
  static int stddev_scale(const dvector& d,const dvector& x);
  static void read(void);
  static void save(void);
  static void save(const ofstream& ofs, int prec);
  static void restore(const ifstream& ifs);
  virtual void restore_value(const ifstream& ifs) = 0;
	virtual void add_to_list(void);
  friend class function_minimizer;
};

/**
 * Description not yet available.
 * \param
 */
class param_init_vector: public named_dvar_vector , public initial_params
{
public:
  virtual const char * label(void);
protected:
  param_init_vector();
private:
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual int size_count(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int&);
  virtual void hess_scale(const dvector& d, const dvector& x, const int&){};
  param_init_vector();
  virtual void save_value(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  void report_value(void);
  //virtual void read_value(void);
  void allocate(int imin,int imax,int phasestart=1,const char * s="UNNAMED");
  void allocate(int imin,int imax,const char * s="UNNAMED");
  friend class model_parameters;
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_vector: public named_dvar_vector,public initial_params
{
  virtual void* parent_this(void){return this;}
public:
  double minb;
  double maxb;
  param_init_bounded_vector();
private:
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual int size_count(void);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){};
  void allocate(int imin,int imax,double _minb,double _maxb,
    int phasestart=1, const char * name="UNNAMED");
  void allocate(int imin,int imax,double _minb,double _maxb,
    const char * name="UNNAMED");
  friend class model_parameters;
  virtual const char * label(void);
  virtual void save_value(const ofstream& ofs,int prec);
  virtual void restore_value(const ifstream& ifs);
  virtual void save_value(void);
  void report_value(void);
  //virtual void read_value(void);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_dev_vector: public param_init_bounded_vector
{
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_number: public named_dvariable , public initial_params
{
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual int size_count(void);
  virtual void save_value(const ofstream& ofs, int prec);
  virtual void restore_value(const ifstream& ifs);
  virtual void save_value(void);
  void report_value(void);
  virtual const char * label(void);
  param_init_number& operator = (CGNU_DOUBLE m);
  param_init_number& operator = (const prevariable& m);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){};
  //virtual void read_value(void);
protected:
  void allocate(int phase_start=1,const char *s="UNNAMED");
  void allocate(const char *s="UNNAMED");
  friend class model_parameters;
  param_init_number();
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_number: public param_init_number
{
  double minb;
  double maxb;
protected:
  param_init_bounded_number();
  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void copy_value_to_vector(const dvector& x, const int& ii);
  virtual void restore_value_from_vector(const dvector&, const int&);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){};
  virtual const char * label(void);
  void report_value(void);
  void allocate(double _minb,double _maxb,int phase_start=1,
    const char * s="UNNAMED");
  param_init_bounded_number& operator = (CGNU_DOUBLE m);
  param_init_bounded_number& operator=(const prevariable& m);
  void allocate(double _minb,double _maxb,const char * s="UNNAMED");
  friend class model_parameters;
  param_init_bounded_number();
};

/**
 * Description not yet available.
 * \param
 */
class param_init_matrix: public named_dvar_matrix,public initial_params
{
public:

  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
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

  void allocate(int rmin,int rmax,int cmin,int cmax,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  param_init_matrix(void);
};

/**
 * Description not yet available.
 * \param
 */
class param_init_bounded_matrix: public param_init_matrix
{
  double minb;
  double maxb;
public:

  virtual void set_value(const dvar_vector& x, const int& ii, const dvariable& pen);
  virtual void set_value_inv(const dvector& x, const int& ii);
  virtual void sd_scale(const dvector& d, const dvector& x, const int& ii);
  virtual void hess_scale(const dvector& d, const dvector& x, const int& ii){};

public:

  void allocate(int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,
    int phase_start=1,const char * = "UNNAMED");
  void allocate(int rmin,int rmax,int cmin,int cmax,
    double _minb,double _maxb,const char * = "UNNAMED");
  param_init_bounded_matrix(void);
};

/**
 * Description not yet available.
 * \param
 */
class data_int : public model_name_tag
{
  int val;
  void allocate(int n,const char * s="UNNAMED");
  void allocate(const char * s="UNNAMED");
  operator int() {return val;}
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
class data_matrix : public named_dmatrix
{
  data_matrix(void) : named_dmatrix() {}
  void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * = "UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_3array : public named_d3_array
{
  data_3array(void) : named_d3_array() {}
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,int cmax,
    const char * ="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, const ivector& rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl, int hsu, const ivector& rmin, const ivector& rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin, int cmax,
    const char * ="UNNAMED");
  void allocate(int hsl, int hsu, int rmin, int rmax, const ivector& cmin,
                const ivector& cmax, const char * = "UNNAMED");
  void allocate(int hsl,int hsu,int rmin,int rmax,int cmin,
                const ivector& cmax ,const char * = "UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_4array : public named_d4_array
{
  data_4array(void) : named_d4_array() {}
  void allocate(int hhsl,int hhsu,int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_imatrix : public named_imatrix
{
  data_imatrix(void) : named_imatrix() {}
  void allocate(int rmin,int rmax,int cmin,int cmax,const char * ="UNNAMED");
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
  data_vector& operator = (CGNU_DOUBLE m);
private:
  data_vector(void) : named_dvector() {}
  void allocate(int imin,int imax,const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_ivector : public named_ivector
{
  data_ivector(void) : named_ivector() {}
  void allocate(int imin,int imax,const char * ="UNNAMED");
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class data_number : public model_name_tag
{
  double val;
  void allocate(const char * ="UNNAMED");
public:
  void report_value(void);
  operator double() {return val;}
  friend class model_data;
};

/**
 * Description not yet available.
 * \param
 */
class function_minimizer
{
public:
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
  void report_function_minimizer_stats(void){}
  virtual void userfunction(void)=0;
  virtual void report(void){};
  static dvector convergence_criteria;
  static dvector maximum_function_evaluations;
  static int sd_flag;
  static adstring user_data_file;
  static adstring user_pin_file;
public:
  function_minimizer(long int sz=0L);
  void likeprof_routine(double global_min);
  virtual ~function_minimizer();
  virtual void minimize(void);
  void computations(int argc,char * argv[]);
  void computations_np(int argc,char * argv[]);
  void computations(void);
  void hess_routine(void);
  void hess_inv(void);
  void depvars_routine(void);
  void sd_routine(void);

#ifdef CURVE_CORRECT
  void constraint_hess_routine(int ip);
  void get_curvature_correction_factors(int ip,
    dvector& g, const int underflow_flag, const dvector& eigenvals,
    dvector& curvcor);
#endif

  void prof_minimize(int iprof, double sigma,
    double new_value, const double& fprof, const int underflow_flag,
    double global_min, const double& penalties, const double& final_weight);
#ifndef CURVE_CORRECT
  void normalize_posterior_distribution(double udet,
    dvector& siglevel, const ofstream& ofs2,int num_pp,
    dvector& all_values, const dmatrix& actual_value, double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet, const dmatrix& xdist,
    dmatrix& penalties, const dmatrix& lg_jacob, const dmatrix& pdet,
    dmatrix& lg_prjacob);
#else
  void normalize_posterior_distribution(double udet,
    dvector& siglevel, const ofstream& ofs2, int num_pp,
    dvector& all_values, const dmatrix& actual_value, double global_min,
    int offset, const dmatrix& lprof, const dmatrix& ldet, const dmatrix& xdist,
    d3_array& eigenvals,d3_array& curvcor);
#endif
	void get_particular_grad(int iprof,int nvar, const dvector& g);
double projected_hess_determinant(const dvector& fg, const dvector& g,
  const int underflow_flag, const dvector& xscale, const double& ln_det_proj_jac)
  double projected_hess_determinant(const dmatrix& hh, const dvector& g,
    const int underflow_flag);
  double projected_hess_determinant(const dvector& g,
    const int underflow_flag, const dvector& xscale, const double& ln_det_proj_jac,
    double& ln_det_proj);

  double diag_projected_hess_determinant(const dvector& g, const int underflow_flagi,
    dmatrix&);
	double unrestricted_hess_determinant(void);

	static void set_runtime(void);
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
protected:
public:
  static stddev_params * stddevptr[100]; // this should be a resizeable array
  static num_stddev_params;
  void allocate(void){};
  static int num_stddev_calc(void);
public:
  stddev_params(void){}
  virtual int size_count(void)=0; // get the number of active parameters
  virtual void set_dependent_variables(void)=0;
  virtual void copy_value_to_vector(const dvector&, const int&) = 0;
  static void copy_all_values(const dvector& x, const int& ii); //get the number of active parameters
  virtual void add_to_list(void);
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
  static likeprof_params * likeprofptr[50]; // this should be a
                                               // resizeable array
  static num_likeprof_params;
  void allocate(void){};
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
class param_likeprof_number: public param_stddev_number ,
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
class ad_comm
{
protected:
  ad_comm(char * argv[]);
  ad_comm(const char * root);
  void allocate(const char * root);
  ~ad_comm();
public:
  static cifstream * global_datafile[MAX_NUM_DATA_FILES];
  static cifstream * global_parfile[MAX_NUM_PARS_FILES];
  static ofstream *  global_savefile;
  static adstring adprogram_name;
  static change_datafile_name;
  static change_parfile_name;
};

/**
 * Description not yet available.
 * \param
 */
  class objective_function_value : public named_dvariable
  {
  public:
    static objective_function_value * pobjfun;
    objective_function_value();
    objective_function_value& operator=(const prevariable& v);
    objective_function_value& operator = (CGNU_DOUBLE v);
  };

/**
 * Description not yet available.
 * \param
 */
class param_init_d3array: public named_dvar3_array,public initial_params
{
public:

  virtual void set_value(const dvar_vector& x,const int& ii, const dvariable& pen);
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

#endif
