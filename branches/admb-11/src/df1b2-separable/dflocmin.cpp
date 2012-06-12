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
/*
        int fcount =0;
static int no_stuff=0;

double evaluate_function(const dvector& x,function_minimizer * pfmin);
void get_newton_raphson_info(int xs,int us,const init_df1b2vector _y,dmatrix& Hess,
  dvector& grad, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin);

//dvariable AD_uf_inner(const dvector& x,const dvar_vector& u);
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator* lap);

  double re_objective_function_value::fun_without_pen=0;

      
int laplace_approximation_calculator::saddlepointflag=0; 
int laplace_approximation_calculator::print_importance_sampling_weights_flag=0;

int laplace_approximation_calculator::where_are_we_flag=0; 
dvar_vector * 
  laplace_approximation_calculator::variance_components_vector=0;
*/

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::local_minimization
(dvector& s,dmatrix& H,dvector& grad,double lambda)
{
  int better_flag=0;
  int counter=0;
  //double fbest,f2;
  double fbest;
  dvector vbest(1,usize);
  s.initialize();
  s(1)=1.0;
  vbest.initialize();
  fbest=evaluate_function_no_derivatives(uhat,pmin);
  do
  {
    dvector v=local_minimization_routine(s,H,grad,lambda);
    dvector xx=uhat+v;
    double f2=evaluate_function_no_derivatives(xx,pmin);
    cout << endl << fbest-f2 << endl;
    if(f2<fbest)
    {
      better_flag=1;
      fbest=f2; 
      lambda*=5.0;
      vbest=v;
      s=v;
    }
    else
    {
      if (better_flag==1)
      {
        // we have a better value so go with it
        return vbest;
      }  
      else
      {
        // try a smaller trust region
        lambda/=5;
        s=vbest;
      }
    }
  }
  while (counter<20);

  if (better_flag==0)
  {
    cerr << "Error cannot find better value to try and get a"
      " positive definite hessian" << endl;
  }
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::local_minimization_routine
(dvector& s,dmatrix& H,dvector& grad,double lambda)
{
  double f=0.0;
  double fb=1.e+100;
  dvector g(1,usize);
  dvector ub(1,usize);
  fmc1.itn=0;
  fmc1.ifn=0;
  fmc1.ireturn=0;
  fmc1.ialph=0;
  fmc1.ihang=0;
  fmc1.ihflag=0;
  fmc1.crit=1.e-12;
  double fmsave=fmc1.maxfn;
  fmc1.maxfn=1000;;
  
 
  fmc1.dfn=1.e-2;
  while (fmc1.ireturn>=0)
  {
    fmc1.fmin(f,s,g);
    if (fmc1.ireturn>0)
    {
      double ns=norm(s);
      double ns2=square(ns);
      dvector v=s/ns;

      dvector z=H*v;
      double vHv=v*z;
        
      double gradv=grad*v;
      f=lambda*gradv+0.5*lambda*lambda*vHv+ square(ns2-1.0);
      //f=0.5*lambda*lambda*s*H*s;
      if (f<fb) 
      {
        fb=f;
        ub=s;
      }
      g=lambda*grad/ns -lambda * gradv*s/ns2 
           + lambda * lambda * z/ns 
           - lambda * lambda * vHv*s/ns2 + 4.0*(ns2-1.0)*s;
     
    }
  }
  s=ub;
  cout <<  " inner maxg = " <<  fmc1.gmax;

  fmc1.maxfn=fmsave;
  fmc1.ireturn=0;
  fmc1.fbest=fb;
  return ub;
}

 //
 //
 //dvector laplace_approximation_calculator::local_minimization_routine
 //(dvector& s,dmatrix& H,dvector& grad,double lambda)
 //{
 //  double f=0.0;
 //  double fb=1.e+100;
 //  dvector g(1,usize);
 //  dvector ub(1,usize);
 //  fmc1.itn=0;
 //  fmc1.ifn=0;
 //  fmc1.ireturn=0;
 //  fmc1.ialph=0;
 //  fmc1.ihang=0;
 //  fmc1.ihflag=0;
 //  fmc1.crit=1.e-12;
 //  double beta=.1;
 //  
 //  s.initialize();
 // 
 //  fmc1.dfn=1.e-2;
 //  while (fmc1.ireturn>=0)
 //  {
 //    fmc1.fmin(f,s,g);
 //    if (fmc1.ireturn>0)
 //    {
 //      double den=lambda-norm2(s);
 //
 //      if (den<=0)
 //      {
 //        f=1.e+60;
 //      }
 //      else
 //      {
 //        f=grad*s+0.5*(s*(H*s))+0.5*beta/den;
 //        if (f<fb) 
 //        {
 //          fb=f;
 //          ub=s;
 //        }
 //        g=grad + H*s + lambda*s +beta*s/square(den);
 //      }
 //    }
 //  }
 //  s=ub;
 //  cout <<  " inner maxg = " <<  fmc1.gmax;
 //
 //  fmc1.ireturn=0;
 //  fmc1.fbest=fb;
 //  return ub;
 //}
#endif  //#if defined(USE_LAPLACE)
