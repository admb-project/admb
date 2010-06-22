
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

    cltudecomp(int l,int u) : /* L(l,u,l,u), U(l,u,l,u),*/ indx(l,u)
    {
      ivector in(l+1,u);
      in.fill_seqadd(l,1);
      L.allocate(l+1,u,l,in);
      ivector in1(l,u);
      in1.fill_seqadd(l,1);
      U.allocate(l,u,l,in1);
    }

    cltudecomp & operator = (const dmatrix& M)
    {
      int mmin=indexmin();
      int mmax=indexmax();

      if (mmin != M.indexmin() ||
          mmax != M.indexmax())
      {
        cerr << "Shape error in =" << endl;
        ad_exit(1);
      }
      for (int i=mmin;i<=mmax;i++)
        for (int j=mmin;j<=mmax;j++)
          elem(i,j)=M(i,j);
      return *this;
    }
      

    cltudecomp & assign_value (const dvar_matrix& M)
    {
      int mmin=indexmin();
      int mmax=indexmax();

      if (mmin != M.indexmin() ||
          mmax != M.indexmax())
      {
        cerr << "Shape error in =" << endl;
        ad_exit(1);
      }
      for (int i=mmin;i<=mmax;i++)
        for (int j=mmin;j<=mmax;j++)
          elem(i,j)=value(M(i,j));
      return *this;
    }
      

    

    dmatrix & get_L(){ return L;}
    dmatrix & get_U(){ return U;}
    ivector & get_index(){ return indx;}
    int indexmin() { return U.indexmin();}
    int indexmax() { return U.indexmax();}
    double & get_sign(){ return sign;}
    double & elem(int i,int j){ if (i>j)
                                         return L(i,j);
                                       else
                                         return U(j,i);
                                     }
    double & operator() (int i,int j){ if (i>j)
                                         return L(i,j);
                                       else
                                         return U(j,i);
                                     }
  };

  cltudecomp ludecomp(const dvar_matrix & M,int pivot_flag=1);
  cltudecomp ludecomp(const dmatrix & M,int pivot_flag=1);
  dvector solve(const cltudecomp & clu,const dvector & x);
  dvector get_implicit_scale(const dmatrix& M);
  dvector get_implicit_scale(const dvar_matrix& M);
  dmatrix inv(const dmatrix & M);
  dmatrix solve(const dmatrix & M,const dmatrix& B);
  void dfsolve(const cltudecomp & clu,const dvector & x,
    const cltudecomp & _dfclu,const dvector& dftmp1);
  void dfludecomp(const cltudecomp & clu,const cltudecomp & dfclu );
