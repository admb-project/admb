/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>

#if ( (defined(_WINDOWS) || defined(_Windows)) && !defined(BORBUGS))
#  include <windows.h>
#endif

void ADSleep(unsigned int x);

  void test_mcmc_options_window(void);
  void ad_open_mcmc_options_window(void);
  void ad_open_mcmchist_window(void);
  void ad_update_mcmc_report(double * v,int l);
  void write_banner_stuff(void);
  int function_minimizer::have_constraints=0;
  int function_minimizer::first_hessian_flag=0;
  //int function_minimizer::in_likeprof_flag=0;

class admb_javapointers;
extern admb_javapointers * adjm_ptr;

  void function_minimizer::computations(int argc,char * argv[])
  {
    //traceflag=1;
    tracing_message(traceflag,"A1");
    //if (option_match(argc,argv,"-gui")>-1)
    //{
    //  void vm_initialize(void);
    //  vm_initialize();
    //  cout << " called vm_initialize() " << endl;
    //}
#if defined (AD_DEMO)
     write_banner_stuff();
#endif
    if (option_match(argc,argv,"-mceval") == -1)
    {
        computations1(argc,argv);
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
     // cleanup_laplace_stuff(lapprox);
  }

  void function_minimizer::computations1(int argc,char * argv[])
  {
    tracing_message(traceflag,"B1");

    int on=-1;
    int nopt=-1;
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

    // Sets the maximum number of function evaluation as determined from the
    // command line
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

    tracing_message(traceflag,"C1");

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
        {
          minimize();
        }
        else
        {
          constraints_minimize();
        }
      }
      else
      {
        initial_params::current_phase=initial_params::max_number_phases;
      }
      tracing_message(traceflag,"D1");

      //double ratio=100.*gradient_structure::max_last_offset/12000.0;
      tracing_message(traceflag,"E1");
      if (option_match(argc,argv,"-est") == -1)
      {
        if (!quit_flag)
        {
          // save the sparse Hessian for the random effects
          if (lapprox && lapprox->sparse_hessian_flag)
          {
            if (lapprox->sparse_triplet2)
            {
              dcompressed_triplet& dct=*(lapprox->sparse_triplet2);
              adstring tmpstring = ad_comm::adprogram_name + ".shess";
              uostream uos((char*)(tmpstring));
              uos << dct.get_n()  << dct.indexmin() << dct.indexmax()
                  << dct.get_coords() << dct.get_x();
            }
          }

          on=option_match(argc,argv,"-nohess");
          int on1=option_match(argc,argv,"-noest");
          if (on==-1 && on1==-1)
          {
            if (option_match(argc,argv,"-sdonly")==-1)
            {
              hess_routine();
            }
            // set this flag so that variables only needed for their std devs
            // will be calculated
            initial_params::sd_phase=1;
#if defined(USE_ADPVM)
            if (ad_comm::pvm_manager)
            {
              if (ad_comm::pvm_manager->mode==1)  //master
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
#endif
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
    #if defined(USE_ADPVM)
                if (ad_comm::pvm_manager)
                {
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
                }
                else
    #endif
                {
                  const double f = value(*objective_function_value::pobjfun);
                  likeprof_routine(f);
                }
              }
            }
            nopt=0;
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

 #if defined(USE_ADPVM)
              if (ad_comm::pvm_manager)
              {
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
              }
              else
 #endif
              {
                mcmc_computations();
              }
            }
            if ( (on=option_match(argc,argv,"-sob",nopt))>-1)
            {
              int nsob=0;
              //int iseed0=0;
              //double dscale=1.0;
              if (nopt)
              {
                nsob=atoi(argv[on+1]);
                if (nsob <=0)
                {
                  cerr << " Invalid option following command line option -sob"
                          " -- "
                    << endl << " ignored" << endl;
                }
              }
              if ( (on=option_match(argc,argv,"-mcr",nopt))>-1)
              {
                //sob_routine(nsob,dscale,1);
                //sobol_importance_routine(nsob,iseed0,dscale,1);
              }
              else
              {
                //sobol_importance_routine(nsob,iseed0,dscale,0);
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
  }

void write_banner_stuff(void)
{
  if (ad_printf)
  {
    char banner0[56]={"*****************************************************"};
    char banner1[56]={"This is the open source version of AD Model Builder"};
    char banner1a[58]={"You can freely use AD Model Builder"};
    char banner2[30]={"http://www.admb-project.org/"};
    char banner3[55]={"http://www.admb-project.org/"};
    char banner4[60]={"users@admb-project.org   http://www.admb-project.org/"};
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
#if defined (AD_DEMO)
  void adwait(double sec);
  adwait(2.5);
#endif
}

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
    int ton,tnopt = 0;
    ton=option_match(ad_comm::argc,ad_comm::argv,"-mcmc",tnopt);
    if (ton<0)
    {
      ton=option_match(ad_comm::argc,ad_comm::argv,"-mcmc2",tnopt);
    }
    int on=ton;
    int nopt=tnopt;

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
          char* end;
          double _dscale = strtod(ad_comm::argv[on + 1], &end);
          if (_dscale != 0.0)
          {
            cerr << "Invalid argument to option -mcmult" << endl;
          }
          else
          {
            dscale = _dscale;
          }
        }
      }
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcseed",nopt))>-1)
      {
        if (nopt)
        {
          int _iseed0 = atoi(ad_comm::argv[on+1]);
          if (_iseed0 <=0)
          {
            cerr << " Invalid option following command line option -mcseed -- "
              << endl << " ignored" << endl;
          }
          else
          {
            iseed0 = _iseed0;
          }
        }
      }
      int hybrid_flag=0;
      if (option_match(ad_comm::argc,ad_comm::argv,"-hybrid") > -1)
      {
        hybrid_flag=1;
        gradient_structure::Hybrid_bounded_flag=1;
      }

      // start addition
      // temporarily adding this here, need to fully merge in with other options still
      if (option_match(ad_comm::argc,ad_comm::argv,"-hmc") > -1)
	{
	  // gradient_structure::Hybrid_bounded_flag=1;
	  shmc_mcmc_routine(nmcmc,iseed0,dscale,0);
	  return;
	}
      if (option_match(ad_comm::argc,ad_comm::argv,"-nuts") > -1)
	{
	  // gradient_structure::Hybrid_bounded_flag=1;
	  nuts_mcmc_routine(nmcmc,iseed0,dscale,0);
	  return;
	}
      // Temporarily turn off this chunk if using HMC
     else
	{
	  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcr",nopt))>-1)
	    {
	      if (hybrid_flag==0)
		{
		  mcmc_routine(nmcmc,iseed0,dscale,1);
		}
	      else
		{
		  hybrid_mcmc_routine(nmcmc,iseed0,dscale,1);
		}
	    }
	  else
	    {
	      if (hybrid_flag==0)
		{
		  mcmc_routine(nmcmc,iseed0,dscale,0);
		}
	      else
		{
		  hybrid_mcmc_routine(nmcmc,iseed0,dscale,0);
		}
	    }
	}
    }
  }


#if defined(USE_ADPVM)
  void function_minimizer::pvm_master_mcmc_computations(void)
  {
    int on,nopt = 0;
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
        //mcmc_routine(nmcmc,iseed0,dscale,1);
        pvm_master_mcmc_routine(nmcmc,iseed0,dscale,1);
      }
      else
      {
        //mcmc_routine(nmcmc,iseed0,dscale,0);
        pvm_master_mcmc_routine(nmcmc,iseed0,dscale,0);
      }
    }
  }
  void function_minimizer::pvm_slave_mcmc_computations(void)
  {
    pvm_slave_mcmc_routine();
  }
#endif
