/*
 * $Id: model7.cpp 945 2011-01-12 23:03:57Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#else
#  include <admodel.h>
#endif
//#include <parallel.h>
#include <signal.h>

#undef ADMB_CONFIGURE
#ifdef ADMB_CONFIGURE
  //#include "../../admb_configure.h"
#endif

void vm_initialize(void);
int have_jvm=0;


#if defined(USE_ADMPI)
const int admpi_manager::MAX_MPI_OFFSET=1000;
dvector admpi_manager::get_dvector_from_master(void)
{
  MPI_Status status;
  int mmin,mmax;
  MPI_Recv(&mmin,1, MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,parent,&status);
  MPI_Recv(&mmax,1, MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,parent,&status);
  dvector tmp(mmin,mmax);
  int size=mmax-mmin+1;
  MPI_Recv(&(tmp(mmin)),size, MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,parent,&status);
  return tmp;
}

dvector admpi_manager::get_dvector_from_slave(int _slave_number)
{
  int slave_number=_slave_number-1;
  MPI_Status status;
  int mmin,mmax;
  MPI_Recv(&mmin,1, MPI_INT,slave_number,0,everyone,&status);
  MPI_Recv(&mmax,1, MPI_INT,slave_number,0,everyone,&status);
  dvector tmp(mmin,mmax);
  int size=mmax-mmin+1;
  MPI_Recv(&(tmp(mmin)),size, MPI_DOUBLE,slave_number,0,everyone,&status);
  return tmp;
}

void admpi_manager::send_dvector_to_master(const dvector& v)
{
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  int size=mmax-mmin+1;
  mpi_int[mpi_offset]=v.indexmin();
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,0,0,parent);
  increment_mpi_offset();
  mpi_int[mpi_offset]=v.indexmax();
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,0,0,parent);
  increment_mpi_offset();
  MPI_Send(&(v[mmin]),size,MPI_DOUBLE,0,0,parent);
}

double admpi_manager::get_double_from_slave(int _slave_number)
{
  double tmp;
  int slave_number=_slave_number-1;
  MPI_Status status;
  MPI_Recv(&tmp,1, MPI_DOUBLE,slave_number,0,everyone,&status);
  return tmp;
}

void admpi_manager::send_double_to_master(const double v)
{
  MPI_Send(&v,1,MPI_DOUBLE,0,0,parent);
}

void admpi_manager::send_double_to_slave(const double v,
  int _slave_number)
{
  int slave_number=_slave_number-1;
  MPI_Send(&v,1,MPI_DOUBLE,slave_number,0,everyone);
}

double admpi_manager::get_double_from_master(void)
{
  MPI_Status status;
  double tmp;
  MPI_Recv(&tmp,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,parent,&status);
  return tmp;
}

ivector admpi_manager::get_ivector_from_master(void)
{
  MPI_Status status;
  int mmin,mmax;
  MPI_Recv(&mmin,1, MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,parent,&status);
  MPI_Recv(&mmax,1, MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,parent,&status);
  ivector tmp(mmin,mmax);
  int size=mmax-mmin+1;
  MPI_Recv(&(tmp(mmin)),size,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,parent,&status);
  //cout << "SCA" << tmp << endl;
  return tmp;
}

void admpi_manager::send_slave_hessian_assignments(int nvar)
{
  int m=nvar/(1+num_hess_slaves);
  int excess=nvar-m*(1+num_hess_slaves);
  if (allocated(all_hess_bounds)) all_hess_bounds.deallocate();
  all_hess_bounds.allocate(0,num_hess_slaves,1,2);
  all_hess_bounds(0,1)=1;
  all_hess_bounds(0,2)=m;
  if (allocated(hess_bounds)) hess_bounds.deallocate();
  hess_bounds.allocate(1,2);
  hess_bounds=all_hess_bounds(0);
  for (int i=1;i<=num_hess_slaves;i++)
  {
    all_hess_bounds(i,1)=all_hess_bounds(i-1,2)+1;
    all_hess_bounds(i,2)=all_hess_bounds(i,1)+m-1;
    if (excess>0) 
    {
      all_hess_bounds(i,2)+=1;
      excess--;
    }
    //cout << "In send slave hess ass from master" << endl;
    //cout << "sending " << hess_bounds << endl;
    send_ivector_to_slave(all_hess_bounds(i),i);
    //cout << "sent" << endl;
  }
}

void admpi_manager::get_slave_hessian_assignments(void)
{
  //cout << "In get slave hess bounds from master" << endl;
  hess_bounds=get_ivector_from_master();
  //cout << "got hess_bounds = " << hess_bounds << endl;
}

void admpi_manager::get_int_from_slave(int &i,int _slave_number)
{
  int slave_number=_slave_number-1;
  MPI_Status status;
  MPI_Recv(&i,1,MPI_INT,slave_number,0,everyone,&status);
}
void admpi_manager::get_int_from_master(int &i)
{
  MPI_Status status;
  MPI_Comm parent2; 
  MPI_Comm_get_parent(&parent2);
  // note this is a blocking receive
  //cout << "SBA" << parent << endl;
  //cout << "parent = " << parent << endl;
  MPI_Recv(&i,1, MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,parent2,&status);
  //cout << "SBB" << parent << endl;
}

int admpi_manager::is_master(void)
{
  return (parent==MPI_COMM_NULL);
}

int admpi_manager::is_slave(void)
{
  return (parent!=MPI_COMM_NULL);
}
admpi_manager::~admpi_manager()
{
  delete [] global_request;
  global_request=0;
  delete [] mpi_int;
  mpi_int=0;
  MPI_Finalize();
}


 // void admpi_manager::send_dvector_to_slave(const dvector& v,
 //   int _slave_number)
 // {
 //   int slave_number=_slave_number-1;
 //   MPI_Status myStatus;
 //   /* make sure that the previous read using this memory area
 //      has completed 
 //   */
 //   if(global_request[mpi_offset])  /* checks to see if has been used at least */
 //                                   /* once */
 //   {
 //     MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   }
 //   mpi_int[mpi_offset]=v.indexmin();
 //   MPI_Isend(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,
 //     everyone,&(global_request[mpi_offset]));
 //   increment_mpi_offset();
 //   if(global_request[mpi_offset])  /* checks to see if has been used at least */
 //                                   /* once */
 //   {
 //     MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   }
 //   mpi_int[mpi_offset]=v.indexmax();
 // 
 //   MPI_Isend(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,
 //     everyone,&(global_request[mpi_offset]));
 //   increment_mpi_offset();
 //   int mmin=v.indexmin();
 //   int mmax=v.indexmax();
 //   int size=mmax-mmin+1;
 //   MPI_Request request;
 //   MPI_Isend(&(v[mmin]),size,MPI_DOUBLE,slave_number,0,everyone,&request);
 // }

void admpi_manager::send_dvector_to_slave(const dvector& v,
  int _slave_number)
{
  int slave_number=_slave_number-1;
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  int size=mmax-mmin+1;
  mpi_int[mpi_offset]=v.indexmin();
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,everyone);
  increment_mpi_offset();
  mpi_int[mpi_offset]=v.indexmax();
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,everyone);
  increment_mpi_offset();
  MPI_Send(&(v[mmin]),size,MPI_DOUBLE,slave_number,0,everyone);
}

void admpi_manager::send_ivector_to_slave(const ivector& v,
  int _slave_number)
{
  int slave_number=_slave_number-1;
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  int size=mmax-mmin+1;
  mpi_int[mpi_offset]=v.indexmin();
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,everyone);
  increment_mpi_offset();
  mpi_int[mpi_offset]=v.indexmax();
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,everyone);
  increment_mpi_offset();
  MPI_Send(&(v[mmin]),size,MPI_INT,slave_number,0,everyone);
}

 // void admpi_manager::send_ivector_to_slave(const ivector& v,int _slave_number)
 // {
 //   int slave_number=_slave_number-1;
 //   MPI_Status myStatus;
 //   /* make sure that the previous read using this memory area
 //      has completed 
 //   */
 //   if(global_request[mpi_offset])  /* checks to see if has been used at least */
 //                                   /* once */
 //   {
 //     MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   }
 //   mpi_int[mpi_offset]=v.indexmin();
 //   MPI_Isend(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,
 //     everyone,&(global_request[mpi_offset]));
 //   increment_mpi_offset();
 //   if(global_request[mpi_offset])  /* checks to see if has been used at least */
 //                                   /* once */
 //   {
 //     MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   }
 //   mpi_int[mpi_offset]=v.indexmax();
 // 
 //   MPI_Isend(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,
 //     everyone,&(global_request[mpi_offset]));
 //   increment_mpi_offset();
 //   int mmin=v.indexmin();
 //   int mmax=v.indexmax();
 //   int size=mmax-mmin+1;
 //   MPI_Request request;
 //   MPI_Isend(&(v[mmin]),size,MPI_INT,slave_number,0,everyone,&request);
 //   //cout << "MBA" << endl;
 //   //cout << "MCA" <<  v << endl;
 //   // wiat remove 1
 //   //MPI_Wait(&(request), &myStatus);
 //   //cout << "MBB" << endl;
 // }
 // 
 // void admpi_manager::send_int_to_slave(int i,int _slave_number)
 // {
 //   int slave_number=_slave_number-1;
 //   MPI_Status myStatus;
 //   MPI_Request request;
 //   /* make sure that the previous read using this memory area
 //      has completed 
 //   */
 //   if(global_request[mpi_offset])  /* checks to see if has been used at least */
 //                                   /* once */
 //   {
 //     MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   }
 //   mpi_int[mpi_offset]=i;
 //   MPI_Isend(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,
 //     everyone,&(global_request[mpi_offset]));
 //   //sleep(1);
 //   //MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   increment_mpi_offset();
 // }

void admpi_manager::send_int_to_slave(int i,int _slave_number)
{
  int slave_number=_slave_number-1;
  mpi_int[mpi_offset]=i;
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,slave_number,0,everyone);
  increment_mpi_offset();
}

void admpi_manager::increment_mpi_cobjfun(const double& f)
{
  mpi_cobjfun+=f;
}

void admpi_manager::set_separable_assignments(const int _num_separable_calls)
{
  int num_separable_calls = _num_separable_calls;
  if(is_master())
  {
    int local_num_slaves = num_slaves+1;
    int nd=num_separable_calls/local_num_slaves;
    int r= num_separable_calls - nd * local_num_slaves;
    ivector mpi_partition(1,local_num_slaves);
    mpi_partition=nd;
    mpi_partition(1,r)+=1;

    ivector minsep(1,local_num_slaves);
    ivector maxsep(1,local_num_slaves);
    minsep(1)=1;
    maxsep(1)=mpi_partition(1);
    for (int i=2;i<=local_num_slaves;i++)
    {
      minsep(i)=maxsep(i-1)+1;
      maxsep(i)=minsep(i)+mpi_partition(i)-1;
    }

    min_separable_index = minsep(1);
    max_separable_index = maxsep(1);
    for(int i=1;i<=num_slaves;i++)
    {
      send_int_to_slave(minsep(i+1),i);
      send_int_to_slave(maxsep(i+1),i);
    }
  }
  else
  {
    get_int_from_master(min_separable_index);
    get_int_from_master(max_separable_index);
  }
}

 // void admpi_manager::send_int_to_master(int i)
 // {
 //   MPI_Status myStatus;
 //   MPI_Request request;
 //   /* make sure that the previous read using this memory area
 //      has completed 
 //   */
 //   if(global_request[mpi_offset])  /* checks to see if has been used at least */
 //                                   /* once */
 //   {
 //     MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   }
 //   mpi_int[mpi_offset]=i;
 //   MPI_Isend(&(mpi_int[mpi_offset]),1,MPI_INT,0,0,
 //     parent,&(global_request[mpi_offset]));
 //   //sleep(1);
 //   // remove 2
 //   //MPI_Wait(&(global_request[mpi_offset]), &myStatus);
 //   increment_mpi_offset();
 // }

void admpi_manager::send_int_to_master(int i)
{
  mpi_int[mpi_offset]=i;
  MPI_Send(&(mpi_int[mpi_offset]),1,MPI_INT,0,0,parent);
  increment_mpi_offset();
}

void admpi_manager::increment_mpi_offset(void)
{
  mpi_offset++;
  if (mpi_offset==MAX_MPI_OFFSET)
  {
    mpi_offset=0;
  }
}

admpi_manager::admpi_manager(int m,int argc,char * argv[])
{
  parent=0;
  global_request = new MPI_Request[MAX_MPI_OFFSET];
  mpi_offset=0;
  num_slaves=0;
  num_hess_slaves=0;
  do_minimize=0;
  do_hess=0;
  sync_objfun_flag=0;
  mpi_int = new int[MAX_MPI_OFFSET];
 
  for (int i=0;i<MAX_MPI_OFFSET;i++)
  {
    global_request[i]=0;
    //mpi_int[i]=0;
  }
 
  int rank,world_size, universe_size, *universe_sizep, flag;
  if (strlen(argv[0])>150)
  {
    cerr << "program name too long for mpi manager" << endl;
    ad_exit(1);
  }
  else
  {
    strncpy(worker_program,argv[0],151);
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  cout << world_size << endl;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  cout << "master rank " << rank << endl;
  MPI_Comm_get_parent(&parent);

  //sleep(1);
  if (is_master())
  {
    cout << "I am the master process" << endl;
    do_minimize=1;
    do_hess=1;
    if (world_size != 1) 
    {
      cerr << "Error --can only have one MPI master process" << endl;
      ad_exit(1);
    }

    //sleep(1);

    // !!! need to pass this number in MPI options
    int on=0; int nopt=0;
    if ( (on=option_match(argc,argv,"-nslaves",nopt))>-1)
    {
      if (nopt ==1)	    
      {	      
        num_slaves=atoi(argv[on+1]);
        //num_hess_slaves=num_slaves;
      }
      else
      {
        cerr << "Wrong number of options to -nslaves -- must be 1"
          " you have " << nopt << endl;		
        ad_exit(1);
      }	
    }
    else
    {
      num_slaves=1;
      //num_hess_slaves=1;
    }
   
    if (num_slaves < 1) 
    {
      cerr << "Error --no room for slaves" << endl;
      ad_exit(1);
    }

    //sleep(1);

    /*
     * Now spawn the slaves. Note that there is a run-time determination
     * of what type of slaves to spawn, and presumably this calculation must

     * be done at run time and cannot be calculated before starting
     * the program. If everything is known when the application is
     * first started, it is generally better to start them all at once
     * in a single MPI_COMM_WORLD.
     */
  
     fprintf(stderr, "will spawn %d slaves\n", num_slaves);
     cout << "there are " << num_hess_slaves << " hess slaves" << endl;
     int * ia=(int*)malloc(sizeof(int));
     char **myargvs=0;  // = {"-slave", NULL};
     myargvs=new char*[argc+3];
     int ii=0;
     myargvs[ii]=new char[strlen(argv[0])+1];
     strcpy(myargvs[ii++],argv[0]);
     myargvs[ii]=new char[strlen("-slave")+1];
     strcpy(myargvs[ii++],"-slave");
     for (int i=1;i<argc;i++)
     {
       if (strcmp(argv[i],"-master"))
       {
         myargvs[ii]=new char[strlen(argv[i])+1];
         strcpy(myargvs[ii++],argv[i]);
       }
     }
     myargvs[ii]=0;
       

     
     ivector ierr(1,num_slaves);
     ierr=-5555;
     MPI_Comm_spawn(worker_program, myargvs, num_slaves,
            MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone,
            &(ierr(1)) );
     for (int i=1;i<=num_slaves;i++)
     {
        if (ierr(i) != MPI_SUCCESS)
        {
          cerr << "Error spawning slave process " << i << endl;
          ad_exit(1);
        }
     }
     cout << "Error codes for spawn  " << ierr << endl;
            //MPI_ERRCODES_IGNORE);
     //cout << "enter 2" << endl;
     //cin >> ia[0];
     ia[0]=2;
     // send an int to the slaves so that they will wait
     // until they get it
     /*  
     for (int i=1;i<=num_slaves;i++)
     {
       send_int_to_slave(ia[0]+i,i);
     }
     */
     //sleep(1);
  }
  if (is_slave())
  {
    //cout << "I am a slave process" << endl;
    slave_number=rank+1;
    //cout << "slave_number = " << slave_number << endl;
    if (initial_df1b2params::separable_flag)
      do_minimize=1;
    else
      do_minimize=0;
    do_hess=1;
    //int i=-1;
    //get_int_from_master(i);
    //cout << "In slave i = " << i << endl;
    //sleep(2);
    cout << "I have " << argc << " argurments which are " << endl;
    for (int i=0;i<argc;i++)
    {
      cout << argv[i] << endl;
    }
  }
}

#endif

separable_bounds::separable_bounds(int _min_bound, int _max_bound)
{
  min_bound=_min_bound;
  max_bound=_max_bound;
#if defined(USE_ADMPI)
  if (ad_comm::mpi_manager)
  {
    int num_separable_calls = max_bound-min_bound+1;
    if(ad_comm::mpi_manager->is_master())
    {
      int local_num_slaves = ad_comm::mpi_manager->get_num_slaves()+1;
      int nd=num_separable_calls/local_num_slaves;
      int r= num_separable_calls - nd * local_num_slaves;
      ivector mpi_partition(1,local_num_slaves);
      mpi_partition=nd;
      mpi_partition(1,r)+=1;

      ivector minsep(1,local_num_slaves);
      ivector maxsep(1,local_num_slaves);
      minsep(1)=1;
      maxsep(1)=mpi_partition(1);
      for (int i=2;i<=local_num_slaves;i++)
      {
        minsep(i)=maxsep(i-1)+1;
        maxsep(i)=minsep(i)+mpi_partition(i)-1;
      }

      min_index = minsep(1);
      max_index = maxsep(1);
      for(int i=1;i<=ad_comm::mpi_manager->get_num_slaves();i++)
      {
        ad_comm::mpi_manager->send_int_to_slave(minsep(i+1),i);
        ad_comm::mpi_manager->send_int_to_slave(maxsep(i+1),i);
      }
    }
    else
    {
      ad_comm::mpi_manager->get_int_from_master(min_index);
      ad_comm::mpi_manager->get_int_from_master(max_index);
    }
  }
  else
  {
#endif
    min_index=min_bound;
    max_index=max_bound;
#if defined(USE_ADMPI)
  }
#endif
  model_parameters_flag=0;
}

int separable_bounds::indexmin(void)
{
#if defined(USE_ADMPI)
  if (ad_comm::mpi_manager)
  {
    if (ad_comm::mpi_manager->sync_objfun_flag)
    {
      return min_index;
    }
    else
    {
      return min_bound;
    }
  }
  else
  {
#endif
    return min_bound;
#if defined(USE_ADMPI)
  }
#endif
}

int separable_bounds::indexmax(void)
{
#if defined(USE_ADMPI)
  if (ad_comm::mpi_manager)
  {
    if (ad_comm::mpi_manager->sync_objfun_flag)
    {
      return max_index;
    }
    else
    {
      return max_bound;
    }
  }
  else
  {
#endif
    return max_bound;
#if defined(USE_ADMPI)
  }
#endif
}

void  strip_full_path(BOR_CONST adstring& _s)
{
  adstring& s = (adstring&) _s; 
  int n=s.size();
  int i=0;
  for (i=n-1;i>=1;i--)
  {
    if ( s(i)=='\\' || s(i) == '/' || s(i)==':') break;
  }
  s=s(i+1,n);
}  

void set_signal_handlers(void)
{
  signal(SIGFPE,exit_handler);
  signal(SIGSEGV,exit_handler);
  signal(SIGILL,exit_handler);
  signal(SIGINT,exit_handler);
}



ad_comm::ad_comm(int _argc,char * _argv[])
{
  ad_comm::argc=_argc;
  ad_comm::argv=_argv;
  int pvm_flag=0;
  if (option_match(_argc,_argv,"-time")>-1)  
  {
    time_flag=1;
  }
  else
  {
    time_flag=0;
  }
  if (time_flag)
  {
    if (!ptm)
    {
      ptm=new adtimer();
    }
    if (!ptm1)
    {
      ptm1=new adtimer();
    }
  }
  no_atlas_flag=0;
  if (option_match(_argc,_argv,"-noatlas")>-1)  no_atlas_flag=1;
  if (option_match(_argc,_argv,"-slave")>-1)  pvm_flag=2;
  if (option_match(_argc,_argv,"-master")>-1) pvm_flag=1;

#if defined(USE_ADMPI)
  if (pvm_flag)
    mpi_manager = new admpi_manager(pvm_flag,_argc,_argv);
  else
    mpi_manager = NULL;
#endif


#if defined(USE_ADPVM)
  if (pvm_flag)
    pvm_manager = new adpvm_manager(pvm_flag);
  else
#endif
    pvm_manager = NULL;

  
#if defined(USE_ADPVM)
  if (pvm_manager)
  {
    if (pvm_manager->mode==2)   //slave
    {
      int on=0; int nopt=0;
      if ( (on=option_match(_argc,_argv,"-slave",nopt))>-1)
      {
        if (nopt ==1)	    
        {	      
          pvm_manager->slave_number=atoi(ad_comm::argv[on+1]);
        }
        else
        {
          cerr << "Wrong number of options to -slave -- must be 1"
            " you have " << nopt << endl;		
          ad_exit(1);
        }	
      }   
      if ( (on=option_match(_argc,_argv,"-slavedir",nopt))>-1)
      {
        if (nopt ==1)	    
        {	      
          ad_chdir(_argv[on+1]);
        }
        else
        {
          cerr << "Wrong number of options to -slavedir -- must be 1"
            " you have " << nopt << endl;		
        }	
      }   
    }
  }
#endif


  /*
  if (option_match(_argc,_argv,"-gui")>-1)
  {
    vm_initialize();
  }
 */
  set_signal_handlers();
  adprogram_name=_argv[0];
  int len=strlen(_argv[0]);
  for (int i=1;i<=len;i++) adprogram_name[i]=tolower(adprogram_name[i]);
#if !defined(__SPDLL__)
  strip_full_path(adprogram_name);
#endif
  adstring workdir;
  ad_getcd(workdir);
#define STR(x) STR2(x)
#define STR2(x) #x
  if (_argc>1)
  {
    if (option_match(_argc,_argv,"-?")>-1
      || option_match(_argc,_argv,"-help")>-1 )
    {
      // remove the first part of the path if present
      unsigned int i;
      for (i=adprogram_name.size();i>=1;i--)
      {
#ifdef _WIN32
        if (adprogram_name(i) == '\\')
#else
        if (adprogram_name(i) == '/')
#endif
        {
          adprogram_name=adprogram_name(i+1,adprogram_name.size());
          break;
        }
      }

      int n = adprogram_name.size() - 1;
      adprogram_name=adprogram_name(1,n);

      (*ad_printf)("AD Model Builder");
#ifdef ADMB_CONFIGURE
    //  (*ad_printf)(" %s", (char*)admb_banner);
#endif
      (*ad_printf)("\n");
      (*ad_printf)("Copyright (c) 2008, 2009, 2010 Regents of the University of California\n");
      (*ad_printf)("\n");

      (*ad_printf)( "Usage: %s option(s)\n",(char*)(adprogram_name));
      (*ad_printf)( "       where an option consists of -option_tag followed by arguments if necessary\n");
      (*ad_printf)("\n");
      (*ad_printf)( " -ainp NAME      change default ascii input parameter file name to NAME\n");
      (*ad_printf)( " -binp NAME      change default binary input parameter file name to NAME\n");
      (*ad_printf)( " -est            only do the parameter estimation\n");
      (*ad_printf)( " -noest          do not do the parameter estimation (optimization) \n");
      (*ad_printf)( " -ind NAME       change default input data file name to NAME\n");
      (*ad_printf)( " -lmn N          use limited memory quasi newton -- keep N steps\n");
      (*ad_printf)( " -lmn2 N         use other limited memory quasi newton -- keep N steps\n");
      (*ad_printf)( " -dd N           check derivatives after n function evaluations\n");
      (*ad_printf)( " -lprof          perform profile likelihood calculations\n");
      (*ad_printf)( " -maxph N        increase the maximum phase number to N\n");
      (*ad_printf)( " -mcdiag         use diagonal covariance matrix for mcmc with diagonal values 1\n");
      (*ad_printf)( " -mcmc [N]       perform markov chain monte carlo with N simulations\n");
      (*ad_printf)( " -mcmult N       multiplier N for mcmc default\n");
      (*ad_printf)( " -mcr            resume previous mcmc\n");
      (*ad_printf)( " -mcrb  N        reduce the amount of correlation in the covariance matrix 1<=N<=9\n");
      (*ad_printf)( " -mcnoscale      don't rescale step size for mcmc depending on acceptance rate\n");
      (*ad_printf)( " -nosdmcmc       turn off mcmc histogram calcs to make mcsave run faster\n");
      (*ad_printf)( " -mcgrope N      use probing strategy for mcmc with factor N\n");
      (*ad_printf)( " -mcseed N       seed for random number generator for markov chain monte carlo\n");
      (*ad_printf)( " -mcscale N       rescale step size for first N evaluations\n");
      (*ad_printf)( " -mcsave N       save the parameters for every N'th simulation\n");
      (*ad_printf)( " -mceval         Go throught the saved mcmc values from a previous mcsave\n");
//      (*ad_printf)( " -mcu            use uniformaly distributed steps for mcmc\n");
      (*ad_printf)( " -crit N1,N2,... set gradient magnitude convergence criterion to N\n");
      (*ad_printf)( " -iprint N       print out function minimizer report every N iterations\n");
      (*ad_printf)( " -maxfn N1,N2,.. set maximum number opf function eval's to N\n");
      (*ad_printf)( " -rs             if function minmimizer can't make progress rescale and try again\n");
  //    (*ad_printf)( " -sp             for DLL running from splus write to command window\n");
      (*ad_printf)( " -nox            don't show vector and gradient values in function minimizer screen report\n");
      (*ad_printf)( " -phase N        start minimization in phase N\n");
      (*ad_printf)( " -simplex        use simplex algorithm for minimization -- deprecated user should port to -neldmead\n");
      (*ad_printf)( " -neldmead       use Nelder-Mead simplex algorithm for minimization (new test version)\n");
      (*ad_printf)( " -nohess         don't do hessian or delta method for std dev\n");
      (*ad_printf)( " -eigvec         calculate eigenvectors of the Hessian\n");
      (*ad_printf)( " -sdonly         do delta method for std dev estimates without redoing hessian\n");
      (*ad_printf)( " -ams N          set arrmblsize to N (ARRAY_MEMBLOCK_SIZE)\n");
      (*ad_printf)( " -cbs N          set CMPDIF_BUFFER_SIZE to N (ARRAY_MEMBLOCK_SIZE)\n");
      (*ad_printf)( " -mno N          set the maximum number of independent variables to N\n");
      (*ad_printf)( " -mdl N          set the maximum number of dvariables to N\n");
      (*ad_printf)( " -master         run as PVM master program\n");
      (*ad_printf)( " -gbs N          set GRADSTACK_BUFFER_SIZE to N (ARRAY_MEMBLOCK_SIZE)\n");
      (*ad_printf)( " -master         run as PVM master program\n");
      (*ad_printf)( " -slave          run as PVM slave program\n");
      (*ad_printf)( " -pvmtime        record timing information for PVM performance analysis\n");
      (*ad_printf)( " -info           Contributors acknowledgements\n");
      (*ad_printf)( " -? or -help     this message\n");
      (*ad_printf)("\n");
      (*ad_printf)( " Random effects options if applicable\n");
    //if (function_minimizer::random_effects_flag)
    {
      (*ad_printf)( " -nr N           maximum number of Newton-Raphson steps\n");       
      (*ad_printf)( " -imaxfn N       maximum number of fevals in quasi-Newton inner optimization\n");       
      (*ad_printf)( " -is N           set importance sampling size to n for random effects\n");       
      (*ad_printf)( " -isf N          set importance sampling size funnel blocksto n for random effects\n");       
      (*ad_printf)( " -isdiag         print importance sampling diagnostics\n");
      (*ad_printf)( " -hybrid         do hybrid Monte Carlo version of MCMC\n");
      (*ad_printf)( " -hbf            set the hybrid bounded flag for bounded parameters\n");
      (*ad_printf)( " -hyeps          mean step size for hybrid Monte Carlo\n");
      (*ad_printf)( " -hynstep        number of steps for hybrid Monte Carlo\n");
      (*ad_printf)( " -noinit         do not initialize random effects before"
           " inner optimzation\n");       
      (*ad_printf)( " -ndi N          set maximum number of separable calls\n");       
      (*ad_printf)( " -ndb N          set number of blocks for derivatives for"
           " random effects (reduces temporary file sizes)\n");       
      (*ad_printf)( " -ddnr           use high precision Newton-Raphson for"
           " inner optimization for banded hessian case ONLY even if implemented\n");       
      (*ad_printf)( " -nrdbg          verbose reporting for debugging newton-raphson\n");       
#  if defined(__MINI_MAX__)
      (*ad_printf)( " -mm N           do minimax optimization\n");
#  endif
      (*ad_printf)( " -shess          use sparse Hessian structure"
           " inner optimzation\n");       
      (*ad_printf)("\n");
      (*ad_printf)("Read online documentation at http://www.admb-project.org/\n");
      (*ad_printf)("Contact <users@admb-project.org> for help.\n");
    }
      ad_exit(0);
    }
    else if (option_match(_argc,_argv,"-info") > -1)
    {
      (*ad_printf)("AD Model Builder");
#ifdef ADMB_CONFIGURE
      //(*ad_printf)(" %s", (char*)admb_banner);
#endif
      (*ad_printf)("\n");
      (*ad_printf)("Copyright (c) 2008, 2009, 2010 Regents of the University of California\n");
      (*ad_printf)("\n");

      (*ad_printf)("ADMB is free software and comes with ABSOLUTELY NO WARRANTY.\n");
      (*ad_printf)("You are welcome to redistribute it under certain conditions.\n");
      //(*ad_printf)("Use the –license command line option for distribution details.\n");
      (*ad_printf)("\n");
      (*ad_printf)("AD Model Builder, or ADMB, was developed by David Fournier of Otter\n");
      (*ad_printf)("Research Ltd, Sidney, B.C., Canada. In 2007, scientists from the University\n");
      (*ad_printf)("of Hawai’i at Mānoa Pelagic Fisheries Research Program (John Sibert and\n");
      (*ad_printf)("Anders Nielsen) and the Inter-American Tropical Tuna Commission (Mark\n");
      (*ad_printf)("Maunder), in consultation with scientists from NOAA Fisheries (Richard\n");
      (*ad_printf)("Methot), created the non-profit ADMB Foundation (admb-foundation.org) with\n");
      (*ad_printf)("the goal of increasing the number of ADMB users by making the software free\n");
      (*ad_printf)("and open source. In partnership with NOAA Fisheries and the National Center\n");
      (*ad_printf)("for Ecological Analysis and Synthesis (NCEAS, www.nceas.ucsb.edu), the ADMB\n");
      (*ad_printf)("Foundation obtained funding from the Gordon and Betty Moore Foundation\n");
      (*ad_printf)("(www.moore.org) to acquire the copyright to the ADMB software suite, in\n");
      (*ad_printf)("order to make it broadly and freely available to the research community. In\n");
      (*ad_printf)("2008 the copyright was transferred from Otter Research Ltd to the\n");
      (*ad_printf)("University of California. The binary files were released in December 2008\n");
      (*ad_printf)("and the source code was released in March 2009. More information about the\n");
      (*ad_printf)("ADMB project can be found at admb-project.org\n");
      (*ad_printf)("\n");
      (*ad_printf)("ADMB was initially written by David Fournier of Otter Research Ltd. ADMB is\n");
      (*ad_printf)("now the result of a collaborative effort. Since 2009 there has been a core\n");
      (*ad_printf)("group modifying the ADMB source code, currently consisting of\n");
      (*ad_printf)("\n");
      (*ad_printf)("David Fournier\n");
      (*ad_printf)("John Sibert\n");
      (*ad_printf)("Mark Maunder\n");
      (*ad_printf)("Anders Nielsen\n");
      (*ad_printf)("Hans Skaug\n");
      (*ad_printf)("Arni Magnusson\n");
      (*ad_printf)("Johnoel Ancheta\n");
      ad_exit(0);
    }
  }
  allocate();
}

ad_comm::ad_comm(void)
{
  allocate();
}

void ad_comm::allocate(void)
{
#if defined (_WIN32)
 directory_prefix='\\';
#else
 directory_prefix='/';
#endif
  adstring tmpstring;
  // remove the first part of the path if present
  unsigned int i;
#if !defined(__SPDLL__)
  for (i=adprogram_name.size();i>=1;i--)
  {
    if (adprogram_name(i)==directory_prefix)
    {
      adprogram_name=adprogram_name(i+1,adprogram_name.size());
      break;
    }
  }

#endif
  // strip off the .exe if it is there
  int n=adprogram_name.size();
  if (adprogram_name(n - 3) == '.' 
      && adprogram_name(n - 2) == 'e' 
      && adprogram_name(n - 1) == 'x' 
      && adprogram_name(n) == 'e') 
  {
    n -= 4;
  }
  adprogram_name=adprogram_name(1,n);

  // change the working directory name
  if (argc > 1)
  {
    int on=0;
    if ( (on=option_match(argc,argv,"-wd"))>-1)
    {
      if (on>argc-2 || argv[on+1][0] == '-') 
      { 
        cerr << "Invalid input data command line option"
           " -- ignored" << endl;  
      }
      else
      {
        tmpstring = adstring(argv[on+1]);
	wd_flag=1;
      }
    }
  }
  if (length(tmpstring))
  {
    if (tmpstring(length(tmpstring)) == directory_prefix)
    {
      adprogram_name=tmpstring + adprogram_name;
      working_directory_path = tmpstring;
    }
    else
    {
      adprogram_name=tmpstring + directory_prefix + adprogram_name;
      working_directory_path = tmpstring + directory_prefix;
    }
  }
  
  tmpstring=adprogram_name + adstring(".dat");
  if (argc > 1)
  {
    int on=0;
    if ( (on=option_match(argc,argv,"-ind"))>-1)
    {
      if (on>argc-2 || argv[on+1][0] == '-') 
      { 
        cerr << "Invalid input data command line option"
           " -- ignored" << endl;  
      }
      else
      {
        tmpstring = adstring(argv[on+1]);
      }
    }
  }
  global_datafile= new cifstream(tmpstring);
  if (!global_datafile)
  {
    cerr << "Error trying to open data input file "
         <<  tmpstring << endl;
  }
  else
  {
    if (!(*global_datafile))
    {
      cerr << "Error trying to open data input file "
         <<  tmpstring << endl;
      delete global_datafile;
      global_datafile=NULL;
    }
  }
  adstring ts=adprogram_name + adstring(".log");
  global_logfile= new ofstream( (char*)ts);

  int biopt=-1;
  int aiopt=-1;
  biopt=option_match(argc,argv,"-binp");
  aiopt=option_match(argc,argv,"-ainp");

  tmpstring=adprogram_name + adstring(".bin");
  if (!global_bparfile && aiopt == -1)
  {
    if (biopt>-1)
    {
      if (biopt>argc-2 || argv[biopt+1][0] == '-')
      { 
        cerr << "Invalid input parameter file command line option"
           " -- ignored" << endl;  
      }
      else
      {
        tmpstring = adstring(argv[biopt+1]);
      }
    }
    global_bparfile= new uistream(tmpstring);
    if (global_bparfile)
    {
      if (!(*global_bparfile))
      {
	if (biopt>-1)
	{
	  cerr << "Error trying to open binary inoput par file "
	       << tmpstring << endl;
	  exit(1);
	}
        delete global_bparfile;
        global_bparfile=NULL;
      }
    }
  }
  tmpstring=adprogram_name + adstring(".pin");
  if (!global_parfile)
  {
    if (aiopt>-1)
    {
      if (aiopt>argc-2 || argv[aiopt+1][0] == '-')
      { 
        cerr << "Invalid input parameter file command line option"
           " -- ignored" << endl;  
      }
      else
      {
        tmpstring = adstring(argv[aiopt+1]);
      }
    }
    global_parfile= new cifstream(tmpstring);
    if (global_parfile)
    {
      if (!(*global_parfile))
      {
	if (aiopt>-1)
	{
	  cerr << "Error trying to open ascii inoput par file "
	       << tmpstring << endl;
	  exit(1);
	}
        delete global_parfile;
        global_parfile=NULL;
      }
    }
  }
}

ad_comm::~ad_comm()
{
#if defined(USE_ADMPI)
  if (mpi_manager)
  {
    delete mpi_manager;
    mpi_manager=0;
  }
#endif

  if (ptm)
  {
    delete ptm;
    ptm=0;
  }
  if (ptm1)
  {
    delete ptm1;
    ptm1=0;
  }
  if (global_datafile)
  {
    delete global_datafile;
    global_datafile=NULL;
  }
  if (global_parfile)
  {
    delete global_parfile;
    global_parfile=NULL;
  }
  if (global_logfile)
  {
    delete global_logfile;
    global_logfile=NULL;
  }
}

#if defined(USE_ADMPI)
void add_slave_suffix(const adstring& _tmpstring)
{
  ADUNCONST(adstring,tmpstring)
  if (ad_comm::mpi_manager)
  {
    if (ad_comm::mpi_manager->is_slave())
    {
      tmpstring += "_";
      tmpstring += str(ad_comm::mpi_manager->get_slave_number());
       cout << "In slave " << tmpstring << endl;
    }
    else
    {
      tmpstring += "_master";
       cout << "In master " << tmpstring << endl;
    }
  }
}

void report_file_opening(const adstring& _tmpstring)
{
  ADUNCONST(adstring,tmpstring)
  if (ad_comm::mpi_manager)
  {
    if (ad_comm::mpi_manager->is_slave())
    {
       cout << "In slave opening file " << tmpstring << endl;
    }
    else
    {
       cout << "In master opening file " << tmpstring << endl;
    }
  }
}
#endif

void function_minimizer::pre_userfunction(void)
{
#if defined(USE_LAPLACE)
  if (lapprox)
  {
    if (lapprox->hesstype==2) 
    {
      //lapprox->num_separable_calls=0;
      lapprox->separable_calls_counter=0;
#if defined(USE_ADMPI)
      lapprox->mpi_separable_calls_counter=0;
      if (ad_comm::mpi_manager)
      {
        if (ad_comm::mpi_manager->is_slave())
        {
          ad_comm::mpi_manager->reset_mpi_cobjfun();
        }
      }
#endif
    }
  }
#endif
  userfunction();
#if defined(USE_LAPLACE)
  int i;
  if (lapprox)
  {
    if (lapprox->hesstype==2) 
    {
      lapprox->num_separable_calls=lapprox->separable_calls_counter;

      double tmp=0.0;
      int inner_opt_value=inner_opt();
      if (lapprox->saddlepointflag==2)
      {
        if (inner_opt_value !=0 )
        {
          for (i=1;i<=lapprox->num_separable_calls;i++)
          {
            tmp-=(*lapprox->separable_function_difference)(i);
          }
          value(*objective_function_value::pobjfun)=tmp;
        }
      }
      else
      {
        for (i=1;i<=lapprox->num_separable_calls;i++)
        {
          tmp+=(*lapprox->separable_function_difference)(i);
        }
        value(*objective_function_value::pobjfun)=tmp;
      }
    }
  }
#endif
#if defined(USE_ADMPI)
  if (ad_comm::mpi_manager)
  {
    if (ad_comm::mpi_manager->sync_objfun_flag)
    {
      double local_pobjfun=value(*objective_function_value::pobjfun);
      if (ad_comm::mpi_manager->is_master())
      {
        // sync objective function
        for(int si=1;si<=ad_comm::mpi_manager->get_num_slaves();si++)
        {
          local_pobjfun+=ad_comm::mpi_manager->get_double_from_slave(si);
        }
        // send to slaves
        for(int si=1;si<=ad_comm::mpi_manager->get_num_slaves();si++)
        {
          ad_comm::mpi_manager->send_double_to_slave(local_pobjfun,si);
        }
      }
      else
      {
        // sync objective function
        ad_comm::mpi_manager->send_double_to_master(local_pobjfun);
        // get initial_df1b2params::cobjfun from master
        local_pobjfun=ad_comm::mpi_manager->get_double_from_master();
      }
      value(*objective_function_value::pobjfun)=local_pobjfun;
    }
  }
#endif
}

