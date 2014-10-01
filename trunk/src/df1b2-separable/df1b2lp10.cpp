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
void report_calling_set(laplace_approximation_calculator *lapprox)
{
  ofstream ofs("callset.rpt");

  imatrix& callset=(*lapprox->calling_set);

  ofs << "Total num_separable calls " <<  callset(0,0)-1 << endl;

  for (int i=1;i<=callset.indexmax();i++)
  {
    ofs << "Variable " << i << " num calls = " << callset(i)(0) << endl;
    ofs << callset(i)(1,callset(i).indexmax())<< endl;
  }
}

/**
Check if v is ordered from low to high.

\returns true if ordered, else false
*/
bool check_order(const ivector& v)
{
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  for (int i=mmin;i<=mmax-1;i++)
  {
    if (v(i+1)<v(i))
    {
      return false;
    }
  }
  return true;
}

/**
Check vectors v and w for single common value.

\returns 1 if has a single common value, else 0.
*/
int common(ivector& v, ivector& w)
{
  if (!check_order(v)) v = sort(v);
  if (!check_order(w)) w = sort(w);
  //int vmin=v.indexmin();
  int wmin=w.indexmin();
  int vmax=v.indexmax();
  int wmax=w.indexmax();
  int common_flag=0;
  int i=wmin; int j=wmin;
  for (;;)
  {
    if (v(i)==w(j))
    {
      common_flag=1;
      break;
    }
    else if (v(i)>w(j))
    {
      if (j<wmax)
        j++;
      else
        break;
    }
    else if (v(i)<w(j))
    {
      if (i<vmax)
        i++;
      else
        break;
    }
  }
  return common_flag;
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  check_hessian_type2(function_minimizer * pfmin)
{
  int ip = 0;
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    hesstype=4;
    if (allocated(Hess))
    {
      if (Hess.indexmax()!=usize)
      {
        Hess.deallocate();
        Hess.allocate(1,usize,1,usize);
      }
    }
    else
    {
       Hess.allocate(1,usize,1,usize);
    }
    if (allocated(Hessadjoint))
    {
      if (Hessadjoint.indexmax()!=usize)
      {
        Hessadjoint.deallocate();
        Hessadjoint.allocate(1,usize,1,usize);
      }
    }
    else
    {
       Hessadjoint.allocate(1,usize,1,usize);
    }
    return;
  }
  else
  {
    int nv=initial_df1b2params::set_index();
    if (allocated(used_flags))
    {
      if (used_flags.indexmax() != nv)
      {
        used_flags.safe_deallocate();
      }
    }
    if (!allocated(used_flags))
    {
      used_flags.safe_allocate(1,nv);
    }

    //for (ip=1;ip<=num_der_blocks;ip++)
    {
      used_flags.initialize();
      // do we need to reallocate memory for df1b2variables?
      check_for_need_to_reallocate(ip);
      df1b2_gradlist::set_no_derivatives();
      //cout << re_objective_function_value::pobjfun << endl;
      //cout << re_objective_function_value::pobjfun->ptr << endl;
      (*re_objective_function_value::pobjfun)=0;
      df1b2variable pen=0.0;
      df1b2variable zz=0.0;

      initial_df1b2params::reset(y,pen);
      // call function to do block diagonal newton-raphson
      // the step vector from the newton-raphson is in the vector step
      df1b2_gradlist::set_no_derivatives();

      funnel_init_var::lapprox=this;
      block_diagonal_flag=5;

      quadratic_prior::in_qp_calculations=1;
      pfmin->pre_user_function();
      quadratic_prior::in_qp_calculations=0;

      int non_block_diagonal=0;
      for (int i=xsize+1;i<=xsize+usize;i++)
      {
        if (used_flags(i)>1)
        {
          non_block_diagonal=1;
          break;
        }
      }
      if (non_block_diagonal)
      {
        if (bw< usize/2)
        {
          hesstype=3;  //banded
          if (bHess)
          {
            if (bHess->bandwidth() !=bw)
            {
              delete bHess;
              bHess = new banded_symmetric_dmatrix(1,usize,bw);
              if (bHess==0)
              {
                cerr << "Error allocating banded_symmetric_dmatrix" << endl;
                ad_exit(1);
              }
            }
          }
          else
          {
            bHess = new banded_symmetric_dmatrix(1,usize,bw);
            if (bHess==0)
            {
              cerr << "Error allocating banded_symmetric_dmatrix" << endl;
              ad_exit(1);
            }
          }
          if (bHessadjoint)
          {
            if (bHessadjoint->bandwidth() !=bw)
            {
              delete bHessadjoint;
              bHessadjoint = new banded_symmetric_dmatrix(1,usize,bw);
              if (bHessadjoint==0)
              {
                cerr << "Error allocating banded_symmetric_dmatrix" << endl;
                ad_exit(1);
              }
            }
          }
          else
          {
            bHessadjoint = new banded_symmetric_dmatrix(1,usize,bw);
            if (bHessadjoint==0)
            {
              cerr << "Error allocating banded_symmetric_dmatrix" << endl;
              ad_exit(1);
            }
          }
        }
        else
        {
          //check_sparse_matrix_structure();
          hesstype=4;  // band is so wide so use full matrix
          if (bHess)
          {
            delete bHess;
            bHess=0;
          }

          if (bHessadjoint)
          {
            delete bHessadjoint;
            bHessadjoint=0;
          }

          if (allocated(Hess))
          {
            if (Hess.indexmax() != usize)
            {
              Hess.deallocate();
              Hess.allocate(1,usize,1,usize);
            }
          }
          else
          {
            Hess.allocate(1,usize,1,usize);
          }
          if (allocated(Hessadjoint))
          {
            if (Hessadjoint.indexmax() != usize)
            {
              Hessadjoint.deallocate();
              Hessadjoint.allocate(1,usize,1,usize);
            }
          }
          else
          {
            Hessadjoint.allocate(1,usize,1,usize);
          }
        }
      }
      else
      {
        hesstype=2;
      }
      if (hesstype==2 && num_importance_samples>0)
      {
        if (importance_sampling_components)
        {
          delete importance_sampling_components;
          importance_sampling_components=0;
        }
        importance_sampling_components=
          new dvar_matrix(1,pmin->lapprox->num_separable_calls,
            1,num_importance_samples);
      }
      // check for containg block diagonal structure
      used_flags(1);
      if (calling_set)
      {
        delete calling_set;
      }
      int mmin=used_flags.indexmin()-1;
      int mmax=used_flags.indexmax();
      ivector tmp(mmin,mmax);
      tmp(mmin)=0;
      tmp(mmin+1,mmax)=used_flags;
      {
        calling_set=new imatrix(mmin,mmax,0,tmp);
        calling_set->initialize();
        (*calling_set)(0,0)=1;
      }
      used_flags.initialize();
      quadratic_prior::in_qp_calculations=1;
      pfmin->pre_user_function();
      quadratic_prior::in_qp_calculations=0;
      report_calling_set(this);

      if (hesstype==2 && (num_importance_samples>0 || use_gauss_hermite>0))
      {
        const ivector & itmp=(*num_local_re_array)(1,num_separable_calls);
        const ivector & itmpf=(*num_local_fixed_array)(1,num_separable_calls);

        // ****************************************************
        // ****************************************************
        if (use_gauss_hermite>0)
        {
          if (gh)
          {
            delete gh;
            gh=0;
          }
          gh=new gauss_hermite_stuff(this,use_gauss_hermite,
            num_separable_calls,itmp);
        }

        if (block_diagonal_vch)
        {
          delete block_diagonal_vch;
          block_diagonal_vch=0;
        }

        block_diagonal_vch = new dvar3_array(1,num_separable_calls,
          1,itmp,1,itmp);
        if (block_diagonal_ch)
        {
          delete block_diagonal_ch;
          block_diagonal_ch=0;
        }
        block_diagonal_ch = new d3_array(1,num_separable_calls,
          1,itmp,1,itmp);
        if (block_diagonal_hessian)
        {
          delete block_diagonal_hessian;
          block_diagonal_hessian=0;
        }
        block_diagonal_hessian = new d3_array(1,num_separable_calls,
          1,itmp,1,itmp);
        if (block_diagonal_hessian ==0)
        {
          cerr << "error_allocating d3_array" << endl;
          ad_exit(1);
        }
        block_diagonal_re_list = new imatrix(1,num_separable_calls,
          1,itmp);
        if (block_diagonal_re_list ==0)
        {
          cerr << "error_allocating imatrix" << endl;
          ad_exit(1);
        }
        block_diagonal_fe_list = new imatrix(1,num_separable_calls,
          1,itmpf);
        if (block_diagonal_fe_list ==0)
        {
          cerr << "error_allocating imatrix" << endl;
          ad_exit(1);
        }
        // ****************************************************
        if (block_diagonal_Dux)
        {
          delete block_diagonal_Dux;
          block_diagonal_Dux=0;
        }
        block_diagonal_Dux = new d3_array(1,num_separable_calls,
          1,itmp,1,itmpf);
        if (block_diagonal_Dux ==0)
        {
          cerr << "error_allocating d3_array" << endl;
          ad_exit(1);
        }

        // ****************************************************
        // ****************************************************
        if (block_diagonal_vhessian)
        {
          delete block_diagonal_vhessian;
          block_diagonal_vhessian=0;
        }
        block_diagonal_vhessian = new dvar3_array(1,num_separable_calls,
          1,itmp,1,itmp);
        if (block_diagonal_vhessian ==0)
        {
          cerr << "error_allocating d3_array" << endl;
          ad_exit(1);
        }

        if (block_diagonal_vhessianadjoint)
        {
          delete block_diagonal_vhessianadjoint;
          block_diagonal_vhessianadjoint=0;
        }
        block_diagonal_vhessianadjoint = new d3_array(1,num_separable_calls,
          1,itmp,1,itmp);
        if (block_diagonal_vhessianadjoint ==0)
        {
          cerr << "error_allocating d3_array" << endl;
          ad_exit(1);
        }
      }
      funnel_init_var::lapprox=0;
      block_diagonal_flag=0;
      pen.deallocate();
    }
  }
}
