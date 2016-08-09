DATA_SECTION
  init_int n
  init_matrix test(1,n,1,4)
  !! for(int i=1; i<=n; ++i)cout<<setprecision(22)<<test(i,1)<<"\t"<<test(i,2)<<"\t"<<test(i,3)<<"\t"<<test(i,4)
  !!                          <<"\t"<<qbeta(test(i,1),test(i,2),test(i,3))<<"\t"<<old_inv_cumd_beta_stable(test(i,2),test(i,3),test(i,1))
  !!                          <<"\t"<<test(i,4)-old_inv_cumd_beta_stable(test(i,2),test(i,3),test(i,1))
  !!                          <<"\t"<<test(i,4)-qbeta(test(i,1),test(i,2),test(i,3))<<endl;
  !! ad_exit(0);

PARAMETER_SECTION
  init_number dummy
  objective_function_value nll

PROCEDURE_SECTION
  nll=square(dummy);
