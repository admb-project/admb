/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>
//#define NO_MCMC
#if ( (defined(_WINDOWS) || defined(_Windows)) && !defined(BORBUGS))
#  include <windows.h>
#endif
char banner0[56]={"*****************************************************"};
char banner1[56]={"This is the open source version of AD Model Builder"};
char banner1a[58]={"You can freely use AD Model Builder"};
char banner2[30]={"http://www.admb-project.org/"};
char banner3[55]={"http://www.admb-project.org/"};
char banner4[60]={"users@admb-project.org   http://www.admb-project.org/"};
int ad_cheat_flag=0;
#if defined(linux)
  int Sleep(int);
#endif

static int return_int(int * v)
{
  if (*v==1011)
    return 1912;
  else
    return 1831;
}

void ADSleep(int x);

  void check_java_flags(int& start_flag,int& quit_flag,int& der_flag,
    int& next_flag);
  void vm_initialize(void);
  void test_mcmc_options_window(void);
  void ad_open_mcmc_options_window(void);
  void ad_open_mcmchist_window(void);
  void ad_update_mcmc_report(double * v,int l);
  void write_banner_stuff(void);
  void calljunk(double x){;}
//#if defined (AD_DEMO)
  void adwait(double sec);
//#endif
  int function_minimizer::have_constraints=0;
  int function_minimizer::first_hessian_flag=0;
  //int function_minimizer::in_likeprof_flag=0;

class admb_javapointers;
extern admb_javapointers * adjm_ptr;

  static int try_it_again(int stupid_flag);

#if defined(ADMB_REDEMO)
  static int q830=830;
  int ** pflag1;
  int ** pflag2;
  int ** pflag3;
  int ** pflag4;
  int ** pflag5;
  int * qflag1;
  int * qflag2;
  int * qflag3;
  int * qflag4;
  int * qflag5;
  int flag1=10;
  int flag2=11;
  int flag3=12;
  int flag4=13;
  int flag5=14;
  
#endif

  
  void extra_random_effects_generator1(void);
  void extra_random_effects_generator2(void);
  void extra_random_effects_generator3(void);

  void function_minimizer::computations(int argc,char * argv[])
  {
    //traceflag=1;
    tracing_message(traceflag,"A1");
    //if (option_match(argc,argv,"-gui")>-1)
    //{
    //  vm_initialize();
    //  cout << " called vm_initialize() " << endl;
    //}
#if defined(__SPDLL__)
    //if (ad_printf) (*ad_printf)("entered void function_minimizer::computations\n");
#endif
#if defined (AD_DEMO)
     write_banner_stuff();
#endif
    if (option_match(argc,argv,"-mceval") == -1)
    {
      //negative_eigenvalue_flag=0;
      //do
      {
#if defined(ADMB_REDEMO)
  exit(1);
#else
        computations1(argc,argv);
#endif
      }
      //while(negative_eigenvalue_flag);
    }
    else
    {
      initial_params::mceval_phase=1;
      mcmc_eval();
      initial_params::mceval_phase=0;
    }
    other_calculations();
    
    final_calcs();
    // clean up if have random effects
#   if defined(USE_LAPLACE)
     // cleanup_laplace_stuff(lapprox);
#   endif
  }
int something_105=0;
static int something_106=0;

#if defined(ADMB_REDEMO)
static int stupid_flag=17;
int * kill_address;
#endif  //#if defined(ADMB_REDEMO)
          int kill_flag_105=901;
          int kill_flag_107=901;

  void function_minimizer::computationsx(int argc,char * argv[])
  {
#if !defined(ADMB_REDEMO)
    ad_exit(0);
#endif
    int f03=0;
    int two=0;
    //traceflag=1;
    int *  xflag_105=0;
    f03=503;
#if defined(ADMB_REDEMO)
    kill_address=&stupid_flag;
#endif
    two=2;
    tracing_message(traceflag,"A1");
    //if (option_match(argc,argv,"-gui")>-1)
    //{
    //  vm_initialize();
    //  cout << " called vm_initialize() " << endl;
    //}
#if defined(__SPDLL__)
    //if (ad_printf) (*ad_printf)("entered void function_minimizer::computations\n");
#endif
#if defined (AD_DEMO)
     write_banner_stuff();
#endif
#if defined(ADMB_REDEMO)
    stupid_flag=0;
#endif
    xflag_105=&something_105;
    if (option_match(argc,argv,"-mceval") == -1)
    {
      //negative_eigenvalue_flag=0;
      //do
#if defined(ADMB_REDEMO)
      for (int ic1=1;ic1<=1000;ic1++)
      {
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        int * s830=&q830;
        extra_random_effects_generator1();
        if (ic1==3* (*s830) )
        {
          extra_random_effects_generator2();
        }
        extra_random_effects_generator3();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
      }
      int *  xflag_106=0;
      for (int ic=1;ic<=1000;ic++)
      {
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        int * s830=&q830;
        extra_random_effects_generator1();
        if (ic==*s830)
        {
          extra_random_effects_generator2();
        }
        extra_random_effects_generator3();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        xflag_106=&something_106;
        extra_random_effects_generator1();
      }
      if (**pflag1 == 1005)
         *xflag_105=1345;
      if (**pflag2 == f03*two+1)
         *xflag_106=f03-two;
      for (int icc=1;icc<=1000;icc++)
      {
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        int * s830=&q830;
        extra_random_effects_generator1();
        if (icc==2000)
        {
          extra_random_effects_generator2();
        }
        extra_random_effects_generator3();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
      }

      if (*xflag_105!=1345)
        kill_flag_105=1;
      if(*xflag_106!=501)
        kill_flag_107=10;
      for (int iccc=1;iccc<=1000;iccc++)
      {
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        int * s830=&q830;
        extra_random_effects_generator1();
        if (iccc==3000)
        {
          extra_random_effects_generator2();
        }
        extra_random_effects_generator3();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
      }
      if (kill_flag_105!=kill_flag_107/2-2*two)
      {
        try_it_again(stupid_flag);
      }
      for (int icccc=1;icccc<=1000;icccc++)
      {
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        int * s830=&q830;
        extra_random_effects_generator1();
        if (iccc==3000)
        {
          extra_random_effects_generator2();
        }
        extra_random_effects_generator3();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
      }
#if defined (AD_REDEMO)
      if (kill_flag_105==kill_flag_107/2-2*two)
      {
        kill_address=0;
      }
#endif
#if !defined(ADMB_REDEMO)
    exit(0);
#endif
      for (int icu=1;icu<=1000;icu++)
      {
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        int * s830=&q830;
        extra_random_effects_generator1();
        if (icu==3000)
        {
          extra_random_effects_generator2();
        }
        extra_random_effects_generator3();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
        extra_random_effects_generator1();
      }
#if defined(ADMB_REDEMO)
      *kill_address=1;
#endif

#if !defined(ADMB_REDEMO)
    exit(0);
#endif
#endif  //#if defined(ADMB_REDEMO)
      {
        computations1(argc,argv);
      }
      //while(negative_eigenvalue_flag);
    }
    else
    {
      initial_params::mceval_phase=1;
      mcmc_eval();
      initial_params::mceval_phase=0;
    }
    other_calculations();
    final_calcs();
    // clean up if have random effects
#   if defined(USE_LAPLACE)
     // cleanup_laplace_stuff(lapprox);
#   endif
  }

  void function_minimizer::computations1(int argc,char * argv[])
  {
    tracing_message(traceflag,"B1");
#if defined(__SPDLL__)
    //if (ad_printf) (*ad_printf)("entered void function_minimizer::computations1\n");
#endif

#if defined (AD_DEMO)
     if (gradient_structure::ARRAY_MEMBLOCK_SIZE != 12000)
     {
#if defined(__SPDLL__)
       //if (ad_printf) (*ad_printf)("setting ad_chea_flag\n");
#endif
       ad_cheat_flag=1;
     }
#endif
    char ch;
    int on=-1;
    int nopt=-1;
    //dvector xxxx("{1.1,2.1,3.1}");
#if defined(USE_ADPVM)
    if (ad_comm::pvm_manager)
    {
      switch (ad_comm::pvm_manager->mode)
      {
      case 1: //master
        pvm_params::send_all_to_slaves();
        break;
      case 2: //slave
        pvm_params::get_all_from_master();
        break;
      default:
        cerr << "Illegal value for ad_comm::pvm_manager->mode"
         " value was " << ad_comm::pvm_manager->mode << endl;
        ad_exit(1);
      }
    }
#endif  // #if defined(USE_ADPVM)
      
    set_runtime();

    if ( (on=option_match(argc,argv,"-hbf",nopt))>-1)
    {
      gradient_structure::Hybrid_bounded_flag=1;
    }

    if ( (on=option_match(argc,argv,"-maxfn",nopt))>-1)
    {
      if (nopt ==1)            
      {              
        set_runtime_maxfn(argv[on+1]);
      }
      else
      {
        cerr << "Wrong number of options to -mafxn -- must be 1"
          " you have " << nopt << endl;                
      }        
    }   
    
    if ( (on=option_match(argc,argv,"-ttr",nopt))>-1)
    {
      test_trust_flag=1;
    }

    if ( (on=option_match(argc,argv,"-crit",nopt))>-1)
    {
      if (nopt ==1)            
      {              
        set_runtime_crit(argv[on+1]);
      }
      else
      {
        cerr << "Wrong number of options to -crit -- must be 1"
          " you have " << nopt << endl;                
      }        
    }   

    stddev_params::get_stddev_number_offset();

#if defined (AD_DEMO)
    if (ad_cheat_flag==1)
    {
      exit(0);
    }
#endif

    tracing_message(traceflag,"C1");

#if defined(ADMB_REDEMO)
  if (return_int(*pflag5) != 1912)
  {
    for (int i=0;i<initial_params::num_initial_params;i++)
    {
      initial_params::varsptr[i]=0;
    }
  }

#endif // #if defined(ADMB_REDEMO)


    repeatminflag=0;
    do 
    {
     /*
      if (spminflag)
      {
        repeatminflag=1;
        spminflag=0;
      }
      else
      {
        repeatminflag=0;
      }
      */

      if (option_match(argc,argv,"-noest") == -1)
      {
        if (!function_minimizer::have_constraints)
          minimize();
        else
          constraints_minimize();
      }
      else
      {
        initial_params::current_phase=initial_params::max_number_phases;
      }
      
      tracing_message(traceflag,"D1");
  
      double ratio=100.*gradient_structure::max_last_offset/12000.0;
  #if defined (AD_DEMO)
      cout << endl << endl;
      if (ad_printf)
      {
        (*ad_printf) (" Your model used %lf  percent of demonstration version"
           " capacity \n",ratio);
      }
      write_banner_stuff();
  
  #endif
      tracing_message(traceflag,"E1");
      if (option_match(argc,argv,"-est") == -1)
      {
        if (!quit_flag)
        {
          int on=-1;
          int on1=-1;
          on=option_match(argc,argv,"-nohess");
          on1=option_match(argc,argv,"-noest");
          if (on==-1 && on1==-1)
          {
            if (option_match(argc,argv,"-sdonly")==-1)
            {
              hess_routine();
            }
            // set this flag so that variables only needed for their std devs
            // will be calculated
            initial_params::sd_phase=1;
            if (ad_comm::pvm_manager)
            {
  #if defined(USE_ADPVM)
              if (ad_comm::pvm_manager->mode==1)  //master
              {
                depvars_routine();
                hess_inv();
                if (spminflag==0)
                {
                  sd_routine();
                }
              }
  #else
              {
                cerr << "PVM not included with this distribution" << endl;
                ad_exit(1);
              }
  #endif
            }
            else
            {
              depvars_routine();
              hess_inv();
              if (spminflag==0)
              {
                sd_routine();
              }
            }
          }
          else
          {
            initial_params::sd_phase=1;
          }
          if (spminflag==0)
          {
            if ( (on=option_match(argc,argv,"-lprof"))>-1)
            {
              if (likeprof_params::num_likeprof_params)
              {
                if (!ad_comm::pvm_manager)
                {
                  likeprof_routine(ffbest);
                }
                else
    #if defined(USE_ADPVM)
                switch (ad_comm::pvm_manager->mode)
                {
                case 1: // master
                  likeprof_routine(ffbest);
                break;
                case 2: // slave
                  pvm_slave_likeprof_routine();
                  break;
                default:
                  cerr << "error illega value for pvm_manager->mode" << endl;
                  exit(1);
                }
    
    #else
                cerr << "PVM not included with this distribution" << endl;
                ad_exit(1);
    #endif
              }
            }
            int nopt=0;
            int on2=-1;
            int nopt2=-1;
  
            // stuff for mcmc
            //cout << "checking for mcmc" << endl;
            if ( (on=option_match(argc,argv,"-mcmc",nopt))>-1 ||
                 (on=option_match(argc,argv,"-mcmc2",nopt))>-1)
            {
              if ( (on2=option_match(argc,argv,"-mcmc2",nopt2))>-1)
                mcmc2_flag=1;
              else
                mcmc2_flag=0;
    
              if (!ad_comm::pvm_manager)
              {
                mcmc_computations();
              }
              else
              {
    #if defined(USE_ADPVM)
                switch (ad_comm::pvm_manager->mode)
                {
                case 1: // master
                  pvm_master_mcmc_computations();
                break;
                case 2: // slave
                  pvm_slave_mcmc_routine();
                  break;
                default:
                  cerr << "error illega value for pvm_manager->mode" << endl;
                  exit(1);
                }
    #else
                cerr << "PVM not included with this distribution" << endl;
                ad_exit(1);
    #endif
              }
            }
       
            if ( (on=option_match(argc,argv,"-sob",nopt))>-1)
            {
              int nsob=0;
              int iseed0=0;
              double dscale=1.0;
              if (nopt)
              {
                nsob=atoi(argv[on+1]);
                if (nsob <=0)
                {
                  cerr << " Invalid option following command line option -sob -- "
                    << endl << " ignored" << endl;
                }
              }
              if ( (on=option_match(argc,argv,"-mcr",nopt))>-1)
              {
    #if defined(NO_MCMC)
                cerr << "mcmc and sob option not supported you must purchase"
                        " this as an add on" << endl;
                exit(1);
    #else
                //sob_routine(nsob,dscale,1);
                //sobol_importance_routine(nsob,iseed0,dscale,1);
    #endif
          
              }
              else
              {
    #if defined(NO_MCMC)
                cerr << "mcmc and sob option not supported you must purchase"
                        " this as an add on" << endl;
                exit(1);
    #else
                //sobol_importance_routine(nsob,iseed0,dscale,0);
    #endif
         
              }
            }
            initial_params::sd_phase=0;
          }
        }
      }
    }
    while(spminflag || repeatminflag);
  }


  void function_minimizer::computations(void)
  {
    // for now just do parameter estimates
    //function_minimizer::minimize();
    minimize();
    //
  }


void write_banner_stuff(void)
{
  if (ad_printf)
  {  
    (*ad_printf)("\n%s\n", banner0);
    (*ad_printf)("%s\n", banner1);
    (*ad_printf)("%s\n", banner1a);
    (*ad_printf)("%s\n", banner2);
    (*ad_printf)("%s\n", banner3);
    (*ad_printf)("%s\n", banner4);
    //(*ad_printf)("%s\n", adcopy);
    (*ad_printf)("%s\n", banner0);
    (*ad_printf)("%s\n\n", banner0);
  }
  adwait(2.5);
}

/*
#if defined (AD_DEMO)
#include <time.h>
double waste_time();

void adwait(double sec)
{
  time_t tt;
  time_t ttold;
  time(&ttold);
  do
  {
    time(&tt);
    if ( (tt-ttold) > sec ) break;
  }
  while(1);
}
#else
void adwait(double sec){;}
#endif
*/

  void test_mcmc_options_window(void)
  {
    dvector v(1,1000);
    random_number_generator rng(908);

    for (int i=5;i<=1000;i++)
    {
      rng.reinitialize(908);
      v(1,i).fill_randn(rng);
      for (int j=2;j<=i;j++)
      {
        v(j)=0.9*v(j-1)+0.435889*v(j);
      }

      //ad_update_mcmc_report(&(v(1)),i);
      ADSleep(500);

    }
  }

  void function_minimizer::set_runtime(void){;}

  void function_minimizer::set_runtime_maxfn(const char * s)
  {
    adstring opt="{" + adstring(s) + "}";          
    dvector temp1((char*)(opt));
    if (allocated(maximum_function_evaluations))
      maximum_function_evaluations.deallocate();
    maximum_function_evaluations.allocate(temp1.indexmin(),temp1.indexmax());
    maximum_function_evaluations=temp1;
  }  

  void function_minimizer::set_runtime_crit(const char * s)
  {
    adstring opt="{" + adstring(s) + "}";          
    dvector temp1((char*)(opt));
    if (allocated(convergence_criteria)) convergence_criteria.deallocate();
    convergence_criteria.allocate(temp1.indexmin(),temp1.indexmax());
    convergence_criteria=temp1;
  }  


  void function_minimizer::mcmc_computations(void)
  {
    int ton,tnopt;
    int on,nopt;
    ton=option_match(ad_comm::argc,ad_comm::argv,"-mcmc",tnopt);
    if (ton<0)
    {
      ton=option_match(ad_comm::argc,ad_comm::argv,"-mcmc2",tnopt);
    }
    on=ton;
    nopt=tnopt;
     
    if (on>-1)
    {
      /*
      if (adjm_ptr)
      {
        ad_open_mcmc_options_window();
        ad_open_mcmchist_window();
        //test_mcmc_options_window();
      }
      */
      int nmcmc=0;
      int iseed0=0;
      double dscale=1.0;
      if (nopt)
      {
        nmcmc=(int)atof(ad_comm::argv[on+1]);
        if (nmcmc <=0)
        {
          cerr << " Invalid option following command line option -mcmc -- "
            << endl << " ignored" << endl;
        }
      }
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcmult",nopt))>-1)
      {
        if (nopt)
        {
          char * end;
          dscale=strtod(ad_comm::argv[on+1],&end);
          if (!dscale) 
          {
            cerr << "Invalid argument to option -mcmult" << endl;
            dscale=1.0;
          }
        }
      }    
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcseed",nopt))>-1)
      {
        if (nopt)
        {
          iseed0=atoi(ad_comm::argv[on+1]);
          if (iseed0 <=0)
          {
            cerr << " Invalid option following command line option -mcseed -- "
              << endl << " ignored" << endl;
            iseed0=0;
          }
        }
      }    
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcr",nopt))>-1)
      {
#if defined(NO_MCMC)
        cerr << "mcmc option not supported you must purchase"
                " this as an add on" << endl;
        exit(1);
#else
        mcmc_routine(nmcmc,iseed0,dscale,1);
#endif
      }
      else
      {
#if defined(NO_MCMC)
        cerr << "mcmc option not supported you must purchase"
                " this as an add on" << endl;
        exit(1);
#else
        int hybrid_flag=0;
        if (option_match(ad_comm::argc,ad_comm::argv,"-hybrid") > -1)
        {
          hybrid_flag=1;
          gradient_structure::Hybrid_bounded_flag=1;
        }
        if (hybrid_flag==0)
        {
          mcmc_routine(nmcmc,iseed0,dscale,0);
        }
        else
        {
          hybrid_mcmc_routine(nmcmc,iseed0,dscale,0);
        }
#endif
      }
    }
  }

  void function_minimizer::pvm_master_mcmc_computations(void)
  {
    int on,nopt;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcmc",nopt))>-1)
    {
      /*
      if (adjm_ptr)
      {
        ad_open_mcmc_options_window();
        ad_open_mcmchist_window();
        //test_mcmc_options_window();
      }
      */
      int nmcmc=0;
      int iseed0=0;
      double dscale=1.0;
      if (nopt)
      {
        nmcmc=(int)atof(ad_comm::argv[on+1]);
        if (nmcmc <=0)
        {
          cerr << " Invalid option following command line option -mcmc -- "
            << endl << " ignored" << endl;
        }
      }
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcmult",nopt))>-1)
      {
        if (nopt)
        {
          char * end;
          dscale=strtod(ad_comm::argv[on+1],&end);
          if (!dscale) 
          {
            cerr << "Invalid argument to option -mcmult" << endl;
            dscale=1.0;
          }
        }
      }    
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcseed",nopt))>-1)
      {
        if (nopt)
        {
          iseed0=atoi(ad_comm::argv[on+1]);
          if (iseed0 <=0)
          {
            cerr << " Invalid option following command line option -mcseed -- "
              << endl << " ignored" << endl;
            iseed0=0;
          }
        }
      }    
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcr",nopt))>-1)
      {
#if defined(NO_MCMC)
        cerr << "mcmc option not supported you must purchase"
                " this as an add on" << endl;
        exit(1);
#else
        //mcmc_routine(nmcmc,iseed0,dscale,1);
        pvm_master_mcmc_routine(nmcmc,iseed0,dscale,1);
#endif
      }
      else
      {
#if defined(NO_MCMC)
        cerr << "mcmc option not supported you must purchase"
                " this as an add on" << endl;
        exit(1);
#else
        //mcmc_routine(nmcmc,iseed0,dscale,0);
        pvm_master_mcmc_routine(nmcmc,iseed0,dscale,0);
#endif
      }
    }
  }
  void function_minimizer::pvm_slave_mcmc_computations(void)
  {
    pvm_slave_mcmc_routine();
  }
#if defined(ADMB_REDEMO)

  int rn3;
  
  extern "C" {
  int verifier1(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier2(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier3(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier4(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  //int verifier5(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier6(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier7(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier8(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier9(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier10(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier11(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier12(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier13(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier14(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier15(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier16(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier17(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier18(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier19(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  int verifier20(int **pflag1,int ** p2,int ** p3,int ** p4,int ** p5);
  }
  
  
  void extra_random_effects_generator2(void)
  {
    int i=1;
    pflag1=&qflag1;
    pflag2=&qflag2;
    pflag3=&qflag3;
    pflag4=&qflag4;
    pflag5=&qflag5;
    qflag1=&flag1;
    qflag2=&flag2;
    qflag3=&flag3;
    qflag4=&flag4;
    qflag5=&flag5;
    qflag5=&flag5;
    int ret=verifier1(pflag1,pflag2,pflag3,pflag4,pflag5);
    
    for (i=1;i<20;i++)
      ret=verifier2(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier3(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier3(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier4(pflag1,pflag2,pflag3,pflag4,pflag5);
    //for (i=1;i<20;i++)
     // ret=verifier5(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier6(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier7(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier8(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier9(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier10(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier11(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier12(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier13(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier14(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier15(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier16(pflag1,pflag2,pflag3,pflag4,pflag5);
    
      ret=verifier17(pflag1,pflag2,pflag3,pflag4,pflag5);
  
    for (i=1;i<20;i++)
      ret=verifier18(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier19(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier20(pflag1,pflag2,pflag3,pflag4,pflag5);
  /*
    cout << " **pflag1 = " << **pflag1 << endl;
    cout << " **pflag2 = " << **pflag2 << endl;
    cout << " **pflag3 = " << **pflag3 << endl;
    cout << " **pflag4 = " << **pflag4 << endl;
    cout << " *qflag5 = " << *qflag5 << endl;
 */
  }
  
  void extra_random_effects_generator1(void)
  {
    int i=1;
    pflag1=&qflag1;
    pflag2=&qflag2;
    pflag3=&qflag3;
    pflag4=&qflag4;
    pflag5=&qflag5;
    qflag1=&flag1;
    qflag2=&flag2;
    qflag3=&flag3;
    qflag4=&flag4;
    qflag5=&flag5;
    qflag5=&flag5;
    int ret=verifier1(pflag1,pflag2,pflag3,pflag4,pflag5);
    
    for (i=1;i<20;i++)
      ret=verifier2(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier3(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier3(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier4(pflag1,pflag2,pflag3,pflag4,pflag5);
    //for (i=1;i<20;i++)
      //ret=verifier5(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier6(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier7(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier8(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier9(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier10(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier11(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier12(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier13(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier14(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier15(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier16(pflag1,pflag2,pflag3,pflag4,pflag5);
    
      //ret=verifier17(pflag1,pflag2,pflag3,pflag4,pflag5);
  
    for (i=1;i<20;i++)
      ret=verifier18(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier19(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier20(pflag1,pflag2,pflag3,pflag4,pflag5);
  }
  
  void extra_random_effects_generator3(void)
  {
    int i=1;
    pflag1=&qflag1;
    pflag2=&qflag2;
    pflag3=&qflag3;
    pflag4=&qflag4;
    pflag5=&qflag5;
    qflag1=&flag1;
    qflag2=&flag2;
    qflag3=&flag3;
    qflag4=&flag4;
    qflag5=&flag5;
    qflag5=&flag5;
    int ret=verifier1(pflag1,pflag2,pflag3,pflag4,pflag5);
    
    for (i=1;i<20;i++)
      ret=verifier2(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier3(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier3(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier4(pflag1,pflag2,pflag3,pflag4,pflag5);
    //for (i=1;i<20;i++)
     // ret=verifier5(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier6(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier7(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier8(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier9(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier10(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier11(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier12(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier13(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier14(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier15(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier16(pflag1,pflag2,pflag3,pflag4,pflag5);
    
      //ret=verifier17(pflag1,pflag2,pflag3,pflag4,pflag5);
  
    for (i=1;i<20;i++)
      ret=verifier18(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier19(pflag1,pflag2,pflag3,pflag4,pflag5);
    for (i=1;i<20;i++)
      ret=verifier20(pflag1,pflag2,pflag3,pflag4,pflag5);
  }
  
  int try_it_again(int stupid_flag)
  {
    if (stupid_flag)
      exit(1);
    switch (stupid_flag)
    {
    case 1:
      exit(1); 
    case 2:
      exit(1); 
    case 3:
      exit(1); 
    case 4:
      exit(1); 
    case 5:
      exit(1); 
    case 6:
      exit(1); 
    case 7:
      exit(1); 
    case 8:
      exit(1); 
    case 9:
      exit(1); 
    }
    return 6945;
  }   
#else
  void extra_random_effects_generator2(void) {;}
  
#endif  //#if defined(ADMB_REDEMO)
