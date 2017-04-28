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
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
double do_gauss_hermite_block_diagonal(const dvector& x,
  const dvector& u0,const dmatrix& Hess,const dvector& _xadjoint,
  const dvector& _uadjoint,const dmatrix& _Hessadjoint,
  function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  //ADUNCONST(dmatrix,Hessadjoint)
#ifndef OPT_LIB
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
  gradient_structure::set_NO_DERIVATIVES();
  int nsc=pmin->lapprox->num_separable_calls;
  const ivector lrea = (*pmin->lapprox->num_local_re_array)(1,nsc);
  int hroom =  sum(square(lrea));
  int nvar = xs + us + hroom;
  independent_variables y(1,nvar);

  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects();
  initial_params::set_active_random_effects();
  /*int onvar=*/initial_params::nvarcalc();
  initial_params::xinit(y);    // get the initial values into the
  // do we need this next line?
  y(1,xs)=x;

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
    for (int i=1;i<=lus;i++)
      for (int j=1;j<=lus;j++)
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
      if (lus>0)
      {
        for (int i=1;i<=lus;i++)
        {
          for (int j=1;j<=lus;j++)
          {
            block_diagonal_vhessian(ic,i,j)=vy(ii++);
          }
        }
        block_diagonal_ch(ic)=
          choleski_decomp(inv(block_diagonal_vhessian(ic)));
      }
    }
  }

   int nsamp=pmin->lapprox->use_gauss_hermite;
   pmin->lapprox->in_gauss_hermite_phase=1;
   dvar_vector sample_value(1,nsamp);
   sample_value.initialize();

   dvar_vector tau(1,us);;
   // !!! This only works for one random efect in each separable call
   // at present.
   for (int is=1;is<=nsamp;is++)
   {
     int offset=0;
     pmin->lapprox->num_separable_calls=0;
     pmin->lapprox->gh->is=is;
     for (int ic=1;ic<=nsc;ic++)
     {
       int lus=lrea(ic);
       // will need vector stuff here when more than one random effect
       if (lus>1)
       {
         cerr << "error not implemented" << endl;
         ad_exit(1);
       }
       if (lus>0)
       {
         tau(offset+1,offset+lus).shift(1)=block_diagonal_ch(ic)(1,1)*
           pmin->lapprox->gh->x(is);
         offset+=lus;
       }
     }

     // have to reorder the terms to match the block diagonal hessian
     imatrix & ls=*(pmin->lapprox->block_diagonal_re_list);
     int mmin=ls.indexmin();
     int mmax=ls.indexmax();

     ii=1;
     for (int i=mmin;i<=mmax;i++)
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
     for (int i=mmin;i<=mmax;i++)
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
   }

   nsc=pmin->lapprox->num_separable_calls;

   dvariable vf=pmin->do_gauss_hermite_integration();

   int sgn=0;
   dvariable ld=0.0;
   if (ad_comm::no_ln_det_choleski_flag)
   {
     for (int ic=1;ic<=nsc;ic++)
     {
       if (allocated(block_diagonal_vhessian(ic)))
       {
         ld+=ln_det(block_diagonal_vhessian(ic),sgn);
       }
     }
     ld*=0.5;
   }
   else
   {
     for (int ic=1;ic<=nsc;ic++)
     {
       if (allocated(block_diagonal_vhessian(ic)))
       {
         ld+=ln_det_choleski(block_diagonal_vhessian(ic));
       }
     }
     ld*=0.5;
   }

   vf+=ld;
   //vf+=us*0.91893853320467241;

   double f=value(vf);
   gradcalc(nvar,g);

   // put uhat back into the model
   gradient_structure::set_NO_DERIVATIVES();
   vy(xs+1,xs+us).shift(1)=u0;
   initial_params::reset(vy);    // get the values into the model
   gradient_structure::set_YES_DERIVATIVES();

   pmin->lapprox->in_gauss_hermite_phase=0;

  ii=1;
  for (int i=1;i<=xs;i++)
    xadjoint(i)=g(ii++);
  for (int i=1;i<=us;i++)
    uadjoint(i)=g(ii++);
  for (int ic=1;ic<=nsc;ic++)
  {
    int lus=lrea(ic);
    for (int i=1;i<=lus;i++)
    {
      for (int j=1;j<=lus;j++)
      {
        (*pmin->lapprox->block_diagonal_vhessianadjoint)(ic)(i,j)=g(ii++);
      }
    }
  }
  return f;
}
