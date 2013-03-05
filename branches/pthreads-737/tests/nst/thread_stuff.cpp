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

pthread_mutex_t mutex_print;

//const int NSLAVES=1;

typedef char * pchar;
void pthread_master_unpack_vector_derivatives(void);

void send_double_to_master(double &x,void * current_bptr,int sno)
{
  memcpy(current_bptr,&x,sizeof(double));
}

void adpthreads_slave_pack_vector_derivative(void);

double get_double_from_master(void * current_bptr, int sno)
{
  double x;
  memcpy(&x,current_bptr,sizeof(double));
  return x;
}

void adpthreads_slave_pack_number_derivative(void)
{
  verify_identifier_string("G1");
  int sno=restore_int_value();
  void * ptr=restore_pointer_value();
  verify_identifier_string("D");
  prevariable_position dvpos=restore_prevariable_position();
  double dv=restore_prevariable_derivative(dvpos);
  //cout << "sending " << dv << " to master " << endl;
  send_double_to_master(dv,ptr,sno);
  //pvm_pack(dv);
  verify_identifier_string("C");
}


dvariable get_dvariable_from_master(void * current_bptr, int sno)
{
  dvariable x;
  value(x)=get_double_from_master(current_bptr,sno);
  save_identifier_string("C");
  x.save_prevariable_position();
  save_identifier_string("D");
  save_pointer_value(current_bptr);
  save_int_value(sno);
  save_identifier_string("G1");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthreads_slave_pack_number_derivative);
  return x;
}


void adpthreads_slave_pack_vector_derivative(void)
{
  // cout  << "XXX In adpthreads_slave_pack_vector_derivative " << endl; 
  verify_identifier_string("G2");
  int sno=restore_int_value();
  void * ptr=restore_pointer_value();
  verify_identifier_string("D");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  dvector dv=restore_dvar_vector_derivatives(dvpos);
  verify_identifier_string("C");
  char * b = (char*)(ptr);
  int mmin=dv.indexmin();
  int mmax=dv.indexmax();
  int sz=mmax-mmin+1;
  // cout  << "In adpthreads_slave_pack_vector_derivative " << sno 
      // << " writing to buffer "
      // << (void*) b << " " << mmin << " " << mmax << endl;
  // cout  << "copy " << mmin << " to " << (void *)b << endl;
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(dv(mmin)),sz*sizeof(double));
}



dvar_vector get_dvar_vector_from_master(void * current_bptr, int sno)
{
  char * b = (char*)(current_bptr);
  int mmin;
  int mmax;
  memcpy(&mmin,b,sizeof(int));
  b+=sizeof(int);
  // cout  << "In dvar_vector get_dvar_vector_from_master " << endl;
  memcpy(&mmax,b,sizeof(int));
  // cout  << " mmin = " << mmin   << " mmax = " << mmax  << endl;
  b+=sizeof(int);
  dvar_vector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(value(x(mmin))),b,sz*sizeof(double));
  save_identifier_string("C");
  x.save_dvar_vector_position();
  save_identifier_string("D");
  save_pointer_value(current_bptr);
  save_int_value(sno);
  save_identifier_string("G2");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthreads_slave_pack_vector_derivative);
  return x;
}


dvector get_dvector_from_master(void * current_bptr, int sno)
{
  char * b = (char*)(current_bptr);
  int mmin;
  int mmax;
  memcpy(&mmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&mmax,b,sizeof(int));
  b+=sizeof(int);
  dvector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(x(mmin)),b,sz*sizeof(double));
  return x;
}





dvector get_dvector_from_slave(void * current_bptr, int sno)
{
  char * b = (char*)(current_bptr);
  int mmin;
  int mmax;
  // cout  << "copy " << (void *)b << " to mmin" << endl;
  memcpy(&mmin,b,sizeof(int));
  // cout  << "In get dvector_from_slave " << sno << " reading from buffer "
      // << (void*) b;
  b+=sizeof(int);
  memcpy(&mmax,b,sizeof(int));
  b+=sizeof(int);
  // cout   << " " << mmin << " " << mmax << endl;
  dvector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(x(mmin)),b,sz*sizeof(double));
  return x;
}
   

double get_double_from_slave(void * current_bptr, int sno)
{
  double x;
  memcpy(&x,current_bptr,sizeof(double));
  return x;
}

void send_dvector_to_master(const dvector &x,void * current_bptr,int sno)
{
  char * b = (char*)(current_bptr);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  // cout  << "In send dvector_to_master from slave " << sno
    //   << " writing to buffer " << (void*) b << " "
      // << mmin << " " << mmax << endl;
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(x(mmin)),sz*sizeof(double));
}

void send_dvector_to_slave(const dvector &x,void * current_bptr,int sno)
{
  char * b = (char*)(current_bptr);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(x(mmin)),sz*sizeof(double));
}
void pthread_master_unpack_vector_derivatives(void);

adpthread_manager::adpthread_manager(int ns,int bs) : buffer_size(1,ns)
{
  int i;
  buffer_size=bs;
  nslaves=ns;
  transfer_buffer=new pchar[ns];
  current_bptr=new pchar[ns];
  current_bptr--;
  buffend=new pchar[ns];
  transfer_buffer--;
  buffend--;
  
  
  for (i=1;i<=ns;i++)
  {
    transfer_buffer[i]=new char[bs];
    current_bptr[i]=transfer_buffer[i];
    buffend[i]=transfer_buffer[i]+bs-1;
  }
  mflag=new int[ns];
  mflag--;
  sflag=new int[ns];
  sflag--;
  smutex=new pthread_mutex_t[ns];
  smutex--;
  for (i=1;i<=ns;i++)
  {
    pthread_mutex_init(smutex+i,NULL);
  }
  scondition=new pthread_cond_t[ns];
  scondition--;
  mcondition=new pthread_cond_t[ns];
  mcondition--;
  thread1=new pthread_t[ns];
  thread1--;
}
void adpthread_manager::check_buffer_size_read(int nbytes,int sno)
{
  // if the buffer is too small on read theree is an error
  if (current_bptr[sno]+nbytes>buffend[sno])
  {
    cerr << "error reading from master slave buffer for slave "
         << sno << endl;
    ad_exit(1);
  }
}

void adpthread_manager::check_buffer_size(int nbytes,int sno)
{
  // if the buffer is too small make it bigger and copy old
  // buffer contents
  if (current_bptr[sno]+nbytes>buffend[sno])
  {
    std::ptrdiff_t pd=current_bptr[sno]-transfer_buffer[sno];
    char * tmp=transfer_buffer[sno];
    buffer_size[sno]*=2;
    transfer_buffer[sno]=new char[buffer_size[sno]];
    ::memcpy(transfer_buffer[sno],tmp,pd+1);
    current_bptr[sno]=transfer_buffer[sno]+pd+1;
    delete [] tmp;
    tmp=0;
    buffend[sno]=transfer_buffer[sno]+buffer_size[sno]-1;
  }
}

void adjoint_write_lock_buffer_master(void)
{
  verify_identifier_string("CT");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_write_lock_buffer_master();
}

void adpthread_manager::adjoint_write_lock_buffer_master(void)
{
  //unlock read buffer slave
  // cout  << "adjoint_write_lock_buffer_master(void)" << endl;
  verify_identifier_string("OD");
  int sno=restore_int_value();
  current_bptr[sno]=transfer_buffer[sno];
  verify_identifier_string("YX");
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
}
void adpthread_manager::write_lock_buffer_master(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(mcondition+sno,smutex+sno);
  save_identifier_string("YX");
  save_int_value(sno);
  save_identifier_string("OD");
  save_pointer_value(this);
  save_identifier_string("CT");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(::adjoint_write_lock_buffer_master);
}   

void adjoint_read_lock_buffer_master(void)
{
  verify_identifier_string("ZE");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_read_lock_buffer_master();
}
void adpthread_manager::adjoint_read_lock_buffer_master(void)
{
  // cout  << "adjoint_read_lock_buffer_master(void)" << endl;
  verify_identifier_string("XE");
  int sno=restore_int_value();
  verify_identifier_string("WE");
  //write_unlock_buffer_master(sno);
  current_bptr[sno]=transfer_buffer[sno];
  mflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(scondition+sno);
}


void adpthread_manager::read_lock_buffer_master(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables

  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (sflag[sno] == 0) 
    pthread_cond_wait(mcondition+sno,smutex+sno);
  // cout  << "A sflag=0" << endl;
  sflag[sno] = 0;
  save_identifier_string("WE");
  save_int_value(sno);
  save_identifier_string("XE");
  save_pointer_value(this);
  save_identifier_string("ZE");
  gradient_structure::GRAD_STACK1->
     set_gradient_stack(::adjoint_read_lock_buffer_master);
}   
void adjoint_write_unlock_buffer_master(void)
{
  verify_identifier_string("ZD");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_write_unlock_buffer_master();
}
void adpthread_manager::adjoint_write_unlock_buffer_master(void)
{
  // cout  << "adjoint_write_unlock_buffer_master(void)" << endl;
  verify_identifier_string("XD");
  int sno=restore_int_value();
  verify_identifier_string("TD");
  //read_lock_buffer_master(sno);
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  // cout  << endl << "XX sflag[sno] = " << sflag[sno] << endl;
  while (sflag[sno] == 0) 
    pthread_cond_wait(mcondition+sno,smutex+sno);
  // cout  << endl << "VV sflag[sno] = " << sflag[sno] << endl;
  // cout  << "B sflag=0" << endl;
  sflag[sno] = 0;
}

void adpthread_manager::write_unlock_buffer_master(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  current_bptr[sno]=transfer_buffer[sno];
  mflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(scondition+sno);
  save_identifier_string("TD");
  save_int_value(sno);
  save_identifier_string("XD");
  save_pointer_value(this);
  save_identifier_string("ZD");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_write_unlock_buffer_master);
}   
void adjoint_write_unlock_buffer_slave(void)
{
  verify_identifier_string("CZ");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_write_unlock_buffer_slave();
}

void adpthread_manager::adjoint_write_unlock_buffer_slave(void)
{
  // cout  << "adjoint_write_unlock_buffer_slave(void)" << endl;
  verify_identifier_string("CD");
  int sno=restore_int_value();
  verify_identifier_string("UD");
  // we should be using the mutexes from the class
  // to get rid of global variables
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 0) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  mflag[sno]=0;
}
void adpthread_manager::write_unlock_buffer_slave(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  current_bptr[sno]=transfer_buffer[sno];
  // cout  << "adpthread_manager::write_unlock_buffer_slave(int sno)=1" << endl;
  sflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(mcondition+sno);
  save_identifier_string("UD");
  save_int_value(sno);
  save_identifier_string("CD");
  save_pointer_value(this);
  save_identifier_string("CZ");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(::adjoint_write_unlock_buffer_slave);

}   

void adjoint_write_lock_buffer_slave(void)
{
  verify_identifier_string("CY");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_write_lock_buffer_slave();
}

void adpthread_manager::adjoint_write_lock_buffer_slave(void)
{
  //unlock read buffer slave
  // cout  << "adjoint_write_lock_buffer_slave(void)" << endl;
  verify_identifier_string("ED");
  int sno=restore_int_value();
  current_bptr[sno]=transfer_buffer[sno];
  verify_identifier_string("YD");
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
}
void adpthread_manager::write_lock_buffer_slave(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  save_identifier_string("YD");
  save_int_value(sno);
  save_identifier_string("ED");
  save_pointer_value(this);
  save_identifier_string("CY");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(::adjoint_write_lock_buffer_slave);
}

void adjoint_read_lock_buffer_slave(void)
{
  verify_identifier_string("D1");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_read_lock_buffer_slave();
}
void adpthread_manager::adjoint_read_lock_buffer_slave(void)
{
  // cout  << "adjoint_read_lock_buffer_slave(void)" << endl;
  //write_unlock_buffer_slave(sno);
  verify_identifier_string("E1");
  int sno=restore_int_value();
  verify_identifier_string("H1");
  // we should be using the mutexes from the class
  // to get rid of global variables
  current_bptr[sno]=transfer_buffer[sno];
  // cout  << "adpthread_manager::adjoint_read_lock_buffer_slave(void)=1" << endl;
  sflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(mcondition+sno);
}

void adpthread_manager::read_lock_buffer_slave(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 0) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  mflag[sno]=0;
  save_identifier_string("H1");
  save_int_value(sno);
  save_identifier_string("E1");
  save_pointer_value(this);
  save_identifier_string("D1");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_read_lock_buffer_slave);
}
void adjoint_master_write_lock(void)
{
  verify_identifier_string("G5");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  verify_identifier_string("G7");
  int sno=restore_int_value();
  verify_identifier_string("G9");
  ptr->adjoint_master_write_lock(sno);
}

void  adpthread_manager::adjoint_master_write_lock(int sno)
{
  // cout  << "adpthread_manager::adjoint_master_write_lock(int sno)" << endl;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  current_bptr[sno]=transfer_buffer[sno];
  while (mflag[sno] == 1 || sflag[sno] ==1 )
    pthread_cond_wait(mcondition+sno,smutex+sno);
}

void adjoint_read_unlock_buffer_master(void)
{
  verify_identifier_string("G5");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_read_unlock_buffer_master();
}

void  adpthread_manager::adjoint_read_unlock_buffer_master(void)
{
  // cout  << "adpthread_manager::adjoint_read_unlock_buffer_master(void);" << endl;
  verify_identifier_string("G7");
  int sno=restore_int_value();
  verify_identifier_string("G9");
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 )
    pthread_cond_wait(mcondition+sno,smutex+sno);
}

void adpthread_manager::read_unlock_buffer_master(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  current_bptr[sno]=transfer_buffer[sno];
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(scondition+sno);
  
  save_identifier_string("G9");
  save_int_value(sno);
  save_identifier_string("G7");
  save_pointer_value(this);
  save_identifier_string("G5");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_read_unlock_buffer_master);
}
void adjoint_read_unlock_buffer_slave(void)
{
  verify_identifier_string("K5");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_read_unlock_buffer_slave();
}
void  adpthread_manager::adjoint_read_unlock_buffer_slave(void)
{ 
  // cout  << "adpthread_manager::adjoint_read_unlock_buffer_slave(void)" << endl;
  // write_lock_slave_buffer
  verify_identifier_string("L7");
  int sno=restore_int_value();
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 )
    pthread_cond_wait(scondition+sno,smutex+sno);
  verify_identifier_string("J5");
}


void adpthread_manager::read_unlock_buffer_slave(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  save_identifier_string("J5");
  current_bptr[sno]=transfer_buffer[sno];
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
  save_int_value(sno);
  save_identifier_string("L7");
  save_pointer_value(this);
  save_identifier_string("K5");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_read_unlock_buffer_slave);
}


double get_double_from_master(void * current_bptr, int sno);
double get_double_from_slave(void * current_bptr, int sno);

void adpthread_master_unpack_number_derivative(void)
{
  verify_identifier_string("F");
  void * ptr=restore_pointer_value();
  int sno=restore_int_value();
  verify_identifier_string("C");
  double dv=get_double_from_slave(ptr,sno);
  prevariable_position dvpos=restore_prevariable_position();
  verify_identifier_string("R5");
  save_double_derivative(dv,dvpos);
}

void send_dvariable_to_slave(const prevariable  &_x,void * current_bptr,
  int sno)
{
  ADUNCONST(prevariable,x)
  save_identifier_string("R5");
  x.save_prevariable_position();
  save_identifier_string("C");
  save_int_value(sno);
  save_pointer_value(current_bptr);
  save_identifier_string("F");
  //send_double_to_slave(value(x),current_bptr,sno);
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthread_master_unpack_number_derivative);
}

void adpthread_slave_unpack_number_derivative(void)
{
  verify_identifier_string("F1");
  void * ptr=restore_pointer_value();
  int sno=restore_int_value();
  verify_identifier_string("C");
  //cout << " getting  dv  from master" << endl;
  double dv=get_double_from_master(ptr,sno);
  //cout << "got "  << dv << " from master" << endl;
  prevariable_position dvpos=restore_prevariable_position();
  verify_identifier_string("S5");
  save_double_derivative(dv,dvpos);
}

void send_double_to_master(double &x,void * current_bptr,int sno);

void send_dvariable_to_master(const prevariable  &_x,
  void * current_bptr,int sno)
{
  ADUNCONST(prevariable,x)
  save_identifier_string("S5");
  x.save_prevariable_position();
  save_identifier_string("C");
  save_int_value(sno);
  save_pointer_value(current_bptr);
  save_identifier_string("F1");
  send_double_to_master(value(x),current_bptr,sno);
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthread_slave_unpack_number_derivative);
}


void pthread_master_unpack_vector_derivatives(void);

/*
void adpthread_manager::send_dvar_vector_to_slave_nl(const dvar_vector &x,
  int sno)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  // !!!!!
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  writebuffer(&(value(x(mmin))),sz*sizeof(double),sno);
  save_identifier_string("T");
  x.save_dvar_vector_position();
  save_identifier_string("G");
  save_pointer_value(current_bptr);
  save_int_value(sno);
  save_identifier_string("HH");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(pthread_master_unpack_vector_derivatives);
}
*/
dvector get_dvector_from_slave(void * current_bptr, int sno);

/*
void pthread_master_unpack_vector_derivatives(void)
{
  kkludge_object kk;
  verify_identifier_string("HH");
  int sno=restore_int_value();
  void * ptr=restore_pointer_value();
  verify_identifier_string("G");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  verify_identifier_string("T");
  dvector v=get_dvector_from_slave(ptr,sno);
  v.save_dvector_derivatives(dvpos);
}
*/
dvector get_dvector_from_master(void * current_bptr, int sno);

void pthread_slave_unpack_vector_derivatives(void)
{
  kkludge_object kk;
  verify_identifier_string("KH");
  int sno=restore_int_value();
  void * ptr=restore_pointer_value();
  save_identifier_string("G");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  verify_identifier_string("O");
  dvector v(dvpos,kk);
  v=get_dvector_from_master(ptr,sno);
  v.save_dvector_derivatives(dvpos);
}


void pthread_slave_unpack_vector_derivatives(void);

void adpthreads_slave_pack_number_derivative(void);

double get_double_from_slave(void * current_bptr, int sno);

/*
void adpthreads_master_pack_number_derivative(void)
{
  verify_identifier_string("G2");
  int sno=restore_int_value();
  void * ptr=restore_pointer_value();
  verify_identifier_string("D");
  prevariable_position dvpos=restore_prevariable_position();
  double dv=restore_prevariable_derivative(dvpos);
  //cout << "sending " << dv << " to master " << endl;
  //send_double_to_slave(dv,ptr,sno);
  //pvm_pack(dv);
  verify_identifier_string("C");
}

dvariable get_dvariable_from_slave(void * current_bptr, int sno)
{
  dvariable x;
  value(x)=get_double_from_slave(current_bptr,sno);
  save_identifier_string("C");
  x.save_prevariable_position();
  save_identifier_string("D");
  save_pointer_value(current_bptr);
  save_int_value(sno);
  save_identifier_string("G2");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthreads_master_pack_number_derivative);
  return x;
}
*/



void adpthread_manager::create_all(void *f ,thread_data * ptr)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_create(thread1+i,NULL,f,ptr+i);
  }
}
dvar_vector get_dvar_vector_from_master(void * current_bptr, int sno);

void adpthread_manager::pthread_join_all(void)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_join(thread1[i], NULL);
  }
}
void adpthread_manager::writebuffer(const void *x,int nbytes,int sno)
{
  check_buffer_size(nbytes,sno);
  ::memcpy(current_bptr[sno],x,nbytes);
  current_bptr[sno]+=nbytes;
}

void adpthread_manager::readbuffer(const void *_x,int nbytes,int sno)
{
  void * x= (void *)(_x); 
  check_buffer_size_read(nbytes,sno);
  ::memcpy(x,current_bptr[sno],nbytes);
  current_bptr[sno]+=nbytes;
}

double adpthread_manager::get_double_from_master_nl(int sno)
{
  double x;
  readbuffer(&x,sizeof(double),sno);
  return x;
}

void adpthread_manager::verify_id_string_from_master_nl(const char * s,int sno)
{
#if defined(CHK_ID_STRING)
  char s1[10];
  int sz=strlen(s);
  s1[sz]='\0';
  readbuffer(s1,sz,sno);
  if (strcmp(s,s1))
  {
    cerr << "Error verifying master string " << s << endl;
    ad_exit(1);
  }
#endif
}

void adpthread_manager::verify_id_string_from_slave_nl(const char * s,int sno)
{
#if defined(CHK_ID_STRING)
  char s1[10];
  int sz=strlen(s);
  s1[sz]='\0';
  readbuffer(s1,sz,sno);
  if (strcmp(s,s1))
  {
    cerr << "Error verifying slave string " << s << endl;
    ad_exit(1);
  }
#endif
}


void adpthread_manager::send_double_to_slave_nl(const double &x,int sno)
{
  writebuffer(&x,sizeof(double),sno);
}

void adpthread_manager::send_id_string_to_slave_nl(const char * x,int sno)
{
#if defined(CHK_ID_STRING)
  int sz=strlen(x);
  writebuffer(x,sz,sno);
#endif
}

void adpthread_manager::send_id_string_to_master_nl(const char * x,int sno)
{
#if defined(CHK_ID_STRING)
  int sz=strlen(x);
  writebuffer(x,sz,sno);
#endif
}


void adpthread_manager::send_dvariable_to_slave(const prevariable& x,int sno)
{
  ::send_dvariable_to_slave(x,current_bptr[sno],sno);
}
void adjoint_get_dvar_vector_from_master(void)
{
  verify_identifier_string("D4");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_get_dvar_vector_from_master();
}

void adpthread_manager::adjoint_get_dvar_vector_from_master(void)
{
  verify_identifier_string("K6");
  int sno=restore_int_value();
  verify_identifier_string("Y7");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  verify_identifier_string("C");
  send_id_string_to_master_nl("SUX",sno);
  dvector dv=restore_dvar_vector_derivatives(dvpos);
  int mmin=dv.indexmin();
  int mmax=dv.indexmax();
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  int sz=mmax-mmin+1;
  writebuffer(&(dv(mmin)),sz*sizeof(double),sno);
}
dvar_vector adpthread_manager::get_dvar_vector_from_master(int sno)
{
  int mmin;
  int mmax;
  readbuffer(&mmin,sizeof(int),sno);
  readbuffer(&mmax,sizeof(int),sno);
  // cout  << "In dvar_vector get_dvar_vector_from_master " << endl;
  // cout  << " mmin = " << mmin   << " mmax = " << mmax  << endl;
  dvar_vector x(mmin,mmax);
  int sz=mmax-mmin+1;
  readbuffer(&(value(x(mmin))),sz*sizeof(double),sno);
  save_identifier_string("C");
  x.save_dvar_vector_position();
  save_identifier_string("Y7");
  save_int_value(sno);
  save_identifier_string("K6");
  save_pointer_value(this);
  save_identifier_string("D4");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvar_vector_from_master);
  return x;
}

dvariable adpthread_manager::get_dvariable_from_master(int sno)
{
  return ::get_dvariable_from_master(current_bptr[sno],sno);
}
void adjoint_get_dvariable_from_slave(void)
{
  verify_identifier_string("G2");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_get_dvariable_from_slave();
}

void adpthread_manager::adjoint_get_dvariable_from_slave(void)
{
  verify_identifier_string("F7");
  int sno=restore_int_value();
  verify_identifier_string("D");
  prevariable_position dvpos=restore_prevariable_position();
  double dv=restore_prevariable_derivative(dvpos);
  verify_identifier_string("C");
  send_id_string_to_slave_nl("RUX",sno);
  writebuffer(&dv,sizeof(double),sno);
}

dvariable adpthread_manager::get_dvariable_from_slave(int sno)
{
  dvariable x;
  double cx;
  verify_id_string_from_slave_nl("BC",sno);
  readbuffer(&cx,sizeof(double),sno);
  value(x)=cx;
  save_identifier_string("C");
  x.save_prevariable_position();
  save_identifier_string("D");
  save_int_value(sno);
  save_identifier_string("F7");
  save_pointer_value(this);
  save_identifier_string("G2");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvariable_from_slave);
  return x;
}
void adjoint_send_dvariable_to_master(void)
{
  verify_identifier_string("FH");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_send_dvariable_to_master();
}

void adpthread_manager::adjoint_send_dvariable_to_master(void)
{
  verify_identifier_string("KK");
  int sno=restore_int_value();
  verify_id_string_from_master_nl("RUX",sno);
  verify_identifier_string("C");
  //double dv=restore_prevariable_derivative(dvpos);
  double dv;
  readbuffer(&dv,sizeof(double),sno);
  prevariable_position dvpos=restore_prevariable_position();
  save_double_derivative(dv,dvpos);
  verify_identifier_string("S5");
}

void adpthread_manager::send_dvariable_to_master(const prevariable& _x,int sno)
{
  ADUNCONST(prevariable,x)
  save_identifier_string("S5");
  x.save_prevariable_position();
  send_id_string_to_master_nl("BC",sno);
  double cx=value(x);
  writebuffer(&cx,sizeof(double),sno);
  save_identifier_string("C");
  save_int_value(sno);
  save_identifier_string("KK");
  save_pointer_value(this);
  save_identifier_string("FH");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_send_dvariable_to_master);
}

void adpthread_manager::send_double_to_master(double &x,int sno)
{
  ::send_double_to_master(x,current_bptr[sno],sno);
}

void adjoint_send_dvar_vector_to_slave(void)
{
  verify_identifier_string("UP");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_send_dvar_vector_to_slave();
}

void adpthread_manager::adjoint_send_dvar_vector_to_slave(void)
{
  verify_identifier_string("HH");
  int sno=restore_int_value();
  verify_identifier_string("OP");
  verify_id_string_from_slave_nl("SUX",sno);
  int mmin;
  int mmax;
  readbuffer(&mmin,sizeof(int),sno);
  readbuffer(&mmax,sizeof(int),sno);
  int sz=mmax-mmin+1;
  dvector x(mmin,mmax);
  readbuffer(&(x(mmin)),sz*sizeof(double),sno);
  dvar_vector_position dvpos=restore_dvar_vector_position();
  verify_identifier_string("T");
  x.save_dvector_derivatives(dvpos);
}

void adpthread_manager::send_dvar_vector_to_slave(const dvar_vector &x,int sno)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  writebuffer(&(value(x(mmin))),sz*sizeof(double),sno);
  save_identifier_string("T");
  x.save_dvar_vector_position();
  save_identifier_string("OP");
  save_int_value(sno);
  save_identifier_string("HH");
  save_pointer_value(this);
  save_identifier_string("UP");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvar_vector_to_slave);
    //set_gradient_stack(pthread_master_unpack_vector_derivatives);
}

void adpthread_manager::send_dvector_to_slave(const dvector &x,int sno)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  writebuffer(&(x(mmin)),sz*sizeof(double),sno);
  //::send_dvector_to_slave(x,current_bptr[sno],sno);
}

void adpthread_manager::send_dvector_to_master(const dvector &x,int sno)
{
  ::send_dvector_to_master(x,current_bptr[sno],sno);
}


double adpthread_manager::get_double_from_slave(int sno)
{
  return ::get_double_from_slave(current_bptr[sno],sno);
}

double adpthread_manager::get_double_from_master(int sno)
{
  return ::get_double_from_master(current_bptr[sno],sno);
}

dvector adpthread_manager::get_dvector_from_slave(int sno)
{
  return ::get_dvector_from_slave(current_bptr[sno],sno);
}

dvector adpthread_manager::get_dvector_from_master(int sno)
{
  return ::get_dvector_from_master(current_bptr[sno],sno);
}
adpthread_manager * test_thread_manager=0;

/*
void add_slave_suffix(const adstring& _tmpstring)
{
  ADUNCONST(adstring,tmpstring)
  if (test_thread_manager)
  {
    if (thread_data::id>0)
    {
      tmpstring += "_";
      tmpstring += str(thread_data::id);
       //cout << "In slave " << tmpstring << endl;
    }
    else
    {
      tmpstring += "_master";
       //cout << "In master " << tmpstring << endl;
    }
  }
}
*/


