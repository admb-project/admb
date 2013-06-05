
#include <fvar.hpp>

double mfexp2(const double& x,double b,double c)
{
  if (x<=b && x>=-c) 
  {
    return exp(x);
  }
  else if (x>b)
  {
    double y=x-b;
    double y2=square(y);
    double y3=y*y2;
    //return exp(b)*(1.+y/(1.+y) +1.5*y2/(1.+y2));
    return exp(b)*(1.+y/(1.+y) +1.5*y2/(1.+y2)-5.0/6.0*y3/(1+y3));
  }
  else
  {
    double y=-x-c;
    double y2=square(y);
    double y3=y*y2;
    return exp(-c)/(1.+y/(1.+y) +1.5*y2/(1.+y2)+(1.0/6.0)*y3/(1+y3));
  }
}

int main(int argc, char * argv[])
{

   int n=10;
   int n1=n-1;
   int n2=n1-1;
   int n3=n2-1;
   double b=5;
   double c=8;
   double h=.001;
   dvector d0(-n,n);
   for (int i=-n;i<=n;i++)
   {
     double x=b+i*h;
     d0(i)=mfexp2(x,b,c);
   }

   dvector d1(-n1,n1);
   for (int i=-n1;i<=n1;i++)
   {
     d1(i)=(d0(i+1)-d0(i-1))/(2*h);
   }

   dvector d2(-n2,n2);
   for (int i=-n2;i<=n2;i++)
   {
     d2(i)=(d1(i+1)-d1(i-1))/(2*h);
   }

   dvector d3(-n3,n3);
   for (int i=-n3;i<=n3;i++)
   {
     d3(i)=(d2(i+1)-d2(i-1))/(2*h);
   }

   cout << d1 << endl;
   cout << "first derivative" << endl;
   cout << d1(0) << endl;
   cout << exp(b) << endl;
   cout << d2 << endl;
   cout << "second derivative" << endl;
   cout << d2(0) << endl;
   cout << exp(b) << endl;
   cout << "third derivative" << endl;
   cout << d3(0) << endl;
   cout << "scaled third derivative" << endl;
   cout << d3(0)/exp(b) << endl;
   cout << exp(b) << endl;

   h=.001;
   for (int i=-n;i<=n;i++)
   {
     double x=-c+i*h;
     d0(i)=mfexp2(x,b,c);
   }

   for (int i=-n1;i<=n1;i++)
   {
     d1(i)=(d0(i+1)-d0(i-1))/(2*h);
   }

   for (int i=-n2;i<=n2;i++)
   {
     d2(i)=(d1(i+1)-d1(i-1))/(2*h);
   }

   for (int i=-n3;i<=n3;i++)
   {
     d3(i)=(d2(i+1)-d2(i-1))/(2*h);
   }

   //cout << d1 << endl;
   cout << d1(0) << endl;
   cout << exp(-c) << endl;
   //cout << d2 << endl;
   cout << d2(0) << endl;
   cout << exp(-c) << endl;




}

