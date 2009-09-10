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

#include <fvar.hpp>
dvariable robust_regression(dvector& obs, dvar_vector& pred, dvariable& a)
{
  if (obs.indexmin() != pred.indexmin() || obs.indexmax() != pred.indexmax() )
  {
    cerr << "Index limits on observed vector are not equal to the Index\n\
 limits on the predicted vector in robust_reg_likelihood function\n";
  }
  RETURN_ARRAYS_INCREMENT(); //Need this statement because the function
			     //returns a variable type
  dvariable v_hat;
  double width=3.0;
  double pcon=0.05;
  double width2=width*width;
  dvariable a2;
  a2=a*a;
  dvar_vector diff = obs-pred;     // These are the residuals
  dvar_vector diff2 = pow(diff,2); // These are the squared residuals
  v_hat = mean(diff2)+1.e-80;
  double b=2.*pcon/(width*sqrt(3.14159));  // This is the weight for the 
                                           // "robustifying" term
  // Use vector calculations to do the entire log-likelihood function in
  // two statements 
  dvariable log_likelihood = -sum(log((1.-pcon)*exp(-diff2/(a2*v_hat))
    + b/(1.+pow(diff2/(width2*a2*v_hat),2))));
  log_likelihood += 0.5*diff.size()*log(a2*v_hat);
  RETURN_ARRAYS_DECREMENT(); // Need this to decrement the stack increment
                             // caused by RETURN_ARRAYS_INCREMENT();
  return(log_likelihood);  
}
