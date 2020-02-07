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

  // First reads in array size for a from .dat and adstrings.
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

FINAL_SECTION
  assert(a.indexmin() == 1 && a.indexmax() == 6);
  assert(strcmp((char*)a(1), (char*)"a1.4") == 0);
  assert(strcmp((char*)a(2), (char*)"a4.7") == 0);
  assert(strcmp((char*)a(3), (char*)"a5.1") == 0);
  assert(strcmp((char*)a(4), (char*)"a8.3") == 0);
  assert(strcmp((char*)a(5), (char*)"a9.0") == 0);
  assert(strcmp((char*)a(6), (char*)"a14.5") == 0);

  assert(b.indexmin() == 1 && b.indexmax() == 2);
  assert(strcmp((char*)b(1), (char*)"b01") == 0);
  assert(strcmp((char*)b(2), (char*)"b02") == 0);

  assert(c.indexmin() == 1 && c.indexmax() == 10);
  assert(strcmp((char*)c(1), (char*)"c1.4") == 0);
  assert(strcmp((char*)c(2), (char*)"c4.7") == 0);
  assert(strcmp((char*)c(3), (char*)"c5.1") == 0);
  assert(strcmp((char*)c(4), (char*)"c8.3") == 0);
  assert(strcmp((char*)c(5), (char*)"c9.0") == 0);
  assert(strcmp((char*)c(6), (char*)"c14.5") == 0);
  assert(strcmp((char*)c(7), (char*)"c14.0") == 0);
  assert(strcmp((char*)c(8), (char*)"c13.4") == 0);
  assert(strcmp((char*)c(9), (char*)"c19.2") == 0);
  assert(strcmp((char*)c(10), (char*)"c18.0") == 0);

  assert(d.indexmin() == 1 && d.indexmax() == 10);
  assert(strcmp((char*)d(1), (char*)"d01") == 0);
  assert(strcmp((char*)d(2), (char*)"d02") == 0);
  assert(strcmp((char*)d(3), (char*)"d03") == 0);
  assert(strcmp((char*)d(4), (char*)"d04") == 0);
  assert(strcmp((char*)d(5), (char*)"d05") == 0);
  assert(strcmp((char*)d(6), (char*)"d06") == 0);
  assert(strcmp((char*)d(7), (char*)"d07") == 0);
  assert(strcmp((char*)d(8), (char*)"d08") == 0);
  assert(strcmp((char*)d(9), (char*)"d09") == 0);
  assert(strcmp((char*)d(10), (char*)"d10") == 0);
