/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009 ADMB Foundation
 */
#include "fvar.hpp"


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


  random_number_generator::random_number_generator(int seed) :
    idum2(123456789), iy(0), iv(0,NTAB-1)
  {
    if (seed<0)
      xdum=seed;
    else if (seed>0)
      xdum=-seed;
    else
      xdum=-14528;
    better_rand();
  }

  void random_number_generator::reinitialize(int seed)
  {
    if (seed<0)
      xdum=seed;
    else if (seed>0)
      xdum=-seed;
    else
      xdum=-14528;

    idum2=123456789;
    iy=0;
    iv=0;
    better_rand();
  }

/** Random number generator.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

    \deprecated Scheduled for replacement by 2010.
*/
double random_number_generator::better_rand() 
{
  long int * idum= (&xdum);
	long int j;
	long k;
	double temp;

	if (*idum <= 0) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		idum2=(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ1;
			*idum=IA1*(*idum-k*IQ1)-k*IR1;
			if (*idum < 0) *idum += IM1;
			if (j < NTAB) iv(j) = *idum;
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
	iy=iv(j)-idum2;
	iv(j) = *idum;
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


          
double randn( BOR_CONST random_number_generator& rng)
{
  double x,y;
  x=((random_number_generator&) rng).better_rand();
  y=((random_number_generator&) rng).better_rand();
  double u=sqrt(-2*log(x))*cos(2*3.14159*y);
  return(u);
}
  
double randu( BOR_CONST random_number_generator& rng)
{
  double x;
  x=((random_number_generator&) rng).better_rand();
  return(x);
}
  

  void dvector::fill_randbi(double p, BOR_CONST random_number_generator& rng)
  {
    if ( p<0 || p>1)
    {
      cerr << "Error in dvar_vector::fill_randbi proportions of"
       " successes must lie between 0 and 1\n";
      ad_exit(1);
    }
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      if ( ((random_number_generator&) rng).better_rand()<=p)
      {
        elem(i)=1;
      }
      else
      {
        elem(i)=0;
      } 
    }
  }


  void dvector::fill_randu( BOR_CONST random_number_generator& rng)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=((random_number_generator&) rng).better_rand();
    }
  }

  void dmatrix::colfill_randu(BOR_CONST int&j, BOR_CONST random_number_generator& rng)
  {
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=((random_number_generator&) rng).better_rand();
    }
  }


  void dmatrix::rowfill_randu(BOR_CONST int& i, BOR_CONST random_number_generator& rng)
  {
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=((random_number_generator&) rng).better_rand();
    }
  }


  void dvector::fill_randn( BOR_CONST random_number_generator& rng)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      (*this)(i)=randn(rng);
    }
  }

  void dmatrix::fill_randn( BOR_CONST random_number_generator& rng)
  {
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randn(rng);
    }
  }

  void d3_array::fill_randn( BOR_CONST random_number_generator& rng)
  {
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randn(rng);
    }
  }

  void d3_array::fill_randu( BOR_CONST random_number_generator& rng)
  {
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randu(rng);
    }
  }

  void dmatrix::fill_randu( BOR_CONST random_number_generator& rng)
  {
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randu(rng);
    }
  }


  void dmatrix::colfill_randn(BOR_CONST int&j, BOR_CONST random_number_generator& rng)
  {
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=randn(rng);
    }
  }


  void dmatrix::rowfill_randn(BOR_CONST int& i, BOR_CONST random_number_generator& rng)
  {
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=randn(rng);
    }
  }



