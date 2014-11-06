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

/**
 * Description not yet available.
 * \param
 */
double calculate_importance_sample_block_diagonal_funnel(const dvector& x,
  const dvector& u0,const dmatrix& Hess,const dvector& _xadjoint,
  const dvector& _uadjoint,const dmatrix& _Hessadjoint,
  function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  //ADUNCONST(dmatrix,Hessadjoint)
  const int xs=x.size();
  const int us=u0.size();
  gradient_structure::set_NO_DERIVATIVES();
  int nsc=pmin->lapprox->num_separable_calls;
  const ivector lrea = (*pmin->lapprox->num_local_re_array)(1,nsc);
  int hroom =  sum(square(lrea));
  int nvar=x.size()+u0.size()+hroom;
  independent_variables y(1,nvar);

  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects();
  initial_params::set_active_random_effects();
  /*int onvar=*/initial_params::nvarcalc();
  initial_params::xinit(y);    // get the initial values into the
  // do we need this next line?
  y(1,xs)=x;

  int i,j;

  // contribution for quadratic prior
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    //Hess+=quadratic_prior::get_cHessian_contribution();
    int & vxs = (int&)(xs);
    quadratic_prior::get_cHessian_contribution(Hess,vxs);
  }
 // Here need hooks for sparse matrix structures

  dvar3_array & block_diagonal_vhessian=
    *pmin->lapprox->block_diagonal_vhessian;
  block_diagonal_vhessian.initialize();
  dvar3_array& block_diagonal_ch=
    *pmin->lapprox->block_diagonal_vch;
    //dvar3_array(*pmin->lapprox->block_diagonal_ch);
  int ii=xs+us+1;
  d3_array& bdH=(*pmin->lapprox->block_diagonal_hessian);
  for (int ic=1;ic<=nsc;ic++)
  {
    int lus=lrea(ic);
    for (i=1;i<=lus;i++)
      for (j=1;j<=lus;j++)
        y(ii++)=bdH(ic)(i,j);
  }

  dvector g(1,nvar);
  gradcalc(0,g);
  gradient_structure::set_YES_DERIVATIVES();
  dvar_vector vy=dvar_vector(y);
  //initial_params::stddev_vscale(d,vy);
  ii=xs+us+1;
  if (initial_df1b2params::have_bounded_random_effects)
  {
    cerr << "can't do importance sampling with bounded random effects"
     " at present" << endl;
    ad_exit(1);
  }
  else
  {
    for (int ic=1;ic<=nsc;ic++)
    {
      int lus=lrea(ic);
      for (i=1;i<=lus;i++)
      {
        for (j=1;j<=lus;j++)
        {
          block_diagonal_vhessian(ic,i,j)=vy(ii++);
        }
      }
      block_diagonal_ch(ic)=
        choleski_decomp(inv(block_diagonal_vhessian(ic)));
    }
  }

   dvariable vf=0.0;

   int nsamp=pmin->lapprox->num_importance_samples;
   dvar_vector sample_value(1,nsamp);
   sample_value.initialize();

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
     //dvariable fdv;
     funnel_dvariable fdv;
     if (lbound>nsamp) break;
     ad_begin_funnel();
     int icount=0;
     dvar_vector tau(1,us);;
     for (int is=lbound;is<=ubound;is++)
     {
       if (is>nsamp) break;
       icount++;
       int offset=0;
       for (int ic=1;ic<=nsc;ic++)
       {
         int lus=lrea(ic);
         tau(offset+1,offset+lus).shift(1)=block_diagonal_ch(ic)*
           pmin->lapprox->epsilon(is)(offset+1,offset+lus).shift(1);
         offset+=lus;
       }

       // have to reorder the terms to match the block diagonal hessian
       imatrix & ls=*(pmin->lapprox->block_diagonal_re_list);
       int mmin=ls.indexmin();
       int mmax=ls.indexmax();

       int ii=1;
       int i;
       for (i=mmin;i<=mmax;i++)
       {
         int cmin=ls(i).indexmin();
         int cmax=ls(i).indexmax();
         for (int j=cmin;j<=cmax;j++)
         {
           vy(ls(i,j))+=tau(ii++);
         }
       }
       if (ii-1 != us)
       {
         cerr << "error in interface" << endl;
         ad_exit(1);
       }
       initial_params::reset(vy);    // get the values into the model
       ii=1;
       for (i=mmin;i<=mmax;i++)
       {
         int cmin=ls(i).indexmin();
         int cmax=ls(i).indexmax();
         for (int j=cmin;j<=cmax;j++)
         {
           vy(ls(i,j))-=tau(ii++);
         }
       }

       *objective_function_value::pobjfun=0.0;
       pmin->AD_uf_outer();

       if (pmin->lapprox->use_outliers==0)
       {
         sample_value(icount)=*objective_function_value::pobjfun
           -0.5*norm2(pmin->lapprox->epsilon(is))-.91893853320467274177;
       }
       else
       {
         dvector& e=pmin->lapprox->epsilon(is);

         sample_value(icount)=*objective_function_value::pobjfun
           +sum(log(.95*exp(-0.5*square(e))+.0166666667*exp(-square(e)/18.0)))
           -.91893853320467274177;
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

   // **************************************************************
   // **************************************************************
   // **************************************************************

   int sgn=0;
   dvariable ld=0.0;

   if (ad_comm::no_ln_det_choleski_flag)
   {
     for (int ic=1;ic<=nsc;ic++)
     {
       ld+=ln_det(block_diagonal_vhessian(ic),sgn);
     }
     ld*=0.5;
   }
   else
   {
     for (int ic=1;ic<=nsc;ic++)
     {
       ld+=ln_det_choleski(block_diagonal_vhessian(ic));
     }
     ld*=0.5;
   }

   vf+=ld;
   vf-=us*0.91893853320467274177;
   double f=value(vf);
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
  for (int ic=1;ic<=nsc;ic++)
  {
    int lus=lrea(ic);
    for (i=1;i<=lus;i++)
    {
      for (j=1;j<=lus;j++)
      {
        (*pmin->lapprox->block_diagonal_vhessianadjoint)(ic)(i,j)=g(ii++);
      }
    }
  }
  return f;
}
