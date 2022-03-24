DATA_SECTION
  init_int n_data
  init_vector y_i(0,n_data-1)
PARAMETER_SECTION
  init_number ln_mu
  init_number ln_phi
  init_number power_prime
  objective_function_value jnll
PROCEDURE_SECTION
  dvariable mu = exp(ln_mu);
  dvariable phi = exp(ln_phi);
  dvariable power = 1.0 + invlogit(power_prime);

  jnll = 0;

  // Probability of data conditional on fixed effect values
  for( int i=0; i<n_data; i++){
    jnll -= dtweedie( y_i(i), mu, phi, power, true );
  }

GLOBALS_SECTION
  #include <fvar.hpp>
  dvariable dtweedie(double y, dvariable& mu, dvariable& phi, dvariable& p, int give_log);
