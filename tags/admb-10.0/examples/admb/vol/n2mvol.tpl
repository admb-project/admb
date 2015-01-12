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
  init_int ndim
  init_int nobs
  int ndim1
  int ndim2
 !! ndim1=ndim*(ndim+1)/2;
 !! ndim2=ndim*(ndim-1)/2;
  init_matrix Y(1,nobs,1,ndim)
 LOC_CALCS
  for (int i=2;i<nobs;i++)
    for (int j=1;j<=ndim;j++)
      if (Y(i,j)==10000)
      {
        int i2=i+1;
        do
        {
          if (Y(i2,j)==10000) 
            i2++;
          else
            break; 
        } 
        while(1);

        Y(i,j)=(Y(i-1,j)+Y(i2,j))/2.;
        if (Y(i,j)>100.0)
          cerr << " Y(i,j) too big " << Y(i,j) << endl; 
      }      
 END_CALCS
 
PARAMETER_SECTION
  matrix h_mean(1,nobs,1,ndim)
  3darray h_var(1,nobs,1,ndim,1,ndim)
  number ldR;
  init_vector theta0(1,ndim,-1);
  vector lmin(1,nobs)
  init_bounded_vector w(1,ndim,-10,10)
  vector w1(1,ndim)
  init_vector lambda(1,ndim,2)
  init_vector lambda2(1,ndim,-1)
  init_bounded_vector delta(1,ndim,0,.98)
  sdreport_matrix R(1,ndim,1,ndim)
  sdreport_matrix Omega(1,ndim,1,ndim)
  matrix ch_R(1,ndim,1,ndim)
  matrix Rinv(1,ndim,1,ndim)
  init_bounded_vector v_R(1,ndim2,-1.0,1.0)
  sdreport_matrix Z(1,ndim,1,ndim)
  matrix ch_Z(1,ndim,1,ndim)
  init_bounded_vector v_Z(1,ndim1,-1.0,1.0)
  matrix S(1,ndim,1,ndim);
  objective_function_value f
INITIALIZATION_SECTION
  delta 0.9
PROCEDURE_SECTION

  fill_the_matrices();
  
  int sgn;
  ldR=ln_det(R,sgn);
  Rinv=inv(R);
  dvar_vector tmp(1,ndim);
  dvar_matrix sh(1,ndim,1,ndim);
  h_mean(1)=theta0;
  
  h_var(1)=0; 
  for (int i=2;i<=nobs;i++)
  {
    dvar_vector tmean=update_the_means(w,h_mean(i-1),Y(i-1));
    dvar_matrix v=update_the_variances(h_var(i-1));
    tmp=tmean;
     
    dvar_vector h(1,ndim);
    dvar_vector gr(1,ndim);
    for (int ii=1;ii<=4;ii++) 
    {
      xfp12(tmp, Y(i),tmean,v,gr,sh);
      h=-solve(sh,gr);
      tmp+=h;
    }
    double nh=norm2(value(h));
    if (nh>1.e-1) 
      cout << "No convergence in NR " << nh << endl;
    if (nh>1.e+02) 
    {
      f+=1.e+7;
      return;
    }
    h_mean(i)=tmp;
    //cout << "h_mean(i)" << endl;
    //cout << setw(12) << h_mean(i) << endl;
    h_var(i)=inv(sh);
    //cout << "h_var(i)" << endl;
    //cout << setw(12) << h_var(i) << endl;
    lmin(i)=fp(tmp,Y(i),tmean,v);
    int sgn;
    f+=lmin(i)+0.5*ln_det(sh,sgn);
  }
  f-=0.5*nobs*ndim*log(2.*3.14159);
  Omega=S;

FUNCTION  dvar_vector update_the_means(dvar_vector& w,dvar_vector& m,dvector& e)
  dvar_vector tmp= w+elem_prod(delta,m)+elem_prod(lambda,e);
  if (active(lambda2))
    tmp+=elem_prod(lambda2,fabs(e)); 
  return tmp;
  
FUNCTION  dvar_matrix update_the_variances(dvar_matrix& v)
  dvar_matrix tmp(1,ndim,1,ndim);
  for (int i=1;i<=ndim;i++)
  {
    for (int j=1;j<=i;j++)
    {
      tmp(i,j)=delta(i)*delta(j)*v(i,j);
      if (i!=j) tmp(j,i)=tmp(i,j);
    }
  }
  tmp+=Z;
  return tmp;
  
FUNCTION dvariable fp(dvar_vector& h, dvector& y, dvar_vector& m,dvar_matrix& v)
  dvar_vector eh=exp(.5*h);
  for (int i=1;i<=ndim;i++)
  {
    for (int j=1;j<=i;j++)
    {
      S(i,j)= eh(i)*eh(j)*R(i,j);
      if (i!=j) S(j,i)=S(i,j);
    }
  }   

  dvariable lndet;
  dvariable sgn;
  dvar_vector u=solve(S,y,lndet,sgn);
  dvariable l;
  l=.5*lndet+.5*(y*u);
  
  dvar_vector hm=h-m;
  w1=solve(v,hm,lndet,sgn);

  l+=.5*lndet+.5*(w1*hm);

  return l;

FUNCTION void sfja(double x)
  ;

FUNCTION void xfp12(dvar_vector& h, dvector& y,dvar_vector& m,dvar_matrix& v, dvar_vector gr,dvar_matrix& hess)
  dvar_vector ehinv=exp(-.5*h);

  dvariable lndet;
  dvariable sgn;
  dvar_vector ys=elem_prod(ehinv,y);
  dvar_vector u=Rinv*ys;
  gr=0.5;
  dvar_vector vv=elem_prod(ys,u);
  gr-=.5*vv;
  dvar_vector hm=h-m;
  dvar_vector w=solve(v,hm,lndet,sgn);
  gr+=w;
  int i;
  for (i=1;i<=ndim;i++)
  {
    for (int j=1;j<=i;j++)
    {
      hess(i,j)=0.25*ys(i)*ys(j)*Rinv(i,j);
      if (i!=j) hess(j,i)=hess(i,j);
    }
  }
  for (i=1;i<=ndim;i++)
  {
    hess(i,i)+=.25*vv(i);
  }
  hess+=inv(v);

FUNCTION  fill_the_matrices

  int ii=1;
  ch_Z.initialize();
  int i;
  for (i=1;i<=ndim;i++)
  {
    for (int j=1;j<=i;j++)
      ch_Z(i,j)=v_Z(ii++);  
    ch_Z(i,i)+=0.5;
  }
  Z=ch_Z*trans(ch_Z);
  ch_R.initialize();
  ii=1;
  for (i=1;i<=ndim;i++)
  {
    for (int j=1;j<i;j++)
      ch_R(i,j)=v_R(ii++);  
    ch_R(i,i)+=0.1;
    ch_R(i)/=norm(ch_R(i));
  }
  R=ch_R*trans(ch_R);

                       // covariance matrix is correct
REPORT_SECTION
  report<<"observed"<<Y<<endl;
  for (int i=1;i<=nobs;i++)
  {
    report<< "mean" <<endl;
    report<< h_mean(i) <<endl;
    report<< "covariance" <<endl;
    report<<h_var(i)<<endl;
    report<<endl;
  }
  report<< "S(nobs) " << endl;
  report<< Omega << endl;
  report<< "Z " << endl;
  report<< Z << endl;
  report<< "R " << endl;
  report<< R << endl;

TOP_OF_MAIN_SECTION
  //gradient_structure::set_MAX_NVAR_OFFSET(1200);
  arrmblsize=20000000;
  gradient_structure::set_CMPDIF_BUFFER_SIZE(25000000);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(1000000);
 
