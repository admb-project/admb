#include <admodel.h>

#include <n2mvol.htp>

model_data::model_data(void)
{
  ndim.allocate("ndim");
  nobs.allocate("nobs");
 ndim1=ndim*(ndim+1)/2;
 ndim2=ndim*(ndim-1)/2;
  Y.allocate(1,nobs,1,ndim,"Y");
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
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 ad_comm(argc,argv), model_data() , function_minimizer(sz)
{
  initializationfunction();
  h_mean.allocate(1,nobs,1,ndim,"h_mean");
  #ifndef NO_AD_INITIALIZE
    h_mean.initialize();
  #endif
  h_var.allocate(1,nobs,1,ndim,1,ndim,"h_var");
  #ifndef NO_AD_INITIALIZE
    h_var.initialize();
  #endif
  ldR.allocate("ldR");
  #ifndef NO_AD_INITIALIZE
  ldR.initialize();
  #endif
  theta0.allocate(1,ndim,-1,"theta0");
  lmin.allocate(1,nobs,"lmin");
  #ifndef NO_AD_INITIALIZE
    lmin.initialize();
  #endif
  w.allocate(1,ndim,-10,10,"w");
  w1.allocate(1,ndim,"w1");
  #ifndef NO_AD_INITIALIZE
    w1.initialize();
  #endif
  lambda.allocate(1,ndim,2,"lambda");
  lambda2.allocate(1,ndim,-1,"lambda2");
  delta.allocate(1,ndim,0,.98,"delta");
  R.allocate(1,ndim,1,ndim,"R");
  Omega.allocate(1,ndim,1,ndim,"Omega");
  ch_R.allocate(1,ndim,1,ndim,"ch_R");
  #ifndef NO_AD_INITIALIZE
    ch_R.initialize();
  #endif
  Rinv.allocate(1,ndim,1,ndim,"Rinv");
  #ifndef NO_AD_INITIALIZE
    Rinv.initialize();
  #endif
  v_R.allocate(1,ndim2,-1.0,1.0,"v_R");
  Z.allocate(1,ndim,1,ndim,"Z");
  ch_Z.allocate(1,ndim,1,ndim,"ch_Z");
  #ifndef NO_AD_INITIALIZE
    ch_Z.initialize();
  #endif
  v_Z.allocate(1,ndim1,-1.0,1.0,"v_Z");
  S.allocate(1,ndim,1,ndim,"S");
  #ifndef NO_AD_INITIALIZE
    S.initialize();
  #endif
  f.allocate("f");
}

void model_parameters::initializationfunction(void)
{
  delta.set_initial_value(0.9);
}

void model_parameters::userfunction(void)
{
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
}

dvar_vector model_parameters::update_the_means(dvar_vector& w,dvar_vector& m,dvector& e)
{
  dvar_vector tmp= w+elem_prod(delta,m)+elem_prod(lambda,e);
  if (active(lambda2))
    tmp+=elem_prod(lambda2,fabs(e)); 
  return tmp;
  
}

dvar_matrix model_parameters::update_the_variances(dvar_matrix& v)
{
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
  
}

dvariable model_parameters::fp(dvar_vector& h, dvector& y, dvar_vector& m,dvar_matrix& v)
{
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
}

void model_parameters::sfja(double x)
{
  ;
}

void model_parameters::xfp12(dvar_vector& h, dvector& y,dvar_vector& m,dvar_matrix& v, dvar_vector gr,dvar_matrix& hess)
{
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
  for (int i=1;i<=ndim;i++)
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
}

void model_parameters::fill_the_matrices(void)
{
  int ii=1;
  ch_Z.initialize();
  for (int i=1;i<=ndim;i++)
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
}

void model_parameters::report()
{
 adstring ad_tmp=initial_params::get_reportfile_name();
  ofstream report((char*)(adprogram_name + ad_tmp));
  if (!report)
  {
    cerr << "error trying to open report file"  << adprogram_name << ".rep";
    return;
  }
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
}

void model_parameters::preliminary_calculations(void){}

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

void function_minimizer::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  //gradient_structure::set_MAX_NVAR_OFFSET(1200);
  arrmblsize=20000000;
  gradient_structure::set_CMPDIF_BUFFER_SIZE(25000000);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(1000000);
 
    gradient_structure::set_NO_DERIVATIVES();
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__)  || \
     defined(__MSVC32__)
      if (!arrmblsize) arrmblsize=150000;
  #else
      if (!arrmblsize) arrmblsize=25000;
  #endif
    model_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;
    mp.preliminary_calculations();
    mp.computations(argc,argv);
    return 0;
}
