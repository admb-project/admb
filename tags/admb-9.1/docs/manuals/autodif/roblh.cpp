
#include <stdio.h>
#include <stdlib.h>

#ifdef _ZORTECH
   #include <stream.hpp>
#else
   #include <iostream.h>
   #include <fstream.h>
#endif

#include <dos.h>

#include "fvar.hpp"


fvariable robust_reg_likelihood(dvector, fvar_array, fvariable robpar,
  fvariable& sigma,  double pcon, double width);

int roblh( int nobs,  dvector& observed_effort, dvector& observed_catch,
     fvar_array& eps, dvector& p0, dvector& p1, dvector& p2, fvariable& alpha,
     fvariable& beta,fvariable& catchability, fvariable& binit,
     fvariable& a, fvariable& b, fvariable& robpar, double& f,fvar_array x,
     int print_switch);

extern unsigned _stklen = 40000;

// Includes the function prototypes for user's functions

 void reset(fvariable& alpha,fvariable& beta,fvariable& binit,fvariable& a,
       fvariable& b, fvariable& catchability, fvar_array& eps, 
       fvariable& robpar, fvar_array& x, int nobs,fvariable& z);

 lhmodel(int nobs,  dvector& observed_effort, dvector& observed_catch,
     fvar_array& eps, dvector& p0, dvector&, dvector& p1, fvariable& alpha,
     fvariable& beta,fvariable& catchability, fvariable& binit,
     fvariable& a, fvariable& b ,fvariable& robpar, double& f, 
     fvar_array x, int print_switch);

  void xinit(double alpha,double beta,double binit,double a, double b,
     double catchability, dvector eps, double robpar,
     independent_variables& x, int nobs);

 main()
 {

   double alpha;
   double beta;
   double catchability;
   double binit;
   double a;
   double b;
   double f;
   double robpar;

   // Open the file lhmodel.dat for reading as an ifstream
   ifstream catch_data("lhmodel.dat");

   // Read in the number of observations -- they determine the
   // size of the arrays used in the program.
   int nobs;
   catch_data >> nobs;

   dvector observed_effort(1,nobs);
   dvector observed_catch(1,nobs);
   dvector eps(1,nobs);
   dvector p0(1,nobs);
   dvector p1(1,nobs);
   dvector p2(1,nobs);

   catch_data >> observed_catch;
   catch_data >> observed_effort;

   catch_data.close();

   // Calculate the first 2 orthogonal polynomials used for removing the
   // ``low frequencies'' from the deviations in the effort fishing
   // mortality relationship

   for (int i=1; i<=nobs; i++)
   {
     p0[i]=1.;
     p1[i]=i;
     p2[i]=i*i;
   }

   p0=1./(pow(p0*p0,.5))*p0;

   p1=p1-(p0*p1)*p0;
   p1=1./(pow(p1*p1,.5))*p1;

   p2=p2-(p0*p2)*p0-(p1*p2)*p1;
   p2=1./(pow(p2*p2,.5))*p2;

   {
     ifstream par("roblh.par");
     par >> alpha >> beta >> binit >>catchability >> a >> b >> eps >> robpar;
   }

   // The number of active parameters is equal to nobs + 7.
   int nvar=nobs+7;

   {

     // an object of type gradient_structure must be defined
     // before any variable AUTODIF types

     gradient_structure gs;

     // The independent variables must be defined to be of type
     // independent_variables.
     independent_variables x(1,nvar);
     dvector g(1,nvar);
     dvector g1(1,nvar);

     // Get the initial x values
     xinit(alpha, beta,binit,a,b,catchability,eps,robpar,x,nobs);

     // fmc is a structure which contains parameters to control the
     // behaviour of the function minimizer. The control parameters
     // have default values which can be changed by the user
     fmm fmc(nvar);

     // set the maximum number of function evaluations to 2000
     fmc.maxfn=2000;

     // The function minimizer will print out the current active
     // parameter estimates every 10 iterations.
     fmc.iprint=10;

     int n;

     int j=1;

     while (fmc.ireturn >=0)
     {
        fmc.fmin(f,x,g);

	if (fmc.ireturn > 0)
	{
	  {
	    roblh(nobs,observed_effort,observed_catch,eps,p0,p1,p2,alpha,
	      beta,catchability,binit,a,b,robpar,f,x,0);

	  }
	  gradcalc(nvar,g);
	}
      }

      // Call the function one more time to print out the final parameter
      // estimates
      roblh(nobs,observed_effort,observed_catch,eps,p0,p1,p2,alpha,
        beta,catchability,binit,a,b,robpar,f,x,1);

    }
  }


 roblh( int nobs,  dvector& observed_effort, dvector& observed_catch,
     fvar_array& eps, dvector& p0, dvector& p1, dvector& p2, fvariable& alpha,
     fvariable& beta,fvariable& catchability, fvariable& binit,
     fvariable& a, fvariable& b, fvariable& robpar, double& f,fvar_array x, 
     int print_switch)
 {
   fvar_array eta(1,nobs);   
   fvar_array survival(1,nobs);   
   fvar_array biomass(1,nobs);   
   fvar_array catch(1,nobs);
   fvariable proj0;
   fvariable proj1;
   fvariable proj2;
   fvariable penalty_weight;
   fvariable z;
   int i;
   penalty_weight=2;
   fvariable sigma;
   reset( alpha, beta, binit, a, b, catchability , eps,robpar,  x, nobs, z);

   proj0=eps*p0;
   proj1=eps*p1;
   proj2=eps*p2;

   eta = eps - proj0 * p0 - proj1 * p1 - proj2 * p2;
   eta = eta + a*p1 +b*p2;


   for (i=1; i<=nobs; i++)
   {
     survival[i] = .000001 +
		 exp( -catchability*(observed_effort[i]*exp(eta[i])) );
   }

   biomass[1]=binit;
   for (i=1; i<nobs; i++)
   {
     biomass[i+1] = alpha*survival[i]*biomass[i]*
			exp(-beta*(biomass[i]/biomass[1]-1));
   }


   for (i=1; i<=nobs; i++)
   {
     catch[i]=.000001 + (1.-survival[i])*biomass[i];
   }

   // Use the robust regression routine
   z+= robust_reg_likelihood(log(observed_catch), log(catch), robpar,
	 sigma);

   fvariable variance=sigma*sigma;

   z+=penalty_weight * (eta*eta)/sigma;

   z+=proj0*proj0;

   z+=proj1*proj1;

   z+=proj2*proj2;

   z=1000*z;

   f = varpart(z);

   // print out the results at the end

   if (print_switch == 1)
   {
     cout << "Estimated initial biomass " << varpart(binit) << "\n";
     cout << "Estimated catchability " << varpart(catchability) << "\n";
     cout << "LH model alpha = " << varpart(alpha);
     cout << " beta = " << varpart(beta) << "\n\n";
     cout << "predicted catch  observed catch  eta    eps    biomass\n";

     int old_width=cout.width(12);
     for (i=1; i<=nobs; i++)
     {
       cout.precision(2);
       cout.width(12);
       cout  << catch[i];
       cout.width(12);
       cout.precision(2);
       cout << observed_catch[i];
       cout.width(12);
       cout.precision(4);
       cout << eta[i];
       cout.width(8);
       cout.precision(4);
       cout << eps[i];
       cout.width(12);
       cout.precision(2);
       cout << biomass[i];
       cout << "\n";
     }
     cout.width(old_width);
     {
       ofstream par("roblh.par");
       par << alpha << " " << beta << " "  << binit << " "
	   << catchability << " " << a << " " << b << endl
	   << eps  << endl << robpar;
     }


   }
   return(0);
 }

   void xinit(double alpha,double beta,double binit,double a, double b,
     double catchability, dvector eps, double robpar,
     independent_variables& x, int nobs)
   {
     int ii=1;
     x[ii]=boundpin(robpar,0.05,1.);
     ii++;
     x[ii]=pow(alpha,.5);
     ii++;
     x[ii]=boundpin(beta,0.0,25.0);
     ii++;
     x[ii]=pow(binit,.5);
     ii++;
     x[ii]=a;
     ii++;
     x[ii]=b;
     ii++;
     x[ii]=boundpin(catchability,0.,1.);
     ii++;

     for (int i=1; i<=nobs; i++)
     {
       x[ii]=boundpin(eps[i],-2.,2.);
       ii++;
     }
  }

   void reset(fvariable& alpha,fvariable& beta,fvariable& binit,fvariable& a,
       fvariable& b, fvariable& catchability, fvar_array& eps, 
       fvariable& robpar, fvar_array& x, int nobs,fvariable& z)
   {
     int ii=1;
     robpar=boundp(x[ii],0.05,1.0,z);
     ii++;
     alpha=x[ii]*x[ii]+.0000001;
     ii++;
     beta=boundp(x[ii],0.0,25.0,z);
     ii++;
     binit=x[ii]*x[ii];
     ii++;
     a=x[ii];
     ii++;
     b=x[ii];
     ii++;
     catchability=boundp(x[ii],0.,1.,z);
     ii++;

     for (int i=1; i<=nobs; i++)
     {
       eps[i]=boundp(x[ii],-2.,2.,z);
       ii++;
     }
  }



