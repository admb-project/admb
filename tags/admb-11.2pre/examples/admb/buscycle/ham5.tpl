// Copyright (c) 2008, 2009, 2010 Regents of the University of California.
//
// ADModelbuilder and associated libraries and documentations are
// provided under the general terms of the "BSD" license.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3.  Neither the name of the  University of California, Otter Research,
// nor the ADMB Foundation nor the names of its contributors may be used
// to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
 !! order=5; // !!5 order of the autoregressive process
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
  5darray qb5(0,1,0,1,0,1,0,1,0,1); // !!5
  7darray qb(op1,nperiods,0,1,0,1,0,1,0,1,0,1,0,1); 
  7darray qa(op1,nperiods,0,1,0,1,0,1,0,1,0,1,0,1);
  7darray eps(op1,nperiods,0,1,0,1,0,1,0,1,0,1,0,1);
  7darray eps2(op1,nperiods,0,1,0,1,0,1,0,1,0,1,0,1);
  7darray prob(op1,nperiods,0,1,0,1,0,1,0,1,0,1,0,1);
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
  int t,i,k,l,m,n,p;
  
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
  
  // !!5
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) {
      for (k=0;k<=1;k++) {
        for (l=0;l<=1;l++) {
          for (m=0;m<=1;m++) qb5(i,j,k,l,m)=P(i,j)*qb4(j,k,l,m); 
	}  
      }
    }  
  }
  // qb(6) is the probabilibility of being in one of 64
  // states (64=2x2x2x2x2x2) in periods 5,4,3,2,1 before observing
  // y(6)
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) {
      for (k=0;k<=1;k++) {
        for (l=0;l<=1;l++) {
          for (m=0;m<=1;m++) { // !!5
            for (n=0;n<=1;n++) qb(op1,i,j,k,l,m,n)=P(i,j)*qb5(j,k,l,m,n); 
          }	
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
              for (n=0;n<=1;n++) { // !!5
	        eps(t,i,j,k,l,m,n)=z(t,i)-phi(z(t-1,j),
	          z(t-2,k),z(t-3,l),z(t-4,m),z(t-5,n),f);
                eps2(t,i,j,k,l,m,n)=square(eps(t,i,j,k,l,m,n));
              }		
	    }  
	  }
	}
      }	    		
    }  
  }  
  // calculate the mean squared "residuals" for use in 
  // "undimensionalized" parameterization of sigma
  dvariable eps2sum=sum(eps2);
  var=smult*eps2sum/(64.0*(nperiods-4));  //!!5
  sigma=sqrt(var);
  
  for (t=op1;t<=nperiods;t++) {
    for (i=0;i<=1;i++) {
      for (j=0;j<=1;j++) {
        for (k=0;k<=1;k++) {
          for (l=0;l<=1;l++)  //!!5
	    prob(t,i,j,k,l)=exp(eps2(t,i,j,k,l)/(-2.*var))/sigma;
        }	    
      }	    		
    }  
  }  
  
  for (i=0;i<=1;i++) {
    for (j=0;j<=1;j++) {
      for (k=0;k<=1;k++) {
        for (l=0;l<=1;l++) {
          for (m=0;m<=1;m++) {
            for (n=0;n<=1;n++) qa(op1,i,j,k,l,m,n)= qb(op1,i,j,k,l,m,n)*
	      prob(op1,i,j,k,l,m,n);
          }	      
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
              for (n=0;n<=1;n++) { //!!5
                qb(t,i,j,k,l,m,n).initialize(); 
	        // here is where having 6 dimensional arrays makes the
	        // formula for moving the state distributions form period
	        // t-1 to period t easy to program and understand.
	        // Throw away  n and accumulate its two values into next
	        // time period after multiplying by transition matrix P
                for (p=0;p<=1;p++) qb(t,i,j,k,l,m,n)+=P(i,j)*
		  qa(t-1,j,k,l,m,n,p); 
              }		
            }
	  }
	}
      }	    		
    }  
    for (i=0;i<=1;i++) {
      for (j=0;j<=1;j++) {
        for (k=0;k<=1;k++) {
          for (l=0;l<=1;l++) {
            for (m=0;m<=1;m++) { // !!5
              for (n=0;n<=1;n++) qa(t,i,j,k,l,m,n)=qb(t,i,j,k,l,m,n)*
	          prob(t,i,j,k,l,m,n);
            }		  
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
    ofstream ofs("qbefore5.tex");
    for (int t=op1;t<=nperiods;t++)
    {
      ofs << (t-4)/100. << " " << qbefore(t,0) << endl;
    }
  }  
  {
    ofstream ofs("qafter5.tex");
    for (int t=op1;t<=nperiods;t++)
    {
      ofs << (t-4)/100. << " " << qafter(t,0) << endl;
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
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(400000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(2100000);
  gradient_structure::set_MAX_NVAR_OFFSET(500);
GLOBALS_SECTION  
  #include <fvar.hpp>
  
   // !!5
  dvariable phi(const dvariable& a1,const dvariable& a2,const dvariable& a3,
    const dvariable& a4,const dvariable& a5,const dvar_vector& f)
  {
    return   a1*f(1)+a2*f(2)+a3*f(3)+a4*f(4)+a5*f(5);
  }  
