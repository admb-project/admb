#include <df1b2fun.h>
#include "betacf.hpp"

df1b2variable betacf(const df1b2variable& a,const df1b2variable& b, const df1b2variable& x, int MAXIT)
{
  typedef tiny_ad::variable<3, 3> Float;
  Float a_ (value(a), 0);
  Float b_ (value(b), 1);
  Float x_ (value(x), 2);
  Float ans = betacf<Float>(a_, b_, x_, MAXIT);  
  double val=ans.value.value.value;
  tiny_vec<double, 3> der1 = ans.value.value.getDeriv();
  tiny_vec<double, 9> der2 = ans.value.getDeriv();
  tiny_vec<double, 27> der3 = ans.getDeriv();

  df1b2variable tmp;
  double * xd=a.get_u_dot();
  double * yd=b.get_u_dot();
  double * zd=x.get_u_dot();
  double * tmpd=tmp.get_u_dot();
  *tmp.get_u()=val;
  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    *tmpd++ = der1[0] * *xd++ + der1[1] * *yd++ + der1[2] * *zd++;
  }
  if (!df1b2_gradlist::no_derivatives)
  {
    f1b2gradlist->write_pass1(&a,&b,&x,&tmp,
     der1[0],der1[1],der1[2],
     der2[0],der2[1],der2[2],der2[4],der2[5],der2[8],
     der3[0],der3[1],der3[2],der3[4],der3[5],der3[8],der3[13],der3[14],der3[17],der3[26]);
  }
  //  f1b2gradlist->write_pass1(&a,&b,&x,&tmp,
  //   F_x,F_y,F_z,
  //   F_xx,F_xy,F_xz,F_yy,F_yz,F_zz,
  //   F_xxx,F_xxy,F_xxz,F_xyy,F_xyz,F_xzz,F_yyy,F_yyz,F_yzz,F_zzz);
  return tmp;
}

df1b2variable pbeta(const df1b2variable & x, const df1b2variable & a, const df1b2variable & b, int maxit)
{
  df1b2variable bt;
  if (value(x) < 0.0 || value(x) > 1.0) cerr << "Bad x in routine pbeta" << endl;
  if (value(x) == 0.0 || value(x) == 1.0) bt=double(0.0);
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (value(x) < (value(a)+1.0)/(value(a)+value(b)+2.0))
    return bt*betacf(a,b,x,maxit)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x,maxit)/b;
}


