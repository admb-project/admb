/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void fooledit2(void){;}

void fooledit(void)
{
  fooledit2();
}

#if defined(USE_ADPVM)
int check_pvm_message(int i,int j)
{
  int arrived=0;
 /*
  int mestag=-1;
  int arrived=pvm_probe(ad_comm::pvm_manager->id(i,j),mestag);
  if (arrived) fooledit();
 */
  return arrived;
}

void function_minimizer::pvm_master_function_evaluation_profile(double& f,
  independent_variables& x,const dvector & _g,int nvar,int iprof,double weight,
  double new_value)
{
  dvector & g=(dvector &) _g;

  grad_chk();
  dvariable vf=0.0;
  dvar_vector vx=dvar_vector(x);
  vf=initial_params::reset(vx);
  send_x_to_slaves(vx);
  *objective_function_value::pobjfun=0.0;
  userfunction();
  dvariable tv=likeprof_params::likeprofptr[iprof]->variable();
  vf+=weight*square(new_value-tv);
  vf+=*objective_function_value::pobjfun;
  imatrix im=get_int_from_slaves();
  if (im(1,1)!=67)
  {
    cout << "Error in im" << endl;
    ad_exit(1);
  }

  dvar_matrix fslave=get_f_from_slaves();
  vf+=sum(fslave);
  f=value(vf);
  gradcalc(nvar,g);
  int arrived=check_pvm_message(1,1);
  if (arrived)
    cout << arrived << endl;
  // !!! dave
  grad_chk();
}


  void function_minimizer::pvm_master_prof_minimize(int iprof, double sigma,
    double new_value, const double& _fprof,const int underflow_flag,
    double global_min, const double& _penalties,
    const double& _final_weight)
  {
    double& penalties=(double&) _penalties;
    double& fprof=(double&) _fprof;
    double& final_weight=(double&) _final_weight;
    int arrived=check_pvm_message(1,1);
   send_int_to_slaves(underflow_flag);
   if (!underflow_flag)
   {
    //int max_profile_phases=1;
    int max_profile_phases=3;
    int profile_phase=1;
    initial_params::current_phase = initial_params::max_number_phases;
    while (profile_phase <= max_profile_phases)
    {
     {
      send_int_to_slaves(5);
      // get the number of active parameters
      int nvar=initial_params::nvarcalc();
      dvector g(1,nvar);
      independent_variables x(1,nvar);
      // get the initial values into the x vector
      initial_params::xinit(x);
      fmm fmc(nvar);
      fmc.maxfn= maxfn;
      fmc.iprint= iprint;
      fmc.crit = crit;
      fmc.imax = imax;
      fmc.dfn= dfn;
      fmc.scroll_flag= scroll_flag;
      fmc.min_improve=min_improve;
      double f=0.0;
      // set convergence criterion for this phase
      if (!(!convergence_criteria))
      {
        int ind=min(convergence_criteria.indexmax(),
          initial_params::current_phase);
        fmc.crit=convergence_criteria(ind);
      }
      if (!(!maximum_function_evaluations))
      {
        int ind=min(maximum_function_evaluations.indexmax(),
          initial_params::current_phase);
        fmc.maxfn=int(maximum_function_evaluations(ind));
      }
      int itnsave=0;
      //double weight=pow(50.0,profile_phase)/(sigma*sigma);
      double weight;
      if (sigma)
      {
        weight=pow(120.0,profile_phase)/(sigma*sigma);
      }
      else
      {
        weight=pow(120.0,profile_phase);
      }
      final_weight=weight;
      while (fmc.ireturn>=0)
      {
        fmc.fmin(f,x,g);
        double oldvalue =
          value(likeprof_params::likeprofptr[iprof]->variable());
        double diff = new_value-oldvalue;
        if (fmc.itn>itnsave && diff < pow(.1,iprof)*sigma)
        {
          fmc.ifn=fmc.imax;
        }
        check_pvm_message(1,1);
        send_int_to_slaves(fmc.ireturn);
        if (fmc.ireturn>0)
        {
          check_pvm_message(1,1);
          gradient_structure::set_YES_DERIVATIVES();
          pvm_master_function_evaluation_profile(f,x,g,nvar,iprof,weight,
            new_value);
          gradient_structure::set_NO_DERIVATIVES();
          check_pvm_message(1,1);
        }
      }

      gradient_structure::set_NO_DERIVATIVES();
      check_pvm_message(1,1);

      int break_flag=38;
      send_int_to_slaves(break_flag);
      iexit=fmc.iexit;
      ihflag=fmc.ihflag;
      ihang=fmc.ihang;
      maxfn_flag=fmc.maxfn_flag;
      quit_flag=fmc.quit_flag;
      dvar_vector vx=dvar_vector(x);
      fprof=value(initial_params::reset(vx));
      //send_int_to_slaves(1);
      send_x_to_slaves(vx);
      *objective_function_value::pobjfun=0.0;
      userfunction();
      imatrix im2=get_int_from_slaves();
      if (im2(1,1)!=67)
      {
        cout << "Error in im" << endl;
        ad_exit(1);
      }

      dvar_matrix fslave=get_f_from_slaves();
      double tv=value(likeprof_params::likeprofptr[iprof]->variable());
      fprof+=value(*objective_function_value::pobjfun);
      fprof+=value(sum(fslave));
      penalties=weight*(new_value-tv)*(new_value-tv);
      fprof+=penalties;

      //send_int_to_slaves(0);

      if (quit_flag=='Q') break;
      if (!quit_flag || quit_flag == 'N')
      {
        profile_phase++;
      }
     }
    }
    send_int_to_slaves(0);
   }
   else
   {
     fprof=global_min+20.0;
   }
  }

  void function_minimizer::pvm_slave_prof_minimize(int underflow_flag)
  {
   if (!underflow_flag)
   {
    int max_profile_phases=3;
    int profile_phase=1;
    initial_params::current_phase = initial_params::max_number_phases;
    do
    {
      int prof_flag=get_int_from_master();
      if (prof_flag && prof_flag !=5)
      {
        cerr << "Error in prof_flag " << prof_flag << endl;
        ad_exit(1);
      }
      grad_chk();
      if (!prof_flag) break;
      {
        gradient_structure::set_YES_DERIVATIVES();
        do
        {
          int ireturn=get_int_from_master();
          grad_chk();
          if (ireturn && ireturn ==5)
          {
            cerr << "Error in ireturn " << ireturn << endl;
            ad_exit(1);
          }
          if (ireturn<=0) break;
            pvm_slave_function_evaluation();
          grad_chk();
        }
        while(1);

        int break_flag=get_int_from_master();
        if (break_flag)
        {
          cout << break_flag << endl;
        }
        gradient_structure::set_NO_DERIVATIVES();

        pvm_slave_function_evaluation_noder();

      }
    }
    while(1);
   }
  }
#endif
