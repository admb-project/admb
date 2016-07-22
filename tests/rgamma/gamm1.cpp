#include <admodel.h>
#include <contrib.h>
#include <time.h>

namespace gsl
{
double rgamma(double alpha, random_number_generator& rng) 
{
  double b=1.0;
  double a=alpha;

  if (a<1)
    {
      double u = randu(rng);
      return gsl::rgamma (1.0 + a,rng) * pow (u, 1.0 / a);
    }
 
  {
    double x, v, u;
    double d = a - 1.0 / 3.0;
    double c = (1.0 / 3.0) / sqrt (d);
 
    while (1)
      {
        do
          {
            x = randn(rng);
            v = 1.0 + c * x;
          }
        while (v<0);
 
        v = v * v * v;
        u = randu(rng);
        //v = v * v * v;
        //u = randu(rng);
 
        if (u < (1 - 0.0331 * x * x * x * x)) 
          break;
 
        if (log (u) < (0.5 * x * x + d * (1 - v + log (v))))
          break;
      }
 
    return b * d * v;
  }
}
}

double rgamma1(double aa,const random_number_generator & rng)
{
  double a=aa;
  if (aa<1.0)
   a=aa+1.0;

   double d=a-1.0/3.0;
   double c=1.0/sqrt(9.9*d);

   do
   {
     double u=randu(rng);
     double x=randn(rng);
     double v=cube(1+c*x);
     if (v>0.0 && log(u)<0.5*square(x)+d-d*v+d*log(v))
     {
       double y=d*v;
       if (aa<1.0)
       {
         double u=randu(rng);
         y*=pow(u,1.0/aa);
       }
       return y;
     }
   }
   while(1);
}




int main()
{
  double alpha=10;
  int n=100000000;
  dvector v(1,n);

  random_number_generator rng(301);
  double ssum=0.0;
  double ssum2=0.0;
  double x1, x2;
  clock_t begin, end;

  begin = clock();
  for (int i=1;i<=n;i++)
  {
    v(i)=gsl::rgamma(alpha,rng);
    ssum+=v(i);
    ssum2+=square(v(i));
  }
  end = clock();
   
  x1=ssum/n;
  x2=ssum2/n;
  cout<<endl<<"GSL:"<<endl;
  cout << x1 << " " << x2-square(x1);
  cout <<  " ( time: "<<  (double)(end - begin) / CLOCKS_PER_SEC <<" )" <<endl;

  random_number_generator rng2(301);
  ssum=0.0;
  ssum2=0.0;
  begin = clock();
  for (int i=1;i<=n;i++)
  {
    v(i)=rgamma1(alpha,rng2);
    ssum+=v(i);
    ssum2+=square(v(i));
  }
  end = clock();

  x1=ssum/n;
  x2=ssum2/n;
  cout<<endl<<"Dave:"<<endl;
  cout << x1 << " " << x2-square(x1);
  cout <<  " ( time: "<<  (double)(end - begin) / CLOCKS_PER_SEC <<" )" <<endl;

  random_number_generator rng3(301);
  ssum=0.0;
  ssum2=0.0;
  begin = clock();
  for (int i=1;i<=n;i++)
  {
    v(i)=rgamma(alpha,rng3);
    ssum+=v(i);
    ssum2+=square(v(i));
  }
  end = clock();
   
  x1=ssum/n;
  x2=ssum2/n;
  cout<<endl<<"QFC:"<<endl;
  cout << x1 << " " << x2-square(x1);
  cout <<  " ( time: "<<  (double)(end - begin) / CLOCKS_PER_SEC <<" )" <<endl;
}
