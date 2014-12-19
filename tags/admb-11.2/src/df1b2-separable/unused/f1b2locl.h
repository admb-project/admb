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
#if !defined(__F1B2LOCL__)
# define __F1B2LOCL__
#include <df1b2fun.h>
#include <adrndeff.h>

class local_dep_df1b2variable;

/**
 * Description not yet available.
 * \param
 */
class local_init_var
{
public:
  static df1b2variable * funnel_constraints_penalty;
  static void reset_counters(void) { num_vars=0; /*num_all_vars=0;*/}
  static void end_local_calculations(void);
  static int num_vars;
  //static int num_all_vars;
  static int num_inactive_vars;
  static int num_active_parameters;
  static init_df1b2vector * py;
  static imatrix * plist;
  int index;
  static   local_init_var ** list;
  //static   local_init_var ** all_list;
  static   local_init_var ** inactive_list;
  local_init_var(void) { add_to_list(); }
  void add_to_list(void);
  void delete_from_list(void);
  void add_to_inactive_list(void);
  virtual void allocate(void);
  //virtual void xinit(void);
  static void dot_calcs_all(local_dep_df1b2variable&);
  virtual void dot_calcs(local_dep_df1b2variable&,int j)=0;
  virtual void set_dot(int)=0;
  static void set_dot_all(void);
  virtual void xinit(init_df1b2vector&,int& ii)=0;
  virtual void xinit(dvector&,int& ii)=0;
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&)=0;
  virtual void set_value(const init_df1b2vector&,const int& ii)=0;
  virtual void set_index(imatrix&,int& ii)=0;
  virtual int nvar_calc(void)=0;

  static void reset(init_df1b2vector& x);

  static void allocate_all(void);
  static int nvarcalc_all(void);
};

/**
 * Description not yet available.
 * \param
 */
class local_init_df1b2variable : public local_init_var, public df1b2variable
{
public:
  const df1b2variable * p;
  const double * xdot;
  int type;
  void * pointer;
  double xu;
  int ind_index;
  int nvar_calc(void){return 1;}
  virtual void set_dot(int ii){*(get_u_dot()+ii)=1;ii++;}
  local_init_df1b2variable(const df1b2_init_number & x);
  local_init_df1b2variable(const df1b2variable & x);
  local_init_df1b2variable(double xu,double * xdot);
  local_init_df1b2variable(void);
  local_init_df1b2variable(const random_effects_bounded_vector_info&);
  virtual void allocate(void);
  virtual void allocate(const df1b2variable&);
  virtual void preallocate(const df1b2variable&);
  virtual void xinit(init_df1b2vector&,int& ii);
  virtual void xinit(dvector&,int& ii);
  virtual void set_value(const init_df1b2vector&,const int& ii);
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_index(imatrix&,int& ii);
  virtual void dot_calcs(local_dep_df1b2variable&,int j);
};

/**
 * Description not yet available.
 * \param
 */
class local_init_bounded_df1b2vector : public local_init_var,
  public df1b2vector
{
  const df1b2vector * p;
public:
  int nvar_calc(void);
  virtual void set_dot(int offset){cout << "HERE" << endl; ad_exit(1);}
  local_init_bounded_df1b2vector(const df1b2_init_bounded_vector & x);
  virtual void xinit(init_df1b2vector&,int& ii);
  virtual void xinit(dvector&,int& ii){ cout << "here"<< endl;}
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_value(const init_df1b2vector&,const int& ii)
    { cout << "here"<< endl;}
  virtual void set_index(imatrix&,int& ii);
};

/**
 * Description not yet available.
 * \param
 */
class local_init_df1b2vector : public local_init_var, public df1b2vector
{
  const df1b2vector * p;
public:
  int nvar_calc(void);
  local_init_df1b2vector(const df1b2vector & x);
  virtual void xinit(init_df1b2vector&,int& ii);
  virtual void xinit(dvector&,int& ii){ cout << "here"<< endl;}
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_value(const init_df1b2vector&,const int& ii);
  virtual void set_index(imatrix&,int& ii);
  virtual void dot_calcs(local_dep_df1b2variable&,int )
    { cout << "Here" << endl;}
};
// ************************************************************
// ************************************************************
// ************************************************************

/**
 * Description not yet available.
 * \param
 */
class local_dep_var
{
public:
  static df1b2variable * funnel_constraints_penalty;
  static void reset_counters(void) { num_vars=0; /*num_all_vars=0;*/}
  static int num_vars;
  //static int num_all_vars;
  static int num_inactive_vars;
  static int num_active_parameters;
  //static dep_df1b2vector * py;
  static imatrix * plist;
  int index;
  static   local_dep_var ** list;
  //static   local_dep_var ** all_list;
  static   local_dep_var ** inactive_list;
  local_dep_var(void) { add_to_list(); }
  void add_to_list(void);
  void delete_from_list(void);
  void add_to_inactive_list(void);
  virtual void allocate(void)=0;
  virtual void deallocate(void)=0;
  //virtual void xdep(void);
  //virtual void xinit(dep_df1b2vector&,int& ii)=0;
  //virtual void xdep(dvector&,int& ii)=0;
  //virtual void set_value(const dep_df1b2vector&,const int& ii,
   // const df1b2variable&)=0;
  //virtual void set_value(const dep_df1b2vector&,const int& ii)=0;
  virtual void set_index(imatrix&,int& ii)=0;
  virtual int nvar_calc(void)=0;

  //static void reset(dep_df1b2vector& x);

  static void deallocate_all(void);
  static void allocate_all(void);
  static int nvarcalc_all(void);
};

/**
 * Description not yet available.
 * \param
 */
class local_dep_df1b2variable : public local_dep_var, public df1b2variable
{
public:
  const df1b2variable * p;
  ~local_dep_df1b2variable();
  int type;
  void * pointer;
  const double * xdot;
  const double * pxdot;
  double xu;
  int ind_index;
  int nvar_calc(void){return 1;}
  //local_dep_df1b2variable(const df1b2_dep_number & x);
  local_dep_df1b2variable(const df1b2variable & x);
  local_dep_df1b2variable(void);
  local_dep_df1b2variable(double * xdot,double * pxdot);
  //local_dep_df1b2variable(const random_effects_bounded_vector_info&);
  local_dep_df1b2variable&  operator = (const df1b2variable&);
  virtual void allocate(void);
  virtual void deallocate(void);
  //virtual void allocate(const df1b2variable&);
  //virtual void preallocate(const df1b2variable&);
  //virtual void xdep(dep_df1b2vector&,int& ii);
  //virtual void xdep(dvector&,int& ii);
  //virtual void set_value(const dep_df1b2vector&,const int& ii);
  //virtual void set_value(const dep_df1b2vector&,const int& ii,
   // const df1b2variable&);
  virtual void set_index(imatrix&,int& ii);
};

/**
 * Description not yet available.
 * \param
 */
class local_dep_df1b2vector : public local_dep_var, public df1b2vector
{
  const df1b2vector * p;
public:
  int nvar_calc(void);
  local_dep_df1b2vector(const df1b2vector & x);
  //virtual void xdep(dep_df1b2vector&,int& ii);
  //virtual void xdep(dvector&,int& ii){ cout << "here"<< endl;}
  //virtual void set_value(const dep_df1b2vector&,const int& ii,
  //  const df1b2variable&);
  //virtual void set_value(const dep_df1b2vector&,const int& ii);
  virtual void set_index(imatrix&,int& ii);
};


df1b2variable plocal_tester(int i,const df1b2variable& x,
  const df1b2variable& y);
df1b2variable local_tester(int i,local_init_df1b2variable x,
  local_init_df1b2variable y);

/**
 * Description not yet available.
 * \param
 */
class local_init_pass1_var
{
public:
  static void reset_counters(void) { num_vars=0; /*num_all_vars=0;*/}
  static void end_local_calculations(void);
  static int num_vars;
  static int num_active_parameters;
  static   local_init_pass1_var ** list;
  local_init_pass1_var(void) { add_to_list(); }
  void add_to_list(void);
  virtual void allocate(void)=0;
  static void dot_calcs_all(local_dep_df1b2variable&);
  virtual void dot_calcs(local_dep_df1b2variable&,int j)=0;
  virtual void set_dot(int)=0;
  static void set_dot_all(void);
  virtual int nvar_calc(void)=0;
  static void allocate_all(void);
  static int nvarcalc_all(void);
};

/**
 * Description not yet available.
 * \param
 */
class local_init_pass1_df1b2variable : public local_init_pass1_var,
  public df1b2variable
{
  double xu;
  double * xudot;
public:
  virtual void set_dot(int ii){*(get_u_dot()+ii)=1;ii++;}
  virtual void dot_calcs(local_dep_df1b2variable&,int j);
  void allocate(void);
  int nvar_calc(void){return 1;}
  local_init_pass1_df1b2variable(double _xu,double* _xudot);
};
#endif  //  #if !defined(__DF1B2FNL__)
