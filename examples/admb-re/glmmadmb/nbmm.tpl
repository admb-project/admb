// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

// GLMM with negative binomial response
// Example 2 in Booth, Casella, Friedl, Hobert (2003) Statistical Modelling, vol. 3, no. 3, pp. 179-191
// Numerical results meant to match rightmost column in Table 2 of Booth et al.

DATA_SECTION

  init_int n					// Number of observations
  init_vector y(1,n)				// Observation vector
  init_int p					// Number of fixed effects
  init_matrix X(1,n,1,p)				// Covariate matrix for fixed effects
  init_int q					// Number of Clusters
  init_int m					// Number of random effects within clusters
  init_matrix Z(1,n,1,m)				// Covariate matrix for random effects
  init_vector I(1,n)				// Grouping variable
  init_int cor_flag
  init_int easy_flag
  init_int zi_flag
  init_int like_type_flag   // 0 neg bin 1 poisson
  init_int no_rand_flag   // 0 have random effects 1 no random effects
  init_int intermediate_maxfn
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
  cout << I << endl;
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
 log_alpha 1
 pz .001

PARAMETER_SECTION
 LOC_CALCS
  int rand_phase=3;
  int rand_sd_phase;
  if (no_rand_flag==1)
  {
    rand_phase=-1;
    rand_sd_phase=-1;
  }
  else
  {
    rand_phase=3;
    rand_sd_phase=4;
  }
  int kludge_phase=-1;
  if (easy_flag)
    kludge_phase=-1;
  else
    kludge_phase=15;

  int zi_phase=5;
  if (zi_flag)
   zi_phase=5;
  else
   zi_phase=-5;
  int cor_phase=4;
  if (cor_flag && no_rand_flag==0)
   cor_phase=4;
  else
   cor_phase=-4;
  int alpha_phase=5;
  if(like_type_flag==0)  
    alpha_phase=6;
  else
    alpha_phase=-6;
  global_rand_phase=rand_phase;
 END_CALCS
  
  init_bounded_number pz(.000001,0.999,zi_phase)
  init_vector b(1,p,1)     	// Fixed effects
  sdreport_vector real_b(1,p)     
  !! int mm = (m*(m+1))/2;
  !! int m1 = (m*(m-1))/2;
  init_bounded_vector tmpL(1,m,-10,10.5,rand_sd_phase)	// Elements of cholesky-factor L of correlation matrix
  init_bounded_vector tmpL1(1,m1,-10,10.5,cor_phase)	// Elements of cholesky-factor L of correlation matrix
  init_bounded_number log_alpha(-5.,6.,alpha_phase)	// phase 2 by dave       

  //sdreport_number sigma                       	// sqrt(variance component)
  sdreport_number alpha                       	// sqrt(variance component)
  sdreport_matrix S(1,m,1,m)
  vector lambda(1,n)  
  init_number kkludge(kludge_phase)  

  random_effects_matrix u(1,q,1,m,rand_phase)            // Random effects
  objective_function_value g                    // Log-likelihood

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);


BETWEEN_PHASES_SECTION
  maxfn=1000;
  if (current_phase()>global_rand_phase && global_rand_phase>0 )
  {
    if (!last_phase())
    {
      maxfn=intermediate_maxfn;
    }
  }




PROCEDURE_SECTION
  g=0.0;

  int i;
  for (i=1;i<=q;i++)
  {
    fu(u(i));
  }

  switch(like_type_flag)
  {
  case 0:   // neg binomial
    if (easy_flag)
    {
      for (i=1;i<=n;i++)
      {
        if (cor_flag)
        { 
          easy_f1_nb(i,tmpL,tmpL1,u((int) I(i)),b,log_alpha,pz);
        }
        else
        { 
          easy_f1_nb(i,tmpL,u((int) I(i)),b,log_alpha,pz);
        }
      }
    }
    else
    {
      for (i=1;i<=n;i++)
      {
        if (cor_flag)
        { 
          hard_f1_nb(i,tmpL,tmpL1,u((int) I(i)),b,log_alpha,pz);
        }
        else
        { 
          hard_f1_nb(i,tmpL,u((int) I(i)),b,log_alpha,pz);
        }
      }
    }
    break;
  case 1:   // poisson
    if (easy_flag)
    {
      for (i=1;i<=n;i++)
      {
        if (cor_flag)
        { 
          easy_f1_poisson(i,tmpL,tmpL1,u((int) I(i)),b,pz);
        }
        else
        { 
          easy_f1_poisson(i,tmpL,u((int) I(i)),b,pz);
        }
      }
    }
    else
    {
      for (i=1;i<=n;i++)
      {
        if (cor_flag)
        { 
          hard_f1_poisson(i,tmpL,tmpL1,u((int) I(i)),b,pz);
        }
        else
        { 
          hard_f1_poisson(i,tmpL,u((int) I(i)),b,pz);
        }
      }
    }
    break;
  default:
    cerr << "Illegal value for like_type_flag" << endl;
    ad_exit(1);
  }


  if (sd_phase())
  {
    alpha = exp(log_alpha);
    real_b=b*phi;
    dvar_matrix L(1,m,1,m);
    L.initialize();
    int i,j;
  
    if (tmpL.indexmax() != m)
    {
      cerr << "size error in get_choleski" << endl;
    }
    int ii=1;
    L(1,1)=1.0;
    for (i=2;i<=m;i++)
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
    S=L*trans(L);
  }

  if (cor_flag)
    f0(tmpL,tmpL1,m,b,pz,kkludge);
  else
    f0(tmpL,m,b,pz,kkludge);

SEPARABLE_FUNCTION void f0(const dvar_vector& tmpL,const dvar_vector& tmpL1,int m,const dvar_vector& b,const dvariable& pz,const dvariable& kkludge)

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
  g-= .001*log(pz)-.001*log(1.0-pz);

  g+=square(kkludge);
  
SEPARABLE_FUNCTION void f0(const dvar_vector& tmpL,int m,const dvar_vector& b,const dvariable& pz,const dvariable& kkludge)

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
  g-= .001*log(pz)-.001*log(1.0-pz);

  g+=square(kkludge);
  
SEPARABLE_FUNCTION void fu(const dvar_vector& ui)
  g+=0.5*m*log(2.0*PI)+0.5*norm2(ui);


SEPARABLE_FUNCTION void easy_f1_nb(int _i,const dvar_vector& tmpL,const dvar_vector& tmpL1,const dvar_vector& ui,const dvar_vector& b,const prevariable& log_alpha,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
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

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  


  dvariable alpha = e2+exp(log_alpha);

  //dvariable alpha = bounder(log_alpha,0.1,28.08,10);



  dvariable tau = 1.01+e1+lambda/alpha;
  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=value(tau);
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4)/value(tau);


  if (!last_phase())
  {
    switch(current_phase())
    {
    case 1:
    case 2:
    case 3:
      g+=0.5*normal;
      break;
    case 4:
      normal_negbin_mixture(_i,e2,1.0,normal,pz,lambda,tau,y(_i),g);
      break;
    case 5:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
      break;
    default:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
    }
  }
  else
  {
    if(y(_i)==0)
    {
      g-=log(e2+pz+(1.0-pz)
        *exp(log_negbinomial_density(y(_i),lambda,tau)));
    }
    else
    {
      g-=log(e2+(1.0-pz)*exp(log_negbinomial_density(y(_i),lambda,tau)));
    }
  }

SEPARABLE_FUNCTION void easy_f1_nb(int _i,const dvar_vector& tmpL,const dvar_vector& ui,const dvar_vector& b,const prevariable& log_alpha,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
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

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  


  dvariable alpha = e2+exp(log_alpha);

  //dvariable alpha = bounder(log_alpha,0.1,28.08,10);



  dvariable tau = 1.01+e1+lambda/alpha;
  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=value(tau);
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4)/value(tau);


  if (!last_phase())
  {
    switch(current_phase())
    {
    case 1:
    case 2:
    case 3:
      g+=0.5*normal;
      break;
    case 4:
      normal_negbin_mixture(_i,e2,1.0,normal,pz,lambda,tau,y(_i),g);
      break;
    case 5:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
      break;
    default:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_negbinomial_density(y(_i),lambda,tau)));
      }
    }
  }
  else
  {
    if(y(_i)==0)
    {
      g-=log(e2+pz+(1.0-pz)
        *exp(log_negbinomial_density(y(_i),lambda,tau)));
    }
    else
    {
      g-=log(e2+(1.0-pz)*exp(log_negbinomial_density(y(_i),lambda,tau)));
    }
  }

SEPARABLE_FUNCTION void hard_f1_nb(int _i,const dvar_vector& tmpL,const dvar_vector& tmpL1,const dvar_vector& ui,const dvar_vector& b,const prevariable& log_alpha,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
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
      L(i)=exp(tmpL(i));
    }
  }

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  


  dvariable alpha = e2+exp(log_alpha);

  dvariable tau = 1.01+e1+lambda/alpha;
  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=value(tau);
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4)/value(tau);

  switch(current_phase())
  {
  case 1:
  case 2:
  case 3:
    g+=0.5*normal;
    break;
  case 4:
    normal_negbin_mixture(_i,e2,10.0,normal,pz,lambda,tau,y(_i),g);
    break;
  case 5:
    normal_negbin_mixture(_i,e2,1.0,normal,pz,lambda,tau,y(_i),g);
    break;
  case 6:
    normal_negbin_mixture(_i,e2,0.3,normal,pz,lambda,tau,y(_i),g);
    break;
  case 7:
    normal_negbin_mixture(_i,e2,0.1,normal,pz,lambda,tau,y(_i),g);
    break;
  case 8:
    normal_negbin_mixture(_i,e2,0.03,normal,pz,lambda,tau,y(_i),g);
    break;
  case 9:
    normal_negbin_mixture(_i,e2,0.01,normal,pz,lambda,tau,y(_i),g);
    break;
  case 10:
    normal_negbin_mixture(_i,e2,0.003,normal,pz,lambda,tau,y(_i),g);
    break;
  case 11:
    normal_negbin_mixture(_i,e2,0.001,normal,pz,lambda,tau,y(_i),g);
    break;
  case 12:
    normal_negbin_mixture(_i,e2,0.0003,normal,pz,lambda,tau,y(_i),g);
    break;
  case 13:
    normal_negbin_mixture(_i,e2,1.e-4,normal,pz,lambda,tau,y(_i),g);
    break;
  case 14:
    normal_negbin_mixture(_i,e2,1.e-5,normal,pz,lambda,tau,y(_i),g);
    break;
  case 15:
    normal_negbin_mixture(_i,e2,1.e-6,normal,pz,lambda,tau,y(_i),g);
    break;
  default:
    normal_negbin_mixture(_i,e2,1.e-6,normal,pz,lambda,tau,y(_i),g);
    break;
  }
SEPARABLE_FUNCTION void hard_f1_nb(int _i,const dvar_vector& tmpL,const dvar_vector& ui,const dvar_vector& b,const prevariable& log_alpha,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
  dvar_matrix L(1,m,1,m);
  L.initialize();
  int i,j;

  if (tmpL.indexmax() != m)
  {
    cerr << "size error in get_choleski" << endl;
  }

  for (i=1;i<=m;i++)
  {
    L(i)=exp(tmpL(i));
  }

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  

  dvariable alpha = e2+exp(log_alpha);

  dvariable tau = 1.01+e1+lambda/alpha;
  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=value(tau);
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4)/value(tau);

  switch(current_phase())
  {
  case 1:
  case 2:
  case 3:
    g+=0.5*normal;
    break;
  case 4:
    normal_negbin_mixture(_i,e2,10.,normal,pz,lambda,tau,y(_i),g);
    break;
  case 5:
    normal_negbin_mixture(_i,e2,1.0,normal,pz,lambda,tau,y(_i),g);
    break;
  case 6:
    normal_negbin_mixture(_i,e2,.3,normal,pz,lambda,tau,y(_i),g);
    break;
  case 7:
    normal_negbin_mixture(_i,e2,.1,normal,pz,lambda,tau,y(_i),g);
    break;
  case 8:
    normal_negbin_mixture(_i,e2,.03,normal,pz,lambda,tau,y(_i),g);
    break;
  case 9:
    normal_negbin_mixture(_i,e2,.01,normal,pz,lambda,tau,y(_i),g);
    break;
  case 10:
    normal_negbin_mixture(_i,e2,.003,normal,pz,lambda,tau,y(_i),g);
    break;
  case 11:
    normal_negbin_mixture(_i,e2,.001,normal,pz,lambda,tau,y(_i),g);
    g-=log(e2+.001*exp(-normal)+exp(log_negbinomial_density(y(_i),lambda,tau)));
    break;
  case 12:
    normal_negbin_mixture(_i,e2,.0003,normal,pz,lambda,tau,y(_i),g);
    break;
  case 13:
    normal_negbin_mixture(_i,e2,.0001,normal,pz,lambda,tau,y(_i),g);
    break;
  case 14:
    normal_negbin_mixture(_i,e2,1.e-5,normal,pz,lambda,tau,y(_i),g);
    break;
  case 15:
    normal_negbin_mixture(_i,e2,1.e-6,normal,pz,lambda,tau,y(_i),g);
    break;
  default:
    normal_negbin_mixture(_i,e2,1.e-6,normal,pz,lambda,tau,y(_i),g);
    break;
  }

SEPARABLE_FUNCTION void hard_f1_poisson(int _i,const dvar_vector& tmpL,const dvar_vector& tmpL1,const dvar_vector& ui,const dvar_vector& b,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
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
      L(i)=exp(tmpL(i));
    }
  }

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  

  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=1;
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4);

  switch(current_phase())
  {
  case 1:
  case 2:
  case 3:
    g+=0.5*normal;
    break;
  case 4:
    if (y(_i)==0)
    {
      g-=log(e2+10.0*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+10.0*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 5:
    if (y(_i)==0)
    {
      g-=log(e2+1.0*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.0*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 6:
    if (y(_i)==0)
    {
      g-=log(e2+0.3*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.3*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 7:
    if (y(_i)==0)
    {
      g-=log(e2+0.1*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.1*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 8:
    if (y(_i)==0)
    {
      g-=log(e2+0.03*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.03*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 9:
    if (y(_i)==0)
    {
      g-=log(e2+0.01*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.01*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 10:
    if (y(_i)==0)
    {
      g-=log(e2+0.003*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.003*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 11:
    if (y(_i)==0)
    {
      g-=log(e2+0.001*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.001*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    g-=log(e2+.001*exp(-normal)+exp(log_density_poisson(y(_i),lambda)));
    break;
  case 12:
    if (y(_i)==0)
    {
      g-=log(e2+0.0003*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.0003*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 13:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-4*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-4*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 14:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-5*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-5*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 15:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-6*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-6*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  default:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-6*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-6*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  }

SEPARABLE_FUNCTION void hard_f1_poisson(int _i,const dvar_vector& tmpL,const dvar_vector& ui,const dvar_vector& b,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
  dvar_matrix L(1,m,1,m);
  L.initialize();
  int i,j;

  if (tmpL.indexmax() != m)
  {
    cerr << "size error in get_choleski" << endl;
  }

  for (i=1;i<=m;i++)
  {
    L(i)=exp(tmpL(i));
  }

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  

  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=1;
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4);

  switch(current_phase())
  {
  case 1:
  case 2:
  case 3:
    g+=0.5*normal;
    break;
  case 4:
    if (y(_i)==0)
    {
      g-=log(e2+10.0*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+10.0*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 5:
    if (y(_i)==0)
    {
      g-=log(e2+1.0*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.0*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 6:
    if (y(_i)==0)
    {
      g-=log(e2+0.3*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.3*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 7:
    if (y(_i)==0)
    {
      g-=log(e2+0.1*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.1*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 8:
    if (y(_i)==0)
    {
      g-=log(e2+0.03*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.03*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 9:
    if (y(_i)==0)
    {
      g-=log(e2+0.01*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.01*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 10:
    if (y(_i)==0)
    {
      g-=log(e2+0.003*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.003*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 11:
    if (y(_i)==0)
    {
      g-=log(e2+0.001*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.001*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    g-=log(e2+.001*exp(-normal)+exp(log_density_poisson(y(_i),lambda)));
    break;
  case 12:
    if (y(_i)==0)
    {
      g-=log(e2+0.0003*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+0.0003*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 13:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-4*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-4*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 14:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-5*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-5*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  case 15:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-6*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-6*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  default:
    if (y(_i)==0)
    {
      g-=log(e2+1.e-6*exp(-normal)+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+1.e-6*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
    break;
  }

SEPARABLE_FUNCTION void easy_f1_poisson(int _i,const dvar_vector& tmpL,const dvar_vector& tmpL1,const dvar_vector& ui,const dvar_vector& b,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
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

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  


  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=1.0;
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4);


  if (!last_phase())
  {
    switch(current_phase())
    {
    case 1:
    case 2:
    case 3:
      g+=0.5*normal;
      break;
    case 4:
      if (y(_i)==0)
      {
        g-=log(e2+1.0*exp(-normal)+pz+(1.0-pz)
          *exp(log_density_poisson(y(_i),lambda)));
      }
      else
      {
        g-=log(e2+1.0*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
      }
      break;
    case 5:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_density_poisson(y(_i),lambda)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
      }
      break;
    default:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_density_poisson(y(_i),lambda)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
      }
    }
  }
  else
  {
    if(y(_i)==0)
    {
      g-=log(e2+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
  }

SEPARABLE_FUNCTION void easy_f1_poisson(int _i,const dvar_vector& tmpL,const dvar_vector& ui,const dvar_vector& b,const prevariable& pz)

  double e1;
  double e2;
  if (last_phase())
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  else
  {
    e1=1.e-8;
    e2=1.e-8;
  }
  
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

  dvariable eta = X(_i)*b + Z(_i)*(L*ui);
  dvariable lambda = e1+mfexp(eta);            	  


  dvariable normal;
  normal=square(eta-log(y(_i)+1.0));
  double dl=value(lambda);
  rr(_i,1)=y(_i);
  rr(_i,2)=dl;
  rr(_i,3)=1.0;
  rr(_i,4)=square(dl-y(_i))/dl;
  rr(_i,5)=rr(_i,4)/1.0;


  if (!last_phase())
  {
    switch(current_phase())
    {
    case 1:
    case 2:
    case 3:
      g+=0.5*normal;
      break;
    case 4:
      if (y(_i)==0)
      {
        g-=log(e2+1.0*exp(-normal)+pz+(1.0-pz)
          *exp(log_density_poisson(y(_i),lambda)));
      }
      else
      {
        g-=log(e2+1.0*exp(-normal)+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
      }
      break;
    case 5:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_density_poisson(y(_i),lambda)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
      }
      break;
    default:
      if (y(_i)==0)
      {
        g-=log(e2+pz+(1.0-pz)
          *exp(log_density_poisson(y(_i),lambda)));
      }
      else
      {
        g-=log(e2+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
      }
    }
  }
  else
  {
    if(y(_i)==0)
    {
      g-=log(e2+pz+(1.0-pz)
        *exp(log_density_poisson(y(_i),lambda)));
    }
    else
    {
      g-=log(e2+(1.0-pz)*exp(log_density_poisson(y(_i),lambda)));
    }
  }

REPORT_SECTION
  //double alpha = bounder(value(log_alpha),1.0,28.08,10);
  double  alpha = exp(value(log_alpha));
  report << "fixed effects" << endl;
  report << "alpha =  "  << alpha  << endl;
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
  #include <float.h>
  int controlword=0;
  /*
   BOOL DllMain(HANDLE hinstDLL,
      DWORD reason,
      LPVOID res)
   {
     // for floating point so that R doesn't complain
     //controlword=control87(0,0);
     return TRUE;
   }
  */
  #if defined(PRINT_DEBUG)
    #include <admodel.h>
    ofstream ofs("model.out");
  #endif

  int global_rand_phase;


  void normal_negbin_mixture(int i,double e,double pn,const prevariable& normal,const prevariable& pz,const prevariable& lambda, const prevariable& tau,double yi,prevariable& g)
  {
    if (yi==0)
    {
      g-=log(e+pn*exp(-normal)+pz+(1.0-pz)
        *exp(log_negbinomial_density(yi,lambda,tau)));
    }
    else
    {
      g-=log(e+pn*exp(-normal)+(1.0-pz)*exp(log_negbinomial_density(yi,lambda,tau)));
    }
  } 

  void normal_negbin_mixture(int i,double e,double pn,const df1b2variable& normal,const df1b2variable& pz,const df1b2variable& lambda, const df1b2variable& tau,double yi,df1b2variable& g)
  {
    if (yi==0)
    {
      g-=log(e+pn*exp(-normal)+pz+(1.0-pz)
        *exp(log_negbinomial_density(yi,lambda,tau)));
    }
    else
    {
      g-=log(e+pn*exp(-normal)+(1.0-pz)*exp(log_negbinomial_density(yi,lambda,tau)));
    }
  }
  

FINAL_SECTION
   //control87(controlword,0xfffff);
