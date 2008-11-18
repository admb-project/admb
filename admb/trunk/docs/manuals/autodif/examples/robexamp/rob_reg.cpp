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
