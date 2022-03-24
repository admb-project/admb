// Space time
#include <TMB.hpp>
template<class Type>
Type objective_function<Type>::operator() ()
{
  // Data
  DATA_VECTOR( y_i );

  // Parameters
  PARAMETER( ln_mu );
  PARAMETER( ln_phi );
  PARAMETER( power_prime );

  // Objective function
  Type mu = exp(ln_mu);
  Type phi = exp(ln_phi);
  Type power = 1.0 + invlogit(power_prime);

  Type jnll = 0;
  int n_data = y_i.size();

  // Probability of data conditional on fixed effect values
  for( int i=0; i<n_data; i++){
    jnll -= dtweedie( y_i(i), mu, phi, power, true );
  }
  
  // Reporting
  return jnll;
}
