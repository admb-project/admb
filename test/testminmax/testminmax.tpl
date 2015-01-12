DATA_SECTION
  number x
  number y
  !! x=3.3; y=2.2;

PARAMETER_SECTION
  init_number b
  objective_function_value nll;

PROCEDURE_SECTION
  cout << min(x, y)  << endl;
  cout << min(0.33,0.22) << endl;
