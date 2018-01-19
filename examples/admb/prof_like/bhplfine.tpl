// Author: Anders Nielsen
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int nR
  init_int nC
  init_matrix obs(1,nR,1,nC)
  vector ssb(1,nR)
  !! ssb=column(obs,1);
  vector logR(1,nR)
  !! logR=column(obs,2);
PARAMETER_SECTION
  init_number loga;
  init_number logb;
  init_number logSigma;
  sdreport_number sigmaSq;
  vector pred(1,nR);
  likeprof_number loga_pl       // NOTICE
  likeprof_number logb_pl       // NOTICE
  objective_function_value nll;
PRELIMINARY_CALCS_SECTION       //!
  loga_pl.set_stepnumber(50);   //!
  loga_pl.set_stepsize(0.1);    //!
  logb_pl.set_stepnumber(50);   //!
  logb_pl.set_stepsize(0.1);    //!
PROCEDURE_SECTION
  loga_pl=loga;                 //NOTICE
  logb_pl=logb;                 //NOTICE 
  sigmaSq=exp(2.0*logSigma);
  pred=loga+log(ssb)-log(1+exp(logb)*ssb);
  nll=0.5*(nR*log(2*M_PI*sigmaSq)+sum(square(logR-pred))/sigmaSq);
