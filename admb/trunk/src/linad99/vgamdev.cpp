/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * This file deals with the Incomplete Gamma Functions
 * of constant types. All supporting mathematical functions
 * required to compute the Inmomplete Gamma Function
 * are included. They being: log gamma,
 * and some polynomial evaluation functions.
 */
/**
 * \defgroup gammafunc
 */

#include <fvar.hpp>

double igam(const double &a, const double &x);
double igamc(const double &a, const double &x);
double lgam(double x);
int mtherr(char *s, int n)
{				
   return 0;
}

/**
 * Gamma Deviate
 * \param _x
 * \param _a
 */
dvariable gamma_deviate(const prevariable & _x, const prevariable & _a)
{
   prevariable & x = (prevariable &) (_x);
   prevariable & a = (prevariable &) (_a);

   dvariable y = cumd_norm(x);

   y = .9999 * y + .00005;

   dvariable z = inv_cumd_gamma(y, a);

   return z;
}

/**
 * A wrapper for igam
 */
static double gammp(double a, double x)
{
   return igam(a, x);
}

static double get_initial_u(double a, double y);

static double Sn(double x, double a);

#if defined(USE_LAPLACE)
#include <df1b2fun.h>
df3_two_variable cumd_gamma(const df3_two_variable & x,
			    const df3_two_variable & a);

/**
 * \param _a \f$a, \, a>0\f$
 * \param _y 
 */
dvariable inv_cumd_gamma(const prevariable & _y, const prevariable & _a)
{
   double a = value(_a);
   double y = value(_y);

   if (a < 0.05)
   {
      cerr << "a must be > 0.1" << endl;
      ad_exit(1);
   }
   double u = get_initial_u(a, y);

   double h;
   int loop_counter = 0;
   do
   {
      loop_counter++;
      double z = gammp(a, a * exp(u));
      double d = y - z;
      double log_fprime = a * log(a) + a * (u - exp(u)) - gammln(a);
      double fprime = exp(log_fprime);
      h = d / fprime;
      u += h;

      if (loop_counter > 1000)
      {
	 cerr << "Error in inv_cumd_gamma"
	    " maximum number of interations exceeded for values"
	    << endl << "  x = " << y << "  a =  " << a << "  h =  " << h <<
	    endl;
      }
   }
   while (fabs(h) > 1.e-12);

   double x = a * exp(u);
   init_df3_two_variable xx(x);
   init_df3_two_variable aa(a);
   *xx.get_u_x() = 1.0;
   *aa.get_u_y() = 1.0;

   df3_two_variable z = cumd_gamma(xx, aa);
   double F_x = 1.0 / (*z.get_u_x());
   double F_y = -F_x * (*z.get_u_y());

   dvariable vz = 0.0;
   value(vz) = x;

   gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
						       &(vz.v->x),
						       &(_y.v->x), F_x,
						       &(_a.v->x), F_y);
   return vz;
}
#endif

/**
 * Subroutine used in get_initial_u
 * \param x
 * \param a 
 */
static double Sn(double x, double a)
{
   int i = 1;
   double xp = x;
   double prod = 1.0;
   double summ = 1.0;
   double summand;
   do
   {
      prod *= (a + i);
      summand = xp / prod;
      if (summand < 1.e-4)
	 break;
      summ += summand;
      i++;
      if (i > 50)
      {
	 cerr << "convergence error" << endl;
	 ad_exit(1);
      }
   }
   while (1);
   return summ;
}

/**
 * Gets initial u value for inv_cumd_gamma
 * \param a
 * \param y 
 */
static double get_initial_u(double a, double y)
{
   const double c = 0.57721;
   // note that P = y;
   double logP = log(y);
   double logQ = log(1 - y);
   double logB = logQ + gammln(a);
   double x0 = 1.e+100;
   double log_x0 = 1.e+100;

   if (a < 1.0)
   {
      if (logB > log(.6) || (logB > log(.45) && a >= .3))
      {
	 double logu;
	 if (logB + logQ > log(1.e-8))
	 {
	    logu = (logP + gammln(1.0 + a)) / a;
	 }
         else
	 {
	    logu = -exp(logQ) / a - c;
	 }
	 double u = exp(logu);
	 x0 = u / (1 - u / (1.0 + a));
	 double tmp = log(1 - u / (1.0 + a));
	 log_x0 = logu;
	 log_x0 -= tmp;
      }
      else if (a < .3 && log(.35) <= logB && logB <= log(.6))
      {
	 double t = exp(-c - exp(logB));
	 double logt = -c - exp(logB);
	 double u = t * exp(t);
	 x0 = t * exp(u);
	 log_x0 = logt + u;
      }
      else if ((log(.15) <= logB && logB <= log(.35)) ||
		 ((log(.15) <= logB && logB <= log(.45)) && a >= .3))
      {
	 double y = -logB;
	 double v = y - (1 - a) * log(y);
	 x0 = y - (1 - a) * log(v) - log(1 + (1.0 - a) / (1.0 + v));
	 log_x0 = log(x0);
      }
      else if (log(.01) < logB && logB < log(.15))
      {
	 double y = -logB;
	 double v = y - (1 - a) * log(y);
	 x0 =
	    y - (1 - a) * log(v) -
	    log((v * v + 2 * (3 - a) * v + (2 - a) * (3 - a)) / (v * v +
								 (5 -
								  a) * v +
								 2));
	 log_x0 = log(x0);
      }
      else if (logB < log(.01))
      {
	 double y = -logB;
	 double v = y - (1 - a) * log(y);
	 x0 =
	    y - (1 - a) * log(v) -
	    log((v * v + 2 * (3 - a) * v + (2 - a) * (3 - a)) / (v * v +
								 (5 -
								  a) * v +
								 2));
	 log_x0 = log(x0);
      }
      else
      {
	 cerr << "this can't happen" << endl;
	 ad_exit(1);
      }
   }
   else if (a >= 1.0)
   {
      const double a0 = 3.31125922108741;
      const double b1 = 6.61053765625462;
      const double a1 = 11.6616720288968;
      const double b2 = 6.40691597760039;
      const double a2 = 4.28342155967104;
      const double b3 = 1.27364489782223;
      const double a3 = .213623493715853;
      const double b4 = .03611708101884203;

      int sgn = 1;
      double logtau;
      if (logP < log(0.5))
      {
	 logtau = logP;
	 sgn = -1;
      }
      else
      {
	 logtau = logQ;
	 sgn = 1;
      }

      double t = sqrt(-2.0 * logtau);

      double num = (((a3 * t + a2) * t + a1) * t) + a0;
      double den = ((((b4 * t + b3) * t + b2) * t) + b1) * t + 1;
      double s = sgn * (t - num / den);
      double s2 = s * s;
      double s3 = s2 * s;
      double s4 = s3 * s;
      double s5 = s4 * s;
      double roota = sqrt(a);
      double w =
	 a + s * roota + (s2 - 1) / 3.0 + (s3 - 7.0 * s) / (36. * roota) -
	 (3.0 * s4 + 7.0 * s2 - 16) / (810.0 * a) + (9.0 * s5 +
						     256.0 * s3 -
						     433.0 * s) /
	 (38880.0 * a * roota);
      if (logP < log(0.5))
      {
	 if (w > .15 * (a + 1))
	 {
	    x0 = w;
	 }
         else
	 {
	    double v = logP + gammln(a + 1);
	    double u1 = exp(v + w) / a;
	    double S1 = 1 + u1 / (a + 1);
	    double u2 = exp((v + u1 - log(S1)) / a);
	    double S2 = 1 + u2 / (a + 1) + u2 * u2 / ((a + 1) * (a + 2));
	    double u3 = exp((v + u2 - log(S2)) / a);
	    double S3 = 1 + u3 / (a + 1) + u3 * u3 / ((a + 1) * (a + 2))
	       + u3 * u3 * u3 / ((a + 1) * (a + 2) * (a + 3));
	    double z = exp((v + u3 - log(S3)) / a);
	    if (z < .002 * (a + 1.0))
	    {
	       x0 = z;
	    }
            else
	    {
	       double sn = Sn(z, a);
	       double zbar = exp((v + z - log(sn)) / a);
	       x0 =
		  zbar * (1.0 -
			  (a * log(zbar) - zbar - v + log(sn)) / (a -
								  zbar));
	    }

	 }
	 log_x0 = log(x0);
      }
      else
      {
	 double u =
	    -logB + (a - 1.0) * log(w) - log(1.0 + (1.0 - a) / (1 + w));
	 x0 = u;
	 log_x0 = log(x0);
      }
   }
   if (a == 1.0)
   {
      x0 = -log(1.0 - y);
      log_x0 = log(x0);
   }
   return log_x0 - log(a);
}
