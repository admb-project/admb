  
  #include <admodel.h>
    
  const double eps=1.e-25;
  class cltudecomp
  {
    dmatrix L;
    dmatrix U;
    ivector indx;
    ivector indx2;
    int sign;
  public:
    void initialize(void) 
    { 
      indx.initialize();
      indx2.fill_seqadd(indexmin(),1);
      sign=1;
      L.initialize(); 
      U.initialize(); 
      for (int i=L.indexmin();i<=L.indexmax();i++)
      {
        L(i,i)=1.0;
      }
    }
    cltudecomp(dmatrix& alpha,dmatrix& gamma);
    cltudecomp(void){}
    void allocate(int lb,int ub) 
    {
      indx.allocate(lb,ub);
      indx2.allocate(lb,ub);
      ivector iv(lb+1,ub);
      iv.fill_seqadd(lb,1);
      L.allocate(lb+1,ub,lb,iv);
      ivector iv1(lb,ub);
      iv1.fill_seqadd(lb,1);
      U.allocate(lb,ub,lb,iv1);
      indx2.fill_seqadd(lb,1);
    }
    cltudecomp(int lb,int ub) : indx(lb,ub), indx2(lb,ub)
    {
      ivector iv(lb+1,ub);
      iv.fill_seqadd(lb,1);
      L.allocate(lb+1,ub,lb,iv);
      ivector iv1(lb,ub);
      iv1.fill_seqadd(lb,1);
      U.allocate(lb,ub,lb,iv1);
      indx2.fill_seqadd(lb,1);
    }
    dmatrix & get_L(){ return L;}
    int indexmin(){return U.indexmin();}
    int indexmax(){return U.indexmax();}
    dmatrix & get_U(){ return U;}
    ivector & get_index(){ return indx;}
    ivector & get_index2(){ return indx2;}
    int & get_sign(){ return sign;}
    // overload () (int,int) to look like Numerical Recipes
    double & operator() (int i,int j){ if (i>j)
                                         return L(i,j);
                                       else
                                         return U(j,i);
                                     }
  };
 
  class dvector_for_adjoint  
  {
    dmatrix D;
    ivector count;
  public:
   int indexmin() { return D.indexmin();}
   int indexmax() { return D.indexmax();}
   const int indexmin() const { return D.indexmin();}
   const int indexmax() const { return D.indexmax();}
   double& operator () (int i) { return D(i,count(i)); }
   const double& operator () (int i) const { return D(i,count(i)); }
   dvector_for_adjoint operator () (int mmin,int mmax) 
   { 
     return dvector_for_adjoint(D.sub(mmin,mmax),count(mmin,mmax));
   }
   dvector_for_adjoint(const dmatrix & _D,const ivector& _count) :
     D(_D),count(_count) {}
  };  
  
  double operator * 
    (const dvector_for_adjoint & v,const dvector_for_adjoint & w)
  {
    double tmp=0.0;
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      tmp+=v(i)*w(i);
    }
    return tmp;
  }
   
  dvector operator * 
    (double x,const dvector_for_adjoint & w)
  {
    int mmin=w.indexmin();
    int mmax=w.indexmax();
    dvector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i)=x*w(i);
    }
    return tmp;
  }
   
  class dmatrix_for_adjoint  
  {
    d3_array D;
    imatrix count;
  public:
   void initialize(void)
   {
     D.initialize();
     count=1.0;
   }
   int indexmin() { return D.indexmin();}
   int indexmax() { return D.indexmax();}
   dvector_for_adjoint operator () (int i) 
   {
     return dvector_for_adjoint(D(i),count(i));
   }
   void increment(int i,int j) 
   { 
     count(i,j)++; 
     if (count(i,j)>3) 
       cout << count(i,j) << endl;
   }
   void decrement(int i,int j) { count(i,j)--; }
   double& operator () (int i,int j) { return D(i,j,count(i,j)); }
   void allocate(int lb,int ub,int l1,ivector & iv,int l2,int u2)
   {
     D.allocate(lb,ub,l1,iv,l2,u2);
     count.allocate(lb,ub,l1,iv);
     count=1;
   }
  };  
  class cltudecomp_for_adjoint
  {
    dmatrix_for_adjoint L;
    dmatrix_for_adjoint U;
    cltudecomp dfclu;
    dvar_matrix_position * pMpos;
    ivector indx;
    ivector indx2;
    int sign;
  public:
    void initialize(void) 
    { 
      pMpos=0;
      indx.initialize();
      indx2.fill_seqadd(indexmin(),1);
      sign=1;
      L.initialize(); 
      U.initialize(); 
      for (int i=L.indexmin();i<=L.indexmax();i++)
      {
        L(i,i)=1.0;
      }
    }
      
    int indexmin(){return U.indexmin();}
    int indexmax(){return U.indexmax();}
    void ludecomp_pivot_for_adjoint_1(void);
    void ludecomp_pivot_for_adjoint_2(void);
    cltudecomp_for_adjoint(void){ pMpos=0;} 
    ~cltudecomp_for_adjoint(){ if (pMpos) delete pMpos;} 
    
    void allocate(int lb,int ub,int n,int m)
    {
      indx.allocate(lb,ub);
      indx2.allocate(lb,ub);
      dfclu.allocate(lb,ub);
      ivector iv(lb+1,ub);
      iv.fill_seqadd(lb,1);
      L.allocate(lb+1,ub,lb,iv,1,n);
      ivector iv1(lb,ub);
      iv1.fill_seqadd(lb,1);
      U.allocate(lb,ub,lb,iv1,1,m);
    }
    cltudecomp_for_adjoint(int lb,int ub,int n,int m) : indx(lb,ub),
      dfclu(lb,ub),pMpos(0)
    {
      ivector iv(lb+1,ub);
      iv.fill_seqadd(lb,1);
      L.allocate(lb+1,ub,lb,iv,1,n);
      ivector iv1(lb,ub);
      iv1.fill_seqadd(lb,1);
      U.allocate(lb,ub,lb,iv1,1,m);
    }
    cltudecomp & get_dfclu() { return dfclu;}
    dmatrix_for_adjoint & get_L(){ return L;}
    dmatrix_for_adjoint & get_U(){ return U;}
    ivector & get_index(){ return indx;}
    int & get_sign(){ return sign;}
    // overload () (int,int) to look like Numerical Recipes
    void decrement(int i,int j)
    { 
      if (i>j)
        L.decrement(i,j);
      else
        U.decrement(j,i);
    }
    void increment(int i,int j)
    { 
      if (i>j)
        L.increment(i,j);
      else
        U.increment(j,i);
    }
    double & operator () (int i,int j)
    { 
      if (i>j)
        return L(i,j);
      else
        return U(j,i);
    }
    friend class double_for_assign;
  };
  dmatrix get_dmatrix(cltudecomp& clu)
  {
    int mmin=clu.indexmin();
    int mmax=clu.indexmax();
    dmatrix tmp(mmin,mmax,mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      for (int j=mmin;j<=mmax;j++)
      {
        tmp(i,j)=clu(i,j);
      }
    }
    return tmp;
  }
  
  dmatrix get_dmatrix(cltudecomp_for_adjoint& clu)
  {
    int mmin=clu.indexmin();
    int mmax=clu.indexmax();
    dmatrix tmp(mmin,mmax,mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      for (int j=mmin;j<=mmax;j++)
      {
        tmp(i,j)=clu(i,j);
      }
    }
    return tmp;
  }
  
  dmatrix get_lower_matrix(cltudecomp_for_adjoint& clu)
  {
    int mmin=clu.indexmin();
    int mmax=clu.indexmax();
    dmatrix tmp(mmin,mmax,mmin,mmax);
    tmp.initialize();
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(i,i)=1.0;
      for (int j=mmin;j<i;j++)
      {
        tmp(i,j)=clu(i,j);
      }
    }
    return tmp;
  }
  
  dmatrix get_upper_matrix(cltudecomp_for_adjoint& clu)
  {
    int mmin=clu.indexmin();
    int mmax=clu.indexmax();
    dmatrix tmp(mmin,mmax,mmin,mmax);
    tmp.initialize();
    for (int i=mmin;i<=mmax;i++)
    {
      for (int j=i;j<=mmax;j++)
      {
        tmp(i,j)=clu(i,j);
      }
    }
    return tmp;
  }
  
  
  
  dmatrix ludecomp_for_adjoint(const dmatrix & M,const cltudecomp & dfclu);
  cltudecomp ludecomp_pivot(const dmatrix & M);
  dmatrix ludecomp_pivot_for_adjoint(const dmatrix & M,
      const cltudecomp & dfclu,const ivector& index2);
  
   
  // adjoint code
  dmatrix ludecomp_for_adjoint(const dmatrix & _M,
    const cltudecomp & _dfclu)
  {
    ADUNCONST(dmatrix,M)
    ADUNCONST(cltudecomp,dfclu)
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    cltudecomp_for_adjoint clu(mmin,mmax,3,2);
 
    // get upper and lower parts of LU
    dmatrix_for_adjoint & alpha = clu.get_L();
    dmatrix_for_adjoint & gamma = clu.get_U(); // gamma is the transpose of beta
    dmatrix & dfalpha = dfclu.get_L();
    dmatrix & dfgamma = dfclu.get_U(); 
    // copy M into alpha and gamma
    // OUTER LOOP1
    int i,j;
    for (i=mmin;i<=mmax;i++)
    {
      for (int j=mmin;j<=mmax;j++)
      {
        clu(i,j)=M(i,j);
      }
    }
    // OUTER LOOP2
    for (j=mmin;j<=mmax;j++)
    {
      int i;
      // INNER LOOP 2 1
      for (i=mmin+1;i<j;i++)
      {
        // using subvector here
        //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        clu.increment(i,j);
        clu(i,j)=tmp;
      }
      // INNER LOOP 2 2
      for (i=j;i<=mmax;i++)
      {
        // using subvector here
        if (j>1)
        {
          //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          double tmp=clu(i,j)-alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          clu.increment(i,j);
          clu(i,j)=tmp;
        }
      }
      // INNER LOOP 2 3
      if (j!=mmax)
      {
        double z= 1.0/gamma(j,j);
        for (i=j+1;i<=mmax;i++)
        {
          double tmp=alpha(i,j);
          clu.increment(i,j);
          alpha(i,j)=tmp*z;
        }
      }
    }
    // OUTER LOOP2
    //for (int j=mmin;j<=mmax;j++)
    for (j=mmax;j>=mmin;j--)
    {
      int i;
      // INNER LOOP 2 3
      if (j!=mmax)
      {
        // need to keep this line for  z
        double z= 1.0/gamma(j,j);
        //for (i=j+1;i<=mmax;i++)
        double dftmp=0.0;
        double dfz=0.0;
        for (i=mmax;i>=j+1;i--)
        {
          // need to keep this line for tmp 
          clu.decrement(i,j);
          double tmp=alpha(i,j);
          //alpha(i,j)=tmp*z;
          dftmp+=dfalpha(i,j)*z;
          dfz+=dfalpha(i,j)*tmp;
          dfalpha(i,j)=0.0;
          //double tmp=alpha(i,j);
          dfalpha(i,j)=dftmp;
          dftmp=0.0;
        }
        //double z= 1.0/gamma(j,j);
        dfgamma(j,j)-=dfz/square(gamma(j,j));
        dfz=0.0;
        
      }
      // INNER LOOP 2 2
      //for (i=j;i<=mmax;i++)
      double dftmp=0.0;
      for (i=mmax;i>=j;i--)
      {
        // using subvector here
        if (j>1)
        {
          //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          //double tmp=clu(i,j)-alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          //clu.increment(i,j);
          //clu(i,j)=tmp;
          clu.decrement(i,j);
          dftmp=dfclu(i,j);
          dfclu(i,j)=0.0;
          dfclu(i,j)=dftmp;
          dfalpha(i)(mmin,j-1)-=dftmp*gamma(j)(mmin,j-1);
          dfgamma(j)(mmin,j-1)-=dftmp*alpha(i)(mmin,j-1);
          dftmp=0.0;
        }
      }
      // INNER LOOP 2 1
      //for (i=mmin+1;i<j;i++)
      for (i=j-1;i>=mmin+1;i--)
      {
        // using subvector here
        //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        //clu.increment(i,j);
        //clu(i,j)=tmp;
        clu.decrement(i,j);
        dftmp=dfclu(i,j);
        dfclu(i,j)=0.0;
        //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        dfclu(i,j)=dftmp;
        dfalpha(i)(mmin,i-1)-=dftmp*gamma(j)(mmin,i-1);
        dfgamma(j)(mmin,i-1)-=dftmp*alpha(i)(mmin,i-1);
        dftmp=0.0;
      }
    }
    // OUTER LOOP1
    dmatrix dfM(mmin,mmax,mmin,mmax);
    for (i=mmin;i<=mmax;i++)
    {
      for (int j=mmin;j<=mmax;j++)
      {
        //clu(i,j)=M(i,j);
        dfM(i,j)=dfclu(i,j);
      }
    }
    return dfM;
  }
  // LU decomp with partial pivoting
  cltudecomp ludecomp_pivot(const dmatrix & M)
  {
    int i,j,k;
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    int imax=mmin-1;
    cltudecomp clu(mmin,mmax);
    dvector scale(mmin,mmax);
 
    // get terms for implicit scaling
    for (i=mmin;i<=mmax;i++)
    {
      
      double tmp=1.0/max(fabs(M(i)));
      if (tmp==0.0)
      {
        cerr << "Error -- trying to take LU decomp of a singular matrix" 
             << endl;
        // use ad_exit() so that debugger can trace this
        ad_exit(1);
      }
      scale(i)=1.0/max(fabs(M(i)));
    }
    // get upper and lower parts of LU
    dmatrix & alpha = clu.get_L();
    dmatrix & gamma = clu.get_U(); // gamma is the transpose of beta
    ivector & index=clu.get_index();
    ivector & index2=clu.get_index2();
    int sign=clu.get_sign();
    // copy M into alpha and gamma
    for (i=mmin;i<=mmax;i++)
    {
      for (int j=mmin;j<=mmax;j++)
      {
        clu(i,j)=M(i,j);
      }
    }
    for (j=mmin;j<=mmax;j++)
    {
      int i;
      for (i=mmin+1;i<j;i++)
      {
        // using subvector here
        clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
      }
      double maxterm=0.0;
      for (i=j;i<=mmax;i++)
      {
        // using subvector here
        if (j>1)
        {
          clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
        }
        double tmp=scale(i)*fabs(clu(i,j));
        if (tmp>maxterm)
        {
          maxterm=tmp;
          imax=i;
        }
      }
      if (j!=imax)
      {
        // have to do this element-wise
        for (k=mmin;k<=mmax;k++)
        {
          double tmp=clu(imax,k);
          clu(imax,k)=clu(j,k);
          clu(j,k)=tmp;
        }
        scale(imax)=scale(j);
        int itmp=index2(imax);
        index2(imax)=index2(j);
        index2(j)=itmp;
        sign=-sign;
      }
      index(j)=imax;
      if (clu(j,j)==0.0)
        clu(j,j)=eps;
      if (j!=mmax)
      {
        double z= 1.0/gamma(j,j);
        for (i=j+1;i<=mmax;i++)
        {
          alpha(i,j)*=z;
        }
      }
    }
    return clu;
  }
  // LU decomp with partial pivoting
  cltudecomp xludecomp_pivot(const dvar_matrix & M)
  {
    int i,j,k;
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    int imax=mmin-1;
    cltudecomp clu(mmin,mmax);
    dvector scale(mmin,mmax);
 
    // get terms for implicit scaling
    for (i=mmin;i<=mmax;i++)
    {
      
      double tmp=1.0/value(max(fabs(M(i))));
      if (tmp==0.0)
      {
        cerr << "Error -- trying to take LU decomp of a singular matrix" 
             << endl;
        // use ad_exit() so that debugger can trace this
        ad_exit(1);
      }
      scale(i)=1.0/value(max(fabs(M(i))));
    }
    // get upper and lower parts of LU
    dmatrix & alpha = clu.get_L();
    dmatrix & gamma = clu.get_U(); // gamma is the transpose of beta
    ivector & index=clu.get_index();
    ivector & index2=clu.get_index2();
    int sign=clu.get_sign();
    // copy M into alpha and gamma
    for (i=mmin;i<=mmax;i++)
    {
      for (int j=mmin;j<=mmax;j++)
      {
        clu(i,j)=value(M(i,j));
      }
    }
    for (j=mmin;j<=mmax;j++)
    {
      int i;
      for (i=mmin+1;i<j;i++)
      {
        // using subvector here
        clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
      }
      double maxterm=0.0;
      for (i=j;i<=mmax;i++)
      {
        // using subvector here
        if (j>1)
        {
          clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
        }
        double tmp=scale(i)*fabs(clu(i,j));
        if (tmp>maxterm)
        {
          maxterm=tmp;
          imax=i;
        }
      }
      if (j!=imax)
      {
        // have to do this element-wise
        for (k=mmin;k<=mmax;k++)
        {
          double tmp=clu(imax,k);
          clu(imax,k)=clu(j,k);
          clu(j,k)=tmp;
        }
        scale(imax)=scale(j);
        int itmp=index2(imax);
        index2(imax)=index2(j);
        index2(j)=itmp;
        sign=-sign;
      }
      index(j)=imax;
      if (clu(j,j)==0.0)
        clu(j,j)=eps;
      if (j!=mmax)
      {
        double z= 1.0/gamma(j,j);
        for (i=j+1;i<=mmax;i++)
        {
          alpha(i,j)*=z;
        }
      }
    }
    save_identifier_string("OZ1");
    M.save_dvar_matrix_value();
    M.save_dvar_matrix_position();
    save_identifier_string("OZ2");
    index2.save_ivector_value();
    index2.save_ivector_position();
    save_identifier_string("OZ");
    return clu;
  }
  static void df_my_ln_det(void);
  dvariable my_ln_det(const dvar_matrix & M,int & sign)
  {
    cltudecomp clu1=xludecomp_pivot(M);
    sign=clu1.get_sign();
    ivector index2=clu1.get_index2();
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    double lndet=0.0;
    dmatrix & gamma=clu1.get_U();
    dmatrix & alpha=clu1.get_L();
    // only need to save the diagonal of gamma
    for (int i=mmin;i<=mmax;i++)
    {
      if (gamma(i,i)<0)
      {
        sign=-sign;
        lndet+=log(-gamma(i,i));
      }
      else
      {
        lndet+=log(gamma(i,i));
      }
    }
    dvariable vldet=nograd_assign(lndet);  
      
    save_identifier_string("OT");
    vldet.save_prevariable_position();
    gradient_structure::GRAD_STACK1->
    set_gradient_stack(df_my_ln_det);
    return vldet;
  }
  static void df_my_ln_det(void)
  {
    double dflndet=restore_prevariable_derivative();
    verify_identifier_string("OT");
  
    // adjoint code for ln_det calc
    cltudecomp_for_adjoint clu1;
    
    clu1.ludecomp_pivot_for_adjoint_1();
    cltudecomp dfclu1=clu1.get_dfclu();
    dmatrix_for_adjoint gamma=clu1.get_U();
    dmatrix dfgamma=dfclu1.get_U();
    dmatrix dfalpha=dfclu1.get_L();
    dfalpha.initialize();
    dfgamma.initialize();
    int mmin=clu1.indexmin();
    int mmax=clu1.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      if (gamma(i,i)<0)
      {
        //sign=-sign;
        //lndet+=log(-gamma(i,i));
        dfgamma(i,i)=dflndet/gamma(i,i);
      }
      else
      {
        dfgamma(i,i)=dflndet/gamma(i,i);
      }
    }
    clu1.ludecomp_pivot_for_adjoint_2();
  }
  // *************************************************************8
  // *************************************************************8
  //split  ludecomp_pivot_for_adjoint into two parts
  // *************************************************************8
  // *************************************************************8
  void cltudecomp_for_adjoint::ludecomp_pivot_for_adjoint_1(void)
  {
    int i,j;
    verify_identifier_string("OZ");
    ivector_position vpos=restore_ivector_position();
    ivector tmpindx2=restore_ivector_value(vpos);
    verify_identifier_string("OZ2");
    if (pMpos)
    {
      delete pMpos;
      pMpos=0;
    }
    pMpos=new dvar_matrix_position(restore_dvar_matrix_position());
    dmatrix M=restore_dvar_matrix_value(*pMpos);
    verify_identifier_string("OZ1");
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    cltudecomp_for_adjoint & clu=*this;
    clu.allocate(mmin,mmax,3,2);
    indx2=tmpindx2;
   
 
    // get upper and lower parts of LU
    dmatrix_for_adjoint & alpha = get_L();
    dmatrix_for_adjoint & gamma = get_U(); // gamma is the transpose of beta
    // copy M into alpha and gamma
    // OUTER LOOP1
    for (i=mmin;i<=mmax;i++)
    {
      int i1=indx2(i);
      for (int j=mmin;j<=mmax;j++)
      {
        clu(i,j)=M(i1,j);
      }
    }
    // OUTER LOOP2
    for (j=mmin;j<=mmax;j++)
    {
      int i;
      // INNER LOOP 2 1
      for (i=mmin+1;i<j;i++)
      {
        // using subvector here
        //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        clu.increment(i,j);
        clu(i,j)=tmp;
      }
      // INNER LOOP 2 2
      for (i=j;i<=mmax;i++)
      {
        // using subvector here
        if (j>1)
        {
          //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          double tmp=clu(i,j)-alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          clu.increment(i,j);
          clu(i,j)=tmp;
        }
      }
      // INNER LOOP 2 3
      if (j!=mmax)
      {
        double z= 1.0/gamma(j,j);
        for (i=j+1;i<=mmax;i++)
        {
          double tmp=alpha(i,j);
          clu.increment(i,j);
          alpha(i,j)=tmp*z;
        }
      }
    }
  }
  void cltudecomp_for_adjoint::ludecomp_pivot_for_adjoint_2(void) 
  {
    int i,j;
    int mmin=indexmin();
    int mmax=indexmax();
    cltudecomp_for_adjoint & clu=*this;
 
    // get upper and lower parts of LU
    dmatrix_for_adjoint & alpha = clu.get_L();
    dmatrix_for_adjoint & gamma = clu.get_U(); // gamma is the transpose of beta
    dmatrix & dfalpha = dfclu.get_L();
    dmatrix & dfgamma = dfclu.get_U(); 
    for (j=mmax;j>=mmin;j--)
    {
      // INNER LOOP 2 3
      if (j!=mmax)
      {
        // need to keep this line for  z
        double z= 1.0/gamma(j,j);
        //for (i=j+1;i<=mmax;i++)
        double dftmp=0.0;
        double dfz=0.0;
        for (i=mmax;i>=j+1;i--)
        {
          // need to keep this line for tmp 
          clu.decrement(i,j);
          double tmp=alpha(i,j);
          //alpha(i,j)=tmp*z;
          dftmp+=dfalpha(i,j)*z;
          dfz+=dfalpha(i,j)*tmp;
          dfalpha(i,j)=0.0;
          //double tmp=alpha(i,j);
          dfalpha(i,j)=dftmp;
          dftmp=0.0;
        }
        //double z= 1.0/gamma(j,j);
        dfgamma(j,j)-=dfz/square(gamma(j,j));
        dfz=0.0;
        
      }
      // INNER LOOP 2 2
      //for (i=j;i<=mmax;i++)
      double dftmp=0.0;
      for (i=mmax;i>=j;i--)
      {
        // using subvector here
        if (j>1)
        {
          //clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          //double tmp=clu(i,j)-alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
          //clu.increment(i,j);
          //clu(i,j)=tmp;
          clu.decrement(i,j);
          dftmp=dfclu(i,j);
          dfclu(i,j)=0.0;
          dfclu(i,j)=dftmp;
          dfalpha(i)(mmin,j-1)-=dftmp*gamma(j)(mmin,j-1);
          dfgamma(j)(mmin,j-1)-=dftmp*alpha(i)(mmin,j-1);
          dftmp=0.0;
        }
      }
      // INNER LOOP 2 1
      //for (i=mmin+1;i<j;i++)
      for (i=j-1;i>=mmin+1;i--)
      {
        // using subvector here
        //clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        //clu.increment(i,j);
        //clu(i,j)=tmp;
        clu.decrement(i,j);
        dftmp=dfclu(i,j);
        dfclu(i,j)=0.0;
        //double tmp=clu(i,j)-alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
        dfclu(i,j)=dftmp;
        dfalpha(i)(mmin,i-1)-=dftmp*gamma(j)(mmin,i-1);
        dfgamma(j)(mmin,i-1)-=dftmp*alpha(i)(mmin,i-1);
        dftmp=0.0;
      }
    }
    // OUTER LOOP1
    dmatrix dfM(mmin,mmax,mmin,mmax);
    for (i=mmin;i<=mmax;i++)
    {
      int i1=indx2(i);
      for (int j=mmin;j<=mmax;j++)
      {
        // clu(i,j)=M(i1,j);
        dfM(i1,j)=dfclu(i,j);
      }
    }
    dfM.save_dmatrix_derivatives(*pMpos);
  }
#include <admodel.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <testadj6.htp>

model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
 n=10;
  M.allocate(1,n,1,n);
 random_number_generator rng(177);
 M.fill_randn(rng);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  initializationfunction();
  VM.allocate(1,n,1,n,"VM");
 VM=M;
  f.allocate("f");
}

void model_parameters::userfunction(void)
{
 int sgn=0;
 //f=my_ln_det(VM,sgn);
 f=ln_det(VM,sgn);
}

void model_parameters::preliminary_calculations(void){
  admaster_slave_variable_interface(*this);
}

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

void model_parameters::report(void){}

void model_parameters::final_calcs(void){}

void model_parameters::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
    ad_set_new_handler();
  ad_exit=&ad_boundf;
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

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}
