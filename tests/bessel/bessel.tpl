DATA_SECTION
  init_int n
  init_matrix test(1,n,1,6)
  !! double reI=0, reK=0, reJ=0, reY=0; 
  !! for(int i=1; i<=n; ++i){
  !!   reI+=fabs(besselI(test(i,1),test(i,2))-test(i,3))/fabs(test(i,3));
  !!   reK+=fabs(besselK(test(i,1),test(i,2))-test(i,4))/fabs(test(i,4));
  !!   reJ+=fabs(besselJ(test(i,1),test(i,2))-test(i,5))/fabs(test(i,5));
  !!   reY+=fabs(besselY(test(i,1),test(i,2))-test(i,6))/fabs(test(i,6));
  !! }
  !! cout<<setprecision(22)<<"ave.rel.err-I "<<(reI/n)<<endl;
  !! cout<<setprecision(22)<<"ave.rel.err-K "<<(reK/n)<<endl;
  !! cout<<setprecision(22)<<"ave.rel.err-J "<<(reJ/n)<<endl;
  !! cout<<setprecision(22)<<"ave.rel.err-Y "<<(reY/n)<<endl;
  !! ad_exit(0);

PARAMETER_SECTION
  init_number dummy
  objective_function_value nll


PROCEDURE_SECTION
  nll=square(dummy);
