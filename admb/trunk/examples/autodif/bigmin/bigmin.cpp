#include <fvar.hpp>
#define TINY 1.0e-20;
#ifdef __TURBOC__
  #pragma hdrstop
  #include <iomanip.h>
  extern unsigned _stklen=24000;
#endif

#ifdef __ZTC__
  #include <iomanip.hpp>
  unsigned _stack=24000;
#endif


double fff(dvar_vector& x);

// finds a the minimum of a funtion of the elements of
// a nsize*nize matrix
//int nsize=100; // 10,000 variables!
int nsize=10; 

int main()
{
  int nvar=nsize*nsize;
  independent_variables x(1,nvar);
  int ii=0;
  double f;
  dvector g(1,nvar);
  x.fill_randu(1001);
  // ifstream infile("matinv.est");
  // infile >> x;

  if (nvar>200)
    gradient_structure::set_MAX_NVAR_OFFSET(nvar);

 gradient_structure::set_GRADSTACK_BUFFER_SIZE(200);
 gradient_structure gs(400000L);

 fmmc fmc(nvar);
 fmc.crit1=.05;


  int ij=0;
  int ireturn=1;
  long int icount=0;
  while (fmc.ireturn>=0)
  {
    fmc.fmin(f,x,g);
    if (fmc.ireturn>0)
    {
      f=fff(x);
      cout << "f = " << f << endl;
      gradcalc(nvar,g);
    }
  }
  ofstream outfile("matinv.est");
  outfile << x << endl;
  return 0;
}

double fff(dvar_vector& x)
{
  dvar_matrix M(1,nsize,1,nsize);
  int ii=0;
  dvariable f=0.0;
  dvariable tmp=0.0;
  for (int i=1;i<=nsize;i++)
  {
    for (int j=1;j<=nsize;j++)
    {
      M[i][j]=x[++ii];
    }
    M[i][i]+=1.0;
  }
  dvar_matrix N=inv(M);
  {
    tmp=norm(M);
    f=tmp*tmp; 
  }

  {
    tmp=norm(N);
    f+=tmp*tmp; 
  }

  tmp=0.;
  for (i=1;i<=nsize;i++)
  {
    tmp+=M[i][i]*M[i][i];
  }
  f-=.01*tmp;
  tmp=0.;
  for (i=1;i<=nsize;i++)
  {
     tmp+=N[i][i]*N[i][i];
  }
  f-=.01*tmp;
  return value(f);
}

