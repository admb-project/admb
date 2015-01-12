DATA_SECTION
  init_int np
  init_int nh
  init_matrix data(1,np,1,4)
  ivector I(1,np)
  ivector nump(1,nh)
  vector S(1,np)
  vector TRT(1,np)
  vector CARD(1,np)
 LOC_CALCS
  I=ivector(column(data,1));
  S=column(data,2);
  TRT=column(data,3);
  CARD=column(data,4);
  int ic=1;
  for (int i=1;i<np;i++)
  {
    if (I(i+1)>I(i))
    {
      nump(I(i))=ic;
      ic=1;
    }
    else
    {
      ic++;
    }
  }
  nump(nh)=ic;
    

PARAMETER_SECTION
  init_vector beta(0,2);
  init_bounded_number log_theta1(-5.0,3.0,2)

  random_effects_vector u(1,nh,2)
  objective_function_value f

PROCEDURE_SECTION

  int i;
  int j=0;
  for (i=1;i<=nh;i++) 
  {
    fun(i,j,u(i),log_theta1,beta);
  }

SEPARABLE_FUNCTION void fun( int i,int & j ,const prevariable& ui, const prevariable& log_theta1, const dvar_vector& beta) 

 f += 0.9189385 + 0.5*square(ui);  // N(0,1) likelihood contribution from u's

 // Likelihood contribution
 dvariable theta1=exp(log_theta1);
 int ii;
 dvariable z=cumd_norm(ui);         // z has uniform (0,1) distribution
 z = 0.99999999*z + 0.000000005;      // To gain numerical stability
 dvariable gi = theta1*inv_cumd_gamma(z,1.0/theta1);
 for (ii=1;ii<=nump(i);ii++) 
 {
   j++;

   dvariable log_lambda=beta(0)+beta(1)*TRT(j)+beta(2)*CARD(j)+log(gi);
   dvariable lambda=mfexp(log_lambda);
   f += lambda*S(j) - log_lambda;
 }






