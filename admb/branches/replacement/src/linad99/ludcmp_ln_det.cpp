#include <ludcmp.hpp>

cltudecomp xludecomp_pivot(const dvar_matrix & M);

dvariable ln_det(const dvar_matrix& a)
{
  int sgn;
  return ln_det(a,sgn);
}

  static void df_my_ln_det(void);

  dvariable my_ln_det(const dvar_matrix & M,int & sign)
  {
    cltudecomp clu1=xludecomp_pivot(M);

    sign=clu1.get_sign();
    ivector index2=clu1.get_index2();
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    double lndet=0.0;
    dmatrix & gamma=clu1.get_U();
    dmatrix & alpha=clu1.get_L();

    // only need to save the diagonal of gamma
    for (int i=mmin;i<=mmax;i++)
    {
      if (gamma(i,i)<0)
      {
        sign=-sign;
        lndet+=log(-gamma(i,i));
      }
      else
      {
        lndet+=log(gamma(i,i));
      }
    }
    dvariable vldet=nograd_assign(lndet);  
      
    save_identifier_string("OT");
    vldet.save_prevariable_position();
    gradient_structure::GRAD_STACK1->
    set_gradient_stack(df_my_ln_det);
    return vldet;
  }
  static void df_my_ln_det(void)
  {
    double dflndet=restore_prevariable_derivative();
    verify_identifier_string("OT");
  
    // adjoint code for ln_det calc

    cltudecomp_for_adjoint clu1;
    
    clu1.ludecomp_pivot_for_adjoint_1();
    cltudecomp dfclu1=clu1.get_dfclu();
    dmatrix_for_adjoint gamma=clu1.get_U();
    dmatrix dfgamma=dfclu1.get_U();
    dmatrix dfalpha=dfclu1.get_L();
    dfalpha.initialize();
    dfgamma.initialize();
    int mmin=clu1.indexmin();
    int mmax=clu1.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      if (gamma(i,i)<0)
      {
        //sign=-sign;
        //lndet+=log(-gamma(i,i));
        dfgamma(i,i)=dflndet/gamma(i,i);
      }
      else
      {
        dfgamma(i,i)=dflndet/gamma(i,i);
      }
    }
    clu1.ludecomp_pivot_for_adjoint_2();
  }

dvariable ln_det(const dvar_matrix& aa,const int& _sgn)
{
  int sign =_sgn;
  dvar_matrix M = aa;
  dvariable lndet = my_ln_det(M,sign);
  return lndet;
}
