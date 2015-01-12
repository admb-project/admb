/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>


#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
/** Random number generator.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

    \deprecated Scheduled for replacement by 2010.
*/
double better_rand(long int &pidum)
{
  long int * idum=&pidum;
	long int j;
	long k;
	static long idum2=123456789;
	static long iy=0;
	static long iv[NTAB];
	double temp;

	if (*idum <= 0) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		idum2=(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ1;
			*idum=IA1*(*idum-k*IQ1)-k*IR1;
			if (*idum < 0) *idum += IM1;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ1;
	*idum=IA1*(*idum-k*IQ1)-k*IR1;
	if (*idum < 0) *idum += IM1;
	k=idum2/IQ2;
	idum2=IA2*(idum2-k*IQ2)-k*IR2;
	if (idum2 < 0) idum2 += IM2;
	j=iy/NDIV;
	iy=iv[j]-idum2;
	iv[j] = *idum;
	if (iy < 1) iy += IMM1;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX
/* (C) Copr. 1986-92 Numerical Recipes Software 888888888888. */
/*
double better_rand(long int& idum)
{
   long int im1=2147483563;
   long int im2=2147483399;
   double am=1./im1;
   long int imm1=im1-1;
   long int ia1=40014;
   long int ia2=40692;
   long int iq1=53668;
   long int iq2=52774;
   long int ir1=12211;
   long int ir2=3791;
   long int ntab=32;
   long int ndiv=1+imm1/ntab;
   double eps=1.2e-8;
   double rnmax=1.-eps;
  static long int idum2;
  long int k;
  static ivector iv(1,ntab);
  static int iy;
  int j;
  if (idum<=0) 
  {
    idum2=123456789;
    iy=0;
    iv.initialize();
    cout << setprecision(12) << rnmax << endl;
    if (-idum>1) 
    {
      idum=-idum;
    }
    else
    {
      idum=1;
    }
    idum2=idum;
    for (j=ntab+8;j>=1;j--)
    {
      k=idum/iq1;
      idum=ia1*(idum-k*iq1)-k*ir1;
      if (idum<=0) idum+=im1;
      if (j<=ntab) iv(j)=idum;
    }
    iy=iv(1);
  }
  k=idum/iq1;
  idum=ia1*(idum-k*iq1)-k*ir1;
  if (idum<0) idum+=im1;
  k=idum2/iq2;
  idum2=ia2*(idum2-k*iq2)-k*ir2;
  if (idum2<0) idum2+=im2;
  j=1+iy/ndiv;
  iy=iv(j)-idum2;
  iv(j)=idum;
  if (iy<1)iy+=imm1;
  double rr=am*iy;
  if (rr>rnmax)
  {
    rr=rnmax;
  }
  return rr;
}
*/
 
