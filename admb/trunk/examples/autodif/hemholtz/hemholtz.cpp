/**
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California
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

//file: hemholtz.cpp
#include <fvar.hpp>

void hemholtz_energy(int n, dmatrix A, dvector b, dvar_vector x, double& f);

#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{
  int n=30;
  double f;
  dvector g(1,n);                // this is the n dimensional gradient vector
  dvector b(1,n);                // define an n dimensional vector b
  dmatrix A(1,n,1,n);            // define an n by n matrix A
  independent_variables x(1,n);  // identify the independent variables
  // make up some values for the parameters
  // we don't know what reasonable values are, but it doesn't 
  // matter for illustration of the method
  for (int i=1; i<=n; i++)
  {
    b[i]=(n/2.-i)/(n*n);   // This could be done using the ``fill'' routines
    x[i]=(1.+i)/(n*n);
    for (int j=1; j<=n; j++)
    {
      A[i][j]=i*j;
    }
  }
  {
    gradient_structure gs;     // An object of type gradient structure must
                               // be declared
    hemholtz_energy(n,A,b,x,f);// calculate the Hemholtz energy
    gradcalc(n,g);             // The gradient (partial derivatives) is 
                               // calculated and put in the dvector g
    cout << "The gradient is:\n";
    cout << g << "\n";
  }
  return 0;
}
