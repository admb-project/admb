/*
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


          
  
#define PI 3.141592654
/* Poisson random deviates.
   \param xm Mean of Poisson distribution
   \param rng Instance of class random_number_generator.
   \return Integer-valued double drawn from the Poisson distribution with given mean.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 7

    \deprecated Scheduled for replacement by 2010.
*/
double randpoisson(double xm, BOR_CONST random_number_generator& rng)
{
  double gammln(double xx);
  static double sq,alxm,g,oldm=(-1.0);
  
  double em,t,y;

  if (xm < 12.0) {
    if (xm != oldm) {
      oldm=xm;
      g=exp(-xm);
    }
    em = -1;
    t=1.0;
    do {
      ++em;
      //t *= ran1(idum);
      t*=  y=((random_number_generator&) rng).better_rand();
    } while (t > g);
  } else {
    if (xm != oldm) {
      oldm=xm;
      sq=sqrt(2.0*xm);
      alxm=log(xm);
      g=xm*alxm-gammln(xm+1.0);
    }
    do {
      do {
        //y=tan(PI*ran1(idum));
        y=tan(PI*((random_number_generator&) rng).better_rand());
        em=sq*y+xm;
      } while (em < 0.0);
      em=floor(em);
      t=0.9*(1.0+y*y)*exp(em*alxm-gammln(em+1.0)-g);
    } while (((random_number_generator&) rng).better_rand() > t);
    //} while (ran1(idum) > t);
  }
  return em;
}
#undef PI

  void dvector::fill_randpoisson(double lambda,BOR_CONST random_number_generator& rng)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randpoisson(lambda,rng);
    }
  }



