
DATA_SECTION

PARAMETER_SECTION
  init_number x 
  random_effects_vector u(1,1)
  objective_function_value f
PROCEDURE_SECTION

  f=0.0;
  if (laplace_approximation_calculator::alternative_user_function_flag==2)
  {
    f+=square(u(1)-5.0);
  }
  else
  {
    f+=square(u(1)-2.0*x);   // maximizing value for u is at u=x
  }

TOP_OF_MAIN_SECTION
  laplace_approximation_calculator::alternative_user_function_flag=1;

