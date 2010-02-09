#include <fvar.hpp>
extern "C" {
static double incbet(double, double, double);
static double incbetl(double, double, double);
}

int main(void)
{
  double x1=1.9999;
  double x2 = 2.0001;
  double x0 = 1.99;  
  double y0 = 0.4;   // aka b
  double z0 = 0.25;  // aka x

  double dx = 0.000002;
  int nx = (x2-x1)/dx + 1;
  //double tx = x1 - dx;
  ofstream bet("betacomp.dat");
  bet << "#  n b  x" << endl;
  bet << nx << " " << y0 <<  " " << z0 << endl;
  bet << "# a  AD  cephes" << endl;
  //for (int i = 1; i <= nx; i++)
  for (double xx=1.9999;xx<=2.0001;xx+=.000002)
  {
    //tx +=  dx;
    //cout << xx << " " << tx << endl;
    double ad = betai(xx,y0,z0);
    double cephes = incbet(xx,y0,z0);
  
  //bet << setprecision(20) << xx << " " << ad << " " << cephes << endl;
    bet << xx << " " << ad << " " << cephes << endl;
  }
  return(0);
}

