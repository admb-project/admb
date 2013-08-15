// This is used to test the following functions:
// 
// void gauss_hermite (const dvector& _t,const dvector& _wts)
// void gauss_legendre ( double a, double b, const dvector& _t, const dvector& _wts)
DATA_SECTION
  int n
  !! n=10;
  vector x(1,n)
  vector y(1,n)
  vector u(1,n)
  vector w(1,n)
 LOC_CALCS
  gauss_hermite(x,y);
  gauss_legendre(2.2,3.0,u,w);

PARAMETER_SECTION
  init_vector Vx(1,n)
  init_vector Vy(1,n)
  init_vector Vu(1,n)
  init_vector Vw(1,n)
  !! Vx=x;
  !! Vy=y;
  !! Vu=u;
  !! Vw=w;
  objective_function_value f

PROCEDURE_SECTION
  f=square(norm2(Vx)-1.0);
  f+=square(norm2(Vy)-0.5);
  f+=square(norm2(Vu)-0.5);
  f+=square(norm2(Vw)-1.0);
