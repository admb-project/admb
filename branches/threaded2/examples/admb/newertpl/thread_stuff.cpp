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
typedef pchar *  ppchar;
typedef ofstream * pofstream;
__ADMBTHREAD__ int adpthread_manager::slave_number;

int adpthread_manager::old_buffer_flag=0;

adpthread_manager::~adpthread_manager()
{
  //cerr << "called adpthread_manager::~adpthread_manager(); nslaves = "
  //     << nslaves << endl;
  int i;
  for (i=0;i<nslaves;i++)
  {
    ssmutex[i]+=i+1;
    delete [] ssmutex[i];
    ssmutex[i]=0;
  }
  delete [] ssmutex;
  ssmutex=0;
  ppf++;
  delete [] ppf;
  ppf=0;
  thread1++;
  delete [] thread1;
  thread1=0;
  buffend++;
  delete [] buffend;
  buffend=0;
  current_bptr++;
  delete [] current_bptr;
  current_bptr=0;
  for (i=0;i<nslaves;i++)
  {
    for (int j=i+1;j<=nslaves;j++)
    {
      if (stransfer_buffer[i][j])
      {
        delete [] stransfer_buffer[i][j];
        stransfer_buffer[i][j]=0;
      }
    }
  }
  for (i=0;i<nslaves;i++)
  {
    stransfer_buffer[i]+=i+1;
    delete [] stransfer_buffer[i];
    stransfer_buffer[i]=0;
  }
  delete [] stransfer_buffer;
  stransfer_buffer=0;
}

adpthread_manager::adpthread_manager(int ns,int bs) : buffer_size(1,ns),
  mflag(1,ns), sflag(1,ns), num_in_group(1,1),ngroups(1),
  initial_buffer_size(bs)
{
  num_in_group=ns;
  gmin.allocate(1,ngroups);
  gmax.allocate(1,ngroups);
  gmin(1)=1;
  gmax(1)=gmin(1)+num_in_group(1)-1;
  logflag=0;
  mflag.initialize();
  sflag.initialize();
  int i;
  buffer_size=bs;
  nslaves=ns;
  transfer_buffer=new pchar[ns];
  current_bptr=new pchar[ns];
  current_bptr--;
  buffend=new pchar[ns];
  transfer_buffer--;
  buffend--;
  // for timing 0 is for master 1-n for slaves
  if (logflag)
  {
    adt=new adtimer[ns+1];
    logfiles=new pofstream[ns+1]; 
    adstring fname="log_master";
    logfiles[0]=new ofstream(fname);
    for (i=1;i<=ns;i++)
    {
      adstring fname="log_slave_" + str(i);
      logfiles[i]=new ofstream(fname);
    }
  }
  ssflag.allocate(0,ns-1);
  smflag.allocate(0,ns-1);
  for (i=0;i<ns;i++)
  {
    ssflag(i).allocate(i+1,ns);
    smflag(i).allocate(i+1,ns);
  }
  smflag.initialize();
  ssflag.initialize();
  
  for (i=1;i<=ns;i++)
  {
    transfer_buffer[i]=new char[bs];
    current_bptr[i]=transfer_buffer[i];
    buffend[i]=transfer_buffer[i]+bs-1;
  }
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
  for (i=1;i<=ns;i++)
  {
    pthread_cond_init(scondition+i,0);
    pthread_cond_init(mcondition+i,0);
  }
  thread1=new pthread_t[ns];
  thread1--;
  pthread_mutex_init(&copy_mutex,NULL);
  pthread_mutex_init(&start_mutex,NULL);
  ssmutex=new ppthread_mutex_t[ns];
  for (i=0;i<ns;i++)
  {
    ssmutex[i]=new pthread_mutex_t[ns-i];
    ssmutex[i]-=i+1;
  }
  sbuffer_size.allocate(0,ns-1);
  for (i=0;i<ns;i++)
  {
    sbuffer_size(i).allocate(i+1,ns);
  }
  sbuffer_size.initialize();

  stransfer_buffer=new ppchar[ns];

  for (i=0;i<ns;i++)
  {
    stransfer_buffer[i]=new pchar[ns-i];
    stransfer_buffer[i]-=i+1;
  }
  scurrent_bptr=new ppchar[ns];
  for (i=0;i<ns;i++)
  {
    scurrent_bptr[i]=new pchar[ns-i];
    scurrent_bptr[i]-=i+1;
  }

  sbuffend=new ppchar[ns];
  for (i=0;i<ns;i++)
  {
    sbuffend[i]=new pchar[ns-i];
    sbuffend[i]-=i+1;
  }

  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      stransfer_buffer[i][j]=0;
      scurrent_bptr[i][j]=0;
      sbuffend[i][j]=0;
    }
  }
  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      pthread_mutex_init(ssmutex[i]+j,NULL);
    }
  }
  sscondition=new ppthread_cond_t[ns];
  for (i=0;i<ns;i++)
  {
    sscondition[i]=new pthread_cond_t[ns-i];
    sscondition[i]-=i+1;
  }
  
  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      pthread_cond_init(sscondition[i]+j,NULL);
    }
  }

  smcondition=new ppthread_cond_t[ns];
  for (i=0;i<ns;i++)
  {
    smcondition[i]=new pthread_cond_t[ns-i];
    smcondition[i]-=i+1;
  }
  
  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      pthread_cond_init(smcondition[i]+j,NULL);
    }
  }
}
adpthread_manager::adpthread_manager(int _ngroups,ivector& _num_in_group,int bs)
  : num_in_group(_num_in_group),ngroups(_ngroups),initial_buffer_size(bs)
{
  int ns=sum(num_in_group);
  gmin.allocate(1,ngroups);
  gmax.allocate(1,ngroups);
  gmin(1)=1;
  gmax(1)=gmin(1)+num_in_group(1)-1;
  for (int i=2;i<=ngroups;i++)
  {
    gmin(i)=gmax(i-1)+1;
    gmax(i)=gmin(i)+num_in_group(i)-1;
  }
    
  nslaves=ns;
  buffer_size.allocate(1,ns),
  mflag.allocate(1,ns);
  sflag.allocate(1,ns); 
  logflag=1;
  mflag.initialize();
  sflag.initialize();
  int i;
  buffer_size=bs;
  transfer_buffer=new pchar[ns];
  current_bptr=new pchar[ns];
  current_bptr--;
  buffend=new pchar[ns];
  transfer_buffer--;
  buffend--;
  // for timing 0 is for master 1-n for slaves
  if (logflag)
  {
    adt=new adtimer[ns+1];
    logfiles=new pofstream[ns+1]; 
    adstring fname="log_master";
    logfiles[0]=new ofstream(fname);
    for (i=1;i<=ns;i++)
    {
      adstring fname="log_slave_" + str(i);
      logfiles[i]=new ofstream(fname);
    }
  }
  
  for (i=1;i<=ns;i++)
  {
    transfer_buffer[i]=new char[bs];
    current_bptr[i]=transfer_buffer[i];
    buffend[i]=transfer_buffer[i]+bs-1;
  }
  smutex=new pthread_mutex_t[ns];
  smutex--;
  pthread_mutex_init(&copy_mutex,NULL);
  pthread_mutex_init(&start_mutex,NULL);
  for (i=1;i<=ns;i++)
  {
    pthread_mutex_init(smutex+i,NULL);
  }
  scondition=new pthread_cond_t[ns];
  scondition--;
  mcondition=new pthread_cond_t[ns];
  mcondition--;
  for (i=1;i<=ns;i++)
  {
    pthread_cond_init(scondition+i,0);
    pthread_cond_init(mcondition+i,0);
  }
  thread1=new pthread_t[ns];
  thread1--;
  ppf = new pthreadfun[ngroups];
  ppf--;
  for (i=1;i<=ngroups;i++)
  {
    ppf[i]= (pthreadfun)(0);
  }
  num_code=0;
  ssflag.allocate(0,ns-1);
  smflag.allocate(0,ns-1);
  for (i=0;i<ns;i++)
  {
    ssflag(i).allocate(i+1,ns);
    smflag(i).allocate(i+1,ns);
  }
  smflag.initialize();
  ssflag.initialize();

  ssmutex=new ppthread_mutex_t[ns];
  for (i=0;i<ns;i++)
  {
    ssmutex[i]=new pthread_mutex_t[ns-i];
    ssmutex[i]-=i+1;
  }
  sbuffer_size.allocate(0,ns-1);
  for (i=0;i<ns;i++)
  {
    sbuffer_size(i).allocate(i+1,ns);
  }
  sbuffer_size.initialize();

  stransfer_buffer=new ppchar[ns];

  for (i=0;i<ns;i++)
  {
    stransfer_buffer[i]=new pchar[ns-i];
    stransfer_buffer[i]-=i+1;
  }
  scurrent_bptr=new ppchar[ns];
  for (i=0;i<ns;i++)
  {
    scurrent_bptr[i]=new pchar[ns-i];
    scurrent_bptr[i]-=i+1;
  }

  sbuffend=new ppchar[ns];
  for (i=0;i<ns;i++)
  {
    sbuffend[i]=new pchar[ns-i];
    sbuffend[i]-=i+1;
  }

  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      stransfer_buffer[i][j]=0;
      scurrent_bptr[i][j]=0;
      sbuffend[i][j]=0;
    }
  }
  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      pthread_mutex_init(ssmutex[i]+j,NULL);
    }
  }
  sscondition=new ppthread_cond_t[ns];
  for (i=0;i<ns;i++)
  {
    sscondition[i]=new pthread_cond_t[ns-i];
    sscondition[i]-=i+1;
  }
  
  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      pthread_cond_init(sscondition[i]+j,NULL);
    }
  }

  smcondition=new ppthread_cond_t[ns];
  for (i=0;i<ns;i++)
  {
    smcondition[i]=new pthread_cond_t[ns-i];
    smcondition[i]-=i+1;
  }
  
  for (i=0;i<ns;i++)
  {
    for (int j=i+1;j<=ns;j++)
    {
      pthread_cond_init(smcondition[i]+j,NULL);
    }
  }
}

void adpthread_manager::attach_code(pthreadfun pf)
{
  ppf[++num_code]=pf;
}

void adpthread_manager::check_buffer_size_read(int nbytes,int sno)
{
  
  // if the buffer is too small on read there is an error
  if (current_bptr[sno]+nbytes>buffend[sno])
  {
    std::ptrdiff_t pd=current_bptr[sno]-transfer_buffer[sno];
    std::ptrdiff_t pd1=buffend[sno]-transfer_buffer[sno];
    cout << "current offset is " << pd << " bytes " << endl;
    cout << "trying to read  " << nbytes << " bytes " << endl;
    cout << "buffend is at     " << pd1 << " bytes " << endl;
    cerr << "error reading from master slave buffer for slave "
         << sno << endl;
    ad_exit(1);
  }
}

void adpthread_manager::check_buffer_size_read(int nbytes,int s1,int s2)
{
  if (stransfer_buffer[s1][s2]== 0)
  {
    transfer_buffer[s1][s2]=new char[bs];
    scurrent_bptr[s1][s2]=transfer_buffer[s1][s2];
    sbuffend[s1][s2]=stransfer_buffer[s1][s2]+bs-1;
    cout << "Initialized transfer buffer for pair " 
         << s1 << "  " << s2 << endl;
  }
  
  // if the buffer is too small on read theree is an error
  if (scurrent_bptr[s1][s2]+nbytes>sbuffend[s1][s2])
  {
    std::ptrdiff_t pd=scurrent_bptr[s1][s2]-stransfer_buffer[s1][s2];
    std::ptrdiff_t pd1=sbuffend[s1][s2]-stransfer_buffer[s1][s2];
    cout << "current offset is " << pd << " bytes " << endl;
    cout << "trying to read  " << nbytes << " bytes " << endl;
    cout << "sbuffend is at     " << pd1 << " bytes " << endl;
    cerr << "error reading from  buffer for pair "
         << s1 << "  " << s2 << endl;
    ad_exit(1);
  }
}
void adpthread_manager::check_buffer_size(int nbytes,int s1,int s2)
{
  // if the buffer is too small make it bigger and copy old
  // buffer contents
  if (scurrent_bptr[s1][s2]+nbytes>sbuffend[s1][s2])
  {
    std::ptrdiff_t pd=scurrent_bptr[s1][s2]-stransfer_buffer[s1][s2];
    std::ptrdiff_t pd1=sbuffend[s1][s2]-stransfer_buffer[s1][s2];
    cout << "scurrent offset is " << pd << " bytes " << endl;
    cout << "trying to write " << nbytes << " bytes " << endl;
    cout << "scurrent sbuffend is at " << pd1 << " bytes " << endl;
    cerr << "master increasing master slave buffer for pair "
         << s1  << "  "  << s2 << endl;
    if (sbuffer_size(s1,s2)==0)
    {
      sbuffer_size(s1,s2)=initial_buffer_size;
      stransfer_buffer[s1][s2]=new char[sbuffer_size(s1,s2)];
      scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2];
    }
    else
    {
      char * tmp=stransfer_buffer[s1][s2];
      sbuffer_size(s1,s2)*=2;
      stransfer_buffer[s1][s2]=new char[sbuffer_size(s1,s2)];
      ::memcpy(stransfer_buffer[s1][s2],tmp,pd+1);
      scurrent_bptr[s1][s2]=stransfer_buffer[s1][s2]+pd;
      delete [] tmp;
      tmp=0;
    }
    sbuffend[s1][s2]=stransfer_buffer[s1][s2]+sbuffer_size(s1,s2)-1;
    std::ptrdiff_t pd2=sbuffend[s1][s2]-stransfer_buffer[s1][s2];
    cout << " new sbuffend is at " << pd2 << " bytes " << endl;
  }
}


/*
void adpthread_manager::check_buffer_size(int nbytes,int sno)
{
  // if the buffer is too small make it bigger and copy old
  // buffer contents
  if (current_bptr[sno]+nbytes>buffend[sno])
  {
    std::ptrdiff_t pd=current_bptr[sno]-transfer_buffer[sno];
    std::ptrdiff_t pd1=buffend[sno]-transfer_buffer[sno];
    cout << "current offset is " << pd << " bytes " << endl;
    cout << "trying to write " << nbytes << " bytes " << endl;
    cout << "current buffend is at " << pd1 << " bytes " << endl;
    cerr << "master increasing master slave buffer for slave "
         << sno << endl;
    char * tmp=transfer_buffer[sno];
    buffer_size[sno]*=2;
    transfer_buffer[sno]=new char[buffer_size[sno]];
    ::memcpy(transfer_buffer[sno],tmp,pd+1);
    current_bptr[sno]=transfer_buffer[sno]+pd;
    delete [] tmp;
    tmp=0;
    buffend[sno]=transfer_buffer[sno]+buffer_size[sno]-1;
    std::ptrdiff_t pd2=buffend[sno]-transfer_buffer[sno];
    cout << " new buffend is at " << pd2 << " bytes " << endl;
  }
}
*/

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
  // !!!!!!!!!!!!!!!!!!!!
  //pthread_cond_signal(mcondition+sno);
  pthread_cond_signal(scondition+sno);
  if (logflag)
  {
    double tm=adt[0].get_elapsed_time_and_reset();
    *(logfiles[0]) << tm << " adjoint_write_lock_buffer_master"   << endl;
  }
}
void adpthread_manager::write_lock_buffer_master(int sno)
{
  if (logflag)
  {
    *(logfiles[0]) << " write_lock_buffer_master"   << endl;
    adt[0].get_elapsed_time_and_reset();
  }
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
  if (logflag)
  {
    double tm=adt[0].get_elapsed_time_and_reset();
    *(logfiles[0]) << tm << " adjoint_read_lock_buffer_master" << endl;
  }
}


void adpthread_manager::read_lock_buffer_master(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  if (logflag)
  {
    *(logfiles[0]) << "starting read_lock_buffer_master " << sno   << endl;
    adt[0].get_elapsed_time_and_reset();
  }

  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  int sf=sflag[sno]; 
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
  if (logflag)
  {
    adt[0].get_elapsed_time_and_reset();
  }
  // cout  << "adjoint_write_unlock_buffer_master(void)" << endl;
  verify_identifier_string("XD");
  int sno=restore_int_value();
  verify_identifier_string("TD");
  //read_lock_buffer_master(sno);
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  // cout  << endl << "XX sflag[sno] = " << sflag[sno] << endl;
  int sf=sflag[sno];
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
  if (logflag)
  {
    double tm=adt[0].get_elapsed_time_and_reset();
    *(logfiles[0]) << tm << " write_unlock_buffer_master" << endl;
  }
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
  if (logflag)
  {
    adt[sno].get_elapsed_time_and_reset();
  }
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
  current_bptr[sno]=transfer_buffer[sno];
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
  if (logflag)
  {
    double tm=adt[sno].get_elapsed_time_and_reset();
    *(logfiles[sno]) << tm  <<  " write_unlock_buffer_slave" << endl;
  }

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
  verify_identifier_string("FN");
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
  if (logflag)
  {
    double tm=adt[sno].get_elapsed_time_and_reset();
    *(logfiles[sno]) << tm << " adjoint_write_lock_buffer_slave"   << endl;
  }
}
void adpthread_manager::write_lock_buffer_slave(int sno)
{
  if (logflag)
  {
    adt[sno].get_elapsed_time_and_reset();
    *(logfiles[sno]) << "starting write_lock_buffer_slave " << sno  << endl;
  }
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  save_identifier_string("FN");
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
  if (logflag)
  {
    double tm=adt[sno].get_elapsed_time_and_reset();
    *(logfiles[sno]) << tm   << " adjoint_read_lock_buffer_slave" << endl;
  }
}

void adpthread_manager::read_lock_buffer_slave(int sno)
{
  // we should be using the mutexes from the class
  // to get rid of global variables
  if (logflag)
  {
    *(logfiles[sno]) << "starting read_lock_buffer_slave "  << sno  << endl;
    adt[sno].get_elapsed_time_and_reset();
  }
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
  if (logflag)
  {
    adt[0].get_elapsed_time_and_reset();
    *(logfiles[0]) << "starting adjoint_master_write_lock " << sno   << endl;
  }
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
  if (logflag)
  {
    *(logfiles[0]) << "starting adjoint_read_unlock_buffer_master " << sno 
                   << endl;
    adt[0].get_elapsed_time_and_reset();
  }
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
  if (logflag)
  {
    double tm=adt[0].get_elapsed_time_and_reset();
    *(logfiles[0]) << tm << " read_unlock_buffer_master"  << endl;
  }
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
  if (logflag)
  {
    *(logfiles[sno]) << "starting adjoint_read_unlock_buffer_slave " << sno  
                     << endl;
    adt[sno].get_elapsed_time_and_reset();
  }
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  int mf=mflag[sno];
  int sf=sflag[sno];
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
  if (logflag)
  {
    double tm=adt[sno].get_elapsed_time_and_reset();
    *(logfiles[sno]) << tm << " read_unlock_buffer_slave" << endl;
  }
}


void adpthread_manager::create_all(pthreadfun pf ,new_thread_data * ptr)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_create(thread1+i,NULL,pf,ptr+i);
  }
}

void adpthread_manager::create_all(pthreadfun pf ,thread_data * ptr)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_create(thread1+i,NULL,pf,ptr+i);
  }
}

void adpthread_manager::create_all(void * ptr)
{
  new_thread_data * dptr = (new_thread_data *)ptr; 
  int ii=0;
  for (int i=1;i<=ngroups;i++)
  {
    if (i>ngroups)
    {
      cerr << " index too high in "
        "adpthread_manager::create_all(void * dptr)" << endl;
      ad_exit(1);
    }
    for (int j=1;j<=num_in_group(i);j++)
    {
      cout << ppf[i] << endl;
      ++ii;
      pthread_create(thread1+ii,NULL,ppf[i],dptr+ii);
    }
  }
}

void adpthread_manager::pthread_join_all(void)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_join(thread1[i], NULL);
  }
}

void adpthread_manager::writebuffer(const void *x,int nbytes,int sno)
{
 /*
  if (old_buffer_flag==1)
  {
    check_buffer_size(nbytes,sno);
    ::memcpy(current_bptr[sno],x,nbytes);
    current_bptr[sno]+=nbytes;
  }
  else
 */
  {
    int s1,s2;
    int tn2=ad_comm::pthread_manager->get_slave_number();
    if (tn2==sno)
    {
      cerr << "This can't happen" << endl;
      ad_exit(1);
    }
    if (tn2<sno)
    {
      s1=tn2;
      s2=sno;
    }
    else
    {
      s1=sno;
      s2=tn2;
    }
    check_buffer_size(nbytes,s1,s2);
    ::memcpy(scurrent_bptr[s1][s2],x,nbytes);
    scurrent_bptr[s1][s2]+=nbytes;
  }
}

void adpthread_manager::readbuffer(const void *_x,int nbytes,int sno)
{
  void * x= (void *)(_x); 
 /*
  if (old_buffer_flag==1)
  {
    check_buffer_size_read(nbytes,sno);
    ::memcpy(x,current_bptr[sno],nbytes);
    current_bptr[sno]+=nbytes;
  }
  else
 */
  {
    int s1,s2;
    int tn2=ad_comm::pthread_manager->get_slave_number();
    if (tn2==sno)
    {
      cerr << "This can't happen" << endl;
      ad_exit(1);
    }
    if (tn2<sno)
    {
      s1=tn2;
      s2=sno;
    }
    else
    {
      s1=sno;
      s2=tn2;
    }
    check_buffer_size_read(nbytes,s1,s2);
    ::memcpy(x,scurrent_bptr[s1][s2],nbytes);
    scurrent_bptr[s1][s2]+=nbytes;
  }
}


void adpthread_manager::verify_id_string_from_master(const char * s,int sno)
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

void adpthread_manager::verify_id_string_from_slave(const char * s,int sno)
{
#if defined(CHK_ID_STRING)
  char s1[10];
  int sz=strlen(s);
  s1[sz]='\0';
  readbuffer(s1,sz,sno);
  if (strcmp(s,s1))
  {
    cerr << "Error verifying slave string " << s <<  "  got " 
         << s1  << " instead" << endl;
    ad_exit(1);
  }
#endif
}

void adpthread_manager::send_double(const double &x,int sno)
{
  send_id_string_to_slave("TY",sno);
  writebuffer(&x,sizeof(double),sno);
}

void adpthread_manager::send_double_to_slave(const double &x,int sno)
{
  send_id_string_to_slave("TY",sno);
  writebuffer(&x,sizeof(double),sno);
}
void adpthread_manager::send_int_to_slave(int x,int sno)
{
  send_id_string_to_slave("RY",sno);
  writebuffer(&x,sizeof(int),sno);
}

void adpthread_manager::send_int(int x,int sno)
{
  send_id_string_to_slave("RY",sno);
  writebuffer(&x,sizeof(int),sno);
}

void adpthread_manager::send_int_to_master(int x,int sno)
{
  send_id_string_to_slave("YY",sno);
  writebuffer(&x,sizeof(int),sno);
}

int adpthread_manager::get_int_from_master(int sno)
{
  verify_id_string_from_master("RY",sno);
  int x;
  readbuffer(&x,sizeof(int),sno);
  return x;
}

int adpthread_manager::get_int(int sno)
{
  verify_id_string_from_master("RY",sno);
  int x;
  readbuffer(&x,sizeof(int),sno);
  return x;
}

int adpthread_manager::get_int_from_slave(int sno)
{
  verify_id_string_from_master("YY",sno);
  int x;
  readbuffer(&x,sizeof(int),sno);
  return x;
}

double adpthread_manager::get_double_from_master(int sno)
{
  verify_id_string_from_master("TY",sno);
  double x;
  readbuffer(&x,sizeof(double),sno);
  return x;
}
double adpthread_manager::get_double(int sno)
{
  verify_id_string_from_master("TY",sno);
  double x;
  readbuffer(&x,sizeof(double),sno);
  return x;
}

void adpthread_manager::send_double_to_master(const double &x,int sno)
{
  send_id_string_to_master("EY",sno);
  writebuffer(&x,sizeof(double),sno);
}

double adpthread_manager::get_double_from_slave(int sno)
{
  verify_id_string_from_master("EY",sno);
  double x;
  readbuffer(&x,sizeof(double),sno);
  return x;
}

void adpthread_manager::send_id_string_to_slave(const char * x,int sno)
{
#if defined(CHK_ID_STRING)
  int sz=strlen(x);
  writebuffer(x,sz,sno);
#endif
}

void adpthread_manager::send_id_string_to_master(const char * x,int sno)
{
#if defined(CHK_ID_STRING)
  int sz=strlen(x);
  writebuffer(x,sz,sno);
#endif
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
  send_id_string_to_master("SUX",sno);
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
  verify_id_string_from_master("DCY",sno);
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
dvar_vector adpthread_manager::get_dvar_vector(int sno)
{
  int mmin;
  int mmax;
  verify_id_string_from_master("DCY",sno);
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

/*
dvariable adpthread_manager::get_dvariable_from_master(int sno)
{
  return ::get_dvariable_from_master(current_bptr[sno],sno);
}
*/

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
  send_id_string_to_slave("RUX",sno);
  writebuffer(&dv,sizeof(double),sno);
}

dvariable adpthread_manager::get_dvariable_from_slave(int sno)
{
  dvariable x;
  double cx;
  verify_id_string_from_slave("VP",sno);
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
dvariable adpthread_manager::get_dvariable(int sno)
{
  dvariable x;
  double cx;
  verify_id_string_from_slave("VP",sno);
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
  verify_id_string_from_master("RUX",sno);
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
  send_id_string_to_master("VP",sno);
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
void adpthread_manager::send_dvariable(const prevariable& _x,int sno)
{
  ADUNCONST(prevariable,x)
  save_identifier_string("S5");
  x.save_prevariable_position();
  send_id_string_to_master("VP",sno);
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

// ***********************************************
// ***********************************************
// ***********************************************
void adjoint_send_dvariable_to_slave(void)
{
  verify_identifier_string("RP");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_send_dvariable_to_slave();
}

void adpthread_manager::adjoint_send_dvariable_to_slave(void)
{
  verify_identifier_string("GH");
  int sno=restore_int_value();
  verify_identifier_string("UP");
  verify_id_string_from_slave("SUA",sno);
  double x;
  readbuffer(&x,sizeof(double),sno);
  prevariable_position dxpos=restore_prevariable_position();
  verify_identifier_string("B");
  save_double_derivative(x,dxpos);
}

void adpthread_manager::send_dvariable_to_slave(const prevariable &x,int sno)
{
  writebuffer(&(value(x)),sizeof(double),sno);
  save_identifier_string("B");
  x.save_prevariable_position();
  save_identifier_string("UP");
  save_int_value(sno);
  save_identifier_string("GH");
  save_pointer_value(this);
  save_identifier_string("RP");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvariable_to_slave);
}

// ***********************************************
// ***********************************************

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
  verify_id_string_from_slave("SUX",sno);
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
  send_id_string_to_slave("DCY",sno);
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
void adpthread_manager::send_dvar_vector(const dvar_vector &x,int sno)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  send_id_string_to_slave("DCY",sno);
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
  send_id_string_to_slave("CCX",sno);
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  writebuffer(&(x(mmin)),sz*sizeof(double),sno);
  //::send_dvector_to_slave(x,current_bptr[sno],sno);
}

void adpthread_manager::send_dvector(const dvector &x,int sno)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  send_id_string_to_slave("CCX",sno);
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  writebuffer(&(x(mmin)),sz*sizeof(double),sno);
  //::send_dvector_to_slave(x,current_bptr[sno],sno);
}

void adpthread_manager::send_dvector_to_master(const dvector &x,int sno)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  send_id_string_to_master("TYU",sno);
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  writebuffer(&(x(mmin)),sz*sizeof(double),sno);
}
dvector adpthread_manager::get_dvector_from_slave(int sno)
{
  int mmin;
  int mmax;
  verify_id_string_from_slave("TYU",sno);
  readbuffer(&mmin,sizeof(int),sno);
  readbuffer(&mmax,sizeof(int),sno);
  dvector x(mmin,mmax);
  int sz=mmax-mmin+1;
  readbuffer(&(x(mmin)),sz*sizeof(double),sno);
  return x;
}

dvector adpthread_manager::get_dvector_from_master(int sno)
{
  int mmin;
  int mmax;
  verify_id_string_from_master("CCX",sno);
  readbuffer(&mmin,sizeof(int),sno);
  readbuffer(&mmax,sizeof(int),sno);
  dvector x(mmin,mmax);
  int sz=mmax-mmin+1;
  readbuffer(&(x(mmin)),sz*sizeof(double),sno);
  return x;
}
dvector adpthread_manager::get_dvector(int sno)
{
  int mmin;
  int mmax;
  verify_id_string_from_master("CCX",sno);
  readbuffer(&mmin,sizeof(int),sno);
  readbuffer(&mmax,sizeof(int),sno);
  dvector x(mmin,mmax);
  int sz=mmax-mmin+1;
  readbuffer(&(x(mmin)),sz*sizeof(double),sno);
  return x;
}
adpthread_manager * test_thread_manager=0;

void adjoint_send_dvar_matrix_to_slave(void)
{
  verify_identifier_string("UN");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_send_dvar_matrix_to_slave();
}

void adpthread_manager::adjoint_send_dvar_matrix_to_slave(void)
{
  verify_identifier_string("HH");
  int sno=restore_int_value();
  verify_identifier_string("OP");
  verify_id_string_from_slave("WVX",sno);
  int rmin;
  int rmax;
  readbuffer(&rmin,sizeof(int),sno);
  readbuffer(&rmax,sizeof(int),sno);
  dmatrix M(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin,mmax;
    readbuffer(&mmin,sizeof(int),sno);
    readbuffer(&mmax,sizeof(int),sno);
    M(i).allocate(mmin,mmax);
    int sz=mmax-mmin+1;
    readbuffer(&(M(i)(mmin)),sz*sizeof(double),sno);
  }
  dvar_matrix_position dmpos=restore_dvar_matrix_position();
  verify_identifier_string("Y");
  M.save_dmatrix_derivatives(dmpos);
}

void adpthread_manager::send_dvar_matrix_to_slave(const dvar_matrix &x,int sno)
{
  int rmin=x.indexmin();
  int rmax=x.indexmax();
  send_id_string_to_slave("WTZ",sno);
  writebuffer(&rmin,sizeof(int),sno);
  writebuffer(&rmax,sizeof(int),sno);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin=x(i).indexmin();
    int mmax=x(i).indexmax();
    int sz=mmax-mmin+1;
    writebuffer(&mmin,sizeof(int),sno);
    writebuffer(&mmax,sizeof(int),sno);
    writebuffer(&(value(x(i)(mmin))),sz*sizeof(double),sno);
  }
  save_identifier_string("Y");
  // !!! should we optimize this ?
  x.save_dvar_matrix_position();
  save_identifier_string("OP");
  save_int_value(sno);
  save_identifier_string("HH");
  save_pointer_value(this);
  save_identifier_string("UN");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvar_matrix_to_slave);
}

void adpthread_manager::send_dvar_matrix(const dvar_matrix &x,int sno)
{
  int rmin=x.indexmin();
  int rmax=x.indexmax();
  send_id_string_to_slave("RAZ",sno);
  writebuffer(&rmin,sizeof(int),sno);
  writebuffer(&rmax,sizeof(int),sno);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin=x(i).indexmin();
    int mmax=x(i).indexmax();
    int sz=mmax-mmin+1;
    writebuffer(&mmin,sizeof(int),sno);
    writebuffer(&mmax,sizeof(int),sno);
    writebuffer(&(value(x(i)(mmin))),sz*sizeof(double),sno);
  }
  save_identifier_string("Y");
  // !!! should we optimize this ?
  x.save_dvar_matrix_position();
  save_identifier_string("OP");
  save_int_value(sno);
  save_identifier_string("HH");
  save_pointer_value(this);
  save_identifier_string("UN");
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(::adjoint_send_dvar_matrix_to_slave);
}
void adpthread_manager::send_dmatrix(const dmatrix &x,int sno)
{
  int rmin=x.indexmin();
  int rmax=x.indexmax();
  send_id_string_to_slave("SAY",sno);
  writebuffer(&rmin,sizeof(int),sno);
  writebuffer(&rmax,sizeof(int),sno);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin=x(i).indexmin();
    int mmax=x(i).indexmax();
    int sz=mmax-mmin+1;
    writebuffer(&mmin,sizeof(int),sno);
    writebuffer(&mmax,sizeof(int),sno);
    writebuffer(&(x(i)(mmin)),sz*sizeof(double),sno);
  }
}
void adjoint_get_dvar_matrix_from_master(void)
{
  verify_identifier_string("T4");
  adpthread_manager * ptr=(adpthread_manager*)(restore_pointer_value());
  ptr->adjoint_get_dvar_matrix_from_master();
}

void adpthread_manager::adjoint_get_dvar_matrix_from_master(void)
{
  verify_identifier_string("K6");
  int sno=restore_int_value();
  verify_identifier_string("Y7");
  dvar_matrix_position dvpos=restore_dvar_matrix_position();
  verify_identifier_string("C2");
  dmatrix dv=restore_dvar_matrix_derivatives(dvpos);
  send_id_string_to_master("WVX",sno);
  int rmin=dv.indexmin();
  int rmax=dv.indexmax();
  writebuffer(&rmin,sizeof(int),sno);
  writebuffer(&rmax,sizeof(int),sno);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin=dv(i).indexmin();
    int mmax=dv(i).indexmax();
    int sz=mmax-mmin+1;
    writebuffer(&mmin,sizeof(int),sno);
    writebuffer(&mmax,sizeof(int),sno);
    writebuffer(&(dv(i)(mmin)),sz*sizeof(double),sno);
  }
}
dvar_matrix adpthread_manager::get_dvar_matrix_from_master(int sno)
{
  verify_id_string_from_master("WTZ",sno);
  int rmin;
  int rmax;
  readbuffer(&rmin,sizeof(int),sno);
  readbuffer(&rmax,sizeof(int),sno);
  // cout  << "In dvar_vector get_dvar_vector_from_master " << endl;
  // cout  << " mmin = " << mmin   << " mmax = " << mmax  << endl;
  dvar_matrix x(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin;
    int mmax;
    readbuffer(&mmin,sizeof(int),sno);
    readbuffer(&mmax,sizeof(int),sno);
    int sz=mmax-mmin+1;
    x(i).allocate(mmin,mmax);
    readbuffer(&(value(x(i)(mmin))),sz*sizeof(double),sno);
  }
  save_identifier_string("C2");
  x.save_dvar_matrix_position();
  save_identifier_string("Y7");
  save_int_value(sno);
  save_identifier_string("K6");
  save_pointer_value(this);
  save_identifier_string("T4");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvar_matrix_from_master);
  return x;
}
dvar_matrix adpthread_manager::get_dvar_matrix(int sno)
{
  verify_id_string_from_master("RAZ",sno);
  int rmin;
  int rmax;
  readbuffer(&rmin,sizeof(int),sno);
  readbuffer(&rmax,sizeof(int),sno);
  // cout  << "In dvar_vector get_dvar_vector_from_master " << endl;
  // cout  << " mmin = " << mmin   << " mmax = " << mmax  << endl;
  dvar_matrix x(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin;
    int mmax;
    readbuffer(&mmin,sizeof(int),sno);
    readbuffer(&mmax,sizeof(int),sno);
    int sz=mmax-mmin+1;
    x(i).allocate(mmin,mmax);
    readbuffer(&(value(x(i)(mmin))),sz*sizeof(double),sno);
  }
  save_identifier_string("C2");
  x.save_dvar_matrix_position();
  save_identifier_string("Y7");
  save_int_value(sno);
  save_identifier_string("K6");
  save_pointer_value(this);
  save_identifier_string("T4");
  gradient_structure::GRAD_STACK1->
            set_gradient_stack(::adjoint_get_dvar_matrix_from_master);
  return x;
}

dmatrix adpthread_manager::get_dmatrix(int sno)
{
  verify_id_string_from_master("SAY",sno);
  int rmin;
  int rmax;
  readbuffer(&rmin,sizeof(int),sno);
  readbuffer(&rmax,sizeof(int),sno);
  dmatrix x(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin;
    int mmax;
    readbuffer(&mmin,sizeof(int),sno);
    readbuffer(&mmax,sizeof(int),sno);
    int sz=mmax-mmin+1;
    x(i).allocate(mmin,mmax);
    readbuffer(&(x(i)(mmin)),sz*sizeof(double),sno);
  }
  return x;
}

void add_slave_suffix(const adstring& _tmpstring)
{
  ADUNCONST(adstring,tmpstring)
  if (ad_comm::pthread_manager)
  {
    pthread_mutex_lock(&ad_comm::pthread_manager->copy_mutex);
    if (ad_comm::pthread_manager->is_slave())
    {
      tmpstring += "_slave_";
      tmpstring += str(ad_comm::pthread_manager->get_slave_number());
       //cout << "In slave " << tmpstring << endl;
    }
    else
    {
      tmpstring += "_master";
       //cout << "In master " << tmpstring << endl;
    }
    pthread_mutex_unlock(&ad_comm::pthread_manager->copy_mutex);
  }
}
new_thread_data::new_thread_data(void)
{
 // id=0;
  thread_no=0;
  pfsh=0;
  m=0;
}

imatrix adpthread_manager::get_imatrix(int sno)
{
  verify_id_string_from_master("FKY",sno);
  int rmin;
  int rmax;
  readbuffer(&rmin,sizeof(int),sno);
  readbuffer(&rmax,sizeof(int),sno);
  imatrix x(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin;
    int mmax;
    readbuffer(&mmin,sizeof(int),sno);
    readbuffer(&mmax,sizeof(int),sno);
    int sz=mmax-mmin+1;
    x(i).allocate(mmin,mmax);
    readbuffer(&(x(i)(mmin)),sz*sizeof(int),sno);
  }
  return x;
}

void adpthread_manager::send_imatrix(const imatrix &x,int sno)
{
  int rmin=x.indexmin();
  int rmax=x.indexmax();
  send_id_string_to_slave("FKY",sno);
  writebuffer(&rmin,sizeof(int),sno);
  writebuffer(&rmax,sizeof(int),sno);
  for (int i=rmin;i<=rmax;i++)
  {
    int mmin=x(i).indexmin();
    int mmax=x(i).indexmax();
    int sz=mmax-mmin+1;
    writebuffer(&mmin,sizeof(int),sno);
    writebuffer(&mmax,sizeof(int),sno);
    writebuffer(&(x(i)(mmin)),sz*sizeof(int),sno);
  }
}
ivector adpthread_manager::get_ivector(int sno)
{
  int mmin;
  int mmax;
  verify_id_string_from_master("EAC",sno);
  readbuffer(&mmin,sizeof(int),sno);
  readbuffer(&mmax,sizeof(int),sno);
  ivector x(mmin,mmax);
  int sz=mmax-mmin+1;
  readbuffer(&(x(mmin)),sz*sizeof(int),sno);
  return x;
}
void adpthread_manager::send_ivector(const ivector &x,int sno)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int sz=mmax-mmin+1;
  send_id_string_to_slave("EAC",sno);
  writebuffer(&mmin,sizeof(int),sno);
  writebuffer(&mmax,sizeof(int),sno);
  writebuffer(&(x(mmin)),sz*sizeof(int),sno);
}
