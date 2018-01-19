// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int T
  init_vector r(0,T)
  vector sub_r(1,T)
  number h0
INITIALIZATION_SECTION
  a0 .1
  a1 .1
  a2 .1
PARAMETER_SECTION
  init_bounded_number a0(0.0,1.0)
  init_bounded_number a1(0.0,1.0,2)
  init_bounded_number a2(0.0,1.0,3)
  init_number Mean
  vector eps2(1,T)
  vector h(1,T)
  objective_function_value log_likelihood
PRELIMINARY_CALCS_SECTION
  h0=square(std_dev(r));   // square forms the element-wise square 
  sub_r=r(1,T);    // form a subvector so we can use vector operations
  Mean=mean(r);    // calculate the mean of the vector r 
PROCEDURE_SECTION
  eps2=square(sub_r-Mean);   
  h(1)=a0+a2*h0;
  for (int t=2;t<=T;t++)
  {
    h(t)=a0+a1*eps2(t-1)+a2*h(t-1);
  }
  // calculate minus the log-likelihood function and assign it to
  // the object of type objective_function_value
  log_likelihood=.5*sum(log(h)+elem_div(eps2,h));  // elem_div performs  
          // element-wise division of vectors
