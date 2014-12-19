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

/**
  \file simple2.cpp
   simple example without macros from the AUTODIF manual.
   Does not use the BEGIN_MINIMIZIATION and 
   END_MINIMIZATION macros.
   Example from the AUTODIF manual,  p 1-8
   Updated to get rid of some warnings.
*/

//file: simple2.cpp

#include <math.h>
#include <fvar.hpp>

double fcomp(int, dvar_vector); // Function prototype declaration

int main()
{
   const int nvar=20; // This is the number of independent variables
   independent_variables x(1,nvar); // these are the independent variables
   double f; // This is the dependent variable
   dvector g(1,nvar); // Holds the vector of partial derivatives (gradient)
   fmm fmc(nvar); // Create structure to manage minimization
   //--- Expansion of BEGIN_MINIMIZATION(nvar,x,f,g,fmc) macro
   gradient_structure gs;
   while (fmc.ireturn >= 0) // Begin loop for minimization
   {
      fmc.fmin(f,x,g);      // Calls the minimization routine
      if (fmc.ireturn > 0)  // Loop for evaluating the function and
      {                    // derivatives
   //--- End of the Expansion of BEGIN_MINIMIZATION macro
         f=fcomp(nvar,x);
   //--- Expansion of END_MINIMIZATION(nvar,g) macro
         gradcalc(nvar,g);
      }
   }
   //--- End of the Expansion of END_MINIMIZATION macro
   cout << " The minimizing values are\n" << x << "\n"; // Print out answer
}
