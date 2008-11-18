
#include <fvar.hpp>

double fcomp(dvector& OBS_Y,dvector& OBS_Z,dvar_vector& x);

//dvariable robust_regression(dvector& obs, dvar_vector& pred,
//  const double& cutoff);


#ifdef __BCPLUSPLUS__
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  long _stack = 20000;
#endif
double alpha;
void main()
{
  ifstream infile("robust.dat"); // robust.dat contains the observed data
  if(!infile)  // Check for I/O error
  {
    cerr << "Error trying to open the file robust.dat\n";
    exit(1);
  }
  int nobs;  // nobs is the number of observations
  infile >> nobs; // read in the number of observations
  if(!infile)  // Check for I/O error
  {
    cerr << "Error reading number of observations from the file robust.dat\n";
    exit(1);
  }
  dvector Y(1,nobs);
  dvector Z(1,nobs);
  // The Data are in the file in the form one Y_i Z_i pair per line
  {  // Limit the scope of the matrix tmp
     dmatrix tmp(1,nobs,1,2);
     infile >> tmp; // Read the  Y_i Z_i pairs into tmp
     if(!infile)  // Check for I/O error
     {
       cerr << "Error reading data in from the file robust.dat\n";
       exit(1);
     }
     Z=extract_column(tmp,1);  // Put the first column of tmp into Z
     Y=extract_column(tmp,2);  // Put the second column of tmp into Y
  } // Now tmp goes out of scope
  infile.close();  // Close the input file
  double b=1.0; // This is the model parameter ... use 1.0 as initial value
  alpha=0.7; // alpha is not used in the first stage of the minimization
  double f;
  gradient_structure gs;
  {
    int nvar=1; // There is 1 parameter, b
    independent_variables x(1,nvar);
    dvector g(1,nvar);
    x[1]=b; // Put the model parameters in the x vector
    fmm fmc(nvar);
    fmc.iprint=1;
    fmc.crit=1.e-6;
    while (fmc.ireturn >=0)
    {
      fmc.fmin(f,x,g);
      if (fmc.ireturn > 0)
      {
        {
          f=fcomp(Y,Z,dvar_vector(x));
        }
        gradcalc(nvar,g);
      }
    }
    cout << " The estimate for b = " << x(1) << "\n";
  }
}

double fcomp(dvector& Y,dvector& Z,dvar_vector& x)
{
  dvariable b;
  b=x[1]; //Put the x vector into the model parameter
  dvar_vector PRED_Y=b*Z+b*b; //calculate the predicted response
  const double alpha=0.7;
  dvariable tmp =robust_regression(Y,PRED_Y,alpha);
  return(value(tmp));
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

