// This is used to test the following functions:
//
// dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
//    dvariable ypn);
// dvariable splint(const dvector& _xa,const dvar_vector& _ya,
//    const dvar_vector& _y2a,double x);
// dvariable splint(const dvector& _xa,const dvar_vector& _ya,
//    const dvar_vector& _y2a,const prevariable& _x);
// dvar_vector spline(const dvector &_x,const dvar_vector&_y,double yp1,
//    double ypn);
// dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
//    double ypn);
//
// the numbers test1 and test2 should be 1.0
DATA_SECTION
  int n
  !! n=10;
  vector x(1,n)
  vector y(1,n)
  number test1
  number test2
  !! random_number_generator rng(277);
  !! y.fill_randn(rng);
  !! x.fill_seqadd(1.5,.75);
PARAMETER_SECTION
  init_vector Vy(1,n)
  !! Vy=y;
  init_number yp1
  !! yp1 = 1.0;
  init_number ypn
  !! ypn = 4.0;
  init_number pos
  !! pos = 2.112;
  objective_function_value f
PROCEDURE_SECTION
  dvar_vector ders = spline(x,Vy,yp1,ypn);
  dvar_vector ders1 = spline(x,Vy,value(yp1),value(ypn));
  dvar_vector ders2 = spline(x,Vy,yp1,value(ypn));
  test1 = 1.0 + value(norm2(ders-ders1));
  test2 = 1.0 + value(norm2(ders-ders2));
  f=square(splint(x,Vy,ders,pos)-1.0);
  f+=square(yp1-1.0);
  f+=square(ypn-4.0);
  f+=square(pos-2.0);
  f+=norm2(ders);

GLOBALS_SECTION
  #include <fvar.hpp>
  dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
    dvariable ypn);
  dvariable splint(const dvector& _xa,const dvar_vector& _ya,
    const dvar_vector& _y2a,double x);
  dvariable splint(const dvector& _xa,const dvar_vector& _ya,
    const dvar_vector& _y2a,const prevariable& _x);
  dvar_vector spline(const dvector &_x,const dvar_vector&_y,double yp1,
    double ypn);
  dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
    double ypn);

REPORT_SECTION
  report << "#test1" << endl;
  report << test1 << endl;
  report << "#test2" << endl;
  report << test2 << endl;

