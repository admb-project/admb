GLOBALS_SECTION
  #include <fvar.hpp>
  #include <admodel.h>
  #include <adthread.h>

  #include "trace.h"

  class thread_funnel
  {
   public:
     // variables and constants used in the trapzd integration
     int interval;
     dvariable s; 

     // constant model objects
     int nsteps;
     //int k;
     dvector a;
     //dvector freq;
     int a_index;
  
     // variable objects
     dvariable log_tau;
     dvariable log_nu;
     dvariable beta;
     dvariable log_sigma;
     dvariable tau;
     dvariable nu;
     dvariable sigma;
     //dvar_vector S;
     //dvariable f;
  
     int get_constant_objects();
     int get_variable_objects();
     //void send_variable_objects();
  
     dvariable h(const dvariable& z);
     dvariable trapzd(double a,double b,int n);
     dvariable adromb(double a, double b, int ns);
  };
  /*
  dvariable tfh(thread_funnel* p, const dvariable& z)
  {
      return p->h(z);

  }
  */

  //FUNCTION dvariable h(const dvariable& z)
  dvariable thread_funnel::h(const dvariable& z)
  {
     dvariable tmp;
     tmp=exp(-.5*z*z + tau*(-1.+exp(-nu*pow(a(a_index),beta)*exp(sigma*z))) );  
     return tmp;
  }

  dvariable thread_funnel::trapzd(double a,double b,int n)
  {
    double x,num_interval,hn;
    dvariable sum;
    //static dvariable s;
    //static int interval;
    int j;
    //model_parameters * ptr= (model_parameters *) mycast();
    if (n == 1) {
      interval=1;
      //return (s=0.5*(b-a)*((ptr->*func)(a)+(ptr->*func)(b)));
      return (s=0.5*(b-a)*(h(a)+h(b)));
    } else {
      num_interval=interval;
      hn=(b-a)/num_interval;
      x=a+0.5*hn;
      //for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += (ptr->*func)(x);
      for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += h(x);
      interval *= 2;
      s=0.5*(s+(b-a)*sum/num_interval);
      //TTRACE(x,s);
      return s;
    }


  }

  dvariable thread_funnel::adromb(double a, double b, int ns)
  {
    const double base = 4; 
    const int JMAX = 50;
    int MAXN = min(JMAX, ns);
    dvar_vector s(1,MAXN+1);
  
    for(int j=1; j<=MAXN+1; j++)
    {
      s[j] = trapzd(a,b,j);
    }
  
    for(int iter=1; iter<=MAXN+1; iter++)
    {
      for(int j=1; j<=MAXN+1-iter; j++)
      {
        s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
      }
    }
  
    return s[1];
  }
  

  int thread_funnel::get_constant_objects()
  {
      // take control of the constant buffer for reading
      ad_comm::pthread_manager->cread_lock_buffer(0);

      // read the independent variables IN THE SAME ORDER AS THEY ARE SENT
      nsteps = ad_comm::pthread_manager->get_int(0);
      //TRACE(nsteps)
      a = ad_comm::pthread_manager->get_dvector(0);
      //TRACE(a)
      a_index = ad_comm::pthread_manager->get_int(0);
      TRACE(a_index)
      
      // release the constant buffer
      ad_comm::pthread_manager->cread_unlock_buffer(0);
      return(1);
  }
  

  int thread_funnel::get_variable_objects()
  {
      // take control of the variable buffer for reading
      ad_comm::pthread_manager->read_lock_buffer(0);
      // read the dependent variables IN THE SAME ORDER AS THEY ARE SENT
      log_tau = ad_comm::pthread_manager->get_dvariable(0);
      log_nu = ad_comm::pthread_manager->get_dvariable(0);
      beta = ad_comm::pthread_manager->get_dvariable(0);
      tau = ad_comm::pthread_manager->get_dvariable(0);
      nu = ad_comm::pthread_manager->get_dvariable(0);
      sigma = ad_comm::pthread_manager->get_dvariable(0);
      
      // release the variable buffer
      ad_comm::pthread_manager->read_unlock_buffer(0);
      return(0);
  }
  

  void funnel_loop(void* ptr)
  {
      // cast the pointer to the proper type
      new_thread_data * tptr = (new_thread_data *) ptr;

      // set up the gradient stack for the thread
      gradient_structure::set_MAX_NVAR_OFFSET(10000);
      gradient_structure::set_GRADSTACK_BUFFER_SIZE(2000000);
      gradient_structure::set_CMPDIF_BUFFER_SIZE   (2000000);
      gradient_structure gs(10000000);
   
      // get the thread number
      ad_comm::pthread_manager->set_slave_number(tptr->thread_no);

      thread_funnel tf;
      //TTRACE(tptr->thread_no,tf.a_index)
      tf.get_constant_objects();
      //TTRACE(tptr->thread_no,tf.a_index)
      if (tptr->thread_no != tf.a_index)
          cerr << "error getting a_index" << endl;
      do
      {
         int lflag = tf.get_variable_objects();
         //TRACE(lflag)
         if (lflag == 1) break;
    
         dvariable Integral=tf.adromb(-3.0,3.0,tf.nsteps);
         //TRACE(Integral)

         // send results to master
         // take control of the variable buffer for sending
         ad_comm::pthread_manager->write_lock_buffer(0);
         // send Integral
         ad_comm::pthread_manager->send_dvariable(Integral, 0);
         // release the variable buffer
         ad_comm::pthread_manager->write_unlock_buffer(0);
   
         // compute derivative contribution for this thread 
         slave_gradcalc();
      } while(1);
      pthread_exit(ptr);

  }

DATA_SECTION
  init_int nsteps 
  init_int k
  init_vector a(1,k+1)
  init_vector freq(1,k)
  int a_index;
  number sum_freq
  !!  sum_freq=sum(freq);

PARAMETER_SECTION
  init_bounded_number log_tau(-14,15,2)
  init_bounded_number log_nu(-15,4)
  init_bounded_number beta(.1,1.0,-1)
  init_bounded_number log_sigma(-5,3)
  likeprof_number tau
 !! tau.set_stepnumber(25);
  sdreport_number nu
  sdreport_number sigma
  vector S(1,k+1)
  objective_function_value f

PRELIMINARY_CALCS_SECTION

  log_tau = 0.0;
  beta = 0.6666667;
  log_nu = 0.0;
  log_sigma = -2.0;

  // number of thread groups
  int nthread = k+1;
  int ngroups=1;
  ivector ng(1,ngroups);
  // number of threads in group 1
  ng(1)=nthread;

  // create instance of pthread_manager class
  // third argument is number of bytes in the transfer buffer
  //ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,500);
  ad_comm::pthread_manager = new adpthread_manager(ngroups,ng,500);

  // create data vecor for argument to thread function
  new_thread_data* data1 = new new_thread_data[nthread+1];
  for (int i=1;i<=nthread;i++)
  {
    data1[i].thread_no = i; // only the thread number is imortant
    data1[i].m=0;           // not used
  }

  // specifiy function to run on the threads by passing apointer to the function
  ad_comm::pthread_manager->attach_code(&funnel_loop);
  // create the threads
  ad_comm::pthread_manager->create_all(data1);

  for (int i=1;i<=k+1;i++)
  {
     a_index = i;
     // take control of the constant buffer for sending
     ad_comm::pthread_manager->cwrite_lock_buffer(i);
    
     ad_comm::pthread_manager->send_int(nsteps, i);
     //TTRACE(i,nsteps)
     ad_comm::pthread_manager->send_dvector(a, i);
     //TTRACE(i,a)
     ad_comm::pthread_manager->send_int(a_index, i);
     //TTRACE(i,a_index)

     // release the constant buffer
     ad_comm::pthread_manager->cwrite_unlock_buffer(i); 
  }
  //TRACE(sleep(1))

PROCEDURE_SECTION
  //cout << endl;
  //cout << "ifn = " << ifn << endl;
  //cout << "quit_flag = " << quit_flag << endl;
  //cout << "ihflag = " << ihflag << endl;
  //cout << "last_phase() " << last_phase() << endl; 
  //cout << "iexit = " << iexit << endl;
  tau=exp(log_tau);
  nu=exp(log_nu);
  sigma=exp(log_sigma);
  //funnel_dvariable Integral;
  for (int i=1;i<=k+1;i++)
  {
     //a_index=i;
     //ad_begin_funnel();
     //Integral=adromb(&model_parameters::h,-3.0,3.0,nsteps);
     //S(i)=Integral;
   
     // take control of the variable buffer for writing
     ad_comm::pthread_manager->write_lock_buffer(i);
     ad_comm::pthread_manager->send_dvariable(log_tau,i);
     ad_comm::pthread_manager->send_dvariable(log_nu,i);
     ad_comm::pthread_manager->send_dvariable(beta,i);
     ad_comm::pthread_manager->send_dvariable(tau,i);
     ad_comm::pthread_manager->send_dvariable(nu,i);
     ad_comm::pthread_manager->send_dvariable(sigma,i);
     ad_comm::pthread_manager->send_int(0,i);

     // release the variable bufffer
     ad_comm::pthread_manager->write_unlock_buffer(i);
     /*
     if (i == 5)
     {  
        TRACE(sleep(1))
        exit(1);
     }
     */
  }
  //TRACE(sleep(1))
  f=0.0;
  for (int i=1;i<=k+1;i++)
  {
     // take control of the variable buffer for reading
     ad_comm::pthread_manager->read_lock_buffer(i);
     dvariable Integral = ad_comm::pthread_manager->get_dvariable(i);
     //TRACE(Integral)
     // release the variable buffer
     ad_comm::pthread_manager->read_unlock_buffer(i);
     S(i) = Integral;
  }
  //TRACE(S)
  for (int i=1;i<=k;i++)
  {
     dvariable ff=0.0;
     dvariable diff=posfun((S(i)-S(i+1))/S(i),.000001,ff);
     f-=freq(i)*log(1.e-50+S(i)*diff);
     f+=ff;
  }
  f+=sum_freq*log(1.e-50+S(1));
  //TRACE(f)

REPORT_SECTION
  report << "report:" << endl;
  report << "ifn = " << ifn << endl;
  report << "quit_flag = " << quit_flag << endl;
  report << "ihflag = " << ihflag << endl;
  report << "last_phase() " << last_phase() << endl; 
  report << "iexit = " << iexit << endl;
  tau=exp(log_tau);
  report << "nsteps = " << std::setprecision(10) <<  nsteps << endl;
  report << "f = " << std::setprecision(10) <<  f << endl;
  report << "a" << endl << a << endl;
  report << "freq" << endl << freq << endl;
  report << "S" << endl << S << endl;
  report << "S/S(1)" << endl << std::ios::fixed << std::setprecision(6) << S/S(1) << endl;
  report << "tau "  << tau << endl; 
  report << "nu "  << nu << endl; 
  report << "beta "  << beta << endl; 
  report << "sigma "  << sigma << endl; 
