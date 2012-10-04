// This is used to test the following functions:
// 
// double betai(double _aa, double _bb, double _xx);
// dvariable betai(const dvariable& _a,const dvariable& _b,const dvariable& _x);
DATA_SECTION
  number a
  number b
  number x
  !! a = 5;
  !! b = 12;
  !! x = .65;

PARAMETER_SECTION
  init_bounded_number a(1,20)
  init_bounded_number b(1,20)
  init_bounded_number x(.4,.8)
  !! a = model_data::a;
  !! b = model_data::b;
  !! x = model_data::x;
  objective_function_value f

PROCEDURE_SECTION
  f += square(1.0 - (betai(a, b, x) - betai(b, a, x)));
