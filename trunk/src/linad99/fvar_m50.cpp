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
#include <fvar.hpp>


void dfcholeski_decomp_banded_positive(void);

/**
 * Description not yet available.
 * \param
 */
banded_lower_triangular_dvar_matrix choleski_decomp_positive(
  const banded_symmetric_dvar_matrix& MM, double eps,
  dvariable& _fpen)
{
  // kludge to deal with constantness
  banded_symmetric_dvar_matrix& M = (banded_symmetric_dvar_matrix&) MM;
  int n=M.indexmax();

  int bw=M.bandwidth();
  banded_lower_triangular_dvar_matrix L(1,n,bw);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  double tmp;
  double ptmp;
  double fpen=0.0;
  ptmp=posfun(value(M(1,1)),eps,fpen);
  L.elem_value(1,1)=sqrt(ptmp);
  for (i=2;i<=bw;i++)
  {
    L.elem_value(i,1)=value(M(i,1))/L.elem_value(1,1);
  }

  for (i=2;i<=n;i++)
  {
    int jmin=admax(2,i-bw+1);
    for (j=jmin;j<=i-1;j++)
    {
      tmp=value(M(i,j));
      int kmin=max(1,j-bw+1,i-bw+1);
      for (k=kmin;k<=j-1;k++)
      {
        tmp-=L.elem_value(i,k)*L.elem_value(j,k);
      }
      L.elem_value(i,j)=tmp/L.elem_value(j,j);
    }
    tmp=value(M(i,i));
    int kmin=admax(i-bw+1,1);
    for (k=kmin;k<=i-1;k++)
    {
      tmp-=L.elem_value(i,k)*L.elem_value(i,k);
    }
    ptmp=posfun(tmp,eps,fpen);
    L.elem_value(i,i)=sqrt(ptmp);
  }


  if (fpen>0)
    cout << "fpen = " << fpen << endl;

   value(_fpen)=fpen;
  //banded_lower_triangular_dvar_matrix vc=nograd_assign(L);
  save_identifier_string("qs");
  _fpen.save_prevariable_position();
  save_double_value(eps);
  save_identifier_string("rs");
  L.save_dvar_matrix_position();
  save_identifier_string("rt");
  MM.save_dvar_matrix_value();
  save_identifier_string("rl");
  MM.save_dvar_matrix_position();
  save_identifier_string("ro");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfcholeski_decomp_banded_positive);

  return L;
}

/**
 * Description not yet available.
 * \param
 */
void dfcholeski_decomp_banded_positive(void)
{
  verify_identifier_string("ro");
  dvar_matrix_position MMpos=restore_dvar_matrix_position();
  verify_identifier_string("rl");
  banded_symmetric_dmatrix M=
    restore_banded_symmetric_dvar_matrix_value(MMpos);
  verify_identifier_string("rt");
  dvar_matrix_position vcpos=restore_dvar_matrix_position();
  verify_identifier_string("rs");
  banded_lower_triangular_dmatrix dfL=
    restore_banded_lower_triangular_dvar_matrix_derivatives(vcpos);
  double eps=restore_double_value();
  prevariable_position fpenpos=restore_prevariable_position();
  verify_identifier_string("qs");
  double dfpen=restore_prevariable_derivative(fpenpos);

  int n=M.indexmax();
  int bw=M.bandwidth();

  double fpen=0.0;
  banded_lower_triangular_dmatrix L(1,n,bw);
  banded_lower_triangular_dmatrix tmp1(1,n,bw);
  banded_lower_triangular_dmatrix dftmp1(1,n,bw);
  banded_symmetric_dmatrix dfM(1,n,bw);
  dvector tmp(1,n);
  dvector ptmp(1,n);
  dvector dftmp(1,n);
  dvector dfptmp(1,n);
  tmp.initialize();
  ptmp.initialize();
  tmp1.initialize();
  dftmp.initialize();
  dfptmp.initialize();
  dftmp1.initialize();
  dfM.initialize();
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  ptmp(1)=posfun(M(1,1),eps,fpen);
  L(1,1)=sqrt(ptmp(1));
  L(1,1)=sqrt(M(1,1));
  for (i=2;i<=bw;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    int jmin=admax(2,i-bw+1);
    for (j=jmin;j<=i-1;j++)
    {
      tmp1(i,j)=M(i,j);
      int kmin=max(1,j-bw+1,i-bw+1);
      for (k=kmin;k<=j-1;k++)
      {
        tmp1(i,j)-=L(i,k)*L(j,k);
      }
      L(i,j)=tmp1(i,j)/L(j,j);
    }
    tmp(i)=M(i,i);
    int kmin=admax(i-bw+1,1);
    for (k=kmin;k<=i-1;k++)
    {
      tmp(i)-=L(i,k)*L(i,k);
    }
    double pen;
    ptmp(i)=posfun(tmp(i),eps,pen);
    L(i,i)=sqrt(ptmp(i));
  }

  dfptmp.initialize();

  for (i=n;i>=2;i--)
  {
    //L(i,i)=sqrt(ptmp(i));
    dfptmp(i)+=dfL(i,i)/(2.0*L(i,i));
    dfL(i,i)=0.0;
    // ptmp(i)=posfun(tmp(i),eps);
    dftmp(i)=dfptmp(i)*dfposfun(tmp(i),eps);
    dftmp(i)+=dfpen*dfposfun1(tmp(i),eps);
    dfptmp(i)=0.0;

    int kmin=admax(i-bw+1,1);
    for (k=i-1;k>=kmin;k--)
    {
      //tmp(i)-=L(i,k)*L(i,k);
      dfL(i,k)-=2.*dftmp(i)*L(i,k);
    }
    //tmp(i)=M(i,i);
    dfM(i,i)+=dftmp(i);
    dftmp(i)=0.0;
    int jmin=admax(2,i-bw+1);
    for (j=i-1;j>=jmin;j--)
    {
      //L(i,j)=tmp1(i,j)/L(j,j);
      double linv=1./L(j,j);
      dftmp1(i,j)+=dfL(i,j)*linv;
      dfL(j,j)-=dfL(i,j)*tmp1(i,j)*linv*linv;
      dfL(i,j)=0.0;
      kmin=max(1,j-bw+1,i-bw+1);
      for (k=j-1;k>=kmin;k--)
      {
        //tmp(i,j)-=L(i,k)*L(j,k);
        dfL(i,k)-=dftmp1(i,j)*L(j,k);
        dfL(j,k)-=dftmp1(i,j)*L(i,k);
      }
      //tmp(i,j)=M(i,j);
      dfM(i,j)+=dftmp1(i,j);
      dftmp1(i,j)=0.0;
    }
  }
  double linv=1./L(1,1);
  for (i=bw;i>=2;i--)
  {
    //L(i,1)=M(i,1)/L(1,1);
    dfM(i,1)+=dfL(i,1)*linv;
    dfL(1,1)-=dfL(i,1)*M(i,1)*linv*linv;
    dfL(i,1)=0.0;
  }
  //L(1,1)=sqrt(M(1,1));
  //dfM(1,1)+=dfL(1,1)/(2.*L(1,1));

  //L(1,1)=sqrt(ptmp(1));
  dfptmp(1)+=dfL(1,1)/(2.*L(1,1));
  dfL(1,1)=0.0;
  //ptmp(1)=posfun(M(1,1),eps,fpen);
  dfM(1,1)+=dfptmp(1)*dfposfun(M(1,1),eps);
  dfM(1,1)+=dfpen*dfposfun1(M(1,1),eps);;
  dfptmp(1)=0.0;

  dfM.save_dmatrix_derivatives(MMpos);
}
