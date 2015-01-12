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
double fcomp1(dvector x,dvector d,int samplesize,int n,dvector & g,
  dmatrix& M);

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::make_sparse_triplet(void)
{
  //int i;
  /*
  int mmax=Hess.indexmax();
  int nz=sum(Hess);
  if (sparse_triplet)
  {
    delete sparse_triplet;
    sparse_triplet=0;
  }
  */
  int nz2=0;
  if (compressed_triplet_information)
  {
    imatrix & cti = *compressed_triplet_information;
    int mmin=cti(cti.indexmin()).indexmin();
    int mmax=cti(cti.indexmin()).indexmax();
    nz2=1;
    int lmin=cti(2,1);
    for (int i=mmin+1;i<=mmax;i++)
    {
      if (cti(1,i)>cti(1,i-1))
      {
        nz2++;
        lmin=cti(2,i);
      }
      else if (cti(2,i)>lmin)
      {
        lmin=cti(2,i);
        nz2++;
      }
    }
  }
  //cout << nz2-nz << endl;
 
  if (sparse_triplet)
  {
    delete sparse_triplet;
    sparse_triplet=0;
  }
  //sparse_triplet = new dcompressed_triplet(1,nz2,usize,usize);
  if (sparse_triplet2)
  {
    delete sparse_triplet2;
    sparse_triplet2=0;
  }
  sparse_triplet2 = new dcompressed_triplet(1,nz2,usize,usize);

  if (compressed_triplet_information)
  {
    imatrix & cti = *compressed_triplet_information;
    int mmin=cti(cti.indexmin()).indexmin();
    int mmax=cti(cti.indexmin()).indexmax();
    if (sparse_iterator)
    {
      delete sparse_iterator;
      sparse_iterator=0;
    }
    sparse_iterator=new ivector(mmin,mmax);
    int ii=1;
    int lmin=cti(2,1);
    (*sparse_triplet2)(1,ii)=cti(1,1);
    (*sparse_triplet2)(2,ii)=cti(2,1);
    (*sparse_iterator)(cti(3,1))=ii;
    for (int i=mmin+1;i<=mmax;i++)
    {
      if (cti(1,i)>cti(1,i-1))
      {
        ii++;
        (*sparse_triplet2)(1,ii)=cti(1,i);
        (*sparse_triplet2)(2,ii)=cti(2,i);
        lmin=cti(2,i);
      }
      else if (cti(2,i)>lmin)
      {
        ii++;
        (*sparse_triplet2)(1,ii)=cti(1,i);
        (*sparse_triplet2)(2,ii)=cti(2,i);
        lmin=cti(2,i);
      }
      (*sparse_iterator)(cti(3,i))=ii;
    }
  }
  //cout << setw(8) << setprecision(2) << setscientific() << rowsum(Hess) << endl;
  //cout << setw(8) << setprecision(2) << setscientific() << Hess << endl;
 /*
  int ii=0;
  for (i=1;i<=mmax;i++)
  {
    for (int j=i;j<=mmax;j++)
    {
      if (Hess(i,j) != 0.0)
      {
        ++ii;
        (*sparse_triplet)(1,ii)=i;
        (*sparse_triplet)(2,ii)=j;
        (*sparse_triplet)(ii)=0.0;
      }
    }
  }
  */
        
  //sparse_symbolic = new hs_symbolic(*sparse_triplet,1); 
  sparse_symbolic2 = new hs_symbolic(*sparse_triplet2,1); 

}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::generate_antithetical_rvs()
{
  // number of random vectors
  const ivector & itmp=(*num_local_re_array)(1,num_separable_calls);
  //const ivector & itmpf=(*num_local_fixed_array)(1,num_separable_calls);
  int i;
  for (i=2;i<=num_separable_calls;i++)
  {
    if (itmp(i) != itmp(i-1))
    {
      cerr << "At present can only use antithetical rv's when "
              "all separable calls are the same size" << endl;
      ad_exit(1);
    }
  }
  int n=itmp(1);
  double samplesize=num_importance_samples;
  
  // mesh size
  double delta=0.01;
  // maximum of distribution is near here
  double mid=sqrt(double(n-1));
  dmatrix weights(1,2*n,1,2);
  double spread=15;
  if (mid-spread<=0.001)
    spread=mid-0.1;
  double ssum=0.0;
  double x=0.0;
  double tmax=(n-1)*log(mid)-0.5*mid*mid;
  for (x=mid-spread;x<=mid+spread;x+=delta)
  {
    ssum+=exp((n-1)*log(x)-0.5*x*x-tmax);
  }
  double tsum=0;
  dvector dist(1,samplesize+1);
  dist.initialize();
  int is=0;
  int ii;
  for (x=mid-spread;x<=mid+spread;x+=delta)
  {
    tsum+=exp((n-1)*log(x)-0.5*x*x-tmax)/ssum*samplesize;
    int ns=int(tsum);
    for (ii=1;ii<=ns;ii++)
    {
      dist(++is)=x;
    }
    tsum-=ns;
  }
  if (is==samplesize-1)
  {
    dist(samplesize)=mid;
  }
  else if (is<samplesize-1)
  {
    cerr << "This can't happen" << endl;
    exit(1);
  }
      
  // get random numbers    
    
  random_number_generator rng(rseed);
  if (antiepsilon)
  {
    if (allocated(*antiepsilon))
    {
      delete antiepsilon;
      antiepsilon=0;
    }
  }
  antiepsilon=new dmatrix(1,samplesize,1,n);
  dmatrix & M=*antiepsilon;
  M.fill_randn(rng);
  
  for (i=1;i<=samplesize;i++)
  {
    M(i)=M(i)/norm(M(i));
  }
  int nvar=(samplesize-1)*n;
  independent_variables xx(1,nvar);
  ii=0;
  for (i=2;i<=samplesize;i++)
  {
    int j;
    for (j=1;j<=n;j++)
    {
      xx(++ii)=M(i,j);
    }
  }

  fmmt1 fmc(nvar,5);
  //fmm fmc(nvar,5);
  fmc.noprintx=1;
  fmc.iprint=10;
  fmc.maxfn=2500;
  fmc.crit=1.e-6;

  double f;
  double fbest=1.e+50;;
  dvector g(1,nvar);
  dvector gbest(1,nvar);
  dvector xbest(1,nvar);

  gbest.fill_seqadd(1.e+50,0.);
  {
    while (fmc.ireturn>=0)
    {
      //int badflag=0;
      fmc.fmin(f,xx,g);
      if (fmc.ihang)
      {
        //int hang_flag=fmc.ihang;
        //double maxg=max(g);
        //double ccrit=fmc.crit;
        //int current_ifn=fmc.ifn;
      }
      if (fmc.ireturn>0)
      {
         f=fcomp1(xx,dist,samplesize,n,g,M);
         if (f < fbest)
         {
           fbest=f;
           gbest=g;
           xbest=xx;
         }
       }
     }
     xx=xbest;
  }
  ii=0;
  for (i=2;i<=samplesize;i++)
  {
    int j;
    for (j=1;j<=n;j++)
    {
      M(i,j)=xx(++ii);
    }
  }
  for (i=1;i<=samplesize;i++)
  {
    M(i)*=dist(i)/norm(M(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
double fcomp1(dvector x,dvector d,int samplesize,int n,dvector & g,
  dmatrix& M)
{
  dmatrix VM(1,samplesize,1,n);
  dmatrix C(1,samplesize,1,samplesize);
  dmatrix VM0(1,samplesize,1,n);
  dvector N(1,samplesize);
  dmatrix dfVM(1,samplesize,1,n);
  dmatrix dfVM0(1,samplesize,1,n);
  dvector dfN(1,samplesize);
  dfVM.initialize();
  dfVM0.initialize();
  dfN.initialize();

  double f=0.0;
  int ii=0;
  int i,j;
  VM0(1)=M(1);
  for (i=2;i<=samplesize;i++)
  {
    for (j=1;j<=n;j++)
    {
      VM0(i,j)=x(++ii);
    }
  }
  for (i=1;i<=samplesize;i++)
  {
    N(i)=norm(VM0(i));
    VM(i)=VM0(i)*(d(i)/N(i));
  }
  for (i=1;i<=samplesize;i++)
  {
    for (ii=i+1;ii<=samplesize;ii++)
    {
      //C(i,ii)=1.0/(0.01+norm2(VM(i)-VM(ii)));
      //f+=C(i,ii);
      C(i,ii)=norm2(VM(i)-VM(ii));
      f-=C(i,ii);
      //f+=1.0/(0.01+norm2(VM(i)-VM(ii)));
    }
    f+=100.0*square(log(N(i)));
  }
  for (i=1;i<=samplesize;i++)
  {
    //f+=100.0*square(log(N(i)));
    dfN(i)+=200*log(N(i))/N(i);
    for (ii=i+1;ii<=samplesize;ii++)
    {
      //f+=1.0/(0.01+norm2(VM(i)-VM(ii)));
      //double tmp=-1.0/square(0.01+norm2(VM(i)-VM(ii)));
      //double tmp=-square(C(i,ii));
      dvector vtmp=-2.0*(VM(i)-VM(ii));
      dfVM(i)+=vtmp;
      dfVM(ii)-=vtmp;
    }
  }
  for (i=1;i<=samplesize;i++)
  {
    //VM(i)=VM0(i)*(d(i)/N(i));
    dfVM0(i)=dfVM(i)*d(i)/N(i);
    dfN(i)-=(dfVM(i)*VM0(i))*d(i)/square(N(i));
    
    //N(i)=norm(VM0(i));
    dfVM0(i)+=dfN(i)/N(i)*VM0(i);
  }
  ii=0;
  for (i=2;i<=samplesize;i++)
  {
    for (j=1;j<=n;j++)
    {
      //VM0(i,j)=vx(++ii);
      g(++ii)=dfVM0(i,j);
    }
  }
  return f;
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::check_hessian_type(const dvector& _x,
  function_minimizer * pfmin)
{  
  pfmin->pre_user_function();
}

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::pre_user_function(void)
{  
  if (lapprox)
  {
    if (lapprox->hesstype==2) 
    {
      lapprox->separable_calls_counter=0;
    }
  }
  user_function();
 /* 
  if (lapprox)
  {
    if (lapprox->hesstype==2) 
    {
      lapprox->nested_shape.trim();
      cout << lapprox->nested_shape;
      lapprox->nested_indices.allocate(lapprox->nested_shape);
      lapprox->separable_calls_counter=0;
      user_function();
    }
  }
 */
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  check_hessian_type(function_minimizer * pfmin)
{
  //int i,j,ip; 
  int i,ip; 
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

      if (sparse_hessian_flag)
      {
        // just to get the number of separable calls
        separable_calls_counter=0;
        pfmin->AD_uf_inner();
        // allocate space for uncompressed sparse hessian information

        //num_separable_calls=separable_calls_counter;
        if (triplet_information==0) 
        {
          triplet_information =new i3_array(1,separable_calls_counter);
        }
        else if ( triplet_information->indexmax() != separable_calls_counter) 
        {
          delete triplet_information;
          triplet_information =new i3_array(1,separable_calls_counter);
        }
        triplet_information->initialize();
        separable_calls_counter=0;
      }

      pfmin->pre_user_function();


      if (sparse_hessian_flag)
      {
        // turn triplet_informaiton into  compressed_triplet_information 
        int mmin= triplet_information->indexmin();
        int mmax= triplet_information->indexmax();
        int i;
        int ndim=0;
        for (i=mmin;i<=mmax;i++)
        {
          if (allocated((*triplet_information)(i)))
          {
            ndim+=(*triplet_information)(i,1).indexmax();
          }
        }
        if (compressed_triplet_information)
        {
          delete compressed_triplet_information;
          compressed_triplet_information=0;
        }
        compressed_triplet_information=new imatrix(1,ndim,1,3);
        (*compressed_triplet_information)(3).fill_seqadd(1,1);
        int ii=0;
        for (i=mmin;i<=mmax;i++)
        {
          if (allocated((*triplet_information)(i)))
          {
            int jmin=(*triplet_information)(i,1).indexmin();
            int jmax=(*triplet_information)(i,1).indexmax();
            int j;
            for (j=jmin;j<=jmax;j++)
            {
              ii++;
              (*compressed_triplet_information)(ii,1)=
                (*triplet_information)(i,1,j);
              (*compressed_triplet_information)(ii,2)=
                (*triplet_information)(i,2,j);
              (*compressed_triplet_information)(ii,3)=ii;
            }
          }
        }
        imatrix & cti= *compressed_triplet_information;
        cti=sort(cti,1);
        int lmin=1;
        int lmax=0;
        for (i=2;i<=ndim;i++)
        {
          if (cti(i,1)>cti(i-1,1))
          {
            lmax=i-1;
            cti.sub(lmin,lmax)=sort(cti.sub(lmin,lmax),2);
            lmin=i;
          }
        } 
        cti.sub(lmin,ndim)=sort(cti.sub(lmin,ndim),2);
        imatrix tmp=trans(cti);
        delete compressed_triplet_information;
        compressed_triplet_information=new imatrix(tmp);
          
      }  

      quadratic_prior::in_qp_calculations=0; 
  
      int non_block_diagonal=0;
      for (i=xsize+1;i<=xsize+usize;i++)
      {
        if (used_flags(i)>1)
        {
          non_block_diagonal=1;
          break;
        } 
      }
      if (non_block_diagonal)
      {
        if (bw< usize/2 && sparse_hessian_flag==0)
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
            if (sparse_hessian_flag)
            {
              Hess.deallocate();
            }
            else
            {
              if (Hess.indexmax() != usize)
              {
                Hess.deallocate();
                Hess.allocate(1,usize,1,usize);
              }
            }
          }
          else
          {
            if (sparse_hessian_flag==0)
              Hess.allocate(1,usize,1,usize);
          } 
          if (sparse_hessian_flag)
          {
            make_sparse_triplet();
          }

          if (allocated(Hessadjoint))
          {
            if (sparse_hessian_flag)
            {
              Hess.deallocate();
            }
            else
            {
              if (Hessadjoint.indexmax() != usize)
              {
                Hessadjoint.deallocate();
                Hessadjoint.allocate(1,usize,1,usize);
              }
            }
          }
          else
          {
            if (sparse_hessian_flag==0)
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

      if (hesstype==2 && (num_importance_samples>0 || use_gauss_hermite>0))
      {
        const ivector & itmp=(*num_local_re_array)(1,num_separable_calls);
        const ivector & itmpf=(*num_local_fixed_array)(1,num_separable_calls);

        // ****************************************************
        // ****************************************************
        if (antiflag>0)
        {
          // generate antithetical rv's
          generate_antithetical_rvs();
        }
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

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::allocate_block_diagonal_stuff(void)
{
  const ivector & itmp=(*num_local_re_array)(1,num_separable_calls);
  const ivector & itmpf=(*num_local_fixed_array)(1,num_separable_calls);

  // ****************************************************
  // ****************************************************
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

/**
 * Description not yet available.
 * \param
 */
void save_number_of_local_effects(int num_separable_calls, 
  ivector ** num_local_re_array, ivector ** num_local_fixed_array,
  int num_local_re,int num_fixed_effects)
  //ivector& lre_index,ivector& lfe_index)
{
  if (*num_local_re_array==0)
  {
    *num_local_re_array=new ivector(1,1000);
    if (*num_local_re_array==0)
    {
      cerr << "error allocating ivector" << endl;
      ad_exit(1);
    }
  }

  if (num_separable_calls> (*num_local_re_array)->indexmax())
  {
    if (num_separable_calls != (*num_local_re_array)->indexmax()+1)
    {
      cerr << "this can't happen" << endl;
      ad_exit(1);
    }
    int old_max=(*num_local_re_array)->indexmax();
    int new_max=old_max+100+10*sqrt(double(old_max));
    ivector tmp(1,old_max);
    tmp=(**num_local_re_array);
    (*num_local_re_array)=new ivector(1,new_max);
  
    delete *num_local_re_array;
    *num_local_re_array=new ivector(1,new_max);
    if (*num_local_re_array==0)
    {
      cerr << "error allocating ivector" << endl;
      ad_exit(1);
    }
    (**num_local_re_array)(1,old_max)=tmp;
  }
  (**num_local_re_array)(num_separable_calls)=num_local_re;

 //***********************************************************
 //***********************************************************
 //***********************************************************
 //***********************************************************

  if (*num_local_fixed_array==0)
  {
    *num_local_fixed_array=new ivector(1,1000);
    if (*num_local_fixed_array==0)
    {
      cerr << "error allocating ivector" << endl;
      ad_exit(1);
    }
  }

  if (num_separable_calls> (*num_local_fixed_array)->indexmax())
  {
    if (num_separable_calls != (*num_local_fixed_array)->indexmax()+1)
    {
      cerr << "this can't happen" << endl;
      ad_exit(1);
    }
    int old_max=(*num_local_fixed_array)->indexmax();
    int new_max=old_max+100+10*sqrt(double(old_max));
    ivector tmp(1,old_max);
    tmp=(**num_local_fixed_array);
    (*num_local_fixed_array)=new ivector(1,new_max);
  
    delete *num_local_fixed_array;
    *num_local_fixed_array=new ivector(1,new_max);
    if (*num_local_fixed_array==0)
    {
      cerr << "error allocating ivector" << endl;
      ad_exit(1);
    }
    (**num_local_fixed_array)(1,old_max)=tmp;
  }
  (**num_local_fixed_array)(num_separable_calls)=num_fixed_effects;
}


/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  do_separable_stuff_hessian_type_information(void)
{
  df1b2_gradlist::set_no_derivatives();

  imatrix& list=*funnel_init_var::plist;
  int num_local_re=0;
  int num_fixed_effects=0;

  int i;
  ivector lre_index(1,funnel_init_var::num_active_parameters);
  ivector lfe_index(1,funnel_init_var::num_active_parameters);

  for (i=1;i<=funnel_init_var::num_active_parameters;i++)
  {
    if (list(i,1)>xsize) 
    {
      lre_index(++num_local_re)=i;
    }
    else if (list(i,1)>0) 
    {
      lfe_index(++num_fixed_effects)=i;
    }
  }
  
  //if (num_local_re > 0)
  {
    int j;
    switch(hesstype)
    {
    case 3:
      num_separable_calls++; 
      save_number_of_local_effects(num_separable_calls,
        &num_local_re_array,&num_local_fixed_array,num_local_re,
        num_fixed_effects); //,lre_index,lfe_index);
      for (i=1;i<=num_local_re;i++)
      {
        int lrei=lre_index(i);
        for (j=1;j<=num_local_re;j++)
        {
          int lrej=lre_index(j);
          int i1=list(lrei,1)-xsize;
          int j1=list(lrej,1)-xsize;
          if (i1>=j1) 
          {
            //(*bHess)(i1,j1)+=locy(i2).u_bar[j2-1];
            int w=i1-j1+1;
            if (bw<w) bw=w;
          }
        }
      }

      if (sparse_hessian_flag)
      {
        if (allocated(Hess))
        {
          Hess.deallocate();
         /* 
          if (Hess.indexmax() !=usize)
          {
            Hess.deallocate();
            Hess.allocate(1,usize,1,usize);
            Hess.initialize();
          }
          */
        }
       /*
        else
        {
          Hess.allocate(1,usize,1,usize);
          Hess.initialize();
        }
        */
        int dim= num_local_re*num_local_re;
        imatrix tmp(1,2,1,dim);
          
        int ii=0;
        for (i=1;i<=num_local_re;i++)
        {
          int lrei=lre_index(i);
          for (j=1;j<=num_local_re;j++)
          {
            int lrej=lre_index(j);
            int i1=list(lrei,1)-xsize;
            int j1=list(lrej,1)-xsize;
            if (i1<=0)
            {
              cout << "cant happen?" << endl;
            }
            if (i1<=j1) 
            {
              //Hess(i1,j1)=1;
              ii++;
              tmp(1,ii)=i1;
              tmp(2,ii)=j1;
              //(*triplet_information)(1,num_separable_calls)=i1;
              //(*triplet_information)(2,num_separable_calls)=j1;
            }
          }
        }

        if (allocated((*triplet_information)(num_separable_calls)))
        {
          (*triplet_information)(num_separable_calls).deallocate();
        }
        if (ii>0)
        {
          (*triplet_information)(num_separable_calls).allocate(1,2,1,ii);
          (*triplet_information)(num_separable_calls)(1)=tmp(1)(1,ii);
          (*triplet_information)(num_separable_calls)(2)=tmp(2)(1,ii);
        }
      }
    }
  } 
  if (derindex)
  {
    if (num_separable_calls> derindex->indexmax())
    {
       cerr << "Need to increase the maximum number of separable calls allowed"
            << " to at least " << num_separable_calls 
            << endl << "Current value is " <<  derindex->indexmax() << endl;
       cerr << "Use the -ndi N command line option" << endl;
       ad_exit(1);
    }
       
    if (allocated((*derindex)(num_separable_calls)))
      (*derindex)(num_separable_calls).deallocate();
    (*derindex)(num_separable_calls).allocate(1,num_local_re);
    for (i=1;i<=num_local_re;i++)
    {
      int lrei=lre_index(i);
      int i1=list(lrei,1)-xsize;
      //int i1=list(lrei,1);
      (*derindex)(num_separable_calls)(i)=i1;
    }
  }

  f1b2gradlist->reset();
  f1b2gradlist->list.initialize();
  f1b2gradlist->list2.initialize();
  f1b2gradlist->list3.initialize();
  f1b2gradlist->nlist.initialize();
  f1b2gradlist->nlist2.initialize();
  f1b2gradlist->nlist3.initialize();
  funnel_init_var::num_vars=0; 
  funnel_init_var::num_active_parameters=0; 
  funnel_init_var::num_inactive_vars=0; 
}

/**
 * Description not yet available.
 * \param
 */
imatrix laplace_approximation_calculator::check_sparse_matrix_structure(void)
{
  int i,ii;
  ivector rowsize(1,usize);
  rowsize.initialize();

  imatrix tmp(1,usize,1,usize);
  tmp.initialize();
  for (ii=1;ii<=num_separable_calls;ii++)
  {
    if (allocated((*derindex)(ii)))
    {
      ivector   iv = sort((*derindex)(ii));
      int n=iv.indexmax();
      if (n>1)                     // so we have off diagonal elements
      { 
        for (int i=1;i<=n;i++)
        {
          int row=iv(i);
          for (int j=1;j<=n;j++)
          {
            if (i != j)
            {
              int col=iv(j);
              int  foundmatch=0;
              for (int k=1;k<=rowsize(row);k++)
              {
                if (tmp(row,k)==col) 
                {
                  foundmatch=1;
                  break;
                }
              }
              if (foundmatch==0)  // add a new element to tmp(row)
              {
                rowsize(row)++;
                if (rowsize(row)> tmp(row).indexmax())
                {
                  tmp(row).reallocate(2);  // double the size
                }
                tmp(row,rowsize(row))=col;
              }
            }
          }
        }
      }
    }
  }     
  imatrix M(1,usize,1,rowsize);
  ofstream ofs("sparseness.info");
  ofs << "# Number of parameters" << endl;
  ofs << usize << endl;
  ofs << "# Number of off diagonal elements in each row" << endl;
  ofs << rowsize << endl;
  ofs << "# The nonempty rows of M" << endl;
  for (i=1;i<=usize;i++)
  {
    if (rowsize(i)>0)
    {
      M(i)=sort(tmp(i)(1,rowsize(i)));
      ofs << setw(4) << M(i) << endl;
    }
  }
  exit(1);
  return M;
}      
      


#endif // if defined(USE_LAPLACE)
