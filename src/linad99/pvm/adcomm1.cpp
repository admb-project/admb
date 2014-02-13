/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#if defined(USE_ADPVM)
#include "adpvm2.h"

//adstring ad_comm::subdir;

  // dvar_vector get_x_from_master(void)
  // {
  //   dvar_vector x;
  //   int ptid=pvm_parent();
  //   // ***************  begin variable receive block *********************
  //   adpvm_slave_vrecv(ptid);
  //   adpvm_unpack(x);
  //   adpvm_slave_end_vreceive();
  //   // ***************  end receive block ***********************************
  //   return x;
  // }
  //
  //
  // void send_f_to_master(const dvariable& f)
  // {
  //   // ***************  begin send block ***********************************
  //   int ptid=pvm_parent();
  //   adpvm_slave_vinitsend(PvmDataDefault);/* allocate message buffer */
  //   adpvm_pack(f);
  //   adpvm_slave_vsend(ptid);/* send buffer to master */
  //   // ***************  end send block ***********************************
  // }
  //
int adpvm_slave_args::get_num_args(void){return num_args;}

/**
 * Description not yet available.
 * \param
 */
void ad_comm::get_slave_assignments(void)
{
  // default slave assignment function
  // starts 1 slave on each host
  int nhost=pvm_manager->nhost;
  ivector & num_per_host=pvm_manager->num_per_host;
  if (allocated(num_per_host))
  {
    num_per_host.deallocate();
  }
  num_per_host.allocate(1,nhost);
  int i;
  pvm_manager->num_slave_processes=0;
  for (i=1;i<=nhost;i++)
  {
    int speed=pvm_manager->hostp[i-1].hi_speed;
    int nsprocs=speed%10;
    if (i>1) nsprocs+=1;
    cout << nsprocs << endl;
    num_per_host(i)=nsprocs;
    pvm_manager->num_slave_processes+=nsprocs;
  }
  imatrix & slave_assignments=pvm_manager->slave_assignments;
  if (allocated(slave_assignments))
  {
    slave_assignments.deallocate();
  }
  slave_assignments.allocate(1,nhost,1,num_per_host);

  slave_assignments.fill_seqadd(1,1);
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_slave_args::operator -- (void)
{
  if (counter>0)
  {
    if (argv[counter])
    {
      delete [] argv[counter];
      argv[counter]=NULL;
    }
    counter--;
    strcpy(argv[0],(char*)str(counter));
  }
}

/**
 * Description not yet available.
 * \param
 */
adpvm_slave_args::operator char ** ()
{
  return argv;
}

/**
 * Description not yet available.
 * \param
 */
void strcpy(const adpvm_slave_args& _a,const char * s)
{
  adpvm_slave_args& a=(adpvm_slave_args&) _a;
  if (((char**)(a))[a.counter])
  {
    delete [] (((char**)(a))[a.counter]);
  }
  int len=strlen(s);
  if (len>1000) len=1000;
  ((char**)(a))[a.counter] = new char[len+1];
  if (a.counter>=a.get_num_args()-1)
  {
    cerr << "need to increase the number of slave args" <<endl;
    ad_exit(1);
  }
  strncpy(((char**)(a))[a.counter++],s,len+1);
  strcpy(((char**)(a))[0],(char*)str(a.counter));
}

/**
 * Description not yet available.
 * \param
 */
void send_int_to_slaves(const ivector &  x)
{
  // *********  begin constant send block  *************
  int sz=x.size();
  if (sz != ad_comm::pvm_manager->num_slave_processes)
  {
    cerr << "wrong shape for ivector in send_int_to_slaves" << endl;
    ad_exit(1);
  }

  int ii=x.indexmin();
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    if (allocated(ad_comm::pvm_manager->slave_assignments(i)))
    {
      for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
               j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
      {
        int bufid = adpvm_master_cinitsend( PvmDataRaw );
        adpvm_pack(x(ii++));
        adpvm_master_csend(ad_comm::pvm_manager->id(i,j));
      }
    }
  }
  // *********  end constant send block  *************
}
#endif
#if defined(USE_ADPVM2)

/**
 * Description not yet available.
 * \param
 */
adpvm_manager::adpvm_manager(int _mode)
{
  cout << "calling load library" << endl;
  if (load_adpvm_library() < 0)
  {
    cerr << "error loading pvm library" << endl;
    exit(1);
  }
  pvm_setopt(PvmRoute, PvmRouteDirect);  /* channel for communication */
  /* get and display configuration of the parallel machine */
  int status=pvm_config( &nhost, &narch, &hostp );  /* get configuration */
  if (status<0)
  {
    cerr << "error trying to get configuration of pvm (virtual machine)" << endl;
    if (status == PvmSysErr)
      cerr << " PVM Daemon not responing -- maybe it is not started" << endl;
    ad_exit(1);
  }
  printf("I found the following hosts in your virtual machine\n");
  int i;
  for (i = 0; i < nhost; i++)
  {
    printf("    %s\n", hostp[i].hi_name);
  }
  //id.allocate(0,nhost);
  mode=_mode;
  if (mode == 1)  // master
  {
    slave_argv = new adpvm_slave_args(20,20);
    strcpy(*slave_argv,"progname");
    int on1,nopt1;
    if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-exec",nopt1))>-1)
    {
      if (nopt1 !=1 && nopt1 !=2)
      {
        cerr << "Wrong number of options to -exec -- must be 1"
          " you have " << nopt1 << endl;
        ad_exit(1);
      }
      slave_names+= ad_comm::argv[on1+1];
      slave_names+= "-exec";
      slave_names+= ad_comm::argv[on1+2];
    }
    else
    {
      slave_names+="test";
    }
  }
  if (!ptm)
  {
    ptm = new adtimer;
  }
}

/**
 * Description not yet available.
 * \param
 */
char * adpvm_slave_args::operator () (int i)
{
  if (i>=num_args || i<0)
  {
    cerr << "index value of " << i
         << "is out of bounds in adpvm_slave_args"
         << " maximum value is " << num_args-1
         << " minimum value is 0 " << endl;
    ad_exit(1);
  }
  return argv[i];
}
typedef char * charptr;

/**
 * Description not yet available.
 * \param
 */
adpvm_slave_args::adpvm_slave_args(int _num_args,int _length_args)
{
  //char ** argv;
  counter=1;
  num_args=_num_args;
  if (allocated(length_args))
    length_args.deallocate();
  length_args.allocate(0,num_args-1);
  length_args=_length_args;
  argv = new charptr[num_args+1];
  argv[0] = new char[20];
  for (int i = 1; i < num_args; i++)
  {
    argv[i] = NULL;
  }
  argv[num_args]=NULL;
}

/**
 * Description not yet available.
 * \param
 */
adpvm_slave_args::~adpvm_slave_args()
{
  if (argv)
  {
    for (int i = 0; i < num_args; i++)
    {
      if (argv[i])
      {
        delete [] argv[i];
        argv[i]=NULL;
      }
    }
    delete [] argv;
    argv = NULL;
    num_args=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
int adpvm_manager::start_slave_processes(const ad_comm& _mp)
{
  ad_comm& mp=(ad_comm&) _mp;
  int i,j,check;
  mp.get_slave_assignments();
  if (allocated(id)) id.deallocate();
  id.allocate(1,nhost,1,num_per_host);
  adstring slavedir;
  int on=0;
  int noptslave=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-dbg"))>-1)
     strcpy(*slave_argv,"-dbg");
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-slavedir",noptslave))>-1)
  {
    if (noptslave !=1)
    {
      cerr << "Wrong number of options to -slavedir -- must be 1"
        " you have " << noptslave << endl;
      ad_exit(1);
    }
  }
  else
  {
    noptslave=0;
  }
  int on1,nopt1;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-mcmc",nopt1))>-1)
  {
    if (nopt1 !=1)
    {
      cerr << "Wrong number of options to -mcmc -- must be 1"
        " you have " << noptslave << endl;
      ad_exit(1);
    }
    strcpy((*slave_argv),"-mcmc");
    strcpy((*slave_argv),ad_comm::argv[on1+1]);
  }

  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-nohess"))>-1)
  {
    strcpy((*slave_argv),"-nohess");
  }

  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-lprof"))>-1)
  {
    strcpy((*slave_argv),"-lprof");
  }
  int gdbflag=option_match(ad_comm::argc,ad_comm::argv,"-gdb");

  for (i=0; i<nhost; i++)      /* spawn processes on */
  {                            /* all physical machines */
    for (j=slave_assignments(i+1).indexmin();j<=slave_assignments(i+1).indexmax();
      j++)
    {
      strcpy((*slave_argv),"-slavename");
      strcpy((*slave_argv),ad_comm::adprogram_name);
      strcpy((*slave_argv),"-slave");
      strcpy((*slave_argv),(char*)(str(slave_assignments(i+1,j))));
      if (noptslave ==1)
      {
        strcpy((*slave_argv),"-slavedir");
        strcpy((*slave_argv),ad_comm::argv[on+1]);
      }

      if ( (on1=option_match(ad_comm::argc,ad_comm::argv,
        "-slaveargs",nopt1))>-1)
      {
        for (int i=on1;i<ad_comm::argc;i++)
        {
          strcpy(*slave_argv,ad_comm::argv[i]);
        }
      }
      if (gdbflag<0)
      {
        check=pvm_spawn(slave_names[1],*slave_argv ,
          PvmTaskHost /* | PvmTaskDebug */ ,
          hostp[i].hi_name, 1, &(id(i+1,j)));
      }
      else
      {
        check=pvm_spawn(slave_names[1],*slave_argv ,
          PvmTaskHost | PvmTaskDebug ,
          hostp[i].hi_name, 1, &(id(i+1,j)));
      }
      if ( (on1=option_match(ad_comm::argc,ad_comm::argv,
        "-slaveargs",nopt1))>-1)
      {
        for (int i=on1;i<ad_comm::argc;i++)
        {
          (*slave_argv)--;
        }
      }

      (*slave_argv)--;
      (*slave_argv)--;
      (*slave_argv)--;
      (*slave_argv)--;
      if (noptslave ==1)
      {
        (*slave_argv)--;
        (*slave_argv)--;
      }
      if (!check)
        printf("Couldn't start process on %s\n",hostp[i].hi_name);
      else
        printf("Started process on %s\n",hostp[i].hi_name);
    }
  }
  return check;
}

/**
 * Description not yet available.
 * \param
 */
adpvm_manager::~adpvm_manager(void)
{
  int i;
  // clean up slaves -- this stops all the slave processes
  for (i=1; i<=nhost; i++)     /* spawn processes on */
  {                            /* all physical machines */
    for (int j=slave_assignments(i).indexmin();
             j<=slave_assignments(i).indexmax();j++)
    {
      pvm_kill(id(i,j));
    }
  }
  //delete [] slave_argv;
  //slave_argv=NULL;
}

/**
 * Description not yet available.
 * \param
 */
void send_cf_to_slaves(int nvar,int current_phase,const dvar_vector&  x)
{
  // *********  begin constant send block  *************
  //for (int i=1;i<=ad_comm::pvm_manager->nhost;i++)
  //{
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i+1).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i+1).indexmax();j++)
    {
      int bufid = adpvm_master_cinitsend( PvmDataRaw );
      pvm_pack(current_phase);
      pvm_pack(nvar);
      adpvm_master_csend(ad_comm::pvm_manager->id(i,j));
    }
  }
  // *********  end variable send block  *************
}

/**
 * Description not yet available.
 * \param
 */
void send_x_to_slaves(const dvar_vector&  x)
{
  // *********  begin variable send block  *************
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      int bufid = adpvm_master_vinitsend( PvmDataRaw );
      adpvm_pack(x);
      adpvm_master_vsend(ad_comm::pvm_manager->id(i,j));
    }
  }
  // *********  end constant send block  *************
}

/**
 * Description not yet available.
 * \param
 */
imatrix get_int_from_slaves(void)
{
  imatrix fslave(1,ad_comm::pvm_manager->nhost,1,ad_comm::pvm_manager->num_per_host);
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      // *********  begin constant receive block  *************
      adpvm_master_crecv(ad_comm::pvm_manager->id(i,j)); //get the values from slave
      adpvm_unpack(fslave(i,j));
      adpvm_master_end_creceive();  // have got all the values
    }
  }
  // *********  end variable receive block  *************
  return fslave;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix get_f_from_slaves(void)
{
  dvar_matrix fslave(1,ad_comm::pvm_manager->nhost,1,ad_comm::pvm_manager->num_per_host);
  // *********  begin variable send block  *************
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      // *********  begin variable receive block  *************
      adpvm_master_vrecv(ad_comm::pvm_manager->id(i,j)); //get the values from slave
      adpvm_unpack(fslave(i,j));
      adpvm_master_end_vreceive();  // have got all the values
    }
  }
  // *********  end variable receive block  *************
  return fslave;
}

/**
 * Description not yet available.
 * \param
 */
int get_int_from_master(void)
{
  int x;
  int ptid=pvm_parent();
  // ***************  begin constant receive block *********************
  adpvm_slave_crecv(ptid);
  adpvm_unpack(x);
  adpvm_slave_end_creceive();
  // ***************  end receive block ***********************************
  return x;
}

/**
 * Description not yet available.
 * \param
 */
void send_int_to_master(int i)
{
  // ***************  begin send block ***********************************
  int ptid=pvm_parent();
  adpvm_slave_cinitsend(PvmDataDefault);/* allocate message buffer */
  adpvm_pack(i);
  adpvm_slave_csend(ptid);/* send buffer to master */
  // ***************  end send block ***********************************
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_manager::send_variable_values_to_slaves(void)
{
  int i,j;
  //for (i=ad_comm::pvm_manager->nhost;i>=1;i--)
  //{
  for (i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      // *********  begin constant send block  *************
      int bufid = adpvm_master_cinitsend( PvmDataRaw );
      // pack all the variables
      for (int jj=1;jj<=initial_params::num_initial_params;jj++)
      {
        initial_params::varsptr[jj-1]->pvm_pack();
      }
      adpvm_master_csend(id(i,j));
      // *********  end constant send block  *************
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void adpvm_manager::get_variable_values_from_master(void)
{
  int i,j;
  // ***************  begin constant receive block *************************
  int ptid=pvm_parent();
  adpvm_slave_crecv(ptid);
  // unpack all the variables
  for (j=1;j<=initial_params::num_initial_params;j++)
  {
    initial_params::varsptr[j-1]->pvm_unpack();
  }
  adpvm_slave_end_creceive();
  // ***************  end receive block ***********************************
}

/**
 * Description not yet available.
 * \param
 */
void admaster_slave_variable_interface(const ad_comm& mp)
{
  if (ad_comm::pvm_manager)
  {
    if (ad_comm::pvm_manager->mode==1)
    {
      ad_comm::pvm_manager->start_slave_processes(mp);
      ad_comm::pvm_manager->send_variable_values_to_slaves();
    }
    if (ad_comm::pvm_manager->mode==2)
      ad_comm::pvm_manager->get_variable_values_from_master();
  }
}
#endif //#if defined(USE_ADPVM)
