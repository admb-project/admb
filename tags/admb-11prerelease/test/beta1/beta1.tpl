// This is used to test the following functions:
// 
// double betai(double _aa, double _bb, double _xx);
// dvariable betai(const dvariable& _a,const dvariable& _b,const dvariable& _x);

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
 f=square(betai(va,vb,vx)+betai(1.-a,1.-b,1.-x)-0.5);
