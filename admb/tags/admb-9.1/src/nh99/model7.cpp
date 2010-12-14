/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#else
#  include <admodel.h>
#endif
//#include <parallel.h>
#include <signal.h>

void vm_initialize(void);
int have_jvm=0;



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
  if (_argc>1)
  {
    if (option_match(_argc,_argv,"-?")>-1
      || option_match(_argc,_argv,"-help")>-1 )
    {
      // remove the first part of the path if present
      int i;
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

      for (i=1;i<=adprogram_name.size();i++)
      {
        if (adprogram_name(i)=='.') break;
      }
      int n=i-1;
      adprogram_name=adprogram_name(1,n);

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x) 
      (*ad_printf)( " AD Model Builder version " TOSTRING(ADMB_VERSION)
                   "\nCopyright (c) 2008, 2009 Regents of the University of California\n");
      (*ad_printf)(" USAGE--%s options\n",(char*)(adprogram_name));
      (*ad_printf)(" where an option consists of -option_tag followed by arguments if necessary\n");
      (*ad_printf)( " -ainp NAME      change default ascii input parameter file name to NAME\n");
      (*ad_printf)( " -binp NAME      change default binary input parameter file name to NAME\n");
      (*ad_printf)( " -est            only do the parameter estimation\n");
      (*ad_printf)( " -noest          do not do the parameter estimation (optimization) \n");
      (*ad_printf)( " -ind NAME       change default input data file name to NAME\n");
      (*ad_printf)( " -lmn N          use limited memory quasi newton -- keep N steps\n");
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
      (*ad_printf)( " -simplex        use simplex algorithm for minimization (new test version)\n");
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
      (*ad_printf)( " -nrdbg           verbose reporting for debugging newton-raphson\n");       
#  if defined(__MINI_MAX__)
      (*ad_printf)( " -mm N          do minimax optimization\n");
#  endif
      (*ad_printf)( " -shess         use sparse Hessian structure"
           " inner optimzation\n");       
    }
      ad_exit(0);
    }
    else if (option_match(_argc,_argv,"-info") > -1)
    {
      (*ad_printf)("ADMB version 9.0.x (2009-xx-xx)\n");
      (*ad_printf)("Copyright (C) 2008, 2009\n");
      (*ad_printf)("\n");
      (*ad_printf)("ADMB is free software and comes with ABSOLUTELY NO WARRANTY.\n");
      (*ad_printf)("You are welcome to redistribute it under certain conditions.\n");
      (*ad_printf)("Use the –license command line option for distribution details.\n");
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
  int i;
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
  for (i=1;i<=adprogram_name.size()-1;i++)
  {
    if ( adprogram_name(i)=='.' 
      && adprogram_name(i+1) != directory_prefix ) 
    {
      n=i-1;
      break;
    }
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

void function_minimizer::pre_userfunction(void)
{
#if defined(USE_LAPLACE)
  if (lapprox)
  {
    if (lapprox->hesstype==2) 
    {
      //lapprox->num_separable_calls=0;
      lapprox->separable_calls_counter=0;
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
}

