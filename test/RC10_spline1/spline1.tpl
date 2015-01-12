// This is used to test the following functions:
// 
// dvector spline(BOR_CONST dvector &_x,BOR_CONST dvector&_y,double yp1,double ypn);
// dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
//    dvariable ypn);
//  dvariable splint(const dvector& _xa,const dvar_vector& _ya,
//    const dvar_vector& _y2a,double x);
//  double splint(BOR_CONST dvector& _xa,BOR_CONST dvector& _ya,BOR_CONST dvector& _y2a,double x);
DATA_SECTION
  int n
  !! n=10;
  vector x(1,n)
  vector y(1,n)
  !! random_number_generator rng(177);
  !! y.fill_randn(rng);
  !! x.fill_seqadd(1.5,.75);
PARAMETER_SECTION
  init_vector Vy(1,n)
  !! Vy=y;
  init_number yp1
  !! yp1 = 1.0;
  init_number ypn
  !! ypn = 4.0;
  objective_function_value f
PROCEDURE_SECTION
  double pos = 2.112;
  dvar_vector ders = spline(x,Vy,yp1,ypn);
  dvector cnstders = spline(x,y,value(yp1),value(ypn));
  f=square(splint(x,Vy,ders,pos))+norm2(Vy)+norm2(ders);
  f+=square(splint(x,y,cnstders,pos))+square(yp1-1.0)+square(ypn-2.5);

GLOBALS_SECTION
  #include <fvar.hpp>
  dvar_vector spline(const dvector &_x,const dvar_vector&_y,dvariable yp1,
    dvariable ypn);
  dvariable splint(const dvector& _xa,const dvar_vector& _ya,
    const dvar_vector& _y2a,double x);
  dvector spline(BOR_CONST dvector &_x,BOR_CONST dvector&_y,double yp1,double ypn);
  double splint(BOR_CONST dvector& _xa,BOR_CONST dvector& _ya,BOR_CONST dvector& _y2a,double x);








