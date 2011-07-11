\begin{lstlisting}
// file: newreg2.cpp

#include <fvar.hpp>

dvariable robust_regression(dvector& obs, 
                        dvar_vector& pred, dvariable& a)
{
  if (obs.indexmin() != pred.indexmin() 
      || obs.indexmax() != pred.indexmax())
  {
    cerr << "Index limits on observed vector 
      << "are not equal to the Index\n 
      << "limits on the predicted vector in 
      << "robust_reg_likelihood function\n";
  }
  RETURN_ARRAYS_INCREMENT(); //Need this statement because the function
  //returns a variable type
  dvariable v_hat;
  double width=3.0;
  double pcon=0.05;
  double width2=width*width;
  dvariable a2;
  a2=a*a;
  dvar_vector diff = obs-pred; // These are the residuals
  dvar_vector diff2 = pow(diff,2); // These are the squared residuals
  v_hat = mean(diff2)+1.e-80;
  double b=2.*pcon/(width*sqrt(PI)); // This is the weight for the
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
\end{lstlisting}
