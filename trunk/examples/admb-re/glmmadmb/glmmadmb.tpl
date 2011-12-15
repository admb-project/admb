// 2011-03-24 version from Dave Fournier
// modified 2011-04-27 Hans Skaug, BMB
DATA_SECTION

  init_int n					// Number of observations
  init_int p_y					// Number of fixed effects
  init_matrix y(1,n,1,p_y)			// Observation matrix
  init_int p					// Number of fixed effects
  init_matrix X(1,n,1,p)			// Design matrix for fixed effects
  init_int M					// Number of RE blocks (crossed terms)
  init_ivector q(1,M)				// Number of levels of each RE block
  init_ivector m(1,M)				// Number of random effects within each block
  int sum_mq
  init_int ncolZ
  init_matrix Z(1,n,1,ncolZ)			// Design matrix for random effects
  init_imatrix I(1,n,1,ncolZ)			// Index vectors into joint RE vector "u" for each
  init_ivector cor_flag(1,M)			// Indicator for whether each RE block should be correlated
  init_ivector cor_block_start(1,M) 		// Indices for blocks of correlated random effects
  init_ivector cor_block_stop(1,M) 
  init_int numb_cor_params			// Total number of correlation parameters to be estimated
  init_int like_type_flag   			// 0 poisson 1 binomial 2 negative binomial 3 Gamma 4 beta 5 gaussian 6 truncated poisson 7 trunc NB
  init_int link_type_flag   			// 0 log 1 logit 2 probit 3 inverse 4 cloglog 5 identity
  init_int rlinkflag                            // robust link function?
  init_int no_rand_flag   			// 0 have random effects 1 no random effects
  init_int zi_flag				// 1=zi, 0=no zi
  // TESTING: remove eventually?
  init_int zi_kluge				// apply zi=0.001?
  init_int nbinom1_flag				// 1=NBinom1, 0=NBinom2
  init_int intermediate_maxfn
  init_int has_offset				// 0=no offset, 1=with offset
  init_vector offset(1,n)				// Offset vector
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

  sum_mq = 0;
  for (i=1;i<=M;i++)
    sum_mq += m(i)*q(i);

INITIALIZATION_SECTION
 tmpL 1.0
 tmpL1 0.0
 log_alpha 1
 pz .001

PARAMETER_SECTION
 LOC_CALCS

  // BMB: FIXME: do we need this?  formerly disallowed for binomial (was like_type_flag 2);
  //     would be problematic for binary data but otherwise OK.  Should test in R code
  //  if(zi_flag && (like_type_flag>=2))
  // {
  //  cerr << "Zero inflation not allowed for this response type" << endl;
  //  ad_exit(1);
  // }

  int pctr = 2;
  // FIXME: move trunc_poisson earlier in like_type hierarchy (or add a scale parameter flag vector)
  int alpha_phase = like_type_flag>1 && like_type_flag!=6 ? pctr++ : -1;         // Phase 2 if active
  int zi_phase = zi_flag ? pctr++ : -1;                      // Phase 3 if active
  int rand_phase = no_rand_flag==0 ? pctr++ : -1;    // Right after zi
  int cor_phase = (rand_phase>0) && (sum(cor_flag)>0) ? pctr++ : -1 ; // Right after rand_phase
  ivector ncolS(1,M);
  double log_alpha_lowerbound = nbinom1_flag==1 ? 0.001 : -5.0 ;
  ncolS = m;                                            // Uncorrelated random effects
  for (int i=1;i<=M;i++)                                // Modifies the correlated ones
    if(cor_flag(i))
      ncolS(i) = m(i)*(m(i)+1)/2;
  int nS = sum(ncolS);             
 END_CALCS
  
  init_bounded_number pz(.000001,0.999,zi_phase)
  init_vector beta(1,p,1)     	// Fixed effects
  sdreport_vector real_beta(1,p)     
  init_bounded_vector tmpL(1,ncolZ,-10,10.5,rand_phase)		// Log standard deviations of random effects
  init_bounded_vector tmpL1(1,numb_cor_params,-10,10.5,cor_phase)	// Offdiagonal elements of cholesky-factor of correlation matrix
  init_bounded_number log_alpha(log_alpha_lowerbound,6.,alpha_phase)	
  sdreport_number alpha
  sdreport_vector S(1,nS)
  random_effects_vector u(1,sum_mq,rand_phase)    // Pool of random effects 
  objective_function_value g                    	   // Log-likelihood
 LOC_CALCS
  for (int i=I.indexmin() ; i<= I.indexmax(); i++)
  {
    if (min(I(i)) < u.indexmin() || max(I(i)) > u.indexmax())
    {
      cerr << "Bounds error in I for i = " << i << endl
         << " I(" << i << ") = " << I(i) << endl
         <<  "u.indexmin() = " << u.indexmin() << endl
          <<  "u.indexmax() = " << u.indexmax() << endl;
      ad_exit(1);
    }
  }

PRELIMINARY_CALCS_SECTION
  cout << setprecision(4);

PROCEDURE_SECTION
  g=0.0;

  int i;

  if(!no_rand_flag)
    for (i=1;i<=sum_mq;i++)
      n01_prior(u(i));			// u's are N(0,1) distributed

  for(i=1;i<=n;i++)
    log_lik(i,tmpL,tmpL1,u(I(i)),beta,log_alpha,pz);

  if (sd_phase())
  {
    alpha = exp(log_alpha);
    real_beta=beta*phi;

    int i,j,i_m;
    int i1=1, i2=1, ii=1;
    for (i_m=1;i_m<=M;i_m++)
    {
      dvar_matrix L(1,m(i_m),1,m(i_m));
      L.initialize();
      dvar_matrix tmpS(1,m(i_m),1,m(i_m));
      tmpS.initialize();

      if(cor_flag(i_m))
      {
        int ii=1;
        L(1,1)=1;
        for (i=1;i<=m(i_m);i++)
        {
          L(i,i)=1;
          for (int j=1;j<i;j++)
            L(i,j)=tmpL1(i2++);
          L(i)(1,i)/=norm(L(i)(1,i));
        }
        for (i=1;i<=m(i_m);i++)
          L(i)*=exp(tmpL(i1++));
      }
      else
      {
        for (i=1;i<=m(i_m);i++)
          L(i,i)=exp(tmpL(i1++));
      }

      tmpS=L*trans(L);

      for (i=1;i<=m(i_m);i++)
      {
          if(cor_flag(i_m))
            for(j=1;j<i;j++)
              S(ii++) = tmpS(i,j);
          S(ii++) = tmpS(i,i);
      }
    }

  }

SEPARABLE_FUNCTION void n01_prior(const prevariable&  u)
 g -= -0.5*log(2.0*M_PI) - 0.5*square(u);

SEPARABLE_FUNCTION void log_lik(int _i,const dvar_vector& tmpL,const dvar_vector& tmpL1,const dvar_vector& ui, const dvar_vector& beta,const prevariable& log_alpha, const prevariable& pz)
  
  int i,j, i_m, Ni;
  double e1=1e-8; // formerly 1.e-20; current agrees with nbmm.tpl
  double e2=1e-8; // formerly 1.e-20; current agrees with nbmm.tpl

  dvariable alpha = e2+exp(log_alpha);

  // Construct random effects vector with proper var-covar structure from u
  dvar_vector b(1,ncolZ);

  int i1=1, i2=1;
  for (i_m=1;i_m<=M;i_m++)
  {
    dvar_matrix L(1,m(i_m),1,m(i_m));
    L.initialize();

    if(cor_flag(i_m))
    {
      L(1,1)=1;
      for (i=1;i<=m(i_m);i++)
      {
        L(i,i)=1;
        for (int j=1;j<i;j++)
          L(i,j)=tmpL1(i2++);
        L(i)(1,i)/=norm(L(i)(1,i));
      }
      for (i=1;i<=m(i_m);i++)
        L(i)*=exp(tmpL(i1++));
    }
    else
    {
      for (i=1;i<=m(i_m);i++)
        L(i,i)=exp(tmpL(i1++));
    }

    int upper = sum(m(1,i_m));
    int lower = upper-m(i_m)+1;

    dvar_vector tmp1(1,m(i_m));

    tmp1 = ui(lower,upper).shift(1);
    tmp1 = L*tmp1;
    //    b(lower,upper) = (L*(ui(lower,upper).shift(1))).shift(lower);	// L*ui
    b(lower,upper) = tmp1.shift(lower);

  }

  // fudge factors for inverse link
  double eps=1.e-2;
  double eps1=1.e-2;
  double eps2=1.e-4; // works on cloglog test in link.R; FAILS when eps2=1.e-6
  switch (current_phase())
  {
  case 1:
    eps=.01;
    eps1=.05;
    break;
  default:
    eps=.01;
    eps1=.01;
  }


  dvariable eta = X(_i)*beta + Z(_i)*b;

  if(has_offset)
    eta += offset(_i);
  dvariable lambda;
  dvariable fpen=0.0;
  switch(link_type_flag) 
  {
     case 0:    // [robust] log
       if (rlinkflag) {
          lambda = e1+mfexp(eta);
       } else {
          lambda = exp(eta);
       }
       break;
     case 1:    // [robust] logistic
       if (rlinkflag) {
        if (value(eta)<10)
          {
            dvariable eeta=mfexp(eta);
            lambda=eeta/(1.0+eeta);
          }
          else
         {
            dvariable eeta=mfexp(-eta);
            lambda=1.0/(1.0+eeta);
         }
       } else {
          lambda = 1.0/(1.0+exp(-eta));
       }
       break;
     case 2:   // probit (cum norm)
       lambda = cumd_norm(eta);
       break;
     case 3:   // inverse link
       if (rlinkflag) {
         lambda = 1.0/(eps+posfun(eta,eps1,fpen));
          g+=fpen;
        } else {
         lambda = 1.0/eta;
        }
       break;
     case 4: // cloglog
	 {
       // FIXME: document/clarify epsilon values  Add rlinkflag?
       dvariable eeta;
       
       if (rlinkflag) {
          eeta = -mfexp(eta);
       } else {
          eeta = -exp(eta);
       }
       // safe (1-exp()); tip from http://www.johndcook.com/cpp_expm1.html
       if (fabs(value(eeta))<1e-5) {
	   lambda = eeta + eeta*eeta*0.5;
       } else {
	   lambda = 1-mfexp(eeta);
       }
       // restrict to (0,1)
       if (rlinkflag) {
          lambda = posfun(lambda,eps2,fpen);
          lambda = (1.0-posfun(1.0-lambda,eps2,fpen));
       }
       }
       break;
     case 5: // identity
        lambda = eta;
	break;
     default:
       cerr << "Illegal value for link_type_flag" << endl;
       ad_exit(1);
  }

  dvariable  tau = nbinom1_flag ? alpha : 1.0 + e1 + lambda/alpha ;
  dvariable tmpl; 				// Log likelihood

  int cph=current_phase();

  // FIXME: does having lots of choices (for like_type_flag and link_flag) slow things down?
  // Is there any advantage to doing this stuff in a vectorized way?
  // Is there some other better approach to the per-point switch() ?

  switch(like_type_flag)
  {
    case 0:   // Poisson
      tmpl = log_density_poisson(y(_i,1),lambda);
      break;
    case 1:   // Binomial: y(_i,1)=#successes, y(_i,2)=#failures, 
      if (p_y==1) {
         if (y(_i,1)==1) {
           tmpl = log(e1+lambda); //BMB: bvprobit.tpl uses e1=1e-10 here
         } else {
           tmpl = log(e1+(1.0-lambda));
         }
      }	 else {
         Ni = sum(y(_i));			// Number of trials
         tmpl = log_comb(Ni,y(_i,1)) + y(_i,1)*log(lambda) + (Ni-y(_i,1))*log(1.0-lambda);
      }
      break;
    case 2:   // neg binomial
      if (cph<2)  // would like to use alpha_phase rather than 2 but it's in local_calcs
        tmpl = -square(log(1.0+y(_i,1))-log(1.0+lambda));
      else
        tmpl = log_negbinomial_density(y(_i,1),lambda,tau);
      break;
    case 3: // Gamma 
        tmpl = log_gamma_density(y(_i,1),alpha,alpha/lambda);
	break;
    case 4: // Beta 
      // FIXME: "log_beta_density" seems more consistent but changing name
      //       causes problems -- already exists somewhere?
      tmpl = ln_beta_density(y(_i,1),lambda,alpha);
      break;
    case 5: // Gaussian
      tmpl = 0.5*(log(2.0*M_PI*square(alpha)))+square((y(_i,1)-lambda)/alpha);
      break;
    case 6:   // truncated Poisson
      // FIXME: check somewhere (here, or preferably in R code) for trunc poisson + not ZI + 0 in response
      if (value(lambda) > 1.0e-10) {
          tmpl = log_density_poisson(y(_i,1),lambda)-log(1.0-exp(-lambda));
      } else {
          tmpl = log_density_poisson(y(_i,1),lambda)-log(lambda);
      }
      break;
    case 7:  // truncated NB
    // NB(0) = p^alpha = (alpha/(alpha+lambda))^alpha = (1+lambda/alpha)^(-alpha)
    //   -> exp(-lambda) as alpha -> infty
      if (cph<2)  // ignore zero-inflation for first phase
        tmpl = -square(log(1.0+y(_i,1))-log(1.0+lambda));
      else
        tmpl = log_negbinomial_density(y(_i,1),lambda,tau)-log(1.0-pow(1.0+lambda/alpha,-alpha));
      break;
    default:
      cerr << "Illegal value for like_type_flag" << endl;
      ad_exit(1);
  }
	
  // Zero inflation part 
  // zi_kluge: apply ZI whether or not zi_flag is true
  if(zi_flag || zi_kluge) {
    if(y(_i,1)==0)
      g -= log(e2+pz+(1.0-pz)*mfexp(tmpl));
    else
      g -= log(e2+(1.0-pz)*mfexp(tmpl));
   } else g -= tmpl;

REPORT_SECTION
  report << beta*phi << endl;

TOP_OF_MAIN_SECTION
  arrmblsize=40000000;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(2000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(100000000);
  gradient_structure::set_MAX_NVAR_OFFSET(2000000);

GLOBALS_SECTION

  #include <admodel.h>
  #include <df1b2fun.h>

  ofstream ofs11("b1");
  ofstream ofs12("b2");
  ofstream ofs13("s1");
  ofstream ofs14("s2");

  dvariable betaln(const prevariable& a,const prevariable& b )
  {
    return gammln(a)+gammln(b)-gammln(a+b);
  }


  dvariable ln_beta_density(double y,const prevariable & mu,
    const prevariable& phi)
  {
    dvariable omega=mu*phi;
    dvariable tau=phi-mu*phi;
    dvariable lb=betaln(omega,tau);
    dvariable d=(omega-1)*log(y)+(tau-1)*log(1.0-y)-lb;
    return d;
  }

  df1b2variable betaln(const df1b2variable& a,const df1b2variable& b )
  {
    return gammln(a)+gammln(b)-gammln(a+b);
  }

  df1b2variable ln_beta_density(double y,const df1b2variable & mu,
    const df1b2variable& phi)
  {
    df1b2variable omega=mu*phi;
    df1b2variable tau=phi-mu*phi;
    df1b2variable lb=betaln(omega,tau);
    df1b2variable d=(omega-1)*log(y)+(tau-1)*log(1.0-y)-lb;
    return d;
  }

