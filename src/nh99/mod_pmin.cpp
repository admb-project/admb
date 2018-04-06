/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void get_confidence_interval(const dvector& left_bd, const dvector& right_bd,
  dmatrix& ms, const dvector& xs, const dvector& siglevel,
  const int& level_index, dvector& xdist,int index);
void get_onesided_intervals(const dvector& left_bd, const dvector& right_bd,
  dmatrix& ms, const dvector& xs, const dvector& siglevel,
  const int& level_index, dvector& xdist,int index);
void report_confidence_limits(const ofstream& ofs3,int numsig_levels,
  dvector& siglevel, const dvector& left_bd, const dvector& right_bd);
void report_onesided_confidence_limits(const ofstream& ofs3,int numsig_levels,
  dvector& siglevel, const dvector& left_bd, const dvector& right_bd,int ip);


dmatrix trans(const dvector& x)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  dmatrix tmp(mmin,mmax,1,1);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i,1)=x(i);
  }
  return tmp;
}
  double mult_factor(int j)
  {
    switch(j)
    {
      case 0:
        return .0;
      case 1:
        return .5;
      case 2:
        return 1.0;
      case 3:
        return 1.5;
      default:
        return 2.0;
    }
  }

  double trimax(double x,double y,double z);

#if defined(USE_ADPVM)
  void function_minimizer::pvm_slave_likeprof_routine(void)
  {
    do
    {
      int prof_switch=get_int_from_master();
      if (!prof_switch) break;
      if (prof_switch !=3)
      {
        cerr << "Error in prof_switch " << prof_switch << endl;
        ad_exit(1);
      }
      int underflow_flag=get_int_from_master();
      pvm_slave_prof_minimize(underflow_flag);
    }
    while(1);
  }
#endif
  void function_minimizer::likeprof_routine(double global_min)
  {
    int on1 = 0;
    int nopt = 0;
    if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-iprint",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -iprint option needs integer  -- ignored" << endl;
        iprint = 10;
      }
      else
      {
        int jj=atoi(ad_comm::argv[on1+1]);
        iprint = jj;
      }
    }
    else
    {
      iprint = 10;
    }

    dvector siglevel("{.90,.95,.975}");
    int num_pp=likeprof_params::likeprofptr[0]->get_stepnumber();
    {
      for (int ip=1;ip<likeprof_params::num_likeprof_params;ip++)
      {
        int sno=likeprof_params::likeprofptr[ip]->get_stepnumber();
        if (sno)
        {
          if (sno>num_pp) num_pp=sno;
        }
      }
    }
    initial_params::current_phase = initial_params::max_number_phases;
    // DF NOV 28 11
    if (random_effects_flag)
    {
     initial_params::set_inactive_only_random_effects();
    }
    int nvar=initial_params::nvarcalc();
    dvector xsave(1,nvar);
    {
      int ii=1;
      initial_params::copy_all_values(xsave,ii);
    }
    double old_value;  // this is where we were
    double new_value;  // this is where we want to go
    double fprof = 0.0;
    double current_value;
    dmatrix lprof(0,likeprof_params::num_likeprof_params-1,-num_pp,num_pp);
    dmatrix ldet(0,likeprof_params::num_likeprof_params-1,-num_pp,num_pp);
    dmatrix ln_det_proj_jac(0,likeprof_params::num_likeprof_params-1,
      -num_pp,num_pp);
    dmatrix pdet(0,likeprof_params::num_likeprof_params-1,-num_pp,num_pp);
    dmatrix actual_value(0,likeprof_params::num_likeprof_params-1,
      -num_pp,num_pp);
    dvector all_values(-num_pp,num_pp);
    dvector all_num_sigs(-num_pp,num_pp);
    //dvector xxxtmp(-num_pp,num_pp);
    //d3_array hesses(-num_pp,num_pp,1,nvar,1,nvar);
    dmatrix lg_jacob(0,likeprof_params::num_likeprof_params-1,-num_pp,num_pp);
    dmatrix lg_prjacob(0,likeprof_params::num_likeprof_params-1,-num_pp,num_pp);
    //dmatrix xxtmp(-num_pp,num_pp,1,nvar);
    dvector xvector(1,nvar);
    dmatrix xmax(-num_pp,num_pp,1,nvar);  // this holds the conditional max
    dmatrix gprof(-num_pp,num_pp,1,nvar);  // this holds the conditional max
    dmatrix fgrads(-num_pp,num_pp,1,nvar);  // this holds the conditional max
    dmatrix xdist(0,likeprof_params::num_likeprof_params-1,-num_pp,num_pp);
    int sign=0;
    double sigma;
    ofstream ofs2((char*) (ad_comm::adprogram_name + adstring(".prf")) );
    double udet =unrestricted_hess_determinant();
    const int offset=0;
    dvector xscale(1,nvar);   // need to get scale from somewhere
    dvector likeprof_save(0,likeprof_params::num_likeprof_params-1);
    dmatrix penalties(0,likeprof_params::num_likeprof_params-1,-num_pp,num_pp);
    penalties.initialize();
#ifdef CURVE_CORRECT
    int nlp=likeprof_params::num_likeprof_params;
    d3_array eigenvals(0,nlp-1,-num_pp,num_pp,1,nvar-1);
    d3_array curvcor(0,nlp-1,-num_pp,num_pp,1,nvar-1);
#endif

    int ip;
    for (ip=0;ip<likeprof_params::num_likeprof_params;ip++)
    {
      likeprof_save(ip)=likeprof_params::likeprofptr[ip]->get_value();
    }
    double final_weight;
    for (ip=0;ip<likeprof_params::num_likeprof_params;ip++)
    {
      int sno=likeprof_params::likeprofptr[ip]->get_stepnumber();
      double snz=likeprof_params::likeprofptr[ip]->get_stepsize();
      if (sno)
      {
        num_pp=sno;
      }
      //snz (step size) must be greater than zero.
      //Check "void likeprof_params::set_stepsize(double x)"
      const double relsig = snz > 0 ? snz : 0.5;

      if (ip>0)
      {
        int ii=1;
        initial_params::restore_all_values(xsave,ii);
      }
      sigma=likeprof_params::likeprofptr[ip]->get_sigma(); // this is the
      if (sigma==0.0)
        cerr << "error standard dev of likeporf parameter is 0" << endl;
                                        // estimated sd
      old_value=likeprof_save(ip);
      old_value=old_value+offset*relsig*sigma;  // this is where we
      int bigint_flag=0;
      int bigint_flag1=0;
      double ldiff=0.0;
      double num_sigs;
      for (int i=1;i<=2;i++)  // go in positive and negative directions
      {
        num_sigs=0.0;
        bigint_flag=0;
        bigint_flag1=0;
        int underflow_flag=0;
        if (i>1) // get the parameter values at the global minimum
        {
          int ii=1;
          initial_params::restore_all_values(xsave,ii);
        }
        if (i==1)
        {
          sign=1;
        }
        else
        {
          sign=-1;
        }
        current_value=old_value;  // initialize at the minimum
        for (int j=0;j<=num_pp;j++)  // go in positive and negative directions
        {
          if (j!=0 || sign > 0)
          {
            if (bigint_flag==0)
            {
              num_sigs+=mult_factor(j)*relsig*sign;
              current_value+=mult_factor(j)*relsig*sign*sigma;
              new_value=current_value;
              // new_value=current_value+j*relsig*sign*sigma;
            }
            else
            {
              if (bigint_flag1==0)
              {
                num_sigs+=1.5*relsig*sign;
                current_value+=1.5*relsig*sign*sigma;
                new_value=current_value;
              }
              else
              {
                num_sigs+=2.5*relsig*sign;
                current_value+=2.5*relsig*sign*sigma;
                new_value=current_value;
              }
            }
#if defined(USE_ADPVM)
          if (ad_comm::pvm_manager)
          {
            if (ad_comm::pvm_manager->mode==1) // master
            {
              send_int_to_slaves(3);
              pvm_master_prof_minimize(ip,sigma,new_value,fprof,underflow_flag,
                global_min,penalties(ip,j*sign),final_weight); // get the
            }
          }
          else
#endif
          {
            if (random_effects_flag==0)
            {
              prof_minimize(ip,sigma,new_value,fprof,underflow_flag,
              global_min,penalties(ip,j*sign),final_weight); // get the
                                                        // conditional max
            }
            else
            {
              prof_minimize_re(ip,sigma,new_value,fprof,underflow_flag,
              global_min,penalties(ip,j*sign),final_weight); // get the
                                                        // conditional max
            }
          }
          all_num_sigs(j*sign)=num_sigs;
          initial_params::xinit(xvector); // save the
          int ic=1;
          // save the conditional maximum
          initial_params::copy_all_values(xmax(sign*j),ic);
          /*int check=*/initial_params::stddev_scale(xscale,xvector);
        //#if defined(DO_PROFILE)
          //dvector curvscale(1,nvar);   // need to get scale from somewhere
        //#endif

       // #if defined(DO_PROFILE)
          // check=initial_params::stddev_curvscale(curvscale,xvector);
       // #endif
          //cout << "xscale = " << endl << xscale << endl;
          //{
           // ofstream ofs("xscale");
           // ofs << xscale << endl;
         // }
#if defined(USE_DDOUBLE)
          lg_jacob(ip,sign*j)=sum(log(fabs(xscale)+double(1.e-60)));
#else
          lg_jacob(ip,sign*j)=sum(log(fabs(xscale)+1.e-60));
#endif
          if (!underflow_flag)
          {
            lprof(ip,sign*j)=fprof;
          }
          else
          {
            lprof(ip,sign*j)=lprof(ip,sign*(j-1))+2;
          }
          double xx=likeprof_params::likeprofptr[ip]->get_value();
          if (!underflow_flag)
          {
            actual_value(ip,sign*j)=xx;
          }
          else
          {
            actual_value(ip,sign*j)=new_value;  // this is where we
          }

          ldiff=fprof-lprof(ip,0);
          if ( ldiff > 40.0)
          {
            underflow_flag=1;
          }

          //if ( (fprof-lprof(ip,0)) > 3.0 && bigint_flag ==0)
          if (abs(j) > 4)
          {
            bigint_flag=1;
          }
          if (abs(j) > 5)
          {
            bigint_flag1=1;
          }
          // get the gradient for the profile likelihood variable at
          // the conditional maximum
          initial_params::current_phase = initial_params::max_number_phases;
          nvar=initial_params::nvarcalc();
          dvector g(1,nvar);
          dvector fg(1,nvar);
          if (!underflow_flag)
          {
            // g is the grad. wrt the prof lik var
            // fg is the grad. wrt the log-likelihood
            get_particular_grad(ip,nvar,fg,g);
            gprof(sign*j)=g;

            fgrads(sign*j)=fg;
            xdist(ip,sign*j)=norm(elem_div(gprof(sign*j),xscale));
          }
          else
          {
            gprof(sign*j)=gprof(sign*(j-1));
            xdist(ip,sign*j)=xdist(ip,sign*(j-1));
          }

        //#if defined(DO_PROFILE)
        /*
          if (!underflow_flag)
          {
            hess_routine_and_constraint(ip,g,fg);  // calculate the hessian
                                            // at the conditional max
          }

          if (!underflow_flag)
          {
            ldet(ip,sign*j)=projected_hess_determinant(g,underflow_flag,
              xscale,ln_det_proj_jac(ip,sign*j));
          }
          else
          {
            ldet(ip,sign*j)=ldet(ip,sign*(j-1));
            ln_det_proj_jac(ip,sign*j)=ln_det_proj_jac(ip,sign*(j-1));
          }
          */
        //#endif
          }   // end of the j loop
        }
      }
      //for (int ix=-num_pp;ix<=num_pp;ix++)
      //{
       // xdist(ip,ix)=norm(elem_div(gprof(ix),xscale));
     // }
      if ( (option_match(ad_comm::argc,ad_comm::argv,"-prsave"))>-1)
      {
        adstring profrep_name=(likeprof_params::likeprofptr[ip]->label());
        ofstream ofs3((char*) (profrep_name+adstring(".pvl")));
        for (int ix=-num_pp;ix<=num_pp;ix++)
        {
          ofs3 << "#Step " << ix << endl;
          ofs3 << "#num sigmas " << all_num_sigs(ix) << endl;
          ofs3 << xmax(ix) << endl;
        }
      }
    }
  #if defined(DO_PROFILE)
    for (ip=0;ip<likeprof_params::num_likeprof_params;ip++)
    {
      ldet(ip)=ldet(ip)-ln_det_proj_jac(ip);
    }
    {
      ofstream ofs("det.tmp");
      for (ip=0;ip<likeprof_params::num_likeprof_params;ip++)
      {
        ofs << "the log dets" << endl;
        ofs << "ldet" << endl;
        ofs << ldet(ip) << endl << endl;
        ofs << "lndet_proj_jac" << endl;
        ofs << ln_det_proj_jac(ip) << endl << endl;
        ofs << "ldet-lndet_proj_jac" << endl;
        ofs << ldet(ip)-ln_det_proj_jac(ip) +ln_det_proj_jac(ip,0)
            << endl << endl;
      }
    }
    //for (ip=0;ip<likeprof_params::num_likeprof_params;ip++)
    //{
     // ldet(ip)=ldet(ip)-(ln_det_proj_jac(ip)-ln_det_proj_jac(ip));
    //}
  #endif
      sigma=likeprof_params::likeprofptr[0]->get_sigma(); // this is the
      if (sigma==0.0)
        cerr << "Error standard dev of likeprof parameter is 0" << endl;
#ifndef CURVE_CORRECT
    normalize_posterior_distribution(udet,siglevel,ofs2,num_pp,
      all_values,actual_value,global_min,offset,lprof,ldet,xdist,
      penalties);
#else
    normalize_posterior_distribution(udet,siglevel,ofs2,num_pp,
      all_values,actual_value,global_min,offset,lprof,ldet,xdist,
      eigenvals,curvcor);
#endif
  }

/*
ofstream of5("eigv.rpt");
void get_ee(const dmatrix& hh, const ofstream& _of5)
{
  ofstream& of5= (ofstream&) _of5;
  int mmin=hh.rowmin();
  int mmax=hh.rowmax();
  dvector l(mmin,mmax);
  dmatrix tmp(mmin,mmax,1,2);
  dvector ll(mmin,mmax);
  dmatrix e=eigenvectors(hh,l);
  for (int i=mmin;i<=mmax;i++)
  {
    ll(i)=e(i)*(hh*e(i));
    of5 << l(i) << "  " << ll(i) << endl;
  }
}
*/
