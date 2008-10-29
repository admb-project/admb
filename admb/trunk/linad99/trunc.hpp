
#if defined(__BORLANDC__ )
#  pragma interface
#endif

// file fvar.hpp
#ifndef FMMT_HPP
#define FMMT_HPP

/*
class fmm_control
{
public:
  long   maxfn;
  long   iprint;
  double crit;
  long   imax;
  double dfn;
  long   ifn;
  long   iexit;
  long   ialph;
  long   ihflag;
  long   ihang;
  long   scroll_flag;
  int maxfn_flag;
  int quit_flag;
  double min_improve;
  int    ireturn;

  void set_defaults();
  fmm_control();
  fmm_control(BOR_CONST fmm_control& );
#ifdef HOME_VERSION
#include "insx014.h"
#endif
  void writeon(BOR_CONST ostream& s) const;
};
*/

class fmmt : public fmm_control
{
private:
  dvector w;
  dvector funval;
  int m;
  int diagco;
public:
  double dmin,fbest,df;
  double gmax;
  dvector gbest;
  dvector xbest;
  dvector diag;
  double eps;
  double xtol;
  double gtol;
  int nvar;
  long int iter;
  int ireturn1;
  int curriter;
  ivector iprint1;

public:
  double minimize(BOR_CONST independent_variables & x,double (*pf)(_CONST dvar_vector&));
  fmmt(int _nvar,int _m=7);

  double minimize(BOR_CONST independent_variables & x,BOR_CONST dvector& c,
        double (*pf)(BOR_CONST dvar_vector&,BOR_CONST dvector&) );

  void fmin(BOR_CONST double& f, BOR_CONST independent_variables & x,BOR_CONST dvector& g);

  dmatrix& hessian();
};

#endif //#ifndef FMMT_HPP


