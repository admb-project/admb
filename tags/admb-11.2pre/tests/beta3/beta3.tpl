// This is used to test the following functions:
// 
// df1b2variable betai(const df1b2variable & _a, const df1b2variable & _b,
//		     const df1b2variable & _x)
//

DATA_SECTION
  number a
  number b
  number x
  !! a=.1;
  !! b=.6;
  !! x=.9;
PARAMETER_SECTION
  init_bounded_number va(.1,.9)
  init_bounded_number vb(.1,.9)
  init_bounded_number vx(.1,.9)
  random_effects_vector u(1,1)
  objective_function_value f
PROCEDURE_SECTION
  f=square(betai(va,vb,value(vx))+betai(1.-a,1.-b,1.-x)-u(1));
  f+=square(va-.2)+square(vb-.6)+square(vx-.8);
