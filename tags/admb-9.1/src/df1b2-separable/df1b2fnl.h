/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
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


#include <df1b2fun.h>
#if !defined(__DF1B2FNL__)
#  define __DF1B2FNL__ 
#include <adrndeff.h>


class funnel_init_var
{
public:
  static laplace_approximation_calculator * lapprox;
  static df1b2variable * funnel_constraints_penalty;
  static void reset_counters(void) { num_vars=0; /*num_all_vars=0;*/}
  static int num_vars;
  //static int num_all_vars;
  static int num_inactive_vars;
  static int num_active_parameters;
  static init_df1b2vector * py;
  static imatrix * plist;
  int index;
  static   funnel_init_var ** list;
  //static   funnel_init_var ** all_list;
  static   funnel_init_var ** inactive_list;
  funnel_init_var(void) { /*add_to_list();*/ }
  void add_to_list(void);
  void delete_from_list(void);
  void add_to_inactive_list(void);
  virtual void allocate(void);
  //virtual void xinit(void);
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

class funnel_dependent_df1b2variable : public df1b2variable 
{
  int assign_flag;
public:
  double * get_u(void){ return df1b2variable::get_u();}
  void operator = (const df1b2variable&) 
  {
    cerr << "Cannot assign to funnel_dependent_df1b2variable" << endl;
    ad_exit(1);
  }
  funnel_dependent_df1b2variable(const df1b2variable&); 
  //virtual void allocate_all(init_df1b2vector&,int& ii);
};


class funnel_init_df1b2variable : public funnel_init_var, public df1b2variable 
{
public:
  int type;
  void * pointer;
  double xu;
  int ind_index;
  int nvar_calc(void){return 1;}
  funnel_init_df1b2variable(const df1b2_init_number & x); 
  funnel_init_df1b2variable(const funnel_init_df1b2variable& x); 
  funnel_init_df1b2variable(const df1b2variable & x); 
  funnel_init_df1b2variable(void); 
  funnel_init_df1b2variable(const random_effects_bounded_vector_info&); 
  virtual void allocate(void);
  virtual void allocate(const df1b2variable&);
  virtual void preallocate(const df1b2variable&);
  virtual void xinit(init_df1b2vector&,int& ii);
  virtual void xinit(dvector&,int& ii);
  virtual void set_value(const init_df1b2vector&,const int& ii);
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_index(imatrix&,int& ii);
};

  
class funnel_init_bounded_df1b2vector : public funnel_init_var, 
  public df1b2vector 
{
  const df1b2_init_bounded_vector * p;
public:
  int nvar_calc(void);
  funnel_init_bounded_df1b2vector(const df1b2_init_bounded_vector & x);
  virtual void xinit(init_df1b2vector&,int& ii);
  virtual void xinit(dvector&,int& ii){ cout << "here"<< endl;}
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_value(const init_df1b2vector&,const int& ii){ cout << "here"<< endl;}
  virtual void set_index(imatrix&,int& ii);
};



class funnel_init_df1b2vector : public funnel_init_var, public df1b2vector 
{
  const df1b2vector * p;
  //const df1b2_init_vector * p;
public:
  int nvar_calc(void);
  //funnel_init_df1b2vector(const df1b2_init_vector & x);
  funnel_init_df1b2vector(const df1b2vector & x);
  virtual void xinit(init_df1b2vector&,int& ii);
  virtual void xinit(dvector&,int& ii){ cout << "here"<< endl;}
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_value(const init_df1b2vector&,const int& ii){ cout << "here"<< endl;}
  virtual void set_index(imatrix&,int& ii);
  virtual void allocate(void);
};



class funnel_init_df1b2matrix : public funnel_init_var, public df1b2matrix 
{
  const df1b2matrix* p;
  //const df1b2_init_vector * p;
public:
  int nvar_calc(void);
  //funnel_init_df1b2vector(const df1b2_init_vector & x);
  funnel_init_df1b2matrix(const df1b2matrix & x);
  virtual void xinit(init_df1b2vector&,int& ii);
  virtual void xinit(dvector&,int& ii){ cout << "here"<< endl;}
  virtual void set_value(const init_df1b2vector&,const int& ii,
    const df1b2variable&);
  virtual void set_value(const init_df1b2vector&,const int& ii){ cout << "here"<< endl;}
  virtual void set_index(imatrix&,int& ii);
};



#endif  //  #if !defined(__DF1B2FNL__)
