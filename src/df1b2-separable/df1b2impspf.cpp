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
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>

class dvar_hs_smatrix;

/**
 * Description not yet available.
 * \param
 */
double calculate_importance_sample_shess(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  const int xs=x.size();
  const int us=u0.size();
  gradient_structure::set_YES_DERIVATIVES();

  int nvar=0;
  if (pmin->lapprox->sparse_hessian_flag==0)
  {
    cerr << "Error we should not be here" << endl;
    ad_exit(1);
  }

  dcompressed_triplet & lst = *(pmin->lapprox->sparse_triplet2);
  int smin=lst.indexmin();
  int smax=lst.indexmax();
  int sz= smax-smin+1;
  nvar=x.size()+u0.size()+sz;
  independent_variables y(1,nvar);

  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects();
  initial_params::set_active_random_effects();
  /*int onvar=*/initial_params::nvarcalc();
  initial_params::xinit(y);    // get the initial values into the
  // do we need this next line?
  y(1,xs)=x;

  dvar_vector d(1,xs+us);

  // contribution for quadratic prior
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    //Hess+=quadratic_prior::get_cHessian_contribution();
    int & vxs = (int&)(xs);
    quadratic_prior::get_cHessian_contribution(Hess,vxs);
  }
 // Here need hooks for sparse matrix structures

  int ii=xs+us+1;
  for (int i=smin;i<=smax;i++)
    y(ii++)=lst(i);

  dvar_vector vy=dvar_vector(y);
  initial_params::stddev_vscale(d,vy);


  ii=xs+us+1;
  if (initial_df1b2params::have_bounded_random_effects)
  {
    cerr << "can't do importance sampling with bounded random effects"
     " at present" << endl;
    ad_exit(1);
  }
  else
  {
    dcompressed_triplet & lst = *(pmin->lapprox->sparse_triplet2);
    int mmin=lst.indexmin();
    int mmax=lst.indexmax();
    dvar_compressed_triplet * vsparse_triplet =
      pmin->lapprox->vsparse_triplet;

    if (vsparse_triplet==0)
    {
      pmin->lapprox->vsparse_triplet=
        new dvar_compressed_triplet(mmin,mmax,us,us);
      vsparse_triplet = pmin->lapprox->vsparse_triplet;
      for (int i=mmin;i<=mmax;i++)
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
        for (int i=mmin;i<=mmax;i++)
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
      for (int i=mmin;i<=mmax;i++)
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
        for (int i=mmin;i<=mmax;i++)
        {
          (*vsparse_triplet_adjoint)(1,i)=lst(1,i);
          (*vsparse_triplet_adjoint)(2,i)=lst(2,i);
        }
      }
    }
    vsparse_triplet->get_x()=vy(ii,ii+mmax-mmin).shift(1);
  }

   int nsamp=pmin->lapprox->num_importance_samples;
   dvar_vector sample_value(1,nsamp);
   sample_value.initialize();
   //dvar_matrix ch=choleski_decomp(inv(vHess));

   dvar_compressed_triplet * vsparse_triplet
     = pmin->lapprox->vsparse_triplet;

   dvar_hs_smatrix * dhs= return_choleski_decomp(*vsparse_triplet);

   dvariable vf=0.0;

   // get fhat for ocputing weighted sums.
   initial_params::reset(vy);    // get the values into the model
   *objective_function_value::pobjfun=0.0;
    pmin->AD_uf_outer();
    double fhat=value(*objective_function_value::pobjfun);
   // check if we do this in a group of funnels
   if (pmin->lapprox->isfunnel_flag==0)
   {
     for (int is=1;is<=nsamp;is++)
     {
       //dvar_vector tau=ch*pmin->lapprox->epsilon(is);
       dvar_vector tau=return_choleski_factor_solve(dhs,
         pmin->lapprox->epsilon(is));

       vy(xs+1,xs+us).shift(1)+=tau;
       initial_params::reset(vy);    // get the values into the model
       vy(xs+1,xs+us).shift(1)-=tau;

       *objective_function_value::pobjfun=0.0;
       pmin->AD_uf_outer();

      /*
       if (pmin->lapprox->istudent_flag==0)
      */
       {
         sample_value(is)=*objective_function_value::pobjfun
           -0.5*norm2(pmin->lapprox->epsilon(is));
       }
      /*
       else
       {
         sample_value(is)=*objective_function_value::pobjfun
           +sum(log_student_density(pmin->lapprox->istudent_flag,
           pmin->lapprox->epsilon(is)));
       }
      */
       if (pmin->lapprox->importance_sampling_values)
         (*(pmin->lapprox->importance_sampling_values))(is)
          =value(sample_value(is))-fhat;
     }
     dvariable min_vf=min(sample_value);
     vf=min_vf-log(mean(exp(min_vf-sample_value)));
   }
   else
   {
     int& nfunnelblocks=pmin->lapprox->nfunnelblocks;
     int lbound=1;
     int samplesize=nsamp/nfunnelblocks;
     int ubound=samplesize;
     int mean_count=0;
     dvar_vector fvalues(1,nfunnelblocks);
     ivector blocksizes(1,nfunnelblocks);
     for (int iblock=1;iblock<=nfunnelblocks;iblock++)
     {
       funnel_dvariable fdv;
       if (lbound>nsamp) break;
       ad_begin_funnel();
       int icount=0;


       for (int is=lbound;is<=ubound;is++)
       {
         if (is>nsamp) break;
         icount++;
         dvar_vector tau=return_choleski_factor_solve(dhs,
           pmin->lapprox->epsilon(is));
         vy(xs+1,xs+us).shift(1)+=tau;
         initial_params::reset(vy);    // get the values into the model
         vy(xs+1,xs+us).shift(1)-=tau;

         *objective_function_value::pobjfun=0.0;
         pmin->AD_uf_outer();
       /*
         if (pmin->lapprox->istudent_flag==0)
       */
         {
           sample_value(icount)=*objective_function_value::pobjfun
             -0.5*norm2(pmin->lapprox->epsilon(is));
         }
        /*
         else
         {
           sample_value(icount)=*objective_function_value::pobjfun
             +sum(log_student_density(pmin->lapprox->istudent_flag,
              pmin->lapprox->epsilon(is)));
         }
       */
         if (pmin->lapprox->importance_sampling_values)
           (*(pmin->lapprox->importance_sampling_values))(is)
             =value(sample_value(icount))-fhat;
       }

       if (icount>0)
       {
         mean_count+=1;
         dvar_vector tsp=sample_value(1,icount);
         double min_vf=min(value(tsp));
         fdv=log(mean(exp(min_vf-tsp)))-min_vf;
         dvariable tmp;
         tmp=fdv;
         fvalues(mean_count)=tmp;
         blocksizes(mean_count)=icount;
       }
       lbound+=samplesize;
       ubound+=samplesize;
     }

     double fm=mean(value(fvalues(1,mean_count)));
     dvar_vector nfval=exp(fvalues(1,mean_count)-fm);
     vf=-fm-log(nfval*blocksizes(1,mean_count)/sum(blocksizes(1,mean_count)));
   }
  /*
   if (pmin->lapprox->istudent_flag==0)
  */
   {
     vf-=us*0.91893853320467241;
   }
  /*
   else
   {
     (*(pmin->lapprox->importance_sampling_values))
        +=us*0.91893853320467241;
   }
  */

   dvariable ld;

   //dvariable sld=0.5*ln_det_choleski(make_dvar_matrix(*vsparse_triplet));
   dvariable sld=0.5*ln_det(*vsparse_triplet);
   vf+=sld;

   double f=value(vf);
   dvector g(1,nvar);
   gradcalc(nvar,g);

   // put uhat back into the model
   gradient_structure::set_NO_DERIVATIVES();
   vy(xs+1,xs+us).shift(1)=u0;
   initial_params::reset(vy);    // get the values into the model
   gradient_structure::set_YES_DERIVATIVES();

  ii=1;
  for (int i=1;i<=xs;i++)
    xadjoint(i)=g(ii++);
  for (int i=1;i<=us;i++)
    uadjoint(i)=g(ii++);

  dcompressed_triplet * vsparse_triplet_adjoint =
    pmin->lapprox->vsparse_triplet_adjoint;
  int mmin=vsparse_triplet_adjoint->indexmin();
  int mmax=vsparse_triplet_adjoint->indexmax();
  vsparse_triplet_adjoint->get_x()
    =g(ii,ii+mmax-mmin).shift(1);

  return f;
}
