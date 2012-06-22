// This is used to test the following functions:
// 
// dvariable inv_cumd_beta_stable(const prevariable& _a,const prevariable& _b,
//   const prevariable& _y,double eps)

DATA_SECTION
  number a
  number b
  number x
  !! a=.1;
  !! b=.6;
  !! x=.9;
PARAMETER_SECTION
  init_bounded_number va(.01,.99)
  init_bounded_number vb(.01,.99)
  init_bounded_number vx(.01,.99)
  !! va=a;
  !! vb=b;
  !! vx=x;
  objective_function_value f
PROCEDURE_SECTION
 f=square(inv_cumd_beta_stable(va,vb,vx,.1)-0.4);
