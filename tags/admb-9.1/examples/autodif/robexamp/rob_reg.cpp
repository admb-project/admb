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

dvariable robust_regression(dvector& obs, dvar_vector& pred, dvariable& cutoff) 
{
  if (obs.indexmin() != pred.indexmin() || obs.indexmax() != pred.indexmax() )
  {
    cerr << "Index limits on observed vector are not equal to the Index\n\
 limits on the predicted vector in robust_reg_likelihood function\n";
  }
  RETURN_ARRAYS_INCREMENT(); //Need this statement because the function
			     //returns a variable type
  int min=obs.indexmin();
  int max=obs.indexmax();
  dvariable sigma_hat;
  dvariable sigma_tilde; 
  int nobs = max-min+1;
  double width=3.0;
  double pcon=0.05;
  double width2=width*width;
  dvariable zpen;
  zpen=0.0;
  dvariable a,a2;
  a=cutoff; 
     // This bounds a between 0.05 and 1.75
  a2=a*a;
  dvariable tmp,tmp2,tmp4,sum_square,v_hat;
  dvar_vector diff_vec = obs-pred;
  tmp = norm(diff_vec);
  sum_square = tmp * tmp;
  v_hat = 1.e-80 + sum_square/nobs;
  sigma_hat=pow(v_hat,.5);
  sigma_tilde=a*sigma_hat;
  double b=2.*pcon/(width*sqrt(3.14159));
  dvariable log_likelihood;
  dvariable div1;
  dvariable div2,div4;
  div1 = 2*(a2*v_hat);
  div2 = width2*(a2*v_hat);
  div4 = div2*div2;
  log_likelihood = 0;
  for (int i=min; i<=max; i++)
  {
    tmp=diff_vec[i];
    tmp2=tmp*tmp;
    tmp4=tmp2*tmp2;
    log_likelihood -= log((1-pcon)*exp(-tmp2/div1)+b/(1.+tmp4/div4) );
  }
  log_likelihood += nobs*log(a2*v_hat)/2.;
  log_likelihood += zpen;
  RETURN_ARRAYS_DECREMENT(); // Need this to decrement the stack increment
			     // caused by RETURN_ARRAYS_INCREMENT();
  return(log_likelihood);  
}

dvariable robust_regression(dvector& obs, dvar_vector& pred, 
  const double& cutoff) 
{
  if (obs.indexmin() != pred.indexmin() || obs.indexmax() != pred.indexmax() )
  {
    cerr << "Index limits on observed vector are not equal to the Index\n\
 limits on the predicted vector in robust_reg_likelihood function\n";
  }
  RETURN_ARRAYS_INCREMENT(); //Need this statement because the function
			     //returns a variable type
  int min=obs.indexmin();
  int max=obs.indexmax();
  dvariable sigma_hat;
  dvariable sigma_tilde; 
  int nobs = max-min+1;
  double width=3.0;
  double pcon=0.05;
  double width2=width*width;
  dvariable zpen;
  zpen=0.0;
  double a,a2;
  a=cutoff; 
     // This bounds a between 0.05 and 1.75
  a2=a*a;
  dvariable tmp,tmp2,tmp4,sum_square,v_hat;
  dvar_vector diff_vec = obs-pred;
  tmp = norm(diff_vec);
  sum_square = tmp * tmp;
  v_hat = 1.e-80 + sum_square/nobs;
  sigma_hat=pow(v_hat,.5);
  sigma_tilde=a*sigma_hat;
  double b=2.*pcon/(width*sqrt(3.14159));
  dvariable log_likelihood;
  dvariable div1;
  dvariable div2,div4;
  div1 = 2*(a2*v_hat);
  div2 = width2*(a2*v_hat);
  div4 = div2*div2;
  log_likelihood = 0;
  for (int i=min; i<=max; i++)
  {
    tmp=diff_vec[i];
    tmp2=tmp*tmp;
    tmp4=tmp2*tmp2;
    log_likelihood -= log((1-pcon)*exp(-tmp2/div1)+b/(1.+tmp4/div4) );
  }
  log_likelihood += nobs*log(a2*v_hat)/2.;
  log_likelihood += zpen;
  RETURN_ARRAYS_DECREMENT(); // Need this to decrement the stack increment
			     // caused by RETURN_ARRAYS_INCREMENT();
  return(log_likelihood);  
}
