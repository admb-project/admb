main()
{
  ifstream infile("robust.dat"); robust.dat contains the observed data
  if(!infile)  // Check for I/O error
  {
    cerr << "Error trying to open the file robust.dat\n";
    exit(1);
  }
  int nobs  // nobs is the number of observations
  infile >> nobs; // read in the number of observations
  if(!infile)  // Check for I/O error
  {
    cerr << "Error reading number of observations from the file robust.dat\n";
    exit(1);
  }
  dvector Y(1,nobs);
  dvector z(1,nobs);
  // The Data are in the file in the form one Y_i z_i pair per line 
  {  // Limit the scope of the matrix tmp
     dmatrix tmp(1,nobs,1,2);
     infile >> tmp; // Read the  Y_i z_i pairs into tmp
     if(!infile)  // Check for I/O error
     {
       cerr << "Error reading data in from the file robust.dat\n";
       exit(1);
     }
     Y=col_extract(tmp,1);  // Put the first column of tmp into Y 
     z=col_extract(tmp,2);  // Put the second column of tmp into z 
  } // Now tmp goes out of scope
  infile.close();  // Close the input file
  double a,b,cutoff; // These are the model parameters
  b=0;  // Initialize the model parameters
  c=0;
  cutoff=0.0; // cutoff is not used in the first stage of the minimization
  gradient_structure gs;
  {
    nvar=2; // There are 2 parameters a and b
    independent_variables x(1,nvar);
    x[1]=b; // Put the model parameters in the x vector
    x[2]=c;
    fmm fmc(nvar);
    while (fmc.ireturn >=0)
    {
      fmc.fmin(f,x,g);
      if (fmc.ireturn > 0)
      {
        {
          fcomp1(f,OBS_Y,OBS_Z,x);
        }
        gradcalc(nvar,g);
      }
    }
    b=x[1]; // Save the estimates for a and b for the next stage
    c=x[2]; // of the minimization
  }

  {
    nvar=3; // There are 3 parameters a and b and cutoff
    independent_variables x(1,nvar);
    x[1]=b; // Put the model parameters in the x vector
    x[2]=c;
    x[3]=cutoff; // Now estimate cutoff. An initial value of 0.0 for
                 // cutoff produces an initial value of 0.9 for the
                 // quantity a in robust_regression
    dvariable sigma_hat,sigma_tilde;
    fmm fmc(nvar);
    while (fmc.ireturn >=0)
    {
      fmc.fmin(f,x,g);
      if (fmc.ireturn > 0)
      {
        {
          fcomp2(f,OBS_Y,OBS_Z,x,sigma_hat,sigma_tilde); // We want the
             // estimates for the standard deviation as well
        }
        gradcalc(nvar,g);
      }
      // Print out the estimates on the screen
      cout << " b = " << x[1] << "  c = " << x[2] << "\n"
        << " sigma_hat = " << sigma_hat
        << "  sigma_tilde = " << sigma_tilde
        << " a (in robust_regression) = " << sigma_tilde/sigma_hat << "\n";
    }
}


 dvariable fcomp1(double& f,dvector& OBS_Y,dvector& OBS_Z,dvar_vector& x)
 {
   dvariable b,c;
   dvariable sigma_hat,sigma_tilde;
   b=x[1]; //Put the x vector into the model parameters
   c=x[2];
   PRED_Y=b*OBS_Z+b*b+c; //calculate the predicted response
   dvariable tmp =robust_regression(OBS_Y,PRED_Y,sigma_hat,sigma_tilde); 
   f=value(tmp);
 } 

 dvariable fcomp2(double& f,dvector& OBS_Y,dvector& OBS_Z,dvar_vector& x,
   dvariable& sigma_hat, dvariable& sigma_tilde)
 {
   dvariable b,c,cutoff;
   dvariable sigma_hat,sigma_tilde;
   b=x[1]; //Put the x vector into the model parameters
   c=x[2];
   cutoff=x[3];
   PRED_Y=b*OBS_Zb*b+c; //calculate the predicted response
   dvariable tmp=robust_regression(OBS_Y,PRED_Y,sigma_hat,sigma_tilde,cutoff); 
   f=value(tmp);
 } 

#include <fvar.hpp>
dvariable robust_reg_likelihood(dvector& obs, dvar_vector& pred,
  dvariable& sigma_hat, dvariable& sigma_tilde,dvariable& cutoff) 
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
  int nobs = max-min+1;
  double width=3.0;
  double pcon=0.05;
  double width2=width*width;
  dvariable zpen;
  zpen=0.0;
  dvariable a,a2;
  a=boundp(cutoff,.05,1.75,zpen); // If cutoff=0.0 then a=0.9
     // This bounds a between 0.05 and 1.75
  a2=a*a;
  dvariable tmp,tmp2,tmp4,sum_square,v_hat;
  dvar_vector diff_vec = obs-pred;
  tmp = norm(diff_vec);
  sum_square = tmp * tmp;
  v_hat = 1.e-80 + sum_square/nobs; // Add 1.e-80 to avoid zero divide
  sigma_hat=pow(v_hat,.5);
  sigma_tilde=a*sigma_hat;
  double b=(pcon*2)/(width*sqrt(3.14159));
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
