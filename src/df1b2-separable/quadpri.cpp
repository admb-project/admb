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
#include <df1b2fnl.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

int quadratic_prior::in_qp_calculations=0;

// this should be a resizeable array
quadratic_prior * quadratic_prior::ptr[100];

int quadratic_prior::num_quadratic_prior=0;
const int quadratic_prior::max_num_quadratic_prior=100;

/**
 * Description not yet available.
 * \param
 */
 void quadratic_prior::get_M_calculations(void)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     //if (ptr[i]->get_num_active_parameters()>0)
     {
       ptr[i]->get_cM();
     }
   }
 }

/**
 * Description not yet available.
 * \param
 */
dvector evaluate_function_with_quadprior(const dvector& x,int usize,
  function_minimizer * pfmin)
{
  int xsize = initial_params::nvarcalc();
  dvector g(1,xsize);
  gradcalc(0,g);
  //double f=0.0;
  independent_variables u(1,xsize);
  u=x;
  dvariable vf=0.0;
  initial_params::reset(dvar_vector(u));
  //vf=0.0;
  dvar_matrix Hess_all(1,usize,1,usize);
  *objective_function_value::pobjfun=0.0;
  // so that dvar_matrix Hessian contributions are calculated
  laplace_approximation_calculator::where_are_we_flag=3;
  pfmin->AD_uf_inner();
  if ( quadratic_prior::get_num_quadratic_prior()>0)
  {
    quadratic_prior::get_M_calculations();
  }
  laplace_approximation_calculator::where_are_we_flag=0;

  *objective_function_value::pobjfun=0.0;
  Hess_all=pfmin->lapprox->Hess;
  for (int i=0;i<quadratic_prior::get_num_quadratic_prior();i++)
  {
    //Hess_all += quadratic_prior::get_ptr(i)->get_vHessian();
    int nv=df1b2quadratic_prior::get_ptr(i)->get_num_active_parameters();
    if (nv>0)
      quadratic_prior::get_ptr(i)->get_vHessian(Hess_all,xsize);
    else
      quadratic_prior::get_ptr(i)->get_cHessian(Hess_all,xsize);
  }
  int sgn;
  vf=0.5*ln_det(Hess_all,sgn);
  gradcalc(xsize,g);
  return g;
}

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::add_to_list(void)
  {
    if (num_quadratic_prior>=max_num_quadratic_prior) ad_exit(1);
    xmyindex=num_quadratic_prior;
    ptr[num_quadratic_prior++]=this;
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable quadratic_prior::get_function(void)
  {
    return (*pu)*((*pMinv)*(*pu));
  }

/**
 * Description not yet available.
 * \param
 */
  dvar_matrix quadratic_prior::get_Hessian(void)
  {
    return *pMinv;
  }

/**
 * Description not yet available.
 * \param
 */
  int quadratic_prior::get_offset(int xs)
  {
    df1b2_init_vector * fpu=df1b2quadratic_prior::ptr[get_myindex()]->pu;
    int mmin=(*fpu)(fpu->indexmin()).get_ind_index();
    return mmin-xs-1;
  }
  //dmatrix quadratic_prior::get_cHessian(void)

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::get_cHessian(dmatrix H,int xsize)
  {
    int offset=get_offset(xsize);
    int imin=pMinv->indexmin();
    int imax=pMinv->indexmax();
    if (offset==0)
    {
      int i,j;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=(*pMinv)(i,j);
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=2.0*(*pMinv)(i,j);
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=2.0*(*pMinv)(i,j);
         break;
      default:
         cerr << "Illegal value in switch statement" << endl;
         ad_exit(1);
      }
    }
    else
    {
      int i,j;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=(*pMinv)(i,j);
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*(*pMinv)(i,j);
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*(*pMinv)(i,j);
         break;
      default:
         cerr << "Illegal value in switch statement" << endl;
         ad_exit(1);
      }
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::get_cHessian(dvar_matrix H,int xsize)
  {
    int offset=get_offset(xsize);
    int imin=pMinv->indexmin();
    int imax=pMinv->indexmax();
    if (offset==0)
    {
      int i,j;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=(*pMinv)(i,j);
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=2.0*(*pMinv)(i,j);
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=2.0*(*pMinv)(i,j);
         break;
      default:
         cerr << "Illegal value in switch statement" << endl;
         ad_exit(1);
      }
    }
    else
    {
      int i,j;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=(*pMinv)(i,j);
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*(*pMinv)(i,j);
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*(*pMinv)(i,j);
         break;
      default:
         cerr << "Illegal value in switch statement" << endl;
         ad_exit(1);
      }
    }
  }

/**
 * Description not yet available.
 * \param
 */
void quadratic_prior::get_vHessian(dvar_matrix H,int xsize)
{
  if (!dfpMinv)
  {
      cerr << "This can't happen" << endl;
      ad_exit(1);
  }
  else
  {
    int imin=dfpMinv->indexmin();
    int imax=dfpMinv->indexmax();
    int offset=get_offset(xsize);
    if (offset==0)
    {
      switch(old_style_flag)
      {
      case 0:
        for (int i=imin;i<=imax;i++)
          for (int j=imin;j<=imax;j++)
            H(i,j)+=(*dfpMinv)(i,j);
        break;
      case 1:
        for (int i=imin;i<=imax;i++)
          for (int j=imin;j<=imax;j++)
            H(i,j)+=2.0*(*dfpMinv)(i,j);
        break;
      case 2:
        for (int i=imin;i<=imax;i++)
          for (int j=imin;j<=imax;j++)
            H(i,j)+=2.0*(*dfpMinv)(i,j);
         break;
      default:
         cerr << "Illegal valueinswitch statement" << endl;
         ad_exit(1);
      }
    }
    else
    {
      switch(old_style_flag)
      {
      case 0:
        for (int i=imin;i<=imax;i++)
          for (int j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=(*dfpMinv)(i,j);
        break;
      case 1:
        for (int i=imin;i<=imax;i++)
          for (int j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*(*dfpMinv)(i,j);
        break;
      case 2:
        for (int i=imin;i<=imax;i++)
          for (int j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*(*dfpMinv)(i,j);
         break;
      default:
         cerr << "Illegal valueinswitch statement" << endl;
         ad_exit(1);
      }
    }
  }
}

 /*
  dvar_matrix quadratic_prior::get_vHessian(void)
  {
    return *dfpMinv;
    //return value(*pMinv);
  }
 */

/**
 * Description not yet available.
 * \param
 */
   void quadratic_prior::get_cHessian_from_vHessian(dmatrix H,int xs)
  {
    int offset=get_offset(xs);
    int imin=dfpMinv->indexmin();
    int imax=dfpMinv->indexmax();
    if (offset==0)
    {
      int i,j;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=value((*dfpMinv)(i,j));
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=2.0*value((*dfpMinv)(i,j));
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(i,j)+=2.0*value((*dfpMinv)(i,j));
        break;
         break;
      default:
         cerr << "Illegal valueinswitch statement" << endl;
         ad_exit(1);
      }
    }
    else
    {
      int i,j;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=value((*dfpMinv)(i,j));
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*value((*dfpMinv)(i,j));
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          for (j=imin;j<=imax;j++)
            H(offset+i,offset+j)+=2.0*value((*dfpMinv)(i,j));
         break;
      default:
         cerr << "Illegal valueinswitch statement" << endl;
         ad_exit(1);
      }
    }
    //return value(*dfpMinv);
  }

/**
 * Description not yet available.
 * \param
 */
  dvar_vector quadratic_prior::get_gradient(void)
  {
    return ((*pMinv)*(*pu));
  }

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::get_cgradient(dvector g,int xs)
  {
    int offset=get_offset(xs);
    dvector tg=((*pMinv)*value(*pu));
    int imin=pMinv->indexmin();
    int imax=pMinv->indexmax();
    if (offset==0)
    {
      int i;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          g(i)+=tg(i);
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          g(i)+=2.0*tg(i);
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          g(i)+=2.0*tg(i);
        break;
      default:
        cerr << "Illegal valueinswitch statement" << endl;
        ad_exit(1);
      }
    }
    else
    {
      int i;
      switch(old_style_flag)
      {
      case 0:
        for (i=imin;i<=imax;i++)
          g(offset+i)+=tg(i);
        break;
      case 1:
        for (i=imin;i<=imax;i++)
          g(offset+i)+=2.0*tg(i);
        break;
      case 2:
        for (i=imin;i<=imax;i++)
          g(offset+i)+=2.0*tg(i);
        break;
      default:
        cerr << "Illegal valueinswitch statement" << endl;
        ad_exit(1);
      }
    }
    //return ((*pMinv)*value(*pu));
  }

/**
 * Description not yet available.
 * \param
 */
  quadratic_prior::quadratic_prior(void)
  {
    pMinv=0;
    dfpMinv=0;
    pu=0;
    add_to_list();
  }

/**
 * Description not yet available.
 * \param
 */
  quadratic_prior::~quadratic_prior(void)
  {
    if (pMinv) delete pMinv;
    pMinv=0;
    if (pu) delete pu;
    pu=0;
    if (dfpMinv) delete pMinv;
    dfpMinv=0;
  }

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::allocate( const dvar_vector & _u,const char * s)
  {
    allocate(_u);
  }

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::allocate(const dvar_vector & _u)
  {
    if (!allocated(_u))
    {
      cerr << "You must put random effects vector before"
       " quadtratic prior in the TPL file" << endl;
      ad_exit(1);
    }
    pu = new dvar_vector((dvar_vector&)(_u));
  }

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::allocate(const dvar_matrix & _M,
    const dvar_vector & _u,const char * s)
  {
    allocate(_M,_u);
  }

/**
 * Description not yet available.
 * \param
 */
  void quadratic_prior::allocate(const dvar_matrix & _M,
    const dvar_vector & _u)
  {
    pMinv =new dmatrix(value(inv(_M)));
    pu = new dvar_vector((dvar_vector&)(_u));
  }

/**
 * Description not yet available.
 * \param
 */
 dvariable quadratic_prior::get_quadratic_priors(void)
 {
   dvariable f=0.0;
   for (int i=0;i<num_quadratic_prior;i++)
   {
     f+=ptr[i]->get_function();
   }
   return f;
 }

/**
 * Description not yet available.
 * \param
 */
 void quadratic_prior::get_cgradient_contribution(dvector g,int xs)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     ptr[i]->get_cgradient(g,xs);
    /*
     if (old_style_flag)
     {
       return ptr[i]->get_cgradient();
     }
     else
     {
       return ptr[i]->get_cgradient();
     }
    */
   }
   //return f;
 }
/*
 dvar_vector quadratic_prior::get_gradient_contribution(void)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     return ptr[i]->get_gradient();
   }
   //return f;
 }
*/

/**
 * Description not yet available.
 * \param
 */
 void quadratic_prior::get_cHessian_contribution(dmatrix H,int xsize)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     if (!ptr[i])
     {
       cerr << "ptr["<<i<<"] = 0 in"
         " quadratic_prior::get_cHessian_contribution" << endl;
       ad_exit(1);
     }
     if (!ptr[i]->pMinv)
     {
       cerr << "ptr["<<i<<"]->pMinv = 0 in"
         " quadratic_prior::get_cHessian_contribution" << endl;
       ad_exit(1);
     }
     if (!allocated(*(ptr[i]->pMinv)))
     {
       cerr << "*ptr["<<i<<"] is unallocated in"
         " quadratic_prior::get_cHessian_contribution" << endl;
       ad_exit(1);
     }
     ptr[i]->get_cHessian(H,xsize);
    /*
     if (old_style_flag)
     {
       return 2.0*ptr[i]->get_cHessian();
     }
     else
     {
       return ptr[i]->get_cHessian();
     }
    */
   }
   //return f;
 }

/**
 * Description not yet available.
 * \param
 */
 void quadratic_prior::get_vHessian_contribution(dvar_matrix H,int xs)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     ptr[i]->get_vHessian(H,xs);
    /*
     if (old_style_flag)
     {
       return 2.0*ptr[i]->get_vHessian();
     }
     else
     {
       return ptr[i]->get_vHessian();
     }
    */
   }
   //return f;
 }
 /*
 dvar_matrix quadratic_prior::get_Hessian_contribution(void)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     return ptr[i]->get_Hessian();
   }
   //return f;
 }
 */

/**
 * Description not yet available.
 * \param
 */
void quadratic_prior::get_cHessian_contribution_from_vHessian(dmatrix Hess,
  int xsize)
 {
   for (int i=0;i<num_quadratic_prior;i++)
   {
     int nv=df1b2quadratic_prior::get_ptr(i)->
       get_num_active_parameters();
     if (nv)
       ptr[i]->get_cHessian_from_vHessian(Hess,xsize);
     else
       ptr[i]->get_cHessian(Hess,xsize);
   }
   //return f;
 }

/**
 * Description not yet available.
 * \param
 */
 void quadratic_prior::operator = (const dvar_matrix & _M)
 {
   dvariable lndet;
   dvariable sgn;

   switch (quadratic_prior::old_style_flag)
   {
   case 0:
     *objective_function_value::pobjfun+=0.5*(*pu)*(solve(_M,*pu,lndet,sgn));
     *objective_function_value::pobjfun+=0.5*lndet;
     //*objective_function_value::pobjfun+=0.5*(*pu)*(solve(_M,*pu));
     //*objective_function_value::pobjfun+=0.5*ln_det(_M);
     break;
   case 1:
     *objective_function_value::pobjfun+=(*pu)*(solve(_M,*pu));
     break;
   case 2:
     *objective_function_value::pobjfun+=(*pu) * ( _M * (*pu) );
     break;
   default:
     cerr << "Illegal value for quadratic_prior::old_style_flag"
          << endl;
     ad_exit(1);
   }
   if (pMinv)
   {
     delete pMinv;
     pMinv=0;
   }
   if (dfpMinv)
   {
     delete dfpMinv;
     dfpMinv=0;
   }
   switch (quadratic_prior::old_style_flag)
   {
   case 0:
   case 1:
     if (laplace_approximation_calculator::where_are_we_flag==2)
     {
       pMinv = new dmatrix(inv(value(_M)));
       if (pMinv==0)
       {
         cerr << "Error allocating dmatrix" << endl;
         ad_exit(1);
       }
     }
     if (laplace_approximation_calculator::where_are_we_flag==3)
     {
       dfpMinv = new dvar_matrix(inv(_M));
       if (dfpMinv==0)
       {
         cerr << "Error allocating dvar_matrix" << endl;
         ad_exit(1);
       }
     }
     break;
   case 2:
     if (laplace_approximation_calculator::where_are_we_flag==2)
     {
       pMinv = new dmatrix(value(_M));
       if (pMinv==0)
       {
         cerr << "Error allocating dmatrix" << endl;
         ad_exit(1);
       }
     }
     if (laplace_approximation_calculator::where_are_we_flag==3)
     {
       int nv =
         df1b2quadratic_prior::get_ptr(xmyindex)->get_num_active_parameters();
       //if (nv==0)
       if (nv!=0)
       {
         dfpMinv = new dvar_matrix(_M);
         if (dfpMinv==0)
         {
           cerr << "Error allocating dvar_matrix" << endl;
           ad_exit(1);
         }
       }
       else
       {
         pMinv = new dmatrix(value(_M));
         if (pMinv==0)
         {
           cerr << "Error allocating dmatrix" << endl;
           ad_exit(1);
         }
       }
     }
     break;
   default:
     cerr << "Illegal value for quadratic_prior::old_style_flag"
          << endl;
     ad_exit(1);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void quadratic_prior::operator = (const dmatrix & _M)
 {
   dvariable lndet;
   dvariable sgn;

   switch (quadratic_prior::old_style_flag)
   {
   case 0:
     cerr << " can't get here " << endl;
     ad_exit(1);
     break;
   case 1:
     cerr << " can't get here " << endl;
     ad_exit(1);
     break;
   case 2:
     *objective_function_value::pobjfun+=(*pu) * ( _M * (*pu) );
     break;
   default:
     cerr << "Illegal value for quadratic_prior::old_style_flag"
          << endl;
     ad_exit(1);
   }
   if (pMinv)
   {
     delete pMinv;
     pMinv=0;
   }
   if (dfpMinv)
   {
     delete dfpMinv;
     dfpMinv=0;
   }
   switch (quadratic_prior::old_style_flag)
   {
   case 0:
   case 1:
     cerr << " can't get here " << endl;
     ad_exit(1);
     break;
   case 2:
     if (laplace_approximation_calculator::where_are_we_flag==2 ||
       laplace_approximation_calculator::where_are_we_flag==3)
     {
       pMinv = new dmatrix(_M);
       if (pMinv==0)
       {
         cerr << "Error allocating dmatrix" << endl;
         ad_exit(1);
       }
     }
     break;
   default:
     cerr << "Illegal value for quadratic_prior::old_style_flag"
          << endl;
     ad_exit(1);
   }
 }

/**
 * Description not yet available.
 * \param
 */
normal_quadratic_prior::normal_quadratic_prior(void)
{
  set_old_style_flag();
}

/**
 * Description not yet available.
 * \param
 */
void normal_quadratic_prior::set_old_style_flag(void)
{
  old_style_flag=0;
}

/**
 * Description not yet available.
 * \param
 */
void normal_quadratic_prior::operator = (const dvar_matrix & M)
{
  quadratic_prior::operator = (M);
}

/**
 * Description not yet available.
 * \param
 */
quadratic_re_penalty::quadratic_re_penalty(void)
{
  set_old_style_flag();
}

/**
 * Description not yet available.
 * \param
 */
void quadratic_re_penalty::set_old_style_flag(void)
{
  old_style_flag=2;
}

/**
 * Description not yet available.
 * \param
 */
void quadratic_re_penalty::operator = (const dvar_matrix & M)
{
  quadratic_prior::operator = (M);
}

/**
 * Description not yet available.
 * \param
 */
void quadratic_re_penalty::operator = (const dmatrix & M)
{
  quadratic_prior::operator = (M);
}

/**
 * Description not yet available.
 * \param
 */
constant_quadratic_re_penalty::constant_quadratic_re_penalty(void)
{
  set_old_style_flag();
}

/**
 * Description not yet available.
 * \param
 */
void constant_quadratic_re_penalty::set_old_style_flag(void)
{
  old_style_flag=2;
}

/**
 * Description not yet available.
 * \param
 */
void constant_quadratic_re_penalty::operator = (const dmatrix & M)
{
  quadratic_prior::operator = (M);
}
