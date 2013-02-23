// $Id: adpthread_manager.cpp 3054 2013-01-10 22:54:36Z jsibert $
#include <iostream>
using namespace std;
#include "adpthread_manager.h"
#include "pt_trace.h"

//pthread_rwlock_t * tb_lock;
pthread_mutex_t * smutex;
pthread_cond_t * scondition;
pthread_cond_t *mcondition;
int * mflag;
int * sflag;

int adpthread_manager::pt_res = 0;

void adpthread_manager::pt_result(const char *string, const char* file, 
                                  const int line)
{
  if (pt_res)
  {
    clogf << "line " << line << ", file " << file 
          << "Error code " << pt_res << ": " << strerror(pt_res)
          << " on " << string << endl;
    //ad_exit(1);
  }
  #ifdef SHOW_SUCCESSFUL
  else
  {
    clogf << "line " << line << ", file " << file
          << ": " << string << " successful." << endl;
  }
  #endif //#ifdef SHOW_SUCCESSFUL
  return;
}

  adpthread_manager::adpthread_manager(int ns,int bs)
  {
    TTRACE(ns,bs)
    nslaves=ns;
    transfer_buffer=new pchar[ns];
    transfer_buffer--;
    buffend=new pchar[ns];
    buffend--;
    tb_save=new pchar[ns];
    tb_save --;
    for (int i=1;i<=ns;i++)
    {
      transfer_buffer[i]=new char[bs];
      tb_save[i] = transfer_buffer[i];
      buffend[i]=transfer_buffer[i]+bs-1;
    }
    //tb_lock=new pthread_rwlock_t[ns+1];
    //tb_lock--;
    mflag=new int[ns];
    mflag--;
    sflag=new int[ns];
    sflag--;
    smutex=new pthread_mutex_t[ns];
    smutex--;
    scondition=new pthread_cond_t[ns];
    scondition--;
    mcondition=new pthread_cond_t[ns];
    mcondition--;
    thread1=new pthread_t[ns];
    thread1--;
    
    initialize();

    //::tb_lock = tb_lock;
    ::smutex = smutex;
    ::scondition = scondition;
    ::mcondition = mcondition;
    ::mflag = mflag;
    ::sflag = sflag;
  }


  adpthread_manager::~adpthread_manager()
  {
     HERE
     clogf <<"adpthread_manager::~adpthread_manager() called" << endl;
     delete[] thread1;
     delete[] mcondition;
     delete[] scondition;
     delete[] smutex;
     delete[] buffend;
     for (int i = 1; i <= nslaves; i++)
     {
       delete[] transfer_buffer[i];
     }
     delete[] transfer_buffer;
     HERE

  }

  void adpthread_manager::initialize(void)
  {
    HERE
    for (int i=1;i<=nslaves;i++)
    {
      pthread_mutex_lock(smutex+i);
      transfer_buffer[i]=tb_save[i];
      pthread_mutex_init(smutex+i,NULL);
      mflag[i] = 0;
      sflag[i] = 0;
      //smutex[i] = PTHREAD_MUTEX_INITIALIZER;
      scondition[i] = PTHREAD_COND_INITIALIZER;
      mcondition[i] = PTHREAD_COND_INITIALIZER;
      //tb_lock[i] = PTHREAD_RWLOCK_INITIALIZER;
      pthread_mutex_unlock(smutex+i);
    }
    HERE
  }
 
/** struct to hold data to be passed to a thread
   this shows how multiple data items can be passed to a thread */
union a_union {
    char * p;
    double d;
};
//a_union au;

void send_dvector_to_slave(const dvector &x,void * transfer_buffer,int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(mcondition+sno,smutex+sno);
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(x(mmin)),sz*sizeof(double));

  mflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(scondition+sno);
}

dvariable get_dvariable_from_slave(void * transfer_buffer, int sno)
{
  dvariable x;

  value(x)=get_double_from_slave(transfer_buffer,sno);
  TTRACE(sno,x)

  save_identifier_string("C");
  x.save_prevariable_position();
  save_identifier_string("D");
  save_pointer_value(transfer_buffer);
  save_int_value(sno);
  save_identifier_string("G2");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthreads_master_pack_number_derivative);
  return x;
}

double adpthread_manager::get_double_from_slave(int sno)
{
  return ::get_double_from_slave(transfer_buffer[sno],sno);
}

double get_double_from_slave(void * transfer_buffer, int sno)
{
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (sflag[sno] == 0) 
    pthread_cond_wait(mcondition+sno,smutex+sno);

  double x;
  memcpy(&x,transfer_buffer,sizeof(double));
  TTRACE(sno,x)

  sflag[sno] = 0;
  TTTRACE(sno,mflag[sno],sflag[sno])
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(scondition+sno);
  return x;
}

void adpthreads_master_pack_number_derivative(void)
{
  verify_identifier_string("G2");
  int sno=restore_int_value();
  void * ptr=restore_pointer_value();
  verify_identifier_string("D");
  prevariable_position dvpos=restore_prevariable_position();
  double dv=restore_prevariable_derivative(dvpos);
  cout << "sending " << dv << " to master " << endl;
  send_double_to_slave(dv,ptr,sno);
  //pvm_pack(dv);
  verify_identifier_string("C");
}

/*
double get_double_from_master(void * transfer_buffer, int sno)
{
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (mflag[sno] == 0) 
    pthread_cond_wait(scondition+sno,smutex+sno);

  double x;
  memcpy(&x,transfer_buffer,sizeof(double));

  mflag[sno] = 0;
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
  return x;
}

int get_int_from_master(void * transfer_buffer, int sno)
{

  TTTRACE(sno,mflag[sno],sflag[sno])
  adpthread_manager::pt_res =  pthread_mutex_lock(&smutex[sno]);
  // only read if buffer full and data is for you
  while (mflag[sno] == 0) 
  {
    adpthread_manager::pt_res =  pthread_cond_wait(&scondition[sno], &smutex[sno]);
  }

  int x = 0;
  memcpy(&x,transfer_buffer,sizeof(int));

  mflag[sno] = 0;
  adpthread_manager::pt_res = pthread_mutex_unlock(&smutex[sno]) ;
  adpthread_manager::pt_res = pthread_cond_signal(&scondition[sno]);

  clogf << "-------- got " << x << " from master in thread " << sno << endl;
  return x;
}

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

void adpthread_slave_unpack_number_derivative(void)
{
  verify_identifier_string("F1");
  void * ptr=restore_pointer_value();
  int sno=restore_int_value();
  verify_identifier_string("C");
  //cout << " getting  dv  from master" << endl;
  HERE
  double dv=get_double_from_master(ptr,sno);
  TRACE(dv)
  //cout << "got "  << dv << " from master" << endl;
  prevariable_position dvpos=restore_prevariable_position();
  verify_identifier_string("S5");
  save_double_derivative(dv,dvpos);
}

void send_double_to_master(const double x,void * transfer_buffer,int sno)
{
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  memcpy(transfer_buffer,&x,sizeof(double));
  sflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(mcondition+sno);
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
  TRACE(dv)
  send_double_to_master(dv,ptr,sno);
  //pvm_pack(dv);
  verify_identifier_string("C");
}

dvariable get_dvariable_from_master(void * transfer_buffer, int sno)
{
  dvariable x;
  value(x)=get_double_from_master(transfer_buffer,sno);
  save_identifier_string("C");
  x.save_prevariable_position();
  save_identifier_string("D");
  save_pointer_value(transfer_buffer);
  save_int_value(sno);
  save_identifier_string("G1");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthreads_slave_pack_number_derivative);
  return x;
}

void send_int_to_slave(const int x,void * transfer_buffer,int sno)
{
  clogf << dec << endl;
  TTRACE(sno,x)

  TTTRACE(sno,mflag[sno],sflag[sno])
  adpthread_manager::pt_res =  pthread_mutex_lock(&smutex[sno]);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
  {
    adpthread_manager::pt_res =  pthread_cond_wait(&scondition[sno],
                                                   &smutex[sno]);
  }
  
  TTRACE(sno,(void*)transfer_buffer)
  memcpy(transfer_buffer,&x,sizeof(int));

  mflag[sno] = 1;
  adpthread_manager::pt_res =  pthread_mutex_unlock(&smutex[sno]);
  adpthread_manager::pt_res =  pthread_cond_signal(&scondition[sno]);
  //TTTRACE(sno,mflag[sno],sflag[sno])
  clogf << "-------- sent " << x << " to slave in thread " << sno << endl;
}

void send_double_to_slave(const double x,void * transfer_buffer,int sno)
{
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(mcondition+sno,smutex+sno);

  memcpy(transfer_buffer,&x,sizeof(double));

  mflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(scondition+sno);
}

void send_dvariable_to_slave(const prevariable  &_x,void * transfer_buffer, int sno)
{
  ADUNCONST(prevariable,x)
  save_identifier_string("R5");
  x.save_prevariable_position();
  save_identifier_string("C");
  save_int_value(sno);
  save_pointer_value(transfer_buffer);
  save_identifier_string("F");
  send_double_to_slave(value(x),transfer_buffer,sno);
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthread_master_unpack_number_derivative);
}


void send_dvariable_to_master(const prevariable  &_x,
  void * transfer_buffer,int sno)
{
  TTRACE(sno,_x)
  ADUNCONST(prevariable,x)
  save_identifier_string("S5");
  x.save_prevariable_position();
  save_identifier_string("C");
  save_int_value(sno);
  save_pointer_value(transfer_buffer);
  save_identifier_string("F1");
  send_double_to_master(value(x),transfer_buffer,sno);
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthread_slave_unpack_number_derivative);
}

void adpthreads_slave_pack_vector_derivative(void)
{
  verify_identifier_string("G2");
  int sno=restore_int_value();
  //TRACE(sno)
  void * ptr=restore_pointer_value();
  verify_identifier_string("D");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  dvector dv=restore_dvar_vector_derivatives(dvpos);
  verify_identifier_string("C");
  char * b = (char*)(ptr);
  int mmin=dv.indexmin();
  int mmax=dv.indexmax();
  int sz=mmax-mmin+1;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
  {
    pthread_cond_wait(scondition+sno,smutex+sno);
  }

  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(dv(mmin)),sz*sizeof(double));
  
  sflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(mcondition+sno);
}

void adpthreads_slave_pack_matrix_derivative(void)
{
  verify_identifier_string("mG2");
  int sno=restore_int_value();
  //TRACE(sno)
  void * ptr=restore_pointer_value();
  //TRACE(ptr)
  verify_identifier_string("mD");
  dvar_matrix_position pos=restore_dvar_matrix_position();
  dmatrix dm=restore_dvar_matrix_derivatives(pos);
  verify_identifier_string("mC");

  //TTTRACE(sno,rowmin,rowmax)
  //int sz=rowmax - rowmin+1;

  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  TTTRACE(sno,mflag[sno],sflag[sno]) 
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
  {
    pthread_cond_wait(scondition+sno,smutex+sno);
  }
  TTTRACE(sno,mflag[sno],sflag[sno]) 
  char * b = (char*)(ptr);
  int rowmin=dm.rowmin();
  int rowmax=dm.rowmax();

  memcpy(b,&rowmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&rowmax,sizeof(int));
  b+=sizeof(int);
  TTTRACE(sno,mflag[sno],sflag[sno]) 

  ivector ncl(rowmin,rowmax);
  ivector nch(rowmin,rowmax);
  for (int i = rowmin; i<= rowmax; i++)
  {
     ncl(i) = dm(i).indexmin();
     nch(i) = dm(i).indexmax();
  }
  TTTRACE(sno,mflag[sno],sflag[sno]) 
  for (int i = rowmin; i<= rowmax; i++)
  {
    TTTRACE(i,mflag[sno],sflag[sno]) 
    memcpy(b,&(ncl(i)),sizeof(int));
    TTTRACE(i,mflag[sno],sflag[sno]) 
    b+= sizeof(int);
    TTRACE((void*)b,(void*)ptr)
  }
  TTTRACE(sno,mflag[sno],sflag[sno]) 
  //TTTRACE(sno,ncl,sum(ncl))
  for (int i = rowmin; i<= rowmax; i++)
  {
    memcpy(b,&(nch(i)),sizeof(int));
    b+= sizeof(int);
  }
  TTTRACE(sno,mflag[sno],sflag[sno]) 
  //TTTRACE(sno,nch,sum(nch))

  for (int i = rowmin; i<= rowmax; i++)
  {
    int sz = nch(i)-ncl(i) + 1;
    memcpy(b, &dm(i,ncl(i)),sz*sizeof(double));
    b += sz*sizeof(double);
  }
  
  TTTRACE(sno,mflag[sno],sflag[sno]) 
  sflag[sno] = 1;
  TTTRACE(sno,mflag[sno],sflag[sno]) 
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(mcondition+sno);
}

dvar_vector get_dvar_vector_from_master(void * transfer_buffer, int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin;
  int mmax;
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (mflag[sno] == 0) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  mflag[sno] = 0;

  memcpy(&mmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&mmax,b,sizeof(int));
  b+=sizeof(int);
  dvar_vector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(value(x(mmin))),b,sz*sizeof(double));

  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
  save_identifier_string("C");
  x.save_dvar_vector_position();
  save_identifier_string("D");
  save_pointer_value(transfer_buffer);
  save_int_value(sno);
  save_identifier_string("G2");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthreads_slave_pack_vector_derivative);
  return x;
}
 
dvar_matrix adpthread_manager::get_dvar_matrix_from_master(int sno)
{

  //TRACE(sno)

  pt_res = pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (mflag[sno] == 0) 
  {
    pt_res = pthread_cond_wait(scondition+sno,smutex+sno);
  }

  char * b = (char*)(transfer_buffer[sno]);
  int rowmin= 0;
  int rowmax= 0;
  memcpy(&rowmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&rowmax,b,sizeof(int));
  b+=sizeof(int);
  //TTTRACE(sno,rowmin,rowmax)
 
  ivector ncl(rowmin,rowmax);
  for (int i = rowmin; i <= rowmax; i++)
  {
     memcpy(&ncl(i),b,sizeof(int));
     b+=sizeof(int);
  }
  //TTTRACE(sno,ncl,sum(ncl)) 

  ivector nch(rowmin,rowmax);
  for (int i = rowmin; i <= rowmax; i++)
  {
     memcpy(&nch(i),b,sizeof(int));
     b+=sizeof(int);
  }
  //TTTRACE(sno,nch,sum(nch)) 

  dvar_matrix x(rowmin,rowmax,ncl,nch);
  for (int i = rowmin; i <= rowmax; i++)
  {
     int sz = nch(i) - ncl(i) + 1;
     memcpy(&(value(x(i,ncl(i)))),b,sz*sizeof(double));
     b += sz*sizeof(double);
  }
  //TTRACE(sno,sum(value(x)))

  save_identifier_string("mC");
  x.save_dvar_matrix_position();
  save_identifier_string("mD");
  save_pointer_value(transfer_buffer);
  save_int_value(sno);
  save_identifier_string("mG2");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(adpthreads_slave_pack_matrix_derivative);

  mflag[sno] = 0;
  pt_res = pthread_mutex_unlock(smutex+sno);
  pt_res = pthread_cond_signal(mcondition+sno);
  return x;
}
 
ivector get_ivector_from_slave(void * transfer_buffer, int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin;
  int mmax;
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (sflag[sno] == 0) pthread_cond_wait(mcondition+sno,smutex+sno);
  sflag[sno] = 0;
  memcpy(&mmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&mmax,b,sizeof(int));
  b+=sizeof(int);
  ivector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(x(mmin)),b,sz*sizeof(int));
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(scondition+sno);
  return x;
}

dvector get_dvector_from_slave(void * transfer_buffer, int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin;
  int mmax;
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (sflag[sno] == 0) pthread_cond_wait(mcondition+sno,smutex+sno);
  sflag[sno] = 0;
  memcpy(&mmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&mmax,b,sizeof(int));
  b+=sizeof(int);
  dvector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(x(mmin)),b,sz*sizeof(double));
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(scondition+sno);
  return x;
}

dmatrix get_dmatrix_from_slave(void * transfer_buffer, int sno)
{
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (sflag[sno] == 0)
  {
    pthread_cond_wait(mcondition+sno,smutex+sno);
  }

  char * b = (char*)(transfer_buffer);
  int rowmin= 0;
  int rowmax= 0;
  memcpy(&rowmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&rowmax,b,sizeof(int));
  b+=sizeof(int);
 
  ivector ncl(rowmin,rowmax);
  for (int i = rowmin; i <= rowmax; i++)
  {
     memcpy(&ncl(i),b,sizeof(int));
     b+=sizeof(int);
  }
  //TTRACE(ncl,sum(ncl))
  ivector nch(rowmin,rowmax);
  for (int i = rowmin; i <= rowmax; i++)
  {
     memcpy(&nch(i),b,sizeof(int));
     b+=sizeof(int);
  }
  //TTRACE(nch,sum(nch))

  dmatrix x(rowmin,rowmax,ncl,nch);
  //TTRACE(x.rowmin(),x.rowmax())
  //TRACE(x.colmin())
  //TRACE(x.colmax())
  for (int i = rowmin; i <= rowmax; i++)
  {
     const int sz = nch(i) - ncl(i) + 1;
     const int j = ncl(i);
     //TTRACE(i,j)
     memcpy(&x(i,j),b,sz*sizeof(double));
     //memcpy(&x(i,ncl(i)),b,sz*sizeof(double));
     b += sz*sizeof(double);
  }

  sflag[sno] = 0;
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(scondition+sno);
  return x;
}

void pthread_master_unpack_vector_derivatives(void)
{
  kkludge_object kk;
  verify_identifier_string("HH");
  int sno=restore_int_value();
  //TRACE(sno)
  void * ptr=restore_pointer_value();
  //TRACE(ptr)
  verify_identifier_string("G");
  dvar_vector_position dvpos=restore_dvar_vector_position();
  verify_identifier_string("T");
  dvector v=get_dvector_from_slave(ptr,sno);
  v.save_dvector_derivatives(dvpos);
}

void pthread_master_unpack_matrix_derivatives(void)
{
  kkludge_object kk;
  verify_identifier_string("mHH");
  int sno=restore_int_value();
  //TRACE(sno)
  void * ptr=restore_pointer_value();
  //TRACE(ptr)
  verify_identifier_string("mG");
  dvar_matrix_position dmpos=restore_dvar_matrix_position();
  //TTRACE(dmpos.rowmin(),dmpos.rowmax())
  //TRACE(dmpos.colmin())
  //TRACE(dmpos.colmax())
  //for (int i = dmpos.rowmin(); i <= dmpos.rowmax(); i++)
 // {
  //   TTRACE(dmpos.lb(i),dmpos.ub(i));
  //}
  verify_identifier_string("mT");
  dmatrix v(dmpos);

  //TTRACE(v.rowmin(),v.rowmax())
  ivector vncl(v.rowmin(),v.rowmax());
  ivector vnch(v.rowmin(),v.rowmax());
  for (int i = v.rowmin(); i <= v.rowmax(); i++)
  {
     vncl(i) = v(i).indexmin();
     vnch(i) = v(i).indexmax();
  }
  //TTRACE(vncl,sum(vncl))
  //TTRACE(vnch,sum(vnch))

  dmatrix tv=get_dmatrix_from_slave(ptr,sno);
  //TTRACE(tv.rowmin(),tv.rowmax())
  ivector tvncl(tv.rowmin(),tv.rowmax());
  ivector tvnch(tv.rowmin(),tv.rowmax());
  for (int i = tv.rowmin(); i <= tv.rowmax(); i++)
  {
     tvncl(i) = tv(i).indexmin();
     tvnch(i) = tv(i).indexmax();
  }
  //TTRACE(tvncl,sum(tvncl))
  //TTRACE(tvnch,sum(tvnch))

  //v = tv;
  for (int i = v.rowmin(); i <= v.rowmax(); i++)
  {
     //TTRACE(v(i).indexmin(),v(i).indexmax())
     //TTRACE(tv(i).indexmin(),tv(i).indexmax())
     for (int j = v(i).indexmin(); j <= v(i).indexmax(); j++)
     {
        //TTRACE(i,j)
        v(i,j) = tv(i,j);
     }
  }

  v.save_dmatrix_derivatives(dmpos);
}

void send_dvar_vector_to_slave(const dvar_vector &x,void * transfer_buffer,int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(mcondition+sno,smutex+sno);
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(value(x(mmin))),sz*sizeof(double));

  save_identifier_string("T");
  x.save_dvar_vector_position();
  save_identifier_string("G");
  save_pointer_value(transfer_buffer);
  save_int_value(sno);
  save_identifier_string("HH");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(pthread_master_unpack_vector_derivatives);

  mflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(scondition+sno);
}

void send_ivector_to_slave(const ivector &x,void * transfer_buffer,int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(mcondition+sno,smutex+sno);
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(x(mmin)),sz*sizeof(int));

  mflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(scondition+sno);
}
void send_dvector_to_master(const dvector &x,void * transfer_buffer,int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(x(mmin)),sz*sizeof(double));
  sflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(mcondition+sno);
}

ivector get_ivector_from_master(void * transfer_buffer, int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin;
  int mmax;
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (mflag[sno] == 0) pthread_cond_wait(scondition+sno,smutex+sno);
  mflag[sno] = 0;
  memcpy(&mmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&mmax,b,sizeof(int));
  b+=sizeof(int);
  ivector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(x(mmin)),b,sz*sizeof(int));
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
  return x;
}

dvector get_dvector_from_master(void * transfer_buffer, int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin;
  int mmax;
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (mflag[sno] == 0) pthread_cond_wait(scondition+sno,smutex+sno);
  mflag[sno] = 0;
  memcpy(&mmin,b,sizeof(int));
  b+=sizeof(int);
  memcpy(&mmax,b,sizeof(int));
  b+=sizeof(int);
  dvector x(mmin,mmax);
  int sz=mmax-mmin+1;
  memcpy(&(x(mmin)),b,sz*sizeof(double));
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
  return x;
}

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

void send_dvar_vector_to_master(const dvar_vector &x,void * transfer_buffer,int sno)
{
  char * b = (char*)(transfer_buffer);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);

  memcpy(b,&(value(x(mmin))),sz*sizeof(double));
  save_identifier_string("O");
  x.save_dvar_vector_position();
  save_identifier_string("G");
  au.p=transfer_buffer;
  save_double_value(au.d);
  save_identifier_string("KH");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(pthread_slave_unpack_vector_derivatives);
  sflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(mcondition+sno);

}

void adpthread_manager::send_dvar_matrix_to_slave(const dvar_matrix &x,int sno)
{
  pt_res = pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
  {
    pt_res = pthread_cond_wait(scondition+sno,smutex+sno);
  }

  char * b = (char*)(transfer_buffer[sno]);
  int rowmin=x.rowmin();
  int rowmax=x.rowmax();
  //TTRACE(rowmin,rowmax)

  memcpy(b,&rowmin,sizeof(int));
  b+=sizeof(int);
  
  memcpy(b,&rowmax,sizeof(int));
  b+=sizeof(int);

  ivector ncl(rowmin,rowmax);
  ivector nch(rowmin,rowmax);
  for (int i = rowmin; i<= rowmax; i++)
  {
     ncl(i) = x(i).indexmin();
     nch(i) = x(i).indexmax();
  }
  //TTRACE(ncl,sum(ncl))
  //TTRACE(nch,sum(nch))
  for (int i = rowmin; i<= rowmax; i++)
  {
    memcpy(b,&(ncl(i)),sizeof(int));
    b+= sizeof(int);
  }
  for (int i = rowmin; i<= rowmax; i++)
  {
    memcpy(b,&(nch(i)),sizeof(int));
    b+= sizeof(int);
  }

  for (int i = rowmin; i<= rowmax; i++)
  {
    int sz = nch(i)-ncl(i) + 1;
    memcpy(b, &(value(x(i,ncl(i)))),sz*sizeof(double));
    b += sz*sizeof(double);
  }
  
  save_identifier_string("mT");
  x.save_dvar_matrix_position();
  save_identifier_string("mG");
  //TRACE(transfer_buffer)
  save_pointer_value(transfer_buffer);
  //TRACE(sno)
  save_int_value(sno);
  save_identifier_string("mHH");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(pthread_master_unpack_matrix_derivatives);

  mflag[sno] = 1;
  pt_res = pthread_mutex_unlock(smutex+sno);
  pt_res = pthread_cond_signal(scondition+sno);

}
 

void adpthread_manager::create_all(void *f ,thread_data * ptr)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_create(thread1+i,NULL,f,ptr+i);
//int pthread_create(pthread_t *thread, 
//                   const pthread_attr_t *attr, // NULL
//                   void *(*start_routine) (void *),  // f
//                   void *arg  // ptr);
  }
}

void adpthread_manager::pthread_join_all(void)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_cond_signal(scondition+i);
    pthread_cond_signal(mcondition+i);
    pthread_join(thread1[i], NULL);
  }
}

void add_slave_suffix(const adstring& _tmpstring)
{
  ADUNCONST(adstring,tmpstring)
  //if (test_thread_manager)
  {
    if (thread_data::id>0)
    {
      tmpstring += "_";
      tmpstring += str(thread_data::id);
       cout << "In slave " << tmpstring << endl;
    }
    else
    {
      tmpstring += "_master";
       cout << "In master " << tmpstring << endl;
    }
  }
}


void adpthread_manager::send_double_to_slave(const double x,int sno)
{
  ::send_double_to_slave(x,transfer_buffer[sno],sno);
}

void adpthread_manager::send_dvariable_to_slave(const prevariable& x,int sno)
{
  ::send_dvariable_to_slave(x,transfer_buffer[sno],sno);
}

dvar_vector adpthread_manager::get_dvar_vector_from_master(int sno)
{
  return ::get_dvar_vector_from_master(transfer_buffer[sno],sno);
}

dvariable adpthread_manager::get_dvariable_from_master(int sno)
{
  return ::get_dvariable_from_master(transfer_buffer[sno],sno);
}

dvariable adpthread_manager::get_dvariable_from_slave(int sno)
{
  return ::get_dvariable_from_slave(transfer_buffer[sno],sno);
}

void adpthread_manager::send_dvariable_to_master(const prevariable& x,int sno)
{
  ::send_dvariable_to_master(x,transfer_buffer[sno],sno);
}

void adpthread_manager::send_double_to_master(const double x,int sno)
{
  ::send_double_to_master(x,transfer_buffer[sno],sno);
}


void adpthread_manager::send_dvar_vector_to_slave(const dvar_vector &x,int sno)
{
  char * b = (char*)(transfer_buffer[sno]);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(mcondition+sno,smutex+sno);

  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(value(x(mmin))),sz*sizeof(double));

  save_identifier_string("T");
  x.save_dvar_vector_position();
  save_identifier_string("G");
  save_pointer_value(transfer_buffer);
  save_int_value(sno);
  save_identifier_string("HH");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(pthread_master_unpack_vector_derivatives);

  mflag[sno] = 1;
  pthread_mutex_unlock(smutex+sno);
  pthread_cond_signal(scondition+sno);
}


int adpthread_manager::get_int_from_master(int sno)
{
  return ::get_int_from_master(transfer_buffer[sno],sno);
}

void adpthread_manager::send_dvector_to_slave(const dvector &x,int sno)
{
  ::send_dvector_to_slave(x,transfer_buffer[sno],sno);
}

void adpthread_manager::send_ivector_to_slave(const ivector &x,int sno)
{
  ::send_ivector_to_slave(x,transfer_buffer[sno],sno);
}
void adpthread_manager::send_dvector_to_master(const dvector &x,int sno)
{
  ::send_dvector_to_master(x,transfer_buffer[sno],sno);
}

void adpthread_manager::send_int_to_slave(const int x,int sno)
{
  ::send_int_to_slave(x,transfer_buffer[sno],sno);
}


double adpthread_manager::get_double_from_master(int sno)
{
  return ::get_double_from_master(transfer_buffer[sno],sno);
}

ivector adpthread_manager::get_ivector_from_slave(int sno)
{
  return ::get_ivector_from_slave(transfer_buffer[sno],sno);
}

ivector adpthread_manager::get_ivector_from_master(int sno)
{
  return ::get_ivector_from_master(transfer_buffer[sno],sno);
}

dvector adpthread_manager::get_dvector_from_master(int sno)
{
  return ::get_dvector_from_master(transfer_buffer[sno],sno);
}
*/
