#include "fvar.hpp"

fvariable robust_reg_likelihood(dvector obs, fvar_array pred, fvariable a,
  fvariable& sigma, double pcon = 0.95, double width = 3.0 )
{
 // cout <<"In rob_reg a= "<<a<<"\n";

  if (obs.indexmin() != pred.indexmin() || obs.indexmax() != pred.indexmax() )
  {
    cerr << "Index limits on observed vector are not equal to the Index\n\
 limits on the predicted vector in robust_reg_likelihood function\n";
  }

  //cout <<"Log obs \n"<<obs<<"\n";
  //cout <<"Log pred \n"<<pred<<"\n";

  int min=obs.indexmin();

  int max=obs.indexmax();  

  int nobs = max-min+1;

  fvariable tmp,sum_square,v_hat;

  fvar_array diff_vec(min,max);

  diff_vec = obs-pred;
  //cout <<"diff_vec \n"<<diff_vec<<"\n";

  tmp = norm(diff_vec);

  sum_square = tmp * tmp;

  v_hat = sum_square/nobs;

  double width2=width*width; 

  double b=(1.-pcon)/width;

  fvariable log_likelihood;

  fvariable div1;

  fvariable div2;

  div1 = 2*a*v_hat;

  div2 = 2*width2*v_hat;

  log_likelihood = 0;

  for (int i=min; i<=max; i++)
  {
    tmp=diff_vec[i];
    tmp=tmp*tmp;
    // log_likelihood += log(pcon*(exp(-diff[i]*diff[i]/(2*a*v_hat))   
    //           b*(exp(-diff[i]*diff[i]/(width2*2*a*v_hat)) );
   
    log_likelihood -= log( pcon*exp(-tmp/div1)+b*exp(-tmp/div2) );
  }

  log_likelihood += nobs*log(a*v_hat)/2.;

  sigma=pow(a*v_hat,.5);

  return(log_likelihood);  

}
