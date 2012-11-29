// simple example modified to include MCMC stuff
// Contributed by Ian Taylor

DATA_SECTION
  init_int nobs
  init_vector Y(1,nobs)
  init_vector x(1,nobs)

  // counter for MCMC
  int mccounter
  !! mccounter = 1;

PARAMETER_SECTION
  init_number a   
  init_number b   
  vector pred_Y(1,nobs)
  objective_function_value f

  // You must declare at least one object of type sdreport to do the mcmc calculations
  sdreport_number Number1 

PROCEDURE_SECTION
  pred_Y=a*x+b;
  f=(norm2(pred_Y-Y)); 
  f=nobs/2.*log(f);    // make it a likelihood function so that
                       // covariance matrix is correct

  if (mceval_phase() )
  {
    if(mccounter%20==0) cout<<"mccounter = "<<mccounter<<endl;

    // delete any old mcmc output files
    // may have to comment this out if -mcr is supposed to add to file
    if (mccounter==1)  remove( "posteriors.rep" ); 

    // define the mcmc output file
    ofstream posts("posteriors.rep", ios::out | ios::app);

    // add a header
    if (mccounter==1) posts<<"counter\tobj_fun\ta\tb"<< endl;
    // fill in values
    posts<<mccounter<<"\t"<<f<<"\t"<<a<<"\t"<<b<<endl;
    mccounter++;
  };
