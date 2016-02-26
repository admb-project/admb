/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <sstream>
using std::istringstream;

#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>

void check_java_flags(int& start_flag,int& quit_flag,int& der_flag,
  int& next_flag);

void ad_update_function_minimizer_report(int feval,int iter,int phase,
  double fval, double gmax,const char * cbuf);
void vm_initialize(void);

void set_initial_simplex(const tdmatrix& p, const dvector& y,int nvar,
  const dvector& x, double delta);

int get_option_number(const char * option_name,const char * error_message,
  int& option_value);

int get_option_number(const char * option_name,const char * error_message,
#ifdef __BORLANDC__
  long int& option_value);
#else
  long long int& option_value);
#endif

extern int traceflag;

void tracing_message(int traceflag,const char *s);

  int function_minimizer::inner_opt(void)
  {
    return inner_opt_flag;
  }

  int function_minimizer::inner_opt_flag=0;


  int function_minimizer::bad_step_flag=0;

  void function_minimizer::minimize(void)
  {
    int nopt=0;
    int on=0;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-shess"))>-1)
    {
      laplace_approximation_calculator::sparse_hessian_flag=1;
    }
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-pis"))>-1)
    {
     laplace_approximation_calculator::print_importance_sampling_weights_flag=1;
    }
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-sp"))>-1)
    {
      laplace_approximation_calculator::saddlepointflag=1;
    }
#    if defined(__MINI_MAX__)
        if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mm"))>-1)
        {
          laplace_approximation_calculator::saddlepointflag=2;
        }
#    else
        if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mm"))>-1)
        {
           cerr << "option -mm MINI_MAX not defined " << endl;
           ad_exit(1);
        }
#    endif

    //initial_params::read(); // read in the values for the initial parameters
    if (initial_params::restart_phase)
    {
      initial_params::current_phase = initial_params::restart_phase;
      initial_params::restart_phase=0;
    }
    int allphases=initial_params::max_number_phases;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-maxph",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -maxph option needs integer  -- ignored" << endl;
      }
      else
      {
        int jj=atoi(ad_comm::argv[on+1]);
        if (jj<=0)
        {
          cerr << "Usage -maxph option needs positive integer  -- ignored.\n";
        }
        else
        {
          if (jj>allphases)
          {
            allphases=jj;
          }
        }
      }
      if (allphases>initial_params::max_number_phases)
      {
        initial_params::max_number_phases=allphases;
      }
    }
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-ndv",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -ndv option needs integer  -- ignored" << endl;
      }
      else
      {
        int jj=atoi(ad_comm::argv[on+1]);
        if (jj<=0)
        {
          cerr << "Usage -ndv option needs positive integer  -- ignored.\n";
        }
        else
        {
          gradient_structure::NUM_DEPENDENT_VARIABLES=jj;
        }
      }
    }

    // set the maximum number of function evaluations by command line
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-maxfn",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -maxph option needs integer  -- ignored" << endl;
      }
      else
      {
        int _maxfn=atoi(ad_comm::argv[on+1]);
        if (_maxfn<0)
        {
          cerr << "Usage -maxfn option needs positive integer  -- ignored.\n";
        }
        else
        {
          maxfn=_maxfn;
        }
      }
    }
    int _crit=0;
    // set the maximum number of function evaluations by command line
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-crit",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -crit option needs number  -- ignored" << endl;
      }
      else
      {
        istringstream ist(ad_comm::argv[on+1]);
        ist >> _crit;

        if (_crit<=0)
        {
          cerr << "Usage -crit option needs positive number  -- ignored.\n";
          _crit=0;
        }
      }
    }
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-bw",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -bw option needs number  -- ignored" << endl;
      }
      else
      {
        int bandwidth = 0;
        istringstream ist(ad_comm::argv[on+1]);
        ist >> bandwidth;

        if (bandwidth <= 0)
        {
          cerr << "Usage -bw option needs positive number  -- ignored" << endl;
          ad_comm::bandwidth = 0;
        }
        else
        {
          ad_comm::bandwidth = bandwidth;
        }
      }
    }
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-phase"))>-1)
    {
      int jj=atoi(ad_comm::argv[on+1]);
      if (jj <=0)
      {
        cerr << " Invalid option following command line option -phase -- "
          << endl << " phase set equal to 1" << endl;
      }
      if (jj>allphases)
      {
        jj=allphases;
      }
      if (jj<=0)
      {
        jj=1;
      }
      initial_params::current_phase = jj;
      cout << "Set current phase to " << jj << endl;
    }
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-lapqd"))>-1)
    {
      ADqd_flag=1;
    }

    tracing_message(traceflag,"A2");
    while (initial_params::current_phase <= allphases)
    {
      between_phases_calculations();

      if (random_effects_flag)
        initial_params::set_inactive_random_effects();

      // get the number of active parameters
      int nvar=initial_params::nvarcalc();
      if (nvar < 1)
      {
        cerr << "Error -- no active parameters. There must be at least 1"
             << endl;
        exit(1);
      }
      dvector g(1,nvar);
      independent_variables x(1,nvar);
      tracing_message(traceflag,"B2");
      initial_params::xinit(x);    // get the initial values into the

      ///\todo What does the -uhess option do?
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-uhess"))>-1)
      {
        int ierr=0;
        ifstream ifs("vector");
        if (!ifs)
        {
          cerr << "couldn't open file vector" << endl;
          ierr=1;
        }
        dvector zz(1,x.indexmax());
        if(ierr==0)
        {
          ifs >> zz;
          if (!ifs)
          {
            cerr << "couldn't read vector" << endl;
            ierr=1;
          }
        }
        if (ierr==0)
        {
          dvector xsave(1,x.indexmax());
          for (;;)
          {
            double delta=0;
            cout << "enter delta" << endl;
            cin >> delta;
            xsave=x;
            x+=delta*zz;
            initial_params::reset(x);    // get the initial values into the
            userfunction();
            x=xsave;
          }
        }
      }

      double f=0.0;

      int simpflag = -1;
      if ( (simpflag=option_match(ad_comm::argc,ad_comm::argv,"-simplex"))>-1)
      {
        gradient_structure::set_NO_DERIVATIVES();
        double delta=1.e-4;
        double ftol=1.e-16;
        dmatrix p(1,nvar+1,1,nvar);
        dvector y(1,nvar+1);
        set_initial_simplex(p,y,nvar,x,delta);
        adamoeba(p,y,nvar,ftol,maxfn);
        double ymin=min(y);
        for (int i=1;i<=nvar+1;i++)
        if (ymin==y(i))
        {
          x=p(i);
          break;
        }
        cerr << "The -simplex option is deprecated. The user should port "
             << "to the -neldmead option." << endl;
      }
      if ( (simpflag=option_match(ad_comm::argc,ad_comm::argv,"-neldmead"))>-1)
      {
        gradient_structure::set_NO_DERIVATIVES();
        double delta=1.e-4;
        double ftol=1.e-16;
        dvector mincords = x;
        double ynewlo;
        double* pynewlo = &ynewlo;
        int icount, numres, ifault;
        int* picount = &icount;
        int* pnumres = &numres;
        int* pifault = &ifault;
        neldmead(nvar,mincords,mincords,pynewlo,ftol,delta,picount,pnumres,
          pifault);
        x = mincords;
      }
      int lmnflag = -1;
      int lmnsteps=10;
      if ( (lmnflag=option_match(ad_comm::argc,ad_comm::argv,"-lmn",nopt))>-1)
      {
        if (random_effects_flag)
        {
          cerr << "At present you can not use the -lmn option for the outer"
               << endl << " optimiation in a random-effects model" << endl;
          ad_exit(1);
        }
        if (!nopt)
        {
          cerr << "Usage -lmn option needs integer  -- set to default 10.\n";
        }
        else
        {
          int jj=atoi(ad_comm::argv[lmnflag+1]);
          if (jj<=0)
          {
            cerr << "Usage -lmn option needs positive integer"
                    " -- set to default 10.\n";
          }
          else
          {
            lmnsteps=jj;
          }
        }
      }
      if (lmnflag==-1)
      {
        // *********************************************************
        // block for quasi newton minimization
        if (negative_eigenvalue_flag)
        {
          trust_region_update(nvar,_crit,x,g,f);
        }
#if defined(USE_ADPVM)
        if (ad_comm::pvm_manager)
        {
          if (random_effects_flag)
          {
            if (maxfn>0)
            {
              switch (ad_comm::pvm_manager->mode)
              {
              case 1: // master
                quasi_newton_block_pvm_master_random_effects(nvar,_crit,x,g,f);
                break;
              case 2: // slave
              // these don't exist yet
                function_evaluation_block_pvm_slave_random_effects
                  (nvar,_crit,x,g,f);
                break;
              default:
                cerr << "error illega value for pvm_manager->mode" << endl;
                exit(1);
              }
            }
          }
          else
          {
            if (maxfn>0)
            {
              switch (ad_comm::pvm_manager->mode)
              {
              case 1: // master
                quasi_newton_block_pvm_master(nvar,_crit,x,g,f);
                break;
              case 2: // slave
                function_evaluation_block_pvm_slave();
                break;
              default:
                cerr << "error illega value for pvm_manager->mode" << endl;
                exit(1);
              }
            }
          }
        }
        else
#endif
        {
          do
          {
            if (spminflag)
            {
              repeatminflag=1;
              spminflag=0;
            }
            else
            {
              repeatminflag=0;
            }
            if (maxfn>0)
            {
              int nsteps=5;
              lmnflag = option_match(ad_comm::argc,ad_comm::argv,
                                     "-lmn2", nopt);
              if (lmnflag > -1)
              {
                if (!nopt)
                {
                  cerr << "Usage -lmn option needs integer"
                     "  -- set to default 5" << endl;
                }
                else
                {
                  int jj=atoi(ad_comm::argv[lmnflag+1]);
                  if (jj<=0)
                  {
                    cerr << "Usage -lmn option needs positive integer "
                     " -- set to default 5" << endl;
                  }
                  else
                  {
                    nsteps=jj;
                  }
                }
              }
              if (lmnflag<0)
              {
                quasi_newton_block(nvar,_crit,x,g,f);
              }
              else
              {
                limited_memory_quasi_newton_block(nvar,_crit,x,g,f,nsteps);
              }
            }
          }
          while(repeatminflag);
        }
      } // end block for quasi newton minimization
      else
      {  // block for limited memory quasi newton minimization
        if (maxfn>0)
        {
          function_minimizer::limited_memory_quasi_newton(x,lmnsteps);
        }
      }
      // end block for limited memory quasi newton minimization
      // *********************************************************
      tracing_message(traceflag,"M2");

      gradient_structure::set_NO_DERIVATIVES();
      initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun=0.0;
      if (!random_effects_flag || !lapprox)
      {
#if defined(USE_ADPVM)
        if (ad_comm::pvm_manager)
        {
          switch (ad_comm::pvm_manager->mode)
          {
          case 1:
            pvm_master_function_evaluation_no_derivatives(f,x,nvar);
            *objective_function_value::pobjfun=f;
            break;
          case 2:
            pvm_slave_function_evaluation_no_derivatives();
            break;
          default:
            cerr << "Illegal value for ad_comm::pvm_manager->mode" << endl;
            ad_exit(1);
          }
        }
        else
        {
#endif  //#if defined(USE_ADPVM)
          userfunction();
#if defined(USE_ADPVM)
        }
#endif  //#if defined(USE_ADPVM)
      }
      else
      {
        (*lapprox)(x,f,this);
        *objective_function_value::pobjfun=f;
        initial_params::set_inactive_only_random_effects();
        print_is_diagnostics(lapprox);
      }
      initial_params::save();
      report(g);
      // in case the user changes some initial_params in the report section
      // call reset again
      initial_params::reset(dvar_vector(x));
      report_function_minimizer_stats();
      if (quit_flag=='Q') break;
      if (!quit_flag || quit_flag == 'N')
      {
        initial_params::current_phase++;
      }
    }
    if (initial_params::current_phase >
      initial_params::max_number_phases)
    {
      initial_params::current_phase =
        initial_params::max_number_phases;
    }
    tracing_message(traceflag,"N2");
  }
  void function_minimizer::set_multinomial_weights(dvector& d)
  {
    multinomial_weights=new dvector(d);
  }

function_minimizer::function_minimizer(long int sz):
  mcmc2_flag(-1),
  robust_hybrid_flag(0),
  ffbest(0),
  ifn(0)
  {
    lapprox=0;
    multinomial_weights=0;
    //cout << lapprox << endl;
    maxfn  = 1000;
    iprint = 1;
    crit   = 0.0001;
    imax   = 30;
    dfn    = 0.01;
    iexit  = 0;
    ihflag = 0;
    ihang  = 0;
    scroll_flag = 1;
    maxfn_flag=0;
    quit_flag=0;
    min_improve=.0;
    negdirections=0;
    spminflag=0;
    repeatminflag=0;

    int ssz;

    int nopt=get_option_number("-ams",
      "-ams option needs positive integer -- ignored",ssz);
    if (nopt>-1 && ssz>0) {
      sz=ssz;
    }

#ifdef __BORLANDC__
    long int lssz;
#else
    long long int lssz;
#endif
    nopt=get_option_number("-cbs",
      "-cbs option needs positive integer -- ignored",lssz);
    if (nopt>-1 && lssz>0) {
      const size_t size = (size_t)lssz;
      gradient_structure::set_CMPDIF_BUFFER_SIZE(size);
    }

    nopt=get_option_number("-gbs",
      "-gbs option needs positive integer -- ignored",lssz);
    if (nopt>-1 && lssz>0) {
      const size_t size = (size_t)lssz / sizeof(grad_stack_entry);
      gradient_structure::set_GRADSTACK_BUFFER_SIZE(size);
    }

    if (!sz)
    {
      pgs = new gradient_structure;
    }
    else
    {
      pgs = new gradient_structure(sz);
    }
  }

/**
Destructor
*/
function_minimizer::~function_minimizer()
{
  if (multinomial_weights)
  {
    delete multinomial_weights;
    multinomial_weights = 0;
  }
  if (lapprox)
  {
    delete lapprox;
    lapprox = 0;
  }
  delete pgs;
  pgs = 0;
  if (negdirections)
  {
    delete negdirections;
    negdirections = 0;
  }
}

void function_minimizer::set_initial_simplex(const dmatrix& _p,
  const dvector& _y, int nvar, const dvector& x, double delta)
  {
    dvector& y=(dvector&) _y;
    dmatrix& p=(dmatrix&) _p;
    int i;
    p(1)=x;
    for (i=2;i<=nvar+1;i++)
    {
      p(i)=x;
      p(i,i-1)+=delta;
    }
    dvector xx(1,nvar);
    double vf=0;
    for (i=1;i<=nvar+1;i++)
    {
      xx=p(i);
      vf=value(initial_params::reset(dvar_vector(xx)));
      *objective_function_value::pobjfun=0.0;
      userfunction();
      vf+=value(*objective_function_value::pobjfun);
      y(i)=vf;
    }
  }

int get_option_number(const char * option_name,const char * error_message,
  int& option_value)
{
  int on1;
  int nopt = 0;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,option_name,nopt))>-1)
  {
    if (!nopt)
    {
      if (ad_printf)
        (*ad_printf)("%s\n",error_message);
      else
        cerr << error_message << endl;
      on1=-1;
    }
    else
    {
      option_value=atoi(ad_comm::argv[on1+1]);
    }
  }
  return on1;
}

int get_option_number(const char * option_name,const char * error_message,
#ifdef __BORLANDC__
  long int& option_value)
#else
  long long int& option_value)
#endif
{
  int on1;
  int nopt = 0;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,option_name,nopt))>-1)
  {
    if (!nopt)
    {
      if (ad_printf)
        (*ad_printf)("%s\n",error_message);
      else
        cerr << error_message << endl;
      on1=-1;
    }
    else
    {
#if defined(__BORLANDC__) || defined(_MSC_VER)
      option_value=atol(ad_comm::argv[on1+1]);
#else
      option_value=atoll(ad_comm::argv[on1+1]);
#endif
    }
  }
  return on1;
}


void function_minimizer::other_separable_stuff_begin(void)
{
  if (lapprox)
  {
    lapprox->separable_calls_counter++;
    /*
    lapprox->separable_call_level++;
    //lapprox->build_up_nested_shape();
    lapprox->nested_separable_calls_counter
      (lapprox->separable_call_level)++;
    //clean(lapprox->nested_tree_position,lapprox->separable_call_level);
    lapprox->nested_tree_position(lapprox->separable_call_level)++;
    */
  }
}

void function_minimizer::other_separable_stuff_end(void)
{
  /*
  if (lapprox)
  {
    lapprox->build_up_nested_shape();
    clean(lapprox->nested_tree_position,lapprox->separable_call_level);
    lapprox->separable_call_level--;
  }
  */
}


void function_minimizer::begin_gauss_hermite_stuff(void)
{
  int nsc=lapprox->separable_calls_counter;
  int is=0;
  if (lapprox->gh->mi==0)
  {
    is=lapprox->gh->is;
  }
  else
  {
    is=lapprox->gh->mi->get_offset()+1;
  }
  lapprox->gh->gauss_hermite_values(nsc,is)=
    *objective_function_value::pobjfun;
}

void function_minimizer::start_get_importance_sampling_comnponent(void)
{
  int nsc=lapprox->separable_calls_counter;
  int isc=lapprox->importance_sampling_counter;
  (*lapprox->importance_sampling_components)(nsc,isc)=
     *objective_function_value::pobjfun;
}

void function_minimizer::end_get_importance_sampling_comnponent(void)
{
  int nsc=lapprox->separable_calls_counter;
  int is=lapprox->importance_sampling_counter;
  if (lapprox->saddlepointflag==2)
  {
    (*lapprox->importance_sampling_components)(nsc,is)=
       (-1)* *objective_function_value::pobjfun-
       (*lapprox->importance_sampling_components)(nsc,is);
  }
  else
  {
    (*lapprox->importance_sampling_components)(nsc,is)=
       *objective_function_value::pobjfun-
       (*lapprox->importance_sampling_components)(nsc,is);
  }
}

void function_minimizer::begin_funnel_stuff(void)
{
  lapprox->separable_calls_counter++;
  if (lapprox->hesstype==2)
  {
    if (lapprox->in_gauss_hermite_phase)
    {
       begin_gauss_hermite_stuff();
    }
    else if (lapprox->num_importance_samples &&
      lapprox->importance_sampling_components)
    {
      if (lapprox->block_diagonal_flag==2)
      {
        start_get_importance_sampling_comnponent();
      }
    }
  }
}

void function_minimizer::get_function_difference(void)
{
  int nsc=lapprox->separable_calls_counter;
  (*(lapprox->separable_function_difference))(nsc)=
    value(*objective_function_value::pobjfun);
    value(*objective_function_value::pobjfun)=0.0;
}
void function_minimizer::end_df1b2_funnel_stuff(void)
{
  if (lapprox->in_gauss_hermite_phase)
  {
    end_gauss_hermite_stuff();
  }
  else
  {
    if (lapprox->hesstype==2)
    {
      if (lapprox->num_importance_samples &&
        lapprox->importance_sampling_components)
      {
        if (lapprox->block_diagonal_flag==2)
        {
          end_get_importance_sampling_comnponent();
        }
      }
      if (!lapprox->no_function_component_flag)
      {
        if (lapprox->saddlepointflag!=2)
        {
          get_function_difference();
        }
        else if (inner_opt()!=0)
        {
          get_function_difference();
        }
      }
    }
  }
}

void function_minimizer::end_gauss_hermite_stuff(void)
{
  int nsc=lapprox->separable_calls_counter;
  int is=0;
  if (lapprox->gh->mi==0)
  {
    is=lapprox->gh->is;
  }
  else
  {
    is=lapprox->gh->mi->get_offset()+1;
  }
  lapprox->gh->gauss_hermite_values(nsc,is)=
    *objective_function_value::pobjfun-
    lapprox->gh->gauss_hermite_values(nsc,is);
}

void print_is_diagnostics(laplace_approximation_calculator *lapprox)
{
  if (lapprox->is_diagnostics_flag)
  {
    if (lapprox->importance_sampling_values)
    {
      int mmin=lapprox->importance_sampling_values->indexmin();
      int mmax=lapprox->importance_sampling_values->indexmax();
      double mn= mean(*lapprox->importance_sampling_values);
      dmatrix tmp(1,2,mmin,mmax);
      tmp(2)=*lapprox->importance_sampling_values-mn;
      tmp(1).fill_seqadd(1,1);
      tmp=trans(sort(trans(tmp),2));
      ofstream ofs("is_diagnostics");
      ofs << "number of importance samples "
          << lapprox->num_importance_samples << endl;
      ofs << "importance_sampling_values" << endl;
      ofs << *lapprox->importance_sampling_values << endl<< endl;;
      ofs << "normalized importance_sampling_values" << endl;
      ofs << *lapprox->importance_sampling_values-mn << endl<< endl;;
      ofs << "sorted normalized importance_sampling_values" << endl;
      ofs << setw(9) << tmp << endl<< endl;;
      ofs << "epsilon(1).indexmax()  "
          << lapprox->epsilon(1).indexmax() << endl;
      ofs << lapprox->epsilon << endl;
      dmatrix plotstuff(1,2,mmin,mmax);
      plotstuff(1)=*lapprox->importance_sampling_weights;
      plotstuff(2)=*lapprox->importance_sampling_values-mn;
      ofs << " weight   value " << endl;
      ofs << setw(9) << sort(trans(plotstuff),2) << endl;
    }
  }
}
