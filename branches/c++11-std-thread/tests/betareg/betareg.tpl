DATA_SECTION
  init_int n
  init_int m 
  init_vector subject(1,n)
  init_vector Y(1,n)
  ivector ind(1,m)
 LOC_CALCS
  
  for (int i=1;i<=n;i++)
  {
    double& y=Y(i);
    if (y==0.0)
    {
      cout << y << endl;
      y=1.e-6;
    }
    if (y==1.0)
    {
      cout << y << endl;
      y=0.99999;
    }
  }
  ofstream ofs("data");
  ofs << setw(6) << setprecision(4) << setfixed() << Y << endl;
PARAMETER_SECTION
  objective_function_value f
  sdreport_vector sigma(1,2)
  sdreport_vector bb(1,2)
  init_bounded_number a(-5.0,5.0,3)
  init_vector b(1,2)
  init_bounded_vector log_sigma(1,2,-3.0,3.0,2)
  random_effects_matrix u(1,m,1,2,2) 
  
TOP_OF_MAIN_SECTION
  gradient_structure::set_MAX_NVAR_OFFSET(1000);

PROCEDURE_SECTION
  int i;
  ind.initialize();
  for (i=1;i<=n;i++)
  {
    f1(i,subject(i),b,u(subject(i)),log_sigma,a);
  }
  if (sd_phase())
  {
    sigma=exp(log_sigma);
    bb=b;
  }
  if (mceval_phase())
  {
    sigma=exp(log_sigma);
    ofs11  << b(1) << endl;
    ofs12  << b(2) << endl;
    ofs13  << sigma(1) << endl;
    ofs14  << sigma(2) << endl;
    ofs15  << a << endl;
  }
  
SEPARABLE_FUNCTION void f1(int i,int subi,const dvar_vector& b,const dvar_vector&  ui,const dvar_vector& log_sigma,const prevariable& a)

    dvar_matrix M(1,2,1,2);
    M(1,1)=1.0;
    M(1,2)=0.0;
    dvariable tmp=1.0/sqrt(1+square(a));
    M(2,1)=a*tmp;
    M(2,2)=tmp;
    dvar_vector vi=M*ui;
    dvariable mu;
    dvariable phi;
    const double ltpi=0.5*log(2.0*PI);
    dvar_vector sigma=exp(log_sigma);
    
    dvariable bx=b(1)+sigma(1)*vi(1);
    if (value(bx)<10)
    {
      dvariable ebx=exp(bx);
      mu=0.99999*(ebx/(1.0+ebx));
    }
    else
    {
      dvariable ebx=exp(-bx);
      mu=1.0/(1.0+ebx);
      mu+=.0000001;
    }
    phi=exp(-b(2)-sigma(2)*vi(2));
    double y=Y(i);
    f-=ln_beta_density(y,mu,phi);
    if (ind(subi)==0) 
    {
      ind(subi)=1;
      f+=ltpi+.5*norm2(ui);
    }

REPORT_SECTION
  //report << sqrt(norm2(u)/u.indexmax())*sigma1 << endl;
  //report << sqrt(norm2(v)/v.indexmax())*sigma2 << endl;

GLOBALS_SECTION

  #include <admodel.h>
  #include <df1b2fun.h>

  ofstream ofs11("b1");
  ofstream ofs12("b2");
  ofstream ofs13("s1");
  ofstream ofs14("s2");
  ofstream ofs15("a");

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

