/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New BSD" license
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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
  class f1b1_data{
  {
  public:
    double        u;
    dvector       udot;      // tangent vector for u
    dvector       uhat;      // adjoint vector for u
    dvector       uhatdot;   // adjoint vector for udot

    f1b_data(int n) : udot(1,n), uhat(1,n), uhatdot(1,n) {}
    int nvar(void) {return udot.indexmax();}
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
    single_f1b1_node operator () (dep_data& v)
    {
      f1b1_data * dep=v->dep;
      f1b_data tmp(dep->nvar());
      tmp.u=f(dep->u);
      udot=d1f(dep->u)*dep->udot;
      single_f1b1_node node : ;
      node.ind=*v;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  class double_f1b1_function
  {
  public:
    double (*f)(double,double);
    double (*d1f)(double,double);
    double (*d2f)(double,double);
    double (*d12f)(double,double);
    double (*d22f)(double,double);
    double_f1b1_node operator () (dep_data& v,dep_data& w)
    {
      f1b1_data * dep1=v->dep;
      f1b1_data * dep2=w->dep;
      f1b1_data * = new f1b1_data(tmp(dep->nvar()));
      tmp.u=f(dep1->u,dep2->u);
      udot=d1f(dep1->u)*dep1->udot;
      udot+=d2f(dep1->u)*dep1->udot;
    }
    class single_f1b1_node : dep_data(f1b1_data);
  };

/**
 * Description not yet available.
 * \param
 */
  class dep_data
  {
  public:
    f1b1_data * dep;
    dep_data(f1b1_data * t) { dep=t;}
  };

/**
 * Description not yet available.
 * \param
 */
  class single_f1b1_node : public dep_data {
  {
  public:
    dep_data * ind1;
    single_f1b1_function * f;
  };

/**
 * Description not yet available.
 * \param
 */
  class double_f1b1_node : public dep_data {
  {
    dep_data * ind1;
    dep_data * ind2;
    double_f1b1_function * f;
  };
