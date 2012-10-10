
// ---------------------------------------------------------------------
// Latent 2D Gaussian Markov Random Field with Poisson observations.
// Assume known mean=0 and variance=1.

// Q1: Precision matrix of stationary AR(1) process with parameter phi1.
// Q2: Precision matrix of stationary AR(1) process with parameter phi2.
// Q:  The kronecker product Q=Q1xQ2 (Full precision matrix of 2D field)
// n:  The dimension of Q1 and Q2
// N:  The observation vector of n*n counts

// Storage of Q1 and Q2 (triplet storage):
// Nonzero entries of e.g. Q1 are (Qi,Qj).
// Matrix only takes three different values: (-phi1, 1, 1+phi1^2)
// Which of the three values to insert in (Qi,Qj) is given by Qx
// ---------------------------------------------------------------------


DATA_SECTION
  init_int n                    // Dimension of Q1 and Q2
  init_int nnz			// Number of non-zeros of Q1 and Q2
  init_ivector Qi(0,nnz-1)      // Pattern of Q1 and Q2 in triplet storage
  init_ivector Qj(0,nnz-1)
  init_ivector Qx(0,nnz-1)
  init_ivector N(0,n*n-1)

PARAMETER_SECTION
  init_bounded_number phi1(0.001,0.999)
  init_bounded_number phi2(0.001,0.999)
  random_effects_vector eta(0,n*n-1)
  objective_function_value val

PROCEDURE_SECTION
  int i;
  #define MYPRINT(x)
  //#define MYPRINT(x)std::cout << #x << "=" << x << "\n";

  val=0;
  for(i=0;i<nnz;i++){   // Loop through non-zeros of Q1
    for(int j=0;j<nnz;j++){ // Loop through non-zeros of Q2
      quad_form(i,j,phi1,phi2,eta[Qrow(i,j)],eta[Qcol(i,j)]);
    }
  }

  // log-determinant of Kronecker product:
  // logdet(Q1xQ2)=n*logdet(Q1)+n*logdet(Q2)
  logdetQ_contrib(phi1);
  logdetQ_contrib(phi2);

  for(i=0;i<n*n;i++){   // Loop through data-entries
    pois_loglik(i,eta[i]); 
  }

// Three different nonzero values in stationary AR(1) precision
// FUNCTION void setparms(dvar_vector& Qx, const dvariable &phi)
//   dvariable kappa=1/(1-phi*phi);
//   Qx[1]=-phi; Qx[2]=1; Qx[3]=1+phi*phi;
//   Qx=kappa*Qx; // Now the inverse of Q1 and Q2 is a correlation matrix 

// Given i'th nonzero of Q1 and j'th nonzero of Q2
// Return the row and column index of Q and the corresponding value of Q.
FUNCTION int Qrow(int i, int j)
  return Qi[i]*n+Qi[j];
FUNCTION int Qcol(int i, int j)
  return Qj[i]*n+Qj[j];

// Add contribution of quadratic form corresponding to i'th nonzero
// of Q1 and j'th nonzero of Q2
SEPARABLE_FUNCTION void quad_form(int i,int j,const dvariable& phi1, const dvariable& phi2, const dvariable& etai, const dvariable& etaj)
  dvar_vector Q1x(1,3);
  dvar_vector Q2x(1,3);
  
  //setparms(Q1x,phi1);  <--- Not work within SEPARABLE_FUNCTION
  dvariable ph12=square(phi1);
  //dvariable kappa1=1/(1-phi1*phi1);
  dvariable kappa1=1/(1-ph12);
  Q1x[1]=-phi1; Q1x[2]=1; Q1x[3]=1+ph12;
  Q1x*=kappa1; // Now the inverse of Q1 and Q2 is a correlation matrix 

  //setparms(Q2x,phi2);  <--- Not work within SEPARABLE_FUNCTION
  dvariable ph22=square(phi2);
  dvariable kappa2=1/(1-ph22);
  Q2x[1]=-phi2; Q2x[2]=1; Q2x[3]=1+ph22;
  Q2x*=kappa2; // Now the inverse of Q1 and Q2 is a correlation matrix 

  dvariable Qij=Q1x[Qx[i]]*Q2x[Qx[j]];
  val += .5*etai*Qij*etaj;

// Add contribution from logdet(Q1) and logdet(Q2)
SEPARABLE_FUNCTION void logdetQ_contrib(const dvariable& phi)
  dvariable kappa=1/(1-phi*phi);
  dvariable logdet=log(1-phi*phi);
  logdet+=n*log(kappa);
  val -= .5*n*logdet;
  
// Add Poisson contribution
SEPARABLE_FUNCTION void pois_loglik(int i, const dvariable &etai)
  val += exp(etai)-N(i)*etai;

TOP_OF_MAIN_SECTION
  arrmblsize=40000000;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(2000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(100000000);
  gradient_structure::set_MAX_NVAR_OFFSET(2000000);
