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
#include <sstream>
using std::istringstream;
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif
        int fcount =0;
static int no_stuff=0;
static int write_sparse_flag=0;
    static void trapper(void)
    {
      //int x=5;
    }
int noboundepen_flag=1;
unsigned int global_nvar=0;

double CHECK_HESSIAN_PENALTY=0.0;

double evaluate_function(const dvector& x,function_minimizer * pfmin);
void get_newton_raphson_info(int xs,int us,const init_df1b2vector _y,
  dmatrix& Hess, dvector& grad,
  df1b2_gradlist* f1b2gradlist,function_minimizer * pfmin);

//dvariable AD_uf_inner(const dvector& x,const dvar_vector& u);
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator* lap);

  double re_objective_function_value::fun_without_pen=0;

int laplace_approximation_calculator::antiflag=0;
int laplace_approximation_calculator::alternative_user_function_flag=0;
int laplace_approximation_calculator::saddlepointflag=0;
int laplace_approximation_calculator::print_importance_sampling_weights_flag=0;
int laplace_approximation_calculator::sparse_hessian_flag=0;

int laplace_approximation_calculator::where_are_we_flag=0;
dvar_vector *
  laplace_approximation_calculator::variance_components_vector=0;

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_uhat_quasi_newton
  (const dvector& x,function_minimizer * pfmin)
{
  //int on,nopt;
  pfmin->inner_opt_flag=1;
  double f=0.0;
  double fb=1.e+100;
  dvector g(1,usize);
  dvector ub(1,usize);
  independent_variables u(1,usize);
  gradcalc(0,g);
  fmc1.itn=0;
  fmc1.ifn=0;
  fmc1.ireturn=0;
  initial_params::xinit(u);    // get the initial values into the
  initial_params::xinit(ubest);    // get the initial values into the
  fmc1.ialph=0;
  fmc1.ihang=0;
  fmc1.ihflag=0;
  fmc1.use_control_c=0;

  if (init_switch)
  {
    u.initialize();
  }
  else
  {
    u=ubest;
  }

  fmc1.dfn=1.e-2;
  dvariable pen=0.0;
  //cout << "starting  norm(u) = " << norm(u) << endl;
  while (fmc1.ireturn>=0)
  {
   /*
    double nu=norm(value(u));
    if (nu>400)
    {
      cout << "U norm(u) = " << nu  << endl;
    }
    cout << "V norm(u) = " << nu
         << " f = " << f  << endl;
    */
    fmc1.fmin(f,u,g);
    //cout << "W norm(u) = " << norm(value(u)) << endl;
    if (fmc1.ireturn>0)
    {
      dvariable vf=0.0;
      pen=initial_params::reset(dvar_vector(u));
      *objective_function_value::pobjfun=0.0;
      pfmin->AD_uf_inner();
      if (saddlepointflag)
      {
        *objective_function_value::pobjfun*=-1.0;
      }
      if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
      {
        quadratic_prior::get_M_calculations();
      }
      vf+=*objective_function_value::pobjfun;

     /*  this is now done in the operator = function
      if (quadratic_prior::get_num_quadratic_prior()>0)
      {
        vf+= quadratic_prior::get_quadratic_priors();
      }
      */

      objective_function_value::fun_without_pen=value(vf);

      //cout << " pen = " << pen << endl;
      if (noboundepen_flag==0)
      {
        vf+=pen;
      }
      f=value(vf);
      if (f<fb)
      {
        fb=f;
        ub=u;
      }
      gradcalc(usize,g);
      //cout << " f = " << setprecision(17) << f << " " << norm(g)
       // << " " << norm(u) << endl;
    }
    u=ub;
  }
  cout <<  " inner maxg = " <<  fmc1.gmax;
  if (fabs(fmc1.gmax)>1.e+3)
    trapper();

  if (fabs(fmc1.gmax)>1.e-4)
  {
    fmc1.itn=0;
    //fmc1.crit=1.e-9;
    fmc1.ifn=0;
    fmc1.ireturn=0;
    fmc1.ihang=0;
    fmc1.ihflag=0;
    fmc1.ialph=0;
    initial_params::xinit(u);    // get the initial values into the
    //u.initialize();
    while (fmc1.ireturn>=0)
    {
      fmc1.fmin(f,u,g);
      if (fmc1.ireturn>0)
      {
        dvariable vf=0.0;
        pen=initial_params::reset(dvar_vector(u));
        *objective_function_value::pobjfun=0.0;
        pfmin->AD_uf_inner();
        if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
        {
          quadratic_prior::get_M_calculations();
        }
        vf+=*objective_function_value::pobjfun;
        objective_function_value::fun_without_pen=value(vf);

        vf+=pen;
        f=value(vf);
        if (f<fb)
        {
          fb=f;
          ub=u;
        }
        gradcalc(usize,g);
        //cout << " f = " << setprecision(15) << f << " " << norm(g) << endl;
      }
    }
    u=ub;
    cout <<  "  Inner second time = " << fmc1.gmax;
  }
  cout << "  Inner f = " << fb << endl;
  fmc1.ireturn=0;
  fmc1.fbest=fb;
  gradient_structure::set_NO_DERIVATIVES();
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  gradient_structure::set_YES_DERIVATIVES();
  pfmin->inner_opt_flag=0;
  return u;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_uhat_lm_newton
  (const dvector& x,function_minimizer * pfmin)
{
  double f=0.0;
  //dvector g(1,usize);
  //g.initialize();
  independent_variables u(1,usize);
  if (init_switch)
  {
    initial_params::xinit(u);    // get the initial values into the
  }
  else
  {
    u=ubest;
  }

  int iprint_save=pfmin->iprint;
  pfmin->iprint=inner_iprint;
  pfmin->limited_memory_quasi_newton(f,u,5,1,inner_maxfn,inner_crit);
  pfmin->iprint=iprint_save;
  if (initial_params::mc_phase==0)
  {
    cout << "  Inner f = " << f << endl;
  }
  //gradient_structure::set_NO_DERIVATIVES();
  //initial_params::set_inactive_only_random_effects();
  //initial_params::reset(dvar_vector(x));
  return u;
}

/**
 * Description not yet available.
 * \param
 */
void set_partition_sizes(int & num_der_blocks,ivector& minder,
  ivector& maxder,int nvariables)
{
  if (num_der_blocks==0)
  {
    num_der_blocks=1;
  }
#if defined(USE_ADPVM)
  if (ad_comm::pvm_manager)
  {
    switch (ad_comm::pvm_manager->mode)
    {
    case 1: //master
      {
        int i;
        int ndb=ad_comm::pvm_manager->num_slave_processes+1;

        minder.allocate(1,ndb);
        maxder.allocate(1,ndb);

        int nd=nvariables/ndb;
        int r= nvariables - nd * ndb;
        ivector partition(1,ndb);
        partition=nd;
        partition(1,r)+=1;
        minder(1)=1;
        maxder(1)=partition(1);

        for (i=2;i<=ndb;i++)
        {
          minder(i)=maxder(i-1)+1;
          maxder(i)=minder(i)+partition(i)-1;
        }
        send_int_to_slaves(minder(2,ndb));
        send_int_to_slaves(maxder(2,ndb));
        break;
      }

    case 2: //slave
      minder.allocate(1,1);
      maxder.allocate(1,1);
      minder(1)=get_int_from_master();
      maxder(1)=get_int_from_master();
      break;
    }
  }
  else
#endif // #USE_ADPVM
  {
    minder.allocate(1,num_der_blocks);
    maxder.allocate(1,num_der_blocks);

    int nd=nvariables/num_der_blocks;
    int r= nvariables - nd * num_der_blocks;
    ivector partition(1,num_der_blocks);
    partition=nd;
    partition(1,r)+=1;

    minder(1)=1;
    maxder(1)=partition(1);
    for (int i=2;i<=num_der_blocks;i++)
    {
      minder(i)=maxder(i-1)+1;
      maxder(i)=minder(i)+partition(i)-1;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
laplace_approximation_calculator::laplace_approximation_calculator
(
  int _xsize,
  int _usize,
  int _minder,
  int _maxder,
  function_minimizer* _pmin
):
  init_switch(1),
  separable_call_level(0),
  triplet_information(0),
  compressed_triplet_information(0),
  nested_separable_calls_counter(1,10),
  nested_tree_position(1,5),
  local_dtemp(1,_xsize),
  nr_debug(0),
  pmin(_pmin),
  block_diagonal_flag(0),
  xsize(_xsize),
  usize(_usize),
  bHess_pd_flag(0),
  sparse_triplet(0),
  sparse_iterator(0),
  sparse_count(0),
  sparse_count_adjoint(0),
  sparse_triplet2(0),
  vsparse_triplet(0),
  vsparse_triplet_adjoint(0),
  sparse_symbolic(0),
  sparse_symbolic2(0),
  fmc1(usize,1),
  fmc(_xsize),
  xadjoint(1,_xsize),
  check_local_uadjoint(1,_usize),
  check_local_uadjoint2(1,_usize),
  check_local_xadjoint(1,_xsize),
  check_local_xadjoint2(1,_xsize),
  uadjoint(1,_usize),
  uhat(1,_usize),
  ubest(1,_usize)
{
  ubest.initialize();
  nested_shape.allocate(100,100,10);
  nested_shape.initialize();
  nested_tree_position.initialize();
  nested_separable_calls_counter.initialize();
  calling_set=0;
  antiepsilon=0;
  dd_nr_flag=0;
  no_re_ders_flag =0;
  importance_sampling_components=0;
  is_diagnostics_flag=0;
  importance_sampling_values = 0;
  importance_sampling_weights = 0;
  no_function_component_flag=0;
  uhat.initialize();
  hesstype=1;
  use_gauss_hermite=0;
  in_gauss_hermite_phase=0;
  multi_random_effects=0;
  //var_flag=1;
  var_flag=0;
  num_separable_calls=0;
  separable_calls_counter=0;
  importance_sampling_counter=0;
  num_local_re_array=0;
  num_local_fixed_array=0;
  isfunnel_flag=0;
  antiflag=0;
  rseed=3457;
  nfunnelblocks=0;
  separable_function_difference=0;
  gh=0;
  block_diagonal_hessian=0;
  block_diagonal_Dux=0;
  block_diagonal_re_list=0;
  block_diagonal_fe_list=0;
  block_diagonal_vhessian=0;
  block_diagonal_vhessianadjoint=0;
  block_diagonal_ch=0;
  block_diagonal_vch=0;
  have_users_hesstype=0;
  pHess_non_quadprior_part=0;
  bw=0;
  bHess=0;
  grad_x_u=0;
  grad_x=0;
  int ndi=20000;
  int nopt=0;
  int on=-1;
  if ( (inner_lmnflag=option_match(ad_comm::argc,ad_comm::argv,"-ndi",nopt))
    >-1)
  {
    if (!nopt)
    {
      cerr << "Usage -ndi option needs integer  -- set to default 20000.\n";
    }
    else
    {
      int jj=atoi(ad_comm::argv[inner_lmnflag+1]);
      if (jj<=0)
      {
        cerr << "Usage -ndi option needs positive integer"
        "  -- set to defalt 20000" << endl;
      }
      else
      {
        ndi=jj;
      }
    }
  }
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-noreders",nopt))>-1)
  {
    no_re_ders_flag=1;
  }
  derindex=new imatrix(1,ndi);
  bHessadjoint=0;
  if (initial_df1b2params::separable_flag)
  {
    if (initial_df1b2params::pointer_table)
    {
      delete initial_df1b2params::pointer_table;
    }
    initial_df1b2params::pointer_table=0;
  }
  inner_lmnflag=0;
  inner_lmnsteps=10;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-noinit",nopt))>-1)
  {
    init_switch=0;
  }
  if ( (inner_lmnflag=option_match(ad_comm::argc,ad_comm::argv,"-ilmn",nopt))
    >-1)
  {
    if (!nopt)
    {
      cerr << "Usage -ilmn option needs integer  -- set to default 10" << endl;
    }
    else
    {
      int jj=atoi(ad_comm::argv[inner_lmnflag+1]);
      if (jj<=0)
      {
        cerr << "Usage -ilmn option needs positive integer"
          "  -- set to defalt 10" << endl;
      }
      else
      {
        inner_lmnsteps=jj;
      }
    }
  }
  else
  {
    inner_lmnflag=0;
  }
  inner_noprintx=0;

  num_der_blocks=1; // default value
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-ndb",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -ndb option needs non-negative integer  -- ignored.\n";
    }
    else
    {
      int _num_der_blocks=atoi(ad_comm::argv[on+1]);
      if (_num_der_blocks<=0)
      {
        cerr << "Usage -ndb option needs positive integer  -- ignored" << endl;
      }
      else
      {
        num_der_blocks=_num_der_blocks;
      }
    }
  }

  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-isf",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -isf option needs non-negative integer  -- ignored.\n";
    }
    else
    {
      int _nfunnelblocks=atoi(ad_comm::argv[on+1]);
      if (_nfunnelblocks<=0)
      {
        cerr << "Usage -isf option needs positive integer  -- ignored" << endl;
      }
      else
      {
        nfunnelblocks=_nfunnelblocks;
        isfunnel_flag=1;
      }
    }
  }

  antiflag=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-anti",nopt))>-1)
  {
    antiflag=1;
  }

  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nrdbg",nopt))>-1)
  {
    nr_debug=1;
  }

  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-ddnr",nopt))>-1)
  {
    dd_nr_flag=1;
  }

  nvariables=xsize+usize;
  /*
  int rem=0;
  if (nvariables%xsize!=0)
    rem=1;
  */

  if (nvariables/num_der_blocks<xsize)
  {
    cerr << " Error -- the number of der blocks (-ndb) can not be larger than "
         << nvariables/xsize << endl;
    ad_exit(1);
  }

  set_partition_sizes(num_der_blocks,minder,maxder,nvariables);

 // !!! remove
  //maxder(1)=5;

  fmc1.crit=1.e-3;

  //cout << "Need to fix Hess" << endl;
  for (int i=1;i<=num_der_blocks;i++)
  {
    if (minder(i)<1 || maxder(i) > nvariables || maxder(i) < minder(i))
    {
      cerr << " minder or maxder value out of bounds in"
        "laplace_approximation_calculator constructor "
       << endl << " values are minder = " << minder
       << " maxder = " << maxder << endl;
      ad_exit(1);
    }
  }

  num_nr_iters=2;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nr",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -nr option needs non-negative integer  -- ignored" << endl;
    }
    else
    {
      int _num_nr_iters=atoi(ad_comm::argv[on+1]);
      if (_num_nr_iters<0)
      {
        cerr << "Usage -nr option needs non-negative integer  -- ignored.\n";
      }
      else
      {
        num_nr_iters=_num_nr_iters;
      }
    }
  }

  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nochol",nopt))>-1)
  {
    ad_comm::no_ln_det_choleski_flag=1;
  }

  ad_comm::print_hess_and_exit_flag=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-phe",nopt))>-1)
  {
    ad_comm::print_hess_and_exit_flag=1;
  }

  double _nr_crit=1.e-11;
  nr_crit=1.e-11;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nrcrit",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -nrcrit option needs number  -- ignored" << endl;
    }
    else
    {
      istringstream ist(ad_comm::argv[on+1]);
      ist >> _nr_crit;

      if (_nr_crit<=0)
      {
        cerr << "Usage -nrcrit option needs positive number  -- ignored.\n";
        _nr_crit=0.0;
      }
    }
    if (_nr_crit>0)
    {
      nr_crit=_nr_crit;
    }
  }
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-gh",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -gh option needs positive integer  -- ignored" << endl;
    }
    else
    {
      int _inner_gh=atoi(ad_comm::argv[on+1]);
      if (_inner_gh<=0)
      {
        cerr << "Usage -gh option needs positive integer  -- ignored" << endl;
      }
      else
      {
        use_gauss_hermite=_inner_gh;
      }
    }
  }

  inner_crit=1.e-3;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-icrit",nopt))>-1)
  {
    double _inner_crit=0.0;;
    if (!nopt)
    {
      cerr << "Usage -icrit option needs number  -- ignored" << endl;
    }
    else
    {
      istringstream ist(ad_comm::argv[on+1]);
      ist >> _inner_crit;

      if (_inner_crit<=0)
      {
        cerr << "Usage -icrit option needs positive number  -- ignored" << endl;
        _inner_crit=0.0;
      }
    }
    if (_inner_crit>0)
    {
      inner_crit=_inner_crit;
    }
  }
  fmc1.crit=inner_crit;

  fmc.dfn=.01;

  inner_iprint=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-iiprint",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -iprint option needs non-negative integer  -- ignored.\n";
    }
    else
    {
      int _inner_iprint=atoi(ad_comm::argv[on+1]);
      if (_inner_iprint<=0)
      {
        cerr << "Usage -iip option needs non-negative integer  -- ignored.\n";
      }
      else
      {
        inner_iprint=_inner_iprint;
      }
    }
  }
  fmc1.iprint=inner_iprint;

  inner_maxfn=1000;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-imaxfn",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -maxfn option needs non-negative integer  -- ignored.\n";
    }
    else
    {
      int _inner_maxfn=atoi(ad_comm::argv[on+1]);
      if (_inner_maxfn<0)
      {
        cerr << "Usage -iip option needs non-negative integer  -- ignored.\n";
      }
      else
      {
        inner_maxfn=_inner_maxfn;
      }
    }
  }
  fmc1.maxfn=inner_maxfn;
  // what sort of structure on the Hessian do we have
  nopt=0;

  rseed=3456;
  num_importance_samples=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-is",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -is option needs positive integer  -- ignored" << endl;
    }
    else
    {
      int tht=atoi(ad_comm::argv[on+1]);
      if (tht<=0)
      {
        cerr << "Usage -is option needs non-negative integer  -- ignored.\n";
      }
      else
      {
        num_importance_samples=tht;
      }
      if (nopt==2)
      {
        int rseed1=atoi(ad_comm::argv[on+2]);
        if (rseed1<=0)
        {
          cerr << "Usage -is option needs non-negative integer  -- ignored.\n";
        }
        else
        {
          rseed=rseed1;
        }
      }
    }
  }
  int use_balanced=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-isb",nopt))>-1)
  {
    use_balanced=1;
    if (!nopt)
    {
      cerr << "Usage -isb option needs positive integer  -- ignored" << endl;
    }
    else
    {
      int tht=atoi(ad_comm::argv[on+1]);
      if (tht<=0)
      {
        cerr << "Usage -isb option needs non-negative integer  -- ignored.\n";
      }
      else
      {
        num_importance_samples=2*tht;
      }
      if (nopt==2)
      {
        int rseed1=atoi(ad_comm::argv[on+2]);
        if (rseed1<=0)
        {
          cerr << "Usage -isb option needs non-negative integer  -- ignored.\n";
        }
        else
        {
          rseed=rseed1;
        }
      }
    }
  }
  use_outliers=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-iso",nopt))>-1)
  {
    use_outliers=1;
  }
  if (num_importance_samples)
  {
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-isdiag",nopt))>-1)
    {
      is_diagnostics_flag=1;
    }
    if (importance_sampling_values)
    {
      delete importance_sampling_values;
      importance_sampling_values=0;
    }
    importance_sampling_values =
      new dvector(1,num_importance_samples);

    if (importance_sampling_weights)
    {
      delete importance_sampling_weights;
      importance_sampling_weights=0;
    }
    importance_sampling_weights =
      new dvector(1,num_importance_samples);

    random_number_generator rng(rseed);
    if (allocated(epsilon)) epsilon.deallocate();
    if (use_balanced)
    {
      // check for eveb num_importance samples
      if (num_importance_samples%2)
        num_importance_samples+=1;
    }
    epsilon.allocate(1,num_importance_samples,1,usize);
    if (use_balanced)
    {
      int n2=num_importance_samples/2;
      epsilon.sub(1,n2).fill_randn(rng);
      if (use_outliers)
      {
        dmatrix os(1,num_importance_samples,1,usize);
        os.fill_randu(rng);
        for (int i=1;i<=num_importance_samples;i++)
        {
          for (int j=1;j<=usize;j++)
          {
            if (os(i,j)<0.05) epsilon(i,j)*=3.0;
          }
        }
      }
      for (int i=1;i<=n2;i++)
      {
        epsilon(i+n2)=-epsilon(i);
      }
    }
    else
    {
      epsilon.fill_randn(rng);
      if (use_outliers)
      {
        dmatrix os(1,num_importance_samples,1,usize);
        os.fill_randu(rng);
        for (int i=1;i<=num_importance_samples;i++)
        {
          for (int j=1;j<=usize;j++)
          {
            if (os(i,j)<0.05) epsilon(i,j)*=3.0;
          }
        }
      }
    }

    double eps_mult=1.0;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-epsmult",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -epsmult option needs number  -- ignored" << endl;
      }
      else
      {
        istringstream ist(ad_comm::argv[on+1]);
        ist >> eps_mult;

        if (eps_mult<=0.0 || eps_mult>1.0)
        {
          cerr << "Usage -epsmult option needs positive number between 0 and 1 "
              "-- ignored" << endl;
          eps_mult=1.0;
        }
      }
      for (int i=1;i<=num_importance_samples;i++)
      {
        epsilon(i)*=eps_mult;
      }
    }
  }

  nopt=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-ht",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -ht option needs positive integer  -- ignored" << endl;
      set_default_hessian_type();
    }
    else
    {
      int tht=atoi(ad_comm::argv[on+1]);
      if (tht<=0)
      {
        cerr << "Usage -ht option needs non-negative integer  -- ignored.\n";
        set_default_hessian_type();
      }
      else
      {
        have_users_hesstype=1;
        hesstype=tht;
      }
      if (nopt>=2)
      {
        int tbw=atoi(ad_comm::argv[on+2]);
        if (tbw<=0)
        {
          cerr << "Usage -ht option needs non-negative bandwidth"
             "  -- ignored" << endl;
        }
        else
        {
          ad_comm::bandwidth=tbw;
        }
      }
    }
  }
  else
  {
    set_default_hessian_type();
  }

  // !! need to check nvar calculation
#ifndef OPT_LIB
  assert(maxder(1) >= minder(1));
#endif
  nvar = (unsigned int)(maxder(1) - minder(1) + 1);

  switch (hesstype)
  {
  case 0:
  case 1:
  case 4:
    grad.allocate(1,usize);
    Hess.allocate(1,usize,1,usize);
    Hessadjoint.allocate(1,usize,1,usize);
    Dux.allocate(1,usize,1,xsize);
    break;
  case 3:
    {
      int bw=2;
      if (ad_comm::bandwidth) bw=ad_comm::bandwidth;
      bHess=new banded_symmetric_dmatrix(1,usize,bw);
      bHessadjoint=new banded_symmetric_dmatrix(1,usize,bw);
      grad.allocate(1,usize);
      Dux.allocate(1,usize,1,xsize);
    }
    break;
  default:
    break;
  }

  step.allocate(1,usize);
  // !!! nov 12
  f1b2gradlist = new df1b2_gradlist(4000000U,200000U,8000000U,400000U,
    2000000U,100000U,adstring("f1b2list1"));

  if (hesstype==2)
  {
    ad_dstar::allocate(nvar);
    global_nvar=nvar;
    df1b2variable::set_nvar(nvar);
    df1b2variable::set_minder(minder(1));
    df1b2variable::set_maxder(maxder(1));
    df1b2variable::set_blocksize();
  }
  if (hesstype!=2)
  {
    if (sparse_hessian_flag==0)
    {
      ad_dstar::allocate(nvar);
      global_nvar=nvar;
      df1b2variable::set_nvar(nvar);
      df1b2variable::set_minder(minder(1));
      df1b2variable::set_maxder(maxder(1));
      df1b2variable::set_blocksize();
      y.allocate(1,nvariables);
    }
    else
    {
      unsigned int nsave=nvar;
      nvar=1;
      ad_dstar::allocate(nvar);
      global_nvar=nvar;
      df1b2variable::set_nvar(1);
      df1b2variable::set_minder(minder(1));
      df1b2variable::set_maxder(maxder(1));
      df1b2variable::set_blocksize();
      y.allocate(1,nvariables);
      nvar=nsave;
      global_nvar=nvar;
    }
  }
  if (df1b2variable::adpool_counter !=0)
  {
    cout << "this can't happen" << endl;
    ad_exit(1);
  }
  df1b2variable::adpool_vector[df1b2variable::adpool_counter]=
    df1b2variable::pool;
#ifndef OPT_LIB
  assert(nvariables >= 0);
#endif
  df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
    (unsigned int)nvariables;
  //df1b2variable::adpool_counter++;
  df1b2variable::increment_adpool_counter();
}

/**
 * Description not yet available.
 * \param
 */
laplace_approximation_calculator::laplace_approximation_calculator(
  int _xsize,
  int _usize,
  ivector _minder,
  ivector _maxder,
  function_minimizer* _pmin
):
  separable_call_level(1),
  triplet_information(0),
  compressed_triplet_information(0),
  nested_separable_calls_counter(1,10),
  nested_tree_position(1,5),
  nr_debug(0),
  pmin(_pmin),
  xsize(_xsize),
  usize(_usize),
  bHess_pd_flag(0),
  sparse_triplet(0),
  sparse_iterator(0),
  sparse_count(0),
  sparse_count_adjoint(0),
  sparse_triplet2(0),
  vsparse_triplet(0),
  vsparse_triplet_adjoint(0),
  sparse_symbolic(0),
  sparse_symbolic2(0),
  fmc1(0),
  fmc(_xsize),
  xadjoint(1,_xsize),
  check_local_uadjoint(1,_usize),
  check_local_uadjoint2(1,_usize),
  check_local_xadjoint(1,_xsize),
  check_local_xadjoint2(1,_xsize),
  uadjoint(1,_usize),
  uhat(1,_usize)
{
  nested_tree_position.initialize();
  nested_separable_calls_counter.initialize();
  //hesstype=1;
  uhat.initialize();
  //var_flag=1;
  var_flag=0;
  calling_set=0;
  antiepsilon=0;
  num_separable_calls=0;
  num_local_re_array=0;
  num_local_fixed_array=0;
  isfunnel_flag=0;
  antiflag=0;
  rseed=3457;
  nfunnelblocks=0;
  block_diagonal_hessian=0;
  block_diagonal_Dux=0;
  block_diagonal_re_list=0;
  block_diagonal_fe_list=0;
  block_diagonal_vhessian=0;
  block_diagonal_vhessianadjoint=0;
  pHess_non_quadprior_part=0;
  bw=0;
  bHess=0;
  grad_x_u=0;
  grad_x=0;
  have_users_hesstype=0;
  int mmin=_minder.indexmin();
  int mmax=_minder.indexmax();
  num_der_blocks= mmax-mmin+1;
  minder.allocate(mmin,mmax);
  maxder.allocate(mmin,mmax);
  minder=_minder;
  maxder=_maxder;
  inner_iprint = 0;
  fmc1.iprint = inner_iprint;
  fmc1.crit=1.e-3;
  nvariables=xsize+usize;
  Hess.allocate(1,usize,1,usize);
  for (int i=1;i<=num_der_blocks;i++)
  {
    if (minder(i)<1 || maxder(i) > nvariables || maxder(i) < minder(i))
    {
      cerr << " minder or maxder value out of bounds in"
        "laplace_approximation_calculator constructor "
       << endl << " values are minder = " << minder
       << " maxder = " << maxder << endl;
      ad_exit(1);
    }
  }
#ifndef OPT_LIB
  assert(maxder(1) >= minder(1));
#endif
  nvar = (unsigned int)(maxder(1) - minder(1) + 1);
  Hessadjoint.allocate(1,usize,1,usize);
  Dux.allocate(1,usize,1,xsize);
  // !!! nov 12
  f1b2gradlist = new df1b2_gradlist(4000000U,200000U,8000000U,400000U,
    2000000U,100000U,adstring("f1b2list1"));
  ad_dstar::allocate(nvar);
  global_nvar=nvar;
  df1b2variable::set_nvar(nvar);
  df1b2variable::set_minder(minder(1));
  df1b2variable::set_maxder(maxder(1));
  df1b2variable::set_blocksize();
  y.allocate(1,nvariables);
}

/**
 * Description not yet available.
 * \param
 */
laplace_approximation_calculator::~laplace_approximation_calculator()
{
  if(importance_sampling_weights)
  {
    delete importance_sampling_weights;
    importance_sampling_weights = 0;
  }
  if(importance_sampling_components)
  {
    delete importance_sampling_components;
    importance_sampling_components = 0;
  }
  if(importance_sampling_values)
  {
    delete importance_sampling_values;
    importance_sampling_values = 0;
  }
  if (block_diagonal_vch)
  {
    delete block_diagonal_vch;
    block_diagonal_vch=0;
  }
  if (block_diagonal_ch)
  {
    delete block_diagonal_ch;
    block_diagonal_ch=0;
  }
  if (block_diagonal_hessian)
  {
    delete block_diagonal_hessian;
    block_diagonal_hessian=0;
  }
  if (block_diagonal_Dux )
  {
    delete block_diagonal_Dux;
    block_diagonal_Dux =0;
  }
  if (block_diagonal_re_list )
  {
    delete block_diagonal_re_list;
    block_diagonal_re_list =0;
  }
  if (block_diagonal_fe_list )
  {
    delete block_diagonal_fe_list;
    block_diagonal_fe_list =0;
  }
  if (block_diagonal_vhessian )
  {
    delete block_diagonal_vhessian;
    block_diagonal_vhessian =0;
  }
  if (block_diagonal_vhessianadjoint )
  {
    delete block_diagonal_vhessianadjoint;
    block_diagonal_vhessianadjoint =0;
  }
  if (separable_function_difference)
  {
    delete separable_function_difference;
    separable_function_difference=0;
  }

  if (derindex)
  {
    delete derindex;
    derindex=0;
  }

  if (pHess_non_quadprior_part)
  {
    delete pHess_non_quadprior_part;
    pHess_non_quadprior_part=0;
  }

  if (triplet_information)
  {
    delete triplet_information;
    triplet_information=0;
  }

  if (bHessadjoint)
  {
    delete bHessadjoint;
    bHessadjoint=0;
  }
  if (grad_x)
  {
    delete grad_x;
    grad_x=0;
  }
  if (grad_x_u)
  {
    delete grad_x_u;
    grad_x_u=0;
  }
  if (bHess)
  {
    delete bHess;
    bHess=0;
  }
  if (f1b2gradlist)
  {
    df1b2_gradlist::set_no_derivatives();
    delete f1b2gradlist;
    f1b2gradlist=0;
  }
  if (df1b2variable::pool)
  {
    //df1b2variable::pool->set_size(-1);
  }
  if (vsparse_triplet_adjoint)
  {
    delete vsparse_triplet_adjoint;
    vsparse_triplet_adjoint=0;
  }
  if (vsparse_triplet)
  {
    delete vsparse_triplet;
    vsparse_triplet=0;
  }
  if (sparse_triplet2)
  {
    delete sparse_triplet2;
    sparse_triplet2=0;
  }
  if (sparse_triplet)
  {
    delete sparse_triplet;
    sparse_triplet=0;
  }
  if (sparse_symbolic)
  {
    delete sparse_symbolic;
    sparse_symbolic=0;
  }
  if (sparse_symbolic2)
  {
    delete sparse_symbolic2;
    sparse_symbolic2=0;
  }
  if (num_local_re_array)
  {
    delete num_local_re_array;
    num_local_re_array = NULL;
  }
  if (num_local_fixed_array)
  {
    delete num_local_fixed_array;
    num_local_fixed_array = NULL;
  }
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::operator()
  (const dvector& _x, const double& _f, function_minimizer * pfmin)
{
  dvector g;

#if defined(USE_ADPVM)
  if (pfmin->test_trust_flag)
  {
    return test_trust_region_method(_x,_f,pfmin);
  }
  if (ad_comm::pvm_manager)
  {
    switch (ad_comm::pvm_manager->mode)
    {
    case 1:
      return default_calculations_parallel_master(_x,_f,pfmin);
      break;
    case 2:
    {
      dvector g(1,1);
      default_calculations_parallel_slave(_x,_f,pfmin);
      return g;
      break;
    }
    default:
      cerr << "illegal value for mode " << endl;
      ad_exit(1);
    }
  }
  else
#endif  //# if defined(USE_ADPVM)

  {
    //hesstype=1;
    //cout << hesstype << endl;
    switch (hesstype)
    {
      case 1:
      {
        int check_der_flag=0;
        int on=-1;
        int nopt=0;
        if ((on=option_match(ad_comm::argc,ad_comm::argv,"-chkder",nopt))>-1)
        {
          check_der_flag=1;
        }
        if (check_der_flag==1)
        {
          g = default_calculations_check_derivatives(_x,pfmin,_f);
        }
        else
        {
          g = default_calculations(_x,_f,pfmin);
        }
        break;
      }
      case 2:
      {
        // Hessian for the random effects is block diagonal
        g = block_diagonal_calculations(_x,_f,pfmin);
        break;
      }
      case 3:
      case 4:  // not banded but full hessian
      {
        // Hessian for the random effects is block diagonal
        if (laplace_approximation_calculator::variance_components_vector)
        {
          g = banded_calculations_lme(_x,_f,pfmin);
        }
        else
        {
          g = banded_calculations(_x,_f,pfmin);
        }
        break;
      }
      default:
      {
        cerr << "illegal value for hesstype " << endl;
        ad_exit(1);
      }
    }
  }

  return g;
}

void random_effects_userfunction(double f,const dvector& x, const dvector& g);

/**
 * Description not yet available.
 * \param
 */
void get_second_ders(int xs,int us,const init_df1b2vector _y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator * lpc)
{
  // Note that xs is the number of active non random effects
  // parameters
  // us is the number of random effects parameters
  int j;
  int i;
  ADUNCONST(init_df1b2vector,y)
  int num_der_blocks=lpc->num_der_blocks;
  int xsize=lpc->xsize;
  int usize=lpc->usize;

  for (int ip=1;ip<=num_der_blocks;ip++)
  {
    df1b2variable::minder=lpc->minder(ip);
    df1b2variable::maxder=lpc->maxder(ip);
    lpc->set_u_dot(ip);
    df1b2_gradlist::set_yes_derivatives();
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;
    initial_params::straight_through_flag=0;
    //initial_params::straight_through_flag=1;
    initial_df1b2params::reset(y,pen);
    initial_params::straight_through_flag=0;
    if (initial_df1b2params::separable_flag)
    {
      initial_df1b2params::separable_calculation_type=2;
      Hess.initialize();
      Dux.initialize();
    }

    //cout << "2D" << endl;
    pfmin->user_function();

    //pfmin->user_function(y,zz);
    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;
    if (!initial_df1b2params::separable_flag)
    {
      set_dependent_variable(*re_objective_function_value::pobjfun);
      df1b2_gradlist::set_no_derivatives();
      df1b2variable::passnumber=1;
      df1b2_gradcalc1();
      int mind=y(1).minder;
      int jmin=max(mind,xsize+1);
      int jmax=min(y(1).maxder,xsize+usize);
      for (i=1;i<=usize;i++)
        for (j=jmin;j<=jmax;j++){
          //cout<<i<<" "<<j<<" "<<mind<<" "<<xsize<<" "<<usize<<endl; 
          Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
        }
      jmin=max(mind,1);
      jmax=min(y(1).maxder,xsize);
      for (i=1;i<=usize;i++)
        for (j=jmin;j<=jmax;j++)
          Dux(i,j)=y(i+xsize).u_bar[j-1];
    }
    if (ip<num_der_blocks)
      f1b2gradlist->reset();
  }

  if  (ad_comm::print_hess_and_exit_flag)
  {
    for (i=1;i<=usize;i++)Hess(i,i) -= 2*CHECK_HESSIAN_PENALTY;
    cout<< "--------------------------------------------------------------------"<<endl;
    cout << "param:" << endl;
    for (i=1;i<=usize;i++)cout << y(i+xsize)<<" ";
    cout << endl;
    cout<< "--------------------------------------------------------------------"<<endl;
    cout << "Hess:" << endl;
    cout <<  Hess << endl;
    cout<< "--------------------------------------------------------------------"<<endl;
    ad_exit(0);
  }

  //cout << "Dux" << endl;
  //cout << setprecision(16) << Dux << endl;
}

/**
 * Description not yet available.
 * \param
 */
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& _Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  ADUNCONST(dmatrix,Hessadjoint)
  ADUNCONST(dmatrix,Hess)
#if !defined(OPT_LIB) && (__cplusplus >= 201103L)
  const int xs = [](unsigned int size)->int
  {
    assert(size <= INT_MAX);
    return static_cast<int>(size);
  }(x.size());
  const int us = [](unsigned int size)->int
  {
    assert(size <= INT_MAX);
    return static_cast<int>(size);
  }(u0.size());
#else
  const int xs = static_cast<int>(x.size());
  const int us = static_cast<int>(u0.size());
#endif
  gradient_structure::set_YES_DERIVATIVES();
  int nvar;
  //dcompressed_triplet & lst2 = *(pmin->lapprox->sparse_triplet);
  //hs_symbolic & ssymb=*(pmin->lapprox->sparse_symbolic);
  //dcompressed_triplet & xxxt = *(pmin->lapprox->sparse_triplet);
  dcompressed_triplet & lst = *(pmin->lapprox->sparse_triplet2);
  hs_symbolic & ssymb=*(pmin->lapprox->sparse_symbolic2);
  {
  /*
    cout << norm2(make_dmatrix(lst)-make_dmatrix(xxxt)) << endl;
    ofstream ofs1("m1");
    ofs1 << setfixed() << setprecision(3) << setw(10)
         << make_dmatrix(lst) << endl;
    ofstream ofs2("m2");
    ofs2 << setfixed() << setprecision(3) << setw(10)
         << make_dmatrix(xxxt) << endl;
   */
  }

  if (laplace_approximation_calculator::alternative_user_function_flag==0)
  {
    if (pmin->lapprox->sparse_hessian_flag==0)
    {
      nvar = xs + us + us * us;
    }
    else
    {
      int sz= lst.indexmax()-lst.indexmin()+1;
      nvar = xs + us + sz;
    }
  }
  else
  {
    nvar = xs + us;
  }
  independent_variables y(1,nvar);

  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects();
  initial_params::set_active_random_effects();
  /*int onvar=*/initial_params::nvarcalc();
  initial_params::xinit(y);    // get the initial values into the
  y(1,xs)=x;

  int i,j;
  dvar_vector d(1,xs+us);

  dmatrix Hess_save;
  // contribution for quadratic prior
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    if (allocated(Hess_save)) Hess_save.deallocate();
    int mmin=Hess.indexmin();
    int mmax=Hess.indexmax();
    Hess_save.allocate(mmin,mmax,mmin,mmax);
    Hess_save=Hess;
    int & vxs = (int&)(xs);
    quadratic_prior::get_cHessian_contribution(Hess,vxs);
  }

  dvar_matrix vHess;
  int ii=xs+us+1;
  if (laplace_approximation_calculator::alternative_user_function_flag!=0)
  {
    dvar_vector vy=dvar_vector(y);
    initial_params::reset(vy);    // get the initial values into the
  }
  else
  {
    // Here need hooks for sparse matrix structures
    if (pmin->lapprox->sparse_hessian_flag==0)
    {
      for (i=1;i<=us;i++)
        for (j=1;j<=us;j++)
          y(ii++)=Hess(i,j);
    }
    else
    {
      int smin=lst.indexmin();
      int smax=lst.indexmax();
      for (i=smin;i<=smax;i++)
        y(ii++)=lst(i);
    }

    if (quadratic_prior::get_num_quadratic_prior()>0)
    {
      Hess=Hess_save;
    }

    dvar_vector vy=dvar_vector(y);
    initial_params::stddev_vscale(d,vy);
    if (pmin->lapprox->sparse_hessian_flag==0)
    {
      vHess.allocate(1,us,1,us);
    }
    initial_params::reset(vy);    // get the initial values into the
    ii=xs+us+1;
    if (initial_df1b2params::have_bounded_random_effects)
    {
      for (i=1;i<=us;i++)
      {
        if (d(i+xs)>0.0)
        {
          for (j=1;j<=us;j++)
          {
            if (d(j+xs)>0.0)
              vHess(i,j)=vy(ii++)/(d(i+xs)*d(j+xs));
            else
              vHess(i,j)=vy(ii++)/d(i+xs);
          }
        }
        else
        {
          for (j=1;j<=us;j++)
          {
            if (d(j+xs)>0.0)
              vHess(i,j)=vy(ii++)/d(j+xs);
            else
              vHess(i,j)=vy(ii++);
          }
        }
      }
    }
    else
    {
      if (laplace_approximation_calculator::sparse_hessian_flag==0)
      {
        for (i=1;i<=us;i++)
        {
          for (j=1;j<=us;j++)
          {
            vHess(i,j)=vy(ii++);
          }
        }
      }
      else
      {
        int mmin=lst.indexmin();
        int mmax=lst.indexmax();
        dvar_compressed_triplet * vsparse_triplet =
        pmin->lapprox->vsparse_triplet;

        if (vsparse_triplet==0)
        {
          pmin->lapprox->vsparse_triplet=
            new dvar_compressed_triplet(mmin,mmax,us,us);
          vsparse_triplet = pmin->lapprox->vsparse_triplet;
          for (i=mmin;i<=mmax;i++)
          {
            (*vsparse_triplet)(1,i)=lst(1,i);
            (*vsparse_triplet)(2,i)=lst(2,i);
          }
        }
        else
        {
          if (!allocated(*vsparse_triplet))
          {
            (*vsparse_triplet).allocate(mmin,mmax,us,us);
            for (i=mmin;i<=mmax;i++)
            {
              (*vsparse_triplet)(1,i)=lst(1,i);
              (*vsparse_triplet)(2,i)=lst(2,i);
            }
          }
        }
        dcompressed_triplet * vsparse_triplet_adjoint =
        pmin->lapprox->vsparse_triplet_adjoint;

        if (vsparse_triplet_adjoint==0)
        {
          pmin->lapprox->vsparse_triplet_adjoint=
          new dcompressed_triplet(mmin,mmax,us,us);
          vsparse_triplet_adjoint = pmin->lapprox->vsparse_triplet_adjoint;
          for (i=mmin;i<=mmax;i++)
          {
            (*vsparse_triplet_adjoint)(1,i)=lst(1,i);
            (*vsparse_triplet_adjoint)(2,i)=lst(2,i);
          }
        }
        else
        {
          if (!allocated(*vsparse_triplet_adjoint))
          {
            (*vsparse_triplet_adjoint).allocate(mmin,mmax,us,us);
            for (i=mmin;i<=mmax;i++)
            {
              (*vsparse_triplet_adjoint)(1,i)=lst(1,i);
              (*vsparse_triplet_adjoint)(2,i)=lst(2,i);
            }
          }
        }
        vsparse_triplet->get_x()=vy(ii,ii+mmax-mmin).shift(1);
      }
    }
  }

  dvariable vf=0.0;

  *objective_function_value::pobjfun=0.0;
  if (laplace_approximation_calculator::alternative_user_function_flag==1)
  {
    laplace_approximation_calculator::alternative_user_function_flag=2;
  }
  pmin->AD_uf_outer();
  if (laplace_approximation_calculator::alternative_user_function_flag==2)
  {
    laplace_approximation_calculator::alternative_user_function_flag=1;
  }
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  vf+=*objective_function_value::pobjfun;
  //cout << setprecision(15) << vf << endl;
  // *********************************************
  // *********************************************
  // *********************************************
  // dvector tmpg(1,nvar);
  // tmpg.initialize();
  // gradcalc(nvar,tmpg);
  // *********************************************
  // *********************************************
  // *********************************************

   int sgn=0;
   dvariable ld = 0;
   double f=0.0;
   if (laplace_approximation_calculator::alternative_user_function_flag==0)
   {
     if (ad_comm::no_ln_det_choleski_flag)
     {
       if(laplace_approximation_calculator::saddlepointflag==0)
       {
         ld=0.5*ln_det(vHess,sgn);
       }
       else
       {
         ld=0.5*ln_det(-vHess,sgn);
       }
     }
     else
     {
       if(laplace_approximation_calculator::saddlepointflag==0)
       {
         int ierr=0;
         if (pmin->lapprox->sparse_hessian_flag==0)
         {
           ld=0.5*ln_det_choleski_error(vHess,ierr);
           if (ierr==1)
           {
             ofstream ofs("hessian.diag");
             ofs << vHess << endl;
             ofs <<  x << endl;
             ofs <<  u0 << endl;
             ofs << "Matrix not positive definite in Ln_det_choleski"
                 << endl;
             cerr << "Matrix not positive definite in Ln_det_choleski\n"
                  << "see file hessian.diag for details"
                 << endl;
             ad_exit(1);
           }
         }
         else
         {
           //double ld1=0.5*ln_det(*(pmin->lapprox->sparse_triplet),
           //  *(pmin->lapprox->sparse_symbolic));

           if (write_sparse_flag)
           {
             //ofstream ofs("sparse");
             //ofs << *(pmin->lapprox->vsparse_triplet) << endl;
           }
           ld=0.5*ln_det(*(pmin->lapprox->vsparse_triplet),
             ssymb,*(pmin->lapprox->sparse_triplet2));
             //*(pmin->lapprox->sparse_symbolic2),pmin->lapprox);
           //cout << ld-ld1 << endl;
         }
       }
       else
       {
         if (pmin->lapprox->sparse_hessian_flag==0)
         {
           ld=0.5*ln_det_choleski(-vHess);
         }
         else
         {
           cerr << "need to fix this" << endl;
           ad_exit(1);
           //ld+=ln_det(-*(pmin->lapprox->vsparse_triplet));
         }
       }
     }

#ifdef DIAG
     int ps1=0;
     if (ps1)
     {
       dmatrix cHess=value(vHess);
       cout << " ln_det = " << ld << " ";
       dvector eig=eigenvalues(cHess);
       dmatrix r(1,2,1,eig.indexmax());
       dvector num(1,eig.indexmax());
       num.fill_seqadd(1,1);
       r(1)=eig;
       r(2)=num;
       dmatrix tt=trans(r);
       dmatrix ss=trans(sort(tt,1));
       cout << ss(1,1)  << " " << ss(1,eig.indexmax()) << " " ;
       int nnn=(int)ss(2,1);
       dmatrix d=eigenvectors(cHess);
       //cout << " d " << d(nnn) << " " << d(nnn)*cHess*d(nnn) << endl;
       dmatrix t=trans(d);
       r(1)=t(nnn);
       r(2)=num;
       dmatrix tt2=trans(r);
       dmatrix ss2=trans(sort(tt2,1));

       cout << " t " << setprecision(3) << ss2(1)(1,5) << " --- "
            << t(nnn)*cHess*t(nnn) << endl;
       cout << "   " << setprecision(3) << ss2(2)(1,5) << endl;
       //cout << " t " << t(1) << " " << t(1)*cHess*t(2) << endl;
     }
#endif

     int nx=0;
     if (nx==0)
     {
       vf+=ld;
     }
     f=value(vf);
     f-=us*0.5*log(2.0*PI);
   }
   else
   {
     f=value(vf);
   }

   dvector g(1,nvar);
   gradcalc(nvar,g);

  ii=1;
  for (i=1;i<=xs;i++)
    xadjoint(i)=g(ii++);
  for (i=1;i<=us;i++)
    uadjoint(i)=g(ii++);

  if (laplace_approximation_calculator::alternative_user_function_flag==0)
  {
    if (pmin->lapprox->sparse_hessian_flag==0)
    {
      if (allocated(Hessadjoint))
      {
        for (i=1;i<=us;i++)
          for (j=1;j<=us;j++)
            Hessadjoint(i,j)=g(ii++);
      }
    }
    else
    {
      dcompressed_triplet * vsparse_triplet_adjoint =
        pmin->lapprox->vsparse_triplet_adjoint;

      int smin=lst.indexmin();
      int smax=lst.indexmax();
      for (i=smin;i<=smax;i++)
      {
        (*vsparse_triplet_adjoint)(i)=g(ii);
        ii++;
      }
    }
  }

   /*
   if (quadratic_prior::get_num_quadratic_prior()>0)
   {
     // *******************************************************
     // *******************************************************
     // for quadratic prior option
     // temporarily get der wrt x of x ---> ln_det(F_uu + inv(A(x)))
     int nvar=x.size()+u0.size();
     independent_variables y(1,nvar);
     initial_params::xinit(y);    // get the initial values into the
     y(1,xs)=x;
     dvar_vector vy=dvar_vector(y);
     initial_params::reset(vy);    // get the initial values into the

     pmin->AD_uf_outer();

     dvar_matrix tmpH=quadratic_prior::get_vHessian_contribution();

     tmpH+=Hess;
     dvariable ld;
     ld=0.5*ln_det(tmpH,sgn);
     dvector g(1,nvar);
     gradcalc(nvar,g);
     int ii=1;
     double checksum=0.0;
     for (i=1;i<=xs;i++)
       xadjoint(i)+=g(ii++);
     for (i=1;i<=us;i++)
       checksum+=g(ii++);

     if (fabs(checksum)> 1.e-10)
     {
       cerr << "checksum too big " << checksum << endl;
       ad_exit(1);
     }

   }
  */


   // *******************************************************
   // *******************************************************

  return f;
}

/**
 * Description not yet available.
 * \param
 */
void get_newton_raphson_info(int xs,int us,const init_df1b2vector _y,
  dmatrix& Hess, dvector& grad, df1b2_gradlist * f1b2gradlist,
  function_minimizer * pfmin)
{
  // Note that xs is the number of active non random effects
  // parameters
  // us is the number of random effects parameters
  int j;
  int i;
  ADUNCONST(init_df1b2vector,y)
  {
    df1b2_gradlist::set_yes_derivatives();
    //cout << re_objective_function_value::pobjfun << endl;
    //cout << re_objective_function_value::pobjfun->ptr << endl;
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;
    initial_df1b2params::reset(y,pen);
    pfmin->user_function();
    //pfmin->user_function(y,zz);
    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;
    set_dependent_variable(*re_objective_function_value::pobjfun);
    df1b2_gradlist::set_no_derivatives();
    df1b2variable::passnumber=1;
  }

  int mind=y(1).minder;
  int jmin=max(mind,xs+1);
  int jmax=min(y(1).maxder,xs+us);
  if (!initial_df1b2params::separable_flag)
  {
    df1b2_gradcalc1();
    for (i=1;i<=us;i++)
      for (j=jmin;j<=jmax;j++)
        Hess(i,j-xs)=y(i+xs).u_bar[j-mind];
    for (j=jmin;j<=jmax;j++)
      grad(j-xs)= re_objective_function_value::pobjfun->u_dot[j-mind];
  }
}

/**
Does Nothing.
*/
void laplace_approximation_calculator::check_for_need_to_reallocate(int ip)
{
}
  //void laplace_approximation_calculator::get_newton_raphson_info
  //  (function_minimizer * pfmin)
  //{
  //  int i,j,ip;
  //
  //  for (ip=1;ip<=num_der_blocks;ip++)
  //  {
  //    // do we need to reallocate memory for df1b2variables?
  //    check_for_need_to_reallocate(ip);
  //    df1b2_gradlist::set_yes_derivatives();
  //    //cout << re_objective_function_value::pobjfun << endl;
  //    //cout << re_objective_function_value::pobjfun->ptr << endl;
  //    (*re_objective_function_value::pobjfun)=0;
  //    df1b2variable pen=0.0;
  //    df1b2variable zz=0.0;
  //    initial_df1b2params::reset(y,pen);
  //    if (initial_df1b2params::separable_flag)
  //    {
  //      Hess.initialize();
  //      grad.initialize();
  //    }
  //    pfmin->user_function();
  //    //pfmin->user_function(y,zz);
  //    (*re_objective_function_value::pobjfun)+=pen;
  //    (*re_objective_function_value::pobjfun)+=zz;
  //
  //    if (!initial_df1b2params::separable_flag)
  //    {
  //      set_dependent_variable(*re_objective_function_value::pobjfun);
  //      df1b2_gradlist::set_no_derivatives();
  //      df1b2variable::passnumber=1;
  //      df1b2_gradcalc1();
  //      int mind=y(1).minder;
  //      int jmin=max(mind,xsize+1);
  //      int jmax=min(y(1).maxder,xsize+usize);
  //      for (i=1;i<=usize;i++)
  //        for (j=jmin;j<=jmax;j++)
  //          Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
  //
  //      for (j=jmin;j<=jmax;j++)
  //        grad(j-xsize)= re_objective_function_value::pobjfun->u_dot[j-mind];
  //    }
  //  }
  //  {
  //    //ofstream ofs("hess.tmp");
  //    //ofs << Hess << endl;
  //    //ofs << grad << endl;
  //  }
  //}
  //

/**
 * Description not yet available.
 * \param
 */
double evaluate_function(const dvector& x,function_minimizer * pfmin)
{
  int usize=initial_params::nvarcalc();
  //double f=0.0;
  dvector g(1,usize);
  independent_variables u(1,usize);
  u=x;
  dvariable vf=0.0;
  vf=initial_params::reset(dvar_vector(u));
  //vf=0.0;
  *objective_function_value::pobjfun=0.0;
  laplace_approximation_calculator::where_are_we_flag=2;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  vf+=*objective_function_value::pobjfun;
  laplace_approximation_calculator::where_are_we_flag=0;
  initial_df1b2params::cobjfun=value(vf);
  gradcalc(usize,g);
  double maxg=max(fabs(g));
  if (!initial_params::mc_phase)
  {
    std::streamsize save = cout.precision();
    cout << setprecision(16) << " f = " << vf
         << " max g = " << maxg << endl;
    cout.precision(save);
  }
  return maxg;
}

/**
 * Description not yet available.
 * \param
 */
double evaluate_function(double& fval,const dvector& x,
  function_minimizer* pfmin)
{
  int usize=initial_params::nvarcalc();
  //double f=0.0;
  dvector g(1,usize);
  independent_variables u(1,usize);
  u=x;
  dvariable vf=0.0;
  vf=initial_params::reset(dvar_vector(u));
  //vf=0.0;
  *objective_function_value::pobjfun=0.0;
  laplace_approximation_calculator::where_are_we_flag=2;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  vf+=*objective_function_value::pobjfun;
  laplace_approximation_calculator::where_are_we_flag=0;
  initial_df1b2params::cobjfun=value(vf);
  gradcalc(usize,g);
  double maxg=max(fabs(g));
  fval=value(vf);
  if (!initial_params::mc_phase)
  {
    cout << setprecision(10) << " f = " << vf
         << " max g = " << maxg << endl;
  }
  return maxg;
}

/**
 * Description not yet available.
 * \param
 */
double evaluate_function(double& fval,const dvector& x,const dvector& g,
  function_minimizer * pfmin)
{
  int usize=initial_params::nvarcalc();
  //double f=0.0;
  //dvector g(1,usize);
  independent_variables u(1,usize);
  u=x;
  dvariable vf=0.0;
  vf=initial_params::reset(dvar_vector(u));
  //vf=0.0;
  *objective_function_value::pobjfun=0.0;
  laplace_approximation_calculator::where_are_we_flag=2;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  vf+=*objective_function_value::pobjfun;
  laplace_approximation_calculator::where_are_we_flag=0;
  initial_df1b2params::cobjfun=value(vf);
  gradcalc(usize,g);
  double maxg=max(fabs(g));
  fval=value(vf);
  if (!initial_params::mc_phase)
  {
    cout << setprecision(15) << " f = " << vf
         << " max g = " << maxg << endl;
  }
  return maxg;
}

/**
 * Description not yet available.
 * \param
 */
double evaluate_function_quiet(const dvector& x,function_minimizer * pfmin)
{
  int usize=initial_params::nvarcalc();
  //double f=0.0;
  dvector g(1,usize);
  independent_variables u(1,usize);
  u=x;
  dvariable vf=0.0;
  vf=initial_params::reset(dvar_vector(u));
  //vf=0.0;
  *objective_function_value::pobjfun=0.0;
  laplace_approximation_calculator::where_are_we_flag=2;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  vf+=*objective_function_value::pobjfun;
  laplace_approximation_calculator::where_are_we_flag=0;
  initial_df1b2params::cobjfun=value(vf);
  gradcalc(usize,g);
  double maxg=max(fabs(g));
  return maxg;
}

/**
 * Description not yet available.
 * \param
 */
void evaluate_function_gradient(double& f,const dvector& x,
  function_minimizer * pfmin,dvector& xadjoint,dvector& uadjoint)
{
  int usize=initial_params::nvarcalc();
  dvector g(1,usize);
  independent_variables u(1,usize);
  u=x;
  dvariable vf=0.0;
  vf=initial_params::reset(dvar_vector(u));
  //vf=0.0;
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  vf+=*objective_function_value::pobjfun;
  initial_df1b2params::cobjfun=value(vf);
  f=value(vf);
  gradcalc(usize,g);
  int xsize=xadjoint.indexmax();
  int us=uadjoint.indexmax();
  xadjoint=g(1,xsize);
  uadjoint=g(xsize+1,xsize+us).shift(1);
}

/**
 * Description not yet available.
 * \param
 */
double evaluate_function_no_derivatives(const dvector& x,
  function_minimizer* pfmin)
{
  double fval;
  gradient_structure::set_NO_DERIVATIVES();
  int usize=initial_params::nvarcalc();
  //double f=0.0;
  dvector g(1,usize);
  independent_variables u(1,usize);
  u=x;
  dvariable vf=0.0;
  vf=initial_params::reset(dvar_vector(u));
  //vf=0.0;
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  vf+=*objective_function_value::pobjfun;
  initial_df1b2params::cobjfun=value(vf);
  fval=value(vf);
  gradient_structure::set_YES_DERIVATIVES();
  return fval;
}

/**
 * Description not yet available.
 * \param
 */
void cleanup_laplace_stuff(laplace_approximation_calculator * l)
{
  if (l)
  {
    delete l;
    l=0;
    df1b2variable::pool->deallocate();

    for (int i=0;i<df1b2variable::adpool_counter;i++)
    {
      delete df1b2variable::adpool_vector[i];
      df1b2variable::adpool_vector[i]=0;
      df1b2variable::nvar_vector[i]=0;
      df1b2variable::adpool_counter=0;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
gauss_hermite_stuff::gauss_hermite_stuff
  (laplace_approximation_calculator * lapprox,
  int use_gauss_hermite,int num_separable_calls ,const ivector& itmp) :
  x(1,use_gauss_hermite), w(1,use_gauss_hermite), mi(0)
{
  // for now we must have the same number of random effects in each
  // separable function call"
  int i;
  for (i=2;i<=num_separable_calls;i++)
  {
    if (itmp(i)!=itmp(i-1))
    {
      cerr << " At present for the adaptive gauss_hermite must have the same"
           << endl
           << " number of random effects in each separable function call"
           << endl;
      ad_exit(1);
    }
  }
  for (i=1;i<=num_separable_calls;i++)
  {
    if (itmp(i)>1)
    {
      lapprox->multi_random_effects=
        max(lapprox->multi_random_effects,itmp(i));
     /*
      cerr << "At present gauss-hermite is only implemented for"
        " one random effect per separable function call "
       << endl;
      ad_exit(1);
     */
    }
  }
  if (allocated(gauss_hermite_values))
    gauss_hermite_values.deallocate();
  if (lapprox->multi_random_effects==0)
  {
    gauss_hermite_values.allocate(1,num_separable_calls,1,use_gauss_hermite);
  }
  else
  {
   ivector indx=pow(use_gauss_hermite,itmp);
    gauss_hermite_values.allocate(1,num_separable_calls,1,indx);
  }

  normalized_gauss_hermite(x,w);
  is=0;
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::set_default_hessian_type(void )
{
  //if (function_minimizer::hesstype==0)
  {
    if (initial_df1b2params::separable_flag)
    {
     // have SEPARABLE_FUNCTION but no object of type quadratic_penalty or
     // normal prior -- can't tell if we should use hesstype 2 or 3
     // until we run
      hesstype=3;
    }
    else
    {
      hesstype=1;  // assume block diagonal
    }
  }
 /*
  else
  {
    hesstype=function_minimizer::hesstype;
  }
 */
}

/**
 * Description not yet available.
 * \param
 */
double laplace_approximation_calculator::get_fx_fu(function_minimizer * pfmin)
{
  initial_params::set_inactive_only_random_effects();
  initial_params::set_active_random_effects();

  if (grad_x==0)
  {
    grad_x=new dvector(1,xsize);
  }
  grad_x->initialize();

  if (grad_x_u==0)
  {
    grad_x_u=new dvector(1,xsize+usize);
  }
  pfmin->inner_opt_flag=0;
  independent_variables u(1,xsize+usize);
  //gradcalc(0,*grad_x_u);
  initial_params::xinit(u);    // get the initial values into the

  dvariable pen=0.0;
  dvariable vf=0.0;
  pen=initial_params::reset(dvar_vector(u));
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  vf+=*objective_function_value::pobjfun;
  objective_function_value::fun_without_pen=value(vf);
  vf+=pen;
  gradcalc(xsize+usize,*grad_x_u);
  double f=value(vf);
  return f;
}

/**
 * Description not yet available.
 * \param
 */
  void laplace_approximation_calculator::begin_separable_call_stuff(void)
  {
    separable_call_level++;
    //build_up_nested_shape();
    //clean(nested_tree_position,separable_call_level);
    //nested_separable_calls_counter(separable_call_level)++;
    //nested_tree_position(separable_call_level)++;
  }

/**
 * Description not yet available.
 * \param
 */
  void laplace_approximation_calculator::end_separable_call_stuff(void)
  {
    //build_up_nested_shape();
    //clean(nested_tree_position,separable_call_level);
    separable_call_level--;
  }

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::build_up_nested_shape(void)
{
  int ll;
  ivector& a =nested_separable_calls_counter;
  int clean_level=0;
  switch(separable_call_level)
  {
  case 1:
    ll=1;
    if (nested_separable_calls_counter(ll)>0)
    {
      if (clean_level==0) clean_level=ll+1;
      if (nested_separable_calls_counter(ll+1)>0)
      {
        nested_shape(a(ll))=a(ll+1);
      }
      else
      {
        break;
      }
    }
    else
    {
      break;
    }
   case 2:
    ll=2;
    if (nested_separable_calls_counter(ll)>0)
    {
      if (clean_level==0) clean_level=ll+1;
      if (nested_separable_calls_counter(ll+1)>0)
      {
        nested_shape(a(1),a(2))=a(ll+1);
      }
      else
      {
        break;
      }
    }
    else
    {
      break;
    }
   case 3:
    ll=3;
    if (nested_separable_calls_counter(ll)>0)
    {
      if (clean_level==0) clean_level=ll+1;
      if (nested_separable_calls_counter(ll+1)>0)
      {
        nested_shape(a(1),a(2),a(3))=a(ll+1);
      }
      else
      {
        break;
      }
    }
    else
    {
      break;
    }
   case 4:
    ll=4;
    if (nested_separable_calls_counter(ll)>0)
    {
      if (clean_level==0) clean_level=ll+1;
      if (nested_separable_calls_counter(ll+1)>0)
      {
        nested_shape(a(1),a(2),a(3),a(4))=a(ll+1);
      }
      else
      {
        break;
      }
    }
    else
    {
      break;
    }
   default:
     cerr << "illegal value in " <<
       "laplace_approximation_calculator::build_up_nested_shape"
       << endl;
  }
  if (clean_level>0)
  {
    int mmax=a.indexmax();
    for (int i=clean_level;i<=mmax;i++)
    {
      a(i)=0;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
ivector * nested_calls_shape::get_ptr1(void)
{
  return ptr1;
}

/**
 * Description not yet available.
 * \param
 */
imatrix * nested_calls_shape::get_ptr2(void)
{
  return ptr2;
}

/**
 * Description not yet available.
 * \param
 */
i3_array * nested_calls_shape::get_ptr3(void)
{
  return ptr3;
}

/**
 * Description not yet available.
 * \param
 */
i4_array * nested_calls_shape::get_ptr4(void)
{
  return ptr4;
}

/**
 * Description not yet available.
 * \param
 */
ostream &  operator << (const ostream& _s,const nested_calls_shape& _m)
{
  ADUNCONST(nested_calls_shape,m)
  ADUNCONST(ofstream,s)
  if (m.get_ptr1())
    s<< *(m.get_ptr1()) << endl << endl;

  if (m.get_ptr2())
    s<< *(m.get_ptr2()) << endl << endl;

  if (m.get_ptr3())
    s<< *(m.get_ptr3()) << endl << endl;

  if (m.get_ptr4())
    s<< *(m.get_ptr4()) << endl << endl;

  return s;
}

/**
 * Description not yet available.
 * \param
 */
void nested_calls_shape::trim(void)
{
  int mmax1=0;
  if (ptr1)
  {
    int imin=ptr1->indexmin();
    int imax=ptr1->indexmax();
    for (int i=imin;i<=imax;i++)
    {
      if ( (*ptr1)(i)==0) break;
      mmax1++;
    }
  }
  if (mmax1==0)
  {
    delete ptr1;
    ptr1=0;
  }
  else
  {
    ivector * tmp=new ivector(1,mmax1);
    (*tmp)=(*ptr1)(1,mmax1);
    delete ptr1;
    ptr1=tmp;
  }
  if (ptr2)
  {
    if (!ptr1)
    {
      delete ptr2;
      ptr2=0;
    }
    else
    {
      imatrix * tmp=new imatrix(1,mmax1);
      int imin=tmp->indexmin();
      int imax=tmp->indexmax();
      for (int i=imin;i<=imax;i++)
      {
        int jmin=(*ptr2)(i).indexmin();
        int jmax=(*ptr2)(i).indexmax();
        int mmax2=0;
        for (int j=jmin;j<=jmax;j++)
        {
          if ((*ptr2)(i,j)==0) break;
          mmax2++;
        }
        if (mmax2>0)
        {
          (*tmp)(i).allocate(1,mmax2);
          (*tmp)(i)=(*ptr2)(i)(1,mmax2);
        }
      }
      delete ptr2;
      ptr2=tmp;
    }
  }
  if (ptr3)
  {
    cerr << "warning not dealitn with prt3" << endl;
    delete ptr3;
    ptr3=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
nested_calls_shape::~nested_calls_shape()
{
  if (ptr1)
  {
    delete ptr1;
    ptr1=0;
  }
  if (ptr2)
  {
    delete ptr2;
    ptr2=0;
  }
  if (ptr3)
  {
    delete ptr3;
    ptr3=0;
  }
  if (ptr4)
  {
    delete ptr4;
    ptr4=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void nested_calls_shape::allocate(int n,int m,int p )
{
  if (ptr1)
  {
    delete ptr1;
    ptr1=0;
  }
  ptr1=new ivector(1,n);

  if (ptr2)
  {
    delete ptr2;
    ptr2=0;
  }
  ptr2=new imatrix(1,n,1,m);
  if (ptr3)
  {
    delete ptr3;
    ptr3=0;
  }
  ptr3=new i3_array(1,n,1,m,1,p);
  /*
  if (ptr4)
  {
    delete ptr4;
    ptr4=0;
  }
  */
}

/**
 * Description not yet available.
 * \param
 */
void nested_calls_shape::allocate(int n,int m)
{
  if (ptr1)
  {
    delete ptr1;
    ptr1=0;
  }
  ptr1=new ivector(1,n);

  if (ptr2)
  {
    delete ptr2;
    ptr2=0;
  }
  ptr2=new imatrix(1,n,1,m);
  /*
  if (ptr3)
  {
    delete ptr3;
    ptr3=0;
  }
  ptr=new i3_array(1,n,1,m,1,p);
  if (ptr4)
  {
    delete ptr4;
    ptr4=0;
  }
  */
}

/**
 * Description not yet available.
 * \param
 */
void nested_calls_shape::initialize(void)
{
  if (ptr1)
  {
    ptr1->initialize();
  }

  if (ptr2)
  {
    ptr2->initialize();
  }

  if (ptr3)
  {
    ptr3->initialize();
  }

  if (ptr4)
  {
    ptr4->initialize();
  }
}

/**
 * Description not yet available.
 * \param
 */
void nested_calls_shape::allocate(int n)
{
  if (ptr1)
  {
    delete ptr1;
    ptr1=0;
  }
  ptr1=new ivector(1,n);

  /*
  if (ptr2)
  {
    delete ptr2;
    ptr2=0;
  }
  ptr=new imatrix(1,n,1,m);
  if (ptr3)
  {
    delete ptr3;
    ptr3=0;
  }
  ptr=new i3_array(1,n,1,m,1,p);
  if (ptr4)
  {
    delete ptr4;
    ptr4=0;
  }
  */
}

/**
 * Description not yet available.
 * \param
 */
void nested_calls_indices::allocate(const nested_calls_shape& _nsc)
{
  int mmax=0;
  ADUNCONST(nested_calls_shape,nsc)
  mmax=nsc.get_ptr1()->indexmax();
  if (ptr1)
  {
    delete ptr1;
    ptr1=0;
  }
  if (nsc.get_ptr1())
  {
    ptr1=new imatrix(1,mmax,1,*nsc.get_ptr1());
  }
  if (ptr2)
  {
    delete ptr2;
    ptr2=0;
  }
  if (nsc.get_ptr2())
  {
    ptr2=new i3_array(1,mmax,1,*nsc.get_ptr1(),1,*nsc.get_ptr2());
  }
  if (ptr3)
  {
    delete ptr3;
    ptr3=0;
  }
  if (nsc.get_ptr3())
  {
    ptr3=new i4_array(1,mmax,1,*nsc.get_ptr1(),1,*nsc.get_ptr2(),
      1,*nsc.get_ptr3());
  }
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_uhat_lm_newton2
  (const dvector& x,function_minimizer * pfmin)
{
  //int on,nopt;
  pfmin->inner_opt_flag=1;
  double f=0.0;
  double fb=1.e+100;
  dvector g(1,usize);
  dvector ub(1,usize);
  independent_variables u(1,usize);
  gradcalc(0,g);
  fmc1.itn=0;
  fmc1.ifn=0;
  fmc1.ireturn=0;
  initial_params::xinit(u);    // get the initial values into the
  initial_params::xinit(ubest);    // get the initial values into the
  fmc1.ialph=0;
  fmc1.ihang=0;
  fmc1.ihflag=0;

  if (init_switch)
  {
    u.initialize();
  }
  else
  {
    u=ubest;
  }

  fmc1.dfn=1.e-2;
  dvariable pen=0.0;
  //cout << "starting  norm(u) = " << norm(u) << endl;
  while (fmc1.ireturn>=0)
  {
   /*
    double nu=norm(value(u));
    if (nu>400)
    {
      cout << "U norm(u) = " << nu  << endl;
    }
    cout << "V norm(u) = " << nu
         << " f = " << f  << endl;
    */
    fmc1.fmin(f,u,g);
    //cout << "W norm(u) = " << norm(value(u)) << endl;
    if (fmc1.ireturn>0)
    {
      dvariable vf=0.0;
      pen=initial_params::reset(dvar_vector(u));
      *objective_function_value::pobjfun=0.0;
      pfmin->AD_uf_inner();
      if (saddlepointflag)
      {
        *objective_function_value::pobjfun*=-1.0;
      }
      if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
      {
        quadratic_prior::get_M_calculations();
      }
      vf+=*objective_function_value::pobjfun;

     /*  this is now done in the operator = function
      if (quadratic_prior::get_num_quadratic_prior()>0)
      {
        vf+= quadratic_prior::get_quadratic_priors();
      }
      */

      objective_function_value::fun_without_pen=value(vf);

      //cout << " pen = " << pen << endl;
      if (noboundepen_flag==0)
      {
        vf+=pen;
      }
      f=value(vf);
      if (f<fb)
      {
        fb=f;
        ub=u;
      }
      gradcalc(usize,g);
      //cout << " f = " << setprecision(17) << f << " " << norm(g)
       // << " " << norm(u) << endl;
    }
    u=ub;
  }
  cout <<  " inner maxg = " <<  fmc1.gmax;
  if (fabs(fmc1.gmax)>1.e+3)
    trapper();

  if (fabs(fmc1.gmax)>1.e-4)
  {
    fmc1.itn=0;
    //fmc1.crit=1.e-9;
    fmc1.ifn=0;
    fmc1.ireturn=0;
    fmc1.ihang=0;
    fmc1.ihflag=0;
    fmc1.ialph=0;
    initial_params::xinit(u);    // get the initial values into the
    //u.initialize();
    while (fmc1.ireturn>=0)
    {
      fmc1.fmin(f,u,g);
      if (fmc1.ireturn>0)
      {
        dvariable vf=0.0;
        pen=initial_params::reset(dvar_vector(u));
        *objective_function_value::pobjfun=0.0;
        pfmin->AD_uf_inner();
        if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
        {
          quadratic_prior::get_M_calculations();
        }
        vf+=*objective_function_value::pobjfun;
        objective_function_value::fun_without_pen=value(vf);

        vf+=pen;
        f=value(vf);
        if (f<fb)
        {
          fb=f;
          ub=u;
        }
        gradcalc(usize,g);
        //cout << " f = " << setprecision(15) << f << " " << norm(g) << endl;
      }
    }
    u=ub;
    cout <<  "  Inner second time = " << fmc1.gmax;
  }
  cout << "  Inner f = " << fb << endl;
  fmc1.ireturn=0;
  fmc1.fbest=fb;
  gradient_structure::set_NO_DERIVATIVES();
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  gradient_structure::set_YES_DERIVATIVES();
  pfmin->inner_opt_flag=0;
  return u;
}
