/*
 * $Id$
 *
 * Author: David Fournier
 * copyright (c) 2009 ADMB foundation
 */

#include <admodel.h>
#include <math.h>
#define NRANSI
//#include "nrutil.h"
#define NMAX 5000

/** \def GET_PSUM
  Computes psum.
*/
#define GET_PSUM \
          for (j=1;j<=ndim;j++) {\
          for (sum=0.0,i=1;i<=mpts;i++) sum += p[i][j];\
          psum[j]=sum;}

/** \def SWAP(a,b)
  Reverses a and b
*/
#define SWAP(a,b) {swap=(a);(a)=(b);(b)=swap;}


/** Nelder-Mead simplex alogrithm.
  \param _p Matrix
  \param _y Vector
  \param ndim Integer
  \param ftol Double
  \param nfunk Integer

  \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 10
*/
void function_minimizer::adamoeba(BOR_CONST dmatrix& _p, BOR_CONST dvector& _y, int ndim,
  double ftol,int nfunk)
{
  dmatrix& p=(dmatrix&) _p;
  dvector& y=(dvector&) _y;
  int i,ihi,ilo,inhi,j,mpts=ndim+1;
  double rtol,sum,swap,ysave,ytry;

  dvector psum(1,ndim);
  nfunk=0;
  GET_PSUM
  for (;;) {
    ilo=1;
    ihi = y[1]>y[2] ? (inhi=2,1) : (inhi=1,2);
    for (i=1;i<=mpts;i++) {
      if (y[i] <= y[ilo]) ilo=i;
      if (y[i] > y[ihi]) {
        inhi=ihi;
        ihi=i;
      } else if (y[i] > y[inhi] && i != ihi) inhi=i;
    }
    rtol=2.0*fabs(y[ihi]-y[ilo])/(fabs(y[ihi])+fabs(y[ilo]));
    if (rtol < ftol) {
      SWAP(y[1],y[ilo])
      for (i=1;i<=ndim;i++) SWAP(p[1][i],p[ilo][i])
      break;
    }
    if (nfunk >= NMAX)
    {
	cerr << "NMAX exceeded" << endl;
    }
    nfunk += 2;
    ytry=amxxx(p,y,psum,ndim,ihi,-1.0);
    if (ytry <= y[ilo])
      ytry=amxxx(p,y,psum,ndim,ihi,2.0);
    else if (ytry >= y[inhi]) {
      ysave=y[ihi];
      ytry=amxxx(p,y,psum,ndim,ihi,0.5);
      if (ytry >= ysave) {
        for (i=1;i<=mpts;i++) {
          if (i != ilo) {
            for (j=1;j<=ndim;j++)
              p[i][j]=psum[j]=0.5*(p[i][j]+p[ilo][j]);
	      
            dvariable vf=0.0;
            vf=initial_params::reset(dvar_vector(psum));
            *objective_function_value::pobjfun=0.0;
            userfunction();
            vf+=*objective_function_value::pobjfun;

            y[i]=value(vf);

          }
        }
        nfunk += ndim;
        GET_PSUM
      }
    } else --(nfunk);
  }
}
#undef SWAP
#undef GET_PSUM
#undef NMAX
#undef NRANSI
#define NRANSI

double function_minimizer::amxxx(BOR_CONST dmatrix& _p, BOR_CONST dvector& _y, BOR_CONST dvector& _psum, int ndim,
  int ihi, double fac)
{
  dmatrix& p=(dmatrix&) _p;
  dvector& y=(dvector&) _y;
  dvector& psum=(dvector&) _psum;
	int j;
	double fac1,fac2,ytry;

	dvector ptry(1,ndim);
	fac1=(1.0-fac)/ndim;
	fac2=fac1-fac;
	for (j=1;j<=ndim;j++) ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;


        dvariable vf=0.0;
        vf=initial_params::reset(dvar_vector(ptry));
        *objective_function_value::pobjfun=0.0;
        userfunction();
        vf+=*objective_function_value::pobjfun;
	ytry=value(vf);

	if (ytry < y[ihi]) {
		y[ihi]=ytry;
		for (j=1;j<=ndim;j++) {
			psum[j] += ptry[j]-p[ihi][j];
			p[ihi][j]=ptry[j];
		}
	}
	return ytry;
}
#undef NRANSI
