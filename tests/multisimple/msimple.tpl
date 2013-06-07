//$Id: msimple.tpl 3054M 2013-01-11 20:23:43Z (local) $

GLOBALS_SECTION
  #include <pthread.h>
  #include <fvar.hpp>
  #include <adthread.h>
 
  void simple_thread(void * ptr)
  {
      new_thread_data * tptr = (new_thread_data *) ptr;

      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
      gradient_structure::set_CMPDIF_BUFFER_SIZE   (20000000);
      gradient_structure gs(10000000);
   
      ad_comm::pthread_manager->set_slave_number(tptr->thread_no);

      ad_comm::pthread_manager->cread_lock_buffer(0);
      dvector x = ad_comm::pthread_manager->get_dvector(0);
      dvector Y = ad_comm::pthread_manager->get_dvector(0);
      ad_comm::pthread_manager->cread_unlock_buffer(0);

      do
      {
         ad_comm::pthread_manager->read_lock_buffer(0);
         int lflag=ad_comm::pthread_manager->get_int(0);
         if (lflag == 0) break;
         dvariable a =ad_comm::pthread_manager->get_dvariable(0);
         dvariable b =ad_comm::pthread_manager->get_dvariable(0);
         ad_comm::pthread_manager->read_unlock_buffer(0);

         dvar_vector pred_Y(x.indexmin(),x.indexmax());

         pred_Y = a * x +  b;
         dvariable f=norm2(pred_Y-Y); 
   
         ad_comm::pthread_manager->write_lock_buffer(0);
         ad_comm::pthread_manager->send_dvariable_to_master(f, 0);
         ad_comm::pthread_manager->write_unlock_buffer(0);
   
         slave_gradcalc();
      }
      while (1);
      pthread_exit(ptr);
   }


DATA_SECTION
  init_int nobs
  init_int nrow
  matrix Y(1,nrow,1,nobs)
  matrix x(1,nrow,1,nobs)
  number A
  number B

 LOCAL_CALCS
    cout << nobs << "  " << nrow << endl;
    A = 2.0;
    B = 4.0;
    random_number_generator rng(101);
    dvector err(1,nobs);
    for (int i = 1; i <= nrow; i++)
    {
       x(i).fill_randu(rng);
       x(i) *= 100.0;
       Y(i) = A*x(i) + B;
       err.fill_randn(rng);
       Y(i) += 5.0*err;
    }

PARAMETER_SECTION
  init_number a   
  init_number b   
  //matrix pred_Y(1,nrow, 1,nobs)
  vector ff(1,nrow)
  objective_function_value f

PRELIMINARY_CALCS_SECTION
    cout << nobs << "  " << nrow << endl;
  //TRACE(x)
  //TRACE(Y)
  a = 1.0;
  b = 2.0;

  int ngroups=1;
  ivector ng(1,ngroups);
  ng(1)=nrow;

  ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,500);
  new_thread_data* data1 = new new_thread_data[nrow+1];
  // initialize data to pass to thread 1
  for (int i=1;i<=nrow;i++)
  {
    data1[i].thread_no = i;
    data1[i].m=0;
  }

  ad_comm::pthread_manager->attach_code(&simple_thread);
  ad_comm::pthread_manager->create_all(data1);

  
  for (int kk=1;kk<=nrow;kk++)
  {
     ad_comm::pthread_manager->cwrite_lock_buffer(kk);
     ad_comm::pthread_manager->send_dvector(Y(kk),kk);
     ad_comm::pthread_manager->send_dvector(x(kk),kk);
     ad_comm::pthread_manager->cwrite_unlock_buffer(kk);
  }


PROCEDURE_SECTION
  for (int kk=1;kk<=nrow;kk++)
  {
     ad_comm::pthread_manager->write_lock_buffer(kk);
     ad_comm::pthread_manager->send_int(1,kk); 
     ad_comm::pthread_manager->send_dvariable(a,kk); 
     ad_comm::pthread_manager->send_dvariable(b,kk); 
     ad_comm::pthread_manager->write_unlock_buffer(kk);
     //TTRACE(kk,sum(x(kk)))
  
  }

  for (int kk=1;kk<=nrow;kk++)
  {
      //TRACE(kk)
      ad_comm::pthread_manager->read_lock_buffer(kk);
      ff(kk) = ad_comm::pthread_manager->get_dvariable(kk);
      ad_comm::pthread_manager->read_unlock_buffer(kk);
      //TTRACE(kk,ff(kk))
  }
  f = sum(ff);
  f=(nrow*nobs)/2.*log(f);    // make it a likelihood function so that
                                  // covariance matrix is correct


REPORT_SECTION
  report << "A = " << A << "; B = " << B <<endl;
  report << "a = " << a << "; b = " << b <<endl;

FINAL_SECTION
  for (int k = 1; k <= nrow;k++)
  {
    ad_comm::pthread_manager->write_lock_buffer(k);
    ad_comm::pthread_manager->send_int(0,k);
    ad_comm::pthread_manager->write_unlock_buffer(k);
  }
  sleep(1);
  delete ad_comm::pthread_manager;
  ad_comm::pthread_manager=0;
