// Copyright (c) 2008, 2009 Regents of the University of California.
//
// ADModelbuilder and associated libraries and documentations are
// provided under the general terms of the "BSD" license.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3.  Neither the name of the  University of California, Otter Research,
// nor the ADMB Foundation nor the names of its contributors may be used
// to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This code does the parameter estimation for the chemical kinetics
// problem discussed in Bard, Nonlinear parameter estimation, 1974,
// Academic Press, chapter 8, section 8-7 pages 233--240.
//
// Note that when using AUTODIF it is not necessary to integrate
// the sensitivity equations (page 227-229) to get the derivatives with
// respect to the model parameters for model fitting. We have used an
// implicit method for which the values of the function being integrated
// are nonlinear functions.
//
// The observations are contained in a file named "admodel.dat".
// The initial parameter estimates are in a file named "inpars"
// but they are read in from the file "admodel.par and then
// the final parameter estimates are written into a file "admodel.par".

DATA_SECTION
  init_matrix Data(1,10,1,3)
  init_vector T(1,3) // the initial temperatures for the three runs
  init_vector stepsize(1,3)  // the stepsize to use for numerical integration
  matrix data(1,3,1,10)
  matrix sample_times(1,3,1,10) // times at which reaction was sampled
  vector x0(1,3)           // the beginning time for each of the three
                           // runs
  vector x1(1,3)           // the ending time for each of the three runs
  // for each of the three runs

PARAMETER_SECTION
  init_vector theta(1,10)   // the model parameters
  matrix init_conc(1,3,1,2) // the initial concentrations of the two
                            // reactants over three time periods
  vector instrument(1,2)    // determines the response of the densitometer
  matrix y_samples(1,10,1,2)// the predicted concentrations of the two
                            // reactants at the ten sampling periods
                            // obtained by integrating the differential
                            // equations
  vector diff(1,10)         // the difference between the observed and
                            // readins of the densitometer
  objective_function_value f // the log_likelihood function
  number bayes_part         // the Bayesian contribution
  number y2
  number x_n
  vector y_n(1,2)
  vector y_n1(1,2)
  number A  // A B C D hold some common subexpressions
  number B
  number C
  number D
PRELIMINARY_CALCS_SECTION
  data=trans(Data);   // it is more convenient to work with the transformed
                   // matrix
PROCEDURE_SECTION
    int i;

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
      int nstep = (int)((x1(run)-x0(run))/stepsize(run));
      nstep++;
      double h=(x1(run)-x0(run))/nstep; // h is the stepsize for intagration

      int is=1;
      // get the initial conditions for this run
      x_n=x0(run);
      y_n=init_conc(run);
      for (i=1;i<=nstep+1;i++)
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
    for  (i=5;i<=9;i++)
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

