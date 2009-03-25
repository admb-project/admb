/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#if defined(USE_LAPLACE)
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>

double calculate_importance_sample_funnel(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  ADUNCONST(dmatrix,Hessadjoint)
  const int xs=x.size();
  const int us=u0.size();
  gradient_structure::set_YES_DERIVATIVES();
  int nvar=x.size()+u0.size()+u0.size()*u0.size();
  independent_variables y(1,nvar);
  
  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects(); 
  initial_params::set_active_random_effects(); 
  int onvar=initial_params::nvarcalc(); 
  initial_params::xinit(y);    // get the initial values into the
  // do we need this next line?
  y(1,xs)=x;

  int i,j;
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
  for (i=1;i<=us;i++)
    for (j=1;j<=us;j++)
    y(ii++)=Hess(i,j);

  dvar_vector vy=dvar_vector(y); 
  initial_params::stddev_vscale(d,vy);
  dvar_matrix vHess(1,us,1,us);
  ii=xs+us+1;
  if (initial_df1b2params::have_bounded_random_effects)
  {
    cerr << "can't do importance sampling with bounded random effects"
     " at present" << endl;
    ad_exit(1);
  }
  else
  {
    for (i=1;i<=us;i++)
    {
      for (j=1;j<=us;j++)
      {
        vHess(i,j)=vy(ii++);
      }
    }
  }

   int nsamp=pmin->lapprox->num_importance_samples;
   dvar_vector sample_value(1,nsamp);
   sample_value.initialize();
   dvar_matrix ch=choleski_decomp(inv(vHess));

   dvariable vf=0.0;

   // **************************************************************
   // **************************************************************
   // **************************************************************
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
       dvar_vector tau=ch*pmin->lapprox->epsilon(is);
      
       vy(xs+1,xs+us).shift(1)+=tau;
       initial_params::reset(vy);    // get the values into the model
       vy(xs+1,xs+us).shift(1)-=tau;
  
       *objective_function_value::pobjfun=0.0;
       pmin->AD_uf_outer();
  
       if (pmin->lapprox->use_outliers==0)
       {
         sample_value(icount)=*objective_function_value::pobjfun
           -0.5*norm2(pmin->lapprox->epsilon(is));
       }
       else
       {
         dvector& e=pmin->lapprox->epsilon(is);
  
         sample_value(icount)=*objective_function_value::pobjfun
           +sum(log(.95*exp(-0.5*square(e))+.05/3.0*exp(-square(e)/18.0))); 
       }
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
   //vf-=us*.91893853320467241; 

   
   int sgn=0;
   dvariable ld;
   if (ad_comm::no_ln_det_choleski_flag)
     ld=0.5*ln_det(vHess,sgn);
   else
     ld=0.5*ln_det_choleski(vHess);

   vf+=ld;
   double f=value(vf);
   dvector g(1,nvar);
   gradcalc(nvar,g);

   // put uhat back into the model
   gradient_structure::set_NO_DERIVATIVES();
   vy(xs+1,xs+us).shift(1)=u0;
   initial_params::reset(vy);    // get the values into the model
   gradient_structure::set_YES_DERIVATIVES();
  
  ii=1;
  for (i=1;i<=xs;i++)
    xadjoint(i)=g(ii++);
  for (i=1;i<=us;i++)
    uadjoint(i)=g(ii++);
  for (i=1;i<=us;i++)
    for (j=1;j<=us;j++)
      Hessadjoint(i,j)=g(ii++);
  return f;
}

#endif
