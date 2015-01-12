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
// file: mixture.cpp
#include <fvar.hpp>

// header file containing all function prototypes used in this exmaple
#include "mixture.h"

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{
  // The observations are in the file mixture.dat
  dvector y("mixture.dat"); // Read in the observations
  ifstream infile2("mixture.par"); // The parameter estimates are in a
				   // file named mixture.par
  int ngroups;
  infile2 >> ngroups; // Read in the number of groups
  ivector control(1,10); // There are 10 control switches for this model
  infile2 >> control; // Read in the control switches
  dvector p(1,ngroups);
  dvector mu(1,ngroups);
  dvector sd(1,ngroups);
  dvector mumin(1,ngroups);
  dvector mumax(1,ngroups);
  dvector sdmin(1,ngroups);
  dvector sdmax(1,ngroups);
  infile2 >> p;  // Read in the mixture proportions
  infile2 >> mu; // Read in the mean lengths
  infile2 >> sd; // Read in the standard deviations
  infile2 >> mumin; // Read in the lower bounds on the mean lengths
  infile2 >> mumax; // Read in the upper bounds on the mean lengths
  infile2 >> sdmin; // Read in the lower bounds on the standard deviations
  infile2 >> sdmax; // Read in the upper bounds on the standard deviations
  infile2.close(); // close the file
  int nvar=nvarcal(control,ngroups); // Get the number of independent variables
  independent_variables x(1,nvar);
  double f;
  dvector g(1,nvar);
  xinit(control,x,p,mu,sd,mumin,mumax,sdmin,sdmax); // Get the initial x values
  fmm fmc(nvar);
  gradient_structure::set_MAX_NVAR_OFFSET(768);
  BEGIN_MINIMIZATION(nvar,f,x,g,fmc) // Estimate the parameters by minimizing fcomp
    dvar_vector x2 = x;
    dvar_vector mu2 = mu;
    dvar_vector sd2 = sd;
    f=fcomp(y,p,mu2,sd2,mumin,mumax,sdmin,sdmax,control,x2,0);
    fcomp(y,p,mu2,sd2,mumin,mumax,sdmin,sdmax,control,x2,1); // Save the parameter
                                                             // estimates
  END_MINIMIZATION(nvar,g)
  return 0;
}
