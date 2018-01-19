// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION

  init_int n			// Number of observations
  init_vector y(1,n)		// Observation vector
  init_int p			// Number of fixed effects
  init_matrix X(1,n,1,p)	// Covariate matrix for fixed effects
  init_int q			// Number of Clusters
  init_int m			// Number of random effects within clusters
  init_matrix Z(1,n,1,m)	// Covariate matrix for random effects
  init_ivector group(1,q+1)		// where the qth group ends
  init_int cor_flag
  init_int like_type_flag   // 0 bvprobit 1 bvlogit
  init_int no_rand_flag   // 0 have random effects 1 no random effects
  matrix rr(1,n,1,6)
  matrix phi(1,p,1,p)
 LOC_CALCS
  int i,j;
  phi.initialize();
  for (i=1;i<=p;i++)
  {
    phi(i,i)=1.0;
  }
 
  dmatrix trr=trans(rr);
  trr(6).fill_seqadd(1,1);
  rr=trans(trr);

  dmatrix TX(1,p,1,n);
  TX=trans(X);
  for (i=1;i<=p;i++)
  {
    double tmp=norm(TX(i));
    TX(i)/=tmp;
    phi(i)/=tmp;
    for (j=i+1;j<=p;j++)
    {
      double a=TX(j)*TX(i);
      TX(j)-=a*TX(i);
      phi(j)-=a*phi(i);
    }
  }
  X=trans(TX);

INITIALIZATION_SECTION
 tmpL 1.0
 tmpL1 0.0

PARAMETER_SECTION
 LOC_CALCS
  int rand_phase=3;
  int rand_sd_phase;
  int kludge_phase=-1;
  if (no_rand_flag==1)
  {
    rand_phase=-1;
    rand_sd_phase=-1;
  }
  else
  {
    rand_phase=2;
    rand_sd_phase=2;
  }
  int cor_phase=4;
  if (cor_flag && no_rand_flag==0)
   cor_phase=3;
  else
   cor_phase=-3;
  global_rand_phase=rand_phase;
 END_CALCS
  
  init_vector b(1,p,1)     	// Fixed effects
  sdreport_vector real_b(1,p)     
  !! int mm = (m*(m+1))/2;
  !! int m1 = (m*(m-1))/2;
  init_bounded_vector tmpL(1,m,-10,10.5,rand_sd_phase)	// Elements of cholesky-factor L of correlation matrix
  init_bounded_vector tmpL1(1,m1,-10,10.5,cor_phase)	// Elements of cholesky-factor L of correlation matrix

  //sdreport_number sigma                       	// sqrt(variance component)
  sdreport_matrix S(1,m,1,m)
  vector lambda(1,n)  
  init_number kkludge(kludge_phase)  

  random_effects_matrix u(1,q,1,m,rand_phase)            // Random effects
  objective_function_value g                    // Log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);


PROCEDURE_SECTION
  g=0.0;

  int i,j;
  switch(like_type_flag)
  {
  case 0:   // binomial probit
    for (j=1;j<=q;j++)
    {
      if (cor_flag)
      { 
        bin_probit(j,tmpL,tmpL1,u(j),b);
      }
      else
      { 
        bin_probit(j,tmpL,u(j),b);
      }
    }
    break;
  case 1:   // logit
    for (j=1;j<=q;j++)
    {
      if (cor_flag)
      { 
        bin_logit(j,tmpL,tmpL1,u(j),b);
      }
      else
      { 
        bin_logit(j,tmpL,u(j),b);
      }
    }
    break;
  default:
    cerr << "Illegal value for like_type_flag" << endl;
    ad_exit(1);
  }

  if (sd_phase())
  {
    real_b=b*phi;
    dvar_matrix L(1,m,1,m);
    L.initialize();
  
    if (tmpL.indexmax() != m)
    {
      cerr << "size error in get_choleski" << endl;
    }
    int ii=1;
    if (cor_flag)
    {
      int ii=1;
      L(1,1)=1;
      for (i=1;i<=m;i++)
      {
        L(i,i)=1;
        for (int j=1;j<i;j++)
        {
          L(i,j)=tmpL1(ii++);
        }
        L(i)(1,i)/=norm(L(i)(1,i));
      }
      for (i=1;i<=m;i++)
      {
        L(i)*=exp(tmpL(i));
      }
    }
    else
    {
      for (i=1;i<=m;i++)
      {
        L(i,i)=exp(tmpL(i));
      }
    }
    S=L*trans(L);
  }

  if (cor_flag)
    f0(tmpL,tmpL1,m,b,kkludge);
  else
    f0(tmpL,m,b,kkludge);


SEPARABLE_FUNCTION void bin_probit(int _i,const dvar_vector& tmpL,const dvar_vector& tmpL1,const dvar_vector& ui,const dvar_vector& b)
  dvar_matrix L(1,m,1,m);
  L.initialize();
  int i,j;

  if (tmpL.indexmax() != m)
  {
    cerr << "size error in get_choleski" << endl;
  }

  if (cor_flag)
  {
    int ii=1;
    L(1,1)=1;
    for (i=1;i<=m;i++)
    {
      L(i,i)=1;
      for (int j=1;j<i;j++)
      {
        L(i,j)=tmpL1(ii++);
      }
      L(i)(1,i)/=norm(L(i)(1,i));
    }
    for (i=1;i<=m;i++)
    {
      L(i)*=exp(tmpL(i));
    }
  }
  else
  {
    for (i=1;i<=m;i++)
    {
      L(i,i)=exp(tmpL(i));
    }
  }


  g+=0.5*m*log(2.0*PI)+0.5*norm2(ui);

  dvar_vector lui=L*ui;

  for (j=group(_i);j<group(_i+1);j++)
  {
    dvariable eta = X(j)*b + Z(j)*lui;
    if (y(j)==1)
    {
      g-=log(1.e-10+cumd_norm(eta));
    }
    else
    {
      g-=log(1.e-10+(1.0-cumd_norm(eta)));
    }
  }

SEPARABLE_FUNCTION void bin_probit(int _i,const dvar_vector& tmpL,const dvar_vector& ui,const dvar_vector& b)
  dvar_matrix L(1,m,1,m);
  L.initialize();
  int i,j;

  if (tmpL.indexmax() != m)
  {
    cerr << "size error in get_choleski" << endl;
  }

  for (i=1;i<=m;i++)
  {
    L(i,i)=exp(tmpL(i));
  }

  g+=0.5*m*log(2.0*PI)+0.5*norm2(ui);

  dvar_vector lui=L*ui;

  for (j=group(_i);j<group(_i+1);j++)
  {
    dvariable eta = X(j)*b + Z(j)*lui;
    if (y(j)==1)
    {
      g-=log(1.e-10+cumd_norm(eta));
    }
    else
    {
      g-=log(1.e-10+(1.0-cumd_norm(eta)));
    }
  }


SEPARABLE_FUNCTION void f0(const dvar_vector& tmpL,const dvar_vector& tmpL1,int m,const dvar_vector& b,const dvariable& kkludge)

  int i;
  // small penalty so that the Hessian is not singiular when 
  // the variance of somecompnent is 0;
  int m1=m*(m-1)/2;
  double pen=.001;
  if (last_phase()) pen=.000001;
  for (i=1;i<=m1;i++)
  {
    g+=.1*square(tmpL1(i));
  }
  for (i=1;i<=m;i++)
  {
    g+=pen*square(tmpL(i));
  }

  g+=square(kkludge);
  
SEPARABLE_FUNCTION void f0(const dvar_vector& tmpL,int m,const dvar_vector& b,const dvariable& kkludge)

  int i;
  // small penalty so that the Hessian is not singiular when 
  // the variance of somecompnent is 0;
  int m1=m*(m-1)/2;
  double pen=.01;
  if (last_phase()) pen=.00001;

  for (i=1;i<=m;i++)
  {
    g+=pen*square(tmpL(i));
  }

  g+=square(kkludge);

SEPARABLE_FUNCTION void bin_logit(int _i,const dvar_vector& tmpL,const dvar_vector& tmpL1,const dvar_vector& ui,const dvar_vector& b)
  dvar_matrix L(1,m,1,m);
  L.initialize();
  int i,j;

  if (tmpL.indexmax() != m)
  {
    cerr << "size error in get_choleski" << endl;
  }

  if (cor_flag)
  {
    int ii=1;
    L(1,1)=1;
    for (i=1;i<=m;i++)
    {
      L(i,i)=1;
      for (int j=1;j<i;j++)
      {
        L(i,j)=tmpL1(ii++);
      }
      L(i)(1,i)/=norm(L(i)(1,i));
    }
    for (i=1;i<=m;i++)
    {
      L(i)*=exp(tmpL(i));
    }
  }
  else
  {
    for (i=1;i<=m;i++)
    {
      L(i,i)=exp(tmpL(i));
    }
  }


  g+=0.5*m*log(2.0*PI)+0.5*norm2(ui);

  dvar_vector lui=L*ui;

  for (j=group(_i);j<group(_i+1);j++)
  {
    dvariable eta = X(j)*b + Z(j)*lui;
    if (value(eta)<20)
    {
      dvariable tmp=exp(eta);
      eta=tmp/(1.0+tmp);
    }
    else
    {
      dvariable tmp=exp(-eta);
      eta=1/(1.0+tmp);
    }
    if (y(j)==1)
    {
      g-=log(1.e-10+eta);
    }
    else
    {
      g-=log(1.e-10+(1.0-eta));
    }
  }
SEPARABLE_FUNCTION void bin_logit(int _i,const dvar_vector& tmpL,const dvar_vector& ui,const dvar_vector& b)
  dvar_matrix L(1,m,1,m);
  L.initialize();
  int i,j;

  if (tmpL.indexmax() != m)
  {
    cerr << "size error in get_choleski" << endl;
  }

  for (i=1;i<=m;i++)
  {
    L(i,i)=exp(tmpL(i));
  }

  g+=0.5*m*log(2.0*PI)+0.5*norm2(ui);

  dvar_vector lui=L*ui;
  for (j=group(_i);j<group(_i+1);j++)
  {
    dvariable eta = X(j)*b + Z(j)*lui;
    if (value(eta)<20)
    {
      dvariable tmp=exp(eta);
      eta=tmp/(1.0+tmp);
    }
    else
    {
      dvariable tmp=exp(-eta);
      eta=1/(1.0+tmp);
    }
    if (y(j)==1)
    {
      g-=log(1.e-10+eta);
    }
    else
    {
      g-=log(1.e-10+(1.0-eta));
    }
  }
  
REPORT_SECTION
  report << "fixed effects" << endl;
  report << b*phi  << endl;
  report << "mean r2/mu = " << mean(column(rr,4))  << endl;
  report << "mean r2/(mu*tau) = " << mean(column(rr,5))  << endl;
  report << "residuals" << endl;
  report << " observed   mean        Tau       r2/mu  r2/(mu*tau) index " << endl;
  int i;
  for (i=1;i<=n;i++)
  {
    report << setw(6) << int(rr(i,1));
    report << setfixed() << setprecision(3) << setw(10) << rr(i)(2,5);
    report << setw(6) << int(rr(i,6)) << endl;
  }

  dmatrix srr=sort(rr,5);
  report << endl << "sorted residuals" << endl;
  report << " observed   mean        Tau       r2/mu  r2/(mu*tau) index " << endl;
  for (i=1;i<=n;i++)
  {
    report << setw(6) << int(srr(i,1));
    report << setfixed() << setprecision(3) << setw(10) << srr(i)(2,5);
    report << setw(6) << int(srr(i,6)) << endl;
  }
  
TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(2000000);
  gradient_structure::set_MAX_NVAR_OFFSET(50000);

GLOBALS_SECTION
  #include <df1b2fun.h>
  #include <admodel.h>
  int global_rand_phase;
  #ifndef PI
    const double PI = 3.14159265358979323846;
  #endif

