/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>

#ifdef ISZERO
  #undef ISZERO
#endif
#define ISZERO(d) ((d)==0.0)

double function_minimizer::projected_hess_determinant(const dvector& g,
  const int underflow_flag)
{
 double lndet=0.0;
 //double ld1=0.0;
 //double ld2=0.0;
 //char ch;
 if (!underflow_flag)
 {
   int sgn=0;
    adstring tmpstring="admodel.hes";
    if (ad_comm::wd_flag)
       tmpstring = ad_comm::adprogram_name + ".hes";
    uistream ifs((char*)tmpstring);

  if (!ifs)
  {
    cerr << "Error opening file admodel.hes" << endl;
  }
  int nvar = 0;
  ifs >> nvar;
  dmatrix S(1,nvar,1,nvar);
  if (nvar > 0)
  {
    if (nvar != initial_params::nvarcalc())
    {
      cout << "the number of independent variables is wrong in admodel.hes"
         << endl;
    }
    dmatrix p(1,nvar,1,nvar);
    //dmatrix p1(1,nvar-1,1,nvar);
    dmatrix h(1,nvar,1,nvar);
    //dmatrix gram(1,nvar-1,1,nvar-1);
    dvector ss(1,nvar);
    ifs >> h;
    if (!ifs)
    {
      cerr << "Error reading the hessian from file admodel.hes" << endl;
    }
    dvector n=g/norm(g);
    // project the standard basis vectors onto the tangent space
    int i;
    for (i=1;i<=nvar;i++)
    {
      p(i)=-n(i)*n;
      p(i,i)+=1;
    }
    //cout << "p*n" << endl;
    //cout << p*n << endl;
    //cin >> ch;

    for (i=1;i<=nvar;i++)
    {
      ss(i)=norm(p(i));
    }

  /*
    double minsize=min(ss);
    for (i=1;i<=nvar;i++)
    {
      if (ss(i)==minsize) break;
      p1(i)=p(i);
    }

    for (int ii=i+1;ii<=nvar;ii++)
    {
      p1(ii-1)=p(ii);
    }
   */

    for (i=1;i<=nvar;i++)
    {
      for (int j=1;j<i;j++)
      {
        double tmp=(h(i,j)+h(j,i))/2.;
        h(i,j)=tmp;
        h(j,i)=tmp;
      }
    }

    //cout << "A" << endl;
   /*
    for (i=1;i<nvar;i++)
    {
      dvector tmp = h*p1(i);
     // cout << "aA" << endl;
      for (int j=1;j<nvar;j++)
      {
        gram(i,j)=tmp*p1(j);
      }
    }
    cout << "B" << endl;
    ld1=ln_det(gram,sgn);
    cout << "CX" << endl;
    for (i=1;i<nvar;i++)
    {
      for (int j=1;j<nvar;j++)
      {
        gram(i,j)=p1(i)*p1(j);
      }
      if (norm(p1(i))==0) cout <<"norm p1 =0 " << endl;
    }
 //   cout << "D" << endl;

    ld2=ln_det(gram,sgn);
   // cout << "E" << endl;
   */

 //   cout << "eigs of h" << endl;
   // cout << sort(eigenvalues(h)) << endl << endl;

 //   cout << "F" << endl;
    for (i=1;i<=nvar;i++)
    {
      dvector tmp=h*p(i);
      for (int j=1;j<=i;j++)
      {
        S(i,j)=tmp*p(j)+n(i)*n(j);
      }
    }
 //   cout << "G" << endl;

    for (i=1;i<=nvar;i++)
    {
      for (int j=1;j<i;j++)
      {
        S(j,i)=S(i,j);
      }
    }
  }
 // cout << "eigs of S" << endl;
 // cout << sort(eigenvalues(S)) << endl << endl;
  lndet=ln_det(S,sgn);
 // cout << "old det = " << lndet << endl;
 // lndet=ld1-ld2;
 // cout << "new det = " << lndet  << "  "  << ld1 << "  " << ld2 << endl;
  //char ch;
  //cin >> ch;
  //double lndet2=0.;
  if (sgn <= 0)
  {
    cerr << "Error restricted Hessian is not positive definite" << endl;
  }
  {
  //  cout << "doing S eigenvalues" << endl;
  //  dvector eig=eigenvalues(S);
  //  cout << "finished S eigenvalues" << endl;
    //lndet2=sum(log(eig));
  //  cout << sort(eig) << endl << endl;
  }
 }
 else
 {
   lndet=-50.0;
 }
 return lndet;
}

void function_minimizer::get_particular_grad(int iprof,int nvar,
  const dvector& fg, const dvector& g)
  {
    independent_variables x(1,nvar);
    // get the initial values into the x vector
    initial_params::xinit(x);
    dvariable vf=0.0;
    gradient_structure::set_YES_DERIVATIVES();
    vf=initial_params::reset(dvar_vector(x));
      if (lapprox)
      {
        if (lapprox->hesstype==2)
        {
          lapprox->separable_calls_counter=0;
        }
      }
    userfunction();
    vf=likeprof_params::likeprofptr[iprof]->variable();
    gradcalc(nvar, g, vf);

    vf=0.0;
    vf=initial_params::reset(dvar_vector(x));
    *objective_function_value::pobjfun=0.0;
      if (lapprox)
      {
        if (lapprox->hesstype==2)
        {
          lapprox->separable_calls_counter=0;
        }
      }
    userfunction();
    vf+=*objective_function_value::pobjfun;
    gradcalc(nvar, fg, vf);

    gradient_structure::set_NO_DERIVATIVES();
    double div=norm(g)*norm(fg);

    if (div==0.0)
      cout << "0" << endl;
    else
      cout << g*fg/(norm(g)*norm(fg)) << endl;
  }

void function_minimizer::prof_minimize(int iprof, double sigma,
  double new_value, const double& _fprof, const int underflow_flag,
  double global_min, const double& _penalties, const double& _final_weight)
   {
     double& penalties=(double&) _penalties;
     double& fprof=(double&) _fprof;
     double& final_weight=(double&) _final_weight;
    if (!underflow_flag)
    {
     int max_profile_phases=3;
     int profile_phase=1;
     initial_params::current_phase = initial_params::max_number_phases;
     while (profile_phase <= max_profile_phases)
     {
      {
       int nvar=initial_params::nvarcalc(); // get the number of active
              // parameters
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
       gradient_structure::set_YES_DERIVATIVES();
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
       double weight = pow(120.0,profile_phase);
       if (!ISZERO(sigma))
       {
         weight /= (sigma*sigma);
       }
       final_weight=weight;
       while (fmc.ireturn>=0)
       {
         fmc.fmin(f,x,g);
         double diff =
           new_value-value(likeprof_params::likeprofptr[iprof]->variable());
         if (fmc.itn>itnsave && diff < pow(.1,iprof)*sigma)
         {
           fmc.ifn=fmc.imax;
         }
         if (fmc.ireturn>0)
         {
           dvariable vf=0.0;
           vf=initial_params::reset(dvar_vector(x));
           *objective_function_value::pobjfun=0.0;
           userfunction();
           dvariable tv=likeprof_params::likeprofptr[iprof]->variable();
           vf+=weight*square(new_value-tv);
           vf+=*objective_function_value::pobjfun;
           gradcalc(nvar, g, vf);
         }
       }
       gradient_structure::set_NO_DERIVATIVES();
       iexit=fmc.iexit;
       ihflag=fmc.ihflag;
       ihang=fmc.ihang;
       maxfn_flag=fmc.maxfn_flag;
       quit_flag=fmc.quit_flag;
       fprof=value(initial_params::reset(dvar_vector(x)));
       *objective_function_value::pobjfun=0.0;
       userfunction();
       double tv=value(likeprof_params::likeprofptr[iprof]->variable());
       fprof+=value(*objective_function_value::pobjfun);
       penalties=weight*(new_value-tv)*(new_value-tv);
       fprof+=penalties;
       if (quit_flag=='Q') break;
       if (!quit_flag || quit_flag == 'N')
       {
         profile_phase++;
       }
      }
     }
    }
    else
    {
      fprof=global_min+20.0;
    }
   }
