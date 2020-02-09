// Example intended to check variance/covariance in RE models: separable version
// Motivated by discovery of bug:  [ADMB Users] difference between ADMB-RE and R/mgcv in SEs for smoother coefficients in a GAM fitted by maximum likelihood

DATA_SECTION
  number y
  !! y=10.0;
  number n
  !! n=10;

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
   init_number x
   random_effects_vector u(1,3)
   objective_function_value f

PROCEDURE_SECTION
   f = 0.0;
   separable_ll(x,u(1));
   for (int i=2;i<=3;i++) separable_ll2(u(i));

SEPARABLE_FUNCTION void separable_ll(const prevariable& x, const prevariable& u)
     f -= -0.5*square(x);	  // Prior on x: x = e1
     f -= -0.5*square(u-x);       // u|x: u = x + e2
     f -= -0.5*square(y-u);       // y|u: y = u + e3

SEPARABLE_FUNCTION void separable_ll2(const prevariable& u)
     f -= -0.5*square(u);	

REPORT_SECTION
  report << "a:\n" << a << endl;
  report << "b:\n" << b << endl;
  report << "c:\n" << c << endl;
  report << "d:\n" << d << endl;

GLOBAL_SECTION
  #include <cassert>

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
