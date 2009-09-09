/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

dvariable robust_regression(_CONST dvector& obs,_CONST dvar_vector& pred,_CONST dvariable& a)
{
  if (obs.indexmin() != pred.indexmin() || obs.indexmax() != pred.indexmax() )
  {
    cerr << "Index limits on observed vector are not equal to the Index\n"
      "limits on the predicted vector in robust_reg_likelihood function\n";
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
  v_hat = mean(diff2)+1.e-80; // add 1.e-80 so that a perfect fit wont't
			      // produce log(0).
  double b=2.*pcon/(width*sqrt(3.14159));  // This is the weight for the
					   // "robustifying" term
  dvariable log_likelihood = -sum(log((1.-pcon)*exp(-diff2/(2.*a2*v_hat))
    + b/(1.+pow(diff2/(width2*a2*v_hat),2))));
  log_likelihood += 0.5*diff.size()*log(a2*v_hat);
  RETURN_ARRAYS_DECREMENT(); // Need this to decrement the stack increment
			     // caused by RETURN_ARRAYS_INCREMENT();
  return(log_likelihood);
}


dvariable robust_regression(_CONST dvector& obs,_CONST dvar_vector& pred, 
  CGNU_DOUBLE a)
{
  if (obs.indexmin() != pred.indexmin() || obs.indexmax() != pred.indexmax() )
  {
    cerr << "Index limits on observed vector are not equal to the Index\n"
      "limits on the predicted vector in robust_reg_likelihood function\n";
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
  dvar_vector diff2 = square(diff); // These are the squared residuals
  v_hat = mean(diff2)+1.e-80; // add 1.e-80 so that a perfect fit wont't
			      // produce log(0).
  double b=2.*pcon/(width*sqrt(3.14159));  // This is the weight for the
					   // "robustifying" term
  dvariable log_likelihood = -sum(log((1.-pcon)*exp(-diff2/(2.*a2*v_hat))
    + b/(1.+pow(diff2/(a2*v_hat),2))));
  log_likelihood += 0.5*diff.size()*log(a2*v_hat);
  RETURN_ARRAYS_DECREMENT(); // Need this to decrement the stack increment
			     // caused by RETURN_ARRAYS_INCREMENT();
  return(log_likelihood);
}


