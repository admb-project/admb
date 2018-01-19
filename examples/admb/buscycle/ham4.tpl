// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_number a1init   // read in the initial value of a1 with the data
  init_int nperiods1   // the number of observations
  int nperiods  // nperiods-1 after differencing
 !! nperiods=nperiods1-1;
  init_vector yraw(1,nperiods1)  //read in the observations
  vector y(1,nperiods)   // the differenced observations
 !! y=100.*(--log(yraw(2,nperiods1)) - log(yraw(1,nperiods))); 
  int order 
  int op1  
 !! order=4; //order of the autoregressive process
 !! op1=order+1;
  int nstates  // the number of states (expansion and contraction)
 !! nstates=2;
PARAMETER_SECTION
  init_vector f(1,order,1)  // coefficients for the atuoregressive
                            // process
  init_bounded_matrix Pcoff(0,nstates-1,0,nstates-1,.01,.99,2)  
        // determines the transition matrix for the markov process
  init_number a0(5)  // equation 4.3 in Hamilton (1989)
  init_bounded_number a1(0.0,10.0,4);  
 !! if (a0==0.0) a1=a1init;  // set initial value for a1 as specified
                     // in the top of the file nham4.dat
  init_bounded_number smult(0.01,1,3)  // used in computing sigma
  matrix z(1,nperiods,0,1)  // computed via equation 4.3 in 
                          // Hamilton (1989)
  matrix qbefore(op1,nperiods,0,1);  // prob. of being in state before
  matrix qafter(op1,nperiods,0,1); // and after observing y(t)
  number sigma // variance of epsilon(t) in equation 4.3
  number var  // square of sigma
  sdreport_matrix P(0,nstates-1,0,nstates-1);
  number ff1;
  vector qb1(0,1); 
  matrix qb2(0,1,0,1); 
  3darray qb3(0,1,0,1,0,1);
  4darray qb4(0,1,0,1,0,1,0,1);
  6darray qb(op1,nperiods,0,1,0,1,0,1,0,1,0,1); 
  6darray qa(op1,nperiods,0,1,0,1,0,1,0,1,0,1);
  6darray eps(op1,nperiods,0,1,0,1,0,1,0,1,0,1);
  6darray eps2(op1,nperiods,0,1,0,1,0,1,0,1,0,1);
  6darray prob(op1,nperiods,0,1,0,1,0,1,0,1,0,1);
  objective_function_value ff;
PROCEDURE_SECTION
  P=Pcoff;
  dvar_vector ssum=colsum(P);  // forma a vector whose elements are the
                           // sums of the columns of P
  ff+=norm2(log(ssum)); // this is a penalty so that the hessian will
                        // not be singular and the coefficients of P 
                        // will be well defined
  // normalize the transition matrix P so its columns sum to 1
  int j;
  for (j=0;j<=nstates-1;j++)
  {
    for (int i=0;i<=nstates-1;i++)
    {
      P(i,j)/=ssum(j);
    }
  }  

  dvar_matrix ztrans(0,1,1,nperiods);
  ztrans(0)=y-a0;
  ztrans(1)=y-a0-a1;
  z=trans(ztrans);
  int t,i,k,l,m,n;
  
  qb1(0)=(1.0-P(1,1))/(2.0-P(0,0)-P(1,1)); // unconditional distribution
  qb1(1)=1.0-qb1(0);
  
  // for periods 2 through 4 there are no observations to condition
  // the state distributions on so we use the unconditional distributions
  // obtained by multiplying by the transition matrix P.
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) qb2(i,j)=P(i,j)*qb1(j);  
  }
  
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) {
      for (k=0;k<=1;k++) qb3(i,j,k)=P(i,j)*qb2(j,k); 
    }  
  }
  
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) {
      for (k=0;k<=1;k++) {
        for (l=0;l<=1;l++) qb4(i,j,k,l)=P(i,j)*qb3(j,k,l); 
      }
    }  
  }
  
  // qb(5) is the probabilibility of being in one of 32
  // states (32=2x2x2x2x2) in periods 5,4,3,2,1 before observing
  // y(5)
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) {
      for (k=0;k<=1;k++) {
        for (l=0;l<=1;l++) {
          for (m=0;m<=1;m++) qb(op1,i,j,k,l,m)=P(i,j)*qb4(j,k,l,m);
        }
      }
    }
  }
  // now calculate the realized values for epsilon for all 
  // possible combinations of states
  for (t=op1;t<=nperiods;t++) {
    for (i=0;i<=1;i++) {
      for (j=0;j<=1;j++) {
        for (k=0;k<=1;k++) {
          for (l=0;l<=1;l++) {
            for (m=0;m<=1;m++) {
              eps(t,i,j,k,l,m)=z(t,i)-phi(z(t-1,j),
                z(t-2,k),z(t-3,l),z(t-4,m),f);
              eps2(t,i,j,k,l,m)=square(eps(t,i,j,k,l,m));
            }  
          }
        }
      }                            
    }  
  }  
  // calculate the mean squared "residuals" for use in 
  // "undimensionalized" parameterization of sigma
  dvariable eps2sum=sum(eps2);
  //sigma=smult*eps2sum/(32.0*(nperiods-4)); 
  //var=sigma*sigma;
  var=smult*eps2sum/(32.0*(nperiods-4)); 
  sigma=sqrt(var);
  
  for (t=op1;t<=nperiods;t++) {
    for (i=0;i<=1;i++) {
      for (j=0;j<=1;j++) {
        for (k=0;k<=1;k++) 
          prob(t,i,j,k)=exp(eps2(t,i,j,k)/(-2.*var))/sigma;
      }                            
    }  
  }  
  
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) {
      for (k=0;k<=1;k++) {
        for (l=0;l<=1;l++) {
          for (m=0;m<=1;m++) qa(op1,i,j,k,l,m)= qb(op1,i,j,k,l,m)*
            prob(op1,i,j,k,l,m);
        }
      }
    }                            
  }  
  ff1=0.0;
  qbefore(op1,0)=sum(qb(op1,0));
  qbefore(op1,1)=sum(qb(op1,1));
  qafter(op1,0)=sum(qa(op1,0));
  qafter(op1,1)=sum(qa(op1,1));
  dvariable sumqa=sum(qafter(op1));
  qa(op1)/=sumqa;
  qafter(op1,0)/=sumqa;
  qafter(op1,1)/=sumqa;
  ff1-=log(1.e-50+sumqa);
  for (t=op1+1;t<=nperiods;t++) { // notice that the t loop includes 2 
    for (i=0;i<=1;i++) {      // i,j,k,l,m blocks
      for (j=0;j<=1;j++) {
        for (k=0;k<=1;k++) {
          for (l=0;l<=1;l++) {
            for (m=0;m<=1;m++) {
              qb(t,i,j,k,l,m).initialize(); 
              // here is where having 6 dimensional arrays makes the
              // formula for moving the state distributions form period
              // t-1 to period t easy to program and understand.
              // Throw away  n and accumulate its two values into next
              // time period after multiplying by transition matrix P
              for (n=0;n<=1;n++) qb(t,i,j,k,l,m)+=P(i,j)*qa(t-1,j,k,l,m,n); 
            }
          }
        }
      }                            
    }  
    for (i=0;i<=1;i++) {
      for (j=0;j<=1;j++) {
        for (k=0;k<=1;k++) {
          for (l=0;l<=1;l++) {
            for (m=0;m<=1;m++) qa(t,i,j,k,l,m)=qb(t,i,j,k,l,m)*
                  prob(t,i,j,k,l,m);
          }
        }
      }                            
    }  
    qbefore(t,0)=sum(qb(t,0));
    qbefore(t,1)=sum(qb(t,1));
    qafter(t,0)=sum(qa(t,0));
    qafter(t,1)=sum(qa(t,1));
    dvariable sumqa=sum(qafter(t));
    qa(t)/=sumqa;
    qafter(t,0)/=sumqa;
    qafter(t,1)/=sumqa;
    ff1-=log(1.e-50+sumqa);
  }  
  
  
  ff+=ff1;
  ff+=.1*norm2(f);
REPORT_SECTION
  dvar_matrix out(1,2,op1,nperiods);
  out(1)=trans(qbefore)(1);
  out(2)=trans(qafter)(1);
  {
    ofstream ofs("qbefore4.tex");
    for (int t=5;t<=nperiods;t++)
    {
      ofs << std::ios::fixed << setprecision(3) 
                   << (t-4)/100. << " " << qbefore(t,0) << endl;
    }
  }  
  {
    ofstream ofs("qafter4.tex");
    for (int t=5;t<=nperiods;t++)
    {
      ofs << std::ios::fixed << setprecision(3) 
          << (t-4)/100. << " " << qafter(t,0) << endl;
    }
  }  
  report << "#qbefore    qafter" <<  endl;
  report << std::ios::fixed << setprecision(3) << setw(7) << trans(out) << endl;
RUNTIME_SECTION
  maximum_function_evaluations 20000 
  convergence_criteria 1.e-6 
TOP_OF_MAIN_SECTION
  //gradient_structure::set_NUM_DEPENDENT_VARIABLES(2000);
  arrmblsize=500000;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(200000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(2100000);
  gradient_structure::set_MAX_NVAR_OFFSET(500);
GLOBALS_SECTION  
  #include <fvar.hpp>
  
  dvariable phi(const dvariable& a1,const dvariable& a2,const dvariable& a3,
    const dvariable& a4,const dvar_vector& f)
  {
    return   a1*f(1)+a2*f(2)+a3*f(3)+a4*f(4);
  }  
