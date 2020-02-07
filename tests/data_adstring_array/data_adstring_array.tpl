// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int n
  init_vector x(1,n)
  init_vector y(1,n)

  init_adstring_array c(1,n)
  adstring_array d(1,n)
  !! d(1) = "d01";
  !! d(2) = "d02";
  !! d(3) = "d03";
  !! d(4) = "d04";
  !! d(5) = "d05";
  !! d(6) = "d06";
  !! d(7) = "d07";
  !! d(8) = "d08";
  !! d(9) = "d09";
  !! d(10) = "d10";

  init_adstring_array a

  adstring_array b
  !! b.allocate(1, 2);
  !! b(1) = "b01";
  !! b(2) = "b02";

PARAMETER_SECTION
  init_number b0
  init_number b1
  vector yhat(1,n)
  objective_function_value f

PROCEDURE_SECTION
  yhat=b0+b1*x;
  f=regression(y,yhat);

REPORT_SECTION
  report << "a:\n" << a << endl;
  report << "b:\n" << b << endl;
  report << "c:\n" << c << endl;
  report << "d:\n" << d << endl;
