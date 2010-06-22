#include <admodel.h>

  class cltudecomp
  {
    dmatrix L;
    dmatrix U;
    ivector indx;
    double sign;
  public:
    void initialize(void) 
    { 
      indx.initialize();
      sign=0;
      L.initialize(); 
      U.initialize(); 
      for (int i=L.indexmin();i<=L.indexmax();i++)
      {
        L(i,i)=1.0;
      }
    }

    cltudecomp(const dmatrix& alpha,const dmatrix& gamma){};

    cltudecomp(int l,int u) : indx(l,u)
    {
      ivector iv(l+1,u);
      iv.fill_seqadd(l,1);
      L.allocate(l+1,u,l,iv);
      ivector iv1(l,u);
      iv1.fill_seqadd(l,1);
      U.allocate(l,u,l,iv1);
    }
    dmatrix & get_L(){ return L;}
    int indexmin(){return U.indexmin();}
    int indexmax(){return U.indexmax();}
    dmatrix & get_U(){ return U;}
    ivector & get_index(){ return indx;}
    double & get_sign(){ return sign;}
    // overload () (int,int) to look like Numerical Recipes
    double & operator() (int i,int j){ if (i>j)
                                         return L(i,j);
                                       else
                                         return U(j,i);
                                     }
  };

 /*
  class vltudecomp
  {
    dvar_matrix L;
    dvar_matrix U;
    ivector indx;
    double sign;
  public:
    void initialize(void) 
    { 
      indx.initialize();
      sign=0;
      L.initialize(); 
      U.initialize(); 
      for (int i=L.indexmin();i<=L.indexmax();i++)
      {
        L(i,i)=1.0;
      }
    }

    vltudecomp(int l,int u) : indx(l,u)
    {
      ivector iv(l+1,u);
      iv.fill_seqadd(l,1);
      L.allocate(l+1,u,l,iv);
      ivector iv1(l,u);
      iv1.fill_seqadd(l,1);
      U.allocate(l,u,l,iv1);
    }
    dvar_matrix & get_L(){ return L;}
    int indexmin(){return U.indexmin();}
    int indexmax(){return U.indexmax();}
    dvar_matrix & get_U(){ return U;}
    ivector & get_index(){ return indx;}
    double & get_sign(){ return sign;}
    // overload () (int,int) to look like Numerical Recipes
    dvariable & operator() (int i,int j){ if (i>j)
                                         return L(i,j);
                                       else
                                         return U(j,i);
                                     }
  };
 */

  // LU decomp wihout partial pivoting
  cltudecomp ludecomp(const dmatrix & M)
  {
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    cltudecomp clu(mmin,mmax);
 
    // get upper and lower parts of LU
    dmatrix & alpha = clu.get_L();
    dmatrix & gamma = clu.get_U(); // gamma is the transpose of beta
    // copy M into alpha and gamma
    for (int i=mmin;i<=mmax;i++)
    {
      for (int j=mmin;j<=mmax;j++)
      {
        clu(i,j)=M(i,j);
      }
    }
    for (int j=mmin;j<=mmax;j++)
    {
      int i;
      for (i=mmin+1;i<j;i++)
      {
        // using subvector here
        clu(i,j)-=alpha(i)(mmin,i-1)*gamma(j)(mmin,i-1);
      }
      for (i=j;i<=mmax;i++)
      {
        // using subvector here
        if (j>1)
        {
          clu(i,j)-=alpha(i)(mmin,j-1)*gamma(j)(mmin,j-1);
        }
      }
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
  class dvector_for_adjoint  
  {
    dmatrix D;
    ivector count;
  public:
   int indexmin() { return D.indexmin();}
   int indexmax() { return D.indexmax();}
   double& operator () (int i) { return D(i,count(i)); }
   dvector_for_adjoint operator () (int & mmin,int mmax) 
   { 
     ivector iv = count(mmin, mmax);
     dmatrix dm = D.sub(mmin,mmax);
     return dvector_for_adjoint(dm,iv);
   }
   dvector_for_adjoint(dmatrix & _D,ivector& _count) :
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

   void increment(int i,int j) { count(i,j)++; }
   void decrement(int i,int j) { count(i,j)--; }

   double& operator () (int i,int j) { return D(i,j,count(i,j)); }
   void allocate(int l,int u,int l1,ivector & iv,int l2,int u2)
   {
     D.allocate(l,u,l1,iv,l2,u2);
     count.allocate(l,u,l1,iv);
     count=1;
   }
  };  


  class cltudecomp_for_adjoint
  {
    dmatrix_for_adjoint L;
    dmatrix_for_adjoint U;
    ivector indx;
    double sign;
  public:
    void initialize(void) 
    { 
      indx.initialize();
      sign=0;
      L.initialize(); 
      U.initialize(); 
      for (int i=L.indexmin();i<=L.indexmax();i++)
      {
        L(i,i)=1.0;
      }
    }
      
    int indexmin(){return U.indexmin();}
    int indexmax(){return U.indexmax();}

    cltudecomp_for_adjoint(int l,int u,int n,int m) : indx(l,u)
    {
      ivector iv(l+1,u);
      iv.fill_seqadd(l,1);
      L.allocate(l+1,u,l,iv,1,n);
      ivector iv1(l,u);
      iv1.fill_seqadd(l,1);
      U.allocate(l,u,l,iv1,1,m);
    }

    dmatrix_for_adjoint & get_L(){ return L;}
    dmatrix_for_adjoint & get_U(){ return U;}
    ivector & get_index(){ return indx;}
    double & get_sign(){ return sign;}
    // overload () (int,int) to look like Numerical Recipes
    void decrement(int i,int j)
    { 
      if (i>j)
        L.increment(i,j);
      else
        U.increment(j,i);
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

extern "C"  {
  void ad_boundf(int i)
  {
    // so we can stop here
    exit(i);
  }
}

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

dmatrix get_lower_dmatrix(cltudecomp_for_adjoint& clu)
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

dmatrix get_upper_dmatrix(cltudecomp_for_adjoint& clu)
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

 
int main()
{
  ad_exit=&ad_boundf;
  int n=3;
  dmatrix C(1,n,1,n);
  dmatrix Id(1,n,1,n);
  random_number_generator rng(873);
  C.fill_randn(rng);
  Id.initialize();
  for (int i=1;i<=n;i++)
    Id(i,i)=1.0;

  cltudecomp clu = ludecomp(C);


  /*cltudecomp_for_adjoint clufa = ludecomp_for_adjoint(C);

  int mmin=clu.indexmin();
  int mmax=clu.indexmax();
  double tmp=0.0;

  for (i=mmin;i<=mmax;i++)
  {
    for (int j=mmin;j<=mmax;j++)
    {
      tmp+=square(clu(i,j)-clufa(i,j));
    }
  }
  cout << get_dmatrix(clu)-get_dmatrix(clufa) << endl;
  cout << norm2(get_lower_dmatrix(clufa)*get_upper_dmatrix(clufa)-C) 
       << endl;
*/

  dmatrix product = get_dmatrix(clu);

  cout << C << endl << endl;

  cout << product << endl;

  return 0;

}

// adjoint code
  dmatrix ludecomp_for_adjoint(const dmatrix & M,
    dmatrix& dfalpha,dmatrix & dfgamma)
  {
    cltudecomp dfclu(dfalpha,dfgamma);
    int mmin=M.indexmin();
    int mmax=M.indexmax();
    cltudecomp_for_adjoint clu(mmin,mmax,3,2);
 
    // get upper and lower parts of LU
    dmatrix_for_adjoint & alpha = clu.get_L();
    dmatrix_for_adjoint & gamma = clu.get_U(); // gamma is the transpose of beta
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
          dfalpha(i,j)=tmp;
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
          dvector x;
          dvector y;
           x-=y; 
          dftmp*gamma(j)(mmin,j-1);
          dfalpha(i)(mmin,j-1)-=dftmp*gamma(j)(mmin,j-1);
          dfgamma(j)(mmin,j-1)-=dftmp*alpha(i)(mmin,j-1);
          dftmp=0.0;
        }
      }
      // INNER LOOP 2 1
      for (i=mmin+1;i<j;i++)
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
