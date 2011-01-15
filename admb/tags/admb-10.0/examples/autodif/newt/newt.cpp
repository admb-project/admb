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
//file: newt.cpp
#include <fvar.hpp>
//  function prototypes for user's functions
dvector function(dvar_vector& x,int nvar);
#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
int main()
{
  int nvar=2;
  independent_variables x(1,nvar);
  dvector f(1,nvar);
  dmatrix jacobian(1,nvar,1,nvar);
  gradient_structure gs;
  x[1]=1;
  x[2]=2;
  do      // Iterate until the norm of the dvector f is < 1.e-12
  {
    dvar_vector x2 = (dvar_vector)x;
    f=function(x2,nvar);
    jacobcalc(nvar,jacobian); // calculate the derivatives for the
                         // dependent variables
    cout << " The x vector        = " << x << endl
         << " The function values = " << f << endl << endl;
    x-=inv(jacobian)*f; // This is the Newton-Raphson step
  }
  while (norm(f)>1.e-12);
    // print out some final statistics
    cout << " Final x vector values       = " << x << endl
         << " Final function values       = " << f << endl
         << " Final jacobian matrix value = " << jacobian(1) << endl
         << "                               " << jacobian(2) << endl;
    cout << " The angle between the rows of the jacobian = "
         << acos(jacobian(1)*jacobian(2)
              /(norm(jacobian(1))*norm(jacobian(2))))
              *180/3.14159 << " degrees" << endl;
    cout << " Final inverse jacobian matrix value = "
         << inv(jacobian)(1) << endl
         << "                                       "
         << inv(jacobian)(2) << endl;
  return 0;
}

dvector function(dvar_vector& x,int nvar)
{
  double offset=.0001;  // try changing offset a bit to see how
                       // unstable the roots are
  dvar_vector f(1,nvar);
  dvariable z,tmp;
  f[1] << 100*x[1]*x[1]+x[2]*x[2]-1.; // << sets the value of the first
                          //  dependent variable
  // now use the first dependent variable in calculation for the
  // second dependent variable
  f[2] << f[1]+offset-.01*pow(x(2)*x(2),2)+.0001*pow(x(1)*x(1),2);
  return value(f);
}
