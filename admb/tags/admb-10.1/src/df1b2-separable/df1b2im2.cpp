/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#if defined(USE_LAPLACE)
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>

/**
 * Description not yet available.
 * \param
 */
double calculate_importance_sample(const dvector& x,const dvector& u0,
  const banded_symmetric_dmatrix& bHess,const dvector& _xadjoint,
  const dvector& _uadjoint,
  const banded_symmetric_dmatrix& _bHessadjoint,function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  ADUNCONST(banded_symmetric_dmatrix,bHessadjoint)
  int bw=bHess.bandwidth();
  const int xs=x.size();
  const int us=u0.size();
  gradient_structure::set_YES_DERIVATIVES();
  int nvar=x.size()+u0.size()+((bw+1)*(2*u0.size()-bw))/2;
  independent_variables y(1,nvar);
  
  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects(); 
  initial_params::set_active_random_effects(); 
  /*int onvar=*/initial_params::nvarcalc(); 
  initial_params::xinit(y);    // get the initial values into the
  y(1,xs)=x;

  int i,j;

 // Here need hooks for sparse matrix structures
  int ii=xs+us+1;
  for (i=1;i<=us;i++)
  {
    int jmin=admax(1,i-bw+1);
    for (j=jmin;j<=i;j++)
    y(ii++)=bHess(i,j);
  }

  dvar_vector vy=dvar_vector(y); 
  banded_symmetric_dvar_matrix vHess(1,us,bw);
  initial_params::reset(vy);    // get the initial values into the
  ii=xs+us+1;
  for (i=1;i<=us;i++)
  {
    int jmin=admax(1,i-bw+1);
    for (j=jmin;j<=i;j++)
      vHess(i,j)=vy(ii++);
  }

   int nsamp=pmin->lapprox->num_importance_samples;
   dvar_vector sample_value(1,nsamp);
   sample_value.initialize();
   
   int ierr;
   banded_lower_triangular_dvar_matrix ch=choleski_decomp(vHess,ierr);
   if (ierr)
   {
     cerr << "error in choleski decomp" << endl;
     ad_exit(1);
   }

   dvariable vf=0.0;
   if (laplace_approximation_calculator::
     print_importance_sampling_weights_flag==0)
   {
     for (int is=1;is<=nsamp;is++)
     {
       dvar_vector tau=solve_trans(ch,pmin->lapprox->epsilon(is));
      
       vy(xs+1,xs+us).shift(1)+=tau;
       initial_params::reset(vy);    // get the values into the model
       vy(xs+1,xs+us).shift(1)-=tau;
  
       *objective_function_value::pobjfun=0.0;
       pmin->AD_uf_outer();
  
       sample_value(is)=*objective_function_value::pobjfun
         -0.5*norm2(pmin->lapprox->epsilon(is));
     }
   }
   else
   {
     dvector normal_weight(1,nsamp);
     int is;
     for (is=1;is<=nsamp;is++)
     {
       dvar_vector tau=solve_trans(ch,pmin->lapprox->epsilon(is));
      
       vy(xs+1,xs+us).shift(1)+=tau;
       initial_params::reset(vy);    // get the values into the model
       vy(xs+1,xs+us).shift(1)-=tau;
  
       *objective_function_value::pobjfun=0.0;
       pmin->AD_uf_outer();
  
       sample_value(is)=*objective_function_value::pobjfun;
       normal_weight(is)=0.5*norm2(pmin->lapprox->epsilon(is));
     }
     dvector tmp1(value(sample_value)-normal_weight);
     double min_vf=min(tmp1);
     dvector tmp=exp(tmp1-min_vf);
     cout << "The unsorted normalized importance samplng weights are " << endl
          << tmp << endl;
     cout << "The sorted normalized importance samplng weights are " << endl
          << sort(tmp) << endl;
     cout << "The sample value normal weight pairs are " << endl;
     for (is=1;is<=nsamp;is++)
     {
       cout << sample_value(is) << "  " << normal_weight(is) << endl;
     }
     cout << "The normalized sample value normal weight pairs are " << endl;
     for (is=1;is<=nsamp;is++)
     {
       cout << normal_weight(is) << "  " 
            << sample_value(is)-normal_weight(is) << endl;
     }
     ad_exit(1);
   }

   dvariable min_vf=min(sample_value);
   vf=min_vf-log(mean(exp(min_vf-sample_value))); 
   vf-=us*0.91893853320467241; 
   
   int sgn=0;
   dvariable ld;
  
   ld=0.5*ln_det_choleski(vHess,sgn);

   vf+=ld;
   double f=value(vf);
   dvector g(1,nvar);
   gradcalc(nvar,g);
  
  ii=1;
  for (i=1;i<=xs;i++)
    xadjoint(i)=g(ii++);
  for (i=1;i<=us;i++)
    uadjoint(i)=g(ii++);
  for (i=1;i<=us;i++)
  {
    int jmin=admax(1,i-bw+1);
    for (j=jmin;j<=i;j++)
      bHessadjoint(i,j)=g(ii++);
  }
  return f;
}

#endif //#if defined(USE_LAPLACE)
