#include <admodel.h>

#include <chem-eng.htp>

model_data::model_data()
{
  Data.allocate(1,10,1,3,"Data");
  T.allocate(1,3,"T");
  stepsize.allocate(1,3,"stepsize");
  data.allocate(1,3,1,10);
  sample_times.allocate(1,3,1,10);
  x0.allocate(1,3);
  x1.allocate(1,3);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 ad_comm(argc,argv), model_data() , function_minimizer(sz)
{
  initializationfunction();
  theta.allocate(1,10,"theta");
  init_conc.allocate(1,3,1,2,"init_conc");
  #ifndef NO_AD_INITIALIZE
    init_conc.initialize();
  #endif
  instrument.allocate(1,2,"instrument");
  #ifndef NO_AD_INITIALIZE
    instrument.initialize();
  #endif
  y_samples.allocate(1,10,1,2,"y_samples");
  #ifndef NO_AD_INITIALIZE
    y_samples.initialize();
  #endif
  diff.allocate(1,10,"diff");
  #ifndef NO_AD_INITIALIZE
    diff.initialize();
  #endif
  f.allocate("f");
  bayes_part.allocate("bayes_part");
  #ifndef NO_AD_INITIALIZE
  bayes_part.initialize();
  #endif
  y2.allocate("y2");
  #ifndef NO_AD_INITIALIZE
  y2.initialize();
  #endif
  x_n.allocate("x_n");
  #ifndef NO_AD_INITIALIZE
  x_n.initialize();
  #endif
  y_n.allocate(1,2,"y_n");
  #ifndef NO_AD_INITIALIZE
    y_n.initialize();
  #endif
  y_n1.allocate(1,2,"y_n1");
  #ifndef NO_AD_INITIALIZE
    y_n1.initialize();
  #endif
  A.allocate("A");
  #ifndef NO_AD_INITIALIZE
  A.initialize();
  #endif
  B.allocate("B");
  #ifndef NO_AD_INITIALIZE
  B.initialize();
  #endif
  C.allocate("C");
  #ifndef NO_AD_INITIALIZE
  C.initialize();
  #endif
  D.allocate("D");
  #ifndef NO_AD_INITIALIZE
  D.initialize();
  #endif
}

void model_parameters::preliminary_calculations(void)
{
  data=trans(Data);   // it is more convenient to work with the transformed
                   // matrix
}

void model_parameters::userfunction(void)
{
    // set up the begining and ending times for the three runs
    x0(1)=0;
    x1(1)=90;
    x0(2)=0;
    x1(2)=18;
    x0(3)=0;
    x1(3)=4.5;
    // set up the sample times for each of the three runs
    sample_times(1).fill_seqadd(0,10);  // fill with 0,10,20,...,90
    sample_times(2).fill_seqadd(0,2);   // fill with 0,2,4,...,18
    sample_times(3).fill_seqadd(0,0.5); // fill with 0,0.5,1.0,...,4.5
    // set up the initial concentrations of the two reactants for
    // each of the three runs
    init_conc(1,1)=theta(5);
    init_conc(1,2)=theta(6);
    init_conc(2,1)=theta(7);
    init_conc(2,2)=0.0;     // the initial concentrations is known to be 0
    init_conc(3,1)=0.0;     // the initial concentrations is known to be 0
    init_conc(3,2)=theta(8);
    // coefficients which determine the response of the densitometer
    instrument(1)=theta(9);
    instrument(2)=theta(10);
    f=0;
    for (int run=1;run<=3;run++)
    {
       // integrate the differential equations to get the predicted
       // values for the y_samples
      int nstep=(x1(run)-x0(run))/stepsize(run);
      nstep++;
      double h=(x1(run)-x0(run))/nstep; // h is the stepsize for intagration
      int is=1;
      // get the initial conditions for this run
      x_n=x0(run);
      y_n=init_conc(run);
      for (int i=1;i<=nstep+1;i++)
      {
        // gather common subexpressions
        y2=y_n(2)*y_n(2);
        A=theta(1)*exp(-theta(2)/T(run));
        B=exp(-1000/T(run));
        C=(1.0+theta(3)*exp(-theta(4)/T(run))*y_n(1));
        C=C*C;
        D=h*A/C;
        // get the y vector for the next time step
        y_n1(1)=(y_n(1)+D*B*y2)/(1+D);
        y_n1(2)=(y_n(2)+2*D*y_n(1))/(1+(2*D*B*y_n(2)));
        // if an observation occurred during this time period save
        // the predicted value
        if (is <=10)
        {
          if (x_n<=sample_times(run,is) && x_n+h >= sample_times(run,is))
          {
            y_samples(is++)=y_n;
          }
        }
        x_n+=h;  // increment the time step
        y_n=y_n1; // update the value of y_n for the next step
      }
      diff=(1+y_samples*instrument)-data(run);
      f+=diff*diff;
    }
    f=15*log(f); // this is (number of obs)/2 it is wrong in Bard (pg 236).
    // Add the Bayesian stuff
    bayes_part=0.0;
    for  (int i=5;i<=9;i++)
    {
      bayes_part+=(theta(i)-1)*(theta(i)-1); 
    }
    bayes_part+=(theta(10)-2)*(theta(10)-2);
    f+=1./(2*.05*.05)*bayes_part;
    // add penalties to keep first four parameters > 0
    // Bard remarks that this is necessary pg 238
    for  (i=1;i<=4;i++)
    {
      if (theta(i)<=0.0)
      {
        f+=1000.*theta(i)*theta(i);
      }
    }
}

  model_data::~model_data(){}

void model_parameters::report(void){}

void function_minimizer::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__)  || \
     defined(__MSVC32__)
    if (!arrmblsize) arrmblsize=150000;
  #else
    if (!arrmblsize) arrmblsize=25000;
  #endif
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.computations(argc,argv);
  return 0;
}
