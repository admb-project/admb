//$Id: $
DATA_SECTION
  !! ad_comm::change_datafile_name("msimple.dat");
  init_int nobs
  init_int nchunk
  vector Y(1,nobs)
  vector x(1,nobs)
  number A
  number B
  number S

  int chunk_size

 LOCAL_CALCS
    chunk_size = nobs/nchunk  + 1;
    A = 2.0;
    B = 4.0;
    S = 7.0;
    random_number_generator rng(101);
    dvector err(1,nobs);
    x.fill_randu(rng);
    x *= 100.0;
    Y = A*x + B;


    err.fill_randn(rng);
    Y += S*err;
    // for log-normal error
    //Y = elem_prod(Y,exp(S*err));

    chunk_size = nobs/nchunk;
    /*
    cout << "chunk_size = " << chunk_size << endl;
    int end_pos = 0;
    for (int kk=1;kk<=nchunk;kk++)
    {
       int start_pos = end_pos + 1;
       end_pos = start_pos+chunk_size-1;
       if (kk == nchunk)
           end_pos = nobs;
        cout << " * * * chunk " << kk << " from " << start_pos << " to " << end_pos << endl;
       dvector t = x(start_pos,end_pos);
       cout << "       t runs from " << t.indexmin() << " to " << t.indexmax() << endl;
    } 
    if (1) exit(1);
    */


PARAMETER_SECTION
  init_number a   
  init_number b   
  number s;
  vector ff(1,nchunk)
  objective_function_value f
  vector pred_Y(1,nobs);

PRELIMINARY_CALCS_SECTION
  a = 1.0;
  b = 2.0;
  crit = 1e-3;

PROCEDURE_SECTION
  #define __CHUNKY__
  #ifdef __CHUNKY__
  int end_pos = 0;
  for (int kk=1;kk<=nchunk;kk++)
  {
     int start_pos = end_pos + 1;
     end_pos = start_pos+chunk_size-1;
     if (kk == nchunk)
         end_pos = nobs;
    
     pred_Y(start_pos,end_pos) = a*x(start_pos,end_pos) + b; 

     ff(kk) = norm2(pred_Y-Y(start_pos,end_pos));
  }
  // sum the results to compute the objective function
  s = sum(ff);
  f = nobs/2.*log(s);    // make it a likelihood function so that
                         // covariance matrix is correct
  #else

  pred_Y=a*x+b;
  s=(norm2(pred_Y-Y)); 
  f=nobs/2.*log(s);    // make it a likelihood function so that
                       // covariance matrix is correct
  #endif


REPORT_SECTION
  s = sqrt(s/nobs);
  report << "A = " << A << "; B = " << B << "; S = " << S <<endl;
  report << "a = " << a << "; b = " << b << "; s = " << s << endl;
  report << "f = " << f <<endl;
  report << "nobs = " << nobs << endl;
  #ifdef __CHUNKY__
  report << "number of chunks = " << nchunk << endl;
  report << "chunk size = " << chunk_size << " elements" << endl;
  report << "           = " << chunk_size*sizeof(double) << " bytes" << endl;
  #endif
  if (nobs <= 100)
  {
     report << endl;
     report << "i,x,Y,pred_Y" << endl;
     for (int i = 1; i <= nobs; i++)
     {
        report << i << "  " << setprecision(15) << x(i) << "," << Y(i)  << "," << pred_Y(i) << endl;
      }
  }

TOP_OF_MAIN_SECTION
    arrmblsize= 25000000;
    
