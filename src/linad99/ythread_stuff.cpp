
#include <admodel.h>
#include <cstddef>
#include "adthread.h"
#if !defined(OPT_LIB)
#  if !defined(CHK_ID_STRING)
#    define CHK_ID_STRING
#  endif
#endif

/* prototype for thread routine */
void admb_thread(void * ptr);

//pthread_mutex_t mutex_print;

//const int NSLAVES=1;

typedef char * pchar;
typedef ofstream * pofstream;

void adjoint_adread_lock_buffer_1(void);
void adjoint_adread_lock_buffer_2(void);

void adpthread_manager::read_lock_buffer(int sno)
{
  if (logflag)
  {
   // *(logfiles[0]) << "starting read_lock_buffer_master " << sno   << endl;
    adt[0].get_elapsed_time_and_reset();
  }
  int tn2=ad_comm::pthread_manager->get_slave_number();
  int s1,s2;
  if (tn2==sno)
  {
   // cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master read from
  {
    s1=tn2;
    s2=sno;
    pthread_mutex_lock(ssmutex[s1]+s2);
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // only read if buffer full and data is for you
    while (ssflag(s1,s2) == 0) 
      pthread_cond_wait(smcondition[s1]+s2,ssmutex[s1]+s2);
    // cout  << "A sflag=0" << endl;
    ssflag(s1,s2)=0; 
    save_identifier_string("WE");
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("XE");
    save_pointer_value(this);
    save_identifier_string("ZE");
    gradient_structure::GRAD_STACK1->
       set_gradient_stack(::adjoint_adread_lock_buffer_1);
  }
  else
  {
    s1=sno;
    s2=tn2;
    pthread_mutex_lock(ssmutex[s1]+s2);
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // only write if buffer empty
    while (smflag(s1,s2) == 0) 
      pthread_cond_wait(sscondition[s1]+s2,ssmutex[s1]+s2);
    smflag(s1,s2)=0; 
    save_identifier_string("H1");
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("EU");
    save_pointer_value(this);
    save_identifier_string("D1");
    gradient_structure::GRAD_STACK1->
              set_gradient_stack(::adjoint_adread_lock_buffer_2);
  }
}   
void adpthread_manager::cread_lock_buffer(int sno)
{
  if (logflag)
  {
   // *(logfiles[0]) << "starting read_lock_buffer_master " << sno   << endl;
    adt[0].get_elapsed_time_and_reset();
  }
  int tn2=ad_comm::pthread_manager->get_slave_number();
  int s1,s2;
  if (tn2==sno)
  {
   // cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master read from
  {
    s1=tn2;
    s2=sno;
    pthread_mutex_lock(ssmutex[s1]+s2);
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // only read if buffer full and data is for you
    while (ssflag(s1,s2) == 0) 
      pthread_cond_wait(smcondition[s1]+s2,ssmutex[s1]+s2);
    // cout  << "A sflag=0" << endl;
    ssflag(s1,s2)=0; 
  }
  else
  {
    s1=sno;
    s2=tn2;
    pthread_mutex_lock(ssmutex[s1]+s2);
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // only write if buffer empty
    while (smflag(s1,s2) == 0) 
      pthread_cond_wait(sscondition[s1]+s2,ssmutex[s1]+s2);
    smflag(s1,s2)=0; 
  }
}   
void adjoint_adread_lock_buffer_1(void)
{
  verify_identifier_string("ZE");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adread_lock_buffer_1();
}
void adpthread_manager::adjoint_adread_lock_buffer_1(void)
{
  // cout  << "adjoint_read_lock_buffer_master(void)" << endl;
  verify_identifier_string("XE");
  // *************************************************
  // *************************************************
  int tn2=restore_int_value();
  int sno=restore_int_value();
  if (tn2>=sno)
  {
    cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  int s1,s2;
  s1=tn2;
  s2=sno;
  // *************************************************
  // *************************************************
  verify_identifier_string("WE");
  //write_unlock_buffer_master(sno);
  scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
  smflag(s1,s2) = 1;
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
  pthread_cond_signal(sscondition[s1]+s2);
  pthread_mutex_unlock(ssmutex[s1]+s2);
  if (logflag)
  {
    double tm=adt[0].get_elapsed_time_and_reset();
    *(logfiles[0]) << tm << " adjoint_read_lock_buffer_master" << endl;
  }
}

void adjoint_adread_lock_buffer_2(void)
{
  verify_identifier_string("D1");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adread_lock_buffer_2();
}
void adpthread_manager::adjoint_adread_lock_buffer_2(void)
{
  // cout  << "adjoint_read_lock_buffer_slave(void)" << endl;
  //write_unlock_buffer_slave(sno);
  verify_identifier_string("EU");
  // *************************************************
  // *************************************************
  int s1,s2;
  int tn2=restore_int_value();
  int sno=restore_int_value();
  if (tn2<sno)
  {
    cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  s1=sno;
  s2=tn2;
  // *************************************************
  // *************************************************
  verify_identifier_string("H1");
  // we should be using the mutexes from the class
  // to get rid of global variables
  scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
  // cout  << "adpthread_manager::adjoint_read_lock_buffer_slave(void)=1" << endl;
  ssflag(s1,s2)=1; 
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
  pthread_cond_signal(smcondition[s1]+s2);
  pthread_mutex_unlock(ssmutex[s1]+s2);
  if (logflag)
  {
    double tm=adt[sno].get_elapsed_time_and_reset();
    *(logfiles[sno]) << tm   << " adjoint_read_lock_buffer_slave" << endl;
  }
}

void adjoint_adread_unlock_buffer_1(void);
void adjoint_adread_unlock_buffer_2(void);

void adpthread_manager::read_unlock_buffer(int sno)
{
  int tn2=ad_comm::pthread_manager->get_slave_number();
  int s1,s2;
  if (tn2==sno)
  {
    cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master read from
  {
    s1=tn2;
    s2=sno;
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    pthread_cond_signal(sscondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    
    save_identifier_string("G9");
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("G7");
    save_pointer_value(this);
    save_identifier_string("G5");
    gradient_structure::GRAD_STACK1->
              set_gradient_stack(::adjoint_adread_unlock_buffer_1);
    if (logflag)
    {
      double tm=adt[0].get_elapsed_time_and_reset();
      *(logfiles[0]) << tm << " read_unlock_buffer_master"  << endl;
    }
  }
  else
  {
    s1=sno;
    s2=tn2;
    // we should be using the mutexes from the class
    // to get rid of global variables
    save_identifier_string("J5");
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    pthread_cond_signal(smcondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("L7");
    save_pointer_value(this);
    save_identifier_string("K5");
    gradient_structure::GRAD_STACK1->
              set_gradient_stack(::adjoint_adread_unlock_buffer_2);
    if (logflag)
    {
      double tm=adt[sno].get_elapsed_time_and_reset();
      *(logfiles[sno]) << tm << " read_unlock_buffer_slave" << endl;
    }
  }
}

void adpthread_manager::cread_unlock_buffer(int sno)
{
  int tn2=ad_comm::pthread_manager->get_slave_number();
  int s1,s2;
  if (tn2==sno)
  {
    cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master read from
  {
    s1=tn2;
    s2=sno;
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    pthread_cond_signal(sscondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    
    if (logflag)
    {
      double tm=adt[0].get_elapsed_time_and_reset();
      *(logfiles[0]) << tm << " read_unlock_buffer_master"  << endl;
    }
  }
  else
  {
    s1=sno;
    s2=tn2;
    // we should be using the mutexes from the class
    // to get rid of global variables
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    pthread_cond_signal(smcondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    if (logflag)
    {
      double tm=adt[sno].get_elapsed_time_and_reset();
      *(logfiles[sno]) << tm << " read_unlock_buffer_slave" << endl;
    }
  }
}

void adjoint_adread_unlock_buffer_1(void)
{
  verify_identifier_string("G5");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adread_unlock_buffer_1();
}

void  adpthread_manager::adjoint_adread_unlock_buffer_1(void)
{
  // cout  << "adpthread_manager::adjoint_read_unlock_buffer_master(void);" << endl;
  verify_identifier_string("G7");
  int tn2=restore_int_value();
  int sno=restore_int_value();
  verify_identifier_string("G9");
  if (tn2>=sno)
  {
    //cerr << "This can't happen" << endl;
    //ad_exit(1);
  }
  int s1,s2;
  s1=tn2;
  s2=sno;
  pthread_mutex_lock(ssmutex[s1]+s2);
  if (logflag)
  {
   // *(logfiles[0]) << "starting adjoint_read_unlock_buffer_master " << sno 
     //              << endl;
    adt[0].get_elapsed_time_and_reset();
  }
  // only write if buffer empty
  while (smflag(s1,s2) == 1 || ssflag(s1,s2) ==1 ) 
    pthread_cond_wait(smcondition[s1]+s2,ssmutex[s1]+s2);
}

void adjoint_adread_unlock_buffer_2(void)
{
  verify_identifier_string("K5");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adread_unlock_buffer_2();
}
void  adpthread_manager::adjoint_adread_unlock_buffer_2(void)
{ 
  // cout  << "adpthread_manager::adjoint_read_unlock_buffer_slave(void)" << endl;
  // write_lock_slave_buffer
  verify_identifier_string("L7");
  int tn2=restore_int_value();
  int sno=restore_int_value();
  if (tn2<=sno)
  {
   // cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  int s1,s2;
  s1=sno;
  s2=tn2;
  pthread_mutex_lock(ssmutex[s1]+s2);
  if (logflag)
  {
    //*(logfiles[sno]) << "starting adjoint_read_unlock_buffer_slave " << sno  
      //               << endl;
    adt[sno].get_elapsed_time_and_reset();
  }
  // only write if buffer empty
  while (smflag(s1,s2) == 1 || ssflag(s1,s2) ==1 ) 
    pthread_cond_wait(sscondition[s1]+s2,ssmutex[s1]+s2);
  verify_identifier_string("J5");
}

