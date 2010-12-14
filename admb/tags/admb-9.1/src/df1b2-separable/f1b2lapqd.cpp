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

//dvariable AD_uf_inner(const dvector& x,const dvar_vector& u);
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

dvector laplace_approximation_calculator::get_uhat_quasi_newton_qd
  (const dvector& x,function_minimizer * pfmin)
{
  double f=0.0;
  dvector g(1,usize);
  independent_variables u(1,usize);
  fmc1.itn=0;
  fmc1.crit=1.e-9;
  fmc1.ifn=0;
  fmc1.ireturn=0;
  initial_params::xinit(u);    // get the initial values into the
  u.initialize();

  ofstream * tmpfile= ad_comm::global_savefile;
  ad_comm::global_savefile=new ofstream("catageqd.ppp");
  if (ad_comm::global_savefile)
  {
    for (int i=0;i<initial_params::num_initial_params;i++)
    {
       (initial_params::varsptr[i])->save_value();
    }
    delete ad_comm::global_savefile;
    ad_comm::global_savefile=tmpfile;
  }

  system(" catageqd -nox -nohess -crit 1.e-10 -ainp catageqd.ppp ");

  uistream ifs("uval.dat");

  ifs >> u;

  return u;
}

#else

dvector laplace_approximation_calculator::get_uhat_quasi_newton_qd
  (const dvector& x,function_minimizer * pfmin) 
{
  dvector u(1,1)
  return u;
}
#endif
