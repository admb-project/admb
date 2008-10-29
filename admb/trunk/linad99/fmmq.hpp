#pragma hdrstop
/*
class fmmq : public fmm_control
{
private:
  dvector h;
  dvector w;
  dvector funval;

  double dmin,fbest,df;
  long int llog,n1,ic,iconv,i1,link;
  double z,zz,gys,gs,sig,gso,alpha,tot,fy,dgs;
  long int itn,icc,np,nn,is,iu,iv,ib,ifn;
  int i, j;
  double gmax;
  double fsave;
  dvector gbest;
  dvector xbest;
  dvector xsave;
  dvector gsave;
  dvector scale;
  dvector xa;
  dvector xb;
  dvector d;
  dvector ga;
  dvector gb;
  int mode;
  int igwindow;
int  ir;
int isfv;
int istart;
int istop;
double c;
double cc;
double dff;
double fa;
double fb;
double dga;
double dgb;
double stmin;
double stepbd;
double tfmin;
double gmin;
double step;
double gl1;
double gl2;
unsigned int k;
int ititle;
int print;
int ipra;
int ip;
int n;
public:
  fmmq(int nvar);
  fmmq(int nvar,_CONST lvector& ipar);
  double minimize(_CONST dvector& x,double (*pf)(_CONST dvar_vector&));
  double minimize(BOR_CONST independent_variables & x,_CONST dvector& c,
        double (*pf)(_CONST dvar_vector&,_CONST dvector&) );
  void fmin(_CONST double& f,_CONST dvector& x,_CONST dvector& g);
  void va13c (_CONST dvector& x,_CONST double& f,_CONST dvector& g);
};
*/

void fgcomp(_CONST double& f,_CONST dvector& x,_CONST dvector& g);

void mc11b (_CONST dvector& h, BOR_CONST int& n, BOR_CONST int& k);
void mc11e (_CONST dvector& h, BOR_CONST int& n,_CONST dvector& d,_CONST dvector& w, BOR_CONST int& nn);

// if you pass ir by referenc it stops after the third func eval
// if you pass ir by value it runs but is wrong

void mc11a(_CONST dvector& h, BOR_CONST int& n,_CONST dvector& xb,_CONST double& sig,_CONST dvector& w,
           int& ir, BOR_CONST int& mk,_CONST double& eps);

void mc11adp(_CONST dvector& h, BOR_CONST int& n,_CONST dvector& d,_CONST double&,_CONST dvector& , BOR_CONST int& ir,
             int& mk,_CONST double&);

double fmax(_CONST double& x,_CONST double& y);
double ffmin(_CONST double& x,_CONST double& y);
double ffmin(BOR_CONST int& x,BOR_CONST int& y);
double mypow(double x, double p);
double dafsqrt(double x);

void fmmq_disp(int nfun, int itn, double f, double gmax,_CONST dvector& x,_CONST dvector& g);
void here(const char* place);


//  dvector xa(1,nvar);
//  dvector xb(1,nvar);
//  dvector d(1,nvar);
//  dvector ga(1,nvar);
//  dvector gb(1,nvar);
//  const int mode = 1;
//  const int igwindow = 2;
