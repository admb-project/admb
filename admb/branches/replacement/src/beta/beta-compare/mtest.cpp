#include <admodel.h>
extern "C" {
double incbet( double aa, double bb, double xx );
}


int main(int agrc,char * argv[])
{
  double x0=2.00; 
  double y0=0.4; 
  double z0=0.25;
  ofstream ofs("ddd");
  for (double xx=1.9999;xx<=2.0001;xx+=.000002)
  {
    ofs << setprecision(20) << xx << " " << incbet(xx,y0,z0) << endl;
  }

}


