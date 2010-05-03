#include <df1b2fun.h>
#define ITMAX 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30

df3_two_variable igam(const df3_two_variable & _a, const df3_two_variable & _x );


double get_values(double x,double y,int print_switch);
  double inv_cumd_gamma(double y,double a,int print_switch);

df3_two_variable df3_get_values(double cx,double cy,
  int print_switch)
{
  double zz=0.25;
  init_df3_two_variable x(cx);
  init_df3_two_variable y(cy);
  *x.get_u_x()=1.0;
  *y.get_u_y()=1.0;
  return igam(x,y);
}

int main()
{
  gradient_structure gs(50000);
  int bd=3;
  int bd1=bd-1;
  int bd2=bd-2;
  int bd3=bd-3;
  dmatrix f(-bd,bd,-bd,bd);
  dmatrix dfx(-bd1,bd1,-bd,bd);
  dmatrix d2fxx(-bd2,bd2,-bd,bd);
  dmatrix d2fxy(-bd1,bd1,-bd1,bd1);
  dmatrix d3fxxy(-bd2,bd2,-bd1,bd1);
  dmatrix d3fxxx(-bd3,bd3,-bd,bd);
  dmatrix dfy(-bd,bd,-bd1,bd1);
  dmatrix d2fyy(-bd,bd,-bd2,bd2);
  dmatrix d3fxyy(-bd1,bd1,-bd2,bd2);
  dmatrix d3fyyy(-bd,bd,-bd3,bd3);
  double h=1.e-4;
  double h2=2*h;
  double x0=0.25;
  double y0=0.76; 
  int i,j;

  do
  {
    cout << "Enter x and then y -- to quit enter -1000" << endl;
    cin >> x0;
    if (x0<-999.) break;
    cin >> y0;
    get_values(x0,y0,1);
  
    for (i=-bd;i<=bd;i++)
    {
      for (j=-bd;j<=bd;j++)
      {
        f(i,j)=get_values(x0+i*h,y0+j*h,0);
      }
    }
    for (i=-bd1;i<=bd1;i++)
    {
      for (j=-bd;j<=bd;j++)
      {
        dfx(i,j)=(f(i+1,j)-f(i-1,j))/h2;
      }
    }
    for (i=-bd1;i<=bd1;i++)
    {
      for (j=-bd1;j<=bd1;j++)
      {
        d2fxy(i,j)=(dfx(i,j+1)-dfx(i,j-1))/h2;
      }
    }
    for (i=-bd2;i<=bd2;i++)
    {
      for (j=-bd;j<=bd;j++)
      {
        d2fxx(i,j)=(dfx(i+1,j)-dfx(i-1,j))/h2;
      }
    }
    
    for (i=-bd3;i<=bd3;i++)
    {
      for (j=-bd;j<=bd;j++)
      {
        d3fxxx(i,j)=(d2fxx(i+1,j)-d2fxx(i-1,j))/h2;
      }
    }
    for (i=-bd;i<=bd;i++)
    {
      for (j=-bd1;j<=bd1;j++)
      {
        dfy(i,j)=(f(i,j+1)-f(i,j-1))/h2;
      }
    }
    for (i=-bd;i<=bd;i++)
    {
      for (j=-bd2;j<=bd2;j++)
      {
        d2fyy(i,j)=(dfy(i,j+1)-dfy(i,j-1))/h2;
      }
    }
    
    for (i=-bd;i<=bd;i++)
    {
      for (j=-bd3;j<=bd3;j++)
      {
        d3fyyy(i,j)=(d2fyy(i,j+1)-d2fyy(i,j-1))/h2;
      }
    }
    for (i=-bd2;i<=bd2;i++)
    {
      for (j=-bd1;j<=bd1;j++)
      {
        d3fxxy(i,j)=(d2fxx(i,j+1)-d2fxx(i,j-1))/h2;
      }
    }
    for (i=-bd1;i<=bd1;i++)
    {
      for (j=-bd2;j<=bd2;j++)
      {
        d3fxyy(i,j)=(d2fyy(i+1,j)-d2fyy(i-1,j))/h2;
      }
    }
    df3_two_variable z=df3_get_values(x0,y0,0);
    
    cout << endl;
    cout << "dfx = " << dfx(0,0) << "  "  << *z.get_u_x() << endl;
    cout << "d2fxx = " << d2fxx(0,0) << "  "  << *z.get_u_xx() << endl;
    cout << "d3fxxx = " << d3fxxx(0,0) << "  "  << *z.get_u_xxx() << endl;
  
    cout << "dfy = " << dfy(0,0) << "  "  << *z.get_u_y() << endl;
    cout << "d2fyy = " << d2fyy(0,0) << "  "  << *z.get_u_yy() << endl;
    cout << "d3fyyy = " << d3fyyy(0,0) << "  "  << *z.get_u_yyy() << endl;
  
    cout << "d2fxy = " << d2fxy(0,0) << "  "  << *z.get_u_xy() << endl;
    cout << "d3fxxy = " << d3fxxy(0,0) << "  "  << *z.get_u_xxy() << endl;
    cout << "d3fxyy = " << d3fxyy(0,0) << "  "  << *z.get_u_xyy() << endl;
  
    cout << "d3fyyy = " << d3fyyy(0,0) << "  "  << *z.get_u_yyy() << endl;
  }
  while(1);

  return 0;
}

double get_values(double cx,double cy,int print_switch)
{
  init_df3_two_variable x(cx);
  init_df3_two_variable y(cy);
  
  *x.get_u_x()=1.0;
  *y.get_u_y()=1.0;

  df3_two_variable z=igam( x,y);
  return *z.get_u();
}
