#include <admodel.h>
#include <cstddef>
#include "adthread.h"
#if !defined(OPT_LIB)
#  if !defined(CHK_ID_STRING)
#    define CHK_ID_STRING
#  endif
#endif

void adjoint_adwrite_lock_buffer_1(void);
void adjoint_adwrite_lock_buffer_2(void);

void adpthread_manager::write_lock_buffer(int sno)
{
  if (logflag)
  {
    //*(logfiles[0]) << " write_lock_buffer_master"   << endl;
    //adt[0].get_elapsed_time_and_reset();
  }
  int tn2=ad_comm::pthread_manager->get_slave_number();
  if (tn2==sno)
  {
    //cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master write to slave
  {
    int s1 = tn2;
    int s2 = sno;
    pthread_mutex_lock(ssmutex[s1]+s2);
    // only write if buffer empty
    while (smflag(s1,s2) == 1 || ssflag(s1,s2) ==1 ) 
      pthread_cond_wait(smcondition[s1]+s2,ssmutex[s1]+s2);
    save_identifier_string("YX");
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("OD");
    save_pointer_value(this);
    save_identifier_string("CT");
    gradient_structure::GRAD_STACK1->
        set_gradient_stack(::adjoint_adwrite_lock_buffer_1);
  }
  else if (sno<tn2)  // old slave write to master
  {
    int s2 = tn2;
    int s1 = sno;
    pthread_mutex_lock(ssmutex[s1]+s2);
    // only write if buffer empty
    while (smflag(s1,s2) == 1 || ssflag(s1,s2) ==1 ) 
      pthread_cond_wait(sscondition[s1]+s2,ssmutex[s1]+s2);
    save_identifier_string("TYD");
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("ED");
    save_pointer_value(this);
    save_identifier_string("CY");
    gradient_structure::GRAD_STACK1->
        set_gradient_stack(::adjoint_adwrite_lock_buffer_2);
  }
}   
void adpthread_manager::cwrite_lock_buffer(int sno)
{
  if (logflag)
  {
    //*(logfiles[0]) << " write_lock_buffer_master"   << endl;
    //adt[0].get_elapsed_time_and_reset();
  }
  int tn2=ad_comm::pthread_manager->get_slave_number();
  if (tn2==sno)
  {
    //cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master write to slave
  {
    int s1 = tn2;
    int s2 = sno;
    pthread_mutex_lock(ssmutex[s1]+s2);
    // only write if buffer empty
    while (smflag(s1,s2) == 1 || ssflag(s1,s2) ==1 ) 
      pthread_cond_wait(smcondition[s1]+s2,ssmutex[s1]+s2);
  }
  else if (sno<tn2)  // old slave write to master
  {
    int s2 = tn2;
    int s1 = sno;
    pthread_mutex_lock(ssmutex[s1]+s2);
    // only write if buffer empty
    while (smflag(s1,s2) == 1 || ssflag(s1,s2) ==1 ) 
      pthread_cond_wait(sscondition[s1]+s2,ssmutex[s1]+s2);
  }
}   
void adjoint_adwrite_lock_buffer_1(void)
{
  verify_identifier_string("CT");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adwrite_lock_buffer_1();
}

void adpthread_manager::adjoint_adwrite_lock_buffer_1(void)
{
  //unlock read buffer slave
   //cout  << "adjoint_write_lock_buffer_master(void)" << endl;
  verify_identifier_string("OD");
  int tn2=restore_int_value();
  int sno=restore_int_value();
  if (tn2>=sno)
  {
    cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  int s1 = tn2;
  int s2 = sno;
  scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
  verify_identifier_string("YX");
  // !!!!!!!!!!!!!!!!!!!!
  //pthread_cond_signal(mcondition+sno);
  pthread_cond_signal(sscondition[s1]+s2);
  pthread_mutex_unlock(ssmutex[s1]+s2) ;
  if (logflag)
  {
    double tm=adt[0].get_elapsed_time_and_reset();
    //*(logfiles[0]) << tm << " adjoint_write_lock_buffer_master"   << endl;
  }
}

void adjoint_adwrite_lock_buffer_2(void)
{
  verify_identifier_string("CY");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adwrite_lock_buffer_2();
}

void adpthread_manager::adjoint_adwrite_lock_buffer_2(void)
{
  //unlock read buffer slave
   //cout  << "adjoint_write_lock_buffer_slave(void)" << endl;
  verify_identifier_string("ED");
  int tn2=restore_int_value();
  int sno=restore_int_value();
  if (sno>=tn2)
  {
    //cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  int s1 = sno;
  int s2 = tn2;
  scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
  verify_identifier_string("TYD");
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  pthread_cond_signal(smcondition[s1]+s2);
  pthread_mutex_unlock(ssmutex[s1]+s2) ;
  if (logflag)
  {
    double tm=adt[sno].get_elapsed_time_and_reset();
    //*(logfiles[sno]) << tm << " adjoint_write_lock_buffer_slave"   << endl;
  }
}
void adjoint_adwrite_unlock_buffer_1(void);
void adjoint_adwrite_unlock_buffer_2(void);

void adpthread_manager::write_unlock_buffer(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  int tn2=ad_comm::pthread_manager->get_slave_number();
  if (tn2==sno)
  {
    //cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master write to slave
  {
    int s1 = tn2;
    int s2 = sno;
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    smflag(s1,s2) = 1;
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    pthread_cond_signal(sscondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    save_identifier_string("SH");
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("KW");
    save_pointer_value(this);
    save_identifier_string("ZD");
    gradient_structure::GRAD_STACK1->
      set_gradient_stack(::adjoint_adwrite_unlock_buffer_1);
    if (logflag)
    {
      double tm=adt[0].get_elapsed_time_and_reset();
     // *(logfiles[0]) << tm << " write_unlock_buffer_master" << endl;
    }
  }
  else if (sno<tn2)  // old slave write to master
  {
    int s2 = tn2;
    int s1 = sno;
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    ssflag(s1,s2) = 1;
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    pthread_cond_signal(smcondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    save_identifier_string("UD");
    save_int_value(sno);
    save_int_value(tn2);
    save_identifier_string("CD");
    save_pointer_value(this);
    save_identifier_string("CZ");
    gradient_structure::GRAD_STACK1->
        set_gradient_stack(::adjoint_adwrite_unlock_buffer_2);
    if (logflag)
    {
      double tm=adt[sno].get_elapsed_time_and_reset();
      //*(logfiles[sno]) << tm  <<  " write_unlock_buffer_slave" << endl;
    }
  }
}   

void adpthread_manager::cwrite_unlock_buffer(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  int tn2=ad_comm::pthread_manager->get_slave_number();
  if (tn2==sno)
  {
    //cerr << "Error -- process can not write to itself" << endl;
    ad_exit(1);
  }
  else if (tn2<sno)  // old master write to slave
  {
    int s1 = tn2;
    int s2 = sno;
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    smflag(s1,s2) = 1;
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    pthread_cond_signal(sscondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    if (logflag)
    {
      double tm=adt[0].get_elapsed_time_and_reset();
     // *(logfiles[0]) << tm << " write_unlock_buffer_master" << endl;
    }
  }
  else if (sno<tn2)  // old slave write to master
  {
    int s2 = tn2;
    int s1 = sno;
    scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    ssflag(s1,s2) = 1;
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    pthread_cond_signal(smcondition[s1]+s2);
    pthread_mutex_unlock(ssmutex[s1]+s2);
    if (logflag)
    {
      double tm=adt[sno].get_elapsed_time_and_reset();
      //*(logfiles[sno]) << tm  <<  " write_unlock_buffer_slave" << endl;
    }
  }
}   
void adjoint_adwrite_unlock_buffer_1(void)
{
  verify_identifier_string("ZD");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adwrite_unlock_buffer_1();
}
void adpthread_manager::adjoint_adwrite_unlock_buffer_1(void)
{
  if (logflag)
  {
    adt[0].get_elapsed_time_and_reset();
  }
  // cout  << "adjoint_write_unlock_buffer_master(void)" << endl;
  verify_identifier_string("KW");
  int tn2=restore_int_value();
  int sno=restore_int_value();
  if (tn2>=sno)
  {
    cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  int s1 = tn2;
  int s2 = sno;
  verify_identifier_string("SH");
  //read_lock_buffer_master(sno);
  pthread_mutex_lock(ssmutex[s1]+s2);
  // only read if buffer full and data is for you
  // cout  << endl << "XX sflag[sno] = " << ssflag[sno] << endl;
  while (ssflag(s1,s2) == 0) 
    pthread_cond_wait(smcondition[s1]+s2,ssmutex[s1]+s2);
  ssflag(s1,s2)=0; 
}
void adjoint_adwrite_unlock_buffer_2(void)
{
  verify_identifier_string("CZ");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_adwrite_unlock_buffer_2();
}
void adpthread_manager::adjoint_adwrite_unlock_buffer_2(void)
{
  // cout  << "adjoint_write_unlock_buffer_slave(void)" << endl;
  verify_identifier_string("CD");
  int tn2=restore_int_value();
  int sno=restore_int_value();
  if (sno>=tn2)
  {
    cerr << "This can't happen" << endl;
    ad_exit(1);
  }
  int s1 = sno;
  int s2 = tn2;
  pthread_mutex_lock(ssmutex[s1]+s2);
  scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
  if (logflag)
  {
    adt[sno].get_elapsed_time_and_reset();
  }
  verify_identifier_string("UD");
  // we should be using the mutexes from the class
  // to get rid of global variables
  // only write if buffer empty
  while (smflag(s1,s2) == 0) 
    pthread_cond_wait(sscondition[s1]+s2,ssmutex[s1]+s2);
  smflag(s1,s2)=0;
}
