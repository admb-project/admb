/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"
 integer stj1;
 integer stj2;
 integer stj3;
 integer stj4;
 integer stj5;
 integer stj23;
 integer stj210;
 logical stj8;
 integer stj9;
 integer stj2800;
 integer stj21;
 integer stj22;
 integer stj41;
 integer stj43;
 integer stj42;
 integer stj17;
 integer stj18;
 integer stj19;
 integer stj110;
 integer stj20;
 integer stj27;
 integer stj24;
 integer stj25;
 integer stj28;
 integer stj26;
 integer stj40;
 integer stj118;
 integer stj44;
 integer stj45;
 integer stj2910;
 integer stj29;
 doublereal stj123;
 doublereal stj124;

#include "constructors.h"

int nx=0;
int inumber1=0;
int number3=0;
int number31=0;

/**
 * Description not yet available.
 * \param
 */
gggg01::gggg01(logical _wwuq3, logical _te0, logical _te1,
  logical _te2, logical _te3, logical _cold) :
  te0(_te0),
  te1(_te1),
  te2(_te2),
  te3(_te3), 
  wwuq3(_wwuq3), 
  cold(_cold) 
{
}

/**
 * Description not yet available.
 * \param
 */
gggg24::gggg24()
{
  accinf = new doublereal[(inumber1+1)*32];
}

/**
 * Description not yet available.
 * \param
 */
gggg25::gggg25()
{
  x = new doublereal[nx];
  x0 = new doublereal[nx];
  x1 = new doublereal[nx];
  xmin = new doublereal[nx];
  resmin = new doublereal[number3];
  d = new doublereal[nx];
  d0 = new doublereal[nx];
  dd = new doublereal[nx];
  difx = new doublereal[nx];
}

/**
 * Description not yet available.
 * \param
 */
gggg26::gggg26() : gphi0(nx), gphi1(nx)
{
  gradf = new doublereal[nx];
  qgf = new doublereal[nx];
  gres = new doublereal[nx*number3];
  gresn = new doublereal[number3];
}

/**
 * Description not yet available.
 * \param
 */
gggg27::gggg27()
{
  qr = new doublereal[nx*number3];
  betaq = new doublereal[number3];
  diag = new doublereal[number3];
  cscal = new doublereal[number3];
  colle = new doublereal[number3];
  colno = new integer[2*number3];
  perm = new integer[nx];
  perm1 = new integer[nx];
}

/**
 * Description not yet available.
 * \param
 */
gggg00::gggg00()
{
  val = new logical[number3+1];
  gconst = new integer[number3+1];
  gunit = new integer[3*(number3+1)];
  llow = new logical[nx];
  lup = new integer[nx];
}

/**
 * Description not yet available.
 * \param
 */
gggg02::gggg02()
{
  a = new doublereal[nx*nx];
  diag0 = new doublereal[nx];
}

/**
 * Description not yet available.
 * \param
 */
gggg03::gggg03()
{
  bind = new integer[number3];
  bind0 = new integer[number3];
  violis = new integer[72001];
  alist__ = new integer[number3+1];
  sort = new integer[number3];
}

/**
 * Description not yet available.
 * \param
 */
gggg07::gggg07(double _jgh4,double _jgh5)
{
  jgh4=_jgh4;
  jgh5=_jgh5;
}

/**
 * Description not yet available.
 * \param
 */
gggg04::gggg04()
{
  res = new doublereal[number3];
  res0 = new doublereal[number3];
  res1 = new doublereal[number3];
  resst = new doublereal[number3];
  u = new doublereal[number3];
  u0 = new doublereal[number3];
  w = new doublereal[number3];
  w1 = new doublereal[number3];
  work = new doublereal[number3+1];
  yu = new doublereal[nx+number3];
  slack = new doublereal[number3];
}

/**
 * Description not yet available.
 * \param
 */
gggg05::gggg05(int _n,int _numberw,int _numberv) :
 n(_n), numberw(_numberw), numberv(_numberv) {}
 
/**
 * Description not yet available.
 * \param
 */
gggg09::gggg09()
{
  cres = new integer[number3];
  cgres = new integer[number3];
}

/**
 * Description not yet available.
 * \param
 */
gggg10::gggg10()
{
  cfuerr = new logical[number3];
}

/**
 * Description not yet available.
 * \param
 */
gggg12::gggg12()
{
  name = new char[40];
}

/**
 * Description not yet available.
 * \param
 */
gggg15::gggg15()
{
  ug = new doublereal[nx];
  og = new doublereal[nx];
  delfac = new doublereal[number3];
}

/**
 * Description not yet available.
 * \param
 */
gggg17::gggg17()
{
  xst = new doublereal[nx];
}

/**
 * Description not yet available.
 * \param
 */
gggg18::gggg18(int _nx, doublereal _wwuq5, doublereal _wdg5bnd) :
    xtr(0,_nx-1), wwuq5(_wwuq5), wdg5bnd(_wdg5bnd)
{
  //xtr = new doublereal[nx];
  xsc = new doublereal[_nx];
  fu = new doublereal[number3+1];
  fugrad = new doublereal[_nx*(number3+1)];	
  fud = new doublereal[(number3+1)*6];
}

/**
 * Description not yet available.
 * \param
 */
gggg19::gggg19(logical _wwuq2,logical _wwuq4, integer _wwuq6) :
      wwuq2(_wwuq2), wwuq4(_wwuq4), wwuq6(_wwuq6){}

/**
 * Description not yet available.
 * \param
 */
gggg21::gggg21()
{
  aitr = new integer[2*number3];
}

/**
 * Description not yet available.
 * \param
 */
gggg23::gggg23()
{
  xj = new doublereal[(nx+number3)*(nx+number3)];
  ddual = new doublereal[(nx+number3)];
  r  = new doublereal[(nx+number3)*(nx+number3)];
  np = new doublereal[(nx+number3)];
  ud = new doublereal[2*number3];
  ud1 = new doublereal[2*number3];
}

#ifdef __cplusplus
	}
#endif

/*
constructors.o: In function `global constructors keyed to gggg04::gggg04(void)':
constructors.o(.text+0x531): undefined reference to `gggg01::gggg01(void)'
constructors.o(.text+0x639): undefined reference to `gggg05::gggg05(void)'
constructors.o(.text+0x659): undefined reference to `gggg06::gggg06(void)'
constructors.o(.text+0x67c): undefined reference to `gggg07::gggg07(void)'
constructors.o(.text+0x69d): undefined reference to `gggg08::gggg08(void)'
constructors.o(.text+0x745): undefined reference to `gggg11::gggg11(void)'
constructors.o(.text+0x791): undefined reference to `gggg13::gggg13(void)'
constructors.o(.text+0x7b1): undefined reference to `gggg14::gggg14(void)'
constructors.o(.text+0x839): undefined reference to `gggg16::gggg16(void)'
constructors.o(.text+0x919): undefined reference to `gggg19::gggg19(void)'
constructors.o(.text+0x939): undefined reference to `gggg20::gggg20(void)'
constructors.o(.text+0x991): undefined reference to `gggg22::gggg22(void)'
donlp2.o: In function `donlp2_':
donlp2.o(.text+0x4eb): undefined reference to `r8llcpu_'
donlp2.o(.text+0x508): undefined reference to `r8llcpu_'
donlp2.o: In function `r8llst_':
donlp2.o(.text+0xde3): undefined reference to `user_eval__'
donlp2.o(.text+0x1654): undefined reference to `user_eval__'
donlp2.o(.text+0x1929): undefined reference to `user_eval__'
donlp2.o(.text+0x1ae8): undefined reference to `r8llunimyy_'
donlp2.o(.text+0x1b5c): undefined reference to `r8llunimyy_'
donlp2.o: In function `r8llfin_':
donlp2.o(.text+0x1c07): undefined reference to `solchk_'
donlp2.o: In function `r8lluert_':
donlp2.o(.text+0xbff8): undefined reference to `user_eval__'
donlp2.o(.text+0xcca9): undefined reference to `user_eval__'
donlp2.o: In function `r8lleval_':
donlp2.o(.text+0xeb82): undefined reference to `user_eval__'
*/

#ifdef __cplusplus
extern "C" {
#endif
gggg23 * gggg23_1 = 0;
gggg24 * gggg24_1 = 0;
gggg25 * gggg25_1 = 0;
gggg26 * gggg26_1 = 0;
gggg27 * gggg27_1 = 0;
gggg00 * gggg00_1 = 0;
gggg01 * gggg01_1 = 0;
gggg02 * gggg02_1 = 0;
gggg03 * gggg03_1 = 0;
gggg04 * gggg04_1 = 0;
gggg05 * gggg05_1 = 0;
gggg06 * gggg06_1 = 0;
gggg07 * gggg07_1 = 0;
gggg08 * gggg08_1 = 0;
gggg09 * gggg09_1 = 0;
gggg10 * gggg10_1 = 0;
gggg11 * gggg11_1 = 0;
gggg12 * gggg12_1 = 0;
gggg13 * gggg13_1 = 0;
gggg14 * gggg14_1 = 0;
gggg15 * gggg15_1 = 0;
gggg16 * gggg16_1 = 0;
gggg17 * gggg17_1 = 0;
gggg18 * gggg18_1 = 0;
gggg19 * gggg19_1 = 0;
gggg20 * gggg20_1 = 0;
gggg21 * gggg21_1 = 0;
gggg22 * gggg22_1 = 0;

/**
 * Description not yet available.
 * \param
 */
void make_all_classes(int _n,int _numberw,int _numberv)
{
 nx=_n;
 number3=_numberw+_numberv;
 number31=number3;
 inumber1=3500;

 doublereal _jgh4=0.1;
 int _jgh5=1.e+4;
 logical _wwuq3=TRUE_;
 logical _te0=FALSE_;
 logical _te1=FALSE_;
 logical _te2=FALSE_;
 logical _te3=FALSE_;
 logical _cold=TRUE_;
 doublereal _wwuq5=1.e-16;
 doublereal _wdg5bnd=1.0;
 logical _wwuq2=TRUE_;
 logical _wwuq4=FALSE_;
 integer _wwuq6=3;
 gggg23_1 = new gggg23;
 gggg24_1 = new gggg24;
 gggg25_1 = new gggg25;
 gggg26_1 = new gggg26;
 gggg27_1 = new gggg27;
 gggg00_1 = new gggg00;
 gggg01_1 = new gggg01(_wwuq3,_te0,_te1,_te2,_te3, _cold);
 gggg02_1 = new gggg02;
 gggg03_1 = new gggg03;
 gggg04_1 = new gggg04;
 gggg05_1 = new gggg05(_n,_numberv,_numberw);
 gggg06_1 = new gggg06;
 gggg07_1 = new gggg07(_jgh4,_jgh5);
 gggg08_1 = new gggg08;
 gggg09_1 = new gggg09;
 gggg10_1 = new gggg10;
 gggg11_1 = new gggg11;
 gggg12_1 = new gggg12;
 gggg13_1 = new gggg13;
 gggg14_1 = new gggg14;
 gggg15_1 = new gggg15;
 gggg16_1 = new gggg16;
 gggg17_1 = new gggg17;
 gggg18_1 = new gggg18(_n,_wwuq5,_wdg5bnd);
 gggg19_1 = new gggg19(_wwuq2,_wwuq4,_wwuq6);
 gggg20_1 = new gggg20;
 gggg21_1 = new gggg21;
 gggg22_1 = new gggg22;
  stj1 = 9;
  stj2 = 1;
  stj3 = 3;
  stj4 = 2;
  stj5 = 0;
  stj23 = 13;
  stj210 = nx;
 //logical stj8 = FALSE_;
  stj9 = 5;
  stj2800 = number3;
  stj21 = 11;
  stj22 = 12;
  stj41 = 21;
  stj43 = 23;
  stj42 = 22;
  stj17 = 4;
  stj18 = -1;
  stj19 = 6;
  stj110 = 7;
  stj20 = 10;
  stj27 = 17;
  stj24 = 14;
  stj25 = 15;
  stj28 = 18;
  stj26 = 16;
  stj40 = 20;
  stj118 = 8;
  stj44 = 24;
  stj45 = 25;
  stj2910 = nx+number3;
  stj29 = 19;
  stj123 = .33333333333333331;
  stj124 = .14285714285714285;

}

#ifdef __cplusplus
	}
#endif

/**
 * Description not yet available.
 * \param
 */
doublestar::doublestar(integer n)
{
  index_max=n;
  index_min=0;
#if defined(SAFE_ALL)
  d =new doublereal[n+2];
  d[0]=123456789.12;
  d[n+1]=123456789.12;
  d+=1-index_min;
#else
  d =new doublereal[n];
  d+=-index_min;
#endif
}

/**
 * Description not yet available.
 * \param
 */
doublestar::doublestar(integer m,integer n)
{
  index_max=n;
  index_min=m;
#if defined(SAFE_ALL)
  d =new doublereal[n-m+2];
  d[0]=123456789.12;
  d[n-m+1]=123456789.12;
  d+=1-index_min;
#else
  d =new doublereal[n-m];
  d+=-index_min;
#endif
}

/**
 * Description not yet available.
 * \param
 */
doublestar::~doublestar()
{
#if defined(SAFE_ALL)
  d+=index_min-1;
  if ( fabs(d[0]-123456789.12) >1.e-10 
    || fabs(d[index_max-index_min+1]-123456789.12) > 1.e-10 )
  {
    cerr << "Memory error in doublestar" << endl;
  };
#else
  d+=index_min;
#endif
  delete [] d;
  d=0;
}

/*
doublereal& doublestar::operator[] (int i)
{ 
  if (i<index_min | i>=index_max)
  {
    cout << "Index too high in doublestar access = " << i << endl;
    exit(1);
  }
  return *(d+i);
}
integer& intstar::operator[] (int i)
{ 
  if (i<0 | i>=index_max)
  {
    cout << "Index too high in intstar access = " << i << endl;
    exit(1);
  }
  return *(d+i);
}
*/

/**
 * Description not yet available.
 * \param
 */
doublestar::operator doublereal * () { return d;}

/**
 * Description not yet available.
 * \param
 */
intstar::intstar(integer n)
{
  index_max=n;
#if defined(SAFE_ALL)
  d =new integer[n+2];
  d[0]=123456789;
  d[n+1]=123456789;
  d+=1;
#else
  d =new integer[n];
#endif
}

/**
 * Description not yet available.
 * \param
 */
intstar::~intstar()
{
#if defined(SAFE_ALL)
  d-=1;
  if (abs(d[0]-123456789) >0 ||  abs(d[index_max+1]-123456789>0) )
  {
    cerr << "Memory error in intstar" << endl;
  }
#endif
  delete [] d;
  d=0;
}
