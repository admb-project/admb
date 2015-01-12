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
//file: reset.cpp
#include <fvar.hpp>
#include "mixture.h"

dvariable reset(ivector& control,dvar_vector& x,dvar_vector& p, dvar_vector& mu,
    dvar_vector& sd,dvector& mumin, dvector& mumax, dvector& sdmin,
    dvector& sdmax)
{
  dvariable zpen=0.;
  int ngroups=p.size();
  int ii=1;
  if (control(1)>0)  // control(1) determines whether the p's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      p(j)=boundp(x(ii++),0.,1.,zpen);
    }
  }
  if (control(2)>0)  // control(2) determines whether the mu's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      mu(j)=boundp(x(ii++),mumin(j),mumax(j),zpen);
    }
  }
  if (control(3)>0)  // control(3) determines whether the sd's are active
  {
    for (int j=1;j<=ngroups;j++)
    {
      sd(j)=boundp(x(ii++),sdmin(j),sdmax(j),zpen);
    }
  }
  return(zpen); // Return zpen so it can be added to the function being
 		// minimized
}

