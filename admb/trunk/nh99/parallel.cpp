/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

#if defined(linux) && !defined(__WIN32)
#include <ctype.h>
    void strlwr(char * s)
    {
      if (s)
      {	      
        int n=strlen(s);	    
	for (int i=0;i<n;i++)
        {
          if (isupper(s[i]))
          {		  
	    s[i]=tolower(s[i]);
          }  
        }	  
      }		
    }	    
#endif    
typedef char * pchar;
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
#if defined(USE_ADPVM)
#include "adpvm2.h"

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
    int ierr=pvm_catchout(stdout);
    if (ierr<0)
    {
      cerr << "Error in pvm_catchout" << endl;
    }
    strcpy(*slave_argv,"progname");
    int on1,nopt1;
    if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-exec",nopt1))>-1)
    {
      if (nopt1 !=1)	    
      {
        cerr << "Wrong number of options to -exec -- must be 1"
          " you have " << nopt1 << endl;		
        ad_exit(1);
      }	
      slave_names+= ad_comm::argv[on1+1];
    }   
    else
    {
      slave_names+="test"; 
    }
  }
  timing_flag=0;
  int on1,nopt1;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-pvmtime",nopt1))>-1)
  {
    timing_flag=1;
  }
}

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

int adpvm_manager::start_slave_processes(const ad_comm& _mp)
{
  ad_comm& mp=(ad_comm&) _mp;
  cout << (mp.pvm_manager)->nhost;
  int i,j,check;
  mp.get_slave_assignments();
  if (allocated(id)) id.deallocate();
  id.allocate(1,nhost,1,num_per_host);
  adstring slavedir;
  int on=0;
  int noptslave=0;

  int td32flag=option_match(ad_comm::argc,ad_comm::argv,"-td32");

  if (td32flag>0)
  {
    strcpy(*slave_argv,slave_names[1]);
  }

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
    if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-mcmc2",nopt1))>-1)
    {
      cerr << "Error -mcmc2 option not implemented for parallel processing"
           << endl;
      ad_exit(1);
    }
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
  int slave_con=option_match(ad_comm::argc,ad_comm::argv,"-scon");

  int ii=0;
  for (i=0; i<nhost; i++)	/* spawn processes on */			
  {				/* all physical machines */
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

      if (td32flag<0)
      {
        //check=pvm_spawn(slave_names[1],*slave_argv ,
        char ** args;
        args=new pchar[10];
        args[0]=new char[20];
        args[1]=new char[20];
        strcpy(args[0],"-slave");
        strcpy(args[1],(char*)str(ii+1));
        args[2]=0;
        check=pvm_spawn(ad_comm::adprogram_name,args ,
          PvmTaskHost /* | PvmTaskDebug */ ,
          hostp[i].hi_name, 1, &(id(i+1,j)));
        ii++;
      }
      else
      {
        char ** args;
        args=new pchar[10];
        if (slave_con>0)
        {
          args[0]=new char[50];
          args[1]=new char[20];
          args[2]=new char[20];
          strncpy(args[0],ad_comm::adprogram_name,49);
          strncpy(args[1],"-slave",19);
          strncpy(args[2],(char*)str(ii+1),19);
          args[3]=0;
        }
        else
        {
          args[0]=new char[20];
          args[1]=new char[50];
          args[2]=new char[20];
          args[3]=new char[50];
  
          strcpy(args[0],"td32");
          strncpy(args[1],ad_comm::adprogram_name,49);
          strcpy(args[2],"-slave");
          strcpy(args[3],(char*)str(ii+1));
          args[4]=0;
        }
        //check=pvm_spawn("nrunslave",*slave_argv ,
        check=pvm_spawn("nrunslave",args ,
          PvmTaskHost /* | PvmTaskDebug */ ,
          hostp[i].hi_name, 1, &(id(i+1,j)));
        ii++;
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

#if defined(USE_LAPLACE)


int adpvm_manager::start_slave_processes_for_random_effects(const ad_comm& _mp)
{
  ad_comm& mp=(ad_comm&) _mp;
  cout << (mp.pvm_manager)->nhost;
  int i,j,check;
  mp.get_slave_assignments();
  if (allocated(id)) id.deallocate();
  id.allocate(1,nhost,1,num_per_host);
  adstring slavedir;
  int on=0;
  int use_td32=1;

  if (use_td32)
  {
    char ** pvmargs=new pchar[ad_comm::argc+5];
    int i;
    for (i=0;i<ad_comm::argc+5;i++)
    {
      pvmargs[i]=0;
    }
    pvmargs[0]=new char[strlen(ad_comm::adprogram_name)+1];
    strcpy(pvmargs[0],ad_comm::adprogram_name);
    
    strlwr(pvmargs[0]);
    for (i=1;i<ad_comm::argc;i++)
    {
      pvmargs[i]=new char[strlen(ad_comm::argv[i])+1];
      strcpy(pvmargs[i],ad_comm::argv[i]);
    }
    pvmargs[ad_comm::argc]=new char[strlen("-slave")+1];
    strcpy(pvmargs[ad_comm::argc],"-slave");

    pvmargs[ad_comm::argc+1]=new char[10];
    pvmargs[ad_comm::argc+3]=0;

  
    for (i=0;i<nhost;i++)
    {
      for (j=1;j<=num_per_host(i+1);j++)
      {
        strncpy(pvmargs[ad_comm::argc+1],
          (char*)(str(slave_assignments(i+1,j))),9);
        //check=pvm_spawn(pvmargs[0],pvmargs,
        check=pvm_spawn("td32rem",pvmargs,
          PvmTaskHost /* | PvmTaskDebug */ ,
          hostp[i].hi_name, 1, &(id(i+1,j)));
        if (!check) 
          printf("Couldn't start slave process %d on %s\n",j,hostp[i].hi_name); 
        else
          printf("Started slave process %d on %s\n",j,hostp[i].hi_name); 
      }
    }
  }
  else
  {
    for (i=0;i<nhost;i++)
    {
      for (j=1;j<=num_per_host(i+1);j++)
      {
        check=pvm_spawn(ad_comm::adprogram_name,0,
          PvmTaskHost /* | PvmTaskDebug */ ,
          hostp[i].hi_name, 1, &(id(i+1,j)));
        if (!check) 
          printf("Couldn't start slave process %d on %s\n",j,hostp[i].hi_name); 
        else
          printf("Started slave process %d on %s\n",j,hostp[i].hi_name); 
      }
    }
  }
  return 0;
}

#endif // #if defined(USE_LAPLACE)
adpvm_manager::~adpvm_manager(void)
{
  int i;
  // clean up slaves -- this stops all the slave processes
  for (i=1; i<=nhost; i++)	/* spawn processes on */			
  {				/* all physical machines */
    for (int j=slave_assignments(i).indexmin();
             j<=slave_assignments(i).indexmax();j++)
    {
      pvm_kill(id(i,j));
    }
  }
  //delete [] slave_argv;
  //slave_argv=NULL;
}

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


void send_int_to_slaves(int  x)
{
  // *********  begin constant send block  *************
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      int bufid = adpvm_master_cinitsend( PvmDataRaw );
      adpvm_pack(x);
      adpvm_master_csend(ad_comm::pvm_manager->id(i,j));
    }
  }
  // *********  end constant send block  *************
}


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

void send_dvector_to_slaves(const dvector&  x)
{
  // *********  begin variable send block  *************
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      int bufid = adpvm_master_cinitsend( PvmDataRaw );
      adpvm_pack(x);
      adpvm_master_csend(ad_comm::pvm_manager->id(i,j));
    }
  }
  // *********  end constant send block  *************
}

void send_dmatrix_to_slaves(const dmatrix&  x,ivector& jmin,ivector& jmax)
{
  // *********  begin variable send block  *************
  int ii=1;
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      int kmin=x.indexmin();
      int kmax=x.indexmax();
      int lmin=jmin(ii);
      int lmax=jmax(ii);
      ii++;
      dmatrix H(kmin,kmax,lmin,lmax);
      for (int k=kmin;k<=kmax;k++)
        for (int l=lmin;l<=lmax;l++)
          H(k,l)=x(k,l);

      int bufid = adpvm_master_cinitsend( PvmDataRaw );
      adpvm_pack(H);
      adpvm_master_csend(ad_comm::pvm_manager->id(i,j));
    }
  }
  // *********  end constant send block  *************
}

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

d3_array get_dmatrix_from_slaves(void)
{
  d3_array M(1,ad_comm::pvm_manager->num_slave_processes);
  // *********  begin variable send block  *************
  int ii=1;
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      // *********  begin variable receive block  *************
      adpvm_master_crecv(ad_comm::pvm_manager->id(i,j)); //get the values from slave
      adpvm_unpack(M(ii++));
      adpvm_master_end_creceive();  // have got all the values
    }
  }
  // *********  end variable receive block  *************
  return M;
}
d3_array get_dmatrix_from_slaves(const imatrix& flags)
{
  d3_array M(1,ad_comm::pvm_manager->num_slave_processes);
  // *********  begin variable send block  *************
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      if (flags(i,j))
      {
        // *********  begin variable receive block  *************
        adpvm_master_crecv(ad_comm::pvm_manager->id(i,j)); //get the values from slave
        adpvm_unpack(M(i));
        adpvm_master_end_creceive();  // have got all the values
      }
    }
  }
  // *********  end variable receive block  *************
  return M;
}


dmatrix get_dvector_from_slaves(void)
{
  dmatrix M(1,ad_comm::pvm_manager->num_slave_processes);
  // *********  begin variable send block  *************
  int ii=1;
  for (int i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (int j=ad_comm::pvm_manager->slave_assignments(i).indexmin();
             j<=ad_comm::pvm_manager->slave_assignments(i).indexmax();j++)
    {
      // *********  begin variable receive block  *************
      adpvm_master_crecv(ad_comm::pvm_manager->id(i,j)); //get the values from slave
      adpvm_unpack(M(ii++));
      adpvm_master_end_creceive();  // have got all the values
    }
  }
  // *********  end variable receive block  *************
  return M;
}

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
  
void send_int_to_master(int i)
{
  // ***************  begin send block ***********************************
  int ptid=pvm_parent();
  //adpvm_slave_cinitsend(PvmDataDefault);/* allocate message buffer */	
  adpvm_slave_cinitsend(PvmDataRaw);/* allocate message buffer */	
  adpvm_pack(i);
  adpvm_slave_csend(ptid);/* send buffer to master */
  // ***************  end send block ***********************************
}

void send_dvector_to_master(const dvector& v)
{
  // ***************  begin send block ***********************************
  int ptid=pvm_parent();
  //adpvm_slave_cinitsend(PvmDataDefault);/* allocate message buffer */	
  adpvm_slave_cinitsend(PvmDataRaw);/* allocate message buffer */	
  adpvm_pack(v);
  adpvm_slave_csend(ptid);/* send buffer to master */
  // ***************  end send block ***********************************
}

void send_dmatrix_to_master(const dmatrix& m)
{
  // ***************  begin send block ***********************************
  int ptid=pvm_parent();
  //adpvm_slave_cinitsend(PvmDataDefault);/* allocate message buffer */	
  adpvm_slave_cinitsend(PvmDataRaw);/* allocate message buffer */	
  adpvm_pack(m);
  adpvm_slave_csend(ptid);/* send buffer to master */
  // ***************  end send block ***********************************
}


void adpvm_manager::send_variable_values_to_slaves(void)
{
  int i,j;
  //for (i=ad_comm::pvm_manager->nhost;i>=1;i--) 
  //{
  for (i=1; i<=ad_comm::pvm_manager-> nhost; i++)
  {
    for (j=1; j<=ad_comm::pvm_manager-> num_per_host(i); j++)
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

void admaster_slave_variable_interface(const ad_comm& mp)
{
  if (ad_comm::pvm_manager)
  {


#  if defined(USE_LAPLACE)
    if (function_minimizer::random_effects_flag)
    {
      if (ad_comm::pvm_manager->mode==1)
      {
        ad_comm::pvm_manager->start_slave_processes_for_random_effects(mp);
        ad_comm::pvm_manager->send_variable_values_to_slaves();
      }
      if (ad_comm::pvm_manager->mode==2)
        ad_comm::pvm_manager->get_variable_values_from_master();
    }
    else
    {
#  endif
      if (ad_comm::pvm_manager->mode==1)
      {
        ad_comm::pvm_manager->start_slave_processes(mp);
        ad_comm::pvm_manager->send_variable_values_to_slaves();
      }
      if (ad_comm::pvm_manager->mode==2)
      {
        //ad_comm::pvm_manager->slave_number=get_int_from_master();
        ad_comm::pvm_manager->get_variable_values_from_master();
      }
#  if defined(USE_LAPLACE)
    }
#  endif
  }
}
void admaster_slave_variable_interface(void){;}

#else  //#if defined(USE_ADPVM)

void admaster_slave_variable_interface(void){;}
void ad_comm::get_slave_assignments(void) { ;}

void admaster_slave_variable_interface(const ad_comm& mp){;}

adpvm_slave_args::operator char ** ()
{
  return argv;
}


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

int adpvm_slave_args::get_num_args(void){return num_args;}
#endif //#if defined(USE_ADPVM)
