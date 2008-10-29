#if !defined(_SVDCMP_)
#define _SVDCMP_ 

#include <fvar.hpp>


double pythag(double a, double b);
double fmax(double a,double b) { if (a>b) return a; else return b;}
double imin(int a,int b) { if (a>b) return b; else return a;}
double sign(double a,double b){ if (b>0) return fabs(a); else return -fabs(a);}

dvariable pythag(_CONST prevariable& a, double b);
dvariable pythag(_CONST prevariable& a, _CONST prevariable& b);
dvariable fmax(BOR_CONST prevariable& a,BOR_CONST prevariable& b) { if (a>b) return a; else return b;}
dvariable sign(BOR_CONST prevariable& a,BOR_CONST prevariable& b){ if (b>0) return fabs(a); else return -fabs(a);}

class d_singular_value_decomposition
{
public:
  dmatrix a;
  dvector w;
  dmatrix v;
  d_singular_value_decomposition(int m,int n) :
    a(1,m,1,n), w(1,n), v(1,n,1,n) {}
};

class dvar_singular_value_decomposition
{
public:
  dvar_matrix a;
  dvar_vector w;
  dvar_matrix v;
  dvar_singular_value_decomposition(int m,int n) :
    a(1,m,1,n), w(1,n), v(1,n,1,n) {}
};

d_singular_value_decomposition svdcmp(BOR_CONST dmatrix& a1);
dvar_singular_value_decomposition svdcmp(BOR_CONST dvar_matrix& a1);

#endif
