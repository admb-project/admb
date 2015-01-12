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
//file: simple.cpp
#include <fvar.hpp>

double fcomp(int, dvar_vector); // Function prototype declaration

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{
  int nvar=20; // This is the number of independent variables
  independent_variables x(1,nvar); // these are the independent variables
  double f;  // This is the dependent variable
  dvector g(1,nvar);  // Holds the vector of partial derivatives (the gradient)
  fmm fmc(nvar);      // Create structure to manage minimization
  BEGIN_MINIMIZATION(nvar,f,x,g,fmc) // Macro to set up beginning of
                                     // minimization loop
    f=fcomp(nvar,x);
  END_MINIMIZATION(nvar,g)    // Macro to set up end of minimization loop
  cout << " The minimizing values are\n" << x << "\n"; //Print out the answer
  return 0;
}
// file: fcomp_s.cpp
double fcomp(int n, dvar_vector x)
{
  dvariable z;
  dvariable tmp;
  int i;
  z=0;
  for (i=1;i<=n;i++)
  {
    tmp=x[i]-1;
    z=z+tmp*tmp;
  }
  return(value(z));
}
