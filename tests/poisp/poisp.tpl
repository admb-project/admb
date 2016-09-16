GLOBALS_SECTION
  #include<df1b2fun.h>

  template<class Type>
  struct L {
    typedef Type Scalar; // Required
    Type a;              // Parameters for integrand
    Type operator()(Type x){
      return a*(sin(x*M_PI)+1.0);
    }
  };
  INTEGRATE1(L,a);

DATA_SECTION
  init_int N;
  init_vector X(1,N);
  
PARAMETER_SECTION
  init_number logS
  sdreport_number S;
  objective_function_value obj

PROCEDURE_SECTION
  S=exp(logS);
  L<dvariable> l; l.a=S;
  obj=0.0;
  for(int i=1; i<=N;++i){
    obj -= log(l(X(i)));
  }
  obj+=integrateL(0.,10.,S);

