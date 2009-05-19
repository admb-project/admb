/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California
 * 
 * License:
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New BSD" license
 * 
 * Copyright (c)  2008 Regents of the University of California.
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



#if defined(__BORLANDC__ )
#  pragma interface
#endif

// file fvar.hpp
#ifndef FMMT_HPP
#define FMMT_HPP

/*
class fmm_control
{
public:
  long   maxfn;
  long   iprint;
  double crit;
  long   imax;
  double dfn;
  long   ifn;
  long   iexit;
  long   ialph;
  long   ihflag;
  long   ihang;
  long   scroll_flag;
  int maxfn_flag;
  int quit_flag;
  double min_improve;
  int    ireturn;

  void set_defaults();
  fmm_control();
  fmm_control(BOR_CONST fmm_control& );
#ifdef HOME_VERSION
#include "insx014.h"
#endif
  void writeon(BOR_CONST ostream& s) const;
};
*/

class fmmt : public fmm_control
{
private:
  dvector w;
  dvector funval;
  int m;
  int diagco;
public:
  double dmin,fbest,df;
  double gmax;
  dvector gbest;
  dvector xbest;
  dvector diag;
  double eps;
  double xtol;
  double gtol;
  int nvar;
  long int iter;
  int ireturn1;
  int curriter;
  ivector iprint1;

public:
  double minimize(BOR_CONST independent_variables & x,double (*pf)(_CONST dvar_vector&));
  fmmt(int _nvar,int _m=7);

  double minimize(BOR_CONST independent_variables & x,BOR_CONST dvector& c,
        double (*pf)(BOR_CONST dvar_vector&,BOR_CONST dvector&) );

  void fmin(BOR_CONST double& f, BOR_CONST independent_variables & x,BOR_CONST dvector& g);

  dmatrix& hessian();
};

#endif //#ifndef FMMT_HPP


