#include <fvar.hpp>

// Reserve some stack for this program
extern unsigned _stklen = 40000;

// Include the function prototypes for user's functions
   void xinit(double alpha,double cutoff,independent_variables x);

 void users_function(double& f,dvector OBS_Y,dvector OBS_X, fvar_array x,
   int nobs, int print_switch, fmm&);

 void reset(fvariable& alpha,fvariable& cutoff,fvar_array& x);

 void get_predictions(fvariable alpha,int nobs,fvar_array PRED_Y, 
   dvector OBS_X);

 main()
 {
   int nobs=20;
   int nvar=2;

   double cutoff=0;
   double alpha=0;
   double f;

   dvector OBS_Y(1,nobs);
   dvector OBS_X(1,nobs);
   dvector g(1,nvar);

   independent_variables x(1,nvar);

   // ``Create'' the data for the model
   //  Y = 5*x + 25;
   for (int i=1;i<=nobs; i++)
   {
     OBS_X[i]=i;
     OBS_Y[i]=5*i+25;
   }

   //Put some errors into the OBS_Y
   int sgn=1;
   for (i=1;i<=nobs; i++)
   {
     sgn=-1*sgn;
     OBS_Y[i]=OBS_Y[i]+sgn*2;
   }
   // Add one large error to OBS_Y[5]
     OBS_Y[20]=OBS_Y[20]+5000;


   // Get the initial x values
   xinit(alpha,cutoff,x);

   // An object of type gradient structure must be declared to that
   // the data structures for managing the derivative calculations
   // will be created

   gradient_structure gs;

   // When the function
   // minimizer completes the job it will set fmc.ireturn to a negative
   // value
   {
     // fmc is a structure which contains parameters to control the
     // behaviour of the function minimizer. The control parameters
     // have default values which can be changed by the user
     fmm fmc(nvar);

     while (fmc.ireturn >=0)
     {
       fmc.fmin(f,x,g);

       if (fmc.ireturn > 0)
       {
	 {
	   users_function(f,OBS_Y,OBS_X,x,nobs,0,fmc);
	 }
	 gradcalc(nvar,g);
       }
     }
     // Call the function one more time to print out the final parameter
     // estimates
     users_function(f,OBS_Y,OBS_X,x,nobs,1,fmc);
   }
 }
