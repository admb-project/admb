#include <admodel.h>
#include <admodel.h>
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

/* prototype for thread routine */
void admb_thread(void * ptr);

/* struct to hold data to be passed to a thread
   this shows how multiple data items can be passed to a thread */
union a_union {
    char * p;
    double d;
};

a_union au;


class thread_data
{
public:
  static int __thread id;
  int thread_no;
  int bufsize;
  pthread_mutex_t *inlock;
  pthread_mutex_t *outlock;
  void * transfer_buffer;
  char message[100];
};
pthread_mutex_t mutex_print;

const int NSLAVES=24;

int mflag[NSLAVES+1];
int sflag[NSLAVES+1];
pthread_mutex_t smutex[NSLAVES+1];
pthread_cond_t scondition[NSLAVES+1];
pthread_cond_t mcondition[NSLAVES+1];

typedef char * pchar;

void send_double_to_slave(double &x,void * transfer_buffer,int sno)
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

double get_double_from_master(void * transfer_buffer, int sno);
double get_double_from_slave(void * transfer_buffer, int sno);

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

void send_dvariable_to_slave(const prevariable  &_x,void * transfer_buffer,
  int sno)
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

void adpthread_slave_unpack_number_derivative(void)
{
  verify_identifier_string("F1");
  void * ptr=restore_pointer_value();
  int sno=restore_int_value();
  verify_identifier_string("C");
  cout << " getting  dv  from master" << endl;
  double dv=get_double_from_master(ptr,sno);
  cout << "got "  << dv << " from master" << endl;
  prevariable_position dvpos=restore_prevariable_position();
  verify_identifier_string("S5");
  save_double_derivative(dv,dvpos);
}

void send_double_to_master(double &x,void * transfer_buffer,int sno);

void send_dvariable_to_master(const prevariable  &_x,
  void * transfer_buffer,int sno)
{
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
void pthread_master_unpack_vector_derivatives(void);

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
dvector get_dvector_from_slave(void * transfer_buffer, int sno);

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

dvector get_dvector_from_master(void * transfer_buffer, int sno);

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



void send_double_to_master(double &x,void * transfer_buffer,int sno)
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
void pthread_slave_unpack_vector_derivatives(void);

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

double get_double_from_master(void * transfer_buffer, int sno)
{
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (mflag[sno] == 0) pthread_cond_wait(scondition+sno,smutex+sno);
  mflag[sno] = 0;
  double x;
  memcpy(&x,transfer_buffer,sizeof(double));
  pthread_mutex_unlock(smutex+sno) ;
  pthread_cond_signal(mcondition+sno);
  return x;
}
void adpthreads_slave_pack_number_derivative(void);

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
double get_double_from_slave(void * transfer_buffer, int sno);

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


dvariable get_dvariable_from_slave(void * transfer_buffer, int sno)
{
  dvariable x;
  value(x)=get_double_from_slave(transfer_buffer,sno);
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

void adpthreads_slave_pack_number_derivative(void)
{
  verify_identifier_string("G1");
  int sno=restore_int_value();
  void * ptr=restore_pointer_value();
  verify_identifier_string("D");
  prevariable_position dvpos=restore_prevariable_position();
  double dv=restore_prevariable_derivative(dvpos);
  cout << "sending " << dv << " to master " << endl;
  send_double_to_master(dv,ptr,sno);
  //pvm_pack(dv);
  verify_identifier_string("C");
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

double get_double_from_slave(void * transfer_buffer, int sno)
{
  pthread_mutex_lock(smutex+sno);
  // only read if buffer full and data is for you
  while (sflag[sno] == 0) pthread_cond_wait(mcondition+sno,smutex+sno);
  sflag[sno] = 0;
  double x;
  memcpy(&x,transfer_buffer,sizeof(double));
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


class adpthread_manager
{
public:
  char ** transfer_buffer;
  char ** buffend;
  int nslaves;
  int bs;
  int * mflag;
  int * sflag;
  pthread_mutex_t * smutex;
  pthread_cond_t * scondition;
  pthread_cond_t *mcondition;
  pthread_t * thread1;  /* thread variables */
  adpthread_manager(int ns,int bs)
  {
    int i;
    nslaves=ns;
    transfer_buffer=new pchar[ns];
    buffend=new pchar[ns];
    transfer_buffer--;
    buffend--;
    for (i=1;i<=ns;i++)
    {
      transfer_buffer[i]=new char[bs];
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
  void send_double_to_slave(double &x,int sno);
  void send_double_to_master(double &x,int sno);
  double get_double_from_slave(int sno);
  double get_double_from_master(int sno);
  void send_dvariable_to_slave(const prevariable &x,int sno);
  void send_dvariable_to_master(const prevariable &x,int sno);
  dvariable get_dvariable_from_slave(int sno);
  dvariable get_dvariable_from_master(int sno);
  void send_dvector_to_slave(const dvector &x,int sno);
  void send_dvector_to_master(const dvector &x,int sno);
  dvector get_dvector_from_slave(int sno);
  dvector get_dvector_from_master(int sno);
  dvar_vector get_dvar_vector_from_slave(int sno);
  dvar_vector get_dvar_vector_from_master(int sno);
  void send_dvar_vector_to_slave(const dvar_vector &x,int sno);
  void send_dvar_vector_to_master(const dvar_vector &x,int sno);
  void pthread_join_all(void);
  void create_all(void*f,thread_data * ptr);
};
void adpthread_manager::create_all(void *f ,thread_data * ptr)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_create(thread1+i,NULL,f,ptr+i);
  }
}
dvar_vector get_dvar_vector_from_master(void * transfer_buffer, int sno);

void adpthread_manager::pthread_join_all(void)
{
  for (int i=1;i<=nslaves;i++)
  {
    pthread_join(thread1[i], NULL);
  }
}
void adpthread_manager::send_double_to_slave(double &x,int sno)
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

void adpthread_manager::send_double_to_master(double &x,int sno)
{
  ::send_double_to_master(x,transfer_buffer[sno],sno);
}

void adpthread_manager::send_dvar_vector_to_slave(const dvar_vector &x,int sno)
{
  ::send_dvar_vector_to_slave(x,transfer_buffer[sno],sno);
}

void adpthread_manager::send_dvector_to_slave(const dvector &x,int sno)
{
  ::send_dvector_to_slave(x,transfer_buffer[sno],sno);
}

void adpthread_manager::send_dvector_to_master(const dvector &x,int sno)
{
  ::send_dvector_to_master(x,transfer_buffer[sno],sno);
}


double adpthread_manager::get_double_from_slave(int sno)
{
  return ::get_double_from_slave(transfer_buffer[sno],sno);
}

double adpthread_manager::get_double_from_master(int sno)
{
  return ::get_double_from_master(transfer_buffer[sno],sno);
}

dvector adpthread_manager::get_dvector_from_slave(int sno)
{
  return ::get_dvector_from_slave(transfer_buffer[sno],sno);
}

dvector adpthread_manager::get_dvector_from_master(int sno)
{
  return ::get_dvector_from_master(transfer_buffer[sno],sno);
}
adpthread_manager * test_thread_manager=0;

void add_slave_suffix(const adstring& _tmpstring)
{
  ADUNCONST(adstring,tmpstring)
  if (test_thread_manager)
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

void adpthreads_slave_pack_vector_derivative(void)
{
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
  pthread_mutex_lock(smutex+sno);
  // only write if buffer empty
  while (mflag[sno] == 1 || sflag[sno] ==1 ) 
    pthread_cond_wait(scondition+sno,smutex+sno);
  memcpy(b,&mmin,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&mmax,sizeof(int));
  b+=sizeof(int);
  memcpy(b,&(dv(mmin)),sz*sizeof(double));
  sflag[sno] = 1;
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
  while (mflag[sno] == 0) pthread_cond_wait(scondition+sno,smutex+sno);
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

int __thread thread_data::id=-1;
char ** buffer=0;

extern "C"  {
  void ad_boundf(int i)
  {
    // so we can stop here
    exit(i);
  }
}

const int m=150;
const int m2=m*m;

int main4()
{
  ad_exit=&ad_boundf;
  //test_thread_manager=new adpthread_manager(NSLAVES,200000);
  int i;

  thread_data data1[NSLAVES+1];         /* structs to be passed to threads */
  /* initialize data to pass to thread 1 */
  for (i=1;i<=NSLAVES;i++)
  {
    data1[i].thread_no=i;
  }

  //test_thread_manager->create_all(&admb_thread,data1);
  const int n=NSLAVES;
  {
    gradient_structure::set_MAX_NVAR_OFFSET(30000);
    //gradient_structure::set_ARRAY_MEMBLOCK_SIZE(20000);
    gradient_structure::set_GRADSTACK_BUFFER_SIZE(40000000);
    gradient_structure::set_CMPDIF_BUFFER_SIZE(550000000);
    gradient_structure gs(3000000);
    independent_variables x(1,m2);
    random_number_generator rng(101);
    x.fill_randn(rng);
    adtimer adt;
    dvar_vector vx=dvar_vector(x);
    
    dvar_matrix M(1,m,1,m);
    int ii=0;
    for (int i=1;i<=m;i++)
    {
      for (int j=1;j<=m;j++)
      {
        M(i,j)=vx(++ii);
      }
    }
    dvar_vector yy(1,n);
    for (int kk=1;kk<=n;kk++)
    {
      int sno=kk;
      dvector u(1,m);
      yy(kk)=0.0;
      u.fill_seqadd(sno,1.0/sno);
      for (int i=1;i<=50;i++)
      {
        yy(kk)+=norm2(solve(M,u+double(i)));
      }
    }
   
    dvariable f=sum(yy);
  
    ofstream ofs1("yyy");
  
    dvector g(1,m2);
    ofs1<<" f = " << f<<endl;
    gradcalc(m2,g);
  

    ofs1<<g<<endl;
    cout << adt.get_elapsed_time_and_reset()<<endl; 
  
  }
  exit(0);
} /* main() */

void admb_thread(void * ptr)
{
  thread_data * tptr = (thread_data *) ptr;
  thread_data::id=tptr->thread_no;
  int sno=tptr->thread_no;
  {
    gradient_structure::set_MAX_NVAR_OFFSET(10000);
    gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000);
    gradient_structure::set_CMPDIF_BUFFER_SIZE(900000000);
    gradient_structure gs(1000000);
    dvar_vector v= test_thread_manager->get_dvar_vector_from_master(sno);
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    dvar_matrix M(1,m,1,m);
    int ii=0;
    for (int i=1;i<=m;i++)
    {
      for (int j=1;j<=m;j++)
      {
        M(i,j)=v(++ii);
      }
    }
    dvector u(1,m);
    u.fill_seqadd(sno,1.0/sno);
    dvariable z=norm2(solve(M,u));
  
    test_thread_manager->send_dvariable_to_master(z,sno);
    slave_gradcalc();
  }
}

