#include <gtest/gtest.h>
#include <admodel.h>

class interpret_spline
{
 /* class to make a function to do a smooth transition
    from the value a to the value b centered at c and having width e.
    The derivatives at each end point are 0.
 */
  dvector coffs;
  double a;
  double b;
  double c;
  double e;
public:
  interpret_spline(double a,double b,double c,double e);
  double operator()(double x);
};

interpret_spline::interpret_spline(double _a,double _b,double _c,double _e)
{
  a=_a;
  b=_b;
  c=_c;
  e=_e;

  double e_1=-e; double e_2=e;
  dmatrix A(1,4,1,4);
  A(1,1)=1; A(1,2)=e_1; A(1,3)=e_1*e_1; A(1,4)=e_1*e_1*e_1; 
  A(2,1)=0; A(2,2)=1;   A(2,3)=2.0*e_1; A(2,4)=3.0*e_1*e_1; 
  A(3,1)=1; A(3,2)=e_2; A(3,3)=e_2*e_2; A(3,4)=e_2*e_2*e_2; 
  A(4,1)=0; A(4,2)=1;   A(4,3)=2.0*e_2; A(4,4)=3.0*e_2*e_2; 

  dvector v(1,4);
  v(1)=a; v(2)=0.0; v(3)=b; v(4)=0.0;
  coffs=solve(A,v);
}

double interpret_spline::operator()(double x)
{
  double y=x-c; 
  if (y<-e)
  {
    return a;
  }
  else if (y>e)
  {
    return b;
  }
  else
  {
    return  ((coffs(4)*y+coffs(3))*y+coffs(2))*y+coffs(1);
  }
}

class test_spline: public ::testing::Test {};

TEST_F(test_spline, main)
{
  double a=2.0;
  double b=4.0;
  double c=3.5;
  double e=0.25;

  interpret_spline sp(a,b,c,e);

  for (double x=c-1.0;x<=c+1.0;x+=.01)
  {
    cout << x << " " << sp(x) << endl;
  }
}
