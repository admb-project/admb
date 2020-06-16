// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int n
  init_vector x(1,n)
  init_vector y(1,n)
PARAMETER_SECTION
  init_number b0
  init_number b1
  vector yhat(1,n)
  objective_function_value f
PROCEDURE_SECTION
  cout << "Start: " << gradient_structure::GRAD_STACK1->total() << endl;

  dvariable result;
  funnel_dvariable Integral;
  {
    ad_begin_funnel();
    yhat=b0+b1*x;
    Integral = regression(y,yhat);
    cout << "During: " << gradient_structure::GRAD_STACK1->total() << endl;
    result = Integral;
  }
  cout << "Before: " << gradient_structure::GRAD_STACK1->total() << endl;
  f = result;
  cout << "After: " << gradient_structure::GRAD_STACK1->total() << endl;
