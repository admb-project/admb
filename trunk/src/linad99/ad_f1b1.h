/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
 * 
 * License:
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
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
#if !defined(__AD_F1B1__)
# define __AD_F1B1__

#include <fvar.hpp>

  class f1b1_variable;

/**
 * Description not yet available.
 * \param
 */
  class f1b1_variable
  {
  public:
    static  double * f1b1_stack_ptr;
    static  double * zeroes;
    static int _nvar;
    static int nbytes;
    double *      u;
    double *      udot;      // tangent vector for u
    double *      uhat;      // adjoint vector for u
    double *      uhatdot;   // adjoint vector for udot

    f1b1_variable();
    static void setnvar(int n);
    static int nvar(void) { return _nvar;}
    static void getzeroes(void);
    void initialize(); 
  };

/**
 * Description not yet available.
 * \param
 */
  class f1b1_stack
  {
  public:
    double * ptr;
    f1b1_stack(int n) { ptr = new double[n]; }
    ~f1b1_stack() { delete ptr; ptr=NULL; deassign();}
    void assign(void) { f1b1_variable::f1b1_stack_ptr=ptr;}
    void deassign(void) { f1b1_variable::f1b1_stack_ptr=NULL;}
  };

/**
 * Description not yet available.
 * \param
 */
  class f1b1_init_data : public f1b1_variable 
  {
  public:
    f1b1_init_data();
    void kludge(double x,int i){*u=x;udot[i]=1;}
  };

/**
 * Description not yet available.
 * \param
 */
  class dep_data
  {
  public:
    f1b1_variable * dep;
    dep_data(f1b1_variable * t) { dep=t;}
  };

  class single_f1b1_function;
  class double_f1b1_function;
  class virtual_double_f1b1_function;

/**
 * Description not yet available.
 * \param
 */
  class virtual_f1b1_node
  {
  public: 
    virtual f1b1_variable * get_dep(void) =0;
  };
  
/**
 * Description not yet available.
 * \param
 */
  class single_f1b1_node : public virtual_f1b1_node
  {
  public:
    f1b1_variable * dep;
    f1b1_variable * ind1;
    single_f1b1_function * f;
    single_f1b1_node(f1b1_variable * _dep, f1b1_variable * _ind1, 
      single_f1b1_function * _f) : dep(_dep) , ind1(_ind1), f(_f) {}
    virtual f1b1_variable * get_dep(void){return dep;}
  };
    
/**
 * Description not yet available.
 * \param
 */
  class double_f1b1_node : virtual_f1b1_node
  {
  public:
    f1b1_variable * dep;
    f1b1_variable * ind1;
    f1b1_variable * ind2;
    virtual_double_f1b1_function * f;
    virtual f1b1_variable * get_dep(void){return dep;}
    double_f1b1_node(f1b1_variable * _dep, f1b1_variable * _ind1,
      f1b1_variable * _ind2,virtual_double_f1b1_function * _f) : dep(_dep), 
      ind1(_ind1), ind2(_ind2), f(_f) {}
  };
    
/**
 * Description not yet available.
 * \param
 */
  class single_f1b1_function
  {
  public:
    double (*f)(double);
    double (*d1f)(double);
    double (*d11f)(double);
    single_f1b1_function( double  (*_f)(double), double  (*_d1f)(double),
      double  (*_d11f)(double));
    single_f1b1_node operator () (virtual_f1b1_node& v);
    single_f1b1_node single_f1b1_function::operator () 
      (f1b1_init_data& v);
  };

  typedef double (*D2f1b1)(double,double);

/**
 * Description not yet available.
 * \param
 */
  class virtual_double_f1b1_function
  {
  public:
  //  virtual double_f1b1_node operator () 
  //    (virtual_f1b1_node& v, virtual_f1b1_node& w)=0;
  //  virtual double_f1b1_node operator () 
  //    (f1b1_init_data& v,f1b1_init_data& w)=0;
    virtual void node_evaluate(void)=0;
  };

/**
 * Description not yet available.
 * \param
 */
  class double_f1b1_function : public virtual_double_f1b1_function
  {
  public:
    double (*f)(double,double);
    double (*d1f)(double,double);
    double (*d2f)(double,double);
    double (*d11f)(double,double);
    double (*d12f)(double,double);
    double (*d22f)(double,double);
    double_f1b1_function( D2f1b1  _f, D2f1b1  _d1f, D2f1b1  _d2f, 
      D2f1b1  _d11f, D2f1b1  _d12f, D2f1b1  _d22f) : f(_f), d1f(_d1f),
      d2f(_d2f), d11f(_d11f), d12f(_d12f), d22f(_d22f) {}

    double_f1b1_node operator () (virtual_f1b1_node& v, 
      virtual_f1b1_node& w);
    double_f1b1_node operator () (f1b1_init_data& v,f1b1_init_data& w);
    void node_evaluate(void);
  };

/**
 * Description not yet available.
 * \param
 */
  class plus_function : public virtual_double_f1b1_function
  {
  public:
    //virtual double_f1b1_node operator () (virtual_f1b1_node& v, 
    //  virtual_f1b1_node& w);

    //virtual double_f1b1_node operator () (f1b1_init_data& v,f1b1_init_data& w);
    void node_evaluate(void);
  };

/**
 * Description not yet available.
 * \param
 */
  class times_function : public virtual_double_f1b1_function
  {
  public:
    //virtual double_f1b1_node operator () (virtual_f1b1_node& v, 
    //  virtual_f1b1_node& w);

    //virtual double_f1b1_node operator () (f1b1_init_data& v,f1b1_init_data& w);
    void node_evaluate(void);
  };

  extern plus_function  f1b1_plus;
  extern times_function  f1b1_times;

#endif
