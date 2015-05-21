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

static int no_stuff=0;
/*
static void print(double ff,dvector& uuu,dvector& gg)
{
  cout << setprecision(10) << setw(19) << ff << " "
       << setw(19) << uuu   << "  "  << setw(19) << gg << endl;
}
*/

typedef fmm* pfmm;

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_uhat_quasi_newton_block_diagonal
  (const dvector& x,function_minimizer * pfmin)
{
  if (separable_function_difference)
  {
    delete separable_function_difference;
    separable_function_difference=0;
  }
  separable_function_difference = new dvector(1,num_separable_calls);

  fmm** pfmc1 = new pfmm[num_separable_calls];
  pfmc1--;
  ivector ishape(1,num_separable_calls);
  dvector gmax(1,num_separable_calls);
  gmax.initialize();

  for (int i=1;i<=num_separable_calls;i++)
  {
    int m=(*derindex)(i).indexmax();
    ishape(i)=m;
    if (m>0)
    {
    pfmc1[i] = new fmm(m);
    pfmc1[i]->iprint=0;
    pfmc1[i]->crit=inner_crit;
    pfmc1[i]->ireturn=0;
    pfmc1[i]->itn=0;
    pfmc1[i]->ifn=0;
    pfmc1[i]->ialph=0;
    pfmc1[i]->ihang=0;
    pfmc1[i]->ihflag=0;
    pfmc1[i]->maxfn=100;
    pfmc1[i]->gmax=1.e+100;
    pfmc1[i]->use_control_c=0;
    }
    else
    {
      pfmc1[i]= (fmm *)(0);
    }
  }
  dmatrix gg(1,num_separable_calls,1,ishape);
  dmatrix ggb(1,num_separable_calls,1,ishape);
  dmatrix uu(1,num_separable_calls,1,ishape);
  dmatrix uub(1,num_separable_calls,1,ishape);
  dvector ff(1,num_separable_calls);
  dvector ffb(1,num_separable_calls);
  ivector icon(1,num_separable_calls);
  icon.initialize();
  ffb=1.e+100;

  double f=0.0;
  double fb=1.e+100;
  dvector g(1,usize);
  dvector ub(1,usize);
  independent_variables u(1,usize);
  gradcalc(0,g);
  fmc1.itn=0;
  fmc1.ifn=0;
  fmc1.ireturn=0;
  initial_params::xinit(u);    // get the initial values into the
  fmc1.ialph=0;
  fmc1.ihang=0;
  fmc1.ihflag=0;

  if (init_switch)
  {
    u.initialize();
  }

  for (int ii=1;ii<=2;ii++)
  {
    // get the initial u into the uu's
    for (int i=1;i<=num_separable_calls;i++)
    {
      int m=(*derindex)(i).indexmax();
      for (int j=1;j<=m;j++)
      {
        uu(i,j)=u((*derindex)(i)(j));
      }
    }
    fmc1.dfn=1.e-2;
    dvariable pen=0.0;
    int converged=0;
    int initrun_flag=1;
    int loop_counter=0;
    int loop_flag=0;

    while (converged==0)
    {
      if (loop_flag) loop_counter++;
      if (loop_counter>18)
      {
        cout << loop_counter;
      }
      if (!initrun_flag)
      {
        converged=1;
      }
      for (int i=1;i<=num_separable_calls;i++)
      {
        if (ishape(i)>0) //check to see if there are any active randoem effects
        {               // in this function call
          if (!icon(i))
          {
            independent_variables& uuu=*(independent_variables*)(&(uu(i)));
            (pfmc1[i])->fmin(ff[i],uuu,gg(i));
            gmax(i)=fabs(pfmc1[i]->gmax);
            if (!initrun_flag)
            {
              if (gmax(i)<1.e-4  || pfmc1[i]->ireturn<=0)
              {
                icon(i)=1;
              }
              else
              {
                converged=0;
              }
            }
          }
        }
      }
      initrun_flag=0;
      for (int i2=1;i2<=num_separable_calls;i2++)
      {
        int m=(*derindex)(i2).indexmax();
        for (int j=1;j<=m;j++)
        {
          u((*derindex)(i2)(j))=uu(i2,j);
        }
      }
      // put the
      //if (fmc1.ireturn>0)
      {
        dvariable vf=0.0;
        pen=initial_params::reset(dvar_vector(u));
        *objective_function_value::pobjfun=0.0;

        //num_separable_calls=0;

        pmin->inner_opt_flag=1;
        pfmin->AD_uf_inner();
        pmin->inner_opt_flag=0;

        if (saddlepointflag)
        {
          *objective_function_value::pobjfun*=-1.0;
        }
        if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
        {
          quadratic_prior::get_M_calculations();
        }
        vf+=*objective_function_value::pobjfun;

        objective_function_value::fun_without_pen=value(vf);
        vf+=pen;

        gradcalc(usize,g);
        for (int i=1;i<=num_separable_calls;i++)
        {
          int m=(*derindex)(i).indexmax();
          for (int j=1;j<=m;j++)
          {
            gg(i,j)=g((*derindex)(i)(j));
          }
        }
        {
          ofstream ofs("l:/temp1.dat");
          ofs << g.indexmax() << " " << setprecision(15) << g << endl;
        }
        if (saddlepointflag==2)
        {
          ff[1]=-(*separable_function_difference)(1);
          for (int i=2;i<=num_separable_calls;i++)
          {
            ff[i]=-(*separable_function_difference)(i);
            //ff[i]=-(*separable_function_difference)(i)
             // +(*separable_function_difference)(i-1);

            if (ff[i] < ffb[i])
            {
              ffb[i]=ff[i];
              uub[i]=uu[i];
              ggb[i]=gg[i];
            }
          }
        }
        else
        {
          ff[1]=(*separable_function_difference)(1);
          for (int i=2;i<=num_separable_calls;i++)
          {
            ff[i]=(*separable_function_difference)(i);
            //ff[i]=(*separable_function_difference)(i)
             // -(*separable_function_difference)(i-1);

            if (ff[i] < ffb[i])
            {
              ffb[i]=ff[i];
              uub[i]=uu[i];
              ggb[i]=gg[i];
            }
          }
        }
        f=0.0;
        for (int i2=1;i2<=num_separable_calls;i2++)
        {
          f+=ff[i2];
        }
        if (f<fb)
        {
          fb=f;
          ub=u;
        }
      }
      u=ub;
    }
    double tmax=max(gmax);
    cout <<  " inner maxg = " << tmax << endl;

    if (tmax< 1.e-4) break;
  }
  fmc1.ireturn=0;
  fmc1.fbest=fb;
  gradient_structure::set_NO_DERIVATIVES();
  //num_separable_calls=0;
  pmin->inner_opt_flag=1;
  pfmin->AD_uf_inner();
  pmin->inner_opt_flag=0;
  if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  gradient_structure::set_YES_DERIVATIVES();
  for (int i=1;i<=num_separable_calls;i++)
  {
    if (pfmc1[i])
    {
      delete pfmc1[i];
    }
  }
  pfmc1++;
  delete [] pfmc1;
  pfmc1 = 0;
  return u;
}
