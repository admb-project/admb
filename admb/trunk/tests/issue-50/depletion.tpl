DATA_SECTION
 init_int StartYear
 init_int EndYear
 
 init_int Leavout_Year
 init_int Leavout_StartWeek
 init_int Leavout_EndWeek
 
 init_matrix Catch(StartYear,EndYear,1,52)

 !!cout<<Catch(EndYear)<<endl;
 
  
 init_number Ncpue
 init_matrix CPUE(1,Ncpue,1,3) //year, week, CPUE

 !!cout<<CPUE(Ncpue)<<endl;  


PARAMETER_SECTION
  init_vector B0(StartYear,EndYear,1)
  init_number lnqmean(1)
  init_number lnqsd(3)
  number qsd
  init_number lnCPUEsd(4)
  
  init_number G(-1)
  init_number S(-1)
  init_number R(-2)
    
  //init_vector qdev(StartYear,EndYear,1)
  random_effects_vector qdev(StartYear,EndYear,2)
 
  likeprof_number B1_posterior
  
  matrix B(StartYear,EndYear,1,52) 
  vector q(StartYear,EndYear)
  
  vector like(1,Ncpue)
  number Bpen

  objective_function_value f
  
PROCEDURE_SECTION
  Bpen=0;
  B1_posterior=B0(StartYear);

  //Setup parameters
  qsd=exp(lnqsd);

  q=mfexp(lnqmean+qdev*qsd);
  //q=mfexp(lnqmean)+(qdev*qsd);

  //Dynamics
  for(int year=StartYear; year<=EndYear; year++)
  {
	B(year,1)=B0(year);
	for(int week=1;week<=52-1;week++)
	{
		//B(year,week+1)=posfun(B(year,week)*(1.0+G)*S+R-Catch(year,week),0.01,Bpen);
		B(year,week+1)=B(year,week)*(1.0+G)*S+R-Catch(year,week);
  	} 
  }
  
  //Likelihood
  for(int i=1;i<=Ncpue;i++)
  {
	if((CPUE(i,1)!=Leavout_Year)||(CPUE(i,2)<Leavout_StartWeek)||(CPUE(i,2)>Leavout_EndWeek))	  
	  //like(i)=log(mfexp(lnCPUEsd))+square(log(CPUE(i,3))-log(q(CPUE(i,1))*B(CPUE(i,1),CPUE(i,2))))/(2*mfexp(lnCPUEsd)*mfexp(lnCPUEsd));
	  //like(i)=square(  (CPUE(i,3))  -  (q(CPUE(i,1))  *  B(CPUE(i,1),CPUE(i,2)))  );
	  like(i)=log(mfexp(lnCPUEsd))+square((CPUE(i,3))-(q(CPUE(i,1))*B(CPUE(i,1),CPUE(i,2))))/(2*mfexp(lnCPUEsd)*mfexp(lnCPUEsd));
  }
  
  f=sum(like)+0.5*norm2(qdev)+Bpen*1000;
  //f=sum(like)+Bpen*1000;

  if(mceval_phase()) output_mcmc();

FUNCTION output_mcmc  
  ofstream outBio("Bio.out",ios::app);
  outBio.precision(10);
  outBio<<B0<<endl;
  outBio.close();

FINAL_SECTION
  ofstream outResults("Results.out",ios::app);
  outResults.precision(10);
  outResults<<Leavout_Year<<" "<<B0<<endl;
  outResults.close();
    
REPORT_SECTION
  report<<"f"<<endl;
  report<<f<<endl;
  report<<"Bpen"<<endl;
  report<<Bpen<<endl;
  report<<"B0"<<endl;
  report<<B0<<endl;
  report<<"q"<<endl;
  report<<q<<endl;
  report<<"B"<<endl;
  report<<B<<endl;
  report<<"qdev"<<endl;
  report<<qdev<<endl;
  report<<"like"<<endl;
  report<<like<<endl;
  report<<"CPUE fit"<<endl;
  for(int i=1;i<=Ncpue;i++)
  {
  report<<CPUE(i)<<" "<<q(CPUE(i,1))*B(CPUE(i,1),CPUE(i,2))<<endl;
  }

  
  
  
