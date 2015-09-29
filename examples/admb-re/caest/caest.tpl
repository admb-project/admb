// TPL code for:
// J. T. Schnute and L. J. Richards.  1995.  The influence of error on
//      population estimates from catch-age models.  Can. J. Fish.
//      Aquat. Sci.  52: 2063-2077.
//
// Modified to version where recruitment is modelled as a random effect.

DATA_SECTION
   init_int nyear
   init_int nage
   init_vector cat(1,nyear)
   init_matrix spat(1,nage,1,nyear)
   init_vector sindex(1,nyear)
   int nf

PARAMETER_SECTION
   init_bounded_number alpha(0.02,50.0) //-- selectivity exponent
   init_bounded_number beta(0.0,1.0)    //-- selectivity at age class 1
   init_bounded_number M(0.02,0.8)      //-- natural mortality
   init_bounded_number q(0.1,10.0)      //-- catchability
   init_bounded_number R(0.1,10.0)      //-- recruitment
   init_bounded_number gam(-1.0,1.0)    //-- recruitment correlation
   init_number rho(-1)                  //-- ratio sigma1^2 and kappa^2
   
   number kappa_2                        
   number tau_2                          
   number xiSS
   number eta0tSS
   number eta_atSS
   number tmp
   number S

   vector beta_a(1,nage)
   vector betaNat(1,nage)                

   matrix Nat(1,nage,1,nyear)
   matrix ut(1,nage,1,nyear)
   matrix dpat(1,nage,1,nyear)
   matrix xat(1,nage,1,nyear)
   vector Ft(1,nyear)
   vector Pt(1,nyear)
   vector dindex(1,nyear)
   vector xi_t(2-nage,nyear)
   vector eta_0t(1,nyear)
   matrix eta_at(1,nage,1,nyear)

   vector like_terms(1,5)
   number penalty

   sdreport_number sd_alpha
   sdreport_number sd_beta
   // sdreport_number sd_M
   // sdreport_number sd_q
   // sdreport_number sd_R
   // sdreport_number sd_gam

   init_bounded_number mean_recruit(.6,1.2,1)
   init_bounded_number sd_recruit(.01,.3,2)
   vector recruit(2-nage,nyear)  
   random_effects_vector u(2-nage,nyear,2)
   //init_bounded_vector recruit(2-nage,nyear,1.0E-03,50.0,2)  

   objective_function_value lf

PRELIMINARY_CALCS_SECTION
   nf = 0;

PROCEDURE_SECTION

   lf += 0.5*norm2(u);
   recruit = mean_recruit + sd_recruit*u;

   Calc_Selectivity();
   Calc_Nat_and_Moments();
   Calc_Resids();
   Calc_Objective_Function();

FUNCTION Calc_Selectivity
   for (int a=1; a<nage; a++)
      beta_a[a] = 1.0 - (1.0 - beta) * pow(double(nage - a) / 
                  double(nage - 1.0), alpha);
   beta_a[nage] = 1.0;

FUNCTION Calc_Nat_and_Moments
   S = exp(-M);
   for (int t=1; t<=nyear; t++)
   {
   	if (t==1)
      {
      	//-- table 1, step 2
         for (int a=1; a<=nage-1; a++)
            Nat[a][1] = recruit[2-a] * exp(-M * (a-1.0));       // D.5
         Nat[nage][1] = recruit[2-nage] * (exp(-M * 
                        (nage-1.0)) / (1.0 - S));               // D.6
      }
      else
      {
      	//-- table 1, step 4
         Nat[1][t] = recruit[t];                                // D.7
         for (int a=2; a<nage; a++)
            Nat[a][t] = S * (Nat[a-1][t-1] - 
                        ut[a-1][t-1] * cat[t-1]);               // D.8
         Nat[nage][t] = S * (Nat[nage-1][t-1] + Nat[nage][t-1]-
                        (ut[nage-1][t-1] + ut[nage][t-1]) * 
                        cat[t-1]);                              // D.9
      }

      betaNat = elem_prod(beta_a, column(Nat, t));
      Pt[t] = sum(betaNat);                                     // D.3
      //ut.colfill(t, (betaNat / Pt[t]));                         // D.4
      //dpat.colfill(t, column(ut,t));                            // D.11
      for(int jj=1; jj<=nage; jj++)
      {
        ut(jj,t) = betaNat(jj)/Pt[t];
        dpat(jj,t) = ut(jj,t);
      }    
      dindex[t] = q * (Pt[t] - cat[t] / 2.0);                   // D.10
   }


FUNCTION Check0
   for (int t=1; t<=nyear; t++)
      for (int a=1; a<=nage; a++)
         if (value(Nat[a][t]) <= 1.0E-08)
         {
         	penalty += 1.0E-08 - Nat[a][t];
            Nat[a][t] = 1.0E-08;
         }

FUNCTION Calc_Resids
   xi_t[2-nage] = log(recruit[2-nage]) - log(R);                // L.3
   xiSS = 0;
   int t;
   for (t=3-nage; t<=nyear; t++)
   {
      xi_t[t] = log(recruit[t]) - (1.0 - gam)*log(R) - 
                gam*log(recruit[t-1]);                          // L.4
      xiSS += xi_t[t] * xi_t[t];
   }

   eta0tSS = 0;
   for (t=1; t<=nyear; t++)
   {
      eta_0t[t] = log(sindex[t]) - log(dindex[t]);              // L.5
      eta0tSS += eta_0t[t] * eta_0t[t];
   }

   eta_atSS = 0;
   for (t=1; t<=nyear; t++)
   {
      tmp = 0;
      int a;
      for (a=1; a<=nage; a++)
         tmp += log(spat[a][t]) - log(dpat[a][t]);
      for (a=1; a<=nage; a++)
      {
         eta_at[a][t] = log(spat[a][t]) - log(dpat[a][t]) - 
                        (1.0/nage)*tmp;                          // L.6
         eta_atSS += eta_at[a][t] * eta_at[a][t];
      }
   }

   kappa_2 = 1.0/(double)(nage + 2*nyear - 2) * ( 1/rho * 
             ((1-gam*gam)*(xi_t[2-nage]*xi_t[2-nage]) +
             xiSS) + 1.0/(1.0-rho) * eta0tSS );                 // L.16

   tau_2 = 1.0/(double)((nage-1)*nyear) * eta_atSS;             // L.17

FUNCTION Calc_Objective_Function

   sd_alpha = alpha;
   sd_beta = beta;
   // sd_gam = gam;
   // sd_R = R;
   // sd_q = q;
   // sd_M = M;

   nf += 1;
   like_terms[1] = (double)(nage + nyear - 2) * log(rho);
   like_terms[2] = (double)(nyear) * log(1.0-rho);
   like_terms[3] = -log(1.0-gam*gam);
   like_terms[4] = ((double)(nage) + (double)(2.0*nyear) - 
                   (double)(2.0)) * log(kappa_2);
   like_terms[5] = (double)((nage - 1.0)*nyear) * log(tau_2);
   lf += 0.5 * sum(like_terms) + penalty;                        // L.18

  //RUNTIME_SECTION
   //convergence_criteria 1.0E-06

REPORT_SECTION
   report << "Number of years                   : " << nyear    << endl;
   report << "Number of ages                    : " << nage     << endl;
   report << "Value of the objective function   : " 
                                << setprecision(10) << lf       << endl;
   report << "M                                 : " << M        << endl;
   report << "R                                 : " << R        << endl;
   report << "gamma                             : " << gam      << endl;
   report << "alpha                             : " << alpha    << endl;
   report << "beta                              : " << beta     << endl;
   report << "q                                 : " << q        << endl;
   report << "Number of function calls:         : " << nf       << endl;

TOP_OF_MAIN_SECTION
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(300000);

