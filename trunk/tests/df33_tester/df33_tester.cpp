#include <df1b2fun.h>
#include <df3fun.h>
#include <df33fun.h>
#define ITMAX 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30

double get_values(double x,double y,double z,int print_switch);
  double inv_cumd_gamma(double y,double a,int print_switch);

df3_three_variable betai(df3_three_variable& a,df3_three_variable& b,
  df3_three_variable& x,int maxit){ cerr << "OO" << endl;}

df3_three_variable df3_get_values(double cx,double cy,double czz,int print_switch);

double inv_cumd_beta_stable(double x,double y,double z, double eps);

main()
{
  gradient_structure gs(50000);
  int bd=3;
  int bd1=bd-1;
  int bd2=bd-2;
  int bd3=bd-3;
  d3_array f(-bd,bd,-bd,bd,-bd,bd);
  d3_array dfx(-bd1,bd1,-bd,bd,-bd,bd);
  d3_array dfy(-bd,bd,-bd1,bd1,-bd,bd);
  d3_array dfz(-bd,bd,-bd,bd,-bd1,bd1);

  d3_array d2fxx(-bd2,bd2,-bd,bd,-bd,bd);
  d3_array d2fyy(-bd,bd,-bd2,bd2,-bd,bd);
  d3_array d2fzz(-bd,bd,-bd,bd,-bd2,bd2);

  d3_array d2fxy(-bd1,bd1,-bd1,bd1,-bd,bd);
  d3_array d2fxz(-bd1,bd1,-bd,bd,-bd1,bd1);
  d3_array d2fyz(-bd,bd,-bd1,bd1,-bd1,bd1);

  d3_array d3fxxy(-bd2,bd2,-bd1,bd1,-bd,bd);
  d3_array d3fxxz(-bd2,bd2,-bd,bd,-bd1,bd1);
  d3_array d3fxxx(-bd3,bd3,-bd,bd,-bd,bd);
  d3_array d3fxyy(-bd1,bd1,-bd2,bd2,-bd,bd);
  d3_array d3fyyy(-bd,bd,-bd3,bd3,-bd,bd);
  d3_array d3fxyz(-bd1,bd1,-bd1,bd1,-bd1,bd1);
  d3_array d3fyyz(-bd,bd,-bd2,bd2,-bd1,bd1);
  d3_array d3fyzz(-bd,bd,-bd1,bd1,-bd2,bd2);
  d3_array d3fxzz(-bd1,bd1,-bd,bd,-bd2,bd2);
  d3_array d3fzzz(-bd,bd,-bd,bd,-bd3,bd3);

  double h=1.e-4;
  double h2=2*h;

  double x0=2.0; 
  double y0=3.0; 
  double z0=0.99;

  int i,j,k;

  get_values(x0,y0,z0,1);

  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        f(i,j,k)=get_values(x0+i*h,y0+j*h,z0+k*h,0);
      }
    }
  }
  for (i=-bd1;i<=bd1;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        dfx(i,j,k)=(f(i+1,j,k)-f(i-1,j,k))/h2;
      }
    }
  }
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd1;j<=bd1;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        dfy(i,j,k)=(f(i,j+1,k)-f(i,j-1,k))/h2;
      }
    }
  }
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd1;k<=bd1;k++)
      {
        dfz(i,j,k)=(f(i,j,k+1)-f(i,j,k-1))/h2;
      }
    }
  }
  for (i=-bd1;i<=bd1;i++)
  {
    for (j=-bd1;j<=bd1;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d2fxy(i,j,k)=(dfx(i,j+1,k)-dfx(i,j-1,k))/h2;
      }
    }
  }
  for (i=-bd2;i<=bd2;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d2fxx(i,j,k)=(dfx(i+1,j,k)-dfx(i-1,j,k))/h2;
      }
    }
  }
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd2;j<=bd2;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d2fyy(i,j,k)=(dfy(i,j+1,k)-dfy(i,j-1,k))/h2;
      }
    }
  }
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd2;k<=bd2;k++)
      {
        d2fzz(i,j,k)=(dfz(i,j,k+1)-dfz(i,j,k-1))/h2;
      }
    }
  }
  for (i=-bd1;i<=bd1;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd1;k<=bd1;k++)
      {
        d2fxz(i,j,k)=(dfx(i,j,k+1)-dfx(i,j,k-1))/h2;
      }
    }
  }
  
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd1;j<=bd1;j++)
    {
      for (k=-bd1;k<=bd1;k++)
      {
        d2fyz(i,j,k)=(dfy(i,j,k+1)-dfy(i,j,k-1))/h2;
      }
    }
  }
  
  for (i=-bd3;i<=bd3;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d3fxxx(i,j,k)=(d2fxx(i+1,j,k)-d2fxx(i-1,j,k))/h2;
      }
    }
  }
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd2;j<=bd2;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d2fyy(i,j,k)=(dfy(i,j+1,k)-dfy(i,j-1,k))/h2;
      }
    }
  }
  
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd3;j<=bd3;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d3fyyy(i,j,k)=(d2fyy(i,j+1,k)-d2fyy(i,j-1,k))/h2;
      }
    }
  }
  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd2;j<=bd2;j++)
    {
      for (k=-bd1;k<=bd1;k++)
      {
        d3fyyz(i,j,k)=(d2fyy(i,j,k+1)-d2fyy(i,j,k-1))/h2;
      }
    }
  }

  for (i=-bd1;i<=bd1;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd2;k<=bd2;k++)
      {
        d3fxzz(i,j,k)=(d2fxz(i,j,k+1)-d2fxz(i,j,k-1))/h2;
      }
    }
  }

  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd1;j<=bd1;j++)
    {
      for (k=-bd2;k<=bd2;k++)
      {
        d3fyzz(i,j,k)=(d2fyz(i,j,k+1)-d2fyz(i,j,k-1))/h2;
      }
    }
  }

  for (i=-bd;i<=bd;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd3;k<=bd3;k++)
      {
        d3fzzz(i,j,k)=(d2fzz(i,j,k+1)-d2fzz(i,j,k-1))/h2;
      }
    }
  }

  for (i=-bd2;i<=bd2;i++)
  {
    for (j=-bd1;j<=bd1;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d3fxxy(i,j,k)=(d2fxx(i,j+1,k)-d2fxx(i,j-1,k))/h2;
      }
    }
  }

  for (i=-bd2;i<=bd2;i++)
  {
    for (j=-bd;j<=bd;j++)
    {
      for (k=-bd1;k<=bd1;k++)
      {
        d3fxxz(i,j,k)=(d2fxx(i,j,k+1)-d2fxx(i,j,k-1))/h2;
      }
    }
  }
  for (i=-bd1;i<=bd1;i++)
  {
    for (j=-bd2;j<=bd2;j++)
    {
      for (k=-bd;k<=bd;k++)
      {
        d3fxyy(i,j,k)=(d2fyy(i+1,j,k)-d2fyy(i-1,j,k))/h2;
      }
    }
  }
  for (i=-bd1;i<=bd1;i++)
  {
    for (j=-bd1;j<=bd1;j++)
    {
      for (k=-bd1;k<=bd1;k++)
      {
        d3fxyz(i,j,k)=(d2fxy(i,j,k+1)-d2fxy(i,j,k-1))/h2;
      }
    }
  }
  df3_three_variable z3=df3_get_values(x0,y0,z0,1);
  //df3_three_variable z3= x0*y0*z0;
  
  cout << endl;
  
  cout << "dfx = " << dfx(0,0,0) << " " << *z3.get_u_x() << endl;
  cout << "dfy = " << dfy(0,0,0) << "  " << *z3.get_u_y()  << endl;
  cout << "dfz = " << dfz(0,0,0) << "  " << *z3.get_u_z()  << endl;
  cout << "d2fxx = " << d2fxx(0,0,0) << "  " << *z3.get_u_xx()  << endl;
  cout << "d2fxy = " << d2fxy(0,0,0) << "  " << *z3.get_u_xy() <<  endl;
  cout << "d2fxz = " << d2fxz(0,0,0) << "  " << *z3.get_u_xz() <<  endl;
  cout << "d2fyy = " << d2fyy(0,0,0) << "  " << *z3.get_u_yy()  << endl;
  cout << "d2fyz = " << d2fyz(0,0,0) << "  " << *z3.get_u_yz()  << endl;
  cout << "d2fzz = " << d2fzz(0,0,0) << "  " << *z3.get_u_zz()  << endl;
  cout << "d3fxxx = " << d3fxxx(0,0,0) << "  " << *z3.get_u_xxx()  << endl;
  cout << "d3fxxy = " << d3fxxy(0,0,0) << "  " << *z3.get_u_xxy()  << endl;
  cout << "d3fxxz = " << d3fxxz(0,0,0) << "  " << *z3.get_u_xxz()  << endl;
  cout << "d3fxyy = " << d3fxyy(0,0,0) << "  " << *z3.get_u_xyy()  << endl;
 
  cout << "d3fxyz = " << d3fxyz(0,0,0) << "  " << *z3.get_u_xyz()  << endl;
  cout << "d3fxzz = " << d3fxzz(0,0,0) << "  " << *z3.get_u_xzz()  << endl;
  cout << "d3fyyy = " << d3fyyy(0,0,0) << "  " << *z3.get_u_yyy()  << endl;
  cout << "d3fyyz = " << d3fyyz(0,0,0) << "  " << *z3.get_u_yyz()  << endl;
  cout << "d3fyzz = " << d3fyzz(0,0,0) << "  " << *z3.get_u_yzz()  << endl;
  cout << "d3fzzz = " << d3fzzz(0,0,0) << "  " << *z3.get_u_zzz()  << endl;
  cout << endl;
  cout << "f = " << f(0,0,0) << endl;
  cout << endl;
  //cout << "dfx = " << dfx << endl;
}

/*
df3_two_variable gammln(const df3_two_variable& xx)
{
  df3_two_variable x,tmp,ser,tmp1;
  static double cof[6]={76.18009173,-86.50532033,24.01409822,
    -1.231739516,0.120858003e-2,-0.536382e-5};
  int j;
  x=xx-1.0;
  tmp=x+5.5;
  tmp -= (x+0.5)*log(tmp);
  ser=1.0;
  for (j=0;j<=5;j++) 
  {
    x += 1.0;
    ser += cof[j]/x;
  }
  return -tmp+log(2.50662827465*ser);
}


void gcf(const df3_two_variable& gammcf,const df3_two_variable& a,
  const df3_two_variable& x,const df3_two_variable& gln)
{
  int i;
  df3_two_variable an,b,c,d,del,h;

  gln=gammln(a);
  b=x+1.0-a;
  c=1.0/FPMIN;
  d=1.0/b;
  h=d;
  for (i=1;i<=ITMAX;i++) {
    an = -i*(i-a);
    b += 2.0;
    d=an*d+b;
    if (fabs(value(d)) < FPMIN) d=FPMIN;
    c=b+an/c;
    if (fabs(value(c)) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(value(del)-1.0) < EPS) break;
  }
  if (i > ITMAX) 
    cerr << "a too large, ITMAX too small in gcf" << endl;
  gammcf=exp(-x+a*log(x)-(gln))*h;
}

void gser(const df3_two_variable& gamser,const df3_two_variable& a,
  const df3_two_variable& x,const df3_two_variable& gln)
{
  int n;
  df3_two_variable sum,del,ap;

  gln=gammln(a);
 // ****************************************************
 // ****************************************************
  //gamser=gln;
  //return;
 // ****************************************************
 // ****************************************************
  if (value(x) <= 0.0) {
    if (value(x) < 0.0) 
      cerr << "x less than 0 in routine gser" << endl;
    gamser=0.0;
    return;
  } 
  else 
  {
    ap=a;
    del=sum=1.0/a;
    for (n=1;n<=ITMAX;n++) {
      ap+=1.0;
      del *= x/ap;
      sum += del;
      if (fabs(value(del)) < fabs(value(sum))*EPS) {
        gamser=sum*exp(-x+a*log(x)-(gln));
        return;
      }
    }
    cerr << "a too large, ITMAX too small in routine gser" << endl;
    return;
  }
}


df3_two_variable gammp(const df3_two_variable& a,
  const df3_two_variable& x)
{
  df3_two_variable gamser,gammcf,gln;

  if (value(x) < 0.0 || value(a) <= 0.0) 
    cerr << "Invalid arguments in routine gammp" << endl;
  if (value(x) < (value(a)+1.0)) {
    gser(gamser,a,x,gln);
    return gamser;
  } else {
    gcf(gammcf,a,x,gln);
    return 1.0-gammcf;
  }
}
*/
double get_values(double cx,double cy,double czz,int print_switch)
{
 //return sin(cx)*exp(cy)*sin(czz);
 // return inv_cumd_beta_stable(cx,cy,czz,1.e-7);
  return betai(cx,cy,czz);
  //return cy* cy*czz;
  //return cx*cy*czz + cx*czz*czz + cy* czz*czz;
 /*
  init_df3_three_variable x(cx);
  init_df3_three_variable y(cy);
  init_df3_three_variable zz(czz);
  
  *x.get_u_x()=1.0;
  *y.get_u_y()=1.0;
  *zz.get_u_z()=1.0;
 */
  double z=betai(cx,cy,czz);

  //df3_three_variable u=cumd_norm(x);
  //df3_three_variable z=cumd_gamma( x,y);
  //double z=inv_cumd_gamma( cx,cy,print_switch);
  
  //df3_three_variable z=atan( x);
  
 
 /*
  if (print_switch)
  {
    cout << "analytic" << endl;
    cout << "f_x = " << *z.get_u_x() << endl;
    cout << "f_xx = " << *z.get_u_xx() << endl;
    cout << "f_xxx = " << *z.get_u_xxx() << endl;
    cout << endl;
    cout << "f_xy = " << *z.get_u_xy() << endl;
    cout << endl;
    cout << "f_y = " << *z.get_u_y() << endl;
    cout << "f_yy = " << *z.get_u_yy() << endl;
    cout << "f_yyy = " << *z.get_u_yyy() << endl;
    cout << endl;
    cout << "f_xxy = " << *z.get_u_xxy() << endl;
    cout << "f_xyy = " << *z.get_u_xyy() << endl;
    cout << "end analytic" << endl;
  }
 */
 

  //return z;
  return z;
  //return *z.get_u();
}

df3_three_variable df3_get_values(double cx,double cy,double czz,int print_switch)
{
  init_df3_three_variable x(cx);
  init_df3_three_variable y(cy);
  init_df3_three_variable zz(czz);
  //*x.get_u_x()=0.0;
  //*zz.get_u_z()=1.0;
  //df3_three_variable z=sin(x)*exp(y)*sin(zz);
  df3_three_variable z=betai(x,y,zz);
  //df3_three_variable z=betai(x,y,zz,100);

  return z;
  
 /*
  *x.get_u_x()=1.0;
  *y.get_u_y()=1.0;
  *zz.get_u_z()=1.0;
 */

  return y* y*zz;
  //return x*y*zz + x*zz*zz + y* zz*zz;
  //return x*y*zz;
  //df3_three_variable z=betai(x,y,zz,100);

  //df3_three_variable u=cumd_norm(x);
  //df3_three_variable z=cumd_gamma( x,y);
  //double z=inv_cumd_gamma( cx,cy,print_switch);
  
  //df3_three_variable z=atan( x);
  //return z;
  
 
 /*
  if (print_switch)
  {
    cout << "analytic" << endl;
    cout << "f_x = " << *z.get_u_x() << endl;
    cout << "f_xx = " << *z.get_u_xx() << endl;
    cout << "f_xxx = " << *z.get_u_xxx() << endl;
    cout << endl;
    cout << "f_xy = " << *z.get_u_xy() << endl;
    cout << endl;
    cout << "f_y = " << *z.get_u_y() << endl;
    cout << "f_yy = " << *z.get_u_yy() << endl;
    cout << "f_yyy = " << *z.get_u_yyy() << endl;
    cout << endl;
    cout << "f_xxy = " << *z.get_u_xxy() << endl;
    cout << "f_xyy = " << *z.get_u_xyy() << endl;
    cout << "end analytic" << endl;
  }
 */
 

}


  double inv_cumd_gamma(double y,double a,int print_switch)
  {
    // get the inverse values
    double x=inv_cumd_gamma(y,a);

    return x;
  /*
    init_df3_three_variable xx(x);
    init_df3_three_variable aa(a);
    //init_df3_three_variable xx(1.0);
    //init_df3_three_variable aa(2.0);
    *xx.get_u_x()=1.0;
    *aa.get_u_y()=1.0;
    
    df3_three_variable z=cumd_gamma(xx,aa);
    //df3_three_variable z=sqrt(sqrt(xx*aa));

    // now use the derivatives of z to get the
    //derivatives of x wrt y,a and save them

    double F_x=1.0/(*z.get_u_x());
   
    double F_y=-F_x* *z.get_u_y();
    double F_xx=-F_x* *z.get_u_xx()/square(*z.get_u_x());

    double F_xy=-(F_xx * *z.get_u_x() * *z.get_u_y() + F_x * *z.get_u_xy())/
                *z.get_u_x();

    double F_yy=-(F_xx * square(*z.get_u_y()) 
                +2.0* F_xy* *z.get_u_y()
                +F_x * *z.get_u_yy());

    double F_xxx=-(F_x* *z.get_u_xxx()
                +3.0*F_xx* *z.get_u_x() * *z.get_u_xx())
                /cube(*z.get_u_x());

    double F_xxy=-(F_xxx * square(*z.get_u_x())* *z.get_u_y()
                 + 2.0*F_xx* *z.get_u_x()* *z.get_u_xy()
                 + F_xx* *z.get_u_xx() * *z.get_u_y()
                 + F_xy * *z.get_u_xx() 
                 + F_x * *z.get_u_xxy())/
                 square(*z.get_u_x());

    double F_xyy=-(F_xxx* *z.get_u_x() *square(*z.get_u_y())
                 +2.0* F_xx * *z.get_u_xy() * *z.get_u_y()
                 +2.0*F_xxy * *z.get_u_x() * *z.get_u_y()
                 + 2.0*F_xy * *z.get_u_xy() 
                 + F_xx * *z.get_u_x() * *z.get_u_yy()
                 + F_x * *z.get_u_xyy())/
                 *z.get_u_x();
     double F_yyy=-(F_xxx*cube(*z.get_u_y())+
                 +3.0*F_xxy*square(*z.get_u_y())
                 +3.0*F_xx* *z.get_u_y() * *z.get_u_yy()
                 +3.0*F_xy* *z.get_u_yy()
                 +3.0*F_xyy * *z.get_u_y()
                 +F_x * *z.get_u_yyy());

     if (print_switch)
     {
       cout << "F_x = " << F_x << endl;
       cout << "F_xx = " << F_xx << endl;
       cout << "F_xxx = " << F_xxx << endl;
       cout << endl;
       cout << "F_xy = " << F_xy << endl;
       cout << endl;
       cout << "F_y = " << F_y << endl;
       cout << "F_yy = " << F_yy << endl;
       cout << "F_yyy = " << F_yyy << endl;
       cout << endl;
       cout << "F_xxy = " << F_xxy << endl;
       cout << "F_xyy = " << F_xyy << endl;
     }

    return x;  
   */

  }


