/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>

int function_minimizer::random_effects_flag=0;
int function_minimizer::test_trust_flag=0;
int function_minimizer::negative_eigenvalue_flag=0;
//dvariable AD_uf_inner(const dvector& x,const dvar_vector& u);
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

//int function_minimizer::hesstype=0;

/*
int function_minimizer::set_hessian_type(int n)
{
  if (n<0 || n>4)
  {
    cerr << "Illegal value of " << n
      << " in function_minimizer::set_hessian_type(int) " << endl;
    ad_exit(1);
  }
  hesstype=n;
}
*/

void   random_effects_userfunction(double f,const dvector& x,
  const dvector& g);

void function_minimizer::AD_uf_outer(){}
void function_minimizer::AD_uf_inner(){}
//void function_minimizer::user_function(const init_df1b2vector& x,
 // df1b2variable& f){;}
void function_minimizer::user_function(){}
