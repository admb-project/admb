//$Id: msimple.tpl 3054M 2013-01-11 20:23:43Z (local) $

GLOBALS_SECTION
  #include <pthread.h>
  #include <fvar.hpp>
  #include <adthread.h>

 
  // write the function to run on the threads
  void simple_thread(void * ptr)
  {
      // cast the pointer to the propper type
      new_thread_data * tptr = (new_thread_data *) ptr;

      // set up the gradient stack for the thread
      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
      gradient_structure::set_CMPDIF_BUFFER_SIZE   (20000000);
      gradient_structure gs(30000000);
   
      // get the thread number
      ad_comm::pthread_manager->set_slave_number(tptr->thread_no);

    
      // take control of the constant buffer for reading
      ad_comm::pthread_manager->cread_lock_buffer(0);
      // read the independent variables IN THE SAME ORDER AS THEY ARE SENT
      dvector x = ad_comm::pthread_manager->get_dvector(0);
      cerr << " * * *  got x chunk " << tptr->thread_no << " from " << x.indexmin() << " to " << x.indexmax() << endl;
      dvector Y = ad_comm::pthread_manager->get_dvector(0);
      cerr << " * * *  got Y chunk " << tptr->thread_no << " from " << Y.indexmin() << " to " << Y.indexmax() << endl;
     // release the constant buffer
      ad_comm::pthread_manager->cread_unlock_buffer(0);

      do
      {
         // take control of the variable buffer for reading
         ad_comm::pthread_manager->read_lock_buffer(0);
         // read the finished signal
         int lflag=ad_comm::pthread_manager->get_int(0);
         if (lflag == 0) break;
         // read current values of parameters
         dvariable a =ad_comm::pthread_manager->get_dvariable(0);
         dvariable b =ad_comm::pthread_manager->get_dvariable(0);
         // release the variable buffer
         ad_comm::pthread_manager->read_unlock_buffer(0);

         // allocate the dependent variable to be the same shape as x
         dvar_vector pred_Y(x.indexmin(),x.indexmax());

         // compute dependent variable
         pred_Y = a * x +  b;
         // compute likelihood
         dvariable f=norm2(pred_Y-Y); 
   
         // send results to master
         // take control of the variable buffer for sending
         ad_comm::pthread_manager->write_lock_buffer(0);
         // send f
         ad_comm::pthread_manager->send_dvariable(f, 0);
         // release the variable buffer
         ad_comm::pthread_manager->write_unlock_buffer(0);
   
         // compute derivative contribution for this thread 
         slave_gradcalc();
      }
      while (1);
      // close thread
      pthread_exit(ptr);
   }


DATA_SECTION
  init_int nobs
  init_int nthread
  vector Y(1,nobs)
  vector x(1,nobs)
  number A
  number B
  number S

  int chunk_size

 LOCAL_CALCS
    chunk_size = nobs/nthread  + 1;
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
    chunk_size = nobs/nthread;
    // for log-normal error
    //Y = elem_prod(Y,exp(S*err));

    /*
    cout << "chunk_size = " << chunk_size << endl;
    int end_pos = 0;
    for (int kk=1;kk<=nthread;kk++)
    {
       int start_pos = end_pos + 1;
       end_pos = start_pos+chunk_size-1;
       if (kk == nthread)
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
  vector ff(1,nthread)
  objective_function_value f

PRELIMINARY_CALCS_SECTION
  a = 1.0;
  b = 2.0;
  crit = 1e-3;

  // number of thread groups
  int ngroups=1;
  ivector ng(1,ngroups);
  // number of threads in group 1
  ng(1)=nthread;

  // create instance of pthread_manager class
  // third argument is number of bytes in the transfer buffer
  //ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,500);
  ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,32005);

  // create data vecor for argument to thread function
  new_thread_data* data1 = new new_thread_data[nthread+1];
  for (int i=1;i<=nthread;i++)
  {
    data1[i].thread_no = i; // only the thread number is imortant
    //data1[i].m=0;           // not used
  }

  // specifiy function to run on the threads by passing apointer to the function
  ad_comm::pthread_manager->attach_code(&simple_thread);
  // create the threads
  ad_comm::pthread_manager->create_all(data1);

  
  // send constant data to the threads;
  // in this case rows of the independent variables
  int end_pos = 0;
  for (int kk=1;kk<=nthread;kk++)
  {
     int start_pos = end_pos + 1;
     end_pos = start_pos+chunk_size-1;
     if (kk == nthread)
         end_pos = nobs;

     // take control of the constant buffer for sending
     ad_comm::pthread_manager->cwrite_lock_buffer(kk);
     // send x and Y
     cerr << " * * * send x chunk " << kk << " from " << start_pos << " to " << end_pos << endl;
     ad_comm::pthread_manager->send_dvector(x(start_pos,end_pos),kk);
     cerr << " * * * send Y chunk " << kk << " from " << start_pos << " to " << end_pos << endl;
     ad_comm::pthread_manager->send_dvector(Y(start_pos,end_pos),kk);
     // release the constant buffer
     ad_comm::pthread_manager->cwrite_unlock_buffer(kk);
  }

PROCEDURE_SECTION
  // send variable data to threads
  for (int kk=1;kk<=nthread;kk++)
  {
     // take control of the variable buffer for sending
     ad_comm::pthread_manager->write_lock_buffer(kk);
     // signal the thread that we are not finished
     ad_comm::pthread_manager->send_int(1,kk); 
     // send current values of parameters
     ad_comm::pthread_manager->send_dvariable(a,kk); 
     ad_comm::pthread_manager->send_dvariable(b,kk); 
     // release the variable buffer
     ad_comm::pthread_manager->write_unlock_buffer(kk);
  
  }

  // get results of thread computations
  for (int kk=1;kk<=nthread;kk++)
  {
      // take control of the variable buffer for reading
      ad_comm::pthread_manager->read_lock_buffer(kk);
      ff(kk) = ad_comm::pthread_manager->get_dvariable(kk);
     // release the variable buffer
      ad_comm::pthread_manager->read_unlock_buffer(kk);
  }
  // sum the results to compute the objective function
  s = sum(ff);
  f = nobs/2.*log(s);    // make it a likelihood function so that
                         // covariance matrix is correct


REPORT_SECTION
  s = sqrt(s/nobs);
  report << "A = " << A << "; B = " << B << "; S = " << S <<endl;
  report << "a = " << a << "; b = " << b << "; s = " << s << endl;
  report << "f = " << f <<endl;
  report << "nobs = " << nobs << endl;
  report << "number of threads = " << nthread << endl;
  report << "chunk size = " << chunk_size << " elements" << endl;
  report << "           = " << chunk_size*sizeof(double) << " bytes" << endl;
  if (nobs <= 100)
  {
     report << endl;
     report << "i,x,Y" << endl;
     for (int i = 1; i <= nobs; i++)
     {
        report << i << "  " << setprecision(15) << x(i) << "," << Y(i) << endl;
      }
  }

  /*
  removed until pthread_manager destructor finalized
  FINAL_SECTION
    for (int k = 1; k <= nthread;k++)
    {
      ad_comm::pthread_manager->write_lock_buffer(k);
      ad_comm::pthread_manager->send_int(0,k);
      ad_comm::pthread_manager->write_unlock_buffer(k);
    }
    sleep(1);
    delete ad_comm::pthread_manager;
    ad_comm::pthread_manager=0;
  */
