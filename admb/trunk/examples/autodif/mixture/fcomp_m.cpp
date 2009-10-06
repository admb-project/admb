/**
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
// file fcomp_m.cpp
#include <fvar.hpp>
#include "mixture.h"

double fcomp(dvector y,dvar_vector p,dvar_vector& mu,dvar_vector& sd,
  dvector& mumin, dvector& mumax, dvector& sdmin, dvector& sdmax,
  ivector& control,dvar_vector& x,int print_switch)
{
  dvariable zpen;
  zpen=reset(control,x,p,mu,sd,mumin,mumax,sdmin,sdmax); // Put the x vector
                                 // into the model parameters and return the 
                                 //bounding function penalty in zpen
  zpen+=normalize_p(p); // Make the proportions sum to 1
  if (print_switch == 1)
  {
    save_pars(p,mu,sd,mumin,mumax,sdmin,sdmax,control);
  }
  dvariable f;
  f=-log_likelihood(y,p,mu,sd); // Change the sign to minimize
  f=f+zpen; // Add the penalty from the ``bounding'' functions
  return(value(f));
}

